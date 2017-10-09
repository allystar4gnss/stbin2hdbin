/*
	Allystar 2017
*/

#include <math.h>

#include "clibs.h"

#include "gpOS.h"

//#include "hdbin.h"
//#include "gnss_nvmids.h"
#include "gnss_api.h"
#include "gnssapp_plugins.h"
#include "gnss_debug.h"
//#include "geom.h"

#if !defined(__linux__) && !defined(_WIN32_WCE)
#include "svc_ver.h"
#endif

#include "gps_nvm.h"
#include "gnss_events.h"
#include "gnssapp.h"
#include "gp_core.h"
#include "rtc.h"
#include "nmea.h"

#include "sw_config.h"
#include "platform.h"

#if defined( NVM_NOR ) || defined( NVM_SQI )
#include "gps_nvm_swap_mgr.h"
#endif

#if defined( STBIN_FRONTEND_SUPPORT )
#include "frontend.h"
#endif

#include "datum.h"

#ifdef _FLASH_DATA_BACKUP
#include "gps_nvm.h"
#endif
#ifdef _RAM_DATA_BACKUP
#include "gps_nvm_backup.h"
#endif

#ifdef RTCM_LINKED
#include "dgps.h"
#include "dgps_hdr.h"
#include "dgps_sat.h"
#endif

#ifdef ST_AGPS
#include "st_agps.h"
//#ifdef ST_AGPS_TESTING
#include "st_agps_testing.h"
//#endif
#endif



#ifdef __ARMCC_VERSION
//#include "mmu.h"
#endif

#ifdef RTC_ERROR_TEST
#include "gps_rtc.h"
#endif

#if defined ( STBIN_ADC_SUPPORT )
#if defined( __STA8088__ )
#include "lld_adc_sta8088.h"
#endif
#if defined( __STA8090__ )
#include "lld_adc_sta8090.h"
#endif
#include "svc_adc.h"
#endif

#include "svc_pwr.h"
#include "svc_mcu.h"

#if defined( STBIN_SQI_DATASTORAGE )
#include "svc_sqi.h"
#endif

#include "error_handler.h"

//------------- Structure of OUTPUT MESSAGES-------------------------------------------//
#include "stbin_gen_structs.h"
#include "stbin_gen_checks.h"

#include "hdbin.h"

#define NUM_BYTE_LEN	0x02U
#define NUM_BYTE_CHK	0x02U

#define ERROR    -1
#define ONE_BYTE 0x01U
#define TWO_BYTE 0x02U
#define THREE_BYTE 0x03U
#define EIGHT_BYTE 0X08U
#define ON  1U
#define OFF 0U
#define FIRST_BYTE 0
#define VAL_NULL   OFF
#define VAL_ONE    ON
#define VAL_100    100

typedef enum msg_state_e
{
  START_SEQUENCE_DETECTION          = 0,
  START_SEQUENCE_DETECTION_SYNC2    = 1,
  MESSAGE_GROUP_ID_DETECTION        = 2,
  MESSAGE_SUB_ID_DETECTION          = 3,
  MESSAGE_LEN_DETECTION             = 4,
  MESSAGE_DATA_DECODING             = 5,
  ERROR_MESSAGE_CORRUPTED           = 6
} msg_state_t;

static boolean_t   msg_sync_flag = FALSE;
static msg_state_t msg_state = START_SEQUENCE_DETECTION;

typedef struct stbin_header_s3
{
  tUInt padding_sync;           /* first 2 bytes are not transmitted */
  frame_qualifier_t qualifier;  /* CID+MID+LEN+STATUSbits */
} stbin_header_t3;

#define HDBIN_MAX_PAYLOAD_SIZE 950U
#define HDBIN_MAX_BUFFER_SIZE  (HDBIN_MAX_PAYLOAD_SIZE+sizeof(stbin_header_t3)+sizeof(tDouble))

/*=============================================================
 * Macro definition for decode the field bytes defined
 * in the frame rx, in order to  compose the fields used in the
 * GNSS API
 * ============================================================*/
#define TRUNC_FFFF 0xFFFFU
#define TRUNC_FF00 0xFF00U
#define TRUNC_FF   0xFFU
#define SHIFT      0x08U

#define RETURN_HB(val)            (tChar)(val >> SHIFT)
#define RETURN_LB(value)          (value & TRUNC_FF)
#define RETURN_USHORT(valHB, valLB) (tU16)((((tU16)valHB << SHIFT) & TRUNC_FF00)|(valLB & TRUNC_FF))
#define RADIANS                   (PI / 180.0)
#define I4  32
#define I16 16
#define I32 I4

typedef union {
  tUChar buffer[HDBIN_MAX_BUFFER_SIZE];
  tDouble dummy;  /* This field force 8byte-alignment of buffer */
} hdbin_buffer_io_type;

//Decode manager: HD parse
static void DecodeHdMsg_Manager               (tU16, tUChar *, const hdbin_req_msg_parms *);
static stbin_status_t base_DecodeHdMsg_Manager(tU16, tUChar *, const hdbin_req_msg_parms *);

// if frame does is not complete in this time window, drop it
#define STBIN_FRAME_TIMEOUT_TICKS (10.0*NAV_CPU_TICKS_PER_SECOND)

//extern
extern void stbin_exec_init_cold_start(tU8);
extern tU32 stbin_ioport_read( tChar *, tU32, gpOS_clock_t*);

//-------------------------------------------------------------------------------------//
static hdbin_status_t hd_cs_compare(hdbin_chkSum_t *cs_a, uint8 cs_0_b, uint8 cs_1_b)
{
  hdbin_status_t result;

  if((cs_a->cs_0 == cs_0_b) && (cs_a->cs_1 == cs_1_b)) {
		result= HDBIN_OK;
  } else {
		result= HDBIN_FAILED;
  }

	return result;
}
static void hd_cs_add_data(tUChar *buf, tU16 len, hdbin_chkSum_t *cs)
{
  tUInt i;
  tUInt cs_0 = cs->cs_0;
  tUInt cs_1 = cs->cs_1;

  for(i = 0; i < len; i++) {
    cs_0 += buf[i];
    cs_1 += cs_0;
  }
  cs->cs_0 = (uint8) cs_0;
  cs->cs_1 = (uint8) cs_1;
}
static void hd_cs_header(uint8 group_id, uint8 sub_id, tU16 msg_len, hdbin_chkSum_t *cs)
{
  cs->cs_0 = 0;
  cs->cs_1 = 0;

  hd_cs_add_data(&group_id, 1, cs);
  hd_cs_add_data(&sub_id, 1, cs);
  hd_cs_add_data((tUChar *)&msg_len, 2, cs);
}

//-----------------------------HDBIN DECODE--------------------------------------------//
static void DecodeHdMsg_Manager(tU16 msg_length, tUChar *msg, const hdbin_req_msg_parms *parms)
{
  hdbin_status_t rc;
  //GPS_DEBUG_MSG(("HDBIN DEAL WITH CID=0x%X, MID=0x%X\n\r", cls_id, msg_id));

  // Check locally
  rc = base_DecodeHdMsg_Manager(msg_length, msg, parms);

  if(HDBIN_NOTFOUND == rc)
  { 
  	//We should never go to there unless play with new command.
    GPS_DEBUG_MSG(("HDBIN cmd was not found\n\r"));

    // Check in plugins
    //TODO
    //rc = gnssapp_plugins_stbin_cmdif_parse(msg_length, msg, parms);
  }

  if((HDBIN_FAILED == rc) || (HDBIN_NOTFOUND == rc))
  {
    // Return NACK if no success
    //TODO
    //Send_ACKorNACK(NACK, parms);
  }
}

static stbin_status_t base_DecodeHdMsg_Manager(tU16 msg_length, tUChar *msg, const hdbin_req_msg_parms *parms)
{
	hdbin_status_t rc;

	switch(parms->group_Id) {
		case HDBIN_GROUP_ID_CFG:
		  rc = hd_decode_cfg_req(msg_length, msg, parms);	
		  break;

		case HDBIN_GROUP_ID_NAV:
		  //TDOD
		  break;
		
		case HDBIN_GROUP_ID_MON:
		  //TODO
		  break;
		
		case HDBIN_GROUP_ID_AID:
		  //TODO
		  break;

		default:
		  break;
	}

	return rc;
}

//---------------------------- HDBIN MAIN ---------------------------------------------//
void hdbin_input_processing(void)
{
  hdbin_buffer_io_type msg;

  hdbin_read_binary_msg(msg.buffer);
}

void hdbin_read_binary_msg(tUChar *msg)
{
  tUChar ch;
  hdbin_chkSum_t cur_cs;
  tU32 io_rc;
  gpOS_clock_t frame_time_limit = 0;
  hdbin_req_msg_parms parms;
  hdbin_buffer_io_type MsgToSendResponse;
  tUChar  Len_field[NUM_BYTE_LEN];
  tU16    msg_length_ = 0,len_temp_, Bytes5_6_ = 0;
  tU32 i;

  parms.out_buf = &(MsgToSendResponse.buffer[sizeof(stbin_header_t3)]);
  do
    {
     /* Parse character */
     switch(msg_state)
     {
        case START_SEQUENCE_DETECTION:
          io_rc = stbin_ioport_read((tChar *)&ch, ONE_BYTE, gpOS_TIMEOUT_INFINITY);

          //In case of TimeOut simply return to caller
          if((ONE_BYTE == io_rc) && (ch == SYNC_BYTE_1) && (msg_sync_flag == FALSE))
          {
            msg_sync_flag = TRUE;
            msg_state =  START_SEQUENCE_DETECTION_SYNC2;
            frame_time_limit = gpOS_time_plus( gpOS_time_now(), (gpOS_clock_t)STBIN_FRAME_TIMEOUT_TICKS);
          }
          else
          {
            /*return in this point if sync_02=0x00*/
            if(msg_sync_flag == TRUE)
            {
              msg_state = ERROR_MESSAGE_CORRUPTED;
            }
          }
          break;
        case START_SEQUENCE_DETECTION_SYNC2:
          if(stbin_ioport_read((tChar *)&ch, ONE_BYTE, &frame_time_limit) == ONE_BYTE)
          {
            if((ch == SYNC_BYTE_2) && (msg_sync_flag == TRUE))
            {
              msg_state =  MESSAGE_GROUP_ID_DETECTION;
              parms.group_Id = VAL_NULL;
              parms.sub_Id   = VAL_NULL;
            }
            else
            {
              msg_state = ERROR_MESSAGE_CORRUPTED;
            }
          }
          else
          {
            msg_state = ERROR_MESSAGE_CORRUPTED;
          }
        break;
        case  MESSAGE_GROUP_ID_DETECTION:
          if(stbin_ioport_read((tChar *)&ch, ONE_BYTE, &frame_time_limit) == ONE_BYTE)
          {
        		parms.group_Id = ch;
        		msg_state = MESSAGE_SUB_ID_DETECTION;
          }
          else
          {
            msg_state = ERROR_MESSAGE_CORRUPTED;
          }
        break;
        case  MESSAGE_SUB_ID_DETECTION:
          if(stbin_ioport_read((tChar *)&ch, ONE_BYTE, &frame_time_limit) == ONE_BYTE)
          {
            	parms.sub_Id   = ch;
        		msg_state = MESSAGE_LEN_DETECTION;
          }
          else
          {
            msg_state = ERROR_MESSAGE_CORRUPTED;
          }
        break;
        case  MESSAGE_LEN_DETECTION:
          if(stbin_ioport_read((tChar *)Len_field, NUM_BYTE_LEN, &frame_time_limit) == NUM_BYTE_LEN)
          {
            Bytes5_6_ = (tU16) (RETURN_USHORT(Len_field[VAL_ONE], Len_field[VAL_NULL]));
            msg_length_ = Bytes5_6_;
            if(msg_length_ > STBIN_MAX_PAYLOAD_SIZE)
            {
              msg_state = ERROR_MESSAGE_CORRUPTED;
            }
            else
            {
              msg_state = MESSAGE_DATA_DECODING;
            }
          }
          else
          {
            msg_state = ERROR_MESSAGE_CORRUPTED;
          }
        break;

        case MESSAGE_DATA_DECODING:
        	len_temp_ = msg_length_ + NUM_BYTE_CHK; /*data-load + 2 byte of ck*/
        	if (len_temp_ >= NUM_BYTE_CHK)
        	{
            if( stbin_ioport_read((tChar *)msg, len_temp_, &frame_time_limit) == len_temp_)  /*get payload+CK from message rx*/
            {
              GPS_DEBUG_MSG(("HDBIN read checksum\r\n"));
              hd_cs_header(parms.group_Id, parms.sub_Id, Bytes5_6_, &cur_cs);
              hd_cs_add_data(msg, msg_length_, &cur_cs);
              if(hd_cs_compare(&cur_cs, msg[len_temp_-NUM_BYTE_CHK], msg[len_temp_-VAL_ONE]) == HDBIN_OK)
              {
                //GPS_DEBUG_MSG(("HDBIN good checksum buf@=0x%X rb=0x%X\n\r", (tU32)(parms.out_buf),
                //                (tU32)MsgToSendResponse.buffer));
              	GPS_DEBUG_MSG(("HDBIN dump payload+CK\r\n"));
                for(i=0; i<len_temp_; i++)
                	GPS_DEBUG_MSG(("0x%x ",msg[i]));

                /*CK ok!!! msg_lenght is only payload len - */
                DecodeHdMsg_Manager(msg_length_, msg, &parms );/*Decode message Terminate ok.*/
                msg_sync_flag = FALSE;
                msg_state = START_SEQUENCE_DETECTION;//restore START_SEQUENCE_DETECTION conditions
              }
              else
              {
                GPS_DEBUG_MSG(("\r\nHDBIN wrong checksum cs_0=0x%x cs_1=0x%x\r\n",cur_cs.cs_0,cur_cs.cs_1));
                /*CK Not ok --> Sending NACK*/
                /*restore START_SEQUENCE_DETECTION conditions Decode message Terminate error */
                msg_sync_flag = FALSE;
                msg_state = START_SEQUENCE_DETECTION;
                //TODO
                //Send_ACKorNACK(NACK, &parms);
              }
            }
            else
            {
                msg_state = ERROR_MESSAGE_CORRUPTED;
            }
        	}
        	else
        	{
        		msg_state = ERROR_MESSAGE_CORRUPTED;
        	}
        	break;
        case ERROR_MESSAGE_CORRUPTED:
        	msg_sync_flag = FALSE;
        	msg_state = START_SEQUENCE_DETECTION;
            parms.group_Id = HDBIN_GENERAL_ERROR_UNKNOW_ID;
            parms.sub_Id = HDBIN_GENERAL_ERROR_UNKNOW_ID;
        	//TODO
        	//Send_ACKorNACK(NACK, &parms);
        break;
        default:
        /* Should never go there */
        break;
     }

    }while(msg_state != START_SEQUENCE_DETECTION);
}


//----------------------------------HDBIN CFG -----------------------------------------//
hdbin_status_t
hd_decode_cfg_req(tU16 msg_length, tUChar *msg, const hdbin_req_msg_parms *parms)
{
	tU32 payload;

	switch(parms->sub_Id) {
		case HDBIN_SUB_ID_SIMPLERST: // CFG-SIMPLERST
		  //TODO
		  payload = msg[msg_length-1];
		  gnssapp_suspend();

		  if (payload == 0x01) {
		    //stbin_exec_init_cold_start() 
		  	stbin_exec_init_cold_start(1); 
		  }
		  else if (payload == 0x02) {
		    //stbin_exec_init_warm()
		  	gnss_clear_all_ephems();
		  }
		  else if (payload == 0x03) {
		    //stbin_exec_init_hot
		  	;
		  }

		  platform_gnss_suspend();
		  platform_gnss_restart();
		  gnssapp_restart();
		  break;

		default:
		  break;
	}

	return HDBIN_OK;
}
