/*****************************************************************************
   FILE:          stbin_plugins_dr.c
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
 * @file    stbin_plugins_dr.c
 * @brief   Plugin for STBIN support of Dead Reckoning
 */

#ifdef DR_CODE_LINKED

/*****************************************************************************
   includes
*****************************************************************************/
#include "clibs.h"
#include "gnss_debug.h"
#include "dr_api.h"
#include "dr_msg.h"
#include "sm_odo.h"
#include "sm_gyro.h"
#include "sm_sampling.h"
#include "sm_3Dgyro.h"
#include "sm_3Dacc.h"
#include "sm_can.h"
#include "dr_plugin.h"
#include "stbin.h"
#include "stbin_dr_gen_structs.h"
#include "stbin_dr_gen_checks.h"

/*****************************************************************************
   external declarations
*****************************************************************************/

/*****************************************************************************
   defines and macros (scope: module-local)
*****************************************************************************/
#define STBIN_MSGID_PSTMDRSAM       0x01
#define STBIN_MSGID_PSTMDRCAN       0x02
#define STBIN_MSGID_PSTM3DACC       0x03
#define STBIN_MSGID_PSTM3DGYRO      0x04
#define STBIN_MSGID_PSTMDRGPS           0x20
#define STBIN_MSGID_PSTMDRSTATE         0x21
#define STBIN_MSGID_PSTMDRDEBUG         0x22
#define STBIN_MSGID_PSTMDRNVM_WRITE     0x23
#define STBIN_MSGID_PSTMDRNVM_READ      0x24
#define STBIN_MSGID_PSTM_KALMAN_INIT    0x25
#define STBIN_MSGID_PSTMDRCOV           0x26
#define STBIN_MSGID_PSTMDRUPD           0x27
#define STBIN_MSGID_PSTMDRSTEP          0x28
#define STBIN_MSGID_PSTMDRTUNNEL        0x29
#define STBIN_MSGID_PSTMDRSTYPE         0x2A
#define STBIN_MSGID_PSTMDRCAL           0x2B
#define STBIN_MSGID_PSTMDRAHRS          0x2D
#define STBIN_MSGID_PSTMDRMMFB          0x2E
#define STBIN_MSGID_SENSOR_ODO_DATA                   0x50
#define STBIN_MSGID_SENSOR_REVERSE_DATA               0x51
#define STBIN_MSGID_SENSOR_ODO_REVERSE_DATA           0x52
#define STBIN_MSGID_SENSOR_GYRO_DATA                  0x53
#define STBIN_MSGID_SENSOR_GYRO_ODO_REV_DATA          0x54
#define STBIN_MSGID_SENSOR_DWP_ODO                    0x55
#define STBIN_MSGID_SENSOR_DWP_2W_F_DATA              0x56
#define STBIN_MSGID_SENSOR_DWP_2W_F_REV_DATA          0x57
#define STBIN_MSGID_SENSOR_DWP_2W_R_DATA              0x58
#define STBIN_MSGID_SENSOR_DWP_2W_R_REV_DATA          0x59
#define STBIN_MSGID_SENSOR_DWP_4W_DATA                0x5A
#define STBIN_MSGID_SENSOR_DWP_4W_REV_DATA            0x5B
#define STBIN_MSGID_SENSOR_IGNITION_DATA              0x5B
#define STBIN_MSGID_SENSOR_SPEED_DATA                 0x5C
#define STBIN_MSGID_SENSOR_DWP_ODO_SPEED              0x5D
#define STBIN_MSGID_SENSOR_DWP_2W_F_SPEED_DATA        0x5E
#define STBIN_MSGID_SENSOR_DWP_2W_F_REV_SPEED_DATA    0x5F
#define STBIN_MSGID_SENSOR_DWP_2W_R_SPEED_DATA        0x60
#define STBIN_MSGID_SENSOR_DWP_2W_R_REV_SPEED_DATA    0x61
#define STBIN_MSGID_SENSOR_DWP_4W_SPEED_DATA          0x62
#define STBIN_MSGID_SENSOR_DWP_4W_REV_SPEED_DATA      0x63
#define STBIN_MSGID_SENSOR_TEMPERATURE                0x64
#define STBIN_MSGID_SENSOR_3A_ACC_DATA                0x65
#define STBIN_MSGID_SENSOR_3A_GYRO_DATA               0x66
#define STBIN_MSGID_SENSOR_MOUNT_ANGLES_DATA          0x67
#define STBIN_MSGID_SENSOR_RESET_ODO_COUNTER          0x68
#define STBIN_MSGID_SENSOR_UNKNOWN_ID           0xF0

/*****************************************************************************
   typedefs and structures (scope: module-local)
*****************************************************************************/

/*****************************************************************************
   global variable definitions  (scope: module-exported)
*****************************************************************************/

/*****************************************************************************
   global variable definitions (scope: module-local)
*****************************************************************************/

static dr_plugin_handler_t *dr_plugin_handler;

/*****************************************************************************
   function prototypes (scope: module-local)
*****************************************************************************/

/*****************************************************************************
   function implementations (scope: module-local)
*****************************************************************************/

static void send_stbin_DR_3Dgyro_MSG_msg(stbin_output_msg_parms *parms)
{
  sm_3Dgyro_sample_t dr_3Dgyro_msg;

  while(sm_3Dgyro_receive_sample(&dr_3Dgyro_msg) == gpOS_SUCCESS)
  {
  	if(TRUE == dr_plugin_handler->pstmdr_msg_enable)
    {
      PREPARE_OUTPUT_MESSAGE(parms->out_buf, output_dr_3d_gyro_sample_t, msg, rspSize);
      frame_qualifier_t frameQ;

      msg->timestamp = dr_3Dgyro_msg.slld_3Dgyro_sample.gyro_3D_cpu_time;
      msg->odometer = dr_3Dgyro_msg.odo_sample.odo_count;
      msg->rawX = (tShort)dr_3Dgyro_msg.slld_3Dgyro_sample.gyro_3D_x_data;
      msg->rawY = (tShort)dr_3Dgyro_msg.slld_3Dgyro_sample.gyro_3D_y_data;
      msg->rawZ = (tShort)dr_3Dgyro_msg.slld_3Dgyro_sample.gyro_3D_z_data;
      msg->rev = dr_3Dgyro_msg.odo_sample.reverse;

      frameQ = frame_ack_qualifier(parms->class_Id, parms->msg_Id, rspSize, ONLY_ONE_FRAME);
      output_dr_3d_gyro_sample_send(msg, frameQ );
    }
  }
}

static void send_stbin_DR_3Dacc_MSG_msg(stbin_output_msg_parms *parms)
{
  slld_3Dacc_sample_t dr_3Dacc_msg;

  while(sm_3Dacc_receive_sample(&dr_3Dacc_msg) == gpOS_SUCCESS)
  {
  	if(TRUE == dr_plugin_handler->pstmdr_msg_enable)
    {
      PREPARE_OUTPUT_MESSAGE(parms->out_buf, output_dr_3d_accel_sample_t, msg, rspSize);
      frame_qualifier_t frameQ;

      msg->timestamp = dr_3Dacc_msg.acc_3D_cpu_time;
      msg->rawX = (tShort)dr_3Dacc_msg.acc_3D_x_data;
      msg->rawY = (tShort)dr_3Dacc_msg.acc_3D_y_data;
      msg->rawZ = (tShort)dr_3Dacc_msg.acc_3D_z_data;

      frameQ = frame_ack_qualifier(parms->class_Id, parms->msg_Id, rspSize, ONLY_ONE_FRAME);
      output_dr_3d_accel_sample_send(msg, frameQ );
    }
  }
}

static void send_stbin_DR_CAN_MSG_msg(stbin_output_msg_parms *parms)
{
  sm_can_msg_t dr_can_msg;

  while(sm_can_receive_message(&dr_can_msg) == gpOS_SUCCESS)
  {
  	if(TRUE == dr_plugin_handler->pstmdr_msg_enable)
    {
      PREPARE_OUTPUT_MESSAGE(parms->out_buf, output_dr_can_sample_t, msg, rspSize);
      frame_qualifier_t frameQ;

      msg->timestamp = dr_can_msg.can_cpu_time;
      msg->carMaker = dr_can_msg.car_maker_id;
      msg->canObjId = dr_can_msg.can_obj_id;
      _clibs_memcpy(&(msg->canData[0]), &(dr_can_msg.can_msg[0]), SM_CAN_MSG_PAYLOAD);

      frameQ = frame_ack_qualifier(parms->class_Id, parms->msg_Id, rspSize, ONLY_ONE_FRAME);
      output_dr_can_sample_send(msg, frameQ );
    }
  }

}

static void send_stbin_DR_analog_MSG_msg(stbin_output_msg_parms *parms)
{
  sm_analog_sample_t dr_analog_msg;

  while(sm_analog_receive_sample(&dr_analog_msg) == gpOS_SUCCESS)
  {
    PREPARE_OUTPUT_MESSAGE(parms->out_buf, output_dr_sensor_sample_t, msg, rspSize);
    frame_qualifier_t frameQ;

    msg->timestamp = dr_analog_msg.cpu_time;
    msg->gyroRate = dr_analog_msg.gyro_volts;
    msg->odometer = dr_analog_msg.odo_count;
    msg->rev = dr_analog_msg.reverse;

    frameQ = frame_ack_qualifier(parms->class_Id, parms->msg_Id, rspSize, ONLY_ONE_FRAME);
    output_dr_sensor_sample_send(msg, frameQ );
  }
}

static void send_stbin_PSTMDRGPS_msg(const dr_msg_gps_sample_t *gps_sample, stbin_output_msg_parms *parms)
{
  PREPARE_OUTPUT_MESSAGE(parms->out_buf, output_dr_fix_metrics_t, msg, rspSize);
  frame_qualifier_t frameQ;

	msg->lon = gps_sample->lat * SCALING_LAT_LON;
	msg->lat = gps_sample->lon * SCALING_LAT_LON;
	msg->velN = SCALING_1000 * (MCR_FP32_QM_TO_DOUBLE(gps_sample->vn,DR_MSG_DOUBLE_2_FP_FRACT14));
	msg->velE = SCALING_1000 * (MCR_FP32_QM_TO_DOUBLE(gps_sample->ve,DR_MSG_DOUBLE_2_FP_FRACT14));
	msg->velU = SCALING_1000 * (MCR_FP32_QM_TO_DOUBLE(gps_sample->vv,DR_MSG_DOUBLE_2_FP_FRACT14));
	msg->rms_vel_res = SCALING_10 * (MCR_FP32_QM_TO_DOUBLE(gps_sample->rms_vel_residual,DR_MSG_DOUBLE_2_FP_FRACT14));
	msg->rms_pos_res = SCALING_10 * (MCR_FP32_QM_TO_DOUBLE(gps_sample->rms_pos_residual,DR_MSG_DOUBLE_2_FP_FRACT14));
	msg->pdop = MCR_FP32_QM_TO_DOUBLE(gps_sample->pdop,DR_MSG_DOUBLE_2_FP_FRACT14);
	msg->vdop = MCR_FP32_QM_TO_DOUBLE(gps_sample->vdop,DR_MSG_DOUBLE_2_FP_FRACT14);
	msg->hdop = MCR_FP32_QM_TO_DOUBLE(gps_sample->hdop,DR_MSG_DOUBLE_2_FP_FRACT14);

  frameQ = frame_ack_qualifier(parms->class_Id, parms->msg_Id, rspSize, ONLY_ONE_FRAME);
  output_dr_fix_metrics_send(msg, frameQ );
}

static void send_stbin_DRSAM_msg(const dr_sample_t *dr_sample, stbin_output_msg_parms *parms)
{
  PREPARE_OUTPUT_MESSAGE(parms->out_buf, output_dr_sensor_sample_t, msg, rspSize);
  frame_qualifier_t frameQ;

  msg->timestamp = dr_sample->cpu_time;
  msg->gyroRate = dr_sample->gyro_volts;
  msg->odometer = dr_sample->odo_count;
  msg->rev = dr_sample->reverse;

  frameQ = frame_ack_qualifier(parms->class_Id, parms->msg_Id, rspSize, ONLY_ONE_FRAME);
  output_dr_sensor_sample_send(msg, frameQ );
}

static void send_stbin_DRSTATE_msg(const dr_msg_state_t *state, stbin_output_msg_parms *parms)
{
  PREPARE_OUTPUT_MESSAGE(parms->out_buf, output_dr_kalman_state_t, msg, rspSize);
  frame_qualifier_t frameQ;

  msg->timestamp = state->cpu_time;
  msg->lon = SCALING_LAT_LON * (MCR_FP32_QM_TO_DOUBLE(state->lon,DR_MSG_DOUBLE_2_FP_FRACT23));
  msg->lat = SCALING_LAT_LON * (MCR_FP32_QM_TO_DOUBLE(state->lat,DR_MSG_DOUBLE_2_FP_FRACT24));
  msg->heading = SCALING_1000 * (MCR_FP32_QM_TO_DOUBLE(state->heading,DR_MSG_DOUBLE_2_FP_FRACT23));
  msg->speed = SCALING_1000 * (MCR_FP32_QM_TO_DOUBLE(state->speed,DR_MSG_DOUBLE_2_FP_FRACT24));
  msg->gyro_offset = SCALING_1000 * (MCR_FP32_QM_TO_DOUBLE(state->gyro_offset,DR_MSG_DOUBLE_2_FP_FRACT24));
  msg->gyro_gain = SCALING_1000 * (MCR_FP32_QM_TO_DOUBLE(state->gyro_offset,DR_MSG_DOUBLE_2_FP_FRACT24));
  msg->odo_scale = SCALING_1000 * (MCR_FP32_QM_TO_DOUBLE(state->odo_scale,DR_MSG_DOUBLE_2_FP_FRACT24));
  msg->gyro_ovst = SCALING_1000 * (MCR_FP32_QM_TO_DOUBLE(state->gyro_ovst,DR_MSG_DOUBLE_2_FP_FRACT24));

  frameQ = frame_ack_qualifier(parms->class_Id, parms->msg_Id, rspSize, ONLY_ONE_FRAME);
  output_dr_kalman_state_send(msg, frameQ );
}

static void send_stbin_DRDEBUG_msg(const dr_debug_t *debug, stbin_output_msg_parms *parms)
{
  PREPARE_OUTPUT_MESSAGE(parms->out_buf, output_dr_debug_info_t, msg, rspSize);
  frame_qualifier_t frameQ;

  msg->lon_err = SCALING_LAT_LON * debug->lon_error;
  msg->lat_err = SCALING_LAT_LON * debug->lat_error;
  msg->heading_err = SCALING_1000 * debug->heading_error;
  msg->speed_err = SCALING_1000 * debug->speed_error;

  frameQ = frame_ack_qualifier(parms->class_Id, parms->msg_Id, rspSize, ONLY_ONE_FRAME);
  output_dr_debug_info_send(msg, frameQ );
}

static void send_stbin_DR_NVM_W_msg(stbin_output_msg_parms *parms)
{
  PREPARE_OUTPUT_MESSAGE(parms->out_buf, output_dr_kalman_nvm_write_t, msg, rspSize);
  frame_qualifier_t frameQ;
  dr_status_backup_t dr_status_backup;

  dr_get_status_backup(&dr_status_backup);

  msg->state_lon = SCALING_LAT_LON * dr_status_backup.dr_state_copy.lon;
  msg->state_lat = SCALING_LAT_LON * dr_status_backup.dr_state_copy.lat;
  msg->state_heading = SCALING_1000 * dr_status_backup.dr_state_copy.heading;
  msg->state_gyro_offset = SCALING_1000 * dr_status_backup.dr_state_copy.gyro_offset;
  msg->state_gyro_gain = SCALING_1000 * dr_status_backup.dr_state_copy.gyro_gain;
  msg->state_odo_scale = SCALING_1000 * dr_status_backup.dr_state_copy.odo_scale;
  msg->state_gyro_ovst = SCALING_1000 * dr_status_backup.dr_state_copy.gyro_ovst;
  msg->sdev_lon = SCALING_LAT_LON * dr_status_backup.std_dev_copy.lon;
  msg->sdev_lat = SCALING_LAT_LON * dr_status_backup.std_dev_copy.lat;
  msg->sdev_heading = SCALING_1000 * dr_status_backup.std_dev_copy.heading;
  msg->sdev_gyro_offset = SCALING_1000 * dr_status_backup.std_dev_copy.gyro_offset;
  msg->sdev_gyro_gain = SCALING_1000 * dr_status_backup.std_dev_copy.gyro_gain;
  msg->sdev_odo_scale = SCALING_1000 * dr_status_backup.std_dev_copy.odo_scale;
  msg->sdev_gyro_ovst = SCALING_1000 * dr_status_backup.std_dev_copy.gyro_ovst;
  msg->temperature = SCALING_1000 * dr_status_backup.temperature;
  msg->angle_pitch = SCALING_1000 * dr_status_backup.tilt_angles.pitch;
  msg->angle_roll = SCALING_1000 * dr_status_backup.tilt_angles.roll;
  msg->angle_yaw = SCALING_1000 * dr_status_backup.tilt_angles.yaw;
  msg->calib_flags =  (dr_status_backup.dr_calib_status.gyro_offset_calib<<2)|
                      (dr_status_backup.dr_calib_status.gyro_gain_calib  <<1)|
                      (dr_status_backup.dr_calib_status.odo_scale_calib    );

  frameQ = frame_ack_qualifier(parms->class_Id, parms->msg_Id, rspSize, ONLY_ONE_FRAME);
  output_dr_kalman_nvm_write_send(msg, frameQ );
}

static void send_stbin_DR_NVM_R_msg(stbin_output_msg_parms *parms)
{
  PREPARE_OUTPUT_MESSAGE(parms->out_buf, output_dr_kalman_nvm_read_t, msg, rspSize);
  frame_qualifier_t frameQ;
  dr_status_backup_t dr_status_backup;

  dr_get_status_backup(&dr_status_backup);

  msg->state_lon = SCALING_LAT_LON * dr_status_backup.dr_state_copy.lon;
  msg->state_lat = SCALING_LAT_LON * dr_status_backup.dr_state_copy.lat;
  msg->state_heading = SCALING_1000 * dr_status_backup.dr_state_copy.heading;
  msg->state_gyro_offset = SCALING_1000 * dr_status_backup.dr_state_copy.gyro_offset;
  msg->state_gyro_gain = SCALING_1000 * dr_status_backup.dr_state_copy.gyro_gain;
  msg->state_odo_scale = SCALING_1000 * dr_status_backup.dr_state_copy.odo_scale;
  msg->state_gyro_ovst = SCALING_1000 * dr_status_backup.dr_state_copy.gyro_ovst;
  msg->sdev_lon = SCALING_LAT_LON * dr_status_backup.std_dev_copy.lon;
  msg->sdev_lat = SCALING_LAT_LON * dr_status_backup.std_dev_copy.lat;
  msg->sdev_heading = SCALING_1000 * dr_status_backup.std_dev_copy.heading;
  msg->sdev_gyro_offset = SCALING_1000 * dr_status_backup.std_dev_copy.gyro_offset;
  msg->sdev_gyro_gain = SCALING_1000 * dr_status_backup.std_dev_copy.gyro_gain;
  msg->sdev_odo_scale = SCALING_1000 * dr_status_backup.std_dev_copy.odo_scale;
  msg->sdev_gyro_ovst = SCALING_1000 * dr_status_backup.std_dev_copy.gyro_ovst;
  msg->temperature = SCALING_1000 * dr_status_backup.temperature;
  msg->angle_pitch = SCALING_1000 * dr_status_backup.tilt_angles.pitch;
  msg->angle_roll = SCALING_1000 * dr_status_backup.tilt_angles.roll;
  msg->angle_yaw = SCALING_1000 * dr_status_backup.tilt_angles.yaw;
  msg->calib_flags =  (dr_status_backup.dr_calib_status.gyro_offset_calib<<2)|
                      (dr_status_backup.dr_calib_status.gyro_gain_calib  <<1)|
                      (dr_status_backup.dr_calib_status.odo_scale_calib    );

  frameQ = frame_ack_qualifier(parms->class_Id, parms->msg_Id, rspSize, ONLY_ONE_FRAME);
  output_dr_kalman_nvm_read_send(msg, frameQ );
}

static void send_stbin_DR_KALMAN_INIT_msg(stbin_output_msg_parms *parms)
{
  dr_status_backup_t dr_status_backup;

  PREPARE_OUTPUT_MESSAGE(parms->out_buf, output_dr_kalman_init_t, msg, rspSize);
  frame_qualifier_t frameQ;

  dr_get_status_backup(&dr_status_backup);

  msg->state_lon = SCALING_LAT_LON * dr_status_backup.dr_state_copy.lon;
  msg->state_lat = SCALING_LAT_LON * dr_status_backup.dr_state_copy.lat;
  msg->state_heading = SCALING_1000 * dr_status_backup.dr_state_copy.heading;
  msg->state_gyro_offset = SCALING_1000 * dr_status_backup.dr_state_copy.gyro_offset;
  msg->state_gyro_gain = SCALING_1000 * dr_status_backup.dr_state_copy.gyro_gain;
  msg->state_odo_scale = SCALING_1000 * dr_status_backup.dr_state_copy.odo_scale;
  msg->state_gyro_ovst = SCALING_1000 * dr_status_backup.dr_state_copy.gyro_ovst;
  msg->sdev_lon = SCALING_LAT_LON * dr_status_backup.std_dev_copy.lon;
  msg->sdev_lat = SCALING_LAT_LON * dr_status_backup.std_dev_copy.lat;
  msg->sdev_heading = SCALING_1000 * dr_status_backup.std_dev_copy.heading;
  msg->sdev_gyro_offset = SCALING_1000 * dr_status_backup.std_dev_copy.gyro_offset;
  msg->sdev_gyro_gain = SCALING_1000 * dr_status_backup.std_dev_copy.gyro_gain;
  msg->sdev_odo_scale = SCALING_1000 * dr_status_backup.std_dev_copy.odo_scale;
  msg->sdev_gyro_ovst = SCALING_1000 * dr_status_backup.std_dev_copy.gyro_ovst;
  msg->temperature = SCALING_1000 * dr_status_backup.temperature;
  msg->angle_pitch = SCALING_1000 * dr_status_backup.tilt_angles.pitch;
  msg->angle_roll = SCALING_1000 * dr_status_backup.tilt_angles.roll;
  msg->angle_yaw = SCALING_1000 * dr_status_backup.tilt_angles.yaw;
  msg->calib_flags =  (dr_status_backup.dr_calib_status.gyro_offset_calib<<2)|
                      (dr_status_backup.dr_calib_status.gyro_gain_calib  <<1)|
                      (dr_status_backup.dr_calib_status.odo_scale_calib    );

  frameQ = frame_ack_qualifier(parms->class_Id, parms->msg_Id, rspSize, ONLY_ONE_FRAME);
  output_dr_kalman_init_send(msg, frameQ );
}

static void send_stbin_DRCOV_msg(const dr_msg_kalman_stddev_t *stddev, stbin_output_msg_parms *parms)
{
  PREPARE_OUTPUT_MESSAGE(parms->out_buf, output_dr_cov_t, msg, rspSize);
  frame_qualifier_t frameQ;

  msg->sdev_lon = SCALING_LAT_LON * (MCR_FP32_QM_TO_DOUBLE(stddev->lon,DR_MSG_DOUBLE_2_FP_FRACT08));
  msg->sdev_lat = SCALING_LAT_LON * (MCR_FP32_QM_TO_DOUBLE(stddev->lat,DR_MSG_DOUBLE_2_FP_FRACT08));
  msg->sdev_heading = SCALING_1000 * (MCR_FP32_QM_TO_DOUBLE(stddev->heading,DR_MSG_DOUBLE_2_FP_FRACT18));
  msg->sdev_gyro_offset = SCALING_1000 * ((MCR_FP32_QM_TO_DOUBLE(stddev->gyro_offset,DR_MSG_DOUBLE_2_FP_FRACT18)))*OFFS_SCALE;
  msg->sdev_gyro_gain = SCALING_1000 * ((MCR_FP32_QM_TO_DOUBLE(stddev->gyro_gain,DR_MSG_DOUBLE_2_FP_FRACT18)))*GAIN_SCALE;
  msg->sdev_odo_scale = SCALING_1000 * ((MCR_FP32_QM_TO_DOUBLE(stddev->odo_scale,DR_MSG_DOUBLE_2_FP_FRACT18)))*SCALE_SCALE;
  msg->sdev_gyro_ovst = SCALING_1000 * ((MCR_FP32_QM_TO_DOUBLE(stddev->gyro_ovst,DR_MSG_DOUBLE_2_FP_FRACT18)));

  frameQ = frame_ack_qualifier(parms->class_Id, parms->msg_Id, rspSize, ONLY_ONE_FRAME);
  output_dr_cov_send(msg, frameQ );
}

static void send_stbin_DRUPDATE_msg(const dr_msg_state_t *update, stbin_output_msg_parms *parms)
{
  PREPARE_OUTPUT_MESSAGE(parms->out_buf, output_dr_kalman_update_t, msg, rspSize);
  frame_qualifier_t frameQ;

  msg->lon = SCALING_LAT_LON * (MCR_FP32_QM_TO_DOUBLE(update->lon,DR_MSG_DOUBLE_2_FP_FRACT18));
  msg->lat = SCALING_LAT_LON * (MCR_FP32_QM_TO_DOUBLE(update->lat,DR_MSG_DOUBLE_2_FP_FRACT18));
  msg->heading = SCALING_1000 * (MCR_FP32_QM_TO_DOUBLE(update->heading,DR_MSG_DOUBLE_2_FP_FRACT18));
  msg->gyro_offset = SCALING_1000 * (MCR_FP32_QM_TO_DOUBLE(update->gyro_offset,DR_MSG_DOUBLE_2_FP_FRACT23))*OFFS_SCALE;
  msg->gyro_gain = SCALING_1000 * (MCR_FP32_QM_TO_DOUBLE(update->gyro_gain,DR_MSG_DOUBLE_2_FP_FRACT23))*GAIN_SCALE;
  msg->odo_scale = SCALING_1000 * (MCR_FP32_QM_TO_DOUBLE(update->odo_scale,DR_MSG_DOUBLE_2_FP_FRACT23))*SCALE_SCALE;
  msg->gyro_ovst = SCALING_1000 * (MCR_FP32_QM_TO_DOUBLE(update->gyro_ovst,DR_MSG_DOUBLE_2_FP_FRACT23));

  frameQ = frame_ack_qualifier(parms->class_Id, parms->msg_Id, rspSize, ONLY_ONE_FRAME);
  output_dr_kalman_update_send(msg, frameQ );
}

static void send_stbin_DRSTEP_msg(const dr_msg_step_t *step, stbin_output_msg_parms *parms)
{
  PREPARE_OUTPUT_MESSAGE(parms->out_buf, output_dr_integrator_step_t, msg, rspSize);
  frame_qualifier_t frameQ;

  msg->ave_gyro_volts = step->yaw_rate_volts;
  msg->gyro_noise = step->gyro_noise;
  msg->tot_odo_step = step->tot_odo_step;
  msg->delta_odo_count = step->final_odo_count - step->initial_odo_count;
  msg->sample_count = step->sample_count;
  msg->delta_cputime = step->cpu_delta_time;
  msg->delta_cputime2 = step->final_cpu_time - step->initial_cpu_time;
  msg->valid_odo = step->valid_odo;

  frameQ = frame_ack_qualifier(parms->class_Id, parms->msg_Id, rspSize, ONLY_ONE_FRAME);
  output_dr_integrator_step_send(msg, frameQ );
}

static void send_stbin_DRTUNNEL_msg(const dr_msg_kal_tunnel_t *tunnel, stbin_output_msg_parms *parms)
{
  PREPARE_OUTPUT_MESSAGE(parms->out_buf, output_dr_tunnel_t, msg, rspSize);
  frame_qualifier_t frameQ;

  msg->heading_error = SCALING_1000 * MCR_FP32_QM_TO_DOUBLE(tunnel->head_error,DR_MSG_DOUBLE_2_FP_FRACT14);
  msg->yaw_rate_error = SCALING_1000 * MCR_FP32_QM_TO_DOUBLE(tunnel->yaw_rate_error,DR_MSG_DOUBLE_2_FP_FRACT14);
  msg->gyro_calib_error = MCR_FP32_QM_TO_DOUBLE(tunnel->calib_error,DR_MSG_DOUBLE_2_FP_FRACT14);
  msg->gyro_noise_error = MCR_FP32_QM_TO_DOUBLE(tunnel->noise_error,DR_MSG_DOUBLE_2_FP_FRACT14);
  msg->length = MCR_FP32_QM_TO_DOUBLE(tunnel->length,DR_MSG_DOUBLE_2_FP_FRACT14);
  msg->duration = tunnel->duration;
  msg->pos_error_DR = MCR_FP32_QM_TO_DOUBLE(tunnel->pos_error,DR_MSG_DOUBLE_2_FP_FRACT14);
  msg->pos_error_percent = MCR_FP32_QM_TO_DOUBLE(tunnel->pos_error_perc,DR_MSG_DOUBLE_2_FP_FRACT14);
  msg->exit = tunnel->exit;

  frameQ = frame_ack_qualifier(parms->class_Id, parms->msg_Id, rspSize, ONLY_ONE_FRAME);
  output_dr_tunnel_send(msg, frameQ );
}

static void send_stbin_DRSTYPE_msg(const sm_sensor_type_t* sens_type, stbin_output_msg_parms *parms)
{
  PREPARE_OUTPUT_MESSAGE(parms->out_buf, output_sm_sensor_type_t, msg, rspSize);
  frame_qualifier_t frameQ;

  msg->sensor_type = *sens_type;

  frameQ = frame_ack_qualifier(parms->class_Id, parms->msg_Id, rspSize, ONLY_ONE_FRAME);
  output_dr_sensor_type_send(msg, frameQ );
}

static void send_stbin_DRCAL_msg(const dr_msg_calib_flags_t* dr_cal, stbin_output_msg_parms *parms)
{
  PREPARE_OUTPUT_MESSAGE(parms->out_buf, output_dr_calib_t, msg, rspSize);
  frame_qualifier_t frameQ;

  msg->calib_flags = 0;
  if(TRUE == dr_cal->odo_is_calib)
    msg->calib_flags |= 0x01;
  if(TRUE == dr_cal->gyro_gain_is_calib)
    msg->calib_flags |= 0x02;
  if(TRUE == dr_cal->gyro_offset_is_calib)
    msg->calib_flags |= 0x04;
  if((TRUE == dr_cal->odo_is_calib)&&
     (TRUE == dr_cal->gyro_gain_is_calib)&&
     (TRUE == dr_cal->gyro_offset_is_calib))
    msg->calib_flags |= 0x80;

  frameQ = frame_ack_qualifier(parms->class_Id, parms->msg_Id, rspSize, ONLY_ONE_FRAME);
  output_dr_calib_send(msg, frameQ );
}

static void send_stbin_DRAHRS_msg(const dr_msg_ahrs_t* dr_ahrs, stbin_output_msg_parms *parms)
{
  PREPARE_OUTPUT_MESSAGE(parms->out_buf, output_dr_ahrs_t, msg, rspSize);
  frame_qualifier_t frameQ;

  msg->angle_pitch    = SCALING_1000 * dr_ahrs->tilt_angles.pitch;
  msg->angle_roll     = SCALING_1000 * dr_ahrs->tilt_angles.roll;
  msg->angle_yaw      = SCALING_1000 * dr_ahrs->tilt_angles.yaw;
  msg->slope          = SCALING_1000 * dr_ahrs->slope;
  msg->slope_accuracy = SCALING_1000 * dr_ahrs->slope_accuracy;
  msg->delta_height   = SCALING_1000 * dr_ahrs->delta_height;

  frameQ = frame_ack_qualifier(parms->class_Id, parms->msg_Id, rspSize, ONLY_ONE_FRAME);
  output_dr_ahrs_send(msg, frameQ );
}

static void send_stbin_MMFB_msg(const dr_msg_mmfb_t* dr_mmfb, stbin_output_msg_parms *parms)
{
  tUInt hhmmss = (tUInt)dr_mmfb->utc;
  tUInt ms;
  PREPARE_OUTPUT_MESSAGE(parms->out_buf, output_dr_mmfb_t, msg, rspSize);
  frame_qualifier_t frameQ;

  ms = (tUInt)((dr_mmfb->utc - (tDouble)hhmmss)*1000);

  msg->hhmmss = hhmmss;
  msg->ms = ms;
  msg->lon = SCALING_LAT_LON * dr_mmfb->lon;
  msg->lat = SCALING_LAT_LON * dr_mmfb->lat;
  msg->height = SCALING_1000 * MCR_FP32_QM_TO_DOUBLE( dr_mmfb->height, DR_MSG_DOUBLE_2_FP_FRACT14 );
  msg->heading = SCALING_1000 * MCR_FP32_QM_TO_DOUBLE( dr_mmfb->heading, DR_MSG_DOUBLE_2_FP_FRACT14 );
  msg->height_err = SCALING_1000 * MCR_FP32_QM_TO_DOUBLE( dr_mmfb->height_error, DR_MSG_DOUBLE_2_FP_FRACT14 );
  msg->heading_err = SCALING_1000 * MCR_FP32_QM_TO_DOUBLE( dr_mmfb->heading_error, DR_MSG_DOUBLE_2_FP_FRACT23);
  msg->lon_err = SCALING_LAT_LON * MCR_FP32_QM_TO_DOUBLE( dr_mmfb->lon_error, DR_MSG_DOUBLE_2_FP_FRACT14 );
  msg->lat_err = SCALING_LAT_LON * MCR_FP32_QM_TO_DOUBLE( dr_mmfb->lat_error, DR_MSG_DOUBLE_2_FP_FRACT14 );
  msg->validity_flags = dr_mmfb->validity & 0xF;

  frameQ = frame_ack_qualifier(parms->class_Id, parms->msg_Id, rspSize, ONLY_ONE_FRAME);
  output_dr_mmfb_send(msg, frameQ );
}

static void send_stbin_DR_MSG_SENSORS_msg(const sm_sensors_msg_t *dr_sensors_msg, stbin_output_msg_parms *parms)
{
  frame_qualifier_t frameQ;

  switch(dr_sensors_msg->msg_id)
  {
    case SM_ODO_DATA_MSG_ID:
    {
      PREPARE_OUTPUT_MESSAGE(parms->out_buf, output_dr_sensor_odo_data_t, msg, rspSize);
      parms->msg_Id = STBIN_MSGID_SENSOR_ODO_DATA;

      msg->timestamp = dr_sensors_msg->cpu_time;
      msg->odometer = dr_sensors_msg->msg_data.odo.counter;
      frameQ = frame_ack_qualifier(parms->class_Id, parms->msg_Id, rspSize, ONLY_ONE_FRAME);
      output_dr_sensor_odo_data_send(msg, frameQ );
    }
    break;
    case SM_REV_DATA_MSG_ID:
    {
      PREPARE_OUTPUT_MESSAGE(parms->out_buf, output_dr_sensor_rev_data_t, msg, rspSize);
      parms->msg_Id = STBIN_MSGID_SENSOR_REVERSE_DATA;

      msg->timestamp = dr_sensors_msg->cpu_time;
      msg->rev = dr_sensors_msg->msg_data.rev.status;
      frameQ = frame_ack_qualifier(parms->class_Id, parms->msg_Id, rspSize, ONLY_ONE_FRAME);
      output_dr_sensor_rev_data_send(msg, frameQ );
    }
    break;
    case SM_ODO_REV_DATA_MSG_ID:
    {
      PREPARE_OUTPUT_MESSAGE(parms->out_buf, output_dr_sensor_odo_rev_data_t, msg, rspSize);
      parms->msg_Id = STBIN_MSGID_SENSOR_ODO_REVERSE_DATA;

      msg->timestamp = dr_sensors_msg->cpu_time;
      msg->odometer = dr_sensors_msg->msg_data.odo_rev.odo_counter;
      msg->rev      = dr_sensors_msg->msg_data.odo_rev.rev_status;

      frameQ = frame_ack_qualifier(parms->class_Id, parms->msg_Id, rspSize, ONLY_ONE_FRAME);
      output_dr_sensor_odo_rev_data_send(msg, frameQ );
    }
    break;
    case SM_GYRO_DATA_MSG_ID:
    {
      PREPARE_OUTPUT_MESSAGE(parms->out_buf, output_dr_sensor_gyro_data_t, msg, rspSize);
      parms->msg_Id = STBIN_MSGID_SENSOR_GYRO_DATA;

      msg->timestamp = dr_sensors_msg->cpu_time;
      msg->gyroRate = dr_sensors_msg->msg_data.gyro.volts;

      frameQ = frame_ack_qualifier(parms->class_Id, parms->msg_Id, rspSize, ONLY_ONE_FRAME);
      output_dr_sensor_gyro_data_send(msg, frameQ );
    }
    break;
    case SM_GYRO_ODO_REV_DATA_MSG_ID:
    {
      PREPARE_OUTPUT_MESSAGE(parms->out_buf, output_dr_sensor_gyro_odo_rev_t, msg, rspSize);
      parms->msg_Id = STBIN_MSGID_SENSOR_GYRO_ODO_REV_DATA;

      msg->timestamp = dr_sensors_msg->cpu_time;
      msg->gyroRate = dr_sensors_msg->msg_data.gyro_odo_rev.gyro_volts;
      msg->odometer = dr_sensors_msg->msg_data.gyro_odo_rev.odo_counter;
      msg->rev      = dr_sensors_msg->msg_data.gyro_odo_rev.rev_status;

      frameQ = frame_ack_qualifier(parms->class_Id, parms->msg_Id, rspSize, ONLY_ONE_FRAME);
      output_dr_sensor_gyro_odo_rev_send(msg, frameQ );
    }
    break;
    case SM_DWP_2W_F_DATA_MSG_ID:
    break;
    case SM_DWP_2W_F_REV_DATA_MSG_ID:
    break;
  	case SM_DWP_2W_F_SPEED_DATA_MSG_ID:
    break;
    case SM_DWP_2W_F_REV_SPEED_DATA_MSG_ID:
    break;
    case SM_DWP_2W_R_DATA_MSG_ID:
    {
      PREPARE_OUTPUT_MESSAGE(parms->out_buf, output_dr_sensor_2w_r_data_t, msg, rspSize);
      parms->msg_Id = STBIN_MSGID_SENSOR_DWP_2W_R_DATA;

      msg->timestamp = dr_sensors_msg->cpu_time;
      msg->left_wheel = dr_sensors_msg->msg_data.dwp_2w.left_wheel;
      msg->right_wheel = dr_sensors_msg->msg_data.dwp_2w.right_wheel;

      frameQ = frame_ack_qualifier(parms->class_Id, parms->msg_Id, rspSize, ONLY_ONE_FRAME);
      output_dr_sensor_2w_r_data_send(msg, frameQ );
    }
    break;
    case SM_DWP_2W_R_REV_DATA_MSG_ID:
    {
      PREPARE_OUTPUT_MESSAGE(parms->out_buf, output_dr_sensor_2w_r_rev_data_t, msg, rspSize);
      parms->msg_Id = STBIN_MSGID_SENSOR_DWP_2W_R_REV_DATA;

      msg->timestamp = dr_sensors_msg->cpu_time;
      msg->left_wheel  = dr_sensors_msg->msg_data.dwp_2w_rev.left_wheel;
      msg->right_wheel = dr_sensors_msg->msg_data.dwp_2w_rev.right_wheel;
      msg->rev_flags = 0;
      if(dr_sensors_msg->msg_data.dwp_2w_rev.left_wheel_dir)
        msg->rev_flags |= 0x01;
      if(dr_sensors_msg->msg_data.dwp_2w_rev.right_wheel_dir)
        msg->rev_flags |= 0x02;
      frameQ = frame_ack_qualifier(parms->class_Id, parms->msg_Id, rspSize, ONLY_ONE_FRAME);
      output_dr_sensor_2w_r_rev_data_send(msg, frameQ );
    }
    break;
	case SM_DWP_2W_R_SPEED_DATA_MSG_ID:
    {
      PREPARE_OUTPUT_MESSAGE(parms->out_buf, output_dr_sensor_2w_r_speed_data_t, msg, rspSize);
      parms->msg_Id = STBIN_MSGID_SENSOR_DWP_2W_R_SPEED_DATA;

      msg->timestamp = dr_sensors_msg->cpu_time;
      msg->left_wheel_speed  = dr_sensors_msg->msg_data.dwp_2w.left_wheel_speed;
      msg->right_wheel_speed = dr_sensors_msg->msg_data.dwp_2w.right_wheel_speed;
      frameQ = frame_ack_qualifier(parms->class_Id, parms->msg_Id, rspSize, ONLY_ONE_FRAME);
      output_dr_sensor_2w_r_speed_data_send(msg, frameQ );
    }
    break;
    case SM_DWP_2W_R_REV_SPEED_DATA_MSG_ID:
    {
      PREPARE_OUTPUT_MESSAGE(parms->out_buf, output_dr_sensor_2w_r_rev_speed_data_t, msg, rspSize);
      parms->msg_Id = STBIN_MSGID_SENSOR_DWP_2W_R_REV_SPEED_DATA;

      msg->timestamp = dr_sensors_msg->cpu_time;
      msg->left_wheel_speed  = dr_sensors_msg->msg_data.dwp_2w_rev.left_wheel_speed;
      msg->right_wheel_speed = dr_sensors_msg->msg_data.dwp_2w_rev.right_wheel_speed;
      msg->rev_flags = 0;
      if(dr_sensors_msg->msg_data.dwp_2w_rev.left_wheel_dir)
        msg->rev_flags |= 0x01;
      if(dr_sensors_msg->msg_data.dwp_2w_rev.right_wheel_dir)
        msg->rev_flags |= 0x02;

      frameQ = frame_ack_qualifier(parms->class_Id, parms->msg_Id, rspSize, ONLY_ONE_FRAME);
      output_dr_sensor_2w_r_rev_speed_data_send(msg, frameQ );
    }
    break;
    case SM_DWP_4W_DATA_MSG_ID:
    {
      PREPARE_OUTPUT_MESSAGE(parms->out_buf, output_dr_sensor_4w_data_t, msg, rspSize);
      parms->msg_Id = STBIN_MSGID_SENSOR_DWP_4W_DATA;

      msg->timestamp = dr_sensors_msg->cpu_time;
      msg->front_left_wheel  = dr_sensors_msg->msg_data.dwp_4w.front_left_wheel;
      msg->front_right_wheel = dr_sensors_msg->msg_data.dwp_4w.front_right_wheel;
      msg->rear_left_wheel   = dr_sensors_msg->msg_data.dwp_4w.rear_left_wheel;
      msg->rear_right_wheel  = dr_sensors_msg->msg_data.dwp_4w.rear_right_wheel;

      frameQ = frame_ack_qualifier(parms->class_Id, parms->msg_Id, rspSize, ONLY_ONE_FRAME);
      output_dr_sensor_4w_data_send(msg, frameQ );
    }
    break;
    case SM_DWP_4W_REV_DATA_MSG_ID:
    {
      PREPARE_OUTPUT_MESSAGE(parms->out_buf, output_dr_sensor_4w_rev_data_t, msg, rspSize);
      parms->msg_Id = STBIN_MSGID_SENSOR_DWP_4W_REV_DATA;

      msg->timestamp = dr_sensors_msg->cpu_time;
      msg->front_left_wheel  = dr_sensors_msg->msg_data.dwp_4w_rev.front_left_wheel;
      msg->front_right_wheel = dr_sensors_msg->msg_data.dwp_4w_rev.front_right_wheel;
      msg->rear_left_wheel   = dr_sensors_msg->msg_data.dwp_4w_rev.rear_left_wheel;
      msg->rear_right_wheel  = dr_sensors_msg->msg_data.dwp_4w_rev.rear_right_wheel;
      msg->rev_flags = 0;
      if(dr_sensors_msg->msg_data.dwp_4w_rev.front_left_wheel_dir)
        msg->rev_flags |= 0x01;
      if(dr_sensors_msg->msg_data.dwp_4w_rev.front_right_wheel_dir)
        msg->rev_flags |= 0x02;
      if(dr_sensors_msg->msg_data.dwp_4w_rev.rear_left_wheel_dir)
        msg->rev_flags |= 0x04;
      if(dr_sensors_msg->msg_data.dwp_4w_rev.rear_right_wheel_dir)
        msg->rev_flags |= 0x08;

      frameQ = frame_ack_qualifier(parms->class_Id, parms->msg_Id, rspSize, ONLY_ONE_FRAME);
      output_dr_sensor_4w_rev_data_send(msg, frameQ );
    }
    break;
	case SM_DWP_4W_SPEED_DATA_MSG_ID:
    {
      PREPARE_OUTPUT_MESSAGE(parms->out_buf, output_dr_sensor_4w_speed_t, msg, rspSize);
      parms->msg_Id = STBIN_MSGID_SENSOR_DWP_4W_SPEED_DATA;

      msg->timestamp = dr_sensors_msg->cpu_time;
      msg->front_left_wheel_speed  = dr_sensors_msg->msg_data.dwp_4w.front_left_wheel_speed;
      msg->front_right_wheel_speed = dr_sensors_msg->msg_data.dwp_4w.front_right_wheel_speed;
      msg->rear_left_wheel_speed  = dr_sensors_msg->msg_data.dwp_4w.rear_left_wheel_speed;
      msg->rear_right_wheel_speed = dr_sensors_msg->msg_data.dwp_4w.rear_right_wheel_speed;

      frameQ = frame_ack_qualifier(parms->class_Id, parms->msg_Id, rspSize, ONLY_ONE_FRAME);
      output_dr_sensor_4w_speed_send(msg, frameQ );
    }
    break;
    case SM_DWP_4W_REV_SPEED_DATA_MSG_ID:
    {
      PREPARE_OUTPUT_MESSAGE(parms->out_buf, output_dr_sensor_4w_rev_speed_t, msg, rspSize);
      parms->msg_Id = STBIN_MSGID_SENSOR_DWP_4W_REV_SPEED_DATA;

      msg->timestamp = dr_sensors_msg->cpu_time;
      msg->front_left_wheel_speed  = dr_sensors_msg->msg_data.dwp_4w_rev.front_left_wheel_speed;
      msg->front_right_wheel_speed = dr_sensors_msg->msg_data.dwp_4w_rev.front_right_wheel_speed;
      msg->rear_left_wheel_speed  = dr_sensors_msg->msg_data.dwp_4w_rev.rear_left_wheel_speed;
      msg->rear_right_wheel_speed = dr_sensors_msg->msg_data.dwp_4w_rev.rear_right_wheel_speed;
      msg->rev_flags = 0;
      if(dr_sensors_msg->msg_data.dwp_4w_rev.front_left_wheel_dir)
        msg->rev_flags |= 0x01;
      if(dr_sensors_msg->msg_data.dwp_4w_rev.front_right_wheel_dir)
        msg->rev_flags |= 0x02;
      if(dr_sensors_msg->msg_data.dwp_4w_rev.rear_left_wheel_dir)
        msg->rev_flags |= 0x04;
      if(dr_sensors_msg->msg_data.dwp_4w_rev.rear_right_wheel_dir)
        msg->rev_flags |= 0x08;

      frameQ = frame_ack_qualifier(parms->class_Id, parms->msg_Id, rspSize, ONLY_ONE_FRAME);
      output_dr_sensor_4w_rev_speed_send(msg, frameQ );
    }
    break;
    case SM_IGNITION_DATA_MSG_ID:
    break;
    case SM_SPEED_DATA_MSG_ID:
    {
      PREPARE_OUTPUT_MESSAGE(parms->out_buf, output_dr_sensor_speed_data_t, msg, rspSize);
      parms->msg_Id = STBIN_MSGID_SENSOR_SPEED_DATA;

      msg->timestamp = dr_sensors_msg->cpu_time;
      msg->speed_kmh = dr_sensors_msg->msg_data.speed.value_kmh;
      frameQ = frame_ack_qualifier(parms->class_Id, parms->msg_Id, rspSize, ONLY_ONE_FRAME);
      output_dr_sensor_speed_data_send(msg, frameQ );
    }
    break;
    case SM_TEMPERATURE_MSG_ID:
    {
      PREPARE_OUTPUT_MESSAGE(parms->out_buf, output_dr_sensor_temperature_data_t, msg, rspSize);
      parms->msg_Id = STBIN_MSGID_SENSOR_TEMPERATURE;

      msg->timestamp = dr_sensors_msg->cpu_time;
      msg->temperature = dr_sensors_msg->msg_data.temperature.value;
      msg->temp_valid = dr_sensors_msg->msg_data.temperature.validity;
      frameQ = frame_ack_qualifier(parms->class_Id, parms->msg_Id, rspSize, ONLY_ONE_FRAME);
      output_dr_sensor_temperature_data_send(msg, frameQ );
    }
    break;
    case SM_3A_GYRO_DATA_MSG_ID:
    {
      PREPARE_OUTPUT_MESSAGE(parms->out_buf, output_dr_sensor_3a_gyro_data_t, msg, rspSize);
      parms->msg_Id = STBIN_MSGID_SENSOR_3A_GYRO_DATA;

      msg->timestamp = dr_sensors_msg->cpu_time;
      msg->x_volts = dr_sensors_msg->msg_data.gyro_3a.xvolts;
      msg->y_volts = dr_sensors_msg->msg_data.gyro_3a.yvolts;
      msg->z_volts = dr_sensors_msg->msg_data.gyro_3a.zvolts;

      frameQ = frame_ack_qualifier(parms->class_Id, parms->msg_Id, rspSize, ONLY_ONE_FRAME);
      output_dr_sensor_3a_gyro_data_send(msg, frameQ );
    }
    break;
    case SM_3A_ACC_DATA_MSG_ID:
    {
      PREPARE_OUTPUT_MESSAGE(parms->out_buf, output_dr_sensor_3a_acc_data_t, msg, rspSize);
      parms->msg_Id = STBIN_MSGID_SENSOR_3A_ACC_DATA;

      msg->timestamp = dr_sensors_msg->cpu_time;
      msg->x_volts = dr_sensors_msg->msg_data.acc_3a.xvolts;
      msg->y_volts = dr_sensors_msg->msg_data.acc_3a.yvolts;
      msg->z_volts = dr_sensors_msg->msg_data.acc_3a.zvolts;

      frameQ = frame_ack_qualifier(parms->class_Id, parms->msg_Id, rspSize, ONLY_ONE_FRAME);
      output_dr_sensor_3a_acc_data_send(msg, frameQ );
    }
    break;
    case SM_RESET_ODO_COUNTER_MSG_ID:
    {
      PREPARE_OUTPUT_MESSAGE(parms->out_buf, output_dr_sensor_odo_counter_t, msg, rspSize);
      parms->msg_Id = STBIN_MSGID_SENSOR_RESET_ODO_COUNTER;

      msg->timestamp = dr_sensors_msg->cpu_time;

      frameQ = frame_ack_qualifier(parms->class_Id, parms->msg_Id, rspSize, ONLY_ONE_FRAME);
      output_dr_sensor_odo_counter_send(msg, frameQ );
    }
    break;
    default:
    {
      PREPARE_OUTPUT_MESSAGE(parms->out_buf, output_dr_sensor_unknown_id_t, msg, rspSize);
      parms->msg_Id = STBIN_MSGID_SENSOR_UNKNOWN_ID;

      msg->unknown_id = dr_sensors_msg->msg_id;

      frameQ = frame_ack_qualifier(parms->class_Id, parms->msg_Id, rspSize, ONLY_ONE_FRAME);
      output_dr_sensor_unknown_id_send(msg, frameQ );
    }
    break;
  }

}

/*****************************************************************************
   function implementations (scope: module-exported)
*****************************************************************************/

stbin_status_t stbin_dr_plugin_cmdif_parse(tU16 msg_length, tUChar *msg, const stbin_req_msg_parms *parms)
{
  stbin_status_t rc = STBIN_NOTFOUND;

#if 0
  switch(parms->class_Id)
  {
/*================== WRITE CMD =============================*/
  case STBIN_DR_WRITE_CLASS_ID:
	  rc = dr_stbin_Decode_DR_WRITE_req(msg_length, msg, parms);
    break;

/*================== READ CMD =============================*/
  case STBIN_DR_READ_CLASS_ID:
	  rc = dr_stbin_Decode_READ_DR_req(msg_length, msg, parms);
    break;

/*================== TEST CMD =============================*/
  case STBIN_DR_TEST_CLASS_ID:
    rc = dr_stbin_Decode_TEST_DR_req(msg_length, msg, parms);
   break;

/*=================OUTPUT POLLED CMD RESPONSE===============*/
  case STBIN_DR_OUTPROCESS_CLASS_ID:
	  rc = dr_stbin_decode_output_process(msg_length, msg, parms);
    break;

  default://send nack if received a unknown class_id
	  rc = STBIN_NOTFOUND;
    break;
	}
#endif

	return rc;
}

void stbin_dr_plugin_outmsg_transmit(const tU32 *msg_list, const stbin_outProcess_input *in)
{
  dr_debug_msg_t dr_msg;
  static dr_msg_gps_sample_t dr_msg_gps_sample_copy;
	stbin_output_msg_parms parms;

  parms.currTow_mills = in->currTow_mills;
  parms.currTow_nanos = in->currTow_nanos;
	parms.class_Id = STBIN_DR_OUTPROCESS_CLASS_ID;
	parms.data_p = in->fix_data;
  parms.out_buf = in->outBuf;

  if(FALSE == dr_fix_is_extrapolated())
  {

    /* Read and transmit sensor queues */
    parms.msg_Id = STBIN_MSGID_PSTMDRSAM;
    send_stbin_DR_analog_MSG_msg(&parms);

    parms.msg_Id = STBIN_MSGID_PSTMDRCAN;
    send_stbin_DR_CAN_MSG_msg(&parms);

    parms.msg_Id = STBIN_MSGID_PSTM3DACC;
    send_stbin_DR_3Dacc_MSG_msg(&parms);

    parms.msg_Id = STBIN_MSGID_PSTM3DGYRO;
    send_stbin_DR_3Dgyro_MSG_msg(&parms);

    /* Read and transmit dr process queue */
    while(dr_msg_read(&dr_msg) == TRUE)
    {
      if(TRUE != dr_plugin_handler->pstmdr_msg_enable)
        continue;

      switch (dr_msg.type)
      {
        case DR_MSG_GPS_ID :
          parms.msg_Id = STBIN_MSGID_PSTMDRGPS;
          send_stbin_PSTMDRGPS_msg(&dr_msg.data.sample.gps_sample, &parms);
          _clibs_memcpy(&dr_msg_gps_sample_copy, &dr_msg.data.sample.gps_sample, sizeof( dr_msg_gps_sample_t ) );
        break;
        case DR_MSG_SAMPLE_ID :
          parms.msg_Id = STBIN_MSGID_PSTMDRSAM;
          send_stbin_DRSAM_msg(&dr_msg.data.sample.dr_sample, &parms);
        break;
        case DR_MSG_STATE_ID :
          parms.msg_Id = STBIN_MSGID_PSTMDRSTATE;
          send_stbin_DRSTATE_msg(&dr_msg.data.sample.dr_state, &parms);
        break;
        case DR_MSG_DEBUG_ID :
          parms.msg_Id = STBIN_MSGID_PSTMDRDEBUG;
          send_stbin_DRDEBUG_msg(&dr_msg.data.sample.dr_debug, &parms);
        break;
        case DR_MSG_NVM_WRITE_ID:
          parms.msg_Id = STBIN_MSGID_PSTMDRNVM_WRITE;
          send_stbin_DR_NVM_W_msg(&parms);
        break;
        case DR_MSG_NVM_READ_ID:
          parms.msg_Id = STBIN_MSGID_PSTMDRNVM_READ;
			   send_stbin_DR_NVM_R_msg(&parms);
        break;
        case DR_MSG_SENSORS_ID:
          // parms.msg_Id will be initialize according to id inside payload
          send_stbin_DR_MSG_SENSORS_msg(&dr_msg.data.sample.dr_sensors_msg, &parms);
        break;
        case DR_MSG_KALMAN_INIT_ID:
          parms.msg_Id = STBIN_MSGID_PSTM_KALMAN_INIT;
          send_stbin_DR_KALMAN_INIT_msg(&parms);
        break;
        case DR_MSG_COV_ID :
          parms.msg_Id = STBIN_MSGID_PSTMDRCOV;
          send_stbin_DRCOV_msg(&dr_msg.data.sample.dr_covariance, &parms);
        break;
        case DR_MSG_UPDATE_ID :
          parms.msg_Id = STBIN_MSGID_PSTMDRUPD;
		      send_stbin_DRUPDATE_msg(&dr_msg.data.sample.dr_update, &parms);
        break;
        case DR_MSG_STEP_ID :
          parms.msg_Id = STBIN_MSGID_PSTMDRSTEP;
			    send_stbin_DRSTEP_msg(&dr_msg.data.sample.dr_step, &parms);
        break;
        case DR_MSG_TUNNEL_ID :
          parms.msg_Id = STBIN_MSGID_PSTMDRTUNNEL;
          send_stbin_DRTUNNEL_msg(&dr_msg.data.sample.dr_tunnel, &parms);
        break;
	      case DR_MSG_SENS_TYPE_ID :
          parms.msg_Id = STBIN_MSGID_PSTMDRSTYPE;
          send_stbin_DRSTYPE_msg(&dr_msg.data.sample.dr_sensor_type, &parms);
        break;
        case DR_MSG_CALIB_FLAGS_ID :
          parms.msg_Id = STBIN_MSGID_PSTMDRCAL;
          send_stbin_DRCAL_msg(&dr_msg.data.sample.dr_calib, &parms);
        break;
        case DR_MSG_AHRS_ID :
          parms.msg_Id = STBIN_MSGID_PSTMDRAHRS;
          send_stbin_DRAHRS_msg(&dr_msg.data.sample.dr_ahrs, &parms);
        break;
        case DR_MSG_MMFB_ID :
          parms.msg_Id = STBIN_MSGID_PSTMDRMMFB;
          send_stbin_MMFB_msg(&dr_msg.data.sample.dr_mmfb, &parms);
        break;
        default :
        break;
  	  }
    }
  }
  if(TRUE == dr_fix_is_extrapolated())
  {
     parms.msg_Id = STBIN_MSGID_PSTMDRGPS;
     send_stbin_PSTMDRGPS_msg(&dr_msg_gps_sample_copy, &parms);
  }
}

void stbin_dr_plugin_init( dr_plugin_handler_t *handler)
{
  dr_plugin_handler = handler;
}

#endif // DR_CODE_LINKED

