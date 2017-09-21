//This code is automatically generated (See rep_crm/tools/stbin/generators)
#define COMPILER_MIN_ARRAY_SIZE 1U
//Section : DR OUTPUT Messages (ClassId 0x04)
//Send helper
#define output_dr_sensor_sample_send(buff, frameQ) {\
	 output_dr_sensor_sample_t *__msg = buff; \
	STBIN_TO_LINK_ENDIAN_CONV_tU16(&((__msg)->gyroRate)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->odometer)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->timestamp)); \
	_stbin_msg_send((tUChar *)(__msg), \
				output_dr_sensor_sample_t_size_send, \
				frameQ); \
	}

//Test structure size against computed size
typedef tS8 Testoutput_dr_sensor_sample_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(output_dr_sensor_sample_t)-12U)];
typedef tS8 Testoutput_dr_sensor_sample_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+12U-sizeof(output_dr_sensor_sample_t))];


//Send helper
#define output_dr_can_sample_send(buff, frameQ) {\
	 output_dr_can_sample_t *__msg = buff; \
	STBIN_TO_LINK_ENDIAN_CONV_tU16(&((__msg)->canObjId)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU16(&((__msg)->carMaker)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->timestamp)); \
	_stbin_msg_send((tUChar *)(__msg), \
				output_dr_can_sample_t_size_send, \
				frameQ); \
	}

//Test structure size against computed size
typedef tS8 Testoutput_dr_can_sample_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(output_dr_can_sample_t)-16U)];
typedef tS8 Testoutput_dr_can_sample_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+16U-sizeof(output_dr_can_sample_t))];


//Send helper
#define output_dr_3d_accel_sample_send(buff, frameQ) {\
	 output_dr_3d_accel_sample_t *__msg = buff; \
	STBIN_TO_LINK_ENDIAN_CONV_tS16(&((__msg)->rawZ)); \
	STBIN_TO_LINK_ENDIAN_CONV_tS16(&((__msg)->rawY)); \
	STBIN_TO_LINK_ENDIAN_CONV_tS16(&((__msg)->rawX)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->timestamp)); \
	_stbin_msg_send((tUChar *)(__msg), \
				output_dr_3d_accel_sample_t_size_send, \
				frameQ); \
	}

//Test structure size against computed size
typedef tS8 Testoutput_dr_3d_accel_sample_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(output_dr_3d_accel_sample_t)-12U)];
typedef tS8 Testoutput_dr_3d_accel_sample_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+12U-sizeof(output_dr_3d_accel_sample_t))];


//Send helper
#define output_dr_3d_gyro_sample_send(buff, frameQ) {\
	 output_dr_3d_gyro_sample_t *__msg = buff; \
	STBIN_TO_LINK_ENDIAN_CONV_tS16(&((__msg)->rawZ)); \
	STBIN_TO_LINK_ENDIAN_CONV_tS16(&((__msg)->rawY)); \
	STBIN_TO_LINK_ENDIAN_CONV_tS16(&((__msg)->rawX)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->odometer)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->timestamp)); \
	_stbin_msg_send((tUChar *)(__msg), \
				output_dr_3d_gyro_sample_t_size_send, \
				frameQ); \
	}

//Test structure size against computed size
typedef tS8 Testoutput_dr_3d_gyro_sample_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(output_dr_3d_gyro_sample_t)-16U)];
typedef tS8 Testoutput_dr_3d_gyro_sample_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+16U-sizeof(output_dr_3d_gyro_sample_t))];


//Send helper
#define output_dr_fix_metrics_send(buff, frameQ) {\
	 output_dr_fix_metrics_t *__msg = buff; \
	STBIN_TO_LINK_ENDIAN_CONV_tS32(&((__msg)->rms_pos_res)); \
	STBIN_TO_LINK_ENDIAN_CONV_tS32(&((__msg)->rms_vel_res)); \
	STBIN_TO_LINK_ENDIAN_CONV_tS32(&((__msg)->velU)); \
	STBIN_TO_LINK_ENDIAN_CONV_tS32(&((__msg)->velE)); \
	STBIN_TO_LINK_ENDIAN_CONV_tS32(&((__msg)->velN)); \
	STBIN_TO_LINK_ENDIAN_CONV_tS32(&((__msg)->lat)); \
	STBIN_TO_LINK_ENDIAN_CONV_tS32(&((__msg)->lon)); \
	_stbin_msg_send((tUChar *)(__msg), \
				output_dr_fix_metrics_t_size_send, \
				frameQ); \
	}

//Test structure size against computed size
typedef tS8 Testoutput_dr_fix_metrics_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(output_dr_fix_metrics_t)-32U)];
typedef tS8 Testoutput_dr_fix_metrics_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+32U-sizeof(output_dr_fix_metrics_t))];


//Send helper
#define output_dr_kalman_state_send(buff, frameQ) {\
	 output_dr_kalman_state_t *__msg = buff; \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->gyro_ovst)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->odo_scale)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->gyro_gain)); \
	STBIN_TO_LINK_ENDIAN_CONV_tS32(&((__msg)->gyro_offset)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->speed)); \
	STBIN_TO_LINK_ENDIAN_CONV_tS32(&((__msg)->heading)); \
	STBIN_TO_LINK_ENDIAN_CONV_tS32(&((__msg)->lat)); \
	STBIN_TO_LINK_ENDIAN_CONV_tS32(&((__msg)->lon)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->timestamp)); \
	_stbin_msg_send((tUChar *)(__msg), \
				output_dr_kalman_state_t_size_send, \
				frameQ); \
	}

//Test structure size against computed size
typedef tS8 Testoutput_dr_kalman_state_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(output_dr_kalman_state_t)-36U)];
typedef tS8 Testoutput_dr_kalman_state_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+36U-sizeof(output_dr_kalman_state_t))];


//Send helper
#define output_dr_debug_info_send(buff, frameQ) {\
	 output_dr_debug_info_t *__msg = buff; \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->speed_err)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->heading_err)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->lat_err)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->lon_err)); \
	_stbin_msg_send((tUChar *)(__msg), \
				output_dr_debug_info_t_size_send, \
				frameQ); \
	}

//Test structure size against computed size
typedef tS8 Testoutput_dr_debug_info_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(output_dr_debug_info_t)-16U)];
typedef tS8 Testoutput_dr_debug_info_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+16U-sizeof(output_dr_debug_info_t))];


//Send helper
#define output_dr_kalman_nvm_write_send(buff, frameQ) {\
	 output_dr_kalman_nvm_write_t *__msg = buff; \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->angle_yaw)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->angle_roll)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->angle_pitch)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->temperature)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->sdev_gyro_ovst)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->sdev_odo_scale)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->sdev_gyro_gain)); \
	STBIN_TO_LINK_ENDIAN_CONV_tS32(&((__msg)->sdev_gyro_offset)); \
	STBIN_TO_LINK_ENDIAN_CONV_tS32(&((__msg)->sdev_heading)); \
	STBIN_TO_LINK_ENDIAN_CONV_tS32(&((__msg)->sdev_lat)); \
	STBIN_TO_LINK_ENDIAN_CONV_tS32(&((__msg)->sdev_lon)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->state_gyro_ovst)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->state_odo_scale)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->state_gyro_gain)); \
	STBIN_TO_LINK_ENDIAN_CONV_tS32(&((__msg)->state_gyro_offset)); \
	STBIN_TO_LINK_ENDIAN_CONV_tS32(&((__msg)->state_heading)); \
	STBIN_TO_LINK_ENDIAN_CONV_tS32(&((__msg)->state_lat)); \
	STBIN_TO_LINK_ENDIAN_CONV_tS32(&((__msg)->state_lon)); \
	_stbin_msg_send((tUChar *)(__msg), \
				output_dr_kalman_nvm_write_t_size_send, \
				frameQ); \
	}

//Test structure size against computed size
typedef tS8 Testoutput_dr_kalman_nvm_write_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(output_dr_kalman_nvm_write_t)-76U)];
typedef tS8 Testoutput_dr_kalman_nvm_write_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+76U-sizeof(output_dr_kalman_nvm_write_t))];


//Send helper
#define output_dr_kalman_nvm_read_send(buff, frameQ) {\
	 output_dr_kalman_nvm_read_t *__msg = buff; \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->angle_yaw)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->angle_roll)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->angle_pitch)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->temperature)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->sdev_gyro_ovst)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->sdev_odo_scale)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->sdev_gyro_gain)); \
	STBIN_TO_LINK_ENDIAN_CONV_tS32(&((__msg)->sdev_gyro_offset)); \
	STBIN_TO_LINK_ENDIAN_CONV_tS32(&((__msg)->sdev_heading)); \
	STBIN_TO_LINK_ENDIAN_CONV_tS32(&((__msg)->sdev_lat)); \
	STBIN_TO_LINK_ENDIAN_CONV_tS32(&((__msg)->sdev_lon)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->state_gyro_ovst)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->state_odo_scale)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->state_gyro_gain)); \
	STBIN_TO_LINK_ENDIAN_CONV_tS32(&((__msg)->state_gyro_offset)); \
	STBIN_TO_LINK_ENDIAN_CONV_tS32(&((__msg)->state_heading)); \
	STBIN_TO_LINK_ENDIAN_CONV_tS32(&((__msg)->state_lat)); \
	STBIN_TO_LINK_ENDIAN_CONV_tS32(&((__msg)->state_lon)); \
	_stbin_msg_send((tUChar *)(__msg), \
				output_dr_kalman_nvm_read_t_size_send, \
				frameQ); \
	}

//Test structure size against computed size
typedef tS8 Testoutput_dr_kalman_nvm_read_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(output_dr_kalman_nvm_read_t)-76U)];
typedef tS8 Testoutput_dr_kalman_nvm_read_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+76U-sizeof(output_dr_kalman_nvm_read_t))];


//Send helper
#define output_dr_kalman_init_send(buff, frameQ) {\
	 output_dr_kalman_init_t *__msg = buff; \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->angle_yaw)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->angle_roll)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->angle_pitch)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->temperature)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->sdev_gyro_ovst)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->sdev_odo_scale)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->sdev_gyro_gain)); \
	STBIN_TO_LINK_ENDIAN_CONV_tS32(&((__msg)->sdev_gyro_offset)); \
	STBIN_TO_LINK_ENDIAN_CONV_tS32(&((__msg)->sdev_heading)); \
	STBIN_TO_LINK_ENDIAN_CONV_tS32(&((__msg)->sdev_lat)); \
	STBIN_TO_LINK_ENDIAN_CONV_tS32(&((__msg)->sdev_lon)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->state_gyro_ovst)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->state_odo_scale)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->state_gyro_gain)); \
	STBIN_TO_LINK_ENDIAN_CONV_tS32(&((__msg)->state_gyro_offset)); \
	STBIN_TO_LINK_ENDIAN_CONV_tS32(&((__msg)->state_heading)); \
	STBIN_TO_LINK_ENDIAN_CONV_tS32(&((__msg)->state_lat)); \
	STBIN_TO_LINK_ENDIAN_CONV_tS32(&((__msg)->state_lon)); \
	_stbin_msg_send((tUChar *)(__msg), \
				output_dr_kalman_init_t_size_send, \
				frameQ); \
	}

//Test structure size against computed size
typedef tS8 Testoutput_dr_kalman_init_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(output_dr_kalman_init_t)-76U)];
typedef tS8 Testoutput_dr_kalman_init_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+76U-sizeof(output_dr_kalman_init_t))];


//Send helper
#define output_dr_cov_send(buff, frameQ) {\
	 output_dr_cov_t *__msg = buff; \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->sdev_gyro_ovst)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->sdev_odo_scale)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->sdev_gyro_gain)); \
	STBIN_TO_LINK_ENDIAN_CONV_tS32(&((__msg)->sdev_gyro_offset)); \
	STBIN_TO_LINK_ENDIAN_CONV_tS32(&((__msg)->sdev_heading)); \
	STBIN_TO_LINK_ENDIAN_CONV_tS32(&((__msg)->sdev_lat)); \
	STBIN_TO_LINK_ENDIAN_CONV_tS32(&((__msg)->sdev_lon)); \
	_stbin_msg_send((tUChar *)(__msg), \
				output_dr_cov_t_size_send, \
				frameQ); \
	}

//Test structure size against computed size
typedef tS8 Testoutput_dr_cov_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(output_dr_cov_t)-28U)];
typedef tS8 Testoutput_dr_cov_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+28U-sizeof(output_dr_cov_t))];


//Send helper
#define output_dr_kalman_update_send(buff, frameQ) {\
	 output_dr_kalman_update_t *__msg = buff; \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->gyro_ovst)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->odo_scale)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->gyro_gain)); \
	STBIN_TO_LINK_ENDIAN_CONV_tS32(&((__msg)->gyro_offset)); \
	STBIN_TO_LINK_ENDIAN_CONV_tS32(&((__msg)->heading)); \
	STBIN_TO_LINK_ENDIAN_CONV_tS32(&((__msg)->lat)); \
	STBIN_TO_LINK_ENDIAN_CONV_tS32(&((__msg)->lon)); \
	_stbin_msg_send((tUChar *)(__msg), \
				output_dr_kalman_update_t_size_send, \
				frameQ); \
	}

//Test structure size against computed size
typedef tS8 Testoutput_dr_kalman_update_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(output_dr_kalman_update_t)-28U)];
typedef tS8 Testoutput_dr_kalman_update_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+28U-sizeof(output_dr_kalman_update_t))];


//Send helper
#define output_dr_integrator_step_send(buff, frameQ) {\
	 output_dr_integrator_step_t *__msg = buff; \
	STBIN_TO_LINK_ENDIAN_CONV_tU16(&((__msg)->sample_count)); \
	STBIN_TO_LINK_ENDIAN_CONV_tS32(&((__msg)->delta_cputime2)); \
	STBIN_TO_LINK_ENDIAN_CONV_tS32(&((__msg)->delta_cputime)); \
	STBIN_TO_LINK_ENDIAN_CONV_tS32(&((__msg)->delta_odo_count)); \
	STBIN_TO_LINK_ENDIAN_CONV_tS32(&((__msg)->tot_odo_step)); \
	STBIN_TO_LINK_ENDIAN_CONV_tS32(&((__msg)->gyro_noise)); \
	STBIN_TO_LINK_ENDIAN_CONV_tS32(&((__msg)->ave_gyro_volts)); \
	_stbin_msg_send((tUChar *)(__msg), \
				output_dr_integrator_step_t_size_send, \
				frameQ); \
	}

//Test structure size against computed size
typedef tS8 Testoutput_dr_integrator_step_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(output_dr_integrator_step_t)-28U)];
typedef tS8 Testoutput_dr_integrator_step_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+28U-sizeof(output_dr_integrator_step_t))];


//Send helper
#define output_dr_tunnel_send(buff, frameQ) {\
	 output_dr_tunnel_t *__msg = buff; \
	STBIN_TO_LINK_ENDIAN_CONV_tU16(&((__msg)->pos_error_DR)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU16(&((__msg)->duration)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU16(&((__msg)->length)); \
	STBIN_TO_LINK_ENDIAN_CONV_tS32(&((__msg)->gyro_noise_error)); \
	STBIN_TO_LINK_ENDIAN_CONV_tS32(&((__msg)->gyro_calib_error)); \
	STBIN_TO_LINK_ENDIAN_CONV_tS32(&((__msg)->yaw_rate_error)); \
	STBIN_TO_LINK_ENDIAN_CONV_tS32(&((__msg)->heading_error)); \
	_stbin_msg_send((tUChar *)(__msg), \
				output_dr_tunnel_t_size_send, \
				frameQ); \
	}

//Test structure size against computed size
typedef tS8 Testoutput_dr_tunnel_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(output_dr_tunnel_t)-24U)];
typedef tS8 Testoutput_dr_tunnel_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+24U-sizeof(output_dr_tunnel_t))];


//Send helper
#define output_dr_sensor_type_send(buff, frameQ) {\
	 output_sm_sensor_type_t *__msg = buff; \
	_stbin_msg_send((tUChar *)(__msg), \
				output_sm_sensor_type_t_size_send, \
				frameQ); \
	}

//Test structure size against computed size
typedef tS8 Testoutput_dr_sensor_type_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(output_sm_sensor_type_t)-4U)];
typedef tS8 Testoutput_dr_sensor_type_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+4U-sizeof(output_sm_sensor_type_t))];


//Send helper
#define output_dr_calib_send(buff, frameQ) {\
	 output_dr_calib_t *__msg = buff; \
	_stbin_msg_send((tUChar *)(__msg), \
				output_dr_calib_t_size_send, \
				frameQ); \
	}

//Test structure size against computed size
typedef tS8 Testoutput_dr_calib_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(output_dr_calib_t)-4U)];
typedef tS8 Testoutput_dr_calib_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+4U-sizeof(output_dr_calib_t))];


//Send helper
#define output_dr_gyro_offset_send(buff, frameQ) {\
	 output_dr_gyro_offset_t *__msg = buff; \
	STBIN_TO_LINK_ENDIAN_CONV_tS16(&((__msg)->yaw_rate_signal_std_dev)); \
	STBIN_TO_LINK_ENDIAN_CONV_tS32(&((__msg)->temperature_correction)); \
	STBIN_TO_LINK_ENDIAN_CONV_tS32(&((__msg)->calibrated_time)); \
	STBIN_TO_LINK_ENDIAN_CONV_tS32(&((__msg)->error)); \
	STBIN_TO_LINK_ENDIAN_CONV_tS32(&((__msg)->last_stopped_value)); \
	_stbin_msg_send((tUChar *)(__msg), \
				output_dr_gyro_offset_t_size_send, \
				frameQ); \
	}

//Test structure size against computed size
typedef tS8 Testoutput_dr_gyro_offset_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(output_dr_gyro_offset_t)-20U)];
typedef tS8 Testoutput_dr_gyro_offset_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+20U-sizeof(output_dr_gyro_offset_t))];


//Send helper
#define output_dr_ahrs_send(buff, frameQ) {\
	 output_dr_ahrs_t *__msg = buff; \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->delta_height)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->slope_accuracy)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->slope)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->angle_yaw)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->angle_roll)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->angle_pitch)); \
	_stbin_msg_send((tUChar *)(__msg), \
				output_dr_ahrs_t_size_send, \
				frameQ); \
	}

//Test structure size against computed size
typedef tS8 Testoutput_dr_ahrs_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(output_dr_ahrs_t)-24U)];
typedef tS8 Testoutput_dr_ahrs_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+24U-sizeof(output_dr_ahrs_t))];


//Send helper
#define output_dr_mmfb_send(buff, frameQ) {\
	 output_dr_mmfb_t *__msg = buff; \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->lat_err)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->lon_err)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->heading_err)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->height_err)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->heading)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->height)); \
	STBIN_TO_LINK_ENDIAN_CONV_tS32(&((__msg)->lat)); \
	STBIN_TO_LINK_ENDIAN_CONV_tS32(&((__msg)->lon)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->ms)); \
	STBIN_TO_LINK_ENDIAN_CONV_tS32(&((__msg)->hhmmss)); \
	_stbin_msg_send((tUChar *)(__msg), \
				output_dr_mmfb_t_size_send, \
				frameQ); \
	}

//Test structure size against computed size
typedef tS8 Testoutput_dr_mmfb_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(output_dr_mmfb_t)-44U)];
typedef tS8 Testoutput_dr_mmfb_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+44U-sizeof(output_dr_mmfb_t))];


//Send helper
#define output_dr_sensor_odo_data_send(buff, frameQ) {\
	 output_dr_sensor_odo_data_t *__msg = buff; \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->odometer)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->timestamp)); \
	_stbin_msg_send((tUChar *)(__msg), \
				output_dr_sensor_odo_data_t_size_send, \
				frameQ); \
	}

//Test structure size against computed size
typedef tS8 Testoutput_dr_sensor_odo_data_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(output_dr_sensor_odo_data_t)-8U)];
typedef tS8 Testoutput_dr_sensor_odo_data_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+8U-sizeof(output_dr_sensor_odo_data_t))];


//Send helper
#define output_dr_sensor_rev_data_send(buff, frameQ) {\
	 output_dr_sensor_rev_data_t *__msg = buff; \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->timestamp)); \
	_stbin_msg_send((tUChar *)(__msg), \
				output_dr_sensor_rev_data_t_size_send, \
				frameQ); \
	}

//Test structure size against computed size
typedef tS8 Testoutput_dr_sensor_rev_data_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(output_dr_sensor_rev_data_t)-8U)];
typedef tS8 Testoutput_dr_sensor_rev_data_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+8U-sizeof(output_dr_sensor_rev_data_t))];


//Send helper
#define output_dr_sensor_odo_rev_data_send(buff, frameQ) {\
	 output_dr_sensor_odo_rev_data_t *__msg = buff; \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->odometer)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->timestamp)); \
	_stbin_msg_send((tUChar *)(__msg), \
				output_dr_sensor_odo_rev_data_t_size_send, \
				frameQ); \
	}

//Test structure size against computed size
typedef tS8 Testoutput_dr_sensor_odo_rev_data_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(output_dr_sensor_odo_rev_data_t)-12U)];
typedef tS8 Testoutput_dr_sensor_odo_rev_data_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+12U-sizeof(output_dr_sensor_odo_rev_data_t))];


//Send helper
#define output_dr_sensor_gyro_data_send(buff, frameQ) {\
	 output_dr_sensor_gyro_data_t *__msg = buff; \
	STBIN_TO_LINK_ENDIAN_CONV_tU16(&((__msg)->gyroRate)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->timestamp)); \
	_stbin_msg_send((tUChar *)(__msg), \
				output_dr_sensor_gyro_data_t_size_send, \
				frameQ); \
	}

//Test structure size against computed size
typedef tS8 Testoutput_dr_sensor_gyro_data_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(output_dr_sensor_gyro_data_t)-8U)];
typedef tS8 Testoutput_dr_sensor_gyro_data_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+8U-sizeof(output_dr_sensor_gyro_data_t))];


//Send helper
#define output_dr_sensor_gyro_odo_rev_send(buff, frameQ) {\
	 output_dr_sensor_gyro_odo_rev_t *__msg = buff; \
	STBIN_TO_LINK_ENDIAN_CONV_tU16(&((__msg)->gyroRate)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->odometer)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->timestamp)); \
	_stbin_msg_send((tUChar *)(__msg), \
				output_dr_sensor_gyro_odo_rev_t_size_send, \
				frameQ); \
	}

//Test structure size against computed size
typedef tS8 Testoutput_dr_sensor_gyro_odo_rev_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(output_dr_sensor_gyro_odo_rev_t)-12U)];
typedef tS8 Testoutput_dr_sensor_gyro_odo_rev_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+12U-sizeof(output_dr_sensor_gyro_odo_rev_t))];


//Send helper
#define output_dr_sensor_2w_r_data_send(buff, frameQ) {\
	 output_dr_sensor_2w_r_data_t *__msg = buff; \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->right_wheel)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->left_wheel)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->timestamp)); \
	_stbin_msg_send((tUChar *)(__msg), \
				output_dr_sensor_2w_r_data_t_size_send, \
				frameQ); \
	}

//Test structure size against computed size
typedef tS8 Testoutput_dr_sensor_2w_r_data_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(output_dr_sensor_2w_r_data_t)-12U)];
typedef tS8 Testoutput_dr_sensor_2w_r_data_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+12U-sizeof(output_dr_sensor_2w_r_data_t))];


//Send helper
#define output_dr_sensor_2w_r_rev_data_send(buff, frameQ) {\
	 output_dr_sensor_2w_r_rev_data_t *__msg = buff; \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->right_wheel)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->left_wheel)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->timestamp)); \
	_stbin_msg_send((tUChar *)(__msg), \
				output_dr_sensor_2w_r_rev_data_t_size_send, \
				frameQ); \
	}

//Test structure size against computed size
typedef tS8 Testoutput_dr_sensor_2w_r_rev_data_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(output_dr_sensor_2w_r_rev_data_t)-16U)];
typedef tS8 Testoutput_dr_sensor_2w_r_rev_data_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+16U-sizeof(output_dr_sensor_2w_r_rev_data_t))];


//Send helper
#define output_dr_sensor_4w_data_send(buff, frameQ) {\
	 output_dr_sensor_4w_data_t *__msg = buff; \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->rear_right_wheel)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->rear_left_wheel)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->front_right_wheel)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->front_left_wheel)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->timestamp)); \
	_stbin_msg_send((tUChar *)(__msg), \
				output_dr_sensor_4w_data_t_size_send, \
				frameQ); \
	}

//Test structure size against computed size
typedef tS8 Testoutput_dr_sensor_4w_data_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(output_dr_sensor_4w_data_t)-20U)];
typedef tS8 Testoutput_dr_sensor_4w_data_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+20U-sizeof(output_dr_sensor_4w_data_t))];


//Send helper
#define output_dr_sensor_4w_rev_data_send(buff, frameQ) {\
	 output_dr_sensor_4w_rev_data_t *__msg = buff; \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->rear_right_wheel)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->rear_left_wheel)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->front_right_wheel)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->front_left_wheel)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->timestamp)); \
	_stbin_msg_send((tUChar *)(__msg), \
				output_dr_sensor_4w_rev_data_t_size_send, \
				frameQ); \
	}

//Test structure size against computed size
typedef tS8 Testoutput_dr_sensor_4w_rev_data_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(output_dr_sensor_4w_rev_data_t)-24U)];
typedef tS8 Testoutput_dr_sensor_4w_rev_data_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+24U-sizeof(output_dr_sensor_4w_rev_data_t))];


//Send helper
#define output_dr_sensor_speed_data_send(buff, frameQ) {\
	 output_dr_sensor_speed_data_t *__msg = buff; \
	STBIN_TO_LINK_ENDIAN_CONV_tU16(&((__msg)->speed_kmh)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->timestamp)); \
	_stbin_msg_send((tUChar *)(__msg), \
				output_dr_sensor_speed_data_t_size_send, \
				frameQ); \
	}

//Test structure size against computed size
typedef tS8 Testoutput_dr_sensor_speed_data_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(output_dr_sensor_speed_data_t)-8U)];
typedef tS8 Testoutput_dr_sensor_speed_data_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+8U-sizeof(output_dr_sensor_speed_data_t))];


//Send helper
#define output_dr_sensor_2w_r_speed_data_send(buff, frameQ) {\
	 output_dr_sensor_2w_r_speed_data_t *__msg = buff; \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->right_wheel_speed)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->left_wheel_speed)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->timestamp)); \
	_stbin_msg_send((tUChar *)(__msg), \
				output_dr_sensor_2w_r_speed_data_t_size_send, \
				frameQ); \
	}

//Test structure size against computed size
typedef tS8 Testoutput_dr_sensor_2w_r_speed_data_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(output_dr_sensor_2w_r_speed_data_t)-12U)];
typedef tS8 Testoutput_dr_sensor_2w_r_speed_data_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+12U-sizeof(output_dr_sensor_2w_r_speed_data_t))];


//Send helper
#define output_dr_sensor_2w_r_rev_speed_data_send(buff, frameQ) {\
	 output_dr_sensor_2w_r_rev_speed_data_t *__msg = buff; \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->right_wheel_speed)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->left_wheel_speed)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->timestamp)); \
	_stbin_msg_send((tUChar *)(__msg), \
				output_dr_sensor_2w_r_rev_speed_data_t_size_send, \
				frameQ); \
	}

//Test structure size against computed size
typedef tS8 Testoutput_dr_sensor_2w_r_rev_speed_data_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(output_dr_sensor_2w_r_rev_speed_data_t)-16U)];
typedef tS8 Testoutput_dr_sensor_2w_r_rev_speed_data_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+16U-sizeof(output_dr_sensor_2w_r_rev_speed_data_t))];


//Send helper
#define output_dr_sensor_4w_speed_send(buff, frameQ) {\
	 output_dr_sensor_4w_speed_t *__msg = buff; \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->rear_right_wheel_speed)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->rear_left_wheel_speed)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->front_right_wheel_speed)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->front_left_wheel_speed)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->timestamp)); \
	_stbin_msg_send((tUChar *)(__msg), \
				output_dr_sensor_4w_speed_t_size_send, \
				frameQ); \
	}

//Test structure size against computed size
typedef tS8 Testoutput_dr_sensor_4w_speed_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(output_dr_sensor_4w_speed_t)-20U)];
typedef tS8 Testoutput_dr_sensor_4w_speed_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+20U-sizeof(output_dr_sensor_4w_speed_t))];


//Send helper
#define output_dr_sensor_4w_rev_speed_send(buff, frameQ) {\
	 output_dr_sensor_4w_rev_speed_t *__msg = buff; \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->rear_right_wheel_speed)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->rear_left_wheel_speed)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->front_right_wheel_speed)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->front_left_wheel_speed)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->timestamp)); \
	_stbin_msg_send((tUChar *)(__msg), \
				output_dr_sensor_4w_rev_speed_t_size_send, \
				frameQ); \
	}

//Test structure size against computed size
typedef tS8 Testoutput_dr_sensor_4w_rev_speed_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(output_dr_sensor_4w_rev_speed_t)-24U)];
typedef tS8 Testoutput_dr_sensor_4w_rev_speed_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+24U-sizeof(output_dr_sensor_4w_rev_speed_t))];


//Send helper
#define output_dr_sensor_temperature_data_send(buff, frameQ) {\
	 output_dr_sensor_temperature_data_t *__msg = buff; \
	STBIN_TO_LINK_ENDIAN_CONV_tS16(&((__msg)->temperature)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->timestamp)); \
	_stbin_msg_send((tUChar *)(__msg), \
				output_dr_sensor_temperature_data_t_size_send, \
				frameQ); \
	}

//Test structure size against computed size
typedef tS8 Testoutput_dr_sensor_temperature_data_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(output_dr_sensor_temperature_data_t)-8U)];
typedef tS8 Testoutput_dr_sensor_temperature_data_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+8U-sizeof(output_dr_sensor_temperature_data_t))];


//Send helper
#define output_dr_sensor_3a_acc_data_send(buff, frameQ) {\
	 output_dr_sensor_3a_acc_data_t *__msg = buff; \
	STBIN_TO_LINK_ENDIAN_CONV_tS16(&((__msg)->z_volts)); \
	STBIN_TO_LINK_ENDIAN_CONV_tS16(&((__msg)->y_volts)); \
	STBIN_TO_LINK_ENDIAN_CONV_tS16(&((__msg)->x_volts)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->timestamp)); \
	_stbin_msg_send((tUChar *)(__msg), \
				output_dr_sensor_3a_acc_data_t_size_send, \
				frameQ); \
	}

//Test structure size against computed size
typedef tS8 Testoutput_dr_sensor_3a_acc_data_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(output_dr_sensor_3a_acc_data_t)-12U)];
typedef tS8 Testoutput_dr_sensor_3a_acc_data_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+12U-sizeof(output_dr_sensor_3a_acc_data_t))];


//Send helper
#define output_dr_sensor_3a_gyro_data_send(buff, frameQ) {\
	 output_dr_sensor_3a_gyro_data_t *__msg = buff; \
	STBIN_TO_LINK_ENDIAN_CONV_tS16(&((__msg)->z_volts)); \
	STBIN_TO_LINK_ENDIAN_CONV_tS16(&((__msg)->y_volts)); \
	STBIN_TO_LINK_ENDIAN_CONV_tS16(&((__msg)->x_volts)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->timestamp)); \
	_stbin_msg_send((tUChar *)(__msg), \
				output_dr_sensor_3a_gyro_data_t_size_send, \
				frameQ); \
	}

//Test structure size against computed size
typedef tS8 Testoutput_dr_sensor_3a_gyro_data_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(output_dr_sensor_3a_gyro_data_t)-12U)];
typedef tS8 Testoutput_dr_sensor_3a_gyro_data_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+12U-sizeof(output_dr_sensor_3a_gyro_data_t))];


//Send helper
#define output_dr_sensor_odo_counter_send(buff, frameQ) {\
	 output_dr_sensor_odo_counter_t *__msg = buff; \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->timestamp)); \
	_stbin_msg_send((tUChar *)(__msg), \
				output_dr_sensor_odo_counter_t_size_send, \
				frameQ); \
	}

//Test structure size against computed size
typedef tS8 Testoutput_dr_sensor_odo_counter_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(output_dr_sensor_odo_counter_t)-4U)];
typedef tS8 Testoutput_dr_sensor_odo_counter_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+4U-sizeof(output_dr_sensor_odo_counter_t))];


//Send helper
#define output_dr_sensor_unknown_id_send(buff, frameQ) {\
	 output_dr_sensor_unknown_id_t *__msg = buff; \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->unknown_id)); \
	_stbin_msg_send((tUChar *)(__msg), \
				output_dr_sensor_unknown_id_t_size_send, \
				frameQ); \
	}

//Test structure size against computed size
typedef tS8 Testoutput_dr_sensor_unknown_id_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(output_dr_sensor_unknown_id_t)-4U)];
typedef tS8 Testoutput_dr_sensor_unknown_id_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+4U-sizeof(output_dr_sensor_unknown_id_t))];


//Above code is automatically generated (See rep_crm/tools/stbin/generators)
