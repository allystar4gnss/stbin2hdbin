/*****************************************************************************
   FILE:          stbin_plugins_sbas.c
   PROJECT:       GPS application
   SW PACKAGE:    GPS library and application
------------------------------------------------------------------------------
   DESCRIPTION:   The main application to run and test STA2062 GPS library
------------------------------------------------------------------------------
   COPYRIGHT:     (c) 2014 STMicroelectronics
------------------------------------------------------------------------------
   Created by : Michel Susini
           on : W421
*****************************************************************************/

/*!
 * @file    stbin_plugins_sbas.c
 * @brief   Plugin for STBIN support od SBAS/WAAS
 */

#ifdef WAAS_LINKED

/*****************************************************************************
   includes
*****************************************************************************/
#include "gnss_debug.h"
#include "waas.h"
#include "stbin.h"
#include "waas_plugin.h"
#include "stbin_waas_gen_structs.h"
#include "stbin_waas_gen_checks.h"

/*****************************************************************************
   external declarations
*****************************************************************************/

/*****************************************************************************
   defines and macros (scope: module-local)
*****************************************************************************/
#define WAAS_STBIN_OUTPUT_SBAS           0x33
#define WAAS_STBIN_OUTPUT_SBAS_DATA      0x34

#define ON  1
#define OFF 0

#define ONE_BYTE 0x01
#define TWO_BYTE 0x02
#define VAL_NULL OFF
#define VAL_ONE  ON

/*****************************************************************************
   typedefs and structures (scope: module-local)
*****************************************************************************/
typedef enum
{
	WAAS_STBIN_READ_WAAS_GET_MULTI_CH             = 0x13,
	WAAS_STBIN_READ_WAAS_GET_PRN_TO_DECODE        = 0x14,

}waas_stbin_read_waas_req;

typedef enum
{
	WAAS_STBIN_WRITE_WAAS_ON_OFF                 = 0x30,
	WAAS_STBIN_WRITE_WAAS_SAT                    = 0x31,
	WAAS_STBIN_WRITE_SBAS_SAT_LIST               = 0x32,
	WAAS_STBIN_WRITE_SBAS_PERIODIC_BACKUP        = 0x33,
	WAAS_STBIN_WRITE_SBAS_BACKUP                 = 0x34,
	WAAS_STBIN_WRITE_WAAS_SET_MULTI_CH_CMD       = 0x35,
	WAAS_STBIN_WRITE_WAAS_SET_PRN_TO_DECODE_CMD  = 0x36,
	WAAS_STBIN_WRITE_SBAS_AUTOSEAECH_CMD         = 0x37,

}waas_stbin_waas_write_req;

typedef enum
{
	WAAS_STBIN_TEST_SBAS_TEST                        = 0x1D,
}waas_stbin_test_waas_req;

typedef struct
{
  satid_t               sat_id;
  gnss_waas_status_t    status;
  boolean_t             debug_integrity_check;
} sbas_stbin_handler_t;

/*****************************************************************************
   global variable definitions  (scope: module-exported)
*****************************************************************************/

/*****************************************************************************
   function prototypes (scope: module-local)
*****************************************************************************/
static gnss_error_t read_WAAS_sat(tUChar waas_sat, tInt *sat);
static stbin_status_t waas_stbin_exec_waas_on_off_cmd(tU16 length, tUChar *msg, const stbin_req_msg_parms *parms_in);
static stbin_status_t waas_stbin_exec_waas_sat_cmd(tU16 length, tUChar *msg, const stbin_req_msg_parms *parms_in);
static stbin_status_t  waas_stbin_exec_sbas_sat_list(tU16 length, tUChar *msg, const stbin_req_msg_parms *parms_in);
static stbin_status_t waas_stbin_exec_sbas_periodic_backup(tU16 length, tUChar *msg, const stbin_req_msg_parms *parms_in);
static stbin_status_t waas_stbin_exec_sbas_backup(tU16 length, tUChar *msg, const stbin_req_msg_parms *parms_in);
static stbin_status_t waas_stbin_exec_waas_set_multi_ch(tU16 length, tUChar *msg, const stbin_req_msg_parms *parms_in);
static stbin_status_t waas_stbin_exec_waas_set_prn_to_decode(tU16 length, tUChar *msg, const stbin_req_msg_parms *parms_in);
static stbin_status_t waas_stbin_exec_sbas_autosearch_cmd(tU16 length, tUChar *msg, const stbin_req_msg_parms *parms_in);
static stbin_status_t waas_stbin_exec_waas_get_multi_ch(tU16 length, tUChar *msg, const stbin_req_msg_parms *parms_in);
static stbin_status_t waas_stbin_exec_waas_get_prn_to_decode(tU16 length, tUChar *msg, const stbin_req_msg_parms *parms_in);
static stbin_status_t waas_stbin_exec_sbas_test (tU16 length, tUChar *msg, const stbin_req_msg_parms *parms_in);
static void waas_stbin_output_exec_sbas(const stbin_output_msg_parms *parms);
static void waas_stbin_output_exec_sbas_data(const stbin_output_msg_parms *parms);
static stbin_status_t waas_stbin_Decode_WAAS_WRITE_req(tU16 msg_length, tUChar *msg, const stbin_req_msg_parms *parms_in);
static stbin_status_t waas_stbin_Decode_READ_WAAS_req (tU16 msg_length, tUChar *msg, const stbin_req_msg_parms *parms_in);
static stbin_status_t waas_stbin_Decode_TEST_WAAS_req(tU16 msg_length, tUChar *msg, const stbin_req_msg_parms *parms_in);
static stbin_status_t waas_stbin_decode_output_process(tU16 msg_length, tUChar *msg, const stbin_req_msg_parms *parms_in);

/*****************************************************************************
   global variable definitions (scope: module-local)
*****************************************************************************/
static const stbin_output_msg_def waas_stbin_outmsg_waas_list[] = {
  { waas_stbin_output_exec_sbas          , WAAS_STBIN_MASK_OUTPUT_SBAS          , STBIN_MASK_BANK_1, WAAS_STBIN_OUTPUT_SBAS           },
  { waas_stbin_output_exec_sbas_data     , WAAS_STBIN_MASK_OUTPUT_SBAS_DATA     , STBIN_MASK_BANK_1, WAAS_STBIN_OUTPUT_SBAS_DATA      },
};
#define WAAS_STBIN_NB_OUTPUT_MSG_IN_LIST     (sizeof(waas_stbin_outmsg_waas_list)/sizeof(waas_stbin_outmsg_waas_list[0]))

static waas_plugin_handler_t *waas_handler;

/*****************************************************************************
   function implementations (scope: module-local)
*****************************************************************************/
/********************************************//**
 * \brief   Execute test on WAAS module
 *
+ * \return  void
 *
 ***********************************************/
static void _execute_sbas_test(void)
{
  GPS_DEBUG_MSG( ( "\r\n\r\n\r\n[stbin][sbas]Initialising SBAS Test...\r\n" ) );

  waas_set_status(WAAS_STATUS_OFF);
  gnss_reset_diff_params();
  gpOS_task_delay(2000000);
  waas_set_status(WAAS_STATUS_ON);
}

static gnss_error_t read_WAAS_sat(tUChar waas_sat, tInt *sat)
{
  *sat = -1;

  if (waas_sat != 0U)
  {
    if( (waas_sat < 120U) || (waas_sat > 138U) )
    {
      if (waas_sat == 6U)
      {
        if( waas_handler->debug_integrity_check == FALSE)
        {
          waas_handler->debug_integrity_check = TRUE;
        }
        else
        {
          waas_handler->debug_integrity_check = FALSE;
        }

        waas_set_integrity_check( waas_handler->debug_integrity_check);
      }
      return(GNSS_ERROR);   /*lint !e904 Return statement before end of function */
    }
    else
    {
      *sat = waas_sat;
      return(GNSS_NO_ERROR);   /*lint !e904 Return statement before end of function */
    }
  }
  else
  {
    *sat = waas_sat;
    return(GNSS_NO_ERROR);  /*lint !e904 Return statement before end of function */
  }
}

//len = 0x01 payload (1 byte)= on or off
static stbin_status_t waas_stbin_exec_waas_on_off_cmd(tU16 length, tUChar *msg, const stbin_req_msg_parms *parms_in)
{
	stbin_status_t result = STBIN_OK;

	stbin_exec_waas_if_on_off_write_req_MAP(req, msg, length, &result);

  if(STBIN_OK == result) {
 	  waas_set_status((1 == req->onOff) ? WAAS_STATUS_ON : WAAS_STATUS_OFF);
	}

  return result;
}

static stbin_status_t waas_stbin_exec_waas_sat_cmd(tU16 length, tUChar *msg, const stbin_req_msg_parms *parms_in)
{
  tInt waas_sat_changed;
	stbin_status_t result = STBIN_OK;

	stbin_exec_waas_if_sat_write_req_MAP(req, msg, length, &result);

  if(STBIN_OK != result)
  {
    return result;  /*lint !e904 Return statement before end of function */
  }

  if(0 != req->sbasSatId) {
    if(read_WAAS_sat(req->sbasSatId, &waas_sat_changed) != GNSS_NO_ERROR)
		{
		  result = STBIN_FAILED;
		}
  } else {
    if(waas_automatic_search(&(waas_handler->sat_id)) == GNSS_ERROR)
		{
		  result = STBIN_FAILED;
    }
    else
		{
		  waas_sat_changed = waas_handler->sat_id;
    }
  }

  if(STBIN_OK != result)
  {
    return result;  /*lint !e904 Return statement before end of function */
  }

  waas_set_satellite(waas_sat_changed);

  return result;
}

static stbin_status_t  waas_stbin_exec_sbas_sat_list(tU16 length, tUChar *msg, const stbin_req_msg_parms *parms_in)
{
  stbin_status_t result=STBIN_OK;

  stbin_exec_sbas_sat_list_req_MAP(req, msg, length, &result);

  if(result==STBIN_OK)
  {
	  //set the sbas satellite list. In this case it is with 3 provider
	  waas_set_sbas_list( (tSbasInfo *)waas_handler->sbas_list, SBAS_PROVIDER_NUMBER);
  }

  return result;
}

/***************************************************************************
 * The sbas periodic backup enable is codified on one byte.  following are present the
 * byte/signals codifies:
 *
 * LEN=1
 * PAYLOAD -->
 * --------------------
 * |SBAS backup Status |
 * --------------------
 * SBAS ON  = 0x01 --> ACK
 * SBAS OFF = 0x00 --> ACK
 * Sbas other values = ERROR --> NACK
 * **************************************************************************/
static stbin_status_t waas_stbin_exec_sbas_periodic_backup(tU16 length, tUChar *msg, const stbin_req_msg_parms *parms_in)
{
  stbin_status_t result=STBIN_OK;

  stbin_exec_sbas_periodic_backup_req_MAP(req, msg, length, &result);

  if(result==STBIN_OK)
  {
	  if(req->onOff== ON)
	  {
		  waas_enable_periodic_data_backup(TRUE);
	  }
	  else if (req->onOff == OFF)
	  {
		  waas_enable_periodic_data_backup(FALSE);
	  }
	  else
	  {
		  result=STBIN_FAILED;
	  }
  }

  return result;
}

static stbin_status_t waas_stbin_exec_sbas_backup(tU16 length, tUChar *msg, const stbin_req_msg_parms *parms_in)
{
  stbin_status_t result=STBIN_OK;

  stbin_exec_sbas_backup_req_MAP(req, msg, length, &result);

  if(result==STBIN_OK)
  {
    waas_execute_data_backup();
  }

  return result;
}
//================================================================
// Len = 0x03  PAYLOAD = CH(1BYTE) + PRN(1BYTE) + STATUS(1BYTE)
//================================================================
static stbin_status_t waas_stbin_exec_waas_set_multi_ch(tU16 length, tUChar *msg, const stbin_req_msg_parms *parms_in)
{
	tInt ch,prn,status;
	stbin_status_t result=STBIN_OK;

	stbin_exec_waas_set_multi_ch_prn_write_req_MAP(req, msg, length,&result);

	if(result==STBIN_OK)
	{
		ch     = req->chan_id;
		prn    = req->sat_id;
		status = req->sbas_status;
		waas_set_multi_ch(ch,prn,(gnss_waas_status_t)status);
	}

	return result;
 }

static stbin_status_t waas_stbin_exec_waas_set_prn_to_decode(tU16 length, tUChar *msg, const stbin_req_msg_parms *parms_in)
{
  tInt sat_id;
  stbin_status_t result=STBIN_OK;

  stbin_exec_waas_set_prn_to_decode_write_req_MAP(req, msg, length,&result);

  if(result==STBIN_OK)
  {
	  sat_id = req->sat_id;
	  waas_set_prn_to_decode(sat_id);
  }

  return result;
 }

//==================================================================================
//len = 1 onoff (1byte)
//==================================================================================
static stbin_status_t waas_stbin_exec_sbas_autosearch_cmd(tU16 length, tUChar *msg, const stbin_req_msg_parms *parms_in)
{
	stbin_status_t result = STBIN_OK;

	stbin_exec_waas_autosearch_on_off_write_req_MAP(req, msg, length, &result);

  if(STBIN_OK == result) {
		switch (req->onOff)
		{
		case ON:
			waas_enable_autosearch();
			break;
		case OFF:
			waas_disable_autosearch();
			break;
		default:
			result = STBIN_FAILED;
			break;
		}
	}

	return result;
}

//len = 0x01 msg[0]=chan_ID
static stbin_status_t waas_stbin_exec_waas_get_multi_ch(tU16 length, tUChar *msg, const stbin_req_msg_parms *parms_in)
{
	tInt   chanid;
	satid_t sat_id;
	gnss_waas_status_t status;

	stbin_status_t result = STBIN_OK;

  frame_qualifier_t frameQ;
  PREPARE_OUTPUT_MESSAGE(parms_in->out_buf, waas_get_multi_ch_t, rsp, rspSize);

	stbin_exec_waas_get_multi_ch_MAP(req, msg, length,&result);

	if(result == STBIN_OK)
	{
		chanid = req->chan_id;
		if(waas_get_multi_ch( chanid, &sat_id, &status) != GNSS_ERROR)
		{
			//Load structure
			rsp->chan_id = req->chan_id;
			rsp->sat_id  = (tU8)sat_id;
			rsp->sbas_status = (tU8)status;

			frameQ = frame_ack_qualifier(parms_in->class_Id, parms_in->msg_Id, rspSize, ONLY_ONE_FRAME);
      waas_get_multi_ch_send(rsp, frameQ );
		}
		else
		{
			result = STBIN_FAILED;
		}
	}

	return result;
}
//len = 0x01 - payload null!
static stbin_status_t waas_stbin_exec_waas_get_prn_to_decode(tU16 length, tUChar *msg, const stbin_req_msg_parms *parms_in)
{
	satid_t sat_id;
	stbin_status_t result = STBIN_OK;

  frame_qualifier_t frameQ;
  PREPARE_OUTPUT_MESSAGE(parms_in->out_buf, waas_get_prn_to_decode_t, rsp, rspSize);

	stbin_exec_waas_get_prn_to_decode_MAP(req, msg, length,&result);

	if(result == STBIN_OK)
	{
		if(waas_get_prn_to_decode( &sat_id) != GNSS_ERROR)
		{
			rsp->sat_id  = (tU8)sat_id;

      frameQ = frame_ack_qualifier(parms_in->class_Id, parms_in->msg_Id, rspSize, ONLY_ONE_FRAME);
      waas_get_prn_to_decode_send(rsp, frameQ );
		}
		else
		{
			result = STBIN_FAILED;
		}
	}

	return result;
}

static stbin_status_t waas_stbin_exec_sbas_test (tU16 length, tUChar *msg, const stbin_req_msg_parms *parms_in)
{
	stbin_status_t result = STBIN_OK;

	stbin_exec_waastest_req_MAP(req, msg, length, &result);

  if(STBIN_OK != result)
  {
    return result;  /*lint !e904 Return statement before end of function */
  }

  _execute_sbas_test();

	return result;
}

static void waas_stbin_output_exec_sbas(const stbin_output_msg_parms *parms)
{
  satid_t                      sbasSatId;
  gnss_waas_status_t           sbasStatus;
  tInt                          i, iod;
  tDouble                       epoch, range, rate;
  boolean_t                    available;
  PREPARE_OUTPUT_MESSAGE(parms->out_buf, outputprocess_sbas_t, sbas, rspSize);
  frame_qualifier_t frameQ;

  if(GNSS_NO_ERROR == gnss_waas_get_status(&sbasSatId,&sbasStatus))
  {
    sbas->iTOW    = parms->currTow_mills;
    sbas->geoPrn  = (tU8)sbasSatId;
    sbas->service = (tU8)sbasStatus;

    //-----------------------------------------------------//
    //--------------------To be recoded with WAAS API -----//
    //-----------------------------------------------------//
    if((120U==sbasSatId)||(124U==sbasSatId)||(126U == sbasSatId))
    {
      sbas->sys   = (tS8)EGNOS;
    }
    else
    {
      if((122U==sbasSatId)||(133U==sbasSatId)||(134U==sbasSatId)||(135U == sbasSatId)||(138U == sbasSatId))
      {
        sbas->sys   = (tS8)WAAS;
      }
      else
      {
        if((129U==sbasSatId)||(137U==sbasSatId))
        {
          sbas->sys   = (tS8)MSAS;
        }
        else
        {
        if((127U==sbasSatId)||(128U==sbasSatId))
        {
          sbas->sys   = (tS8)GAGAN;
        }
        else
        {
          sbas->sys   = (tS8)NO_SERVICE;
        }
        }
      }
    }
    //-----------------------------------------------------//
    //-----------------------------------------------------//
    if (WAAS_STATUS_OFF == sbasStatus)
    {
      sbas->elevation = RESERVED_U8;
      sbas->azimuth   = RESERVED_U16;
      sbas->cno       = RESERVED_U8;
      sbas->cnt       = RESERVED_U8;
    }
    else
    {
      visible_sats_data_t sats_visible;
      sbas->elevation = (tU8)waas_sat_get_elevation(sbasSatId);
      sbas->azimuth   = (tU16)waas_sat_get_azimuth(sbasSatId);
      sbas->cno       = (tU8)gnss_get_sat_cn0(sbasSatId);

      gnss_get_sats_visible(&sats_visible);
      sbas->cnt       = RESERVED_U8;
      for (i=(sats_visible.list_size-1); i>=0; i--)
      {
        if(GPS_SAT_ID_VALID(sats_visible.list[i].satid) == TRUE)
        {
          gnss_get_diff_params(sats_visible.list[i].satid,&iod,&epoch,&range,&rate,&available);
          if (TRUE == available)
            sbas->cnt++;
        }
      }
    }

    frameQ = frame_ack_qualifier(parms->class_Id, parms->msg_Id, rspSize, ONLY_ONE_FRAME);
    outputprocess_sbas_send(sbas, frameQ );
  }
}

static void waas_stbin_output_exec_sbas_data(const stbin_output_msg_parms *parms)
{
  satid_t                      sbasSatId;
  gnss_waas_status_t           sbasStatus;
  tInt                          i, nb_sat, nb_sat_cnt, iod;
  tDouble                       epoch, range, rate;
  boolean_t                    available;
  frame_status_t          frame_seq;
  PREPARE_OUTPUT_MESSAGE(parms->out_buf, outputprocess_sbas_data_t, SbasInfo, rspSize);
  frame_qualifier_t frameQ;

  visible_sats_data_t sats_visible;

  nb_sat=0;
  nb_sat_cnt=0;


  if(GNSS_NO_ERROR == gnss_waas_get_status(&sbasSatId,&sbasStatus))
  {
    if (WAAS_STATUS_ON == sbasStatus)
    {
      gnss_get_sats_visible(&sats_visible);

      for (i=(sats_visible.list_size-1); i>=0; i--)
      {
        if(GPS_SAT_ID_VALID(sats_visible.list[i].satid) == TRUE)
        {
          gnss_get_diff_params(sats_visible.list[i].satid,&iod,&epoch,&range,&rate,&available);
          if (TRUE == available)
          {
            nb_sat++;
          }
        }
      }

      for (i=(sats_visible.list_size-1); i>=0; i--)
      {
        if(GPS_SAT_ID_VALID(sats_visible.list[i].satid) == TRUE)
        {

          gnss_get_diff_params(sats_visible.list[i].satid,&iod,&epoch,&range,&rate,&available);
          if (TRUE == available)
          {
            SbasInfo->svid             = (tU8)sats_visible.list[i].satid;
            SbasInfo->iod              = iod;
            SbasInfo->diff_epoch       = (tInt)(epoch         * SCALING_1000);
            SbasInfo->delta_range      = (tInt)(range         * SCALING_1000);
            SbasInfo->delta_range_rate = (tInt)(rate          * SCALING_1000);

            SbasInfo->total            = RESERVED_U32;
            SbasInfo->sat              = RESERVED_U32;
            SbasInfo->iono             = RESERVED_U32;
            SbasInfo->tropo            = RESERVED_U32;

            frame_seq = (0 == nb_sat_cnt) ? START_OF_SEVERAL_FRAMES : MIDDLE_OF_SEVERAL_FRAMES;
            frame_seq |= ((nb_sat -1) == nb_sat_cnt) ? END_OF_SEVERAL_FRAMES : MIDDLE_OF_SEVERAL_FRAMES;

            frameQ = frame_ack_qualifier(parms->class_Id, parms->msg_Id, rspSize, frame_seq);
            outputprocess_sbas_data_send(SbasInfo, frameQ );
            nb_sat_cnt++;

          }
        }
      }
    }
  }
}

static stbin_status_t waas_stbin_Decode_WAAS_WRITE_req(tU16 msg_length, tUChar *msg, const stbin_req_msg_parms *parms_in)
{
	stbin_status_t command_EXECUTE_status;

		switch( (waas_stbin_waas_write_req)parms_in->msg_Id )
		{
		    case WAAS_STBIN_WRITE_WAAS_ON_OFF:
		    	command_EXECUTE_status = waas_stbin_exec_waas_on_off_cmd(msg_length,msg, parms_in);
			break;
		    case WAAS_STBIN_WRITE_WAAS_SAT:
		    	command_EXECUTE_status = waas_stbin_exec_waas_sat_cmd(msg_length,msg, parms_in);
		    break;
		    case WAAS_STBIN_WRITE_SBAS_SAT_LIST:
		    	command_EXECUTE_status = waas_stbin_exec_sbas_sat_list(msg_length,msg, parms_in);
		    break;
		    case WAAS_STBIN_WRITE_SBAS_PERIODIC_BACKUP:
		    	command_EXECUTE_status = waas_stbin_exec_sbas_periodic_backup(msg_length,msg, parms_in);
		    break;
		    case WAAS_STBIN_WRITE_SBAS_BACKUP:
		    	command_EXECUTE_status = waas_stbin_exec_sbas_backup(msg_length,msg, parms_in);
		    break;
		    case WAAS_STBIN_WRITE_WAAS_SET_MULTI_CH_CMD:
		    	command_EXECUTE_status = waas_stbin_exec_waas_set_multi_ch(msg_length,msg, parms_in);
		    break;
		    case WAAS_STBIN_WRITE_WAAS_SET_PRN_TO_DECODE_CMD:
		    	command_EXECUTE_status = waas_stbin_exec_waas_set_prn_to_decode(msg_length,msg, parms_in);
		    break;
		    case WAAS_STBIN_WRITE_SBAS_AUTOSEAECH_CMD:
		    	 command_EXECUTE_status =  waas_stbin_exec_sbas_autosearch_cmd(msg_length,msg, parms_in);
		    break;
		    default :
		    	command_EXECUTE_status = STBIN_NOTFOUND;
		    break;
		}
	if(command_EXECUTE_status == STBIN_OK)
	{
		/*send ACK*/
		Send_ACKorNACK(ACK, parms_in);
	}

	return command_EXECUTE_status;
}

static stbin_status_t waas_stbin_Decode_READ_WAAS_req (tU16 msg_length, tUChar *msg, const stbin_req_msg_parms *parms_in)
{
	stbin_status_t command_EXECUTE_status;

	switch((waas_stbin_read_waas_req)parms_in->msg_Id)
	{
	case WAAS_STBIN_READ_WAAS_GET_MULTI_CH:
		command_EXECUTE_status = waas_stbin_exec_waas_get_multi_ch(msg_length, msg, parms_in);
		break;
	case WAAS_STBIN_READ_WAAS_GET_PRN_TO_DECODE:
		command_EXECUTE_status = waas_stbin_exec_waas_get_prn_to_decode(msg_length, msg, parms_in);
		break;
	default:
    command_EXECUTE_status = STBIN_NOTFOUND;
		break;
	}
	return command_EXECUTE_status;
}

static stbin_status_t waas_stbin_Decode_TEST_WAAS_req(tU16 msg_length, tUChar *msg, const stbin_req_msg_parms *parms_in)
{
	stbin_status_t command_EXECUTE_status;
	switch((waas_stbin_test_waas_req)parms_in->msg_Id)
	{
	case WAAS_STBIN_TEST_SBAS_TEST:
		command_EXECUTE_status = waas_stbin_exec_sbas_test(msg_length, msg, parms_in);
		break;
	default:
		command_EXECUTE_status = STBIN_NOTFOUND;
		break;
	}

	if(command_EXECUTE_status == STBIN_OK)
	{
		/*send ACK*/
		Send_ACKorNACK(ACK, parms_in);
	}

	return command_EXECUTE_status;
}

static stbin_status_t waas_stbin_decode_output_process(tU16 msg_length, tUChar *msg, const stbin_req_msg_parms *parms_in)
{
  return stbin_decode_output_process(msg_length, msg, parms_in,
                                     waas_stbin_outmsg_waas_list, WAAS_STBIN_NB_OUTPUT_MSG_IN_LIST);
}

/*****************************************************************************
   function implementations (scope: module-exported)
*****************************************************************************/

stbin_status_t stbin_waas_plugin_cmdif_parse(tU16 msg_length, tUChar *msg, const stbin_req_msg_parms *parms)
{
  stbin_status_t rc;

  switch(parms->class_Id)
  {
/*================== WRITE CMD =============================*/
  case STBIN_WAAS_WR_CLASS_ID:
	  rc = waas_stbin_Decode_WAAS_WRITE_req(msg_length, msg, parms);
    break;

/*================== READ CMD =============================*/
  case STBIN_WAAS_RD_CLASS_ID:
	  rc = waas_stbin_Decode_READ_WAAS_req(msg_length, msg, parms);
    break;

/*================== TEST CMD =============================*/
  case STBIN_WAAS_TS_CLASS_ID:
    rc = waas_stbin_Decode_TEST_WAAS_req(msg_length, msg, parms);
   break;

/*=================OUTPUT POLLED CMD RESPONSE===============*/
  case STBIN_WAAS_OUTPROCESS_CLASS_ID:
	  rc = waas_stbin_decode_output_process(msg_length, msg, parms);
    break;

  default://send nack if received a unknown class_id
	  rc = STBIN_NOTFOUND;
    break;
	}

	return rc;
}

void stbin_waas_plugin_outmsg_transmit(const tU32 *msg_list, const stbin_outProcess_input *in)
{
	stbin_output_msg_parms parms;
	tInt i;

  parms.currTow_mills = in->currTow_mills;
  parms.currTow_nanos = in->currTow_nanos;
	parms.class_Id = STBIN_WAAS_OUTPROCESS_CLASS_ID;
	parms.data_p = in->fix_data;
  parms.out_buf = in->outBuf;

  for(i=0;i<(tInt)WAAS_STBIN_NB_OUTPUT_MSG_IN_LIST;i++)
  {
    if((waas_stbin_outmsg_waas_list[i].mask & msg_list[waas_stbin_outmsg_waas_list[i].mask_bank]) != 0U)
    {
			parms.msg_Id = waas_stbin_outmsg_waas_list[i].msg_Id;
			waas_stbin_outmsg_waas_list[i].gen(&parms);
    }
  }
}

void stbin_waas_plugin_init(waas_plugin_handler_t *handler)
{
  waas_handler = handler;
}

#endif // WAAS_LINKED


