/*{{{  COMMENT Standard Header*/
/****************************************************************************************
 * COPYRIGHT (C) ST Microelectronics 1995,1996,1997,1998,1999
 *                                        All Rights Reserved
 *
 *----------------------------------------------------------------------------------------
 * Source file name : stbin.c
 * PURPOSE          :
 * Section SDK      : Source --> Modules --> stbin --> stbin.c
 * LANGUAGE         : C
 * MICRO_TYPE       : STA 8088
 * ---------------------------------------------------------------------------------------
 * Interpretes / Produces Binary commands on the proprietary STm protocol.
 * The binary commands are derived from the NMEA proprietary STm message.
 * The st binary protocol is mapped on the OSI layer.
 *
 * To performs all commands, this module are subdivided in three layers.
 *
 * =====================
 * 1) Data link layer. = function name convention : stbin_<nameFunction>
 * =====================
 * 2) Application layer= function name convention : stbin_exec_<nameFunction>
 * =====================
 * 3) Decoding layer.  = function name convention : stbin_dec_<nameFunction>
 * =====================
 *
 *---------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------
 * Intecs Notes:  New module created/added by intecs spa
 *
 * Customer : ST Microelectronics Naples/Arzano Italy
 * Project  : Supporto Teseo 2
 * Author   : Francesco Vaia
 * Date     : 16/10/2012 (start date) - STOP DATE (22/05/2013)
 * Version  : 1.6
 * ---------------------------------------------------------------------------------------
 * Dev Tasks:

 * **************************************************************************************/


/*}}}  */

#include <math.h>

#include "clibs.h"

#include "gpOS.h"

#include "stbin.h"
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

/*============ Structure of OUTPUT MESSAGES =============*/
#include "stbin_gen_structs.h"
#include "stbin_gen_checks.h"

#if defined(HDBIN_LINKED)
extern void hdbin_input_processing(void);
extern void hdbin_output_processing(void);
#endif

/*Modifies added to merge the binary protocol in gpsstdpkg SDK*/

typedef enum msg_state_e
{
  START_SEQUENCE_DETECTION          = 0,
  MESSAGE_CLASS_ID_DETECTION        = 1,
  MESSAGE_MSG_ID_DETECTION          = 2,
  MESSAGE_LEN_DETECTION             = 3,
  MESSAGE_DATA_DECODING             = 4,
  START_SEQUENCE_DETECTION_sync02   = 5,
  ERROR_MESSAGE_CORRUPTED           = 6
} msg_state_t;

#if (STBIN_LEN_STRING < gpOS_TASK_NAME_SIZE)
#error Please change STBIN_LEN_STRING generated value
#endif

#if (STBIN_SW_CONFIG_TEXT_LENGTH != SW_CONFIG_TEXT_LENGTH)
#error Please change STBIN_SW_CONFIG_TEXT_LENGTH generated value
#endif

#if (STBIN_WGS84_INDEX != _WGS84)
#error Please change STBIN_WGS84_INDEX generated value
#endif

#define ERROR        -1

#define ONE_BYTE 0x01U
#define TWO_BYTE 0x02U
#define THREE_BYTE 0x03U
#define EIGHT_BYTE   0X08U
#define ON  1U
#define OFF 0U
#define FIRST_BYTE 0
#define VAL_NULL OFF
#define VAL_ONE  ON
#define VAL_100  100

#define SYNC_BYTE_1                 0xAAU
#define SYNC_BYTE_2                 0xAAU

#define HEADER_LEN_MASK 0x03FFU
#define HEADER_STATUS_MASK 0xE000U
#define HEADER_STATUS_SHIFT 10U
#define HEADER_RESERVED_MASK 0x1C00U
#define HEADER_PADDING_SIZE 2
typedef struct stbin_header_s3
{
  tUInt     padding_sync;    /* first 2 bytes are not transmitted */
  frame_qualifier_t     qualifier;       /* CID+MID+LEN+STATUSbits */
} stbin_header_t3;

/* keep space at end on buffer to make sure of possible alignment for doubles */
#define STBIN_MAX_BUFFER_SIZE     (STBIN_MAX_PAYLOAD_SIZE+sizeof(stbin_header_t3)+sizeof(tDouble))

typedef union {
  tUChar buffer[STBIN_MAX_BUFFER_SIZE];
  tDouble dummy;  /* This field force 8byte-alignment of buffer */
} stbin_buffer_io_type;


//----------------MsgToSend_Byte6--------------------------
//|START | END  |  Ack |      |      |      |      |      |
//|  OF  |  OF  |   /  |   0  |   0  |   0  |   LengthHB  |
//|TRAMES|TRAMES| Nack |      |      |      |      |      |
//---------------------------------------------------------
typedef struct stbin_chkSum_s
{
  tU8    cs_0;
  tU8    cs_1;
} stbin_chkSum_t;


#define NUM_BYTE_LEN                0x02U
#define NUM_BYTE_CHK                0x02U
#define NUM_BYTE_LEN_CONST_MASK     0x05U

#define ERROR_GENERIC       0x19  //Frame corrupted
#define CONTROL_COMM_MSG_ID   0x81 //enable output messages
#define RETURN_IN_NMEA      0x78 //return in mnea communication

#define LEN_MAX_POS         0x0C ///*lenght of the gps position in the SET_GPS_POS*/

#define INDEX_LAT_MIN       0
#define INDEX_LAT_MAX       3
#define INDEX_LON_MIN       4
#define INDEX_LON_MAX       7
#define INDEX_HEIGHT_MIN    8
#define INDEX_HEIGHT_MAX    11
#define LAT_MAX_VAL         90
#define LAT_MIN_VAL        -90
#define LON_MAX_VAL         180
#define LON_MIN_VAL        -180
#define HEIGHT_MAX_VAL      10000
#define HEIGHT_MIN_VAL      0
#define HEIGHT_MIN_VAL_EN_DIS_POS_HOLD      -1500


#define INDEX_CONF_SECTION  1
#define INDEX_CONF_PARAM_ID 2
#define INDEX_VALUE         3
#define INDEX_MODE          4
#define INDEX_SCALING       7

#define INDEX_START_NOTCH_FREQ 2
#define INDEX_STOP_NOTCH_FREQ  5

#define GPS 0
#define GLO 1


#define LEN_NVM_ITEM_INV      4
#define LEN_SW_CONFIG_SET_PAR 8
#define LEN_NOTCH_EN          6

#define PULSE_DURATION_MIN      100
#define PULSE_DURATION_MAX      900
#define LEN_PPS_IF_DATA_CMD     0x07
#define LEN_PPS_TIMING_DATA_CMD 0x06

#define LEN_SQI_DATA_SET        (9*4)
#define OFFSET_MAX_SQI_SET_DATA  0xFFE0 //nmea derived

#define TEST_TYPE_01            1
#define TEST_TYPE_02            2
#define TEST_TYPE_03            3
#define SAT_ID_TEST_03          16

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

/*=====================================*/
/*Struct definition - used in Read commands*/

/*============ END STRUCT READ =======================*/


/******************************************************/
/*============DEFINE OUTPUT PROCESS===================*/
/******************************************************/

//MSG ID output command competitor
#define STBIN_OUTPUT_POS_ECEF       0x01U
#define STBIN_OUTPUT_POS_LLH        0x02U
#define STBIN_OUTPUT_STATUS         0x03U
#define STBIN_OUTPUT_DOP            0x04U
#define STBIN_OUTPUT_VELECEF        0x11U
#define STBIN_OUTPUT_VELNEU         0x12U
#define STBIN_OUTPUT_TIMEGNSS       0x20U
#define STBIN_OUTPUT_TIMEUTC        0x21U
#define STBIN_OUTPUT_SVINFO         0x30U
#define STBIN_OUTPUT_DGPS           0x31U
#define STBIN_OUTPUT_DGPS_DATA      0x32U
//=========================================
//MSG_ID output commands -  STn NMEA derived
#define STBIN_OUTPUT_TS             0x80U
#define STBIN_OUTPUT_TG             0x81U
#define STBIN_OUTPUT_PA             0x85U
#define STBIN_OUTPUT_RF             0x86U
#define STBIN_OUTPUT_COV            0x87U
#define STBIN_OUTPUT_GST            0x88U
#define STBIN_OUTPUT_PPS_DATA       0x89U
#define STBIN_OUTPUT_HOLD_DATA      0x90U
#define STBIN_OUTPUT_TRAIM_DATA     0x91U
#define STBIN_OUTPUT_LOWPOWER_DATA  0x92U
#define STBIN_OUTPUT_CPU_DATA       0x93U
#define STBIN_OUTPUT_TEST_RF        0x94U
#define STBIN_OUTPUT_POSRES         0x95U
#define STBIN_OUTPUT_VELRES         0x96U
#define STBIN_OUTPUT_NOTCH_F_STATUS 0x97U
#define STBIN_OUTPUT_READ_ERRORS    0x98U

static gnss_events_synch_handler_t *stbin_outmsg_synchdlr_ptr;

/*=====================================*/
/*MSG_ID of INIT_GNSS_CLASS_ID  0x20   */
/*=====================================*/
typedef enum
{
	EXEC_INIT_GNSS_GPS       = 0x01,
	EXEC_INIT_GNSS_FREQ      = 0x02,
	EXEC_INIT_GNSS_COLD      = 0x03,
	EXEC_INIT_GNSS_WARM      = 0x04,
	EXEC_INIT_GNSS_HOT       = 0x05,
	EXEC_INIT_GNSS_TIME      = 0x06,
	EXEC_INIT_GNSS_CLR_EPH   = 0x07,
	EXEC_INIT_GNSS_CLR_ALM   = 0x08
}Exec_GNSS_init_ID;

/*lint -e(9023,9024) Multiple use of '#/##' operators [MISRA 2012 Rule 20.10, advisory]*/
#define READ_WRITE_MSG_ID(dir)\
	STBIN_##dir##_EPH                      = 0xFE,/*STBIN_READ_EPH STBIN_WRITE_EPH*/\
	STBIN_##dir##_ALM                      = 0xFD,/*STBIN_READ_ALM STBIN_WRITE_ALM*/\
	STBIN_##dir##_SW_CONF_PAR              = 0xFC,/*STBIN_READ_SW_CONF_PAR STBIN_WRITE_SW_CONF_PAR*/\
	STBIN_##dir##_SW_CONF_PAR_CHAR         = 0xFB,/*STBIN_READ_SW_CONF_PAR_CHAR STBIN_WRITE_SW_CONF_PAR_CHAR*/\
	STBIN_##dir##_SW_CONF_PAR_INT          = 0xFA,/*STBIN_READ_SW_CONF_PAR_INT STBIN_WRITE_SW_CONF_PAR_INT*/\
	STBIN_##dir##_SW_CONF_PAR_UINT         = 0xF9,/*STBIN_READ_SW_CONF_PAR_UINT STBIN_WRITE_SW_CONF_PAR_UINT*/\
	STBIN_##dir##_SW_CONF_PAR_DOUBLE       = 0xF8,/*STBIN_READ_SW_CONF_PAR_DOUBLE STBIN_WRITE_SW_CONF_PAR_DOUBLE*/\
	STBIN_##dir##_SW_CONF_PAR_DOP          = 0xF7,/*STBIN_READ_SW_CONF_PAR_DOP STBIN_WRITE_SW_CONF_PAR_DOP*/ \
  STBIN_##dir##_SW_CONF_PAR_STRING       = 0xF6,/*STBIN_READ_SW_CONF_PAR_STRING STBIN_WRITE_SW_CONF_PAR_STRING*/ \
	STBIN_##dir##_ALGO                     = 0xF5,/*STBIN_READ_ALGO STBIN_WRITE_ALGO*/ \
	STBIN_##dir##_DATUM                    = 0xF4,/*STBIN_READ_DATUM STBIN_WRITE_DATUM*/ \
	STBIN_##dir##_SW_CONF_ALL_BLOCKS       = 0xF3, /*STBIN_READ_SW_CONF_ALL_BLOCKS STBIN_WRITE_SW_CONF_ALL_BLOCKS*/ \
	STBIN_##dir##_DIFF_SOURCE              = 0xF2 /*STBIN_READ_DIFF_SOURCE STBIN_WRITE_DIFF_SOURCE*/


typedef enum
{
	STBIN_WRITE_SET_GPS_POS         = 0x01,
	STBIN_WRITE_SET_RANGE           = 0x02,
	STBIN_WRITE_ADC_START           = 0x03,
	STBIN_WRITE_SET_FIX_RATE        = 0x05,
	STBIN_WRITE_SET_CONSTEL_MASK    = 0x06,
	STBIN_WRITE_USER_DATUM          = 0x07,
	STBIN_WRITE_DEBUG_ON_OFF        = 0x0B,
	STBIN_WRITE_TIME_INV            = 0x0C,
	STBIN_WRITE_NVM_SWAP            = 0x0F,
	STBIN_WRITE_NVM_ITEM_INV        = 0x10,
	STBIN_WRITE_GPS_FW_UPDATE       = 0x11,
	STBIN_WRITE_FIX2D_ON_OFF        = 0x12,
	STBIN_WRITE_STOP_DET_ON_OFF     = 0x13,
	STBIN_WALKING_MODE_ON_OFF       = 0x14,
	STBIN_SW_CONFIG_SAVE_PARAM      = 0x16,
	STBIN_SW_CONFIG_RESTORE_PARAM   = 0x17,
	STBIN_RTC_WRITE                 = 0x18,
	STBIN_FE_WRITE                  = 0x19,
	STBIN_SF_RECOVERY               = 0x1A,
	STBIN_WRITE_NOTCH_ENABLE        = 0x1B,
	STBIN_LOAD_EPH                 = 0x1C,
	STBIN_LOAD_ALM                  = 0x1D,
	STBIN_WRITE_EN_DIS_POS_HOLD     = 0x1E,
	STBIN_WRITE_EPH_ON_OFF          = 0x1F,
	STBIN_WRITE_LOWPOWER_ON_OFF     = 0x20,
	STBIN_WRITE_STANDBY_ON_OFF      = 0x21,
  READ_WRITE_MSG_ID(WRITE)
}stbin_write_req;

#define STBIN_NOTCH_FILTER_DISABLED       0x00U
#define STBIN_NOTCH_FILTER_ENABLED        0x01U
#define STBIN_NOTCH_FILTER_ENABLED_AUTO   0x02U
#define STBIN_NOTCH_FILTER_PATH_GLONASS   0x01U
#define STBIN_NOTCH_FILTER_PATH_GPS       0x00U

typedef enum
{
	STBIN_WRITE_PPS_IF_ON_OFF_CMD	                = 0x24,
	STBIN_WRITE_PPS_IF_OUT_MODE_CMD               = 0x25,
	STBIN_WRITE_PPS_IF_REF_CONST_CMD              = 0x26,
	STBIN_WRITE_PPS_IF_REF_TIME_CMD               = 0x27,
	STBIN_WRITE_PPS_IF_PULSE_DELAY_CMD            = 0x28,
	STBIN_WRITE_PPS_IF_DURATION_CMD               = 0x29,
	STBIN_WRITE_PPS_IF_PULSE_POLARITY_CMD         = 0x2A,
	STBIN_WRITE_PPS_IF_FIX_CONDITION_CMD          = 0x2C,
	STBIN_WRITE_PPS_IF_SAT_THRESHOLD_CMD          = 0x2D,
	STBIN_WRITE_PPS_IF_CONSTELLATION_RF_DELAY_CMD = 0x2E,
	STBIN_WRITE_PPS_IF_ELEVATION_MASK_CMD         = 0x2F,
	STBIN_WRITE_PPS_IF_COSTELLATION_MASK_CMD      = 0x30,
	STBIN_WRITE_PPS_IF_AUTO_HOLD_SAMPLES_CMD      = 0x33,

  // Requests shared with READ
	STBIN_WRITE_PPS_IF_DATA_CMD                   = 0x4A,
	STBIN_WRITE_PPS_IF_TIMING_DATA_CMD            = 0x4B,
	STBIN_WRITE_PPS_IF_POSITION_HOLD_DATA_CMD     = 0x4C,
	STBIN_WRITE_PPS_IF_TRAIM_AUTO                 = 0x4D,

}stbin_write_pps_req;

#ifdef STBIN_SQI_DATASTORAGE
typedef enum
{
	STBIN_WRITE_SQI_DATA_ERASE                 = 0x38,
	STBIN_WRITE_SQI_DATA_SET                   = 0x39,

}stbin_sqi_data_write_req;

typedef enum
{
	STBIN_READ_SQI_DATA_GET                    = 0x15 + 0x39,
}stbin_sqi_data_read_req;
#endif
//progressivi rispetto a STBIN_SQI_DATASTORAGE

typedef enum
{
	STBIN_READ_SW_VERS                = 0x20,
	STBIN_READ_TASK_CHECK             = 0x21,
	STBIN_READ_CPU_USAGE_CHECK        = 0x22,
	STBIN_READ_HEAP_CHECK             = 0x23,
	STBIN_READ_ADC                    = 0x24,
	STBIN_READ_ALL_SW_VER             = 0x25,
	STBIN_READ_ERRORS                 = 0x26,
	STBIN_READ_SW_FE_DUMP             = 0x2E,
  STBIN_READ_RTC_TIME               = 0x30,

  READ_WRITE_MSG_ID(READ)
}stbin_read_req;

typedef enum
{
  // Values shared with Write request
	STBIN_READ_PPS_IF_PULSE_DATA_CMD         = 0x4A,
	STBIN_READ_PPS_IF_TIMING_DATA_CMD        = 0x4B,
	STBIN_READ_PPS_IF_POSITION_HOLD_DATA_CMD = 0x4C,
	STBIN_READ_PPS_IF_TRAIM_CMD              = 0x4D,
}stbin_read_pps_req;

typedef enum
{
	STBIN_TEST_RF_ON                            = 0x16,
	STBIN_TEST_RF_ADD                           = 0x17,
	STBIN_TEST_RF_DEL                           = 0x18,
	STBIN_TEST_RF_OFF                           = 0x19,
	STBIN_TEST_RTC_ON                           = 0x1A,
	STBIN_TEST_TRK_INTERFERE                    = 0x1B,
	STBIN_TEST_RTC_ERROR                        = 0x1C,

}stbin_test_req;

typedef enum
{
	STBIN_RESET_GPS                             = 0x5C,
	STBIN_RESET_SOFT                            = 0x5D,
	STBIN_RESET_STACK_CHECK                     = 0x5E,
        STBIN_RESET_GPS_SUSPEND                     = 0x5F,
	STBIN_RESET_GPS_RESUME                      = 0x60,
}stbin_reset_req;

#ifdef STBIN_SQI_DATASTORAGE
tChar msg_tx[255];
#endif
static tChar rf_test_sat_id;


typedef enum
{
  Latitude               = 0x01,
  Longitude              = 0x04,
  Height                 = 0x07,
  Height_en_dis_pos_hold = 0x09,
}init_gps_values;

#define SVINFO_FLAG_SAT_NAV_USED                 0x01U
#define SVINFO_FLAG_SAT_DIFF_CORRECTION_AVAIL    0x02U
#define SVINFO_FLAG_SAT_ORBIT_INFO_AVAIL         0x04U
#define SVINFO_FLAG_SAT_ORBIT_IS_EPH             0x08U
#define SVINFO_FLAG_SAT_ORBIT_IS_ALM             0x10U
#define SVINFO_FLAG_SAT_HEALTHY                  0x20U
#define SVINFO_FLAG_SAT_ORBIT_STAGPS             0x40U

/*==========================================================================*/
/*NOTE:  Import in stbin.c module*/ //Communication Layer -
/*Data link verifies functions ......                                       */
/*==========================================================================*/
//extern nmea_inout_t NMEA_read_fun;
void stbin_input_processing                     (void);
void stbin_output_processing                    (void);
void stbin_read_binary_msg                      (tUChar *);            //entry point module.

#ifdef STBIN_SQI_DATASTORAGE
static tU8          stbin_sqi_databuf[SQI_BUFFER_SIZE];
static tU32         stbin_sqi_databuf_size = SQI_BUFFER_SIZE;
#endif

#if defined ( STBIN_ADC_SUPPORT )
static boolean_t           stbin_ext_adctest_started = FALSE;
#endif

/*==========================================================================*/
/*NOTE:  Import in stbin.c module*/ //Communication Layer
/*==========================================================================*/
//Decode manager: General parse - Filter general cmd type
static void DecodeMsg_Manager              (tU16, tUChar *, const stbin_req_msg_parms *); //NOTE: Import in stbin.c
static stbin_status_t base_DecodeMsg_Manager(tU16, tUChar *, const stbin_req_msg_parms *);
//Decode init
static stbin_status_t stbin_return_in_nmea_communication (tU16 , tUChar *, const stbin_req_msg_parms *);
static stbin_status_t stbin_decode_itf_control_req(tU16 , tUChar *, const stbin_req_msg_parms *);
static stbin_status_t stbin_control_output_req(tU16, tUChar *, const stbin_req_msg_parms *);

static stbin_status_t stbin_Decode_GNSS_init         (tU16, tUChar*, const stbin_req_msg_parms *);   //NOTE: Import in stbin.c
//Decode Write cmd
static stbin_status_t stbin_Decode_WRITE_req         (tU16, tUChar*, const stbin_req_msg_parms *);
static stbin_status_t stbin_Decode_PPS_WRITE_req     (tU16, tUChar*, const stbin_req_msg_parms *);   //NOTE: Import in stbin.c
#ifdef STBIN_SQI_DATASTORAGE
static stbin_status_t stbin_Decode_SQI_DATA_WRITE_req(tU16, tUChar*, const stbin_req_msg_parms *);   //NOTE: Import in stbin.c
#endif
             /*==================================================*/

//Decode Read cmd
static stbin_status_t stbin_Decode_READ_req          (tU16, tUChar*, const stbin_req_msg_parms *);  //NOTE: Import in stbin.c
static stbin_status_t stbin_Decode_READ_PPS_req      (tU16, tUChar*, const stbin_req_msg_parms *);  //NOTE: Import in stbin.c
#ifdef STBIN_SQI_DATASTORAGE
static stbin_status_t stbin_Decode_SQI_DATA_READ_req (tU16, tUChar*, const stbin_req_msg_parms *);
#endif
static stbin_status_t stbin_decode_output_process_base(tU16, tUChar *, const stbin_req_msg_parms *);
             /*==================================================*/
////Decode TEST cmd
static stbin_status_t stbin_Decode_TEST_req            (tU16, tUChar*, const stbin_req_msg_parms *);

//             /*==================================================*/
//
//Decode RESET cmd
static stbin_status_t stbin_Decode_RESET_req           (tU16, tUChar*, const stbin_req_msg_parms *);
/*==========================================================================*/
/*Decode module stbin_dec.c */
/*==========================================================================*/
//static tDouble stbin_dec_Perform_Two_Compl               (tInt, tInt);
//static tDouble stbin_dec_Get_Val                         (tUChar*, tInt, tInt, tInt);
//static tDouble stbin_dec_Decode_Height                   (tUChar*, tInt, tInt);
//static tDouble stbin_dec_Decode_LatORLong                (tUChar*, tInt, tInt);

// static tDouble stbin_dec_perform_scaling                 (tDouble, tU16 );


tInt    stbin_dec_return_elaborate_notch_freq_forAPI (tUChar, tUChar, tInt);

/*==========================================================================*/
/*Decode module  stbin_exec.c *///Communication Application Layer
/*==========================================================================*/
void                          stbin_exec_init_cold_start              (tU8);//decoding setting init cold and calls the APIs
static void                   execute_fwupgrade                       (void);


static stbin_status_t stbin_exec_init_GPS_params              (tU16, tUChar*, const stbin_req_msg_parms *);
static stbin_status_t stbin_exec_init_GPS_time                (tU16, tUChar*, const stbin_req_msg_parms *);
static stbin_status_t stbin_exec_init_freq                    (tU16, tUChar*, const stbin_req_msg_parms *);
static stbin_status_t stbin_exec_init_cold                    (tU16, tUChar*, const stbin_req_msg_parms *);
static stbin_status_t stbin_exec_init_warm                    (tU16, tUChar*, const stbin_req_msg_parms *);
static stbin_status_t stbin_exec_init_hot                     (tU16, tUChar*, const stbin_req_msg_parms *);
static stbin_status_t stbin_exec_init_clr_ephemes             (tU16, tUChar*, const stbin_req_msg_parms *);
static stbin_status_t stbin_exec_init_clr_almanacs            (tU16, tUChar*, const stbin_req_msg_parms *);
static stbin_status_t stbin_exec_set_gps_pos                  (tU16, tUChar*, const stbin_req_msg_parms *);
static stbin_status_t stbin_exec_set_range                    (tU16, tUChar*, const stbin_req_msg_parms *);
static stbin_status_t stbin_exec_set_algo_on_off              (tU16, tUChar*, const stbin_req_msg_parms *);
static stbin_status_t stbin_exec_set_diff_source              (tU16, tUChar*, const stbin_req_msg_parms *);
static stbin_status_t stbin_exec_set_fix_rate                 (tU16, tUChar*, const stbin_req_msg_parms *);
static stbin_status_t stbin_exec_set_constellation_mask       (tU16, tUChar*, const stbin_req_msg_parms *);
static stbin_status_t stbin_exec_load_ephemes                 (tU16, tUChar*, const stbin_req_msg_parms *);
static stbin_status_t stbin_exec_load_almanac                 (tU16, tUChar*, const stbin_req_msg_parms *);
static stbin_status_t stbin_exec_debug_on_off                 (tU16, tUChar*, const stbin_req_msg_parms *);
static stbin_status_t stbin_exec_time_inv                     (tU16, tUChar*, const stbin_req_msg_parms *);
static stbin_status_t stbin_exec_gps_suspend                  (tU16, tUChar*, const stbin_req_msg_parms *);
static stbin_status_t stbin_exec_gps_resume                   (tU16, tUChar*, const stbin_req_msg_parms *);
static stbin_status_t stbin_exec_nvm_swap                     (tU16, tUChar*, const stbin_req_msg_parms *);
static stbin_status_t stbin_exec_nvm_item_inv                 (tU16, tUChar*, const stbin_req_msg_parms *);
static stbin_status_t stbin_exec_gps_fw_update                (tU16, tUChar*, const stbin_req_msg_parms *);
static stbin_status_t stbin_exec_fix2d_on_off                 (tU16, tUChar*, const stbin_req_msg_parms *);
static stbin_status_t stbin_exec_stop_detection_on_off        (tU16, tUChar*, const stbin_req_msg_parms *);
static stbin_status_t stbin_exec_walking_mode_on_off          (tU16, tUChar*, const stbin_req_msg_parms *);

static stbin_status_t stbin_exec_sw_config_set_param_char     (tU16, tUChar*, const stbin_req_msg_parms *);
static stbin_status_t stbin_exec_sw_config_set_param_int      (tU16, tUChar*, const stbin_req_msg_parms *);
static stbin_status_t stbin_exec_sw_config_set_param_uint     (tU16, tUChar*, const stbin_req_msg_parms *);
static stbin_status_t stbin_exec_sw_config_set_param_double   (tU16, tUChar*, const stbin_req_msg_parms *);
static stbin_status_t stbin_exec_sw_config_set_param_dop      (tU16, tUChar*, const stbin_req_msg_parms *);
static stbin_status_t stbin_exec_sw_config_set_param_string   (tU16, tUChar*, const stbin_req_msg_parms *);
static stbin_status_t stbin_exec_sw_config_save_param         (tU16, tUChar*, const stbin_req_msg_parms *);
static stbin_status_t stbin_exec_sw_config_restore_param      (tU16, tUChar*, const stbin_req_msg_parms *);

static stbin_status_t stbin_exec_rtc_write                    (tU16, tUChar*, const stbin_req_msg_parms *);
static stbin_status_t stbin_exec_fe_write                     (tU16, tUChar*, const stbin_req_msg_parms *);
static stbin_status_t stbin_exec_sf_recovery                  (tU16, tUChar*, const stbin_req_msg_parms *);
static stbin_status_t stbin_exec_notch_enable                 (tU16, tUChar*, const stbin_req_msg_parms *);
static stbin_status_t stbin_exec_save_ephems                  (tU16, tUChar*, const stbin_req_msg_parms *);
static stbin_status_t stbin_exec_save_almanac                 (tU16, tUChar*, const stbin_req_msg_parms *);
static stbin_status_t stbin_exec_enable_disable_position_hold (tU16, tUChar*, const stbin_req_msg_parms *);
static stbin_status_t stbin_exec_real_ephems_on_off           (tU16, tUChar*, const stbin_req_msg_parms *);
#if defined ( STBIN_ADC_SUPPORT )
static stbin_status_t stbin_exec_adc_start                    (tU16, tUChar*, const stbin_req_msg_parms *);
#endif
static stbin_status_t stbin_exec_lowpower_onoff               (tU16, tUChar*, const stbin_req_msg_parms *);

//WRITE
//all cmd present in section 0x3C, are derived from nmea PPS_IF_CMD single command.
static stbin_status_t stbin_exec_pps_if_on_off_cmd                (tU16, tUChar*, const stbin_req_msg_parms *);
static stbin_status_t stbin_exec_pps_if_out_mode_cmd              (tU16, tUChar*, const stbin_req_msg_parms *);
static stbin_status_t stbin_exec_pps_if_ref_constellation_cmd     (tU16, tUChar*, const stbin_req_msg_parms *);
static stbin_status_t stbin_exec_pps_if_ref_time_cmd              (tU16, tUChar*, const stbin_req_msg_parms *);
static stbin_status_t stbin_exec_pps_if_pulse_delay_cmd           (tU16, tUChar*, const stbin_req_msg_parms *);
static stbin_status_t stbin_exec_pps_if_duration_cmd              (tU16, tUChar*, const stbin_req_msg_parms *);
static stbin_status_t stbin_exec_pps_if_pulse_polarity_cmd        (tU16, tUChar*, const stbin_req_msg_parms *);
static stbin_status_t stbin_exec_pps_if_data_cmd                  (tU16, tUChar*, const stbin_req_msg_parms *);
static stbin_status_t stbin_exec_pps_if_fix_condition_cmd         (tU16, tUChar*, const stbin_req_msg_parms *);
static stbin_status_t stbin_exec_pps_if_sat_threshold_cmd         (tU16, tUChar*, const stbin_req_msg_parms *);
static stbin_status_t stbin_exec_pps_if_constallation_rf_delay_cmd(tU16, tUChar*, const stbin_req_msg_parms *);
static stbin_status_t stbin_exec_pps_if_elevation_mask_cmd        (tU16, tUChar*, const stbin_req_msg_parms *);
static stbin_status_t stbin_exec_pps_if_constellation_mask_cmd    (tU16, tUChar*, const stbin_req_msg_parms *);
static stbin_status_t stbin_exec_pps_if_timing_data_cmd           (tU16, tUChar*, const stbin_req_msg_parms *);
static stbin_status_t stbin_exec_pps_if_hold_data_cmd             (tU16, tUChar*, const stbin_req_msg_parms *);
static stbin_status_t stbin_exec_pps_if_auto_hold_samples_cmd     (tU16, tUChar*, const stbin_req_msg_parms *);
static stbin_status_t stbin_exec_pps_if_traim_cmd                 (tU16, tUChar*, const stbin_req_msg_parms *);

//WRITE
static stbin_status_t stbin_exec_write_sw_config_all_blocks     (tU16, tUChar*, const stbin_req_msg_parms *);
#ifdef STBIN_SQI_DATASTORAGE
static stbin_status_t stbin_exec_sqi_data_erase                   (tU16, tUChar*, const stbin_req_msg_parms *);
static stbin_status_t stbin_exec_sqi_data_set                     (tU16, tUChar*, const stbin_req_msg_parms *);
#endif
//READ 0x2A  ///*ID STBIN READ SERVICE */

static stbin_status_t stbin_exec_dump_ephems    (tU16, tUChar*, const stbin_req_msg_parms *);
static void                   Send_Ephemeris            (tInt, tInt*, tInt*, const stbin_req_msg_parms *);
static stbin_status_t stbin_exec_dump_almanacs  (tU16, tUChar*, const stbin_req_msg_parms *);
static void                   Send_Almanacs             (tInt, tInt*, tInt*, const stbin_req_msg_parms *);

static stbin_status_t                   stbin_exec_get_rtc_time                   (tU16, tUChar*, const stbin_req_msg_parms *);
static stbin_status_t                   stbin_exec_get_sw_ver                     (tU16, tUChar*, const stbin_req_msg_parms *);
static stbin_status_t                   stbin_exec_get_all_sw_ver                 (tU16, tUChar*, const stbin_req_msg_parms *);
static stbin_status_t                   stbin_exec_get_algo_status                (tU16, tUChar*, const stbin_req_msg_parms *);
static stbin_status_t                   stbin_exec_check_task                     (tU16, tUChar*, const stbin_req_msg_parms *);
static stbin_status_t                   stbin_exec_check_cpu_usage                (tU16, tUChar*, const stbin_req_msg_parms *);
static stbin_status_t                   stbin_exec_check_heap                     (tU16, tUChar*, const stbin_req_msg_parms *);
static stbin_status_t                   stbin_exec_sw_config_get_par              (tU16, tUChar*, const stbin_req_msg_parms *);
static stbin_status_t stbin_exec_sw_config_get_single_par       (tUChar, tUChar, tUChar, const stbin_req_msg_parms *);
static stbin_status_t stbin_exec_sw_config_get_all_par          (tUChar, tUChar, tUChar, const stbin_req_msg_parms *);
static stbin_status_t                   stbin_exec_read_datum_selection           (tU16, tUChar*, const stbin_req_msg_parms *);
static stbin_status_t                   stbin_exec_dump_fe                        (tU16, tUChar*, const stbin_req_msg_parms *);
static stbin_status_t stbin_exec_write_datum_selection          (tU16, tUChar*, const stbin_req_msg_parms *);
static stbin_status_t stbin_exec_define_user_datum              (tU16, tUChar*, const stbin_req_msg_parms *);
static stbin_status_t stbin_exec_read_sw_config_all_blocks      (tU16, tUChar*, const stbin_req_msg_parms *);
static stbin_status_t stbin_exec_get_diff_source                (tU16, tUChar*, const stbin_req_msg_parms *);
#if defined ( STBIN_ADC_SUPPORT )
static stbin_status_t stbin_exec_adc_read                       (tU16, tUChar*, const stbin_req_msg_parms *);
#endif

//READ 0x2B  ///*ID STBIN READ SQI SERVICE */
#ifdef STBIN_SQI_DATASTORAGE
static stbin_status_t                   stbin_exec_sqi_data_get                   (tU16, tUChar*, const stbin_req_msg_parms *);
#endif
//READ 0x2D  ///*ID STBIN READ PPS SERVICE */
static stbin_status_t stbin_exec_pps_if_pulse_data_read         (tU16, tUChar*, const stbin_req_msg_parms *);
static stbin_status_t stbin_exec_pps_if_timing_data_read        (tU16, tUChar*, const stbin_req_msg_parms *);
static stbin_status_t stbin_exec_pps_if_pos_hold_data_read      (tU16, tUChar*, const stbin_req_msg_parms *);
static stbin_status_t stbin_exec_pps_if_traim_read              (tU16, tUChar*, const stbin_req_msg_parms *);
//TEST 0x4A
static stbin_status_t stbin_exec_test_rf_on                     (tU16, tUChar*, const stbin_req_msg_parms *);
static stbin_status_t        execute_rf_test_on                 (tChar, tU16, tChar);
static stbin_status_t stbin_exec_test_add                       (tU16, tUChar*, const stbin_req_msg_parms *);
static stbin_status_t stbin_exec_test_rf(boolean_t, tChar, tU16, tChar);
static stbin_status_t stbin_exec_test_del                       (tU16, tUChar*, const stbin_req_msg_parms *);
static stbin_status_t stbin_exec_test_off                       (tU16, tUChar*, const stbin_req_msg_parms *);
#ifdef RTC_TESTING
static stbin_status_t stbin_exec_test_rtc_on_off                (tU16, tUChar*, const stbin_req_msg_parms *);
#endif
static stbin_status_t stbin_exec_test_trk_interfere              (tU16, tUChar*, const stbin_req_msg_parms *);
static stbin_status_t stbin_exec_test_rtc_error                  (tU16, tUChar*, const stbin_req_msg_parms *);
//TEST 0x4A
//RESET GPS 0x5A
static stbin_status_t stbin_exec_reset_gps                       (tU16, tUChar*, const stbin_req_msg_parms *);
static stbin_status_t stbin_exec_reset_soft                      (tU16, tUChar*, const stbin_req_msg_parms *);
static stbin_status_t stbin_exec_reset_stack_check               (tU16, tUChar*, const stbin_req_msg_parms *);
static void                    execute_stack_usage_reset                 (void);

static stbin_status_t stbin_exec_binary_output_ON_OFF             (tU8);
static stbin_status_t stbin_exec_switch_to_NMEA                   (void);

/*==================================================================================================*/
/* OUTPUT PROCESS osi function*/
/*==================================================================================================*/

// OUTPUT PROCESS Commands
static void stbin_output_exec_pos_llh        (const stbin_output_msg_parms *parms);
static void stbin_output_exec_pos_ecef       (const stbin_output_msg_parms *parms);
static void stbin_output_exec_status         (const stbin_output_msg_parms *parms);
static void stbin_output_exec_dop            (const stbin_output_msg_parms *parms);
static void stbin_output_exec_velecef        (const stbin_output_msg_parms *parms);
static void stbin_output_exec_velneu         (const stbin_output_msg_parms *parms);
static void stbin_output_exec_timegnss       (const stbin_output_msg_parms *parms);
static void stbin_output_exec_timeutc        (const stbin_output_msg_parms *parms);
static void stbin_output_exec_svinfo         (const stbin_output_msg_parms *parms);
static void stbin_output_exec_dgps           (const stbin_output_msg_parms *parms);
static void stbin_output_exec_dgps_data      (const stbin_output_msg_parms *parms);
static void stbin_output_exec_ts             (const stbin_output_msg_parms *parms);
static void stbin_output_exec_tg             (const stbin_output_msg_parms *parms);
static void stbin_output_exec_pos_algo       (const stbin_output_msg_parms *parms);
static void stbin_output_exec_RF             (const stbin_output_msg_parms *parms);
static void stbin_output_exec_cov            (const stbin_output_msg_parms *parms);
static void stbin_output_exec_gst            (const stbin_output_msg_parms *parms);
static void stbin_output_exec_pps_data       (const stbin_output_msg_parms *parms);
static void stbin_output_exec_hold_data      (const stbin_output_msg_parms *parms);
static void stbin_output_exec_traim_data     (const stbin_output_msg_parms *parms);
static void stbin_output_exec_lowpower_data  (const stbin_output_msg_parms *parms);
static void stbin_output_exec_cpu_data       (const stbin_output_msg_parms *parms);
static void stbin_output_test_rf             (const stbin_output_msg_parms *parms);
static void stbin_output_posRes_data         (const stbin_output_msg_parms *parms);
static void stbin_output_velRes_data         (const stbin_output_msg_parms *parms);
static void stbin_output_notch_filter_status (const stbin_output_msg_parms *parms);
static void stbin_output_read_errors         (const stbin_output_msg_parms *parms);

//changes necessary for porting stbin in sdk gpsstdpkg
static void         send_msg_to_uart_p                                       (const tUChar *, const tInt); //

stbin_inout_t         stbin_ioport_read;
stbin_inout_t         stbin_ioport_write;
static gpOS_semaphore_t *    stbin_outmsg_access;
static boolean_t             stbin_out_processing_enabled = FALSE;
static boolean_t             stbin_out_msg_on_off = TRUE;
static tU32                  stbin_msg_list[2] = {0,0};

static const stbin_output_msg_def stbin_outmsg_base_list[] = {
// BANK 0
  { stbin_output_exec_pos_ecef      , STBIN_MASK_OUTPUT_POS_ECEF      , STBIN_MASK_BANK_0, STBIN_OUTPUT_POS_ECEF       },
  { stbin_output_exec_pos_llh       , STBIN_MASK_OUTPUT_POS_LLH       , STBIN_MASK_BANK_0, STBIN_OUTPUT_POS_LLH        },
  { stbin_output_exec_status        , STBIN_MASK_OUTPUT_STATUS        , STBIN_MASK_BANK_0, STBIN_OUTPUT_STATUS         },
  { stbin_output_exec_dop           , STBIN_MASK_OUTPUT_DOP           , STBIN_MASK_BANK_0, STBIN_OUTPUT_DOP            },
  { stbin_output_exec_velecef       , STBIN_MASK_OUTPUT_VELECEF       , STBIN_MASK_BANK_0, STBIN_OUTPUT_VELECEF        },
  { stbin_output_exec_velneu        , STBIN_MASK_OUTPUT_VELNEU        , STBIN_MASK_BANK_0, STBIN_OUTPUT_VELNEU         },
  { stbin_output_exec_timegnss      , STBIN_MASK_OUTPUT_TIMEGNSS      , STBIN_MASK_BANK_0, STBIN_OUTPUT_TIMEGNSS       },
  { stbin_output_exec_timeutc       , STBIN_MASK_OUTPUT_TIMEUTC       , STBIN_MASK_BANK_0, STBIN_OUTPUT_TIMEUTC        },
  { stbin_output_exec_svinfo        , STBIN_MASK_OUTPUT_SVINFO        , STBIN_MASK_BANK_0, STBIN_OUTPUT_SVINFO         },
  { stbin_output_exec_dgps          , STBIN_MASK_OUTPUT_DGPS          , STBIN_MASK_BANK_0, STBIN_OUTPUT_DGPS           },
  { stbin_output_exec_dgps_data     , STBIN_MASK_OUTPUT_DGPS_DATA     , STBIN_MASK_BANK_0, STBIN_OUTPUT_DGPS_DATA      },
  { stbin_output_posRes_data        , STBIN_MASK_OUTPUT_POSRES        , STBIN_MASK_BANK_0, STBIN_OUTPUT_POSRES         },
  { stbin_output_velRes_data        , STBIN_MASK_OUTPUT_VELRES        , STBIN_MASK_BANK_0, STBIN_OUTPUT_VELRES         },
  { stbin_output_exec_ts            , STBIN_MASK_OUTPUT_TS            , STBIN_MASK_BANK_0, STBIN_OUTPUT_TS             },
  { stbin_output_exec_tg            , STBIN_MASK_OUTPUT_TG            , STBIN_MASK_BANK_0, STBIN_OUTPUT_TG             },
  { stbin_output_exec_pos_algo      , STBIN_MASK_OUTPUT_PA            , STBIN_MASK_BANK_0, STBIN_OUTPUT_PA             },
  { stbin_output_exec_RF            , STBIN_MASK_OUTPUT_RF            , STBIN_MASK_BANK_0, STBIN_OUTPUT_RF             },
  { stbin_output_exec_cov           , STBIN_MASK_OUTPUT_COV           , STBIN_MASK_BANK_0, STBIN_OUTPUT_COV            },
  { stbin_output_exec_gst           , STBIN_MASK_OUTPUT_GST           , STBIN_MASK_BANK_0, STBIN_OUTPUT_GST            },
  { stbin_output_exec_pps_data      , STBIN_MASK_OUTPUT_PPS_DATA      , STBIN_MASK_BANK_0, STBIN_OUTPUT_PPS_DATA       },
  { stbin_output_exec_hold_data     , STBIN_MASK_OUTPUT_HOLD_DATA     , STBIN_MASK_BANK_0, STBIN_OUTPUT_HOLD_DATA      },
  { stbin_output_exec_traim_data    , STBIN_MASK_OUTPUT_TRAIM_DATA    , STBIN_MASK_BANK_0, STBIN_OUTPUT_TRAIM_DATA     },
  { stbin_output_exec_lowpower_data , STBIN_MASK_OUTPUT_LOWPOWER_DATA , STBIN_MASK_BANK_0, STBIN_OUTPUT_LOWPOWER_DATA  },
#if !defined(__linux__) && !defined(_WIN32_WCE)
  { stbin_output_exec_cpu_data      , STBIN_MASK_OUTPUT_CPU_DATA      , STBIN_MASK_BANK_0, STBIN_OUTPUT_CPU_DATA       },
#endif
  { stbin_output_notch_filter_status, STBIN_MASK_OUTPUT_NOTCH_F_STATUS, STBIN_MASK_BANK_0, STBIN_OUTPUT_NOTCH_F_STATUS },
  { stbin_output_read_errors        , STBIN_MASK_OUTPUT_READ_ERRORS   , STBIN_MASK_BANK_0, STBIN_OUTPUT_READ_ERRORS    },

// BANK 1
  { stbin_output_test_rf            , STBIN_MASK_OUTPUT_TEST_RF       , STBIN_MASK_BANK_1, STBIN_OUTPUT_TEST_RF  },
};

#define STBIN_NB_OUTPUT_MSG_IN_LIST     (sizeof(stbin_outmsg_base_list)/sizeof(stbin_outmsg_base_list[0]))

/*=============================================================*/
/*global static variables - status machine frame RX            */
/*=============================================================*/
static boolean_t   msg_sync_flag = FALSE;
static msg_state_t msg_state = START_SEQUENCE_DETECTION;

frame_qualifier_t frame_ack_qualifier(tUChar cid, tUChar mid, tUInt msg_len, frame_status_t frame_status_value)
{
  frame_qualifier_t q;
  ack_nack_status_t ack_nack_value = ACK;

#if ( defined(__linux__) && (__BYTE_ORDER == __BIG_ENDIAN) ) || ( (! defined(__linux__)) && defined(__BIG_ENDIAN) )
#  error This code must be updated for BigEndian
#endif
  // set len in header
  q = msg_len & HEADER_LEN_MASK; /* Reset status bits */
  // Set status bits
  q |= (((tUInt)frame_status_value | (tUInt)ack_nack_value) << 8U) & HEADER_STATUS_MASK; /* make sure to just touch status bits */
  q <<= 16;
  q |= ((tUInt)mid << 8)|cid;

  return q;
}

static frame_qualifier_t frame_nack_qualifier(tUChar cid, tUChar mid)
{
  frame_qualifier_t q;
  ack_nack_status_t ack_nack_value = NACK;
  frame_status_t frame_status_value = ONLY_ONE_FRAME;

  // set len=0 in header
  // Set status bits
  q = ((((tUInt)frame_status_value | (tUInt)ack_nack_value) << 8U) & HEADER_STATUS_MASK) << 16U; /* make sure to just touch status bits */
  q |= ((tUInt)mid << 8)|cid;

  return q;
}

/*==============================================================*/
/*+-------------------------------------------------------------------------+*/
/*|                                                                         |*/
/*|  .-----.__________________.------.                   _.--._             |*/
/*|  |=======================' |||||| )      .----------'------`--------.   |*/
/*|  `----------------._____.--------'       ============================   |*/
/*|                 _.-|   |---.__             /=====/  `------'            |*/
/*|           __.--'---|___|------`-------------------.                     |*/
/*|          '---------------._        ___.-------._ /                      |*/
/*|                            `-.----'-------------'                       |*/
/*|                                \____.-----'                             |*/
/*|
 * =========================================================================|*/
                 /*Entry point module - datalink layer*/
/*|-------------------------------------------------------------------------+*/

gnss_error_t stbin_init_p( gpOS_partition_t *part, stbin_inout_t read_func, stbin_inout_t write_func, tU32 *msg_list)
{
  stbin_outmsg_access = gpOS_semaphore_create_p( SEM_FIFO, part, 1);
  if(stbin_outmsg_access == NULL)
  {
    return GNSS_ERROR;  /*lint !e904 Return statement before end of function */
  }
  if((read_func == NULL) || (write_func == NULL))
  {
    return GNSS_ERROR;  /*lint !e904 Return statement before end of function */
  }

  stbin_outmsg_synchdlr_ptr = gnss_events_synch_handler_create();

  if( stbin_outmsg_synchdlr_ptr == GNSS_EVENTS_SYNCHANDLER_NONE)
  {
    return(GNSS_ERROR);  /*lint !e904 Return statement before end of function */
  }

  stbin_ioport_read = read_func;
  stbin_ioport_write = write_func;
  stbin_msg_list[0] = msg_list[0];
  stbin_msg_list[1] = msg_list[1];

  GPS_DEBUG_MSG(("[gnssapp] stbin init start\r\n"));

#if defined(HDBIN_LINKED)
  nmea_set_external_cmdif_callback((nmea_external_cmdif_callback_t)hdbin_input_processing);
  //TODO:
  //nmea_set_external_outmsg_callback((nmea_external_outmsg_callback_t)hdbin_output_processing);
#else
  nmea_set_external_cmdif_callback((nmea_external_cmdif_callback_t)stbin_input_processing);
  nmea_set_external_outmsg_callback((nmea_external_outmsg_callback_t)stbin_output_processing);
#endif

  return(GNSS_NO_ERROR);
}

void stbin_input_processing(void)
{
  stbin_buffer_io_type msg;

  stbin_read_binary_msg(msg.buffer);
}

static stbin_status_t cs_compare(stbin_chkSum_t *cs_a, uint8 cs_0_b, uint8 cs_1_b)
{
  stbin_status_t result;

  if((cs_a->cs_0 == cs_0_b) && (cs_a->cs_1 == cs_1_b)) {
		result= STBIN_OK;
  } else {
		result= STBIN_FAILED;
  }

	return result;
}

static void cs_add_data(tUChar *buf, tU16 len, stbin_chkSum_t *cs)
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

static void cs_header(uint8 class_id, uint8 msg_id, tU16 msg_len, stbin_chkSum_t *cs)
{
  tUChar sync_part[] = {SYNC_BYTE_1, SYNC_BYTE_2};
  cs->cs_0 = 0;
  cs->cs_1 = 0;

  cs_add_data(sync_part, 2, cs);
  cs_add_data(&class_id, 1, cs);
  cs_add_data(&msg_id, 1, cs);
  cs_add_data((tUChar *)&msg_len, 2, cs);
}

static tInt stbin_message_update_cs(tUChar *msg, tInt cs_offset)
{
  msg[cs_offset] = 0;
  msg[cs_offset+1] = 0;
  cs_add_data(msg, (tU16)cs_offset, (stbin_chkSum_t *) &msg[cs_offset]);
  return cs_offset + (tInt)sizeof(stbin_chkSum_t);
}

// if frame does is not complete in this time window, drop it
#define STBIN_FRAME_TIMEOUT_TICKS (10.0*NAV_CPU_TICKS_PER_SECOND)

void stbin_read_binary_msg(tUChar *msg)
{
  tUChar ch;
  stbin_chkSum_t cur_cs;
  tU32 io_rc;
  gpOS_clock_t frame_time_limit = 0;
  stbin_req_msg_parms parms;
  stbin_buffer_io_type MsgToSendResponse;
  tUChar  Len_field[NUM_BYTE_LEN];
  tU16      msg_length_ = 0,len_temp_, Bytes5_6_ = 0;

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
            msg_state =  START_SEQUENCE_DETECTION_sync02;
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
        case START_SEQUENCE_DETECTION_sync02:
          if(stbin_ioport_read((tChar *)&ch, ONE_BYTE, &frame_time_limit) == ONE_BYTE)
          {
            if((ch == SYNC_BYTE_2) && (msg_sync_flag == TRUE))
            {
              msg_state =  MESSAGE_CLASS_ID_DETECTION;
              parms.class_Id = VAL_NULL;
              parms.msg_Id   = VAL_NULL;
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
        case  MESSAGE_CLASS_ID_DETECTION:
          if(stbin_ioport_read((tChar *)&ch, ONE_BYTE, &frame_time_limit) == ONE_BYTE)
          {
        		parms.class_Id = ch;
        		msg_state = MESSAGE_MSG_ID_DETECTION;
          }
          else
          {
            msg_state = ERROR_MESSAGE_CORRUPTED;
          }
        break;
        case  MESSAGE_MSG_ID_DETECTION:
          if(stbin_ioport_read((tChar *)&ch, ONE_BYTE, &frame_time_limit) == ONE_BYTE)
          {
            parms.msg_Id   = ch;
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
            msg_length_ = Bytes5_6_ & 0x03FFU;
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
              GPS_DEBUG_MSG(("STBIN READ checksum\r\n"));
              cs_header(parms.class_Id, parms.msg_Id, Bytes5_6_, &cur_cs);
              cs_add_data(msg, msg_length_, &cur_cs);
              if(cs_compare(&cur_cs, msg[len_temp_-NUM_BYTE_CHK], msg[len_temp_-VAL_ONE]) == STBIN_OK)
              {
                GPS_DEBUG_MSG(("STBIN Good checksum buf@=0x%X rb=0x%X\n\r", (tU32)(parms.out_buf),
                                (tU32)MsgToSendResponse.buffer));
                /*CK ok!!! msg_lenght is only payload len - */
                DecodeMsg_Manager(msg_length_, msg, &parms );/*Decode message Terminate ok.*/
                msg_sync_flag = FALSE;
                msg_state = START_SEQUENCE_DETECTION;//restore START_SEQUENCE_DETECTION conditions
              }
              else
              {
                GPS_DEBUG_MSG(("\r\nSTBIN Wrong checksum\r\n"));
                /*CK Not ok --> Sending NACK*/
                /*restore START_SEQUENCE_DETECTION conditions Decode message Terminate error */
                msg_sync_flag = FALSE;
                msg_state = START_SEQUENCE_DETECTION;
                Send_ACKorNACK(NACK, &parms);
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
        	msg_sync_flag         = FALSE;
        	msg_state             = START_SEQUENCE_DETECTION;
          parms.class_Id        = STBIN_GENERAL_ERROR_CLASS_ID;
          parms.msg_Id = ERROR_GENERIC;
        	Send_ACKorNACK(NACK, &parms);
        break;
        default:
        /* Should never go there */
        break;
     }

    }while(msg_state != START_SEQUENCE_DETECTION);
}

//changes necessary for porting stbin in sdk gpsstdpkg
//Added new function. In the old stbin, this feature was handled
//by a callback function (with the same name)
static void send_msg_to_uart_p(const tUChar *msg, const tInt length)
{
  gpOS_semaphore_wait( stbin_outmsg_access);

  stbin_ioport_write( (tChar *)msg, length, gpOS_TIMEOUT_INFINITY);

  gpOS_semaphore_signal( stbin_outmsg_access);
}

/*===========================================================================*/
/*                         Plugins Management                                */
/*===========================================================================*/
typedef struct stbin_plugin {
  stbin_status_t (* decoder)(tU16 msg_length, tUChar *msg, const stbin_req_msg_parms *parms);
  struct stbin_plugin *next;
} stbin_plugin_t;

stbin_plugin_t *plugins = NULL;

/*===========================================================================*/
/*Manager of the binary response defined in the msg_function matrics         */
/*===========================================================================*/
static void DecodeMsg_Manager(tU16 msg_length, tUChar *msg, const stbin_req_msg_parms *parms)
{
  stbin_status_t rc;
  //GPS_DEBUG_MSG(("STBIN DEAL WITH CID=0x%X, MID=0x%X\n\r", cls_id, msg_id));

  // Check locally
  rc = base_DecodeMsg_Manager(msg_length, msg, parms);

  if(STBIN_NOTFOUND == rc)
  {
    // Check in plugins
    rc = gnssapp_plugins_stbin_cmdif_parse(msg_length, msg, parms);
  }

  if((STBIN_FAILED == rc) || (STBIN_NOTFOUND == rc))
  {
    // Return NACK if no success
    Send_ACKorNACK(NACK, parms);
  }
}

static stbin_status_t base_DecodeMsg_Manager(tU16 msg_length, tUChar *msg, const stbin_req_msg_parms *parms)
{
  stbin_status_t rc;

  switch(parms->class_Id)
  {
  case STBIN_ITF_CONTROL_CLASS_ID:
    rc = stbin_decode_itf_control_req(msg_length, msg, parms);
    break;

  case INIT_GNSS_CLASS_ID:
    rc = stbin_Decode_GNSS_init(msg_length, msg, parms);
    break;

  case STBIN_WRITE_CLASS_ID:
	  rc = stbin_Decode_WRITE_req(msg_length, msg, parms);
    break;

  case STBIN_PPS_WR_CLASS_ID:
    rc = stbin_Decode_PPS_WRITE_req(msg_length, msg, parms);
    break;

#ifdef STBIN_SQI_DATASTORAGE
  case STBIN_SQI_WR_CLASS_ID:
	  rc = stbin_Decode_SQI_DATA_WRITE_req(msg_length, msg, parms);
    break;
#endif
/*================== READ CMD =============================*/
  case STBIN_READ_CLASS_ID:
    rc = stbin_Decode_READ_req(msg_length, msg, parms);
    break;

  case STBIN_PPS_RD_CLASS_ID:
	  rc = stbin_Decode_READ_PPS_req(msg_length, msg, parms);
    break;

#ifdef STBIN_SQI_DATASTORAGE
  case STBIN_SQI_RD_CLASS_ID :
	  rc = stbin_Decode_SQI_DATA_READ_req(msg_length, msg, parms);
    break;
#endif
/*================== TEST CMD =============================*/
  case STBIN_TEST_CLASS_ID:
	  rc = stbin_Decode_TEST_req(msg_length, msg, parms);
    break;

/*================== RESET CMD =============================*/
  case STBIN_RESET_CLASS_ID:
	  rc = stbin_Decode_RESET_req(msg_length, msg, parms);
    break;
/*=================OUTPUT POLLED CMD RESPONSE===============*/
  case STBIN_OUTPROCESS_CLASS_ID:
	  rc = stbin_decode_output_process_base(msg_length, msg, parms);
    break;

  default://send nack if received a unknown class_id
	  rc = STBIN_NOTFOUND;
    break;
	}

	return rc;
}

/**/
stbin_status_t stbin_decode_output_process(tU16 msg_length, tUChar *msg,
                                         const stbin_req_msg_parms *parms_in,
                                         const stbin_output_msg_def *list, tInt nb_elem)
{
  tInt i;
	tInt week_n;
	gpOS_clock_t fix_clock;
	tDouble tow, tow_ms;
	stbin_output_msg_parms parms;
  stbin_status_t cmd_status = STBIN_NOTFOUND;

  if(0U != msg_length)
  {
    return STBIN_FAILED;   /*lint !e904 Return statement before end of function */
  }

  for(i=0; i<nb_elem; i++) {
    if(parms_in->msg_Id == list[i].msg_Id) {
      gnss_fix_store_local(NULL);
      gnss_fix_read_claim();
      gnss_fix_get_time_local(&week_n, &tow, &fix_clock,NULL);
      tow_ms = tow * SCALING_KILO;
      parms.currTow_mills = (tUInt)tow_ms;
      parms.currTow_nanos = (tUInt)((tow_ms - (tDouble)parms.currTow_mills) * SCALING_MEGA);
      parms.class_Id = parms_in->class_Id;
      parms.msg_Id = parms_in->msg_Id;
      parms.data_p = NULL;
      parms.out_buf = parms_in->out_buf;

      list[i].gen(&parms);
      cmd_status = STBIN_OK;

      gnss_fix_read_release();

      break;
    }
  }

	return cmd_status;
}

/**/
static stbin_status_t stbin_decode_output_process_base(tU16 msg_length, tUChar *msg, const stbin_req_msg_parms *parms_in)
{
  return stbin_decode_output_process(msg_length, msg, parms_in,
                                  stbin_outmsg_base_list, STBIN_NB_OUTPUT_MSG_IN_LIST);
}

/*===========================================================================*/
/*DecodeREAD_Request : Execute the command and Send the binaryResponse       */
/*===========================================================================*/
static stbin_status_t stbin_Decode_READ_req(tU16 msg_length, tUChar *msg, const stbin_req_msg_parms *parms_in)
{
  stbin_status_t cmd_status = 0;

	switch((stbin_read_req)parms_in->msg_Id)
	{
	case STBIN_READ_EPH:
		cmd_status = stbin_exec_dump_ephems(msg_length, msg, parms_in);
	break;

	case STBIN_READ_ALM:
		cmd_status = stbin_exec_dump_almanacs(msg_length, msg, parms_in);
	break;

	case STBIN_READ_RTC_TIME:
		cmd_status = stbin_exec_get_rtc_time(msg_length, msg, parms_in);
	break;

	case STBIN_READ_SW_VERS:
		cmd_status = stbin_exec_get_sw_ver(msg_length, msg, parms_in);
	break;

	case STBIN_READ_ALGO:
		cmd_status = stbin_exec_get_algo_status(msg_length, msg, parms_in);
	break;

	case STBIN_READ_TASK_CHECK:
		cmd_status = stbin_exec_check_task(msg_length,msg, parms_in);
	break;

	case STBIN_READ_CPU_USAGE_CHECK:
		cmd_status = stbin_exec_check_cpu_usage(msg_length,msg, parms_in);
	break;

	case STBIN_READ_HEAP_CHECK:
		cmd_status = stbin_exec_check_heap(msg_length,msg, parms_in);
	break;

	case STBIN_READ_SW_CONF_PAR:
		cmd_status = stbin_exec_sw_config_get_par(msg_length,msg, parms_in);
	break;

	case STBIN_READ_DATUM:
		cmd_status = stbin_exec_read_datum_selection(msg_length,msg, parms_in);
	break;

	case STBIN_READ_SW_FE_DUMP:
		cmd_status = stbin_exec_dump_fe(msg_length,msg, parms_in);
	break;

	case STBIN_READ_SW_CONF_ALL_BLOCKS:
		cmd_status = stbin_exec_read_sw_config_all_blocks(msg_length,msg, parms_in);
	break;

	case STBIN_READ_DIFF_SOURCE:
		cmd_status = stbin_exec_get_diff_source(msg_length,msg, parms_in);
	break;

	case STBIN_READ_ADC:
#if defined ( STBIN_ADC_SUPPORT )
		cmd_status = stbin_exec_adc_read(msg_length,msg, parms_in);
#endif
	break;

	case STBIN_READ_ALL_SW_VER:
	  cmd_status = stbin_exec_get_all_sw_ver(msg_length, msg, parms_in);
	break;

	default:
		cmd_status = STBIN_NOTFOUND;
	break;
	}

	return cmd_status;
}
static stbin_status_t stbin_Decode_READ_PPS_req(tU16 msg_length, tUChar *msg, const stbin_req_msg_parms *parms_in)
{
  stbin_status_t cmd_status;
	switch((stbin_read_pps_req)parms_in->msg_Id)	{
	case STBIN_READ_PPS_IF_PULSE_DATA_CMD:
		cmd_status = stbin_exec_pps_if_pulse_data_read(msg_length, msg, parms_in);
	break;
	case STBIN_READ_PPS_IF_TIMING_DATA_CMD:
		cmd_status = stbin_exec_pps_if_timing_data_read(msg_length, msg, parms_in);
	break;
	case STBIN_READ_PPS_IF_POSITION_HOLD_DATA_CMD:
		cmd_status = stbin_exec_pps_if_pos_hold_data_read(msg_length, msg, parms_in);
	break;
	case STBIN_READ_PPS_IF_TRAIM_CMD:
		cmd_status = stbin_exec_pps_if_traim_read(msg_length, msg, parms_in);
	break;
	default:
		cmd_status = STBIN_NOTFOUND;
	break;
	}

  return cmd_status;
}
/***************************************************************
Decode all stbin_Decode_WRITE_req.
NOTE:  Import into stbin.c
*****************************************************************/
static stbin_status_t stbin_Decode_WRITE_req(tU16 msg_length, tUChar *msg, const stbin_req_msg_parms *parms_in)
{
	stbin_status_t cmd_status = 0;

	switch( (stbin_write_req)parms_in->msg_Id )
	{
	    case STBIN_WRITE_SET_GPS_POS:
	    	cmd_status = stbin_exec_set_gps_pos(msg_length, msg, parms_in);
	    break;
	    case STBIN_WRITE_SET_RANGE:
	    	cmd_status = stbin_exec_set_range(msg_length, msg, parms_in);
	    break;
	    case STBIN_WRITE_ADC_START:
#if defined ( STBIN_ADC_SUPPORT )
	    	cmd_status = stbin_exec_adc_start(msg_length, msg, parms_in);
#endif
	    break;
	    case STBIN_WRITE_LOWPOWER_ON_OFF:
	    	cmd_status = stbin_exec_lowpower_onoff(msg_length,msg, parms_in);
	    break;
	    case STBIN_WRITE_ALGO:
	    	 cmd_status = stbin_exec_set_algo_on_off(msg_length, msg, parms_in);
	    break;
	    case STBIN_WRITE_DATUM:
	      cmd_status = stbin_exec_write_datum_selection(msg_length, msg, parms_in);
	    break;
	    case STBIN_WRITE_DIFF_SOURCE:
	    	 cmd_status = stbin_exec_set_diff_source(msg_length, msg, parms_in);
	    break;
	    case STBIN_WRITE_SET_FIX_RATE:
	    	 cmd_status = stbin_exec_set_fix_rate(msg_length, msg, parms_in);
	    break;
	    case STBIN_WRITE_SET_CONSTEL_MASK:
	    	cmd_status = stbin_exec_set_constellation_mask(msg_length, msg, parms_in);
	    break;
	    case STBIN_WRITE_USER_DATUM:
	    	cmd_status = stbin_exec_define_user_datum(msg_length, msg, parms_in);
	    break;
	    case STBIN_LOAD_EPH:
	    	cmd_status = stbin_exec_load_ephemes(msg_length,msg, parms_in);
	    break;
	    case STBIN_LOAD_ALM:
	    	cmd_status = stbin_exec_load_almanac(msg_length,msg, parms_in);
	    break;
	    case STBIN_WRITE_DEBUG_ON_OFF:
	    	cmd_status = stbin_exec_debug_on_off(msg_length,msg, parms_in);
	    break;
	    case STBIN_WRITE_TIME_INV:
	    	cmd_status = stbin_exec_time_inv(msg_length,msg, parms_in);
	    break;
	    case STBIN_WRITE_NVM_SWAP:
	   	    cmd_status = stbin_exec_nvm_swap(msg_length,msg, parms_in);
	    break;
	    case STBIN_WRITE_NVM_ITEM_INV:
	  	    cmd_status = stbin_exec_nvm_item_inv(msg_length,msg, parms_in);
	    break;
	    case STBIN_WRITE_GPS_FW_UPDATE:
	    	cmd_status = stbin_exec_gps_fw_update(msg_length,msg, parms_in);
	    break;
	    case STBIN_WRITE_FIX2D_ON_OFF:
	    	cmd_status = stbin_exec_fix2d_on_off(msg_length,msg, parms_in);
	    break;
	    case STBIN_WRITE_STOP_DET_ON_OFF:
	    	cmd_status = stbin_exec_stop_detection_on_off(msg_length,msg, parms_in);
	    break;
	    case STBIN_WALKING_MODE_ON_OFF:
	    	 cmd_status = stbin_exec_walking_mode_on_off(msg_length,msg, parms_in);
	    break;
	    case STBIN_WRITE_SW_CONF_PAR_CHAR:
	    	cmd_status = stbin_exec_sw_config_set_param_char(msg_length,msg, parms_in);
	    break;
	    case STBIN_WRITE_SW_CONF_PAR_INT:
	    	cmd_status = stbin_exec_sw_config_set_param_int(msg_length,msg, parms_in);
	    break;
	    case STBIN_WRITE_SW_CONF_PAR_UINT:
	    	cmd_status = stbin_exec_sw_config_set_param_uint(msg_length,msg, parms_in);
	    break;
	    case STBIN_WRITE_SW_CONF_PAR_DOUBLE:
	    	cmd_status = stbin_exec_sw_config_set_param_double(msg_length,msg, parms_in);
	    break;
	    case STBIN_WRITE_SW_CONF_PAR_DOP:
	    	cmd_status = stbin_exec_sw_config_set_param_dop(msg_length,msg, parms_in);
	    break;
	    case STBIN_WRITE_SW_CONF_PAR_STRING:
	    	cmd_status = stbin_exec_sw_config_set_param_string(msg_length,msg, parms_in);
	    break;
	    case STBIN_SW_CONFIG_SAVE_PARAM:
	    	cmd_status = stbin_exec_sw_config_save_param(msg_length,msg, parms_in);
	    break;
	    case STBIN_SW_CONFIG_RESTORE_PARAM:
	    	cmd_status = stbin_exec_sw_config_restore_param(msg_length,msg, parms_in);
	    break;
	    case STBIN_RTC_WRITE:
	    	cmd_status = stbin_exec_rtc_write(msg_length,msg, parms_in);
	    break;
	    case STBIN_FE_WRITE:
	    	cmd_status = stbin_exec_fe_write(msg_length,msg, parms_in);
	    break;
	    case STBIN_SF_RECOVERY:
	    	cmd_status = stbin_exec_sf_recovery(msg_length,msg, parms_in);
	    break;
	    case STBIN_WRITE_NOTCH_ENABLE:
	    	cmd_status = stbin_exec_notch_enable(msg_length,msg, parms_in);
	    break;
	    case STBIN_WRITE_EPH:
	    	cmd_status = stbin_exec_save_ephems(msg_length,msg, parms_in);
	    break;
	    case STBIN_WRITE_ALM:
	    	cmd_status = stbin_exec_save_almanac(msg_length,msg, parms_in);
	    break;
	    case STBIN_WRITE_EN_DIS_POS_HOLD:
	    	cmd_status = stbin_exec_enable_disable_position_hold(msg_length,msg, parms_in);
	    break;
	    case STBIN_WRITE_EPH_ON_OFF:
	    	cmd_status = stbin_exec_real_ephems_on_off(msg_length,msg, parms_in);
	    break;
	    case STBIN_WRITE_SW_CONF_ALL_BLOCKS:
	    	cmd_status = stbin_exec_write_sw_config_all_blocks(msg_length,msg, parms_in);
	    break;
	    default :
	    	cmd_status = STBIN_NOTFOUND;
	    break;
	}

	if(cmd_status == STBIN_OK)
	{
		/*send ACK*/
		Send_ACKorNACK(ACK, parms_in);
	}

	return cmd_status;
}

static stbin_status_t stbin_Decode_PPS_WRITE_req(tU16 msg_length, tUChar *msg, const stbin_req_msg_parms *parms_in)
{
	stbin_status_t cmd_status;

	switch( (stbin_write_pps_req)parms_in->msg_Id )
	{
	    case STBIN_WRITE_PPS_IF_ON_OFF_CMD:
	    	cmd_status = stbin_exec_pps_if_on_off_cmd(msg_length,msg, parms_in);
	    break;
	    case STBIN_WRITE_PPS_IF_OUT_MODE_CMD:
	    	cmd_status = stbin_exec_pps_if_out_mode_cmd(msg_length,msg, parms_in);
	    break;
	    case STBIN_WRITE_PPS_IF_REF_CONST_CMD:
	    	cmd_status = stbin_exec_pps_if_ref_constellation_cmd(msg_length,msg, parms_in);
	    break;
	    case STBIN_WRITE_PPS_IF_REF_TIME_CMD:
	        cmd_status = stbin_exec_pps_if_ref_time_cmd(msg_length,msg, parms_in);
	    break;
	    case STBIN_WRITE_PPS_IF_PULSE_DELAY_CMD:
	        cmd_status = stbin_exec_pps_if_pulse_delay_cmd(msg_length,msg, parms_in);
	    break;
	    case STBIN_WRITE_PPS_IF_DURATION_CMD :
	    	cmd_status = stbin_exec_pps_if_duration_cmd(msg_length,msg, parms_in);
	    break;
	    case STBIN_WRITE_PPS_IF_PULSE_POLARITY_CMD:
	    	cmd_status = stbin_exec_pps_if_pulse_polarity_cmd(msg_length,msg, parms_in);
	    break;
	    case STBIN_WRITE_PPS_IF_DATA_CMD:
	    	cmd_status = stbin_exec_pps_if_data_cmd(msg_length,msg, parms_in);
	    break;
	    case STBIN_WRITE_PPS_IF_FIX_CONDITION_CMD:
	    	cmd_status = stbin_exec_pps_if_fix_condition_cmd(msg_length,msg, parms_in);
	    break;
	    case STBIN_WRITE_PPS_IF_SAT_THRESHOLD_CMD:
	        cmd_status = stbin_exec_pps_if_sat_threshold_cmd(msg_length,msg, parms_in);
	    break;
	    case STBIN_WRITE_PPS_IF_CONSTELLATION_RF_DELAY_CMD:
	    	cmd_status = stbin_exec_pps_if_constallation_rf_delay_cmd(msg_length,msg, parms_in);
	    break;
	    case STBIN_WRITE_PPS_IF_ELEVATION_MASK_CMD :
	    	cmd_status = stbin_exec_pps_if_elevation_mask_cmd(msg_length,msg, parms_in);
	    break;
	    case STBIN_WRITE_PPS_IF_COSTELLATION_MASK_CMD:
	    	cmd_status = stbin_exec_pps_if_constellation_mask_cmd (msg_length,msg, parms_in);
	    break;
	    case STBIN_WRITE_PPS_IF_TIMING_DATA_CMD:
	    	cmd_status = stbin_exec_pps_if_timing_data_cmd(msg_length,msg, parms_in);
	    break;
	    case STBIN_WRITE_PPS_IF_POSITION_HOLD_DATA_CMD:
	        cmd_status = stbin_exec_pps_if_hold_data_cmd(msg_length,msg, parms_in);
	    break;
	    case STBIN_WRITE_PPS_IF_AUTO_HOLD_SAMPLES_CMD:
	        cmd_status = stbin_exec_pps_if_auto_hold_samples_cmd(msg_length,msg, parms_in);
	    break;
	    case STBIN_WRITE_PPS_IF_TRAIM_AUTO:
	    	cmd_status = stbin_exec_pps_if_traim_cmd(msg_length,msg, parms_in);
	    break;
	    default :
	    	cmd_status = STBIN_NOTFOUND;
	    break;
	}
	if(cmd_status == STBIN_OK)
	{
		/*send ACK*/
		Send_ACKorNACK(ACK, parms_in);
	}

	return cmd_status;
}

#ifdef STBIN_SQI_DATASTORAGE
static stbin_status_t stbin_Decode_SQI_DATA_WRITE_req(tU16 msg_length, tUChar *msg, const stbin_req_msg_parms *parms_in)
{
	stbin_status_t cmd_status;

	switch( (stbin_sqi_data_write_req)parms_in->msg_Id )
	{

	case STBIN_WRITE_SQI_DATA_ERASE:
		cmd_status = stbin_exec_sqi_data_erase(msg_length,msg, parms_in);
	break;

	case STBIN_WRITE_SQI_DATA_SET:
		cmd_status = stbin_exec_sqi_data_set(msg_length,msg, parms_in);
	break;

	default :
		cmd_status = STBIN_NOTFOUND;
	break;
	}

	if(cmd_status == STBIN_OK)
	{
		/*send ACK*/
		Send_ACKorNACK(ACK, parms_in);
	}

	return cmd_status;
}

static stbin_status_t stbin_Decode_SQI_DATA_READ_req(tU16 msg_length, tUChar *msg, const stbin_req_msg_parms *parms_in)
{
  stbin_status_t cmd_status;

  switch((stbin_sqi_data_read_req)parms_in->msg_Id)
  {
    case STBIN_READ_SQI_DATA_GET:
       stbin_exec_sqi_data_get(msg_length, msg, parms_in);
       cmd_status = STBIN_OK;
    break;

    default:
       cmd_status = STBIN_NOTFOUND;
    break;
  }

  return cmd_status;
}
#endif

static stbin_status_t stbin_Decode_TEST_req(tU16 msg_length, tUChar *msg, const stbin_req_msg_parms *parms_in)
{
	stbin_status_t cmd_status;
	tInt doNotACKifOk = 0;

	switch( (stbin_test_req)parms_in->msg_Id )
	{
	case STBIN_TEST_RF_ON:
		cmd_status = stbin_exec_test_rf_on(msg_length,msg, parms_in);
	break;

	case STBIN_TEST_RF_ADD:
		cmd_status = stbin_exec_test_add(msg_length,msg, parms_in);
	break;

	case STBIN_TEST_RF_DEL:
		cmd_status = stbin_exec_test_del(msg_length,msg, parms_in);
	break;

	case STBIN_TEST_RF_OFF:
		cmd_status = stbin_exec_test_off(msg_length, msg, parms_in);
	break;

#ifdef RTC_TESTING
	case STBIN_TEST_RTC_ON:
		cmd_status = stbin_exec_test_rtc_on_off(msg_length, msg, parms_in);
	break;
#endif

	case STBIN_TEST_TRK_INTERFERE:
		 cmd_status = stbin_exec_test_trk_interfere (msg_length, msg, parms_in);
	break;

	case STBIN_TEST_RTC_ERROR:
    doNotACKifOk = 1; // A response is sent when treating this request
		cmd_status = stbin_exec_test_rtc_error (msg_length, msg, parms_in);
	break;

	default :
		cmd_status = STBIN_NOTFOUND;
	break;
	}
	if((cmd_status == STBIN_OK) && (doNotACKifOk == 0))
	{
		/*send ACK*/
		Send_ACKorNACK(ACK, parms_in);
	}

  return cmd_status;
}

static stbin_status_t stbin_Decode_RESET_req(tU16 msg_length, tUChar *msg, const stbin_req_msg_parms *parms_in)
{
	stbin_status_t cmd_status;

	switch( (stbin_reset_req)parms_in->msg_Id )
	{
		case STBIN_RESET_GPS:
		   cmd_status = stbin_exec_reset_gps (msg_length,msg, parms_in);
		break;
		case STBIN_RESET_SOFT:
		   cmd_status = stbin_exec_reset_soft (msg_length,msg, parms_in);
		break;
		case STBIN_RESET_STACK_CHECK:
		   cmd_status = stbin_exec_reset_stack_check(msg_length,msg, parms_in);
		break;
		case STBIN_RESET_GPS_SUSPEND:
		   cmd_status = stbin_exec_gps_suspend(msg_length,msg, parms_in);
		break;
		case STBIN_RESET_GPS_RESUME:
		   cmd_status = stbin_exec_gps_resume(msg_length,msg, parms_in);
		break;
		default :
		   cmd_status = STBIN_NOTFOUND;
		break;
	}
	if(cmd_status == STBIN_OK)
	{
		/*send ACK*/
		Send_ACKorNACK(ACK, parms_in);
	}

  return cmd_status;
}

/***************************************************************
Decode all gnss init funtions.
NOTE:  Import into stbin.c
*****************************************************************/
static stbin_status_t stbin_Decode_GNSS_init(tU16 msg_len, tUChar *msg_, const stbin_req_msg_parms *parms_in)
{
	stbin_status_t cmd_status;

	switch( (Exec_GNSS_init_ID)parms_in->msg_Id )
	{
	    case EXEC_INIT_GNSS_GPS:
		      cmd_status = stbin_exec_init_GPS_params( msg_len, msg_, parms_in);
	    break;
	    case EXEC_INIT_GNSS_FREQ:
	          cmd_status = stbin_exec_init_freq( msg_len, msg_ , parms_in);
	    break;
	    case EXEC_INIT_GNSS_COLD:
	    	  cmd_status = stbin_exec_init_cold( msg_len, msg_, parms_in );
	    break;
	    case EXEC_INIT_GNSS_WARM:
	   	      cmd_status = stbin_exec_init_warm( msg_len, msg_ , parms_in);
	    break;
	    case EXEC_INIT_GNSS_HOT:
	    	  cmd_status = stbin_exec_init_hot( msg_len, msg_ , parms_in);
	    break;
	    case EXEC_INIT_GNSS_TIME:
	    	  cmd_status = stbin_exec_init_GPS_time( msg_len, msg_ , parms_in);
	    break;
	    case EXEC_INIT_GNSS_CLR_EPH:
	    	  cmd_status = stbin_exec_init_clr_ephemes( msg_len, msg_ , parms_in);
	    break;
	    case EXEC_INIT_GNSS_CLR_ALM:
	    	  cmd_status = stbin_exec_init_clr_almanacs( msg_len, msg_ , parms_in);
	    break;
	    default :
	    	  cmd_status = STBIN_NOTFOUND;
	    break;
	}
	if(cmd_status == STBIN_OK)
	{
		/*send ACK*/
		Send_ACKorNACK(ACK, parms_in);
	}

  return cmd_status;
}

static stbin_status_t stbin_return_in_nmea_communication(tU16 length, tUChar *msg, const stbin_req_msg_parms *parms_in)
{
  stbin_status_t result = STBIN_OK;

  stbin_return_in_nmea_communication_MAP(req, msg, length, &result);

  if(STBIN_OK == result)
  {
    /*send ACK before switching */
    Send_ACKorNACK(ACK, parms_in);
    stbin_exec_switch_to_NMEA();
  }

  return result;
}

static stbin_status_t stbin_decode_itf_control_req(tU16 msg_length, tUChar *msg, const stbin_req_msg_parms *parms_in)
{
  stbin_status_t cmd_status;

  /* Called function must manage the ACK/NACK sending themselves because here we cannot know about the
  interface change processing */
  switch(parms_in->msg_Id) {
    case RETURN_IN_NMEA:
    cmd_status = stbin_return_in_nmea_communication(msg_length, msg, parms_in);
    break;

    case CONTROL_COMM_MSG_ID:
    cmd_status = stbin_control_output_req(msg_length, msg, parms_in);
    break;

    default:
    cmd_status = STBIN_NOTFOUND;
    break;
  }
  return cmd_status;
}

static stbin_status_t stbin_control_output_req(tU16 msg_length, tUChar *msg, const stbin_req_msg_parms *parms_in)
{
  stbin_status_t result = STBIN_OK;

  stbin_control_output_req_MAP(req, msg, msg_length, &result);

  if(result == STBIN_OK)
  {
    result = stbin_exec_binary_output_ON_OFF(req->onOff);
  }

  return result;
}

void Send_General_Read_Response(tU16 msg_length, tUChar *msg, const stbin_req_msg_parms *parms_in)
{
	  tUInt index=0U;
	  tUInt header_size = 0U;
	  tInt  len_response_msg;
	  tUChar dataTx[STBIN_MAX_BUFFER_SIZE];
	  tUChar *data_load_temp_ptr = msg;

	  /*Start build Frame Tx ......*/
	  dataTx[header_size]=SYNC_BYTE_1;
    header_size++;
	  dataTx[header_size]=SYNC_BYTE_2;
    header_size++;
	  dataTx[header_size]=parms_in->class_Id;
    header_size++;
	  dataTx[header_size]=parms_in->msg_Id;
    header_size++;

	  /*build len data load............*/
	  /*Len coded in little endian mode*/
	  *((tU16 *)&dataTx[header_size]) = msg_length;
	  header_size += 2U;

	  /*load in the frame the data load*/
	  for(index=0; index< msg_length; index++)
	  {
		  dataTx[header_size + index] = data_load_temp_ptr[index];
	  }

	  /*calculating ck........*/
	  /*load ck in the frame tx*/
	  len_response_msg = stbin_message_update_cs(dataTx, header_size + msg_length);

	  send_msg_to_uart_p(dataTx, len_response_msg);  /*Send frame on the uart........*/
}

static stbin_status_t stbin_exec_init_GPS_params(tU16 length, tUChar *msg, const stbin_req_msg_parms *parms_in)
{
	stbin_status_t result = STBIN_OK;
	tDouble lat_scaled;
	tDouble lon_scaled;
	tDouble height_scaled;

	stbin_exec_init_GPS_params_req_MAP(req, msg, length, &result);

  if(result != STBIN_OK)
  {
    return result;   /*lint !e904 Return statement before end of function */
  }

  lat_scaled = (tDouble)req->lat_val/SCALING_LAT_LON;
	lon_scaled = (tDouble)req->lon_val/SCALING_LAT_LON;
	height_scaled = (tDouble)req->height/SCALING_HEIGHT;

  if(gnss_set_pos(lat_scaled, lon_scaled, height_scaled)!=GNSS_NO_ERROR)
	{
    GPS_DEBUG_MSG(("gnss_set_pos() failed\r\n"));
		result = STBIN_FAILED;
		return result;   /*lint !e904 Return statement before end of function */
	}

  if(gnss_date_time_valid((tInt)req->year, (tInt)req->month, (tInt)req->day, (tInt)req->hour, (tInt)req->min, (tInt)req->sec) == FALSE)
  {
    // error
	  result = STBIN_FAILED;
    return result;   /*lint !e904 Return statement before end of function */
  }

  if(gnss_set_time((tInt)req->year, (tInt)req->month, (tInt)req->day,
    (tInt)req->hour, (tInt)req->min, (tInt)req->sec,
    (gnss_sat_type_t)req->constel) == GNSS_ERROR) {
	  result = STBIN_FAILED;
	  return result;   /*lint !e904 Return statement before end of function */
  }
	return result;
}

static stbin_status_t stbin_exec_init_GPS_time(tU16 length, tUChar *msg, const stbin_req_msg_parms *parms_in)
{
	stbin_status_t result = STBIN_OK;

	stbin_exec_init_GPS_time_req_MAP(req, msg, length, &result);

  if(result != STBIN_OK)
  {
    return result;   /*lint !e904 Return statement before end of function */
  }

  if(gnss_date_time_valid((tInt)req->year, (tInt)req->month, (tInt)req->day, (tInt)req->hour, (tInt)req->min, (tInt)req->sec) == FALSE)
  {
	  result = STBIN_FAILED;
    return result;   /*lint !e904 Return statement before end of function */
  }

  if(gnss_set_time((tInt)req->year, (tInt)req->month, (tInt)req->day,
    (tInt)req->hour, (tInt)req->min, (tInt)req->sec,
    (gnss_sat_type_t)req->constel) == GNSS_ERROR) {
	  result = STBIN_FAILED;
	  return result;   /*lint !e904 Return statement before end of function */
  }
	return result;
}

/*******************************************************************************
 * Il msg dell`intic could deve essere fatto solo su due byte (len=0x02)
 *
 * Un primo byte rappresentante l'init mask del cold start (stbin_dec_init_cold_start(message);)
 * Un secondo byte (Flag che se attivo richiama la
 * sw_config_get_param(CURRENT_CONFIG_DATA,COLD_START_TYPE_ID,&config_type);)
 * la quale ritorna il valore da passare alla stbin_dec_init_cold_start(message);
 *
 * ====================================
 * |message| flag sw_config_get_param |
 * ====================================
 *     |               |
 *     |               +-----> se vale == 1 il payload della stbin_dec_init_cold_start
 *     |                       e` dato dalla  sw_config_get_param
 *     +-----------> payload utile se flag == 0
 * ******************************************************************************/
static stbin_status_t  stbin_exec_init_cold(tU16 length, tUChar *msg, const stbin_req_msg_parms *parms_in)
{
  stbin_status_t result = STBIN_OK;
  tU8 init_type;

  stbin_exec_init_cold_req_MAP(req, msg, length, &result);

  if(result != STBIN_OK)
  {
    return result;   /*lint !e904 Return statement before end of function */
  }

	gnssapp_suspend();

	switch (req->use_fw)
	{
		case VAL_ONE:
			sw_config_get_param(CURRENT_CONFIG_DATA, COLD_START_TYPE_ID, &init_type);
		break;

		default:
			init_type = req->type;
		break;
	}

	stbin_exec_init_cold_start(init_type);
	platform_gnss_suspend();
	platform_gnss_restart();
	gnssapp_restart();

	return result;
}

/*{{{  nmea_init_cold_start()*/
void stbin_exec_init_cold_start(tU8 type)
{
	gpOS_task_delay(1000000);
	if ((type & 0x1U) != 0U)
	{
		gnss_clear_all_almanacs();
	}
	/* set up bad ephemeris data *//*nmea_init_warm_start();*/
	if ((type & 0x2U) != 0U)
	{
		gnss_clear_all_ephems();
	}
	/* set up erroneous user position */
	/* the following values have been chosen such that the user position is invalidated */
	if ((type & 0x4U) != 0U)
	{
		gnss_test_invalidate_user_pos();
		GPS_DEBUG_MSG(("invalid user position set ...\r\n"));
	}
	/* set up erroneous frequency */
	/*gnss_nmea_set_nco_value(FALSE, 0);
     GPS_DEBUG_MSG(("invalid nco frequency set ...\n"));*/

	/* set up an invalid rtc time */
	if ((type & 0x8U) != 0U)
	{
		gnss_test_invalidate_rtc();
		GPS_DEBUG_MSG(("invalid rtc set ...\r\n"));
	}

	if ((type & 0x10U) != 0U)
	{
		nvm_swap(TRUE);
	}

	if ((type & 0x20U) != 0U)
	{
		gnss_test_invalidate_utc_params();
		GPS_DEBUG_MSG(("invalid UTC set ...\r\n"));
	}
}

static stbin_status_t stbin_exec_init_warm(tU16 length, tUChar *msg, const stbin_req_msg_parms *parms_in)
{
	stbin_status_t result = STBIN_OK;

  stbin_exec_init_warm_req_MAP(req, msg, length, &result);

  if(result != STBIN_OK)
  {
    return result;   /*lint !e904 Return statement before end of function */
  }

  gnssapp_suspend();
  gnss_clear_all_ephems();
  platform_gnss_suspend();
  platform_gnss_restart();
  gnssapp_restart();

	return result;
}

static stbin_status_t stbin_exec_init_hot(tU16 length, tUChar *msg, const stbin_req_msg_parms *parms_in)
{
	stbin_status_t result = STBIN_OK;

  stbin_exec_init_hot_req_MAP(req, msg, length, &result);

  if(result != STBIN_OK)
  {
    return result;   /*lint !e904 Return statement before end of function */
  }

  gnssapp_suspend();
  platform_gnss_suspend();
  platform_gnss_restart();
  gnssapp_restart();

  return result;
}

static stbin_status_t stbin_exec_init_clr_ephemes(tU16 length, tUChar *msg, const stbin_req_msg_parms *parms_in)
{
  stbin_status_t result = STBIN_OK;

  stbin_exec_init_clr_ephemes_MAP(req,msg,length,&result);

  if(result == STBIN_OK)
  {
    gnss_clear_all_ephems();
  }

  return result;
}

static stbin_status_t stbin_exec_init_clr_almanacs(tU16 length, tUChar *msg, const stbin_req_msg_parms *parms_in)
{
  stbin_status_t result = STBIN_OK;

  stbin_exec_init_clr_almanacs_MAP(req,msg,length,&result);

    if(result == STBIN_OK)
  {
    gnss_clear_all_almanacs();
  }

  return result;
}

static stbin_status_t stbin_exec_set_gps_pos(tU16 len, tUChar *message, const stbin_req_msg_parms *parms_in)
{
	stbin_status_t result = STBIN_OK;
	tDouble lat;
	tDouble lon;
	tDouble height;

	stbin_exec_set_gps_pos_MAP(req,message,len,&result);

	if(result == STBIN_OK)
	{
		//lat    = stbin_dec_Get_Val(message, INDEX_LAT_MIN, INDEX_LAT_MAX,       Latitude) ;
		//lon    = stbin_dec_Get_Val(message, INDEX_LON_MIN, INDEX_LON_MAX,       Longitude);
		//height = stbin_dec_Get_Val(message, INDEX_HEIGHT_MIN, INDEX_HEIGHT_MAX, Height)   ;

    lat = (tDouble)((req->lat)/(tS32)SCALING_LAT_LON);
    lon = (tDouble)((req->lon)/(tS32)SCALING_LAT_LON);
    height = (tDouble)((req->alt)/(tS32)SCALING_1000);

    gnss_test_set_user_pos(lat * RADIANS, lon * RADIANS, height);

	}
	return result;
}

/*{{{  execute_set_range()*/
/***************************************************************************
 * Max and Min values are codified on 4 bytes.
 * *************************************************************************/
static stbin_status_t stbin_exec_set_range(tU16 len, tUChar *msg, const stbin_req_msg_parms *parms_in)
{
	stbin_status_t result = STBIN_OK;

	stbin_exec_set_range_MAP(req,msg,len, &result);

	if(result == STBIN_OK)
	{
    if ((gnss_set_freq_range(((tInt)req->max)/(tInt)SCALING_1000, ((tInt)req->min)/(tInt)SCALING_1000) != GNSS_NO_ERROR))
		{
			result=STBIN_FAILED;
		}
	}
        return result;
}

/***************************************************************************
 *
 * *************************************************************************/
#if defined ( STBIN_ADC_SUPPORT )
static stbin_status_t stbin_exec_adc_start(tU16 len, tUChar *msg, const stbin_req_msg_parms *parms_in)
{
  stbin_status_t result = STBIN_OK;
  tU16 clk_div = 0x1;

  stbin_exec_adc_start_MAP(req,msg,len, &result);

  if(result == STBIN_OK)
  {

    svc_adc_chan_cfg_t number_channels;
    //svc_adc_mode_cfg_t adc_mode = ADC_NOINTERRUPT;
    svc_adc_int_mode_cfg_t adc_mode = {
    (svc_adc_mode_cfg_t)ADC_NOINTERRUPT
    };

    if( !stbin_ext_adctest_started )
    {
      number_channels = (svc_adc_chan_cfg_t)req->sel_line;
      adc_mode.adc_int_mode = (svc_adc_mode_cfg_t) req->adc_functional_mode;

      if(( number_channels == ADC_8CHAN_AVAILABLE ) ||
        ( number_channels == ADC_4CHAN_AVAILABLE ) ||
        ( number_channels == ADC_2CHAN_AVAILABLE ) ||
        ( number_channels == ADC_1CHAN_AVAILABLE ))
      {

        svc_adc_init(NULL, 0, gpOS_INTERRUPT_NOPRIORITY, number_channels, clk_div, &adc_mode);
        stbin_ext_adctest_started = TRUE;
      }
      else
      {
        result = STBIN_FAILED;
        stbin_ext_adctest_started = FALSE;
        GPS_DEBUG_MSG(("STBIN adc start error: wrong sel_line number %d \r\n",req->sel_line));
      }
    }
    else
    {
      result = STBIN_FAILED;
      GPS_DEBUG_MSG(("STBIN adc start error: adc already started before \r\n"));
    }
  }

  return result;
}
#endif
/***************************************************************************
 *
 * *************************************************************************/
static stbin_status_t stbin_exec_lowpower_onoff(tU16 length, tUChar *msg, const stbin_req_msg_parms *parms_in)
{
  stbin_status_t result=STBIN_OK;

	stbin_exec_lowpower_onoff_MAP(Input_param, msg, length, &result);

	if(result == STBIN_OK)
	{
    gnss_low_power_cyclic_mode_t cyclic;
    gnss_low_power_periodic_mode_t periodic;

    cyclic.ehpe_threshold = Input_param->ehpe_threshold;
    cyclic.N_sats_reduced         = Input_param->N_sats_reduced;

    periodic.periodic_mode        = (boolean_t)((Input_param->periodic_mode >> 0) & 0x01);
    periodic.fix_period           = (tU32)Input_param->fix_period;
    periodic.fix_on_time          = (tU8)Input_param->fix_on_time;
    periodic.EPH_refresh          = (tU8)Input_param->EPH_refresh;
    periodic.RTC_refresh          = (tU8)Input_param->RTC_refresh;
    periodic.NoFixTimeout         = (tU8)Input_param->NoFixTimeout;
    periodic.NoFixOffTime         = (tU16)Input_param->NoFixOffTime;

    if ( Input_param->reduced_type == 0U )
    {
      if ( Input_param->duty_cycle_on_off == 1U )
      {
        cyclic.reduced_type       = FALSE;
        cyclic.duty_cycle_on_off  = TRUE;
        cyclic.ms_off             = (tShort)Input_param->ms_off;
      }
      else if ( Input_param->duty_cycle_on_off == 0U )
      {
        cyclic.reduced_type       = FALSE;
        cyclic.duty_cycle_on_off  = FALSE;
        cyclic.ms_off             = (tShort)Input_param->ms_off;
      }
    }
    else if ( Input_param->reduced_type == 1U )
    {
      if ( Input_param->duty_cycle_on_off == 1U )
      {
        cyclic.reduced_type       = TRUE;
        cyclic.duty_cycle_on_off  = TRUE;
        cyclic.ms_off             = (tShort)Input_param->ms_off;
      }
      else if ( Input_param->duty_cycle_on_off == 0U )
      {
        cyclic.reduced_type       = TRUE;
        cyclic.duty_cycle_on_off  = FALSE;
        cyclic.ms_off             = (tShort)Input_param->ms_off;
      }
    }

    /* load constellation applicable */
    cyclic.const_mask_init = Input_param->const_type;

    if ( Input_param->on_off == 0U )
    {
      gnssapp_low_power_setup_update(GNSSAPP_LOW_POWER_STANDBY_DISABLE, NULL, NULL);
    }
    else
    {
      gnss_app_lowpow_standby_type_t Standby;

      if(((Input_param->periodic_mode >> 1) & 0x01) == 0x01)
      {
        Standby = GNSSAPP_LOW_POWER_STANDBY_ENABLE;
      }
      else
      {
        Standby = GNSSAPP_LOW_POWER_STANDBY_DISABLE;
      }
      gnssapp_low_power_setup_update(Standby, &cyclic, &periodic);
    }

	}
	return result;
}
/***************************************************************************
 *
 * *************************************************************************/


static stbin_status_t stbin_exec_set_algo_on_off(tU16 length, tUChar *msg, const stbin_req_msg_parms *parms_in)
{
  stbin_status_t result = STBIN_OK;

  set_algo_status_MAP(Input_param, msg, length, &result);

	if(STBIN_OK == result)
	{
		switch(Input_param->algo_type)
		{
		  case 0:/*FDA*/
      break;

		  case 1:/*FDE*/
		  {
			  if (OFF != Input_param->algo_status)
			  {
				  gnss_set_fde_status(FDE_STATUS_ON);
			  }
			  else
			  {
				  gnss_set_fde_status(FDE_STATUS_OFF);
			  }
			}
      break;

		  case 2:/*ADS*/
		  break;

      default:
			break;
		}
	}
	return result;
}

/***************************************************************************
 * stbin_exec_set_diff_source is codified on 1 byte. following are present the
 * byte/signals codifies:
 *
 * LEN=0x01
 * PAYLOAD -->
 *                        ---------------------------
 *                        |    diff_source_value    |
 *                        ---------------------------
 *
 *          diff_source_value  = 0x00 = DIFF_SOURCE_NONE
 *                               0x01 = DIFF_SOURCE_WAAS
 *                               0x02 = DIFF_SOURCE_RTCM
 *                               0x03 = DIFF_SOURCE_AUTO
 * *************************************************************************/
static stbin_status_t stbin_exec_set_diff_source(tU16 len, tUChar *msg, const stbin_req_msg_parms *parms_in)
{
	 stbin_status_t result=STBIN_OK;
	 gnss_error_t err = GNSS_NO_ERROR;

	 stbin_exec_set_diff_source_MAP(req,msg, len, &result);

	 if(result == STBIN_OK)
	 {

		 switch ((gps_diff_source_t)req->diff_source)
		 {
		 case DIFF_SOURCE_NONE:
			 err = gnss_diff_set_source_type( DIFF_SOURCE_NONE);
			 break;
		 case DIFF_SOURCE_WAAS:
			 err =  gnss_diff_set_source_type( DIFF_SOURCE_WAAS);
			 break;
		 case DIFF_SOURCE_RTCM:
			 err = gnss_diff_set_source_type( DIFF_SOURCE_RTCM);
			 break;
		 case DIFF_SOURCE_AUTO:
			 err = gnss_diff_set_source_type( DIFF_SOURCE_AUTO);
			 break;
		 default:
			 result = STBIN_FAILED;
			 break;
		 }
		 if(err == GNSS_ERROR)
		 {
			 result = STBIN_FAILED;
		 }

	 }

	return result;
}

/*{{{  execute_set_fix_rate()*/
static stbin_status_t stbin_exec_set_fix_rate(tU16 len, tUChar *msg, const stbin_req_msg_parms *parms_in)
{
	stbin_status_t result=STBIN_OK;
	tDouble value;

	stbin_exec_set_fix_rate_MAP(req, msg, len,&result);

	if(result == STBIN_OK)
	{
		value = (tDouble)((req->fix_rate)/(tU16)SCALING_1000);

		if( gnss_set_fix_rate(value) == GNSS_ERROR)
		{
			result = STBIN_FAILED;
		}
	}
	return result;
}
/*}}}  */

/***************************************************************************
 * stbin_exec_set_constellation_mask
 * *************************************************************************/
static stbin_status_t stbin_exec_set_constellation_mask(tU16 len, tUChar *msg, const stbin_req_msg_parms *parms_in)
{
	stbin_status_t result=STBIN_OK;

	stbin_exec_set_constellation_mask_MAP(req,msg,len,&result);

  if(result == STBIN_OK)
  {
    if(req->slave_reset == 2U)
    {
      if(gnss_dynamic_set_constellation_mask(req->constellation_mask ) == GNSS_ERROR)
      {
        result=STBIN_FAILED;
      }
    }
    else
    {
      gnssapp_suspend();

      if( gnss_set_constellation_mask(req->constellation_mask) == GNSS_ERROR)
      {
        result=STBIN_FAILED;
        return result;   /*lint !e904 Return statement before end of function */
      }

      if(req->slave_reset == 1U)
      {
        platform_gnss_suspend();
        platform_gnss_restart();
      }
      gnssapp_restart();
    }
	}

	return result;
}

static stbin_status_t stbin_exec_load_ephemes(tU16 len, tUChar *msg, const stbin_req_msg_parms *parms_in)
{
	stbin_status_t result = STBIN_OK;

	stbin_exec_load_ephemes_MAP(req,msg,len,&result);

	if(result == STBIN_OK)
		{
			gnss_clear_all_ephems();
    if(nvm_swap(TRUE)!= NVM_NO_ERROR)
    {
      result = STBIN_FAILED;
    }
	}

	return result;
}

static stbin_status_t stbin_exec_load_almanac(tU16 len, tUChar *msg, const stbin_req_msg_parms *parms_in)
{
	stbin_status_t result = STBIN_OK;

	stbin_exec_load_almanac_MAP(req,msg,len,&result);

	if(result == STBIN_OK)
		{
			gnss_clear_all_almanacs();
    if(nvm_swap(TRUE)!= NVM_NO_ERROR)
    {
      result = STBIN_FAILED;
    }
	}

	return result;
}

static stbin_status_t stbin_exec_debug_on_off(tU16 len, tUChar *msg, const stbin_req_msg_parms *parms_in)
{
	stbin_status_t result=STBIN_OK;

	stbin_exec_debug_on_off_MAP(req,msg,len,&result);

	if(result == STBIN_OK)
	{
    if ( req->on_off != 0U )
		{
      //in_out_open_port( IN_OUT_DEBUG_PORT );
			gnss_debug_set_status(GNSS_DEBUG_ON);
		}
		else
		{
			gnss_debug_set_status(GNSS_DEBUG_OFF);
      //in_out_close_port( IN_OUT_DEBUG_PORT );
		}
	}

	return result;
}

static stbin_status_t stbin_exec_time_inv(tU16 len, tUChar *msg, const stbin_req_msg_parms *parms_in)
{
	stbin_status_t result=STBIN_OK;

	stbin_exec_time_inv_MAP(req,msg,len,&result);

	if(result == STBIN_OK)
		{
			gnss_test_invalidate_rtc();
		}

	return result;
}

static stbin_status_t stbin_exec_gps_suspend(tU16 len, tUChar *msg, const stbin_req_msg_parms *parms_in)
{
	stbin_status_t result=STBIN_OK;

	stbin_exec_gps_suspend_MAP(req,msg,len,&result);

	if(result == STBIN_OK)
		{
			gnssapp_suspend();
			platform_gnss_suspend();

	}
	return result;
}

static stbin_status_t stbin_exec_gps_resume(tU16 len, tUChar *msg, const stbin_req_msg_parms *parms_in)
{
	stbin_status_t result=STBIN_OK;

	stbin_exec_gps_resume_MAP(req,msg,len,&result)

	if(result == STBIN_OK)
		{
			platform_gnss_restart();
			gnssapp_restart();
		}
	return result;
}

static stbin_status_t stbin_exec_nvm_swap(tU16 len, tUChar *msg, const stbin_req_msg_parms *parms_in)
{
	stbin_status_t result=STBIN_OK;

	stbin_exec_nvm_swap_MAP(req, msg, len, &result);

	if(result == STBIN_OK)
	{
    if(nvm_swap(TRUE) != NVM_NO_ERROR)
		{
			result=STBIN_FAILED;
		}
	}
	return result;
}

/***************************************************************************

 * *************************************************************************/
static stbin_status_t stbin_exec_nvm_item_inv(tU16 len, tUChar *msg, const stbin_req_msg_parms *parms_in)
{
  stbin_status_t result=STBIN_OK;

  gnsslibid_t idx;

  stbin_exec_nvm_item_inv_MAP(req, msg, len, &result);

  if(result == STBIN_OK)
  {
    if((req->sat_id != 0U)&&((req->nvm_id== 1 /*GNSS_NVMID_ALMANACS*/)||(req->nvm_id==2/*GNSS_NVMID_EPHEMERIDES*/)))
    {

      idx  = GNSS_NAV_SAT_ID_TO_GNSSLIB_ID(req->sat_id);

      if(idx != GNSSLIB_ID_NOT_VALID)
      {
        if(nvm_set_item_invalid( req->nvm_id, (tInt)(1U + idx) )== NVM_ERROR)
        {
          result=STBIN_FAILED;
        }
      }
      else
      {
        result=STBIN_FAILED;
      }

    }
    else
    {
      if(nvm_set_item_invalid(req->nvm_id,req->item_number) == NVM_ERROR)
      {
        result=STBIN_FAILED;
      }
    }
  }

  return result;
}

static stbin_status_t stbin_exec_gps_fw_update(tU16 len, tUChar *msg, const stbin_req_msg_parms *parms_in)
{
	stbin_status_t result=STBIN_OK;

	stbin_exec_gps_fw_update_MAP(req,msg,len,&result);

	if(result == STBIN_OK)
		{
			execute_fwupgrade();
		}

	return result;
}

/*{{{  execute_fwupgrade()*/
static void execute_fwupgrade(void)
{
  #if defined( STBIN_BINIMG_SUPPORT )
  gnssapp_suspend();

  gpOS_task_delay( gpOS_timer_ticks_per_sec() / 10U );
  gpOS_interrupt_lock();

  platform_fwupgrade();
  #endif
}
/*}}}  */

//*************************************************************************
//len=1 - msg[0] = 1 --> gnss_fix_allow_large_2D_move = TRUE
//ELSE
//gnss_fix_allow_large_2D_move = FALSE
//**************************************************************************
static stbin_status_t stbin_exec_fix2d_on_off(tU16 len, tUChar *msg, const stbin_req_msg_parms *parms_in)
{
	stbin_status_t result=STBIN_OK;
	extern boolean_t gnss_fix_allow_large_2D_move;

  stbin_exec_fix2d_on_off_MAP(req, msg, len,&result);

	if(result == STBIN_OK)
	{
		if(req->on_off == 1U)
		{
	       gnss_fix_allow_large_2D_move = TRUE;
      GPS_DEBUG_MSG((">>>>>>>>>>>>>>>> stbin_exec_fix2d_on_off: 2D fix enabled \r\n"));
		}
		else
		{
		   gnss_fix_allow_large_2D_move = FALSE;
      GPS_DEBUG_MSG((">>>>>>>>>>>>>>>> stbin_exec_fix2d_on_off: 2D fix disabled \r\n"));
		}
	}
	return result;
}

//*************************************************************************
//len=1 - msg[0] = 1 --> gnss_turn_stop_detection_on = TRUE
//ELSE
//gnss_turn_stop_detection_on = FALSE
//**************************************************************************
static stbin_status_t stbin_exec_stop_detection_on_off(tU16 len, tUChar *msg, const stbin_req_msg_parms *parms_in)
{
	stbin_status_t result=STBIN_OK;

	stbin_exec_stop_detection_on_off_MAP(req,msg,len,&result);

	if(result == STBIN_OK)
	{
		if(req->on_off== ON)
		{
			gnss_turn_stop_detection_on(TRUE);
		}
		else
		{
			gnss_turn_stop_detection_on(FALSE);
		}
	}
	return result;
}


//*************************************************************************
//len=1 - msg[0] = 1 --> gnss_turn_walking_mode_on = TRUE
//ELSE
//gnss_turn_walking_mode_on = FALSE
//**************************************************************************
static stbin_status_t stbin_exec_walking_mode_on_off(tU16 len, tUChar *msg, const stbin_req_msg_parms *parms_in)
{
	stbin_status_t result=STBIN_OK;

	stbin_exec_walking_mode_on_off_MAP(req,msg,len,&result);

	if(result == STBIN_OK)
	{
		if(req->on_off == ON)
		{
			gnss_turn_walking_mode_on(TRUE);
		}
		else
		{
			gnss_turn_walking_mode_on(FALSE);
		}
	}
	return result;
}

static stbin_status_t stbin_exec_sw_config_set_param_char(tU16 length, tUChar *msg, const stbin_req_msg_parms *parms_in)
{
	stbin_status_t result = STBIN_OK;

  sw_config_set_par_val_Char_MAP(Input_param, msg, length, &result);

	if(STBIN_OK == result)
	{
    if(GNSS_ERROR == sw_config_set_param((100 + (tInt)Input_param->configParamId),&(Input_param->value),0))
    {
      result = STBIN_FAILED;
    }
  }

	return result;
}

static stbin_status_t stbin_exec_sw_config_set_param_int(tU16 length, tUChar *msg, const stbin_req_msg_parms *parms_in)
{
	stbin_status_t result = STBIN_OK;

  sw_config_set_par_val_Int_MAP(Input_param, msg, length, &result);

	if(STBIN_OK == result)
	{
    if(GNSS_ERROR == sw_config_set_param((200 + (tInt)Input_param->configParamId),&(Input_param->value),0))
    {
      result = STBIN_FAILED;
    }
  }

	return result;
}

static stbin_status_t stbin_exec_sw_config_set_param_uint(tU16 length, tUChar *msg, const stbin_req_msg_parms *parms_in)
{
	stbin_status_t result = STBIN_OK;

  sw_config_set_par_val_UInt_MAP(Input_param, msg, length, &result);

	if(STBIN_OK == result)
	{
#if defined( DR_CODE_LINKED )
    if(2 == Input_param->configSection)
    {
#endif
      if(GNSS_ERROR == sw_config_set_param((200 + (tInt)Input_param->configParamId),&(Input_param->value),Input_param->mode))
      {
        result = STBIN_FAILED;
      }
#if defined( DR_CODE_LINKED )
    }
    else
    {
      if(GNSS_ERROR == sw_config_set_param((600 + (tInt)Input_param->configParamId),&(Input_param->value),Input_param->mode))
      {
        result = STBIN_FAILED;
      }
    }
#endif
  }

	return result;
}

static stbin_status_t stbin_exec_sw_config_set_param_double(tU16 length, tUChar *msg, const stbin_req_msg_parms *parms_in)
{
	stbin_status_t result = STBIN_OK;

  sw_config_set_par_val_Double_MAP(Input_param, msg, length, &result);

	if(STBIN_OK == result)
	{
    if(GNSS_ERROR == sw_config_set_param((300 + (tInt)Input_param->configParamId),&(Input_param->value),0))
    {
      result = STBIN_FAILED;
    }
  }

	return result;
}

static stbin_status_t stbin_exec_sw_config_set_param_dop(tU16 length, tUChar *msg, const stbin_req_msg_parms *parms_in)
{
	stbin_status_t result = STBIN_OK;
  sw_config_dops_t       Dop_param;

  sw_config_set_par_val_Dops_MAP(Input_param, msg, length, &result);

	if(STBIN_OK == result)
	{
    Dop_param.gdop = Input_param->gdop;
    Dop_param.hdop = Input_param->hdop;
    Dop_param.pdop = Input_param->pdop;
    Dop_param.vdop = Input_param->vdop;

    if(GNSS_ERROR == sw_config_set_param((400 + (tInt)Input_param->configParamId),&Dop_param,0))
    {
      result = STBIN_FAILED;
    }
  }

	return result;
}

static stbin_status_t stbin_exec_sw_config_set_param_string(tU16 length, tUChar *msg, const stbin_req_msg_parms *parms_in)
{
	stbin_status_t result = STBIN_OK;

  sw_config_set_par_val_String_MAP(Input_param, msg, length, &result);

	if(STBIN_OK == result)
	{
    if(GNSS_ERROR == sw_config_set_param((500 + (tInt)Input_param->configParamId),&(Input_param->value),0))
    {
      result = STBIN_FAILED;
    }
  }

	return result;
}

static stbin_status_t stbin_exec_sw_config_save_param(tU16 length, tUChar *msg, const stbin_req_msg_parms *parms_in)
{
	stbin_status_t result=STBIN_OK;

  stbin_exec_sw_config_save_param_MAP(req, msg, length, &result);

	if(STBIN_OK == result)
	{
		if(sw_config_save_param()!= GNSS_ERROR )
		{
			gnssapp_swconfig_reload();
		}
		else
		{
			result = STBIN_FAILED;
		}
	}

	return result;
}

static stbin_status_t stbin_exec_sw_config_restore_param(tU16 length, tUChar *msg, const stbin_req_msg_parms *parms_in)
{
	stbin_status_t result=STBIN_OK;

  stbin_exec_sw_config_restore_param_MAP(req, msg, length, &result);

	if(STBIN_OK == result)
	{
		if(sw_config_restore_param()!= GNSS_ERROR )
		{
			gnssapp_swconfig_reload();
		}
		else
		{
			result = STBIN_FAILED;
		}
	}

	return result;
}

static stbin_status_t stbin_exec_rtc_write(tU16 len, tUChar *msg, const stbin_req_msg_parms *parms_in)
{
	tUInt current_RTC;
	stbin_status_t result=STBIN_OK;

	stbin_exec_rtc_write_MAP(req,msg,len,&result) ;

	  if(result == STBIN_OK)
	  {
		  rtc_drv_rtc_read(&current_RTC);
		  current_RTC += (tUInt)req->time_delta;

		  if(rtc_drv_rtc_write(current_RTC) == GNSS_ERROR)
		  {
			  result = STBIN_FAILED;
		  }
	  }

	return result;
}

static stbin_status_t stbin_exec_fe_write(tU16 len, tUChar *msg, const stbin_req_msg_parms *parms_in)
{
	stbin_status_t result = STBIN_OK;
	tUInt addr;
	tU8 data;

#ifdef STBIN_FRONTEND_SUPPORT
	stbin_exec_fe_write_MAP(req,msg,len,&result);

	  if(result == STBIN_OK)
	  {
		  addr = req->addr;
		  data = req->data;

		  if( FE_write_data( addr, data) == LLD_ERROR)
		  {
			  result = STBIN_FAILED;
			  GPS_DEBUG_MSG(("STBIN [fe][write]: error 0x%x = 0x%x\r\n", addr, data));
		  }
	  }
#endif
	return result;
}

static stbin_status_t stbin_exec_sf_recovery(tU16 len, tUChar *msg, const stbin_req_msg_parms *parms_in)
{
	stbin_status_t result=STBIN_OK;
	tUChar sf_rec_status = 0 ;

	stbin_exec_sf_recovery_MAP(req,msg,len,&result)

	if(result == STBIN_OK)
	{
		sf_rec_status = req->on_off;

		switch(sf_rec_status)
		{
		case ON:
			gnss_set_sf_recovery_status(TRUE);
			break;
		case OFF:
			gnss_set_sf_recovery_status(FALSE);
			break;
		default :
			result = STBIN_FAILED;
			break;
		}
	}

	return result;
}

/*****************************************************************************************************
 * notch sat type , notch status,  and noth freq values are codified on 6 bytes.
 * following are present the byte/signals codifies:
 *
 * LEN = 6 => 1(notch sat type) + 1(notch status) + 4 (noth freq)
 * PAYLOAD -->
 * ----------------------------------------------------------------------------------------------
 * | notch sat type | notch status | noth freq HHB |noth freq HB | noth freq HLB |noth freq LLB |
 * ----------------------------------------------------------------------------------------------
 * notch sat type  tChar [0-1]
 * notch status    tChar [0-2]
 * noth freq       tInt on 32 bit
 *
 * *************************************************************************************************/
static stbin_status_t stbin_exec_notch_enable(tU16 len, tUChar *msg, const stbin_req_msg_parms *parms_in)
{
	stbin_status_t result=STBIN_OK;

	stbin_exec_notch_enable_MAP(req,msg,len,&result);

	if(result == STBIN_OK)
	{
    #if defined( STBIN_NOTCH_SUPPORT )
	  tUChar notch_sat_type,notch_status;
    tInt notch_frequency;    //coding freq from bus
    tInt starting_frequency; //processed notch freq for API

		notch_sat_type     = (tUChar)req->sat_type;
		notch_status       = (tUChar)req->mode;
		notch_frequency    = (tInt)req->Reserved;


		starting_frequency = stbin_dec_return_elaborate_notch_freq_forAPI(notch_sat_type, notch_status, notch_frequency );

		if((notch_status == STBIN_NOTCH_FILTER_ENABLED)     ||   (notch_status == STBIN_NOTCH_FILTER_ENABLED_AUTO))
		{
			if( notch_sat_type == STBIN_NOTCH_FILTER_PATH_GPS)
			{
				gnss_notch_filter_enable(GNSS_SAT_TYPE_GPS,starting_frequency,(tInt)notch_status);
			}
			else if ( notch_sat_type == STBIN_NOTCH_FILTER_PATH_GLONASS)
			{
				gnss_notch_filter_enable(GNSS_SAT_TYPE_GLONASS,starting_frequency,(tInt)notch_status);
			}

		}
    if( notch_status == STBIN_NOTCH_FILTER_DISABLED) /* disable a branch*/
		{
      if( notch_sat_type == STBIN_NOTCH_FILTER_PATH_GPS )
				 {
					 gnss_notch_filter_disable(GNSS_SAT_TYPE_GPS);
				 }
      else if (notch_sat_type == STBIN_NOTCH_FILTER_PATH_GLONASS)
				 {
					 gnss_notch_filter_disable(GNSS_SAT_TYPE_GLONASS);
				 }
			 }
    GPS_DEBUG_MSG(("STBIN stbin_exec_notch_enable: sat_type %d ; mode %d\r\n",notch_sat_type,notch_status));

    #endif
	}
	return result;
}


static stbin_status_t stbin_exec_save_ephems(tU16 length, tUChar *msg, const stbin_req_msg_parms *parms_in)
{
	stbin_status_t result=STBIN_OK;

	stbin_exec_save_ephems_MAP(Input_param, msg, length, &result);

	if(result == STBIN_OK)
	{
		if(GNSS_ERROR == gnss_set_ephemeris_params(Input_param->dsp_satid, (ephemeris_raw_t*)(&(Input_param->value))))
		{
			result = STBIN_FAILED;
		}
	}
	return result;
}

static stbin_status_t stbin_exec_real_ephems_on_off(tU16 length, tUChar *msg, const stbin_req_msg_parms *parms_in)
{
  stbin_status_t result=STBIN_OK;

	stbin_exec_real_ephems_on_off_MAP(Input_param, msg, length, &result);

	if(result == STBIN_OK)
	{

    if( Input_param->param == 1U )
    {
      gnss_ephemeris_broadcast_enable_sat( Input_param->sat_id );
    }
    else
    {
      gnss_ephemeris_broadcast_disable_sat( Input_param->sat_id );
    }

	}
	return result;
}

static stbin_status_t stbin_exec_save_almanac(tU16 length, tUChar *msg, const stbin_req_msg_parms *parms_in)
{
	stbin_status_t result=STBIN_OK;

	stbin_exec_save_alams_MAP(Input_param, msg, length, &result);

	if(result == STBIN_OK)
	{
		if(GNSS_ERROR == gnss_set_almanac_params(Input_param->dsp_satid, (almanac_raw_t*)(&(Input_param->value))))
		{
			result = STBIN_FAILED;
		}
	}
	return result;
}

static stbin_status_t stbin_exec_enable_disable_position_hold(tU16 message_len, tUChar *message, const stbin_req_msg_parms *parms_in)
{
	stbin_status_t result = STBIN_OK;
	tDouble lat;
	tDouble lon;
	tDouble height;

	stbin_exec_enable_disable_position_hold_MAP(req,message,message_len,&result);

  if ( req->on_off != 0U )
	{
    if(result==STBIN_OK)
	{
        //lat    = stbin_dec_Get_Val(message, INDEX_LAT_MIN, INDEX_LAT_MAX,       Latitude) ;
        //lon    = stbin_dec_Get_Val(message, INDEX_LON_MIN, INDEX_LON_MAX,       Longitude);
        //height = stbin_dec_Get_Val(message, INDEX_HEIGHT_MIN, INDEX_HEIGHT_MAX, HEIGHT_MIN_VAL_EN_DIS_POS_HOLD);

        //lat    = lat * RADIANS;
        //lon    = lon * RADIANS;
        //height = height * RADIANS;
        lat = (tDouble)((req->lat)/(tS32)SCALING_LAT_LON);
        lon = (tDouble)((req->lon)/(tS32)SCALING_LAT_LON);
        height = (req->alt)/(tS32)SCALING_1000;
        gnss_pps_set_position_hold_llh_pos(lat,lon,height);
        gnss_pps_set_position_hold_status(TRUE);
    }
		}
		else
		{
    gnss_pps_set_position_hold_status( FALSE );
    result = STBIN_OK;
	}

	return result;
}


static stbin_status_t stbin_exec_write_sw_config_all_blocks(tU16 message_len, tUChar *message, const stbin_req_msg_parms *parms_in)
{
  stbin_status_t result = STBIN_OK;

  stbin_exec_write_sw_config_all_blocks_MAP(req,message,message_len,&result);

  if(result==STBIN_OK)
	{
    if(req->length == sizeof( sw_config_t ))
    {
      if ( sw_config_data_block_write(req->length, 0,req->value ) == GNSS_ERROR )
      {
        result = STBIN_FAILED;
        GPS_DEBUG_MSG((">>> ERROR stbin_exec_write_sw_config_all_blocks: write failed \r\n"));
      }
    }
    else
    {
      result = STBIN_FAILED;
      GPS_DEBUG_MSG((">>> ERROR stbin_exec_write_sw_config_all_blocks: length = %d ; sizeof(sw_config_t) = %d\r\n",req->length,sizeof( sw_config_t )));
    }
    //Debug
    //sw_config_print();
  }
  return result;

}

/************************************
 * Len = 1
 * payload = ON or OFF
 ************************************/
static stbin_status_t stbin_exec_pps_if_on_off_cmd(tU16 length, tUChar *msg, const stbin_req_msg_parms *parms_in)
{
	stbin_status_t result = STBIN_OK;

	stbin_exec_pps_if_on_off_write_req_MAP(req, msg, length, &result);

  if(STBIN_OK == result)
  {
    gnss_pps_set_signal_on_off_status((boolean_t)req->onOff);
  }

	return result;
}

/********************************************************
 * Len = 1
 * payload = only 0-1-2.  other values send nack
 *******************************************************/
static stbin_status_t stbin_exec_pps_if_out_mode_cmd(tU16 length, tUChar *msg, const stbin_req_msg_parms *parms_in)
{
	stbin_status_t result = STBIN_OK;

	stbin_exec_pps_if_output_mode_write_req_MAP(req, msg, length, &result);

  if(STBIN_OK == result)
  {
    gnss_pps_set_output_mode((pps_output_mode_t)req->outMode);
  }

	return result;
}

/********************************************************
 * Len = 2
 * payload =  .... see gnss_sat_type_t
 *******************************************************/
static stbin_status_t stbin_exec_pps_if_ref_constellation_cmd(tU16 length, tUChar *msg, const stbin_req_msg_parms *parms_in)
{
	stbin_status_t result = STBIN_OK;

	stbin_exec_pps_if_ref_constellation_write_req_MAP(req, msg, length, &result);

  if(STBIN_OK == result)
  {
    gnss_pps_set_reference_constellation((gnss_sat_type_t)req->refConst);
  }

 	return result;
}

/********************************************************
 * Len = 1
 * payload = [0-4].  other values send nack
 *******************************************************/
static stbin_status_t stbin_exec_pps_if_ref_time_cmd(tU16 length, tUChar *msg, const stbin_req_msg_parms *parms_in)
{
	stbin_status_t result = STBIN_OK;

	stbin_exec_pps_if_ref_time_write_req_MAP(req, msg, length, &result);

  if(STBIN_OK == result)
  {
		gnss_pps_set_reference_time((pps_reference_time_t)req->refTimeId);
  }

	return result;
}

/********************************************************
 * Len = 2
 * payload decode the time in nano seconds.
 * The scaling value is static scaling = 1E-9,
 * the paylod codified shall be
 * multiplied for the scaling value:
 *================================================
 * payload(twobytes) x scaling = input api (delayCMD)
 *================================================
 *******************************************************/
static stbin_status_t stbin_exec_pps_if_pulse_delay_cmd(tU16 length, tUChar *msg, const stbin_req_msg_parms *parms_in)
{
	stbin_status_t result = STBIN_OK;
	tDouble delay;

	stbin_exec_pps_if_pulse_delay_write_req_MAP(req, msg, length, &result);

  if(STBIN_OK == result) {
    // convert to ns
    delay = ((tDouble)(req->pulseDelay)) * (1E-9);
		gnss_pps_set_time_delay(delay);
	}

	return result;
}

/********************************************************
 * Len = 2
 * payload decode the time in milli seconds.
 * The scaling value is static scaling = 1E-3,
 * the paylod codified shall be
 *
 * multiplied for the scaling value:
 *================================================
 * payload(twobytes) x scaling = time api value
 *================================================
 *
 *The payload is defined into a range:
 *[0.1sec 0.9sec] border included
 *******************************************************/
static stbin_status_t stbin_exec_pps_if_duration_cmd(tU16 length, tUChar *msg, const stbin_req_msg_parms *parms_in)
{
	stbin_status_t result = STBIN_OK;
	tDouble pulse_duration;

	stbin_exec_pps_if_pulse_duration_write_req_MAP(req, msg, length, &result);

  if(STBIN_OK == result) {
    // convert to ms
    pulse_duration = ((tDouble)(req->pulseDuration)) * (1E-3);
    gnss_pps_set_pulse_duration(pulse_duration);
  }

	return result;
}

/************************************
 * Len = 1
 * payload = ON or OFF
 ************************************/
static stbin_status_t stbin_exec_pps_if_pulse_polarity_cmd(tU16 length, tUChar *msg, const stbin_req_msg_parms *parms_in)
{
	stbin_status_t result = STBIN_OK;

	stbin_exec_pps_if_pulse_polarity_write_req_MAP(req, msg, length, &result);

  if(STBIN_OK == result)
  {
		gnss_pps_set_polarity(req->pulsePolarity);
  }

	return result;
}

static stbin_status_t stbin_exec_pps_if_data_cmd(tU16 length, tUChar *msg, const stbin_req_msg_parms *parms_in)
{
	tDouble delay;
	tDouble pulse_duration;
	stbin_status_t result = STBIN_OK;

	stbin_exec_pps_if_data_write_req_MAP(req, msg, length, &result);

  if(STBIN_OK == result) {
    gnss_pps_set_output_mode((pps_output_mode_t)req->outMode);
		gnss_pps_set_reference_time((pps_reference_time_t)req->refTimeId);
		gnss_pps_set_polarity(req->pulsePolarity);

    delay = ((tDouble)(req->pulseDelay)) * (1E-9); // convert to ns
		gnss_pps_set_time_delay(delay);

    pulse_duration = ((tDouble)(req->pulseDuration)) * (1E-3); // convert to ms
    gnss_pps_set_pulse_duration(pulse_duration);
  }

	return result;
}

/************************************
 * Len = 1
 * payload = NO_FIX = 1,
             FIX_2D = 2,
             FIX_3D = 3
 ************************************/
static stbin_status_t stbin_exec_pps_if_fix_condition_cmd(tU16 length, tUChar *msg, const stbin_req_msg_parms *parms_in)
{
	stbin_status_t result = STBIN_OK;

	stbin_exec_pps_if_fix_condition_write_req_MAP(req, msg, length, &result);

  if(STBIN_OK == result) {
		gnss_pps_set_fix_condition((fix_status_t)req->fixCondition);
  }

	return result;
}

/************************************
 * Len = 1
 * payload = 0-255
 ************************************/
static stbin_status_t stbin_exec_pps_if_sat_threshold_cmd(tU16 length, tUChar *msg, const stbin_req_msg_parms *parms_in)
{
	stbin_status_t result = STBIN_OK;
	stbin_exec_pps_if_sat_threshold_write_req_MAP(req, msg, length, &result);

  if(STBIN_OK == result) {
		gnss_pps_set_sat_threshold(req->satTh);
	}

	return result;
}
/********************************************************
 * Len = 4
 * payload =  4 byte = 2byte (Sat_type) + 2byte(RF comp)
 *
 * Sat type is a signed value
 * rf comp is tUInt value.
 * scaling value for rf_comp is static = 1E-9
 *******************************************************/
static stbin_status_t stbin_exec_pps_if_constallation_rf_delay_cmd(tU16 length, tUChar *msg, const stbin_req_msg_parms *parms_in)
{

	tDouble rf_compensation;
	stbin_status_t result = STBIN_OK;
	stbin_exec_pps_if_constallation_rf_delay_write_req_MAP(req, msg, length, &result);

  if(STBIN_OK == result) {
		rf_compensation =  ((tDouble)req->rfDelay) * (1E-9);
		gnss_pps_set_rf_compensation((gnss_sat_type_t)req->constellation, rf_compensation);
	}

	return result;
}

static stbin_status_t stbin_exec_pps_if_elevation_mask_cmd(tU16 length, tUChar *msg, const stbin_req_msg_parms *parms_in)
{
	stbin_status_t result = STBIN_OK;
	stbin_exec_pps_if_elevation_mask_write_req_MAP(req, msg, length, &result);

  if(STBIN_OK == result) {
		gnss_pps_set_elevation_mask(req->elevationMask);
	}

	return result;
}

static stbin_status_t stbin_exec_pps_if_constellation_mask_cmd(tU16 length, tUChar *msg, const stbin_req_msg_parms *parms_in)
{
	stbin_status_t result = STBIN_OK;
	stbin_exec_pps_if_constellation_mask_write_req_MAP(req, msg, length, &result);

  if(STBIN_OK == result) {
		gnss_pps_set_constellation_mask(req->constellationMask);
	}

	return result;
}

static stbin_status_t stbin_exec_pps_if_timing_data_cmd(tU16 length, tUChar *msg, const stbin_req_msg_parms *parms_in)
{
	stbin_status_t result = STBIN_OK;

	stbin_exec_pps_if_timing_data_write_req_MAP(req, msg, length, &result);

  if(STBIN_OK == result) {
		gnss_pps_set_fix_condition((fix_status_t)req->fixCondition);
		gnss_pps_set_sat_threshold(req->satTh);
		gnss_pps_set_elevation_mask(req->elevationMask);
		gnss_pps_set_constellation_mask(req->constellationMask);
	}

	return result;
}

static stbin_status_t stbin_exec_pps_if_hold_data_cmd(tU16 length, tUChar *msg, const stbin_req_msg_parms *parms_in)
{
	tDouble lat;
	tDouble lon;
	tDouble height;
	stbin_status_t result = STBIN_OK;

	stbin_exec_pps_if_hold_data_write_req_MAP(req, msg, length, &result);

  if(STBIN_OK == result) {
    switch (req->posHoldOnOff) {
    case ON:
       lat    = ((tDouble)req->lat_val) / SCALING_LAT_LON;
       lon    = ((tDouble)req->lon_val) / SCALING_LAT_LON;
       height = ((tDouble)req->height)  / SCALING_HEIGHT;

       gnss_pps_set_position_hold_llh_pos(lat, lon, height);
       gnss_pps_set_position_hold_status(req->posHoldOnOff);
       break;

     case OFF:
       gnss_pps_set_position_hold_status(req->posHoldOnOff);
       break;

     default:
       result=STBIN_FAILED;
       break;
    }
	}

	return result;
}

static stbin_status_t stbin_exec_pps_if_auto_hold_samples_cmd(tU16 length, tUChar *msg, const stbin_req_msg_parms *parms_in)
{
	stbin_status_t result = STBIN_OK;

	stbin_exec_pps_if_auto_hold_samples_write_req_MAP(req, msg, length, &result);

  if(STBIN_OK == result) {
		gnss_pps_set_auto_hold_samples(req->nbSamples);
	}

	return result;
}
//len = 3 onoff (1byte) +  alarm(2 byte)
static stbin_status_t stbin_exec_pps_if_traim_cmd(tU16 length, tUChar *msg, const stbin_req_msg_parms *parms_in)
{
	tDouble alarm;
	stbin_status_t result = STBIN_OK;

	stbin_exec_pps_if_traim_data_write_req_MAP(req, msg, length, &result);

  if(STBIN_OK == result) {
		switch (req->enabled)	{
		case ON:
			alarm =  ((tDouble)req->alarm) * (1E-9);
			gnss_pps_enable_traim(alarm);
		break;

		case OFF:
			gnss_pps_disable_traim();
	    break;

		default:
			result = STBIN_FAILED;
		break;
		}
	}

	return result;
}


#ifdef STBIN_SQI_DATASTORAGE
//Len = 1 paylod =0x00 else ecu send nack.
static stbin_status_t stbin_exec_sqi_data_erase(tU16 len, tUChar *msg, const stbin_req_msg_parms *parms_in)
{
	stbin_status_t result = STBIN_OK;
	tU32 dest_addr = SQI_START_ADDR + SQI_USER_REGION_OFFSET;
	tU8 spm_conf;
  gpOS_error_t error;

	stbin_exec_sqi_data_erase_MAP(req, msg, len, &result);

	if(result==STBIN_OK)
	{
    // Check if Software Protection Mode is enabled
    error = svc_sqi_get_sw_protection( &spm_conf);

    if(( error == gpOS_SUCCESS) && ( spm_conf != 0))
    {
      svc_sqi_set_sw_protection( 0);
    }

		if ( svc_sqi_erase( (void *)dest_addr, 8, FALSE) != gpOS_SUCCESS)
		{
			result = STBIN_FAILED;
		}

		// Check if Software Protection Mode is enabled
    if( spm_conf)
    {
      svc_sqi_set_sw_protection( spm_conf);
    }
	}
	return result;
}

/*
static tUInt stbin_dec_return_U32(tUChar *msg, tInt start_index, tInt stop_index)
{
	tDouble value = ERROR;
    tUInt val_u32=0;

    val_u32 = val_u32|((((tUInt)msg[start_index])<<24)& 0xFF000000);
    val_u32 = val_u32|((((tUInt)msg[start_index+VAL_ONE])<<16)& 0xFF0000);
    val_u32 = val_u32|((((tUInt)msg[stop_index-VAL_ONE])<<8)& 0xFF00);
    val_u32 = val_u32|((((tUInt)msg[stop_index]))& 0xFF);
	return value;
}
  */

//len = LEN_SQI_DATA_SET (9x4)
static stbin_status_t stbin_exec_sqi_data_set(tU16 len, tUChar *msg, const stbin_req_msg_parms *parms_in)
{
	stbin_status_t result = STBIN_OK;
	tU32 cnt;
	tU32 data[8];
	tU32 *data_buffer_ptr = (tU32 *)stbin_sqi_databuf;
	tU32 dest_addr;
  frame_qualifier_t        frameQ;
  tU8 spm_conf;
  gpOS_error_t error;

  PREPARE_OUTPUT_MESSAGE(parms_in->out_buf, sqi_data_set_t, rsp, rspSize);

  stbin_exec_sqi_data_set_MAP(req, msg, len, &result);

	if(result==STBIN_OK)
	{
		dest_addr = SQI_START_ADDR + SQI_USER_REGION_OFFSET + req->offset; //sector_start_addr + offset;

		data[0] = req->word1;
		data[1] = req->word2;
		data[2] = req->word3;
		data[3] = req->word4;
		data[4] = req->word5;
		data[5] = req->word6;
		data[6] = req->word7;
		data[7] = req->word8;


    for( cnt = 0; cnt < (stbin_sqi_databuf_size / 4); cnt++)
    {
      data_buffer_ptr[cnt] = data[cnt];
    }

    // Check if Software Protection Mode is enabled
    error = svc_sqi_get_sw_protection( &spm_conf);

    if(( error == gpOS_SUCCESS) && ( spm_conf != 0))
    {
      svc_sqi_set_sw_protection( 0);
    }

    if ( svc_sqi_write( (void *)dest_addr, (void *)data_buffer_ptr, stbin_sqi_databuf_size) == gpOS_FAILURE)
    {
      result = STBIN_FAILED;
    }

    // Check if Software Protection Mode is enabled
    if( spm_conf)
    {
      svc_sqi_set_sw_protection( spm_conf);
    }

    rsp->dest_addr = dest_addr;

    frameQ = frame_ack_qualifier(parms_in->class_Id, parms_in->msg_Id, rspSize, ONLY_ONE_FRAME);
    sqi_data_set_send(rsp, frameQ);
	}

	return result;
}

//len = 0x01
static stbin_status_t stbin_exec_sqi_data_get(tU16 length, tUChar *msg, const stbin_req_msg_parms *parms_in)
{
	tU32 dest_addr;
	stbin_status_t result = STBIN_OK;
	frame_qualifier_t        frameQ;

  PREPARE_OUTPUT_MESSAGE(parms_in->out_buf, sqi_data_get_t, rsp, rspSize);

	stbin_exec_sqi_data_get_MAP(req, msg, length, &result);

	if(result==STBIN_OK)
	{
    dest_addr = SQI_START_ADDR + SQI_USER_REGION_OFFSET + req->offset;

    rsp->dest_addr = dest_addr;
    rsp->word1=((tU32 *)dest_addr)[0];
    rsp->word2=((tU32 *)dest_addr)[1];
    rsp->word3=((tU32 *)dest_addr)[2];
    rsp->word4=((tU32 *)dest_addr)[3];
    rsp->word5=((tU32 *)dest_addr)[4];
    rsp->word6=((tU32 *)dest_addr)[5];
    rsp->word7=((tU32 *)dest_addr)[6];
    rsp->word8=((tU32 *)dest_addr)[7];

    frameQ = frame_ack_qualifier(parms_in->class_Id, parms_in->msg_Id, rspSize, ONLY_ONE_FRAME);
    sqi_data_get_send(rsp, frameQ);
	}

	return result;
}
#endif


static stbin_status_t stbin_exec_dump_ephems(tU16 length, tUChar *msg, const stbin_req_msg_parms *parms_in)
{
	stbin_status_t   result               = STBIN_OK;
  gnss_sat_type_mask_t     const_mask_supported = 0;
  tInt                      sat, nb_frame, nb_frame_sent;
  frame_status_t           frame_seq;
  frame_qualifier_t        frameQ;
  PREPARE_OUTPUT_MESSAGE(parms_in->out_buf, dumpEphe_t, EphemerisDump, rspSize);

	stbin_exec_dump_ephems_MAP(Input_param, msg, length, &result);

  nb_frame       = 0;
  nb_frame_sent  = 0;

  if(STBIN_OK == result)
  {
    //Set of const_mask_supported with input information
    switch(Input_param->Constellation)
    {
      case 0:
        const_mask_supported = gnss_get_constellation_mask();
        break;
      case 1:
        MCR_SETBIT(const_mask_supported, GNSS_SAT_TYPE_GPS);
        break;
      case 2:
        MCR_SETBIT(const_mask_supported, GNSS_SAT_TYPE_GLONASS);
        break;
      case 3:
        MCR_SETBIT(const_mask_supported, GNSS_SAT_TYPE_QZSS_L1_CA);
        break;
      default:
        break;
    }

    if( MCR_ISBITSET( const_mask_supported, GNSS_SAT_TYPE_GPS))
    {
      for (sat = MIN_GPS_SAT_ID; sat <= MAX_GPS_SAT_ID ; sat++)
      {
        Send_Ephemeris(sat, &nb_frame, &nb_frame_sent, parms_in);
      }
    }

    if( MCR_ISBITSET( const_mask_supported, GNSS_SAT_TYPE_GLONASS))
    {
      for (sat = MIN_GLONASS_SAT_ID; sat <= MAX_GLONASS_SAT_ID ; sat++)
      {
        Send_Ephemeris(sat, &nb_frame, &nb_frame_sent, parms_in);
      }
    }

    if( MCR_ISBITSET( const_mask_supported, GNSS_SAT_TYPE_QZSS_L1_CA))
    {
      for (sat = MIN_QZSS_L1_CA_SAT_ID; sat <= MAX_QZSS_L1_CA_SAT_ID ; sat++)
      {
        Send_Ephemeris(sat, &nb_frame, &nb_frame_sent, parms_in);
      }
    }

    if (0 != nb_frame)
    {
      // Send of last frame present in buffer
      //Ckeck if only one frame to send
      frame_seq = (1 == nb_frame) ? ONLY_ONE_FRAME : END_OF_SEVERAL_FRAMES;
      frameQ = frame_ack_qualifier(parms_in->class_Id, parms_in->msg_Id, rspSize, frame_seq);
      dumpEphe_send(EphemerisDump, frameQ );
    }
    else
    {
      // Nothing to send. Just Ack
      Send_ACKorNACK(ACK, parms_in);
    }
  }

	return result;
}
/*}}}  */

// When an eph must be repported by this function, it sends the content of output buffer befor refilling it
static void Send_Ephemeris(tInt satId, tInt* num_frame, tInt* num_frame_sent, const stbin_req_msg_parms *parms_in)
{
  ephemeris_raw_t          ephemeris;
  tU8*           ephepointer   = (tU8*)  (&ephemeris);
  boolean_t                eph_available = FALSE;
  tInt                      i;
  frame_status_t           frame_seq;
  frame_qualifier_t frameQ;
  PREPARE_OUTPUT_MESSAGE(parms_in->out_buf, dumpEphe_t, EphemerisDump, rspSize);

  if (GNSS_NO_ERROR == gnss_get_ephemeris_params(satId, &ephemeris, &eph_available))
  {
    if( eph_available == TRUE)
    {
      // Sth to send. Send data already present in output buffer, if any
      if(*num_frame_sent == (*num_frame - 1))
      {
        frame_seq = (0 == *num_frame_sent) ? START_OF_SEVERAL_FRAMES : MIDDLE_OF_SEVERAL_FRAMES;
        frameQ = frame_ack_qualifier(parms_in->class_Id, parms_in->msg_Id, rspSize, frame_seq);
        dumpEphe_send(EphemerisDump, frameQ );

        (*num_frame_sent)++;
      }
      // Here output buffer is free, fill it for next frame.
      EphemerisDump->dsp_satid = (tU8)satId;
      for(i=(sizeof(ephemeris_raw_t) - 1U); i >= 0 ; i--)
      {
        EphemerisDump->value[i] = ephepointer[i];
      }
      (*num_frame)++;
    }
  }
}

static stbin_status_t stbin_exec_dump_almanacs(tU16 length, tUChar *msg, const stbin_req_msg_parms *parms_in)
{
	stbin_status_t   result               = STBIN_OK;
  gnss_sat_type_mask_t     const_mask_supported = 0;
  tInt                      sat, nb_frame, nb_frame_sent;
  frame_status_t           frame_seq;
  frame_qualifier_t        frameQ;
  PREPARE_OUTPUT_MESSAGE(parms_in->out_buf, dumpAlmans_t, AlmanacsDump, rspSize);


	stbin_exec_dump_almans_MAP(Input_param, msg, length, &result);

  nb_frame       = 0;
  nb_frame_sent  = 0;

  if(STBIN_OK == result)
  {
    //Set of const_mask_supported with input information
    switch(Input_param->Constellation)
    {
      case 0:
        const_mask_supported = gnss_get_constellation_mask();
        break;
      case 1:
        MCR_SETBIT(const_mask_supported, GNSS_SAT_TYPE_GPS);
        break;
      case 2:
        MCR_SETBIT(const_mask_supported, GNSS_SAT_TYPE_GLONASS);
        break;
      case 3:
        MCR_SETBIT(const_mask_supported, GNSS_SAT_TYPE_QZSS_L1_CA);
        break;
      default:
        break;
    }


    if( MCR_ISBITSET( const_mask_supported, GNSS_SAT_TYPE_GPS))
    {
      for (sat = MIN_GPS_SAT_ID; sat <= MAX_GPS_SAT_ID ; sat++)
      {
        Send_Almanacs(sat, &nb_frame, &nb_frame_sent, parms_in);
      }
    }

    if( MCR_ISBITSET( const_mask_supported, GNSS_SAT_TYPE_GLONASS))
    {
      for (sat = MIN_GLONASS_SAT_ID; sat <= MAX_GLONASS_SAT_ID ; sat++)
      {
        Send_Almanacs(sat, &nb_frame, &nb_frame_sent, parms_in);
      }
    }

    if( MCR_ISBITSET( const_mask_supported, GNSS_SAT_TYPE_QZSS_L1_CA))
    {
      for (sat = MIN_QZSS_L1_CA_SAT_ID; sat <= MAX_QZSS_L1_CA_SAT_ID ; sat++)
      {
        Send_Almanacs(sat, &nb_frame, &nb_frame_sent, parms_in);
      }
    }

    if (0 != nb_frame)
    {
      // Send of last frame
      //Ckeck if only one frame to send
      frame_seq = (1 == nb_frame) ? ONLY_ONE_FRAME : END_OF_SEVERAL_FRAMES;
      frameQ = frame_ack_qualifier(parms_in->class_Id, parms_in->msg_Id, rspSize, frame_seq);
      dumpAlmans_send(AlmanacsDump, frameQ );
    }
    else
    {
      // Nothing to send. Just Ack
      Send_ACKorNACK(ACK, parms_in);
    }
  }

	return result;
}
/*}}}  */

static void Send_Almanacs(tInt satId, tInt* num_frame, tInt* num_frame_sent, const stbin_req_msg_parms *parms_in)
{
  almanac_raw_t            almanac;
  tU8*           almanspointer = (tU8*)  (&almanac);
  boolean_t                alm_available = FALSE;
  tInt                      i;
  frame_status_t           frame_seq;
  frame_qualifier_t        frameQ;
  PREPARE_OUTPUT_MESSAGE(parms_in->out_buf, dumpAlmans_t, AlmanacsDump, rspSize);

  if (GNSS_NO_ERROR == gnss_get_almanac_params(satId, &almanac, &alm_available))
  {
    GPS_DEBUG_MSG(("STBIN - get ephemeris ok\r\n"));
    if( alm_available == TRUE)
    {
      if(*num_frame_sent == (*num_frame - 1))
      {
        frame_seq = (0 == *num_frame_sent) ? START_OF_SEVERAL_FRAMES : MIDDLE_OF_SEVERAL_FRAMES;
        frameQ = frame_ack_qualifier(parms_in->class_Id, parms_in->msg_Id, rspSize, frame_seq);
        dumpAlmans_send(AlmanacsDump, frameQ );

        (*num_frame_sent)++;
      }
      AlmanacsDump->dsp_satid = (tU8)satId;
      for(i=(sizeof(almanac_raw_t) - 1U); i >= 0 ; i--)
      {
        AlmanacsDump->value[i] = almanspointer[i];
      }
      (*num_frame)++;
    }
  }
}


static stbin_status_t stbin_exec_get_rtc_time(tU16 length, tUChar *msg, const stbin_req_msg_parms *parms_in)
{
  gnss_time_t            gnss_time;
  gpOS_clock_t           cpu_time;
  rtc_status_t           rtc_status;
  time_validity_t        time_validity;
  tInt                    year, month, day, hours, mins, secs, msecs;
  stbin_status_t result = STBIN_OK;
  frame_qualifier_t        frameQ;
  PREPARE_OUTPUT_MESSAGE(parms_in->out_buf, read_rtc_time_t, rsp, rspSize);

  stbin_exec_read_rtc_time_MAP(Input_param, msg, length, &result);

 	if(STBIN_OK == result)
  {
    gnss_rtc_get_time( &gnss_time, &cpu_time, &rtc_status, &time_validity );
    gnss_get_utc_time( gnss_time.tow, &hours, &mins, &secs, &msecs );
    gnss_get_date( gnss_time.week_n, gnss_time.tow, &year, &month, &day );

	  rsp->year       = (tUShort)year;
	  rsp->month      = (tUChar)month;
	  rsp->day        = (tUChar)day;
	  rsp->hour       = (tUChar)hours;
	  rsp->min        = (tUChar)mins;
	  rsp->sec        = (tUChar)secs;
	  rsp->millisec   = (tUChar)msecs;
	  rsp->time_valid = (tUChar)time_validity;
	  rsp->rtc_status = (tUChar)rtc_status;

    frameQ = frame_ack_qualifier(parms_in->class_Id, parms_in->msg_Id, rspSize, ONLY_ONE_FRAME);
    read_rtc_time_send(rsp, frameQ );
  }

  return result;
}

static stbin_status_t stbin_exec_get_sw_ver(tU16 length, tUChar *msg, const stbin_req_msg_parms *parms_in)
{
  stbin_status_t result = STBIN_OK;
  frame_qualifier_t        frameQ;
  tInt                  index, gnssapp_plugins_used=0;
  gnssapp_plugins_id_t gnssapp_plugins_name=GNSSAPP_PLUGINS_ID_WAAS;     //Initialization to avoid a compilation warning

  PREPARE_OUTPUT_MESSAGE(parms_in->out_buf, getSwVers_t, rsp, rspSize);

  stbin_exec_get_sw_ver_MAP(Input_param, msg, length, &result);

 	if(STBIN_OK == result)
  {
	    //init string sw version:
    for(index=STBIN_LEN_STRING-1; index>=0; index--)
    {
      rsp->swVersID[index]=0x00;
    }

  	switch (Input_param->control)
    {
    	case 0:
        /*Load struct*/
				_clibs_strcpy(rsp->swVersID, gnss_version());
        break;

		  case 1:
        /*Load struct*/
				_clibs_strcpy(rsp->swVersID, gpOS_version());
        break;

      case 2:
        /*Load struct*/
				_clibs_strcpy(rsp->swVersID, gnssapp_version());
        break;

#if !defined(__linux__) && !defined(_WIN32_WCE)
      case 3:
      	/*Load struct*/
				_clibs_strcpy(rsp->swVersID, svc_version());
        break;
#endif

      case 4:
      	gnssapp_plugins_name = GNSSAPP_PLUGINS_ID_WAAS;
      	gnssapp_plugins_used = 1;
      	break;

#if defined( STBIN_BINIMG_SUPPORT )
      case 6:
        /*Load struct*/
				_clibs_strcpy(rsp->swVersID, gnssapp_binimg_version());
        break;
#endif

      case 7:
        /*Load struct*/
				index = _clibs_sprintf(rsp->swVersID, "%s_%08x", svc_mcu_getprodname(), svc_mcu_getromver());
        break;

      case 8:
      	gnssapp_plugins_name = GNSSAPP_PLUGINS_ID_STAGPS;
      	gnssapp_plugins_used = 1;
      	break;

      case 9:
      	gnssapp_plugins_name = GNSSAPP_PLUGINS_ID_RTCM;
      	gnssapp_plugins_used = 1;
      	break;

      case 10:
      	gnssapp_plugins_name = GNSSAPP_PLUGINS_ID_DR;
      	gnssapp_plugins_used = 1;
      	break;

      case 11:
        index = _clibs_sprintf(rsp->swVersID, "SWCFG_%08x",gnssapp_swcfg_version());
        break;

      default:
      /* Should never go there */
        break;
    }

    if (gnssapp_plugins_used == 1)
    {
      const tChar *ver_ptr = NULL;
      gnssapp_plugins_cmd_param_t gpparam;
      gpparam.data_ptr = (void *)&ver_ptr;
      gnssapp_plugins_cmd( gnssapp_plugins_name, GNSSAPP_PLUGINS_CMD_GETVER, &gpparam);

      if(ver_ptr != NULL)
      {
        _clibs_strcpy(rsp->swVersID, ver_ptr);
      }
    }
    if(rsp->swVersID[0] != (tChar)0x00)
    {
      frameQ = frame_ack_qualifier(parms_in->class_Id, parms_in->msg_Id, rspSize, ONLY_ONE_FRAME);
      getSwVers_send(rsp, frameQ );
    }
    else
    {
      result = STBIN_FAILED;
    }
  }

  return result;
}


static stbin_status_t stbin_exec_get_all_sw_ver(tU16 length, tUChar *msg, const stbin_req_msg_parms *parms_in)
{
  stbin_status_t result = STBIN_OK;
  frame_qualifier_t frameQ;
  tInt index;
  frame_status_t  frame_seq = START_OF_SEVERAL_FRAMES;
  tU8 mul_idx = 0;

  PREPARE_OUTPUT_MESSAGE(parms_in->out_buf, getAllSwVers_t, rsp, rspSize);

  stbin_exec_get_all_sw_ver_MAP(Input_param, msg, length, &result);

 	if(STBIN_OK == result)
  {
	    //init string sw version:
    for(index=STBIN_LEN_STRING-1; index>=0; index--)
    {
      rsp->SWID[index]=0x00;
    }

      rsp->idx = mul_idx++;
      _clibs_strcpy(rsp->SWID, gnss_version());
      frameQ = frame_ack_qualifier(parms_in->class_Id, parms_in->msg_Id, rspSize, frame_seq);
      getAllSwVers_send(rsp, frameQ );

      for(index=STBIN_LEN_STRING-1; index>=0; index--)
      {
        rsp->SWID[index]=0x00;
      }

      rsp->idx = mul_idx++;
      _clibs_strcpy(rsp->SWID, gpOS_version());

      frame_seq = MIDDLE_OF_SEVERAL_FRAMES;
      frameQ = frame_ack_qualifier(parms_in->class_Id, parms_in->msg_Id, rspSize, frame_seq);
      getAllSwVers_send(rsp, frameQ );

      for(index=STBIN_LEN_STRING-1; index>=0; index--)
      {
        rsp->SWID[index]=0x00;
      }

      rsp->idx = mul_idx++;
      _clibs_strcpy(rsp->SWID, gnssapp_version());
      frameQ = frame_ack_qualifier(parms_in->class_Id, parms_in->msg_Id, rspSize, frame_seq);
      getAllSwVers_send(rsp, frameQ );

      for(index=STBIN_LEN_STRING-1; index>=0; index--)
      {
        rsp->SWID[index]=0x00;
      }

#if defined( STBIN_BINIMG_SUPPORT )
      rsp->idx = mul_idx++;
			_clibs_strcpy(rsp->SWID, gnssapp_binimg_version());
			frameQ = frame_ack_qualifier(parms_in->class_Id, parms_in->msg_Id, rspSize, frame_seq);
      getAllSwVers_send(rsp, frameQ );

      for(index=STBIN_LEN_STRING-1; index>=0; index--)
      {
        rsp->SWID[index]=0x00;
      }

#endif
       rsp->idx = mul_idx++;
       _clibs_sprintf(rsp->SWID, "SWCFG_%08x",gnssapp_swcfg_version());
       frameQ = frame_ack_qualifier(parms_in->class_Id, parms_in->msg_Id, rspSize, frame_seq);
      getAllSwVers_send(rsp, frameQ );

      rsp->idx = mul_idx++;
      _clibs_sprintf(rsp->SWID, "%s_%08x", svc_mcu_getprodname(), svc_mcu_getromver());
      frameQ = frame_ack_qualifier(parms_in->class_Id, parms_in->msg_Id, rspSize, frame_seq);
      getAllSwVers_send(rsp, frameQ );

#if !defined(__linux__) && !defined(_WIN32_WCE)
      for(index=STBIN_LEN_STRING-1; index>=0; index--)
      {
        rsp->SWID[index]=0x00;
      }
      rsp->idx = mul_idx++;
			_clibs_strcpy(rsp->SWID, svc_version());
			frameQ = frame_ack_qualifier(parms_in->class_Id, parms_in->msg_Id, rspSize, frame_seq);
      getAllSwVers_send(rsp, frameQ );

#endif


      {
        tInt id;

        for ( id = 0; id < GNSSAPP_PLUGINS_NUMBER; id++ )
        {
          const tChar *ver_ptr = NULL;
          gnssapp_plugins_cmd_param_t gpparam;
          gpparam.data_ptr = ( void * )&ver_ptr;
          gnssapp_plugins_cmd( ( gnssapp_plugins_id_t )id, GNSSAPP_PLUGINS_CMD_GETVER, &gpparam );

          if ( ver_ptr != NULL )
          {
            rsp->idx = mul_idx++;
            _clibs_strcpy(rsp->SWID, ver_ptr);
            frame_seq = ((GNSSAPP_PLUGINS_NUMBER -1) == id) ? END_OF_SEVERAL_FRAMES : MIDDLE_OF_SEVERAL_FRAMES;
            frameQ = frame_ack_qualifier(parms_in->class_Id, parms_in->msg_Id, rspSize, frame_seq);
            getAllSwVers_send(rsp, frameQ );
          }

          for(index=STBIN_LEN_STRING-1; index>=0; index--)
          {
            rsp->SWID[index]=0x00;
          }
        }
      }
  }

return result;
}

static stbin_status_t stbin_exec_get_algo_status(tU16 length, tUChar *msg, const stbin_req_msg_parms *parms_in)
{
  stbin_status_t result = STBIN_OK;
  frame_qualifier_t        frameQ;
  PREPARE_OUTPUT_MESSAGE(parms_in->out_buf, get_algo_status_t, rsp, rspSize);

  stbin_exec_get_algo_status_MAP(Input_param, msg, length, &result);

	if(STBIN_OK == result)
	{
		switch(Input_param->control)
		{
		case 0: /*FDA*///Not performed
			break;
		case 1:/*FDE*/
			rsp->algo_type = Input_param->control;
			rsp->algo_status = (tU8)gnss_get_fde_status();
			break;
		case 2:/*ADS*/ //Not performed
			break;
		default:
		/* Should never go there */
			break;
		}

    frameQ = frame_ack_qualifier(parms_in->class_Id, parms_in->msg_Id, rspSize, ONLY_ONE_FRAME);
    get_algo_status_send(rsp, frameQ );
	}

  return result;
}

//len = 0x01 payload null. the payload is defined between the "(" payload fields ")".
//the single field is terminated with the ";" = 0x3B
static stbin_status_t stbin_exec_check_task(tU16 length, tUChar *msg, const stbin_req_msg_parms *parms_in)
{
  stbin_status_t result = STBIN_OK;
  #ifndef _WIN32_WCE
  #ifndef __linux__
  frame_status_t           frame_seq;
  frame_qualifier_t frameQ;
  PREPARE_OUTPUT_MESSAGE(parms_in->out_buf, checkTask_t, CheckTaskStruct, rspSize);

	gpOS_task_t*      task;
	tUInt size;
	tUInt used;
	tInt          index;
	tInt          index_response;

  stbin_exec_check_task_MAP(Input_param, msg, length, &result);

	if(STBIN_OK == result)
	{
		task = gpOS_task_get_head();//returns a pointer to the task structure of the first created task

		index_response=0;
		while( task != NULL)
    {
		  /* determine stack unused */
		  used = (tUInt)gpOS_task_get_stack_used(task);
		  size = (tUInt)gpOS_task_get_stack_size(task);



		  for(index=STBIN_LEN_STRING-1; index >=0 ; index--)
		  {
			  CheckTaskStruct->taskIdStr[index]=0x00;
		  }
		  /*Load struct*/
		  _clibs_strcpy(CheckTaskStruct->taskIdStr, gpOS_task_get_name(task));

		  CheckTaskStruct->task_get_priority   = gpOS_task_get_priority(task);
		  CheckTaskStruct->task_get_stack_base = (tUInt)gpOS_task_get_stack_base(task);
		  CheckTaskStruct->task_get_stack_ptr  = (tUInt)gpOS_task_get_stack_ptr(task);
		  CheckTaskStruct->size                = size;
		  CheckTaskStruct->used                = used;

		  task = gpOS_task_get_next( task); //gpOS_task_get_next() returns the pointer to the task structure of the next task of task task.
		  if(NULL == task )
		  {
		      frame_seq =  END_OF_SEVERAL_FRAMES;
		  }
		  else
		  {
		    if (0 == index_response)
		    {
		      frame_seq = START_OF_SEVERAL_FRAMES;
		    }
		    else
		    {
		      frame_seq = MIDDLE_OF_SEVERAL_FRAMES;
		    }
		  }

      /*Send Data on the serial port */
      frameQ = frame_ack_qualifier(parms_in->class_Id, parms_in->msg_Id, rspSize, frame_seq);
      checkTask_send(CheckTaskStruct, frameQ );

		  index_response++;
    }
	}
  #endif
  #endif
  return result;
}

//idem stbin_exec_check_task(tU16 length, tChar *msg)
static stbin_status_t stbin_exec_check_cpu_usage(tU16 length, tUChar *msg, const stbin_req_msg_parms *parms_in)
{
  stbin_status_t result = STBIN_OK;
  frame_status_t    frame_seq;
  frame_qualifier_t frameQ;
  PREPARE_OUTPUT_MESSAGE(parms_in->out_buf, checkCpuUsage_t, checkCpuUsage, rspSize);

	gpOS_task_t*          curr_task;
	tUInt     total_cpu_usage = 0;
	tInt              index, responseID;

	tChar EndMsg_Id[] = "Interrupts";

  stbin_exec_check_cpu_usage_MAP(Input_param, msg, length, &result);

	if(STBIN_OK == result)
	{
    responseID = 0;

    gpOS_task_lock();
	  curr_task = gpOS_task_get_head();

    while(curr_task != NULL)
    {
      tUInt curr_task_cpu_usage = (tUInt)gpOS_task_get_cpuusage(curr_task);

	     /*String initialize*/
      for(index = STBIN_LEN_STRING-1; index >=0; index--)
      {
        checkCpuUsage->taskNameId[index]=0x00;
		  }
		  checkCpuUsage->cpuUsage_CurrentTask=0;
      /*Load struct*/
		  _clibs_strcpy(checkCpuUsage->taskNameId, gpOS_task_get_name(curr_task));
		  //checkCpuUsage.cpuUsage_CurrentTask = ((tFloat)curr_task_cpu_usage)/100.0;da inserire in host codifica
		  checkCpuUsage->cpuUsage_CurrentTask =  curr_task_cpu_usage;

      /*Send Data on the serial port */
      frame_seq = (0 != responseID) ? MIDDLE_OF_SEVERAL_FRAMES : START_OF_SEVERAL_FRAMES;
      frameQ = frame_ack_qualifier(parms_in->class_Id, parms_in->msg_Id, rspSize, frame_seq);
      checkCpuUsage_send(checkCpuUsage, frameQ );

      total_cpu_usage += curr_task_cpu_usage;
      curr_task = gpOS_task_get_next(curr_task);
      responseID++;
    }

	  //init struct
	  for(index = STBIN_LEN_STRING-1; index >=0; index--)
	  {
		  checkCpuUsage->taskNameId[index]=0x00;
	  }
	  checkCpuUsage->cpuUsage_CurrentTask=0;
    /*Load struct*/
	  _clibs_strcpy(checkCpuUsage->taskNameId, EndMsg_Id);
	  checkCpuUsage->cpuUsage_CurrentTask = (10000U-total_cpu_usage);

	  /*Send Data on the serial port - Send last message */
    frameQ = frame_ack_qualifier(parms_in->class_Id, parms_in->msg_Id, rspSize, END_OF_SEVERAL_FRAMES);
    checkCpuUsage_send(checkCpuUsage, frameQ );

	  gpOS_task_unlock();
	}

  return result;
}

static stbin_status_t stbin_exec_check_heap(tU16 length, tUChar *msg, const stbin_req_msg_parms *parms_in)
{
  stbin_status_t result = STBIN_OK;
  #ifndef _WIN32_EMU
  #ifndef _WIN32_WCE
  #ifndef __linux__
  frame_status_t    frame_seq;
  frame_qualifier_t frameQ;
  PREPARE_OUTPUT_MESSAGE(parms_in->out_buf, check_heap_t, CheckHeap, rspSize);

	gpOS_partition_t* next_part = NULL;
	tInt responseID;

  stbin_exec_check_heap_MAP(Input_param, msg, length, &result);

	if(STBIN_OK == result)
	{
		responseID=0;

		CheckHeap->memory_getheapfree = gpOS_memory_getheapfree();
		CheckHeap->memory_getheapsize = gpOS_memory_getheapsize();

		responseID++;

		do
		{
			next_part = gpOS_memory_getnextpartition(next_part);
			if (next_part != NULL)
			{
        frame_seq = (1 == responseID) ? START_OF_SEVERAL_FRAMES : MIDDLE_OF_SEVERAL_FRAMES;
        frameQ = frame_ack_qualifier(parms_in->class_Id, parms_in->msg_Id, rspSize, frame_seq);
        check_heap_send(CheckHeap, frameQ );

				CheckHeap->memory_getheapsize  = gpOS_memory_getheapsize_p(next_part);
				CheckHeap->memory_getheapfree  = gpOS_memory_getheapfree_p(next_part); //da cambiare in attesa di risposta fulvio
				responseID++;
			}
			else
			{
        frame_seq = (1 == responseID) ? ONLY_ONE_FRAME : END_OF_SEVERAL_FRAMES;
        frameQ = frame_ack_qualifier(parms_in->class_Id, parms_in->msg_Id, rspSize, frame_seq);
        check_heap_send(CheckHeap, frameQ );
			}
		}
		while (next_part != NULL);
	}

  #endif
  #endif
  #endif
  return result;
}


//len = 0x03 - msg[0]= config_TYPE - msg[1]=config_SECTION - msg[2]=config_param_id
static stbin_status_t stbin_exec_sw_config_get_par(tU16 length, tUChar *msg, const stbin_req_msg_parms *parms_in)
{
	stbin_status_t result = STBIN_OK;

  stbin_exec_sw_config_get_par_MAP(Input_param, msg, length, &result);

  if(STBIN_OK ==result)
  {
    result = STBIN_FAILED;
    if((0U == Input_param->SectionId))
    {
      if(STBIN_OK == stbin_exec_sw_config_get_all_par(Input_param->ConfigBlock,SW_CONFIG_SEC_1,SW_CONFIG_SEC_1_ITEMS, parms_in))
      {
        if(STBIN_OK == stbin_exec_sw_config_get_all_par(Input_param->ConfigBlock,SW_CONFIG_SEC_2,SW_CONFIG_SEC_2_ITEMS, parms_in))
        {
          if(STBIN_OK == stbin_exec_sw_config_get_all_par(Input_param->ConfigBlock,SW_CONFIG_SEC_3,SW_CONFIG_SEC_3_ITEMS, parms_in))
          {
            if(STBIN_OK == stbin_exec_sw_config_get_all_par(Input_param->ConfigBlock,SW_CONFIG_SEC_4,SW_CONFIG_SEC_4_ITEMS, parms_in))
            {
              result = stbin_exec_sw_config_get_all_par(Input_param->ConfigBlock,SW_CONFIG_SEC_5,SW_CONFIG_SEC_5_ITEMS, parms_in);
            }
          }
        }
      }
    }
    else
    {
      result = stbin_exec_sw_config_get_single_par(Input_param->ConfigBlock,
                                                  Input_param->SectionId,
                                                  Input_param->ParamId,
                                                  parms_in);
    }

  }

  if (STBIN_OK == result)
  {
    Send_ACKorNACK(ACK, parms_in);
  }

  return result;
}

static stbin_status_t
    stbin_exec_sw_config_get_all_par(tUChar config_type, tUChar config_section,
                                      tUChar max_items_in_section, const stbin_req_msg_parms *parms_in)
{
  stbin_status_t error = STBIN_OK;
	tInt i;

  if (max_items_in_section > 100U)
  {
    max_items_in_section = 100U;
  }
	for (i=0;i<(tInt)max_items_in_section;i++)
	{
		if (STBIN_OK == error)
		{
		  error = stbin_exec_sw_config_get_single_par(config_type,config_section,(tUChar)i, parms_in);
    }
	}
	return(error);
}

static stbin_status_t
        stbin_exec_sw_config_get_single_par(tUChar config_type, tUChar config_section,
                                            tUChar config_param_id, const stbin_req_msg_parms *parms_in)
{
  stbin_status_t error = STBIN_FAILED;
  frame_qualifier_t frameQ;

	switch (config_section)
  {
    case 1:
      {
        tChar value;
        if(sw_config_get_param(config_type,(100 + (tInt)config_param_id),&value) == GNSS_NO_ERROR)
        {
          PREPARE_OUTPUT_MESSAGE(parms_in->out_buf, sw_config_get_par_val_Char_t, Param_char_value, rspSize);

          Param_char_value->configType = config_type;
          Param_char_value->configSection = config_section;
          Param_char_value->configParamId = config_param_id;
          Param_char_value->value = value;

          frameQ = frame_ack_qualifier(STBIN_READ_CLASS_ID, STBIN_READ_SW_CONF_PAR_CHAR, rspSize, ONLY_ONE_FRAME);
          sw_config_get_par_val_Char_send(Param_char_value, frameQ );

          error = STBIN_OK;
        }
      }
		  break;

    case 2:
      {
        if ((config_param_id >= (tChar)2)&&(config_param_id <= (tChar)5))
        {
          tInt value;
          if(sw_config_get_param(config_type,(200 + (tInt)config_param_id),&value) == GNSS_NO_ERROR)
          {
            PREPARE_OUTPUT_MESSAGE(parms_in->out_buf, sw_config_get_par_val_Int_t, Param_int_value, rspSize);

            Param_int_value->configType = config_type;
            Param_int_value->configSection = config_section;
            Param_int_value->configParamId = config_param_id;
            Param_int_value->value = value;

            frameQ = frame_ack_qualifier(STBIN_READ_CLASS_ID, STBIN_READ_SW_CONF_PAR_INT, rspSize, ONLY_ONE_FRAME);
            sw_config_get_par_val_Int_send(Param_int_value, frameQ );

            error = STBIN_OK;
          }
        }
        else
        {
          tUInt value;
          if(sw_config_get_param(config_type,(200 + (tInt)config_param_id),&value) == GNSS_NO_ERROR)
          {
            PREPARE_OUTPUT_MESSAGE(parms_in->out_buf, sw_config_get_par_val_UInt_t, Param_uint_value, rspSize);

            Param_uint_value->configType = config_type;
            Param_uint_value->configSection = config_section;
            Param_uint_value->configParamId = config_param_id;
            Param_uint_value->value = value;

            frameQ = frame_ack_qualifier(STBIN_READ_CLASS_ID, STBIN_READ_SW_CONF_PAR_UINT, rspSize, ONLY_ONE_FRAME);
            sw_config_get_par_val_UInt_send(Param_uint_value, frameQ );

            error = STBIN_OK;
          }
        }
      }
		  break;
        case 3:
          {
            tDouble value;
            if(sw_config_get_param(config_type,(300 + (tInt)config_param_id),&value) == GNSS_NO_ERROR)
            {
              PREPARE_OUTPUT_MESSAGE(parms_in->out_buf, sw_config_get_par_val_Double_t, Param_double_value, rspSize);

              Param_double_value->configType = config_type;
              Param_double_value->configSection = config_section;
              Param_double_value->configParamId = config_param_id;
              Param_double_value->value = value;

              frameQ = frame_ack_qualifier(STBIN_READ_CLASS_ID, STBIN_READ_SW_CONF_PAR_DOUBLE, rspSize, ONLY_ONE_FRAME);
              sw_config_get_par_val_Double_send(Param_double_value, frameQ );

              error = STBIN_OK;
            }
          }
		      break;
        case 4:
          {
            sw_config_dops_t value;
            if(sw_config_get_param(config_type,(400 + (tInt)config_param_id),&value) == GNSS_NO_ERROR)
            {
              PREPARE_OUTPUT_MESSAGE(parms_in->out_buf, sw_config_get_par_val_Dops_t, Param_dops_value, rspSize);

              Param_dops_value->configType = config_type;
              Param_dops_value->configSection = config_section;
              Param_dops_value->configParamId = config_param_id;
              Param_dops_value->gdop = value.gdop;
              Param_dops_value->hdop = value.hdop;
              Param_dops_value->pdop = value.pdop;
              Param_dops_value->vdop = value.vdop;

              frameQ = frame_ack_qualifier(STBIN_READ_CLASS_ID, STBIN_READ_SW_CONF_PAR_DOP, rspSize, ONLY_ONE_FRAME);
              sw_config_get_par_val_Dops_send(Param_dops_value, frameQ );

              error = STBIN_OK;
            }
          }
		      break;
        case 5:
          {
            tInt index;
            tChar value[SW_CONFIG_TEXT_LENGTH];
            PREPARE_OUTPUT_MESSAGE(parms_in->out_buf, sw_config_get_par_val_String_t, Param_string_value, rspSize);

            for(index = SW_CONFIG_TEXT_LENGTH-1; index >=0; index--)
            {
              Param_string_value->value[index]=0x00;
            }

            if(sw_config_get_param(config_type,(500 + (tInt)config_param_id), (tChar*)(value)) == GNSS_NO_ERROR)
            {
              Param_string_value->configType = config_type;
              Param_string_value->configSection = config_section;
              Param_string_value->configParamId = config_param_id;
              _clibs_strcpy(Param_string_value->value, value);

              frameQ = frame_ack_qualifier(STBIN_READ_CLASS_ID, STBIN_READ_SW_CONF_PAR_STRING, rspSize, ONLY_ONE_FRAME);
              sw_config_get_par_val_String_send(Param_string_value, frameQ );

              error = STBIN_OK;
            }
          }
		  break;
#if defined( DR_CODE_LINKED )
    case 6:
      {
        tUInt value;
        if(sw_config_get_param(config_type,(600 + (tInt)config_param_id),&value) == GNSS_NO_ERROR)
        {
          PREPARE_OUTPUT_MESSAGE(parms_in->out_buf, sw_config_get_par_val_UInt_t, Param_uint_value, rspSize);

          Param_uint_value->configType = config_type;
          Param_uint_value->configSection = config_section;
          Param_uint_value->configParamId = config_param_id;
          Param_uint_value->value = value;

          frameQ = frame_ack_qualifier(STBIN_READ_CLASS_ID, STBIN_READ_SW_CONF_PAR_UINT, rspSize, ONLY_ONE_FRAME);
          sw_config_get_par_val_UInt_send(Param_uint_value, frameQ );

          error = STBIN_OK;
        }
      }
		  break;
#endif
    default:
    /* Should never go there */
      break;
	}
	return(error);
}

static stbin_status_t stbin_exec_write_datum_selection (tU16 length, tUChar *msg, const stbin_req_msg_parms *parms_in)
{
  stbin_status_t result = STBIN_OK;

  stbin_exec_write_datum_selection_MAP(Input_param, msg, length, &result);

	if(STBIN_OK == result)
	{
	  if(GNSS_NO_ERROR != datum_select((datum_code_t)Input_param->datum))
	  {
	    result = STBIN_FAILED;
	  }
    if(STBIN_OK == result)
    {
      if(GNSS_NO_ERROR != sw_config_set_param(DATUM_ID, &(Input_param->datum), 0))
	    {
        result = STBIN_FAILED;
      }
    }
  }
  return result;
}

static stbin_status_t stbin_exec_define_user_datum (tU16 length, tUChar *msg, const stbin_req_msg_parms *parms_in)
{
  stbin_status_t result = STBIN_OK;
  datum_local_to_WGS84_param_t user_datum;

  stbin_exec_define_datum_MAP(Input_param, msg, length, &result);

	if(STBIN_OK == result)
	{
    user_datum.delta_x = Input_param->d_x;
    user_datum.delta_y = Input_param->d_y;
    user_datum.delta_z = Input_param->d_z;
    user_datum.delta_a = Input_param->d_a;
    user_datum.delta_f = Input_param->d_f;

	  if(GNSS_ERROR == datum_set_by_user(user_datum))
	  {
	    result = STBIN_FAILED;
	  }
	}
	return result;
}

static stbin_status_t stbin_exec_read_datum_selection (tU16 length, tUChar *msg, const stbin_req_msg_parms *parms_in)
{
  stbin_status_t result = STBIN_OK;
  frame_qualifier_t frameQ;
  PREPARE_OUTPUT_MESSAGE(parms_in->out_buf, read_datum_selection_t, rsp, rspSize);

  stbin_exec_read_datum_selection_MAP(Input_param, msg, length, &result);

	if(STBIN_OK == result)
	{
	  rsp->datum = (tU8)datum_get_current_code();
    frameQ = frame_ack_qualifier(parms_in->class_Id, parms_in->msg_Id, rspSize, ONLY_ONE_FRAME);
	  read_datum_selection_send(rsp, frameQ );
  }

	return result;
}

static stbin_status_t stbin_exec_dump_fe(tU16 length, tUChar *msg, const stbin_req_msg_parms *parms_in)
{
  #if defined( STBIN_FRONTEND_SUPPORT )
	stbin_status_t result = STBIN_OK;
	FE_reg_item_t reg_table[STBIN_FE_NB_REG_MAX];
	tUChar *reg_ptr= (tUChar*)&reg_table;
  tUInt index;

  #if defined( STBIN_REMOTE_FRONTEND_SUPPORT )
  tUInt fe_regs_size;
  #endif

	frame_qualifier_t frameQ;
  PREPARE_OUTPUT_MESSAGE(parms_in->out_buf, stbin_exec_dump_fe_t, rsp, rspSize);

  stbin_exec_dump_fe_MAP(req, msg, length, &result);

	if(result==STBIN_OK)
	{
	  //Init
    for(index=0; index< sizeof(reg_table); index++)
    {
      rsp->value[index]=0;
    }

  #if defined( STBIN_REMOTE_FRONTEND_SUPPORT )
  fe_regs_size = sizeof( reg_table );

  if ( remote_fe_dump( reg_table, &fe_regs_size ) == GNSS_NO_ERROR )
  #else
	if( FE_dump_regs( reg_table) == LLD_NO_ERROR)
  #endif
		{
      for(index=0; index< sizeof(reg_table); index++)
		 {
        rsp->value[index]= reg_ptr[index];
		 }

      frameQ = frame_ack_qualifier(parms_in->class_Id, parms_in->msg_Id, rspSize, ONLY_ONE_FRAME);
      stbin_exec_dump_fe_send(rsp, frameQ );
	}
	else
	{
		result = STBIN_FAILED;
	}
	}
  #else
  stbin_status_t result = STBIN_FAILED;
  GPS_DEBUG_MSG(("STBIN ERROR- stbin_exec_dump_fe command not available\r\n"));
  #endif

	return result;
}

static stbin_status_t stbin_exec_read_sw_config_all_blocks(tU16 length, tUChar *msg, const stbin_req_msg_parms *parms_in)
{
  stbin_status_t result = STBIN_OK;
  frame_qualifier_t frameQ;
  PREPARE_OUTPUT_MESSAGE(parms_in->out_buf, read_sw_config_all_blocks_t, rsp, rspSize);

  stbin_exec_read_sw_config_all_blocks_MAP(req, msg, length, &result);

  if(result == STBIN_OK)
  {
    sw_config_t temp_sw_config;
    tU8 *ptr;
    tUInt i;

    // Init response value buffer
    for ( i = 0; i < (sizeof(read_sw_config_all_blocks_t) - sizeof(tChar) - sizeof(tShort)); i++ )
    {
      rsp->value[i]= 0;
    }

    if ( sw_config_data_block_copy( req->config_type, &temp_sw_config ) != GNSS_ERROR )
    {

      rsp->length = sizeof( sw_config_t );
      rsp->config_type = req->config_type;

      ptr = ( tU8 * )&temp_sw_config;

      for ( i = 0; i < sizeof( sw_config_t ); i++ )
      {
        rsp->value[i]=*ptr;
        ptr++;
      }

      frameQ = frame_ack_qualifier(parms_in->class_Id, parms_in->msg_Id, rspSize, ONLY_ONE_FRAME);
      read_sw_config_all_blocks_send(rsp, frameQ );
    }
    else
    {
      result = STBIN_FAILED;
    }
  }

  return result;
}

static stbin_status_t stbin_exec_get_diff_source(tU16 len, tUChar *msg, const stbin_req_msg_parms *parms)
{
	 stbin_status_t result=STBIN_OK;
	 frame_qualifier_t frameQ;

   PREPARE_OUTPUT_MESSAGE(parms->out_buf, get_diff_source_t, rsp, rspSize);

	 stbin_exec_get_diff_source_MAP(req,msg, len, &result);

	 if(result == STBIN_OK)
	 {
    gnss_diff_source_t diff_source;

    gnss_diff_get_source_type(&diff_source);//Returns always GNSS_NO_ERROR

    rsp->diff_source_selected = (tU8)diff_source;

    frameQ = frame_ack_qualifier(parms->class_Id, parms->msg_Id, rspSize, ONLY_ONE_FRAME);
    get_diff_source_send(rsp, frameQ);
	 }

	return result;
}

#if defined ( STBIN_ADC_SUPPORT )
static stbin_status_t stbin_exec_adc_read(tU16 len, tUChar *msg, const stbin_req_msg_parms *parms)
{
  stbin_status_t result=STBIN_OK;
  frame_qualifier_t frameQ;

  tU32 adc_data = 0;
  tU32 out_data[SVC_ADC_AVERG_MIN];
  tInt ain;
  tInt i;
  svc_adc_chan_cfg_t number_channels;

  PREPARE_OUTPUT_MESSAGE(parms->out_buf, adc_read_t, rsp, rspSize);

  stbin_exec_adc_read_MAP(req,msg,len,&result);

  if(result == STBIN_OK)
  {

    for (i = 0; i < SVC_ADC_AVERG_MIN; i++)
    {
      out_data[i] = 0;
    }

    if( stbin_ext_adctest_started )
    {
      number_channels = (svc_adc_chan_cfg_t) req->sel_line;
      ain = req->ain;

    if( ( ( number_channels == ADC_8CHAN_AVAILABLE ) && ( ain >= 0 ) && ( ain <= 7 ) )
           || ( ( number_channels == ADC_4CHAN_AVAILABLE ) && ( ( ain == 0 ) || ( ain == 2 ) || ( ain == 4 ) || ( ain == 6 ) ) )
           || ( ( number_channels == ADC_2CHAN_AVAILABLE ) && ( ( ain == 0 ) || ( ain == 4 ) ) )
           || ( ( number_channels == ADC_1CHAN_AVAILABLE ) && ( ain == 0 ) ) )
      {
        svc_adc_read(ain, SVC_ADC_AVERG_MIN, &adc_data, out_data);
        rsp->data_read = adc_data;
        rsp->ain = ain;
      }
      else
      {
        result = STBIN_FAILED;
        GPS_DEBUG_MSG(("STBIN adc read error: line mask and channel values mismatch \r\n"));
      }

    }
    else
    {
     result = STBIN_FAILED;
     GPS_DEBUG_MSG(("STBIN adc read error: adc not started before \r\n"));
    }
  }
  frameQ = frame_ack_qualifier(parms->class_Id, parms->msg_Id, rspSize, ONLY_ONE_FRAME);
  adc_read_send(rsp, frameQ);

	return result;
}
#endif

static stbin_status_t stbin_exec_pps_if_pulse_data_read(tU16 length, tUChar *msg, const stbin_req_msg_parms *parms)
{
  frame_qualifier_t frameQ;
  PREPARE_OUTPUT_MESSAGE(parms->out_buf, stbin_exec_pps_if_pulse_data_read_rsp_t, rsp, rspSize);
	stbin_status_t result = STBIN_OK;
  stbin_exec_pps_if_pulse_data_read_req_MAP(req, msg, length, &result);

  if(STBIN_OK != result)
  {
    return result;   /*lint !e904 Return statement before end of function */
  }

  rsp->outMode       = gnss_pps_get_signal_on_off_status();
  rsp->refTimeId     = gnss_pps_get_reference_time();
  rsp->pulseDelay    = (tShort)((gnss_pps_get_time_delay() * 1E9) + 0.5);  // ns
  rsp->pulsePolarity = gnss_pps_get_polarity();
  rsp->pulseDuration = (tU16)(gnss_pps_get_pulse_duration()*1000.0); // ms

  frameQ = frame_ack_qualifier(parms->class_Id, parms->msg_Id, rspSize, ONLY_ONE_FRAME);
  stbin_exec_pps_if_pulse_data_read_rsp_send(rsp, frameQ );

  return result;
}

static stbin_status_t stbin_exec_pps_if_timing_data_read(tU16 length, tUChar *msg, const stbin_req_msg_parms *parms)
{
  frame_qualifier_t frameQ;
  PREPARE_OUTPUT_MESSAGE(parms->out_buf, stbin_exec_pps_if_timing_data_read_rsp_t, rsp, rspSize);
	stbin_status_t result = STBIN_OK;
  stbin_exec_pps_if_timing_data_read_req_MAP(req, msg, length, &result);

  if(STBIN_OK != result)
  {
    return result;   /*lint !e904 Return statement before end of function */
  }

	rsp->fixCondition      = gnss_pps_get_fix_condition();
	rsp->satTh             = gnss_pps_get_sat_threshold();
	rsp->elevationMask     = gnss_pps_get_elevation_mask();
	rsp->constellationMask = gnss_pps_get_constellation_mask();
	rsp->gpsRfDelay        = (tShort)((gnss_pps_get_rf_compensation(GNSS_SAT_TYPE_GPS) * 1E9) + 0.5);
	rsp->glonassRfDelay    = (tShort)((gnss_pps_get_rf_compensation(GNSS_SAT_TYPE_GLONASS) * 1E9) + 0.5);

  frameQ = frame_ack_qualifier(parms->class_Id, parms->msg_Id, rspSize, ONLY_ONE_FRAME);
  stbin_exec_pps_if_timing_data_read_rsp_send(rsp, frameQ );

  return result;
}

static stbin_status_t stbin_exec_pps_if_pos_hold_data_read(tU16 length, tUChar *msg, const stbin_req_msg_parms *parms)
{
  frame_qualifier_t frameQ;
  PREPARE_OUTPUT_MESSAGE(parms->out_buf, stbin_exec_pps_if_pos_hold_data_read_rsp_t, rsp, rspSize);
	tDouble lat, lon, height;
	stbin_status_t result = STBIN_OK;
  stbin_exec_pps_if_pos_hold_data_read_req_MAP(req, msg, length, &result);

  if(STBIN_OK != result)
  {
    return result;   /*lint !e904 Return statement before end of function */
  }

  gnss_pps_get_position_hold_llh_pos(&lat,&lon,&height);

  rsp->posHoldOnOff = gnss_pps_get_position_hold_status();
  rsp->lat_val = (tUInt)(lat * SCALING_LAT_LON);
  rsp->lon_val = (tUInt)(lon * SCALING_LAT_LON);
  rsp->height =  (tUInt)(height * SCALING_HEIGHT);

  frameQ = frame_ack_qualifier(parms->class_Id, parms->msg_Id, rspSize, ONLY_ONE_FRAME);
  stbin_exec_pps_if_pos_hold_data_read_rsp_send(rsp, frameQ );

  return result;
}

#if NB_MAX_TRAIM_SATS_REPORTED != TRK_CHANNELS_SUPPORTED
#  error Please Revisit field definition
#endif

static stbin_status_t stbin_exec_pps_if_traim_read(tU16 length, tUChar *msg, const stbin_req_msg_parms *parms)
{
	tInt i=0;
	timing_data_t timing_data;
  frame_qualifier_t frameQ;

  PREPARE_OUTPUT_MESSAGE(parms->out_buf, stbin_exec_pps_if_traim_read_rsp_t, rsp, rspSize);
	stbin_status_t result = STBIN_OK;
  stbin_exec_pps_if_traim_read_req_MAP(req, msg, length, &result);

  if(STBIN_OK != result)
  {
    return result;   /*lint !e904 Return statement before end of function */
  }

  gnss_pps_get_timing_data(&timing_data);

	rsp->enabled     = timing_data.traim_enabled;
	rsp->algo_state  = (tU8)timing_data.traim_data.traim_solution;
	rsp->ave_error   = (tU32)timing_data.traim_data.ave_error;
	rsp->used_sat    = (tU8)timing_data.traim_data.used_sat_id;
	rsp->removed_sat = (tU8)timing_data.traim_data.removed_sat_id;
	for(i = 0; i < (tInt)rsp->used_sat; i++) {
		rsp->used_sats[i]    = (tU8)timing_data.traim_data.used_sat_id_table[i];
		rsp->residual_tab[i] = (tU16)timing_data.traim_data.residual[i];
	}

	for(i = 0; i < (tInt)rsp->removed_sat; i++) {
		rsp->removed_sats[i] = (tU8)timing_data.traim_data.removed_sat_id_table[i];
	}

  frameQ = frame_ack_qualifier(parms->class_Id, parms->msg_Id, rspSize, ONLY_ONE_FRAME);
  stbin_exec_pps_if_traim_read_rsp_send(rsp, frameQ );

  return result;
}

static stbin_status_t stbin_exec_test_rf_on(tU16 length, tUChar *msg, const stbin_req_msg_parms *parms)
{
	stbin_status_t result = STBIN_OK;
	stbin_exec_test_on_req_MAP(req, msg, length, &result);

  if(result != STBIN_OK)
  {
    return result;   /*lint !e904 Return statement before end of function */
  }

	result = stbin_exec_test_rf(false, req->test_type, req->satId, req->threshold);

	return result;
}

static stbin_status_t execute_rf_test_on(tChar Test_type, tU16 sat_id, tChar trk_threshold)
{
	stbin_status_t result = STBIN_OK;

	switch (Test_type) //test type check,  because this field have impact on the len protocol field.
	{
	case TEST_TYPE_01:
		gnss_set_rf_test_mode_on_sat_n_cn0_trk_thr(sat_id, trk_threshold);
		rf_test_sat_id=sat_id;
		break;
	case TEST_TYPE_02:
		gnss_set_rf_test_mode_on_sat_n (sat_id);
		rf_test_sat_id=sat_id;
		break;
	case TEST_TYPE_03:
		gnss_set_rf_test_mode_on_sat_n (SAT_ID_TEST_03);
		rf_test_sat_id=SAT_ID_TEST_03;
		break;
	default:
		result = STBIN_FAILED;
		break;
	}

  // Activate TEST_RF output message
  stbin_msg_list[1] |= STBIN_MASK_OUTPUT_TEST_RF;

	return result;
}

static stbin_status_t stbin_exec_test_rf(boolean_t add, tChar test_type,
                                        tU16 sat_id, tChar trk_threshold)
{
	stbin_status_t result = STBIN_OK;

  if(add == 0U) {
	  gnssapp_suspend();
	  platform_gnss_suspend();
	  platform_gnss_restart();
	  gnss_reset_rf_test_mode();
	}

	result = execute_rf_test_on(test_type, sat_id,trk_threshold);

  if(add == 0U)
  {
  	gnssapp_restart();
  }

	return result;
}

static stbin_status_t stbin_exec_test_add(tU16 length, tUChar *msg, const stbin_req_msg_parms *parms)
{
	stbin_status_t result = STBIN_OK;
	stbin_exec_test_add_req_MAP(req, msg, length, &result);

  if(result != STBIN_OK)
  {
    return result;   /*lint !e904 Return statement before end of function */
  }

	result = stbin_exec_test_rf(true, req->test_type, req->satId, req->threshold);

	return result;
}

static stbin_status_t stbin_exec_test_del(tU16 length, tUChar *msg, const stbin_req_msg_parms *parms)
{
	stbin_status_t result = STBIN_OK;
	stbin_exec_test_del_req_MAP(req, msg, length, &result);

  if(result != STBIN_OK)
  {
    return result;   /*lint !e904 Return statement before end of function */
  }

  if(gnss_rf_test_mode_del_sat_n(req->satId) != TRUE)
 	{
 	  result = STBIN_FAILED;
  }

 	return result;
}

static stbin_status_t stbin_exec_test_off(tU16 length, tUChar *msg, const stbin_req_msg_parms *parms)
{
	stbin_status_t result = STBIN_OK;
	stbin_exec_test_off_req_MAP(req, msg, length, &result);

  if(result != STBIN_OK)
  {
    return result;   /*lint !e904 Return statement before end of function */
  }

	gnss_reset_rf_test_mode();

  // Deactivate TEST_RF output message
  stbin_msg_list[1] &= ~STBIN_MASK_OUTPUT_TEST_RF;

	gnssapp_suspend();
	platform_gnss_suspend();
  platform_gnss_restart();
  gnssapp_restart();

	return result;
}


#ifdef RTC_TESTING
static stbin_status_t stbin_exec_test_rtc_on_off(tU16 length, tUChar *msg, const stbin_req_msg_parms *parms)
{
  extern void rtc_test_on_off( boolean_t );
	stbin_status_t result = STBIN_OK;
	stbin_exec_test_rtc_testOnOff_req_MAP(req, msg, length, &result);

  if(result != STBIN_OK)
  {
    return result;   /*lint !e904 Return statement before end of function */
  }

  rtc_test_on_off(req->onOff);

	return result;
}
#endif

static stbin_status_t stbin_exec_test_trk_interfere (tU16 length, tUChar *msg, const stbin_req_msg_parms *parms)
{
	stbin_status_t result = STBIN_OK;
	stbin_exec_test_trkjammer_req_MAP(req, msg, length, &result);

  if(result != STBIN_OK)
  {
    return result;   /*lint !e904 Return statement before end of function */
  }

  gnss_set_tracker_jammer(req->onOff);

 	return result;
}

static stbin_status_t stbin_exec_test_rtc_error(tU16 length, tUChar *msg, const stbin_req_msg_parms *parms)
{
	tDouble time_error=0;
	gnss_time_t gnss_time_result;
	gpOS_clock_t cpu_time_result;
	rtc_status_t rtc_status;
	time_validity_t stored_time_validity;
	gnss_time_reference_t gnss_time_reference_copy;
  gnss_sat_type_t sat_type;
	tDouble utc_delta_time;
	stbin_status_t result = STBIN_OK;
  frame_qualifier_t frameQ;

  PREPARE_OUTPUT_MESSAGE(parms->out_buf, stbin_exec_test_rtc_err_rsp_t, rsp, rspSize);

	stbin_exec_test_rtc_err_req_MAP(req, msg, length, &result);

  if(result != STBIN_OK)
  {
    return result;   /*lint !e904 Return statement before end of function */
  }

  gnssapp_suspend();
  gpOS_interrupt_lock();
  gnss_rtc_read( &gnss_time_result, &cpu_time_result, &rtc_status,
                &stored_time_validity, &sat_type, &utc_delta_time );
  time_error = ( tDouble )req->error / 1000;
  gnss_time_result = gnss_time_plus( &gnss_time_result, time_error );
  gnss_time_reference_copy.gps_time = gnss_time_result;
  gnss_time_reference_copy.sat_type = sat_type;
  gnss_time_reference_copy.cpu_time = cpu_time_result;

  if ( req->accuracy < 50/*ms*/ )
  {
    gnss_rtc_write( gnss_time_reference_copy, ACCURATE_TIME, TRUE, utc_delta_time );
  }
  else
  {
    gnss_rtc_write( gnss_time_reference_copy, RTC_TIME, TRUE, utc_delta_time );
  }

  gpOS_interrupt_unlock();
  GPS_DEBUG_MSG( ( "[rtc][deliberate error]: %d ms\r\n", req->error ) );

  rsp->error = req->error;
  rsp->accuracy = req->accuracy;
  rsp->week = (tU16)gnss_time_reference_copy.gps_time.week_n;
  rsp->tow = (tU32)(gnss_time_reference_copy.gps_time.tow * SCALING_1000);

  frameQ = frame_ack_qualifier(parms->class_Id, parms->msg_Id, rspSize, ONLY_ONE_FRAME);
  stbin_exec_test_rtc_err_rsp_send(rsp, frameQ );

  platform_gnss_suspend();
  gnssapp_reset_startup_time();
	platform_gnss_restart();
  gnssapp_restart();

	return result;
}

static stbin_status_t stbin_exec_reset_gps (tU16 length, tUChar *msg, const stbin_req_msg_parms *parms)
{
	stbin_status_t result = STBIN_OK;
	stbin_exec_reset_gps_req_MAP(req, msg, length, &result);

  if(result != STBIN_OK)
  {
    return result;   /*lint !e904 Return statement before end of function */
  }

	gnssapp_suspend();
	platform_gnss_suspend();
	platform_gnss_restart();
	gnssapp_restart();

	return result;
}

static stbin_status_t stbin_exec_reset_soft (tU16 length, tUChar *msg, const stbin_req_msg_parms *parms)
{
	stbin_status_t result = STBIN_OK;
  stbin_exec_reset_soft_req_MAP(req, msg, length, &result);

	if (result != STBIN_OK)
	{
    return result;   /*lint !e904 Return statement before end of function */
  }

	gnssapp_suspend();
  platform_gnss_suspend();
  svc_mcu_sw_reset();

	return result;
}

static stbin_status_t stbin_exec_reset_stack_check (tU16 length, tUChar *msg, const stbin_req_msg_parms *parms)
{
	stbin_status_t result = STBIN_OK;
  stbin_exec_reset_stack_check_req_MAP(req, msg, length, &result);

	if (result != STBIN_OK)
  {
    return result;   /*lint !e904 Return statement before end of function */
  }

	execute_stack_usage_reset ();

	return result;
}

static void execute_stack_usage_reset (void)
{
  gpOS_task_t*  task;
  tChar *i;
  tChar *start;

  task = gpOS_task_get_head();
  while (task != NULL)
  {
    for (i=(tChar *)gpOS_task_get_stack_base(task);(*i!=(tChar)0xaa) && (i<(tChar *)gpOS_task_get_stack_ptr(task));i++) {};
    start=i+1;
    /* determine stack unused */
    gpOS_interrupt_lock();
    for (i=start;i<(tChar *)gpOS_task_get_stack_ptr(task);i++)
    {
      *i=0xaa;
    }
    gpOS_interrupt_unlock();
    task = gpOS_task_get_next( task);
  }
}

/*{{{  execute_init_freq()  */
static stbin_status_t stbin_exec_init_freq(tU16 length, tUChar *msg, const stbin_req_msg_parms *parms)
{
  stbin_status_t result=STBIN_OK;

  stbin_exec_init_freq_req_MAP(req, msg, length, &result);

  if(result != STBIN_OK)
  {
    return result;   /*lint !e904 Return statement before end of function */
  }

  gnss_set_centre_freq(((tDouble)req->freq)/SCALING_1000);

  return result;
}


static stbin_status_t stbin_exec_binary_output_ON_OFF(tU8 status_bin_protocol)
{
  stbin_status_t result=STBIN_OK;

  if(status_bin_protocol == ON)
  {
    //enable output messages
    if(stbin_out_msg_on_off == FALSE)
    {
      gnss_events_install(GNSS_EVENTID_FIXREADY,stbin_outmsg_synchdlr_ptr);
      stbin_out_msg_on_off = TRUE;
    }
  }
  else
  {
    //disable output messages
    if(stbin_out_msg_on_off == TRUE)
    {
      gnss_events_uninstall(GNSS_EVENTID_FIXREADY,stbin_outmsg_synchdlr_ptr);
      stbin_out_msg_on_off = FALSE;
    }
  }

  return result;
}




static stbin_status_t stbin_exec_switch_to_NMEA()
{
  stbin_status_t result=STBIN_OK;

  /* Prepare main dispatcher to new state */
  nmea_set_if_mode(NMEA_INTERNAL_IF_MODE);

  /* Prepare stbin output event handler to return to main dispatcher */
  stbin_out_processing_enabled = FALSE;

  if(stbin_out_msg_on_off == FALSE)
  {
    // Re-enable event to make sure the output process handler will wake up and see the state change
    gnss_events_install(GNSS_EVENTID_FIXREADY,stbin_outmsg_synchdlr_ptr);

    // If comming back again to stbin, this flag must be True by default
    stbin_out_msg_on_off = TRUE;
  }

  return result;
}
/*}}}  */
/*+-------------------------------------------------------------------------+*/
/*|                                                                         |*/
/*|  .-----.__________________.------.                   _.--._             |*/
/*|  |=======================' |||||| )      .----------'------`--------.   |*/
/*|  `----------------._____.--------'       ============================   |*/
/*|                 _.-|   |---.__             /=====/  `------'            |*/
/*|           __.--'---|___|------`-------------------.                     |*/
/*|          '---------------._        ___.-------._ /                      |*/
/*|                            `-.----'-------------'                       |*/
/*|                                \____.-----'                             |*/
/*|                                                                         |*/
/*|@F_PROJECT      : gnssapp_scl [napus012.nap.st.com]                      |*/
/*|@F_PROJECT_REL  : 1.2                                                    |*/
/*|@F_NAME         : Teseo2 sdk - binary protocol                           |*/
/*|@F_PURPOSE      : Add binary protocol features / stbin_dec.c             |*/
/*|@F_CREATED_BY   : Intecs Spa                                             |*/
/*|@F_CREATION_DATE: xx/xx/xxxx                                             |*/
/*|@F_CREATION_SITE: STm Naples/Arzano Italy                                |*/
/*|@F_MODIFIED_BY  : FV                                                     |*/
/*|@F_CHANGE_DATE  : xx.xx.xxxx                                             |*/
/*|@F_MODIFY_CODE  : none                                                   |*/
/*|@F_LANGUAGE     : C                                                      |*/
/*|@F_MICRO_TYPE   : STA 8088                                               |*/
/*|@F_ANNOTATIONS  : Decode function List                                   |*/
/*+-------------------------------------------------------------------------+*/
/*Perform two complement of generic size type*/
/*lint --e{9059}  : C comment contains C++ comment [MISRA 2012 Rule 3.1, required]*/
/*static tDouble stbin_dec_Perform_Two_Compl(tInt val_to_covert, tInt dim_bit)
 {
    tDouble val = 0.0;
	tDouble val_3;
	tDouble val_2 = val_to_covert;

	val_3 = pow(2, dim_bit) - 1;
	val_3 = (val_3 + 1); //0xFFFFFF + 0x01
	if (val_2 >= (pow(2, dim_bit) / 2))
	{
		val = (val_2 - val_3);
	}
	else
	{
		val = val_2;
	}
	return val;
 }
 */

 /*
static tDouble stbin_dec_Get_Val(tUChar *msg, tInt start_index, tInt stop_index, tInt typeVal)
{
	tDouble value = ERROR;

    switch (typeVal)
    {
    case Latitude:
             value = stbin_dec_Decode_LatORLong(msg, start_index, stop_index);

             if(( value > LAT_MAX_VAL) || ( value < LAT_MIN_VAL))
             {
            	 value = ERROR;
             }
    	break;
    case Longitude:
    	     value = stbin_dec_Decode_LatORLong(msg, start_index, stop_index);
    	     if(( value > LON_MAX_VAL) || ( value < LON_MIN_VAL))
    	     {
    	    	 value = ERROR;
    	     }
        break;
    case Height:
    	      value=stbin_dec_Decode_Height(msg, start_index, stop_index);
    	      if(( value > HEIGHT_MAX_VAL) || ( value < (HEIGHT_MIN_VAL)))
    	      {
    	    	  value = ERROR;
    	      }
        break;
    case Height_en_dis_pos_hold:

    	 value=stbin_dec_Decode_Height(msg, start_index, stop_index);
    	 if(( value > HEIGHT_MAX_VAL) || ( value < (HEIGHT_MIN_VAL_EN_DIS_POS_HOLD)))
    	 {
    		 value = ERROR;
    	 }
        break;
    default:
    	value = ERROR;
    	break;
	}
	return value;
}

static tDouble stbin_dec_Decode_Height(tUChar *msg, tInt start_index, tInt stop_index)
{
	tDouble value = ERROR;
	tUInt decVal=0;
	tInt scaling = SCALING_HEIGHT;

	decVal=decVal|((((tUInt)msg[start_index])<<24)& 0xFF000000);
	decVal=decVal|((((tUInt)msg[start_index+VAL_ONE])<<16)& 0xFF0000);
	decVal=decVal|((((tUInt)msg[stop_index-VAL_ONE])<<8)& 0xFF00);
	decVal=decVal|((((tUInt)msg[stop_index]))& 0xFF);
	value=stbin_dec_Perform_Two_Compl(decVal,I4)/scaling;
	return value;
}

static tDouble stbin_dec_Decode_LatORLong(tUChar *msg, tInt start_index, tInt stop_index)
{
	tDouble value =ERROR;
    tUInt decVal=0;
    tInt scaling =SCALING_LAT_LON;

    decVal=decVal|((((tUInt)msg[start_index])<<24)& 0xFF000000);
    decVal=decVal|((((tUInt)msg[start_index+VAL_ONE])<<16)& 0xFF0000);
    decVal=decVal|((((tUInt)msg[stop_index-VAL_ONE])<<8)& 0xFF00);
    decVal=decVal|((((tUInt)msg[stop_index]))& 0xFF);
    value=stbin_dec_Perform_Two_Compl(decVal,I4)/scaling;
	return value;
}

static tDouble stbin_dec_perform_scaling(tDouble value, tU16 scaling)
{
	tDouble scal_val = ERROR;
	if(scaling > 0 )
	{
		scal_val=value/scaling;
	}
	else
	{
		scal_val = ERROR;
	}
	return scal_val;
}
 */

tInt stbin_dec_return_elaborate_notch_freq_forAPI(tUChar _notch_sat_type, tUChar _notch_status, tInt _notch_frequency)
{
	tInt value=0;
	tDouble kfreq_init ;
	tInt local_notch_status;
	tInt local_notch_sat_type;

  local_notch_status = (tInt) _notch_status;
  local_notch_sat_type = (tInt) _notch_sat_type;

	if( ((local_notch_status >= 0) && (local_notch_status < 3)) && ((local_notch_sat_type >= 0) && (local_notch_status < 2 ))  && (_notch_frequency >=0) )   /* check on params  */
	{
		if(local_notch_status == 0)
		{
			kfreq_init =  -1.0*cos(2.0*(PI)*(tDouble)_notch_frequency/(16.0*1023000.0)) ;
			value = (tInt) (kfreq_init*(8.0*1024.0*1024.0)); /*(cos(2*pi*wnotch)/16*1023000)*2^23) , GPS*/
		}
		else
		{
			kfreq_init =  -1.0*cos(2.0*(PI)*(tDouble)_notch_frequency/(32.0*1023000.0)) ;
			value = (tInt) (kfreq_init*(8.0*1024.0*1024.0)); /*(cos(2*pi*wnotch)/32*1023000)*2^23) , GLonass*/
		}
	}
	return value;
}

/*}}}  */
/*+-------------------------------------------------------------------------+*/
/*|                                                                         |*/
/*|  .-----.__________________.------.                   _.--._             |*/
/*|  |=======================' |||||| )      .----------'------`--------.   |*/
/*|  `----------------._____.--------'       ============================   |*/
/*|                 _.-|   |---.__             /=====/  `------'            |*/
/*|           __.--'---|___|------`-------------------.                     |*/
/*|          '---------------._        ___.-------._ /                      |*/
/*|                            `-.----'-------------'                       |*/
/*|                                \____.-----'                             |*/
/*|                                                                         |*/
/*|@F_PROJECT      : gnssapp_scl [napus012.nap.st.com]                      |*/
/*|@F_PROJECT_REL  : 1.xx                                                   |*/
/*|@F_NAME         : Teseo2 sdk - binary protocol                           |*/
/*|@F_PURPOSE      : Add binary protocol features / stbin_outProcess.c      |*/
/*|@F_CREATED_BY   : Intecs Spa                                             |*/
/*|@F_CREATION_DATE: 20/03/2012                                             |*/
/*|@F_CREATION_SITE: STm Naples/Arzano Italy                                |*/
/*|@F_MODIFIED_BY  : FV                                                     |*/
/*|@F_CHANGE_DATE  : xx.xx.xxxx                                             |*/
/*|@F_MODIFY_CODE  : none                                                   |*/
/*|@F_LANGUAGE     : C                                                      |*/
/*|@F_MICRO_TYPE   : STA 8088                                               |*/
/*|@F_ANNOTATIONS  : Created stbin Ouput Commands                           |*/
/*+-------------------------------------------------------------------------+*/


/*Entry point Output process......*/

static void stbin_send_configured_base_msg(const tU32 *msg_list, const stbin_outProcess_input *in)
{
	stbin_output_msg_parms parms;
	tInt i;

  parms.currTow_mills = in->currTow_mills;
  parms.currTow_nanos = in->currTow_nanos;
	parms.class_Id = STBIN_OUTPROCESS_CLASS_ID;
	parms.data_p = in->fix_data;
  parms.out_buf = in->outBuf;

  for(i=0;i<STBIN_NB_OUTPUT_MSG_IN_LIST;i++)
  {
    if((stbin_outmsg_base_list[i].mask & msg_list[stbin_outmsg_base_list[i].mask_bank]) != 0U)
    {
			parms.msg_Id = stbin_outmsg_base_list[i].msg_Id;
			stbin_outmsg_base_list[i].gen(&parms);
    }
  }
}


void stbin_output_processing(void)
{
  stbin_outProcess_input input;
  stbin_buffer_io_type MsgToSendOutputMessages;
  tInt           week_n;
  gpOS_clock_t  fix_clock;
  tDouble tow;
  tDouble tow_ms;

  stbin_out_processing_enabled = TRUE;
  input.outBuf = &(MsgToSendOutputMessages.buffer[sizeof(stbin_header_t3)]);
  input.fix_data = NULL;

  gnss_events_install(GNSS_EVENTID_FIXREADY,stbin_outmsg_synchdlr_ptr);

  while(stbin_out_processing_enabled == TRUE)
  {
    gnss_events_wait(GNSS_EVENTID_FIXREADY, stbin_outmsg_synchdlr_ptr);

    // Check if stbin has switch to disable while it was waiting the event
    if(stbin_out_processing_enabled != FALSE) {
      gnss_fix_store_local(NULL);
      gnss_fix_read_claim();

      gnss_fix_get_time_local(&week_n, &tow, &fix_clock,NULL);
      tow_ms = tow * SCALING_KILO;
      input.currTow_mills = (tUInt)(tow * SCALING_1000);
      input.currTow_nanos = (tUInt)((tow_ms - (tDouble)input.currTow_mills) * SCALING_MEGA);

      // Local msgs
      stbin_send_configured_base_msg(stbin_msg_list, &input);

      // Plugins msgs
      gnssapp_plugins_stbin_outmsg_transmit(stbin_msg_list, &input);

      gnss_fix_read_release();
    }
  }

  gnss_events_uninstall(GNSS_EVENTID_FIXREADY,stbin_outmsg_synchdlr_ptr);
}

void _stbin_msg_send(tUChar *buf, tUInt msg_len, frame_qualifier_t frameQ )
{
  tInt frame_header_size = sizeof(stbin_header_t3) - HEADER_PADDING_SIZE;
  stbin_header_t3 *header = (stbin_header_t3 *)(buf - sizeof(stbin_header_t3));
  tUChar *frame_start_addr = buf - frame_header_size;

#if ( defined(__linux__) && (__BYTE_ORDER != __BIG_ENDIAN) ) || ( (! defined(__linux__)) && (! defined(__BIG_ENDIAN)) )
  header->padding_sync = ((tUInt)((SYNC_BYTE_1 << 8) | SYNC_BYTE_2)) << 16;
#else
#  error Sync bytes must be recoded for BIG ENDIAN
#endif
  header->qualifier = frameQ;

  // Add header len to payload len
  msg_len += frame_header_size;

  // Add checksum and get total len
  msg_len = stbin_message_update_cs(frame_start_addr, msg_len);

  // Send message
  send_msg_to_uart_p(frame_start_addr, msg_len);
}

void Send_ACKorNACK(ack_nack_status_t ResponseType, const stbin_req_msg_parms *parms_in)
{
  frame_qualifier_t frameQ;

  if (ACK == ResponseType)
  {
    frameQ = frame_ack_qualifier(parms_in->class_Id, parms_in->msg_Id, 0, ONLY_ONE_FRAME);
  }
  else
  {
    frameQ = frame_nack_qualifier(parms_in->class_Id, parms_in->msg_Id);
  }

  _stbin_msg_send((tUChar *)parms_in->out_buf, 0, frameQ );
}

//------------------------------------------------------------------
//------------------------------------------------------------------
//------- START OF CLASS ID 01 Output Messages
//------------------------------------------------------------------
//------------------------------------------------------------------

static void stbin_output_exec_pos_ecef(const stbin_output_msg_parms *parms)
{
  ECEF_pos_t* ecef_pos;
  tDouble N, E, V;
  PREPARE_OUTPUT_MESSAGE(parms->out_buf, outprocess_ecef_t, posECEF, rspSize);
  frame_qualifier_t frameQ;

	ecef_pos = gnss_fix_get_fil_ecef_pos_local(parms->data_p);

	//write structure
	posECEF->iTOW  = parms->currTow_mills;
	posECEF->ecefX = ecef_pos->x;
	posECEF->ecefY = ecef_pos->y;
  posECEF->ecefZ = ecef_pos->z;

  gnss_fix_get_position_covariance_local( &N, &E, &V, parms->data_p );
	posECEF->pAcc  = sqrt( N + E + V ) * SCALING_1000;

  frameQ = frame_ack_qualifier(parms->class_Id, parms->msg_Id, rspSize, ONLY_ONE_FRAME);
  outprocess_ecef_send(posECEF, frameQ);
}


static void stbin_output_exec_pos_llh(const stbin_output_msg_parms *parms)
{
  position_t  *pos;
  position_t extrap_pos;
	tDouble  geoid_msl, rms_residual;
  tDouble N, E, V;
  PREPARE_OUTPUT_MESSAGE(parms->out_buf, outProcess_pos_llh_t, posLLH, rspSize);
  frame_qualifier_t frameQ;

	//Get working data from gnss api
  pos =  gnss_fix_get_fil_pos_local(parms->data_p);
  extrap_pos.latitude = pos->latitude;
  extrap_pos.longitude = pos->longitude;
  extrap_pos.height = pos->height;

  geoid_msl = gnss_fix_get_geoid_msl_local(parms->data_p);

  /*{{{   Convert the WGS84 to local datum*/
  {
    ECEF_pos_t* temp_ecef;
    temp_ecef = gnss_fix_get_fil_ecef_pos_local( parms->data_p );
    datum_convert_position_wgs84_to_local_datum(temp_ecef,&extrap_pos,&geoid_msl);
    pos = &extrap_pos;
  }

	rms_residual = gnss_fix_get_position_rms_residual_local(parms->data_p);
	//write structure
	posLLH->iTOW        = parms->currTow_mills;
	posLLH->lon         = (tInt)((pos->longitude) * SCALING_LAT_LON);
	posLLH->lat         = (tInt)((pos->latitude)  * SCALING_LAT_LON);
	posLLH->height      = (tInt)(((pos->height)   * SCALING_HEIGHT) + (geoid_msl * SCALING_HEIGHT));
	posLLH->hMSL        = (tInt)((pos->height)    * SCALING_HEIGHT);
	posLLH->rms_pos_res = (tInt)(rms_residual * SCALING_10);

  gnss_fix_get_position_covariance_local( &N, &E, &V, parms->data_p );
	posLLH->hAcc   = (tU32)(sqrt( N + E ) * SCALING_1000);
	posLLH->vAcc   = (tU32)(sqrt(V) * SCALING_1000);

  frameQ = frame_ack_qualifier(parms->class_Id, parms->msg_Id, rspSize, ONLY_ONE_FRAME);
  outProcess_pos_llh_send(posLLH, frameQ );
}

static void stbin_output_exec_status (const stbin_output_msg_parms *parms)
{
  gnssapp_startup_time_t * gnssapp_startup_time;
  gpOS_clock_t first_fix_timestamp;
  tU32 set_timer_clock_delay_ms;
  fix_status_t  fix_status;
  diff_status_t diff_status;
  PREPARE_OUTPUT_MESSAGE(parms->out_buf, outputprocess_status_t, status, rspSize);
  frame_qualifier_t frameQ;

  fix_status = gnss_fix_get_pos_status_local(parms->data_p);
  diff_status = gnss_fix_get_diff_status_local(parms->data_p);

  first_fix_timestamp      = gnss_position_get_first_fix_timestamp();
  gnssapp_startup_time     = gnssapp_get_startup_time();
  set_timer_clock_delay_ms = ( gnssapp_startup_time->gnss_lib_set_timer_clock -
                             gnssapp_startup_time->suspend_restart_support_time ) / gnssapp_startup_time->MTU_timer_clock; // suspend_restart_support_time =0 when the receiver is turn ON

  //write structure
  status->iTOW   = parms->currTow_mills;

  status->flags  = (tU8)diff_status;
  status->fixStat= (tU8)fix_status;
  status->ttff_ms= set_timer_clock_delay_ms + ((first_fix_timestamp - gnssapp_startup_time->gnss_lib_set_timer_clock) / (tU32)TRACKER_CPU_TICKS_PER_MSEC);
  status->msss   = gnssapp_update_running_time();

  frameQ = frame_ack_qualifier(parms->class_Id, parms->msg_Id, rspSize, ONLY_ONE_FRAME);
  outputprocess_status_send(status, frameQ );
}

static void stbin_output_exec_dop (const stbin_output_msg_parms *parms)
{
  tDouble pdop, hdop, vdop, gdop, tdop;
  PREPARE_OUTPUT_MESSAGE(parms->out_buf, outputprocess_dop_t, dop, rspSize);
  frame_qualifier_t frameQ;

	gnss_fix_get_dops_local(&pdop, &hdop, &vdop, &gdop, parms->data_p);

	tdop = sqrt((gdop*gdop)- (pdop*pdop));

	//write structure
	dop->iTOW   = parms->currTow_mills;
	dop->gDOP   = (tU16)(gdop * SCALING_1000);
	dop->pDOP   = (tU16)(pdop * SCALING_1000);
	dop->tDOP   = (tU16)(tdop * SCALING_1000);
	dop->vDOP   = (tU16)(vdop * SCALING_1000);
	dop->hDOP   = (tU16)(hdop * SCALING_1000);

  frameQ = frame_ack_qualifier(parms->class_Id, parms->msg_Id, rspSize, ONLY_ONE_FRAME);
  outputprocess_dop_send(dop, frameQ );
}

static void stbin_output_exec_velecef (const stbin_output_msg_parms *parms)
{
  tDouble N, E, V;
	ECEF_vel_t*              ecef_vel;
  PREPARE_OUTPUT_MESSAGE(parms->out_buf, outputprocess_velecef_t, velecef, rspSize);
  frame_qualifier_t frameQ;

	ecef_vel = gnss_fix_get_fil_ecef_vel_local(parms->data_p);

	//write structure
	velecef->iTOW   = parms->currTow_mills;
	velecef->ecefVX = (tInt)(ecef_vel->x * SCALING_100);
	velecef->ecefVY = (tInt)(ecef_vel->y * SCALING_100);
	velecef->ecefVZ = (tInt)(ecef_vel->z * SCALING_100);

  gnss_fix_get_position_covariance_local( &N, &E, &V, parms->data_p );
	velecef->sAcc   = sqrt( N + E + V ) * SCALING_1000;

  frameQ = frame_ack_qualifier(parms->class_Id, parms->msg_Id, rspSize, ONLY_ONE_FRAME);
  outputprocess_velecef_send(velecef, frameQ );
}

static void stbin_output_exec_velneu (const stbin_output_msg_parms *parms)
{
  tDouble N, E, V;
	velocity_t              *vel;
	tDouble                  course_2D, course_3D, speed_2D, speed_3D, rms_residual;
  PREPARE_OUTPUT_MESSAGE(parms->out_buf, outputprocess_velneu_t, velneu, rspSize);
  frame_qualifier_t frameQ;

	vel = gnss_fix_get_fil_vel_local(parms->data_p);

	if (GNSS_NO_ERROR == gnss_conv_vel_to_course_speed(vel, &course_2D, &speed_2D ))
  {
    velneu->gSpeed  = (tUInt)(speed_2D  * SCALING_1000);
    velneu->heading = (tInt)(course_2D * SCALING_1000);
  }
  else
  {
    velneu->gSpeed  = RESERVED_U32;
    velneu->heading = RESERVED_U32;
  }

  if (GNSS_NO_ERROR == gnss_conv_vel_to_course_speed_3D(vel, &course_3D, &speed_3D ))
  {
    velneu->speed = (tUInt)(speed_3D  * SCALING_1000);
  }
  else
  {
    velneu->speed = RESERVED_U32;
  }

  velneu->iTOW    =  parms->currTow_mills;
  velneu->velN    =  (tInt)(vel->vel_north * SCALING_1000);
  velneu->velE    =  (tInt)(vel->vel_east  * SCALING_1000);
  velneu->velU    =  (tInt)(vel->vel_vert  * SCALING_1000);

  rms_residual = gnss_fix_get_velocity_rms_residual_local(parms->data_p);
  velneu->rms_vel_res = (tInt)(rms_residual * SCALING_10);

  gnss_fix_get_position_covariance_local( &N, &E, &V, parms->data_p );
  velneu->sAcc    =  sqrt( N + E + V ) * SCALING_1000;
  velneu->cAcc    =  atan2(sqrt(vel->vel_north), sqrt(vel->vel_east)) * SCALING_1000;  //approximation

  frameQ = frame_ack_qualifier(parms->class_Id, parms->msg_Id, rspSize, ONLY_ONE_FRAME);
  outputprocess_velneu_send(velneu, frameQ );
}

/************************************************************************
*  Since no API is provided to retrieve Time Accuracy, this function is
*  used to get approximated value from available parameter.
************************************************************************/
static tUInt timeAccuracy_from_timeLocalValidity(time_validity_t timeValid)
{
  tUInt timeAccuracy;

  switch(timeValid) {
    case POSITION_TIME:
    case EPHEMERIS_TIME:
      timeAccuracy = 50;
      break;
    case RTC_TIME_ACCURATE:
      timeAccuracy = 50000000;
      break;
    case NO_TIME:
    case FLASH_TIME:
    case USER_TIME:
    case USER_RTC_TIME:
    case RTC_TIME:
    case APPROX_TIME:
    case ACCURATE_TIME:
    default:
      timeAccuracy = 1000000000;
      break;
  }

  return timeAccuracy;
}

static void stbin_output_exec_timegnss (const stbin_output_msg_parms *parms)
{
	tDouble                   tow;
	tDouble                   tow_ms;
	tInt                      weekN;
	tChar                     leap;
  gpOS_clock_t              cpuTime;
  time_validity_t           timeValid;
  PREPARE_OUTPUT_MESSAGE(parms->out_buf, outputprocess_timegnss_t, timegps, rspSize);
  frame_qualifier_t frameQ;

	gnss_fix_get_time_local(&weekN, &tow, &cpuTime, parms->data_p);
	leap = (tChar)gnss_get_utc_delta_time();
	timeValid = gnss_fix_get_time_validity_local(parms->data_p);

	//write structure
	tow_ms = tow * SCALING_1000;
	timegps->iTOW  = (tUInt)tow_ms;
	timegps->fTOW  = (tUInt)((tow_ms - (tDouble)timegps->iTOW) *  SCALING_MEGA);
	if(timegps->fTOW > (tS32)(SCALING_MEGA/2.0)) {
    timegps->iTOW -= 1;
    timegps->fTOW -= (tS32)(SCALING_MEGA/2.0);
  }
	timegps->week  = (tU16)weekN;
	timegps->leapS = leap;
	timegps->valid = (tChar)timeValid;
	timegps->tAcc  = timeAccuracy_from_timeLocalValidity(timeValid);

  frameQ = frame_ack_qualifier(parms->class_Id, parms->msg_Id, rspSize, ONLY_ONE_FRAME);
  outputprocess_timegnss_send(timegps, frameQ );
}

static void stbin_output_exec_timeutc  (const stbin_output_msg_parms *parms)
{
  gnss_time_t             local_time;
  gnss_time_t             utc_time;
  tDouble                 tau_g;
  tInt                    year, month, day, hours, minutes, seconds, milliseconds;
  gpOS_clock_t            fc_null;
  time_validity_t         timeValid;
  PREPARE_OUTPUT_MESSAGE(parms->out_buf, outputprocess_timeutc_t, timeutc, rspSize);
  frame_qualifier_t frameQ;

  gnss_fix_get_time_local(&local_time.week_n, &local_time.tow, &fc_null, parms->data_p);

  utc_time = gnss_time_to_utc_time( local_time, gnss_fix_get_time_sat_type_local( NULL ) );

  //gnss_get_utc_time(local_time.tow, &hours, &minutes, &seconds, &milliseconds);
  gnss_get_utc_time(utc_time.tow, &hours, &minutes, &seconds, &milliseconds);

  gnss_get_date(local_time.week_n, local_time.tow, &year, &month, &day);
  timeValid = gnss_fix_get_time_validity_local(parms->data_p);

	timeutc->iTOW  = (tUInt)(local_time.tow * SCALING_1000);
	timeutc->tAcc  = timeAccuracy_from_timeLocalValidity(timeValid);
	if(gnss_utc_gps_get_tau_g(&local_time, &tau_g) == GNSS_NO_ERROR)
  {
    timeutc->nano  = (tInt)((tau_g * (SCALING_GIGA))*SCALING_Q10_5);
  }
  else
  {
    timeutc->nano  = 0;
  }
	timeutc->year  = (tU16)year;
	timeutc->month = (tU8)month;
	timeutc->day   = (tU8)day;
	timeutc->hour  = (tU8)hours;
	timeutc->min   = (tU8)minutes;
	timeutc->sec   = (tU8)seconds;
  timeutc->valid = (tU8)timeValid;

  frameQ = frame_ack_qualifier(parms->class_Id, parms->msg_Id, rspSize, ONLY_ONE_FRAME);
  outputprocess_timeutc_send(timeutc, frameQ );
}

static void stbin_output_exec_svinfo (const stbin_output_msg_parms *parms)
{
	visible_sats_data_t     sats_visible;
	gnss_sat_type_mask_t    ConstellationMaskUsed;
	tInt                     j, i, nb_sat_to_report, sat_found;
	raw_measure_list_t*     raw_measure_ptr;
	satid_t                 sat_id;
  satid_t                 List_Prn_Found[VISIBLE_MAX_NUM_OF_SATS + TRK_CHANNELS_SUPPORTED];
  frame_status_t          frame_seq;
  PREPARE_OUTPUT_MESSAGE(parms->out_buf, outputprocess_svinfo_t, SatVehiculeInfo, rspSize);
  frame_qualifier_t frameQ;

  ConstellationMaskUsed = gnss_get_constellation_usage_mask();
  if(sw_config_get_software_switch_status(WAAS_ON_OFF_SWITCH) != 0U)
  {
    ConstellationMaskUsed |= (1U << (tUInt)GNSS_SAT_TYPE_SBAS);
  }

  nb_sat_to_report     = 0;

  raw_measure_ptr = gnss_fix_get_raw_measurements_local(parms->data_p);

  //Store list of Satellite tracked
  for (i = ((tInt)TRK_CHANNELS_SUPPORTED-1); i >= 0 ; i--)
  {
    if(raw_measure_ptr->list[i].dsp.flags.state != 0)
    {
      if(MCR_ISBITSET(ConstellationMaskUsed, gnss_sat_id_to_sat_type(raw_measure_ptr->list[i].dsp.satid)))
      {
        if(GNSS_NO_ERROR == nmea_support_translate_satid(raw_measure_ptr->list[i].dsp.satid, &sat_id))
        {
          List_Prn_Found[nb_sat_to_report] = raw_measure_ptr->list[i].dsp.satid;
          nb_sat_to_report++;
        }
      }
    }
  }

  //Add list of visible Satellite not tracked
  gnss_get_sats_visible(&sats_visible);
  for( j = (sats_visible.list_size-1) ; j >= 0; j--)
  {
    sat_found = 0;
    for(i = (nb_sat_to_report-1); (0 == sat_found) && (i >= 0); i--)
    {
      if (sats_visible.list[j].satid == List_Prn_Found[i])
      {
        sat_found = 1;
      }
    }
    if (0 == sat_found)
    {
      if(MCR_ISBITSET(ConstellationMaskUsed, gnss_sat_id_to_sat_type(raw_measure_ptr->list[i].dsp.satid)))
      {
        if(GNSS_NO_ERROR == nmea_support_translate_satid(sats_visible.list[j].satid,&sat_id))
        {
          List_Prn_Found[nb_sat_to_report] = sats_visible.list[j].satid;
          nb_sat_to_report++;
        }
      }
    }
  }

  //List of satellites is established and can be sent
  for(j = (nb_sat_to_report-1); j >= 0; j--)
  {
    sat_found = 0;
    SatVehiculeInfo->flags    = 0; // Reset flags
    SatVehiculeInfo->elev     = RESERVED_U8;
    SatVehiculeInfo->azim     = RESERVED_U16;
    SatVehiculeInfo->cno      = RESERVED_U8;
    SatVehiculeInfo->quality  = -1 /*CHAN_STATE_LOST*/;  // By default, can be updated for tracked sats
    SatVehiculeInfo->chn      = TRK_CHANNELS_SUPPORTED +1;

    //If Satellite is SBAS
    if(GNSS_SAT_TYPE_SBAS == gnss_sat_id_to_sat_type(List_Prn_Found[j]))
    {
      nmea_support_sat_params_t sbas_sat_params;
      gnssapp_plugins_cmd_param_t gpparam;

      sbas_sat_params.satid = List_Prn_Found[j];

      gpparam.id = 0;
      gpparam.data_ptr = &sbas_sat_params;

      // If Sat id equal to SBAS sat id - all information are be obtain
      if(gpOS_SUCCESS == gnssapp_plugins_cmd(GNSSAPP_PLUGINS_ID_WAAS, GNSSAPP_PLUGINS_CMD_CUSTOM, &gpparam))
      {
        SatVehiculeInfo->svid    = (tU8)sbas_sat_params.satid;
        SatVehiculeInfo->elev    = (tU8)sbas_sat_params.elevation;
        SatVehiculeInfo->azim    = (tU16)sbas_sat_params.azimuth;
        SatVehiculeInfo->cno     = (tChar)sbas_sat_params.CN0;
        sat_found = 2;
      }
      else
      {
        sat_found = 3;
      }
    }

    if (0 == sat_found)
    {
      for( i = (sats_visible.list_size-1); (0 == sat_found) && (i >= 0); i--)
      {
        // If sat tracked equal to visible sat => elev and Azim value can be found
        if(List_Prn_Found[j] == sats_visible.list[i].satid)
        {
          if(GNSS_NO_ERROR == nmea_support_translate_satid(List_Prn_Found[j],&sat_id) )
          {
            tInt iod;
            tDouble epoch;
            tDouble range;
            tDouble rate;
            boolean_t available;
            ephemeris_raw_t ephemeris;
            boolean_t eph_available = FALSE;
            almanac_raw_t almanac;
            boolean_t alm_available = FALSE;

            SatVehiculeInfo->svid    = (tU8)sat_id;
            SatVehiculeInfo->elev    = (tU8)sats_visible.list[i].elevation;

            gnss_get_diff_params(List_Prn_Found[j],&iod,&epoch,&range,&rate,&available);
            if(available != FALSE)
            {
              SatVehiculeInfo->flags   |= SVINFO_FLAG_SAT_DIFF_CORRECTION_AVAIL;
            }
            gnss_get_ephemeris_params(List_Prn_Found[j], &ephemeris, &eph_available);
            if(eph_available != FALSE)
            {
              SatVehiculeInfo->flags   |= SVINFO_FLAG_SAT_ORBIT_IS_EPH;
            }
            gnss_get_almanac_params(List_Prn_Found[j], &almanac, &alm_available);

            if(alm_available != FALSE)
            {
              SatVehiculeInfo->flags   |= SVINFO_FLAG_SAT_ORBIT_IS_ALM;
            }
            if((alm_available != FALSE) || (eph_available != FALSE))
            {
              SatVehiculeInfo->flags   |= SVINFO_FLAG_SAT_ORBIT_INFO_AVAIL;
            }
            if(gnss_get_sat_health(List_Prn_Found[j]) == 0)
            {
              SatVehiculeInfo->flags   |= SVINFO_FLAG_SAT_HEALTHY;
            }
            if(gnss_ephemeris_predicted(List_Prn_Found[j]) != FALSE)
            {
              SatVehiculeInfo->flags   |= SVINFO_FLAG_SAT_ORBIT_STAGPS;
            }
            SatVehiculeInfo->azim    = (tU16)sats_visible.list[i].azimuth;
            sat_found = 1;
          }
        }
      }
    }

    for (i = ((tInt)TRK_CHANNELS_SUPPORTED-1); i >= 0 ; i--)
    {
      if(raw_measure_ptr->list[i].dsp.flags.state != 0)
      {
        if(List_Prn_Found[j] == raw_measure_ptr->list[i].dsp.satid)
        {
          SatVehiculeInfo->quality  = raw_measure_ptr->list[i].dsp.flags.state;

          if(raw_measure_ptr->chans_used[i] != FALSE)
          {
            SatVehiculeInfo->flags |= SVINFO_FLAG_SAT_NAV_USED;
          }
          SatVehiculeInfo->chn     = (tU8)i;

          if ( 3 == sat_found)
          {
            SatVehiculeInfo->svid    = (tU8)raw_measure_ptr->list[i].dsp.satid;
          }
          if ( 0 == sat_found)
          {
            if(GNSS_NO_ERROR == nmea_support_translate_satid(List_Prn_Found[j],&sat_id) )
            {
              SatVehiculeInfo->svid    = (tU8)sat_id;
            }
          }
          if ( 2 != sat_found)
          {
            SatVehiculeInfo->cno     = (tChar)raw_measure_ptr->list[i].dsp.signal_strength;
          }
        }
      }
    }

    frame_seq = ((nb_sat_to_report-1) == j) ? START_OF_SEVERAL_FRAMES : MIDDLE_OF_SEVERAL_FRAMES;
    frame_seq |= (0 == j) ? END_OF_SEVERAL_FRAMES : MIDDLE_OF_SEVERAL_FRAMES;

    frameQ = frame_ack_qualifier(parms->class_Id, parms->msg_Id, rspSize, frame_seq);
    outputprocess_svinfo_send(SatVehiculeInfo, frameQ );
  }
}


static void stbin_output_exec_dgps(const stbin_output_msg_parms *parms)
{
#ifdef RTCM_LINKED
	tInt number_of_sats, station_health;
  PREPARE_OUTPUT_MESSAGE(parms->out_buf, outputprocess_dgps_t, statusDgps, rspSize);
  frame_qualifier_t frameQ;

	number_of_sats = dgps_sat_get_sat_number();

  station_health = dgps_hdr_get_station_health();

  statusDgps->iTOW         = parms->currTow_mills;
  statusDgps->age          = RESERVED_U32;  //To be implemented
  statusDgps->status = (DIFF_STATUS_ON == gnss_fix_get_diff_status_local(parms->data_p)) ?
                        1 : 0;
  if(REFERENCE_STATION_UNHEALTHY == station_health)
  {
    statusDgps->baseHealth = (tU8)station_health;
    statusDgps->baseId     = (tUInt)dgps_hdr_get_station_id();
    statusDgps->numCh      = (tU8)number_of_sats;
  }
  else
  {
    statusDgps->baseHealth = RESERVED_U8;
    statusDgps->baseId     = RESERVED_U32;
    statusDgps->numCh      = RESERVED_U8;
  }

  frameQ = frame_ack_qualifier(parms->class_Id, parms->msg_Id, rspSize, ONLY_ONE_FRAME);
  outputprocess_dgps_send(statusDgps, frameQ );
#endif
}

static void stbin_output_exec_dgps_data(const stbin_output_msg_parms *parms)
{
#ifdef RTCM_LINKED
  dgps_sat_data_diff_t     diffDataSat;
  tInt                         number_of_sats, i, gnss_iode;
  frame_status_t          frame_seq;
  PREPARE_OUTPUT_MESSAGE(parms->out_buf, outputprocess_dgps_data_t, dataDgps, rspSize);
  frame_qualifier_t frameQ;

	number_of_sats = dgps_sat_get_sat_number();


  for (i=0; i < number_of_sats; i++)
  {
    dgps_sat_get_params(i, &diffDataSat);

    gnss_iode = gnss_get_sat_iode(diffDataSat.sat_id);

    dataDgps->svid     = (tU8)diffDataSat.sat_id;
    dataDgps->ageC     = RESERVED_U16;
    dataDgps->chNum    = (tU8)i;

    if ((gnss_iode != -1) && (gnss_iode == (tInt)diffDataSat.issue_of_data))
    {
      if(0U == diffDataSat.scale_factor)
      {
        dataDgps->prc    = (tInt)(diffDataSat.pseudorange_correction * 2);   //(0.02 * SCALING_100)
        dataDgps->prrc   = (tInt)(diffDataSat.range_rate_correction * 2);    //(0.002 * SCALING_1000)
      }
      else if (diffDataSat.scale_factor == 1U)
      {
        dataDgps->prc    = (tInt)(diffDataSat.pseudorange_correction * 32);  //(0.32 * SCALING_100)
        dataDgps->prrc   = (tInt)(diffDataSat.range_rate_correction * 32);   //(0.032 * SCALING_1000)
      }
      else
      {
        dataDgps->prc    = RESERVED_U32;
        dataDgps->prrc   = RESERVED_U32;
      }
    }
    else
    {
      dataDgps->prc    = RESERVED_U32;
      dataDgps->prrc   = RESERVED_U32;
    }

    frame_seq = (0 == i) ? START_OF_SEVERAL_FRAMES : MIDDLE_OF_SEVERAL_FRAMES;
    frame_seq |= ((number_of_sats -1) == i) ? END_OF_SEVERAL_FRAMES : MIDDLE_OF_SEVERAL_FRAMES;

    frameQ = frame_ack_qualifier(parms->class_Id, parms->msg_Id, rspSize, frame_seq);
    outputprocess_dgps_data_send(dataDgps, frameQ );
  }
#endif
}

static void stbin_output_exec_ts(const stbin_output_msg_parms *parms)
{
  raw_t*               raw_data;
  tInt                  chn_index, nb_trames, nb_trame_cnt;
  frame_status_t          frame_seq;
  PREPARE_OUTPUT_MESSAGE(parms->out_buf, outputprocess_ts_t, ts, rspSize);
  frame_qualifier_t frameQ;

  //write structure
	raw_data = gnss_fix_get_raw_measurements_local(parms->data_p)->list;

  nb_trames=0;
  nb_trame_cnt=0;

  //Count number of trames to extract
  for(chn_index = ((tInt)TRK_CHANNELS_SUPPORTED-1); chn_index >= 0; chn_index--)
  {
    if ((raw_data[chn_index].dsp.flags.available == TRUE) || (raw_data[chn_index].sat.available != FALSE) || (raw_data[chn_index].diff.available != DIFF_CORRECTION_NONE))
    {
      nb_trames++;
    }
  }

  for(chn_index = ((tInt)TRK_CHANNELS_SUPPORTED-1); chn_index >= 0; chn_index--)
  {
    if ((raw_data[chn_index].dsp.flags.available == TRUE) || (raw_data[chn_index].sat.available != FALSE) || (raw_data[chn_index].diff.available != DIFF_CORRECTION_NONE))
    {
      ts->chn_id                     = (tU8) chn_index;
      ts->dsp_satid                  = (tU8) raw_data[chn_index].dsp.satid;
      ts->flag_availability          = (tU8) ((tU8)raw_data[chn_index].diff.available           |
                                                       (raw_data[chn_index].dsp.flags.available       << 4)|
                                                       (raw_data[chn_index].sat.available       << 5)|
                                                       (raw_data[chn_index].dsp.flags.preamble_locked << 6)|
                                                       (raw_data[chn_index].pred.available      << 7));
      ts->dsp_pseudorange            =                 MCR_FPU32_QM_TO_DOUBLE(raw_data[chn_index].dsp.pseudorange,GNSS_PSEUDORANGE_SHIFT);   /*lint !e9033 */
      ts->dsp_frequency              = (tInt)           MCR_FP32_QM_TO_DOUBLE(raw_data[chn_index].dsp.frequency,GNSS_FREQUENCY_SHIFT);   /*lint !e9033 */
      ts->dsp_signal_strength        = (tUInt)  raw_data[chn_index].dsp.signal_strength;
      ts->dsp_tracked_time           = (tInt)           raw_data[chn_index].dsp.tracked_time;

      ts->sat_pos_x                  = (tInt)           (MCR_FP32_QM_TO_DOUBLE(raw_data[chn_index].sat.sat_pos.x,GNSS_SAT_POS_SHIFT)              * SCALING_100);
      ts->sat_pos_y                  = (tInt)           (MCR_FP32_QM_TO_DOUBLE(raw_data[chn_index].sat.sat_pos.y,GNSS_SAT_POS_SHIFT)              * SCALING_100);
      ts->sat_pos_z                  = (tInt)           (MCR_FP32_QM_TO_DOUBLE(raw_data[chn_index].sat.sat_pos.z,GNSS_SAT_POS_SHIFT)              * SCALING_100);
      ts->sat_vel_x                  = (tInt)           (MCR_FP32_QM_TO_DOUBLE(raw_data[chn_index].sat.sat_vel.x,GNSS_SAT_VEL_SHIFT)              * SCALING_100);
      ts->sat_vel_y                  = (tInt)           (MCR_FP32_QM_TO_DOUBLE(raw_data[chn_index].sat.sat_vel.y,GNSS_SAT_VEL_SHIFT)              * SCALING_100);
      ts->sat_vel_z                  = (tInt)           (MCR_FP32_QM_TO_DOUBLE(raw_data[chn_index].sat.sat_vel.z,GNSS_SAT_VEL_SHIFT)              * SCALING_100);
      ts->sat_range_corr             = (tInt)           (raw_data[chn_index].sat.range_correction * SCALING_100);
      ts->sat_atmos_corr             = (tInt)           (MCR_FP16_QM_TO_DOUBLE(raw_data[chn_index].sat.atmospheric_correction,GNSS_ATM_CORRECT_SHIFT) * SCALING_100);

      ts->diff_range_corr            = (tInt)           (MCR_FP16_QM_TO_DOUBLE(raw_data[chn_index].diff.range_correction,GNSS_DIFF_RANGE_CORRECT_SHIFT)      * SCALING_100);
      ts->diff_range_rate_corr       = (tInt)           (MCR_FP16_QM_TO_DOUBLE(raw_data[chn_index].diff.range_rate_correction,GNSS_DIFF_RANGE_RATE_CORRECT_SHIFT) * SCALING_100);

      ts->pred_age_h                 = (tU8) raw_data[chn_index].pred.age_h;
      ts->pred_ephems_n              = (tU8) raw_data[chn_index].pred.ephems_n;
      ts->pred_time_distance_h       = (tU8) raw_data[chn_index].pred.time_distance_h;

      frame_seq = (0 == nb_trame_cnt) ? START_OF_SEVERAL_FRAMES : MIDDLE_OF_SEVERAL_FRAMES;
      frame_seq |= ((nb_trames -1) == nb_trame_cnt) ? END_OF_SEVERAL_FRAMES : MIDDLE_OF_SEVERAL_FRAMES;

      frameQ = frame_ack_qualifier(parms->class_Id, parms->msg_Id, rspSize, frame_seq);
      outputprocess_ts_send(ts, frameQ );

      nb_trame_cnt++;
	  }
  }
}


static void stbin_output_exec_tg(const stbin_output_msg_parms *parms)
{
  raw_measure_list_t*     raw_data;
  gpOS_clock_t            cpu_time;
  tInt week;
  tDouble tow;
  PREPARE_OUTPUT_MESSAGE(parms->out_buf, outputprocess_tg_t, tg, rspSize);
  frame_qualifier_t frameQ;

  gnss_fix_get_time_local(&week, &tow, &cpu_time, parms->data_p);
  raw_data = gnss_fix_get_raw_measurements_local(parms->data_p);

  if(raw_data != NULL)
  {
    tg->numSatUsed = (tU8)  raw_data->list_size;
  }
  else
  {
    tg->numSatUsed = RESERVED_U8;
  }

  tg->timeValidity = (tU8) (gnss_time_get_validity(gnss_time_get_master()));
	tg->nco        = (tInt)           (gnss_get_centre_freq() * SCALING_1000);
	tg->week       = (tU16) week;
	tg->iTOW       = (tUInt)  (tow * SCALING_1000);
	tg->cpuTime    = (tUInt)   cpu_time;

  frameQ = frame_ack_qualifier(parms->class_Id, parms->msg_Id, rspSize, ONLY_ONE_FRAME);
  outputprocess_tg_send(tg, frameQ );
}

static void stbin_output_exec_pos_algo(const stbin_output_msg_parms *parms)
{
  tInt                     stopped_duration;
  pos_algo_t              pos_algo;
  PREPARE_OUTPUT_MESSAGE(parms->out_buf, outputprocess_Pos_Algo_t, Algo_Pos, rspSize);
  frame_qualifier_t frameQ;

  gnss_fix_get_stopped_duration(&stopped_duration);
  pos_algo = gnss_fix_get_pos_algo_local(parms->data_p);

  Algo_Pos->iTOW    = parms->currTow_mills;
  Algo_Pos->posAlgo = (tU8)pos_algo;
  Algo_Pos->stoppedDuration = stopped_duration;

  frameQ = frame_ack_qualifier(parms->class_Id, parms->msg_Id, rspSize, ONLY_ONE_FRAME);
  outputprocess_Pos_Algo_send(Algo_Pos, frameQ );
}

static void stbin_output_exec_RF(const stbin_output_msg_parms *parms)
{
  raw_measure_list_t*     raw;
  tInt                    chan_index, sats_used, sat_reported;
  frame_status_t          frame_seq;
  PREPARE_OUTPUT_MESSAGE(parms->out_buf, outputprocess_RF_t, RF_info, rspSize);
  frame_qualifier_t frameQ;

  raw = gnss_fix_get_raw_measurements_local(parms->data_p);

  sats_used     = 0;
  sat_reported  = 0;

  for (chan_index = ((tInt)TRK_CHANNELS_SUPPORTED-1); chan_index >= 0; chan_index--)
  {
    if (TRUE == raw->list[chan_index].dsp.flags.available)
    {
      sats_used++;
    }
  }

  for (chan_index = ((tInt)TRK_CHANNELS_SUPPORTED-1); chan_index >= 0; chan_index--)
  {
    if (TRUE == raw->list[chan_index].dsp.flags.available)
    {

      RF_info->chn_id          = (tU8)chan_index;
      RF_info->dsp_satid       = (tU8)raw->list[chan_index].dsp.satid;
      RF_info->ave_phase_noise = (tInt)raw->list[chan_index].dsp.ave_phase_noise;
      RF_info->dsp_frequency   = (tInt)MCR_FP32_QM_TO_DOUBLE(raw->list[chan_index].dsp.frequency,GNSS_FREQUENCY_SHIFT);
      RF_info->cno             = (tInt)raw->list[chan_index].dsp.signal_strength;
      sat_reported++;

      if(1 == sat_reported)
      {
        frame_seq = (sat_reported == sats_used) ? ONLY_ONE_FRAME : START_OF_SEVERAL_FRAMES;
      }
      else
      {
        frame_seq = (sat_reported == sats_used) ? END_OF_SEVERAL_FRAMES : MIDDLE_OF_SEVERAL_FRAMES;
      }

      frameQ = frame_ack_qualifier(parms->class_Id, parms->msg_Id, rspSize, frame_seq);
      outputprocess_RF_send(RF_info, frameQ );
    }
  }
}

static void stbin_output_exec_cov(const stbin_output_msg_parms *parms)
{
  tDouble                  N,E,V,H;
  PREPARE_OUTPUT_MESSAGE(parms->out_buf, outputprocess_Cov_t, RF_info, rspSize);
  frame_qualifier_t frameQ;

  RF_info->iTOW       = parms->currTow_mills;

  gnss_fix_get_position_covariance_local(&N, &E, &V, parms->data_p);
  H = sqrt(N + E);
  RF_info->Pos_H_cov  = (tInt)(H * SCALING_10);
  RF_info->Pos_N_cov  = (tInt)(N * SCALING_10);
  RF_info->Pos_E_cov  = (tInt)(E * SCALING_10);
  RF_info->Pos_V_cov  = (tInt)(V * SCALING_10);

  gnss_fix_get_velocity_covariance_local(&N, &E, &V, parms->data_p);
  H = sqrt(N + E);
  RF_info->Vel_H_cov  = (tInt)(H * SCALING_10);
  RF_info->Vel_N_cov  = (tInt)(N * SCALING_10);
  RF_info->Vel_E_cov  = (tInt)(E * SCALING_10);
  RF_info->Vel_V_cov  = (tInt)(V * SCALING_10);

  frameQ = frame_ack_qualifier(parms->class_Id, parms->msg_Id, rspSize, ONLY_ONE_FRAME);
  outputprocess_Cov_send(RF_info, frameQ );
}

static void stbin_output_exec_gst(const stbin_output_msg_parms *parms)
{
  gnss_time_t utc_time;
  gnss_time_t local_time;
  gpOS_clock_t            fc_null;
  tDouble                 ehpe, n_cov, e_cov, v_cov, angle;
  math_ellipse_t          ellipse;
  tInt                    hours, mins, secs, msecs;
  PREPARE_OUTPUT_MESSAGE(parms->out_buf, outputprocess_GST_t, GST_info, rspSize);
  frame_qualifier_t frameQ;

  gnss_fix_get_time_local(&local_time.week_n, &local_time.tow, &fc_null, parms->data_p);

  utc_time = gnss_time_to_utc_time( local_time, gnss_fix_get_time_sat_type_local( NULL ) );

  gnss_get_utc_time(utc_time.tow, &hours, &mins, &secs, &msecs);

  ehpe = gnss_fix_get_ehpe_local(parms->data_p);
  gnss_fix_get_position_covariance_local(&n_cov, &e_cov, &v_cov, parms->data_p);
  gnss_fix_get_error_ellipse_local(&ellipse, parms->data_p);
  if(ellipse.semiaxis_n >= ellipse.semiaxis_e)
  {
    GST_info->major_axis = (tInt)(ellipse.semiaxis_n  * SCALING_10);
    GST_info->minor_axis = (tInt)(ellipse.semiaxis_e  * SCALING_10);
    angle                = (0.0 - ellipse.theta) ;
  }
  else
  {
    GST_info->major_axis = (tInt)(ellipse.semiaxis_e  * SCALING_10);
    GST_info->minor_axis = (tInt)(ellipse.semiaxis_n  * SCALING_10);
    angle                = (90.0 - ellipse.theta);
  }

  /* wrap angle*/
  if(angle > 180.0)
  {
     angle -= 360.0;
  }
  else if(angle < (-180.0))
  {
     angle += 360.0;
  }

  GST_info->iTOW        = parms->currTow_mills;
  GST_info->alt_err_dev = (tInt)(SCALING_10 * sqrt(v_cov));
  GST_info->lat_err_dev = (tInt)(SCALING_10 * sqrt(n_cov));
  GST_info->lon_err_dev = (tInt)(SCALING_10 * sqrt(e_cov));
  GST_info->ehpe        = (tInt)(SCALING_10 * ehpe);
  GST_info->angle       = (tS16)(SCALING_10 * angle);
  GST_info->hour        = (tU8)hours;
  GST_info->min         = (tU8)mins;
  GST_info->sec         = (tU8)secs;
  GST_info->msec        = (tU16)msecs;

  frameQ = frame_ack_qualifier(parms->class_Id, parms->msg_Id, rspSize, ONLY_ONE_FRAME);
  outputprocess_GST_send(GST_info, frameQ );
}

static void stbin_output_exec_pps_data(const stbin_output_msg_parms *parms)
{
  pps_data_t pps_data;
  PREPARE_OUTPUT_MESSAGE(parms->out_buf, outputprocess_PPSData_t, msg, rspSize);
  frame_qualifier_t frameQ;

  _clibs_memset(&pps_data, 0, sizeof(pps_data));
  gnss_pps_get_data( &pps_data );

	msg->onOff = pps_data.enabled; /* 0 */
	msg->pps_valid = pps_data.pps_valid; /* 1 */
	msg->synch_valid = pps_data.pps_synch_valid; /* 2 */
	msg->outMode = (tU8)pps_data.output_mode; /* 3 */
	msg->refTimeId = (tU8)pps_data.reference_time; /* 4 */
	msg->refConst = (tU8)pps_data.reference_constellation; /* 5 */
	msg->pulseDuration = (tU16)(pps_data.pulse_duration * SCALING_1000); /* 6 */ /* ms */
	msg->pulseDelay = (tU16)( pps_data.rf_correction * 1E9 ); /* 8 */ /* ns */
	msg->gpsRfDelay = (tU16)( pps_data.gps_rf_correction * 1E9 ); /* 10 */ /* ns */
	msg->glonassRfDelay = (tU16)( pps_data.glonass_rf_correction * 1E9 ); /* 12 */ /* ns */
	msg->pulsePolarity = pps_data.inverted_polarity; /* 14 */
	msg->fixCondition = (tU8)pps_data.fix_condition; /* 15 */
	msg->satTh = pps_data.sat_threshold; /* 16 */
	msg->elevationMask = pps_data.applied_timing_data.elevation_mask; /* 17 */
	msg->refsec = pps_data.applied_timing_data.traim_data.ref_second; /* 18 */
	msg->fixStat = (tU8)pps_data.applied_timing_data.fix_status; /* 19 */
	msg->constellationMask = (tU32)pps_data.applied_timing_data.constellation_mask; /* 20 */
	msg->ppsClockFreq = (tDouble)pps_data.pps_clk_freq_Hz; /* 24 */
	msg->tcxoClockFreq = (tDouble)pps_data.tcxo_clk_freq_Hz; /* 32 */
	msg->glonassUtcDelta_ns = (tU32)pps_data.glonass_utc_delta_time_ns; /* 40 */
	msg->gpsUtcDelta_ns = (tU32)pps_data.gps_utc_delta_time_ns; /* 44 */
	msg->quantErr = (tU16)((pps_data.quantization_error * SCALING_100000000)* SCALING_Q3_12); /* 48 */
	msg->gpsUtcDelta_s = (tU8)pps_data.gps_utc_delta_time_s; /* 50 */
	msg->used_sat = (tU8)pps_data.applied_timing_data.used_sats; /* 51 */

  frameQ = frame_ack_qualifier(parms->class_Id, parms->msg_Id, rspSize, ONLY_ONE_FRAME);
  outputprocess_PPSData_send(msg, frameQ );
}

static void stbin_output_exec_hold_data(const stbin_output_msg_parms *parms)
{
  tDouble latitude, longitude, height;
  PREPARE_OUTPUT_MESSAGE(parms->out_buf, outputprocess_HoldData_t, msg, rspSize);
  frame_qualifier_t frameQ;

  gnss_pps_get_position_hold_llh_pos( &latitude, &longitude, &height );

  msg->onOff = (gnss_pps_get_position_hold_status() != FALSE) ? 1U : 0U;
  msg->lat_val = (tInt)(latitude * SCALING_LAT_LON); /* 0 */
	msg->lon_val = (tInt)(longitude * SCALING_LAT_LON); /* 4 */
	msg->height  = (tInt)(height * SCALING_HEIGHT); /* 8 */

  frameQ = frame_ack_qualifier(parms->class_Id, parms->msg_Id, rspSize, ONLY_ONE_FRAME);
  outputprocess_HoldData_send(msg, frameQ );
}

static void stbin_output_exec_traim_data(const stbin_output_msg_parms *parms)
{
  tInt i;
  timing_data_t timing_data;
  PREPARE_OUTPUT_MESSAGE(parms->out_buf, outputprocess_TraimData_t, msg, rspSize);
  frame_qualifier_t frameQ;

  _clibs_memset(&timing_data, 0, sizeof(timing_data));
  gnss_pps_get_timing_data( &timing_data );

	msg->enabled = (tU8)timing_data.traim_enabled; /* 0 */
	msg->algo_state = (tU8)timing_data.traim_data.traim_solution; /* 1 */
	msg->used_sat = (tU8)timing_data.traim_data.used_sat_id; /* 2 */
	msg->removed_sat = (tU8)timing_data.traim_data.removed_sat_id; /* 3 */
  for ( i = 0; i < (tInt)timing_data.traim_data.used_sat_id; i++ ) {
    msg->used_sats[i] = (tU8)timing_data.traim_data.used_sat_id_table[i]; /* 4 */
    msg->residual_tab[i] = (tU16)timing_data.traim_data.residual[i]; /* 28 */
	}
  for ( i = 0; i < (tInt)timing_data.traim_data.removed_sat_id; i++ ) {
    msg->removed_sats[i] = (tU8)timing_data.traim_data.removed_sat_id_table[i]; /* 76 */
	}
	msg->ave_error = (tU32)timing_data.traim_data.ave_error; /* 100 */
	msg->alarm = (tU16)timing_data.traim_alarm; /* 104 */
	msg->refsec = (tU8)timing_data.traim_data.ref_second; /* 106 */

  frameQ = frame_ack_qualifier(parms->class_Id, parms->msg_Id, rspSize, ONLY_ONE_FRAME);
  outputprocess_TraimData_send(msg, frameQ );
}

static void stbin_output_exec_lowpower_data(const stbin_output_msg_parms *parms)
{
  gnss_low_power_data_t data;
  PREPARE_OUTPUT_MESSAGE(parms->out_buf, outputprocess_lowpowerData_t, msg, rspSize);
  frame_qualifier_t frameQ;

  gnss_low_power_get_data( &data );

  msg->state = (tU8)data.cyclic.state;
  msg->steadyState = data.steady_state;
  msg->eng1 = (tS16)data.no_fix;
  msg->eng2 = data.cyclic.sats_used;
  msg->ehpe = (tU16)(data.cyclic.ehpe * SCALING_1000);
  msg->eng3 = (tS16)data.glonass_tow_referesh;
  msg->ehpe_average = (tU16)(data.cyclic.average_ehpe_nmea * SCALING_1000);
  msg->eng4 = data.cyclic.average_NO_FIX;
  msg->eng5 = (tS16)data.counter_glonass_eph_ON;
  msg->gps_eph = (tU8)data.eph_const_mask;
  msg->eng6 = data.cyclic.reduced_type;
  msg->eng7 = data.cyclic.duty_cycle_on_off;
  msg->eng8 = data.cyclic.ms_off;
  msg->eng9 = data.cyclic.duty_cycle_state;

  frameQ = frame_ack_qualifier(parms->class_Id, parms->msg_Id, rspSize, ONLY_ONE_FRAME);
  outputprocess_lowpowerData_send(msg, frameQ );
}

static void stbin_output_exec_cpu_data(const stbin_output_msg_parms *parms)
{
  tInt clk_source, clk_speed;
  PREPARE_OUTPUT_MESSAGE(parms->out_buf, outputprocess_cpuData_t, msg, rspSize);
  frame_qualifier_t frameQ;
  tUInt cpu_usage;

  cpu_usage = svc_mcu_getcpuusage();

  #if defined( __STA8088__ )
  {
    boolean_t clk48f0enabled;

    platform_get_clock_configuration_status( &clk48f0enabled, &clk_source, &clk_speed );

    msg->cpu_usage = (tU16)cpu_usage;    //scaling is already 100
    msg->cpu_freq = (tU16)(((clk48f0enabled == TRUE)? (tS32)48 : (tS32)52) * ( clk_speed + 1 ));
    msg->pll_state = (clk_source != 0) ? 0U : 1U;
  }
  #elif defined( __STA8090__ )
  {
    platform_get_clock_configuration_status( &clk_source, &clk_speed);

    msg->cpu_usage = (tU16)cpu_usage;    //scaling is already 100

    if( LLD_PRCC_ARMCLKSRC_192f0 == (LLD_PRCC_ARMClkSrcTy)clk_source)
    {
      clk_speed = ((192 * 1023) / 1000) / (clk_speed + 1);
      msg->cpu_freq = (tU16)clk_speed;
      msg->pll_state = 1U;
    }
    else if( LLD_PRCC_ARMCLKSRC_TCXO == (LLD_PRCC_ARMClkSrcTy)clk_source)
    {
      msg->cpu_freq = (tU16)(platform_get_tcxo_speed()/1000000U);
      msg->pll_state = 0U;
    }
    else
    {
      msg->cpu_freq = 255U;
      msg->pll_state = 0U;
    }
  }
  #endif

  frameQ = frame_ack_qualifier(parms->class_Id, parms->msg_Id, rspSize, ONLY_ONE_FRAME);
  outputprocess_cpuData_send(msg, frameQ );
}

static void stbin_output_test_rf(const stbin_output_msg_parms *parms)
{
  tUInt chan_id    = 0;
  tInt  cn0        = 0;
  tInt  freq       = 0;
  tInt phase_noise = 0;
  raw_measure_list_t*     raw;
  PREPARE_OUTPUT_MESSAGE(parms->out_buf, outprocess_test_rf_t, msg, rspSize);
  frame_qualifier_t frameQ;

  raw = gnss_fix_get_raw_measurements_local(parms->data_p);

  for ( chan_id = 0; chan_id < TRK_CHANNELS_SUPPORTED; chan_id++ )
  {
    if ( rf_test_sat_id == raw->list[chan_id].dsp.satid )
    {
      if ( gnss_sat_tracking_check( raw->list[chan_id].dsp.flags.state ) == TRUE )
      {
        cn0         = raw->list[chan_id].dsp.signal_strength;
        freq        = (tInt)MCR_FP32_QM_TO_DOUBLE(raw->list[chan_id].dsp.frequency,GNSS_FREQUENCY_SHIFT);
        phase_noise = raw->list[chan_id].dsp.ave_phase_noise;
      }

      break;
    }
  }

  msg->frequency = freq;
  msg->phase_noise = phase_noise;
  msg->cno = cn0;
  msg->satid = rf_test_sat_id;

  frameQ = frame_ack_qualifier(parms->class_Id, parms->msg_Id, rspSize, ONLY_ONE_FRAME);
  outprocess_test_rf_send(msg, frameQ );
}

#if NB_MAX_TRK_REPORTED != TRK_CHANNELS_SUPPORTED
#  error Please Revisit field definition
#endif

static void stbin_output_posRes_data(const stbin_output_msg_parms *parms)
{
  tDouble rms_residual;
  chanid_t chan_id;
  tInt sat_cnt = 0;
  PREPARE_OUTPUT_MESSAGE(parms->out_buf, outputprocess_posres_t, msg, rspSize);
  frame_qualifier_t frameQ;

  rms_residual = gnss_fix_get_position_rms_residual_local( parms->data_p );
	msg->rmsRes = rms_residual * SCALING_10;

  for ( chan_id = 0; chan_id < TRK_CHANNELS_SUPPORTED; chan_id++ )
  {
    tDouble residual;
    boolean_t residual_valid;
    gnss_fix_get_position_residual_local( chan_id, &residual, &residual_valid, parms->data_p );

    if ( residual_valid != FALSE )
    {
      msg->posRes[sat_cnt] = (tU16)(residual * SCALING_10);
      sat_cnt++;
    }
  }

  msg->cnt = (tU8)sat_cnt;

  frameQ = frame_ack_qualifier(parms->class_Id, parms->msg_Id, rspSize, ONLY_ONE_FRAME);
  outputprocess_posres_send(msg, frameQ );
}

static void stbin_output_velRes_data(const stbin_output_msg_parms *parms)
{
  tDouble rms_residual;
  chanid_t chan_id;
  tInt sat_cnt = 0;
  PREPARE_OUTPUT_MESSAGE(parms->out_buf, outputprocess_velres_t, msg, rspSize);
  frame_qualifier_t frameQ;

  rms_residual = gnss_fix_get_velocity_rms_residual_local( parms->data_p );
	msg->rmsRes = rms_residual * SCALING_10;

  for ( chan_id = 0; chan_id < TRK_CHANNELS_SUPPORTED; chan_id++ )
  {
    tDouble residual;
    boolean_t residual_valid;
    gnss_fix_get_velocity_residual_local( (tInt)chan_id, &residual, &residual_valid, parms->data_p );

    if ( residual_valid != FALSE )
    {
      msg->velRes[sat_cnt] = residual * SCALING_10;
      sat_cnt++;
    }
  }

  msg->cnt = (tU8)sat_cnt;

  frameQ = frame_ack_qualifier(parms->class_Id, parms->msg_Id, rspSize, ONLY_ONE_FRAME);
  outputprocess_velres_send(msg, frameQ );
}

#define NOTCH_LOCK_BIT 7
#define NOTCH_OVERFLOWS_BIT 2
#define NOTCH_MODE_BITS 0
static void stbin_output_notch_filter_status(const stbin_output_msg_parms *parms)
{
  PREPARE_OUTPUT_MESSAGE(parms->out_buf, outputprocess_notch_filter_status_t, msg, rspSize);
  frame_qualifier_t frameQ;
  tInt kfreq_now, lock_en, pwr, ovfs;
  tShort mode;

  // GPS
  gnss_notch_filter_get_status( GNSS_SAT_TYPE_GPS, &kfreq_now, &lock_en, &pwr, &ovfs, &mode );
  if ( 0 == mode )
  {
    msg->kfreq_now_gps = 0;
    msg->pwr_gps = 0;
  }
  else
  {
    if ( kfreq_now > 512 )
    {
      kfreq_now = -( 1024 - kfreq_now );
    }

    msg->kfreq_now_gps = ( tInt )( ( acos( ( (tDouble)kfreq_now * 16384.0 / 8388608.0 ) ) / ( ( 2.0 * PI ) ) ) * ( 16.0 * 1023000.0 ) );
    msg->pwr_gps = pwr;

    if(ovfs >= 1000) {
      ovfs -= 1000;
      ovfs |= 0x8;
    }
    msg->flags_gps = 0;
    msg->flags_gps |= ((tU8)ovfs << NOTCH_OVERFLOWS_BIT);
    msg->flags_gps |= ((tU16)mode << NOTCH_MODE_BITS);
    if(lock_en != 0)
    {
      msg->flags_gps |= (1U << NOTCH_LOCK_BIT);
    }
  }

  // GLONASS
  gnss_notch_filter_get_status( GNSS_SAT_TYPE_GLONASS, &kfreq_now, &lock_en, &pwr, &ovfs, &mode );
  if ( 0 == mode )
  {
    msg->kfreq_now_gln = 0;
    msg->pwr_gln = 0;
  }
  else
  {
    if ( kfreq_now > 512 )
    {
      kfreq_now = -( 1024 - kfreq_now );
    }

    msg->kfreq_now_gln = ( tS32 )( ( acos( ( (tDouble)kfreq_now * 16384.0 / 8388608.0 ) ) / ( ( 2.0 * PI ) ) ) * ( 16.0 * 1023000.0 ) );
    msg->pwr_gln = (tU16)pwr;

    if(ovfs >= 1000) {
      ovfs -= 1000;
      ovfs |= 0x8;
    }
    msg->flags_gln = 0;
    msg->flags_gln |= ((tU8)ovfs << NOTCH_OVERFLOWS_BIT);
    msg->flags_gln |= ((tU16)mode << NOTCH_MODE_BITS);
    if(lock_en != 0)
    {
      msg->flags_gln |= (1U << NOTCH_LOCK_BIT);
    }
  }

  frameQ = frame_ack_qualifier(parms->class_Id, parms->msg_Id, rspSize, ONLY_ONE_FRAME);
  outputprocess_notch_filter_status_send(msg, frameQ );
}


static void stbin_output_read_errors(const stbin_output_msg_parms *parms)
{
	stbin_status_t result = STBIN_OK;
	frame_qualifier_t frameQ;

  PREPARE_OUTPUT_MESSAGE(parms->out_buf, outputprocess_read_errors_t, rsp, rspSize);

	if(result==STBIN_OK)
	{
    tU32 error_array[8];
    tU32 returned_params_nb = error_handler_pop(error_array);

	  while (returned_params_nb>0U)
    {
      rsp->error_code = error_array[0];
      rsp->param1 = error_array[2];
      rsp->param2 = error_array[3];
      rsp->param3 = error_array[4];
      rsp->param4 = error_array[5];
      rsp->param5 = error_array[6];
      rsp->param6 = error_array[7];

      frameQ = frame_ack_qualifier(parms->class_Id, parms->msg_Id, rspSize, ONLY_ONE_FRAME);
      outputprocess_read_errors_send(rsp, frameQ );

      returned_params_nb = error_handler_pop(error_array);
    }
  }
}


