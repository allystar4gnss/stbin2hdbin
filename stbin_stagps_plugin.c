/*****************************************************************************
   FILE:          stbin_plugins_stagps.c
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
 * @file    stbin_plugins_stagps.c
 * @brief   Plugin for STBIN support of STAGPS
 */

#ifdef ST_AGPS

/*****************************************************************************
   includes
*****************************************************************************/
#include "gnss_debug.h"
#include "stagps_plugin.h"
#include "st_agps.h"
#include "st_agps_ephmgr.h"
#include "st_agps_testing.h"
#include "stbin.h"
#include "stbin_stagps_gen_structs.h"
#include "stbin_stagps_gen_checks.h"

#if defined PGPS_LOAD_SEED_NMEA
#include "pgps.h"
#endif

/*****************************************************************************
   external declarations
*****************************************************************************/

/*****************************************************************************
   defines and macros (scope: module-local)
*****************************************************************************/
#define STAGPS_STBIN_OUTPUT_AGPS_GPS     0x01
#define STAGPS_STBIN_OUTPUT_AGPS_GLONASS 0x02

/*****************************************************************************
   typedefs and structures (scope: module-local)
*****************************************************************************/
typedef enum
{
	STAGPS_STBIN_WRITE_ONOFF       = 0x01,
}stagps_stbin_write_req;

#ifdef PGPS_LOAD_SEED_NMEA
typedef enum
{
	STAGPS_STBIN_CTL_PASSGEN           = 0x01,
	STAGPS_STBIN_CTL_SATSEED           = 0x02,
	STAGPS_STBIN_CTL_SAT_SEED_NEXT_PRN = 0x03,
}stagps_stbin_ctl_req;
#endif

typedef enum
{
	STAGPS_STBIN_TEST_INVALIDATE              = 0x01,
	STAGPS_STBIN_TEST_REAL_EPH_UPDATE_CNTL    = 0x02,
	STAGPS_STBIN_TEST_PRED_EPH_UPDATE_CNTL    = 0x03,
	STAGPS_STBIN_TEST_GET_STATUS              = 0x04,
	STAGPS_STBIN_TEST_REAL_EPH_UPLOAD         = 0x05,
}stagps_stbin_test_req;


/*****************************************************************************
   global variable definitions  (scope: module-exported)
*****************************************************************************/

/*****************************************************************************
   function prototypes (scope: module-local)
*****************************************************************************/
static void stagps_stbin_outmsg_send_AGPS_GPS    (const stbin_output_msg_parms *parms);
static void stagps_stbin_outmsg_send_AGPS_GLONASS(const stbin_output_msg_parms *parms);

static stbin_status_t stagps_stbin_exec_set_onoff(tU16, tUChar *,const stbin_req_msg_parms *);
static stbin_status_t stagps_stbin_exec_test_invalidate(tU16 , tUChar *, const stbin_req_msg_parms *);
static stbin_status_t stagps_stbin_exec_test_real_eph_update_req(tU16 , tUChar *, const stbin_req_msg_parms *);
static stbin_status_t stagps_stbin_test_use_pred_ephem_req(tU16 , tUChar *, const stbin_req_msg_parms *);
static stbin_status_t stagps_stbin_test_get_status(tU16 , tUChar *, const stbin_req_msg_parms *);
static stbin_status_t stagps_stbin_test_ephems_upload(tU16 , tUChar *, const stbin_req_msg_parms *);
static stbin_status_t stagps_stbin_Decode_WRITE_req(tU16 , tUChar *, const stbin_req_msg_parms *);
static stbin_status_t stagps_stbin_Decode_TEST_req(tU16 , tUChar *, const stbin_req_msg_parms *);
static stbin_status_t stbin_decode_output_process_stagps(tU16 , tUChar *, const stbin_req_msg_parms *);

/*****************************************************************************
   global variable definitions (scope: module-local)
*****************************************************************************/
static const stbin_output_msg_def stagps_stbin_outmsg_stagps_list[] = {
  { stagps_stbin_outmsg_send_AGPS_GPS      , STAGPS_STBIN_MASK_OUTPUT_AGPS_GPS,     STBIN_MASK_BANK_1, STAGPS_STBIN_OUTPUT_AGPS_GPS     },
  { stagps_stbin_outmsg_send_AGPS_GLONASS  , STAGPS_STBIN_MASK_OUTPUT_AGPS_GLONASS, STBIN_MASK_BANK_1, STAGPS_STBIN_OUTPUT_AGPS_GLONASS },
};
#define STAGPS_STBIN_NB_OUTPUT_MSG_IN_LIST     (sizeof(stagps_stbin_outmsg_stagps_list)/sizeof(stagps_stbin_outmsg_stagps_list[0]))

static stagps_plugin_handler_t *stagps_handler;

/*****************************************************************************
   function implementations (scope: module-local)
*****************************************************************************/
static stbin_status_t stagps_stbin_exec_set_onoff(tU16 len, tUChar *msg, const stbin_req_msg_parms *parms_in)
{
	stbin_status_t result = STBIN_OK;

	stbin_stagps_onoff_req_MAP(req, msg, len, &result);

	if(result == STBIN_OK)
	{
    if (req->onOff == 1)
    {
      ST_AGPS_start();
      ST_AGPS_ephmgr_initial_prediction_start();
    }
    else
    {
      ST_AGPS_suspend( ST_AGPS_SUSPEND_IMMEDIATELY);
    }
	}

  return result;
}

#ifdef PGPS_LOAD_SEED_NMEA
static stbin_status_t stagps_stbin_exec_ctl_passgen(tU16 len, tUChar *msg, const stbin_req_msg_parms *parms_in)
{
#if (STBIN_DOC_PASSGEN_ID_LEN != PGPS_PWDGEN_MAX_FIELD_LENGTH)
#  error ID length must be updated
#endif

#if (STBIN_DOC_PASSGEN_PASS_LEN != PASSWORD_LENGTH)
#  error PASS length must be updated
#endif
	stbin_status_t result = STBIN_OK;

	stbin_stagps_ctl_passgen_req_MAP(req, msg, len, &result);

	if(result == STBIN_OK)
	{
    frame_qualifier_t        frameQ;
    PREPARE_OUTPUT_MESSAGE(parms_in->out_buf, stbin_stagps_ctl_passgen_rsp_t, rsp, rspSize);

    // Make sure input string are Null terminated
    req->vendorId[PGPS_PWDGEN_MAX_FIELD_LENGTH-1] = '\0';
    req->deviceId[PGPS_PWDGEN_MAX_FIELD_LENGTH-1] = '\0';
    if (pgps_generate_pwd(req->vendorId, req->deviceId, req->gps_seconds,
                          rsp->password) == FALSE) {
      result = STBIN_FAILED;
    } else {
      frameQ = frame_ack_qualifier(parms_in->class_Id, parms_in->msg_Id, rspSize, ONLY_ONE_FRAME);
      stbin_stagps_ctl_passgen_rsp_send(rsp, frameQ);
    }
  }

  return result;
}

static stbin_status_t stagps_stbin_exec_ctl_satseed(tU16 len, tUChar *msg, const stbin_req_msg_parms *parms_in)
{
#if (STBIN_DOC_SATSEED_MAX_SIZE != (STAGPS_NMEA_PGPSSEEDMAXSIZE / 2))
#  error SATSEED length must be updated
#endif
	stbin_status_t result = STBIN_OK;

	stbin_stagps_ctl_satseed_req_MAP(req, msg, len, &result);

	if(result == STBIN_OK)
	{
    if ((req->prn != gnss_stagps_gnsslib_id_to_sat_id(stagps_handler->sat_idx_counter)) && (req->prn != MIN_GPS_SAT_ID))
    {
      GPS_DEBUG_MSG(("[stbin] error: pgps seed prn in wrong order\r\n"));
      result = STBIN_FAILED;
    }
    else
    {
      if (req->prn == MIN_GPS_SAT_ID)
      {
        stagps_handler->sat_idx_counter = 0;
      }

      if(req->no_seed)
      {
        //GPS_DEBUG_MSG(("[nmea] loading pgps seed empty for prn %d\r\n", prn));
      }
      else
      {
        //GPS_DEBUG_MSG(("[nmea] loading pgps seed from prn %d t0 %d\r\n", prn, seed_t0));
        #if defined (STAGPS_USE_OLD_PGPS_SEED)
        if(pgps_load(req->prn, &(req->seed[0]),
                    req->seed_t0, req->seed_tcur, req->seed_clkid))
        #else
        if (FALSE) // TO BE IMPLEMENTED FOR PGPS7!!!!
        #endif
        {
          #if !defined(PGPS_PARALLEL_PROPAGATION)
          pgps_start();
          #else
          if (req->prn == MAX_GPS_SAT_ID)
          {
            pgps_start();
          }
          #endif
        }
        else
        {
          result = STBIN_FAILED;
        }
      }
    }
  }

  if (result != STBIN_FAILED)
  {
    stagps_handler->sat_idx_counter++;
    if (stagps_handler->sat_idx_counter > stagps_handler->sat_idx_pgps_max)
    {
      stagps_handler->sat_idx_counter = 0;
    }
		/*send ACK*/
		Send_ACKorNACK(ACK, parms_in);
  }

  return result;
}

static stbin_status_t stagps_stbin_exec_ctl_sat_seed_next_prn(tU16 len, tUChar *msg, const stbin_req_msg_parms *parms_in)
{
	stbin_status_t result = STBIN_OK;

	stbin_stagps_ctl_satseed_nextPrn_req_MAP(req, msg, len, &result);

	if(result == STBIN_OK)
	{
  	frame_qualifier_t        frameQ;
    PREPARE_OUTPUT_MESSAGE(parms_in->out_buf, stbin_stagps_ctl_satseed_nextPrn_rsp_t,
                            rsp, rspSize);

    rsp->nextPrn = gnss_stagps_gnsslib_id_to_sat_id(stagps_handler->sat_idx_counter);

    frameQ = frame_ack_qualifier(parms_in->class_Id, parms_in->msg_Id, rspSize, ONLY_ONE_FRAME);
    stbin_stagps_ctl_satseed_nextPrn_rsp_send(rsp, frameQ);
  }

  return result;
}

#endif /* PGPS_LOAD_SEED_NMEA */

static stbin_status_t stagps_stbin_exec_test_invalidate(tU16 len, tUChar *msg, const stbin_req_msg_parms *parms_in)
{
  tInt sat_idx;
	stbin_status_t result = STBIN_OK;

	stbin_stagps_test_invalidate_req_MAP(req, msg, len, &result);

	if(result == STBIN_OK)
	{
    boolean_t suspended = ST_AGPS_suspended();

    if(!suspended)
    {
      ST_AGPS_suspend( ST_AGPS_SUSPEND_IMMEDIATELY);
    }

    for( sat_idx = 0; sat_idx < gnss_get_predicted_linked_sat_ids(); sat_idx++)
    {
      GPS_DEBUG_MSG(("[st-agps-bin/invalidate] Invalidating sat %d, id %d, mask 0x%X\r\n",
            gnss_stagps_gnsslib_id_to_sat_id(sat_idx), sat_idx, req->selectionMask));
      ST_AGPS_invalidate( gnss_stagps_gnsslib_id_to_sat_id(sat_idx), req->selectionMask);
    }

    if(!suspended)
    {
      ST_AGPS_start();
      ST_AGPS_ephmgr_initial_prediction_start();
    }
	}

  return result;
}

static stbin_status_t stagps_stbin_exec_test_real_eph_update_req(tU16 len, tUChar *msg, const stbin_req_msg_parms *parms_in)
{
	stbin_status_t result = STBIN_OK;

	stbin_stagps_test_real_ephem_update_req_MAP(req, msg, len, &result);

	if(result == STBIN_OK)
    ST_AGPS_TST_ephmgr_set_real_ephemeris_update(req->onOff);

  return result;
}

static stbin_status_t stagps_stbin_test_use_pred_ephem_req(tU16 len, tUChar *msg, const stbin_req_msg_parms *parms_in)
{
	stbin_status_t result = STBIN_OK;

  stagps_stbin_test_use_pred_ephem_req_MAP(req, msg, len, &result);

	if(result == STBIN_OK)
    ST_AGPS_TST_ephmgr_set_predicted_ephemeris_update(req->onOff);

  return result;
}

static stbin_status_t stagps_stbin_test_get_status(tU16 len, tUChar *msg, const stbin_req_msg_parms *parms_in)
{
	stbin_status_t result = STBIN_OK;
	frame_qualifier_t        frameQ;

  PREPARE_OUTPUT_MESSAGE(parms_in->out_buf, stagps_stbin_test_get_status_t, rsp, rspSize);

  stagps_stbin_test_get_status_MAP(req, msg, len, &result);

	if(result == STBIN_OK)
	{
	 rsp->status = ST_AGPS_TST_get_state();

   frameQ = frame_ack_qualifier(parms_in->class_Id, parms_in->msg_Id, rspSize, ONLY_ONE_FRAME);
   stagps_stbin_test_get_status_send(rsp, frameQ );
	}
  return result;
}

static stbin_status_t stagps_stbin_test_ephems_upload(tU16 len, tUChar *msg, const stbin_req_msg_parms *parms_in)
{
	stbin_status_t result = STBIN_OK;

  stagps_stbin_test_ephems_upload_MAP(req, msg, len, &result);

	if(result == STBIN_OK)
	{
    if( ST_AGPS_TST_ephmgr_fill_eph(req->dsp_satid, (ephemeris_raw_t*)(&(req->value))))
    {
      /* report error */
      result = STBIN_FAILED;
      GPS_DEBUG_MSG(("STBIN stagps_stbin_test_ephems_upload KO: sat_type %d\r\n",req->dsp_satid));
    }
    else
    {
      GPS_DEBUG_MSG(("STBIN stagps_stbin_test_ephems_upload OK: sat_type %d\r\n",req->dsp_satid));
    }

	}
  return result;
}

static stbin_status_t stagps_stbin_Decode_WRITE_req(tU16 msg_length, tUChar *msg, const stbin_req_msg_parms *parms_in)
{
	stbin_status_t command_EXECUTE_status;

	switch( parms_in->msg_Id )
	{
	  case STAGPS_STBIN_WRITE_ONOFF:
	   	command_EXECUTE_status = stagps_stbin_exec_set_onoff(msg_length, msg, parms_in);
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

static stbin_status_t stagps_stbin_Decode_CONTROL_req(tU16 msg_length, tUChar *msg, const stbin_req_msg_parms *parms_in)
{
	stbin_status_t command_EXECUTE_status;

	switch( parms_in->msg_Id )
	{
#ifdef PGPS_LOAD_SEED_NMEA
	  case STAGPS_STBIN_CTL_PASSGEN:
	   	command_EXECUTE_status = stagps_stbin_exec_ctl_passgen(msg_length, msg, parms_in);
		break;
	  case STAGPS_STBIN_CTL_SATSEED:
	   	command_EXECUTE_status = stagps_stbin_exec_ctl_satseed(msg_length, msg, parms_in);
		break;
	  case STAGPS_STBIN_CTL_SAT_SEED_NEXT_PRN:
	   	command_EXECUTE_status = stagps_stbin_exec_ctl_sat_seed_next_prn(msg_length, msg, parms_in);
		break;
#endif
	  default :
	   	command_EXECUTE_status = STBIN_NOTFOUND;
	  break;
	}

	return command_EXECUTE_status;
}

static stbin_status_t stagps_stbin_Decode_TEST_req(tU16 msg_length, tUChar *msg, const stbin_req_msg_parms *parms_in)
{
	stbin_status_t command_EXECUTE_status;

	switch( parms_in->msg_Id )
	{
         case STAGPS_STBIN_TEST_INVALIDATE:
	   	command_EXECUTE_status = stagps_stbin_exec_test_invalidate(msg_length, msg, parms_in);
		break;
	  case STAGPS_STBIN_TEST_REAL_EPH_UPDATE_CNTL:
	   	command_EXECUTE_status = stagps_stbin_exec_test_real_eph_update_req(msg_length, msg, parms_in);
		break;
          case STAGPS_STBIN_TEST_PRED_EPH_UPDATE_CNTL:
	   	command_EXECUTE_status = stagps_stbin_test_use_pred_ephem_req(msg_length, msg, parms_in);
		break;
		case STAGPS_STBIN_TEST_GET_STATUS:
      command_EXECUTE_status = stagps_stbin_test_get_status(msg_length, msg, parms_in);
      break;
    case STAGPS_STBIN_TEST_REAL_EPH_UPLOAD:
      command_EXECUTE_status = stagps_stbin_test_ephems_upload(msg_length, msg, parms_in);
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

/**/
static stbin_status_t stbin_decode_output_process_stagps(tU16 msg_length, tUChar *msg, const stbin_req_msg_parms *parms_in)
{
  return stbin_decode_output_process(msg_length, msg, parms_in,
                                     stagps_stbin_outmsg_stagps_list, STAGPS_STBIN_NB_OUTPUT_MSG_IN_LIST);
}

#if STAGPS_MAX_LIST_LEN != NB_MAX_STAGPS_SATS_REPORTED
#  error Discrepency detected between frame definition and runtime code
#endif
static void stagps_stbin_outmsg_send_AGPS_GPS(const stbin_output_msg_parms *parms)
{
  tInt sat_cnt = 0;
  tShort i;
  raw_t *raw_data;
  raw_measure_list_t *raw_meas;
  tDouble hdop;
  tDouble pdop;
  tDouble vdop;
  tDouble gdop;
  PREPARE_OUTPUT_MESSAGE(parms->out_buf, outputprocess_stagps_gps_t, msg, rspSize);
  frame_qualifier_t frameQ;

  gnss_fix_get_dops_local(&pdop, &hdop, &vdop, &gdop, parms->data_p);
  msg->fixMode = gnss_fix_get_pos_status_local(parms->data_p);
  msg->pDOP = (tU16)(pdop * SCALING_1000);
  msg->hDOP = (tU16)(hdop * SCALING_1000);
  msg->vDOP = (tU16)(vdop * SCALING_1000);


  raw_meas = gnss_fix_get_raw_measurements_local(parms->data_p);
  raw_data = raw_meas->list;


  for(i = 0; (i < TRK_CHANNELS_SUPPORTED) && (sat_cnt < NB_MAX_STAGPS_SATS_REPORTED); i++)
  {
    if ((raw_meas->chans_used[i])
        && (gnss_sat_id_to_sat_type(raw_data[i].dsp.satid) == GNSS_SAT_TYPE_GPS))
    {
      pred_data_t pred_data;

      gnss_get_ephemeris_predict_params(raw_data[i].dsp.satid,&pred_data);
      msg->ids[sat_cnt] = raw_data[i].dsp.satid;
      if (pred_data.available != 0)
        msg->ages[sat_cnt] = (pred_data.age_h/24) + 1;
      else
        msg->ages[sat_cnt] = -1;

      sat_cnt++;
    }
  }

  msg->cnt = sat_cnt;

  // Clean unused entries
  for(i = sat_cnt; i < NB_MAX_STAGPS_SATS_REPORTED; i++) {
    msg->ids[i] = 0;
    msg->ages[i] = -1;
  }

  frameQ = frame_ack_qualifier(parms->class_Id, parms->msg_Id, rspSize, ONLY_ONE_FRAME);
  outputprocess_stagps_gps_send(msg, frameQ );
}

static void stagps_stbin_outmsg_send_AGPS_GLONASS(const stbin_output_msg_parms *parms)
{
  tInt sat_cnt = 0;
  tShort i;
  raw_t *raw_data;
  raw_measure_list_t *raw_meas;
  tDouble hdop;
  tDouble pdop;
  tDouble vdop;
  tDouble gdop;
  satid_t current_sat_id;
  PREPARE_OUTPUT_MESSAGE(parms->out_buf, outputprocess_stagps_glonass_t, msg, rspSize);
  frame_qualifier_t frameQ;

  gnss_fix_get_dops_local(&pdop, &hdop, &vdop, &gdop, parms->data_p);
  msg->fixMode = gnss_fix_get_pos_status_local(parms->data_p);
  msg->pDOP = (tU16)(pdop * SCALING_1000);
  msg->hDOP = (tU16)(hdop * SCALING_1000);
  msg->vDOP = (tU16)(vdop * SCALING_1000);


  raw_meas = gnss_fix_get_raw_measurements_local(parms->data_p);
  raw_data = raw_meas->list;


  for(i = 0; (i < TRK_CHANNELS_SUPPORTED) && (sat_cnt < NB_MAX_STAGPS_SATS_REPORTED); i++)
  {
    if ((raw_meas->chans_used[i])
        && (gnss_sat_id_to_sat_type(raw_data[i].dsp.satid) == GNSS_SAT_TYPE_GLONASS)
        && (nmea_support_translate_satid(raw_data[i].dsp.satid,&current_sat_id) == GNSS_NO_ERROR))
    {
      pred_data_t pred_data;

      gnss_get_ephemeris_predict_params(raw_data[i].dsp.satid,&pred_data);
      msg->ids[sat_cnt] = current_sat_id;
      if (pred_data.available != 0)
        msg->ages[sat_cnt] = (pred_data.age_h/24) + 1;
      else
        msg->ages[sat_cnt] = -1;

      sat_cnt++;
    }
  }

  msg->cnt = sat_cnt;

  // Clean unused entries
  for(i = sat_cnt; i < NB_MAX_STAGPS_SATS_REPORTED; i++) {
    msg->ids[i] = 0;
    msg->ages[i] = -1;
  }

  frameQ = frame_ack_qualifier(parms->class_Id, parms->msg_Id, rspSize, ONLY_ONE_FRAME);
  outputprocess_stagps_glonass_send(msg, frameQ );
}

/*****************************************************************************
   function implementations (scope: module-exported)
*****************************************************************************/

stbin_status_t stbin_stagps_plugin_cmdif_parse(tU16 msg_length, tUChar *msg, const stbin_req_msg_parms *parms)
{
  stbin_status_t rc;

  switch(parms->class_Id)
  {
/*================== WRITE CMD =============================*/
  case STBIN_STAGPS_WR_CLASS_ID:
	  rc = stagps_stbin_Decode_WRITE_req(msg_length, msg, parms);
    break;

/*================== CONTROL CMD =============================*/
  case STBIN_STAGPS_CTL_CLASS_ID:
	  rc = stagps_stbin_Decode_CONTROL_req(msg_length, msg, parms);
    break;

/*================== TEST CMD =============================*/
  case STBIN_STAGPS_TEST_CLASS_ID:
	  rc = stagps_stbin_Decode_TEST_req(msg_length, msg, parms);
    break;

/*=================OUTPUT POLLED CMD RESPONSE===============*/
  case STBIN_STAGPS_OUTPROCESS_CLASS_ID:
	  rc = stbin_decode_output_process_stagps(msg_length, msg, parms);
    break;

  default://send nack if received a unknown class_id
	  rc = STBIN_NOTFOUND;
    break;
	}

	return rc;
}

void stbin_stagps_plugin_outmsg_transmit (const tU32 *msg_list, const stbin_outProcess_input *in)
{
	stbin_output_msg_parms parms;
	tInt i;

  parms.currTow_mills = in->currTow_mills;
  parms.currTow_nanos = in->currTow_nanos;
	parms.class_Id = STBIN_STAGPS_OUTPROCESS_CLASS_ID;
	parms.data_p = in->fix_data;
  parms.out_buf = in->outBuf;

  for(i=0;i<STAGPS_STBIN_NB_OUTPUT_MSG_IN_LIST;i++)
  {
    if(stagps_stbin_outmsg_stagps_list[i].mask & msg_list[stagps_stbin_outmsg_stagps_list[i].mask_bank])
    {
			parms.msg_Id = stagps_stbin_outmsg_stagps_list[i].msg_Id;
			stagps_stbin_outmsg_stagps_list[i].gen(&parms);
    }
  }
}

void stbin_stagps_plugin_init( stagps_plugin_handler_t *handler)
{
  stagps_handler = handler;
}

#endif // ST_AGPS



