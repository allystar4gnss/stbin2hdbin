//!
//!   \file       stbin.h
//!   \brief      <i><b> ST binary module, header file</b></i>
//!   \author     Many
//!   \authors    Many
//!   \version    1.0
//!   \date       2010.09.01
//!   \bug        Unknown
//!   \warning    None
//!   \addtogroup modules
//!   \{
//!

#ifndef STBIN_H
#define STBIN_H

/*****************************************************************************
   includes
*****************************************************************************/
#include "clibs.h"
#include "gnss_api.h"

/*****************************************************************************
   defines and macros
*****************************************************************************/

#undef  STBIN_FRONTEND_SUPPORT
#undef  STBIN_REMOTE_FRONTEND_SUPPORT
#undef  STBIN_ADC_SUPPORT
#undef  STBIN_ANTENNA_SENSING_SUPPORT
#undef  STBIN_NOTCH_SUPPORT
#undef  STBIN_SQI_DATASTORAGE
#undef  STBIN_BINIMG_SUPPORT

#if defined( __STA2062__)
#define STBIN_FRONTEND_SUPPORT
#endif

#if defined( __STA2064__)
#define STBIN_FRONTEND_SUPPORT
#if defined( RCIF_OVER_UART)
#define STBIN_REMOTE_FRONTEND_SUPPORT
#define STBIN_NOTCH_SUPPORT
#endif
#endif

#if defined( __STA8088__)
#define STBIN_FRONTEND_SUPPORT
#define STBIN_ADC_SUPPORT
#define STBIN_ANTENNA_SENSING_SUPPORT
#define STBIN_NOTCH_SUPPORT
#if defined( VERSION_BINARY )
#define STBIN_BINIMG_SUPPORT
#endif
#if defined( NVM_SQI )
#define STBIN_SQI_DATASTORAGE
#endif
#endif

#if defined( __STA8090__)
#define STBIN_FRONTEND_SUPPORT
#define STBIN_ANTENNA_SENSING_SUPPORT
#define STBIN_NOTCH_SUPPORT
#if defined( VERSION_BINARY )
#define STBIN_BINIMG_SUPPORT
#endif
#if defined( NVM_SQI )
#define STBIN_SQI_DATASTORAGE
#endif
#endif

#ifdef STBIN_SQI_DATASTORAGE
#define SQI_BUFFER_SIZE               32U
#define SQI_USER_REGION_OFFSET        0xF0000
#endif

#if defined ( STBIN_ADC_SUPPORT )
#define SVC_ADC_AVERG_MIN             256
#define SVC_ADC_AVERG_MAX             2048
#endif

#define STBIN_MAX_PAYLOAD_SIZE        950U

#define STBIN_FAILED                  0U
#define STBIN_OK                      1U
#define STBIN_NOTFOUND                2U

#define STBIN_GENERAL_ERROR_CLASS_ID        0x00
#define STBIN_OUTPROCESS_CLASS_ID           0x01  ///*ID STBIN OUT PROCESS SERVICE*/
#define STBIN_STAGPS_OUTPROCESS_CLASS_ID    0x02
#define STBIN_WAAS_OUTPROCESS_CLASS_ID      0x03
#define STBIN_DR_OUTPROCESS_CLASS_ID        0x04
#define STBIN_ITF_CONTROL_CLASS_ID          0x12
#define INIT_GNSS_CLASS_ID                  0x20  ///*ID of all init service (EX: init_GPS_params)*/
#define STBIN_READ_CLASS_ID                 0x2A  ///*ID STBIN READ SERVICE */
#define STBIN_SQI_RD_CLASS_ID               0x2B  ///*ID STBIN SQI READ SERVICE */
#define STBIN_WAAS_RD_CLASS_ID              0x2C  ///*ID STBIN WAAS READ SERVICE */
#define STBIN_PPS_RD_CLASS_ID               0x2D  ///*ID STBIN PPS  READ SERVICE */
#define STBIN_DR_READ_CLASS_ID              0x2F  ///*ID STBIN DR READ SERVICE */
#define STBIN_WRITE_CLASS_ID                0x3A  ///*ID STBIN WRITE SERVICE*/
#define STBIN_SQI_WR_CLASS_ID               0x3B  ///*ID STBIN WRITE SQI SERVICE*/
#define STBIN_WAAS_WR_CLASS_ID              0x3C  ///*ID STBIN WRITE WAAS SERVICE*/
#define STBIN_PPS_WR_CLASS_ID               0x3D  ///*ID STBIN WRITE PPS SERVICE*/
#define STBIN_STAGPS_WR_CLASS_ID            0x3E  ///*ID STBIN WRITE STAGPS SERVICE*/
#define STBIN_DR_WRITE_CLASS_ID             0x3F  ///*ID STBIN WRITE DR SERVICE*/
#define STBIN_TEST_CLASS_ID                 0x4A  ///*ID STBIN TEST SERVICE */
#define STBIN_WAAS_TS_CLASS_ID              0x4B  ///*ID STBIN TEST WAAS SERVICE*/
#define STBIN_STAGPS_TEST_CLASS_ID          0x4E  ///*ID STBIN TEST STAGPS SERVICE*/
#define STBIN_DR_TEST_CLASS_ID              0x4F  ///*ID STBIN TEST DR SERVICE*/
#define STBIN_RESET_CLASS_ID                0x5A  ///*ID STBIN RESET SERVICE*/
#define STBIN_STAGPS_CTL_CLASS_ID           0x5E  ///*ID STBIN CONTROL STAGPS SERVICE*/

#define STBIN_MASK(n)         ((tUInt)1U<<n)
#define STBIN_MASK_BANK_0     0U
#define STBIN_MASK_BANK_1     1U

/***************************************************
 Output messages selected in BANK 0
***************************************************/
#define STBIN_MASK_OUTPUT_POS_ECEF       STBIN_MASK( 0)
#define STBIN_MASK_OUTPUT_POS_LLH        STBIN_MASK( 1)
#define STBIN_MASK_OUTPUT_STATUS         STBIN_MASK( 2)
#define STBIN_MASK_OUTPUT_DOP            STBIN_MASK( 3)
#define STBIN_MASK_OUTPUT_VELECEF        STBIN_MASK( 4)
#define STBIN_MASK_OUTPUT_VELNEU         STBIN_MASK( 5)
#define STBIN_MASK_OUTPUT_TIMEGNSS       STBIN_MASK( 6)
#define STBIN_MASK_OUTPUT_TIMEUTC        STBIN_MASK( 7)
#define STBIN_MASK_OUTPUT_SVINFO         STBIN_MASK( 8)
#define STBIN_MASK_OUTPUT_DGPS           STBIN_MASK( 9)
#define STBIN_MASK_OUTPUT_DGPS_DATA      STBIN_MASK(10)
#define STBIN_MASK_OUTPUT_POSRES         STBIN_MASK(11)
#define STBIN_MASK_OUTPUT_VELRES         STBIN_MASK(12)
#define STBIN_MASK_OUTPUT_TS             STBIN_MASK(13)
#define STBIN_MASK_OUTPUT_TG             STBIN_MASK(14)
#define STBIN_MASK_OUTPUT_PA             STBIN_MASK(15)
#define STBIN_MASK_OUTPUT_RF             STBIN_MASK(16)
#define STBIN_MASK_OUTPUT_COV            STBIN_MASK(17)
#define STBIN_MASK_OUTPUT_GST            STBIN_MASK(18)
#define STBIN_MASK_OUTPUT_PPS_DATA       STBIN_MASK(19)
#define STBIN_MASK_OUTPUT_HOLD_DATA      STBIN_MASK(20)
#define STBIN_MASK_OUTPUT_TRAIM_DATA     STBIN_MASK(21)
#define STBIN_MASK_OUTPUT_LOWPOWER_DATA  STBIN_MASK(22)
#define STBIN_MASK_OUTPUT_CPU_DATA       STBIN_MASK(23)
#define STBIN_MASK_OUTPUT_NOTCH_F_STATUS STBIN_MASK(24)
#define STBIN_MASK_OUTPUT_READ_ERRORS    STBIN_MASK(25)
//#define STBIN_MASK_OUTPUT_XXXXX      STBIN_MASK(xx)
//#define STBIN_MASK_OUTPUT_XXXXX      STBIN_MASK(31)

/***************************************************
 Output messages selected in BANK 1
***************************************************/
//#define STBIN_MASK_OUTPUT_XXXXX      STBIN_MASK(0)
//#define STBIN_MASK_OUTPUT_XXXXX      STBIN_MASK(xx)
#define STAGPS_STBIN_MASK_OUTPUT_AGPS_GPS     STBIN_MASK( 8)
#define STAGPS_STBIN_MASK_OUTPUT_AGPS_GLONASS STBIN_MASK( 9)
//#define STBIN_MASK_OUTPUT_XXXXX      STBIN_MASK(xx)
#define WAAS_STBIN_MASK_OUTPUT_SBAS           STBIN_MASK(16)
#define WAAS_STBIN_MASK_OUTPUT_SBAS_DATA      STBIN_MASK(17)
//#define STBIN_MASK_OUTPUT_XXXXX      STBIN_MASK(xx)
#define STBIN_MASK_OUTPUT_TEST_RF             STBIN_MASK(31)

/****************************************************************
 Scaling factors for fixed point numbers representation
 ****************************************************************/
/* 16 bits numbers */
#define  SCALING_Q15    32768.0
#define  SCALING_Q1_14  16384.0
#define  SCALING_Q2_13  8192.0
#define  SCALING_Q3_12  4096.0
#define  SCALING_Q10_5  32.0

/* 8 bits numbers */
#define  SCALING_Q8     256

/****************************************************************
 Scaling factors
 ****************************************************************/

#define SCALING_10             10.0
#define SCALING_100            100.0
#define SCALING_1000           1000.0
#define SCALING_1000000        1000000.0
#define SCALING_10000000       10000000.0
#define SCALING_100000000      100000000.0
#define SCALING_1000000000     1000000000.0
#define SCALING_KILO           1000.0
#define SCALING_MEGA           SCALING_1000000
#define SCALING_GIGA           SCALING_1000000000
#define SCALING_LAT_LON        SCALING_10000000
#define SCALING_HEIGHT         1000.0

#define RESERVED_U32           0x00000000
#define RESERVED_U16           0x0000
#define RESERVED_U8            0x00

#if ( defined(__linux__) && (__BYTE_ORDER != __BIG_ENDIAN) ) || ( (! defined(__linux__)) && (! defined(__BIG_ENDIAN)) )
#define STBIN_FROM_LINK_ENDIAN_CONV_double(addr)
#define STBIN_FROM_LINK_ENDIAN_CONV_uShort(addr)
#define STBIN_FROM_LINK_ENDIAN_CONV_short(addr)
#define STBIN_FROM_LINK_ENDIAN_CONV_uInt(addr)
#define STBIN_FROM_LINK_ENDIAN_CONV_int(addr)

#define STBIN_FROM_LINK_ENDIAN_CONV_tDouble(addr)
#define STBIN_FROM_LINK_ENDIAN_CONV_tU16(addr)
#define STBIN_FROM_LINK_ENDIAN_CONV_tS16(addr)
#define STBIN_FROM_LINK_ENDIAN_CONV_tU32(addr)
#define STBIN_FROM_LINK_ENDIAN_CONV_tS32(addr)

#define STBIN_TO_LINK_ENDIAN_CONV_uShort(addr)
#define STBIN_TO_LINK_ENDIAN_CONV_short(addr)
#define STBIN_TO_LINK_ENDIAN_CONV_uInt(addr)
#define STBIN_TO_LINK_ENDIAN_CONV_int(addr)
#define STBIN_TO_LINK_ENDIAN_CONV_double(addr)
#define STBIN_TO_LINK_ENDIAN_CONV_uShort_ARRAY(addr,nb)

#define STBIN_TO_LINK_ENDIAN_CONV_tU16(addr)
#define STBIN_TO_LINK_ENDIAN_CONV_tS16(addr)
#define STBIN_TO_LINK_ENDIAN_CONV_tU32(addr)
#define STBIN_TO_LINK_ENDIAN_CONV_tS32(addr)
#define STBIN_TO_LINK_ENDIAN_CONV_tDouble(addr)
#define STBIN_TO_LINK_ENDIAN_CONV_tU16_ARRAY(addr,nb)

#else
#  error CONVERSION MACRO FOR BIG ENDIAN MUST BE DEFINED
#endif

#define PREPARE_OUTPUT_MESSAGE(outBuf, type, bufName, lenName) \
  /*lint -e{9087} cast performed between a pointer to object type and a pointer to a different object type */ \
  type *bufName = (type *)(outBuf); \
  tUInt  lenName = type ## _size_send

/*****************************************************************************
   typedefs and structures
*****************************************************************************/

typedef tU32    (*stbin_inout_t)      ( tChar *, tU32, gpOS_clock_t*);

typedef tU8     stbin_status_t;

typedef struct {
  tUChar *  out_buf;
  tUChar    class_Id;
  tUChar    msg_Id;
} stbin_req_msg_parms;

typedef struct {
  tUInt     currTow_mills;
  tUInt     currTow_nanos;
  tUChar *  outBuf;
  void *    fix_data;
} stbin_outProcess_input;

typedef struct {
  tUChar *  out_buf;
  void*     data_p;
  tUInt     currTow_mills;
  tUInt     currTow_nanos;
  tUChar    class_Id;
  tUChar    msg_Id;
} stbin_output_msg_parms;

typedef struct {
  void (* const gen)  (const stbin_output_msg_parms *parms);
  const tU32  mask;
  const tU8   mask_bank;
  const tU8   msg_Id;
} stbin_output_msg_def;

typedef enum frames_status_e
{
  ONLY_ONE_FRAME                 = 0xC0,
  START_OF_SEVERAL_FRAMES        = 0x80,
  MIDDLE_OF_SEVERAL_FRAMES       = 0x00,
  END_OF_SEVERAL_FRAMES          = 0x40
} frame_status_t;

typedef tU32 frame_qualifier_t;

/*Response type - ACK or NACK */
typedef enum ack_nack_status_e
{
	NACK = 0x00,
	ACK  = 0x20
} ack_nack_status_t;

/*****************************************************************************
   exported variables
*****************************************************************************/

/*****************************************************************************
   exported function prototypes
*****************************************************************************/

extern void               Send_ACKorNACK              ( ack_nack_status_t, const stbin_req_msg_parms *);
extern void               _stbin_msg_send             ( tUChar *buf, tUInt msg_len, frame_qualifier_t frameQ );
extern void               Send_General_Read_Response  ( tU16 , tUChar *, const stbin_req_msg_parms *);
extern gnss_error_t       stbin_init_p                ( gpOS_partition_t *, stbin_inout_t, stbin_inout_t, tU32 *);
extern frame_qualifier_t  frame_ack_qualifier         ( tUChar cid, tUChar mid, tUInt msg_len, frame_status_t frame_status_value);
extern stbin_status_t     stbin_decode_output_process ( tU16 msg_length, tUChar *msg, const stbin_req_msg_parms *parms_in, const stbin_output_msg_def *list, tInt nb_elem);

#endif
