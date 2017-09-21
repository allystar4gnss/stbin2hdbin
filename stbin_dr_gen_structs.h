//This code is automatically generated (See rep_crm/tools/stbin/generators)
//Section : DR OUTPUT Messages (ClassId 0x04)
//Frame output_dr_sensor_sample (cid=0x4 mid=0x1)
typedef struct output_dr_sensor_sample {
	tU32 timestamp; /* 0 */
	tU32 odometer; /* 4 */
	tU16 gyroRate; /* 8 */
	tU8 rev; /* 10 */
	tU8 pad1; /* 11 */
} output_dr_sensor_sample_t;
#define output_dr_sensor_sample_t_size_send 11

//Frame output_dr_can_sample (cid=0x4 mid=0x2)
typedef struct output_dr_can_sample {
	tU32 timestamp; /* 0 */
	tU16 carMaker; /* 4 */
	tU16 canObjId; /* 6 */
	tU8 canData[8]; /* 8 */
} output_dr_can_sample_t;
#define output_dr_can_sample_t_size_send 16

//Frame output_dr_3d_accel_sample (cid=0x4 mid=0x3)
typedef struct output_dr_3d_accel_sample {
	tU32 timestamp; /* 0 */
	tS16 rawX; /* 4 */
	tS16 rawY; /* 6 */
	tS16 rawZ; /* 8 */
	tU16 pad2; /* 10 */
} output_dr_3d_accel_sample_t;
#define output_dr_3d_accel_sample_t_size_send 10

//Frame output_dr_3d_gyro_sample (cid=0x4 mid=0x4)
typedef struct output_dr_3d_gyro_sample {
	tU32 timestamp; /* 0 */
	tU32 odometer; /* 4 */
	tS16 rawX; /* 8 */
	tS16 rawY; /* 10 */
	tS16 rawZ; /* 12 */
	tU8 rev; /* 14 */
	tU8 pad1; /* 15 */
} output_dr_3d_gyro_sample_t;
#define output_dr_3d_gyro_sample_t_size_send 15

//Frame output_dr_fix_metrics (cid=0x4 mid=0x20)
typedef struct output_dr_fix_metrics {
	tS32 lon; /* 0 */
	tS32 lat; /* 4 */
	tS32 velN; /* 8 */
	tS32 velE; /* 12 */
	tS32 velU; /* 16 */
	tS32 rms_vel_res; /* 20 */
	tS32 rms_pos_res; /* 24 */
	tU8 pdop; /* 28 */
	tU8 vdop; /* 29 */
	tU8 hdop; /* 30 */
	tU8 pad; /* 31 */
} output_dr_fix_metrics_t;
#define output_dr_fix_metrics_t_size_send 31

//Frame output_dr_kalman_state (cid=0x4 mid=0x21)
typedef struct output_dr_kalman_state {
	tU32 timestamp; /* 0 */
	tS32 lon; /* 4 */
	tS32 lat; /* 8 */
	tS32 heading; /* 12 */
	tU32 speed; /* 16 */
	tS32 gyro_offset; /* 20 */
	tU32 gyro_gain; /* 24 */
	tU32 odo_scale; /* 28 */
	tU32 gyro_ovst; /* 32 */
} output_dr_kalman_state_t;
#define output_dr_kalman_state_t_size_send 36

//Frame output_dr_debug_info (cid=0x4 mid=0x22)
typedef struct output_dr_debug_info {
	tU32 lon_err; /* 0 */
	tU32 lat_err; /* 4 */
	tU32 heading_err; /* 8 */
	tU32 speed_err; /* 12 */
} output_dr_debug_info_t;
#define output_dr_debug_info_t_size_send 16

//Frame output_dr_kalman_nvm_write (cid=0x4 mid=0x23)
typedef struct output_dr_kalman_nvm_write {
	tS32 state_lon; /* 0 */
	tS32 state_lat; /* 4 */
	tS32 state_heading; /* 8 */
	tS32 state_gyro_offset; /* 12 */
	tU32 state_gyro_gain; /* 16 */
	tU32 state_odo_scale; /* 20 */
	tU32 state_gyro_ovst; /* 24 */
	tS32 sdev_lon; /* 28 */
	tS32 sdev_lat; /* 32 */
	tS32 sdev_heading; /* 36 */
	tS32 sdev_gyro_offset; /* 40 */
	tU32 sdev_gyro_gain; /* 44 */
	tU32 sdev_odo_scale; /* 48 */
	tU32 sdev_gyro_ovst; /* 52 */
	tU32 temperature; /* 56 */
	tU32 angle_pitch; /* 60 */
	tU32 angle_roll; /* 64 */
	tU32 angle_yaw; /* 68 */
	tU8 calib_flags; /* 72 */
	tU8 pad1; /* 73 */
	tU16 pad2; /* 74 */
} output_dr_kalman_nvm_write_t;
#define output_dr_kalman_nvm_write_t_size_send 73

//Frame output_dr_kalman_nvm_read (cid=0x4 mid=0x24)
typedef struct output_dr_kalman_nvm_read {
	tS32 state_lon; /* 0 */
	tS32 state_lat; /* 4 */
	tS32 state_heading; /* 8 */
	tS32 state_gyro_offset; /* 12 */
	tU32 state_gyro_gain; /* 16 */
	tU32 state_odo_scale; /* 20 */
	tU32 state_gyro_ovst; /* 24 */
	tS32 sdev_lon; /* 28 */
	tS32 sdev_lat; /* 32 */
	tS32 sdev_heading; /* 36 */
	tS32 sdev_gyro_offset; /* 40 */
	tU32 sdev_gyro_gain; /* 44 */
	tU32 sdev_odo_scale; /* 48 */
	tU32 sdev_gyro_ovst; /* 52 */
	tU32 temperature; /* 56 */
	tU32 angle_pitch; /* 60 */
	tU32 angle_roll; /* 64 */
	tU32 angle_yaw; /* 68 */
	tU8 calib_flags; /* 72 */
	tU8 pad1; /* 73 */
	tU16 pad2; /* 74 */
} output_dr_kalman_nvm_read_t;
#define output_dr_kalman_nvm_read_t_size_send 73

//Frame output_dr_kalman_init (cid=0x4 mid=0x25)
typedef struct output_dr_kalman_init {
	tS32 state_lon; /* 0 */
	tS32 state_lat; /* 4 */
	tS32 state_heading; /* 8 */
	tS32 state_gyro_offset; /* 12 */
	tU32 state_gyro_gain; /* 16 */
	tU32 state_odo_scale; /* 20 */
	tU32 state_gyro_ovst; /* 24 */
	tS32 sdev_lon; /* 28 */
	tS32 sdev_lat; /* 32 */
	tS32 sdev_heading; /* 36 */
	tS32 sdev_gyro_offset; /* 40 */
	tU32 sdev_gyro_gain; /* 44 */
	tU32 sdev_odo_scale; /* 48 */
	tU32 sdev_gyro_ovst; /* 52 */
	tU32 temperature; /* 56 */
	tU32 angle_pitch; /* 60 */
	tU32 angle_roll; /* 64 */
	tU32 angle_yaw; /* 68 */
	tU8 calib_flags; /* 72 */
	tU8 pad1; /* 73 */
	tU16 pad2; /* 74 */
} output_dr_kalman_init_t;
#define output_dr_kalman_init_t_size_send 73

//Frame output_dr_cov (cid=0x4 mid=0x26)
typedef struct output_dr_cov {
	tS32 sdev_lon; /* 0 */
	tS32 sdev_lat; /* 4 */
	tS32 sdev_heading; /* 8 */
	tS32 sdev_gyro_offset; /* 12 */
	tU32 sdev_gyro_gain; /* 16 */
	tU32 sdev_odo_scale; /* 20 */
	tU32 sdev_gyro_ovst; /* 24 */
} output_dr_cov_t;
#define output_dr_cov_t_size_send 28

//Frame output_dr_kalman_update (cid=0x4 mid=0x27)
typedef struct output_dr_kalman_update {
	tS32 lon; /* 0 */
	tS32 lat; /* 4 */
	tS32 heading; /* 8 */
	tS32 gyro_offset; /* 12 */
	tU32 gyro_gain; /* 16 */
	tU32 odo_scale; /* 20 */
	tU32 gyro_ovst; /* 24 */
} output_dr_kalman_update_t;
#define output_dr_kalman_update_t_size_send 28

//Frame output_dr_integrator_step (cid=0x4 mid=0x28)
typedef struct output_dr_integrator_step {
	tS32 ave_gyro_volts; /* 0 */
	tS32 gyro_noise; /* 4 */
	tS32 tot_odo_step; /* 8 */
	tS32 delta_odo_count; /* 12 */
	tS32 delta_cputime; /* 16 */
	tS32 delta_cputime2; /* 20 */
	tU16 sample_count; /* 24 */
	tU8 valid_odo; /* 26 */
	tU8 pad1; /* 27 */
} output_dr_integrator_step_t;
#define output_dr_integrator_step_t_size_send 27

//Frame output_dr_tunnel (cid=0x4 mid=0x29)
typedef struct output_dr_tunnel {
	tS32 heading_error; /* 0 */
	tS32 yaw_rate_error; /* 4 */
	tS32 gyro_calib_error; /* 8 */
	tS32 gyro_noise_error; /* 12 */
	tU16 length; /* 16 */
	tU16 duration; /* 18 */
	tU16 pos_error_DR; /* 20 */
	tU8 pos_error_percent; /* 22 */
	tU8 exit; /* 23 */
} output_dr_tunnel_t;
#define output_dr_tunnel_t_size_send 24

//Frame output_dr_sensor_type (cid=0x4 mid=0x2A)
typedef struct output_dr_sensor_type {
	tU8 sensor_type; /* 0 */
	tU8 pad1; /* 1 */
	tU16 pad2; /* 2 */
} output_sm_sensor_type_t;
#define output_sm_sensor_type_t_size_send 1

//Frame output_dr_calib (cid=0x4 mid=0x2B)
typedef struct output_dr_calib {
	tU8 calib_flags; /* 0 */
	tU8 pad1; /* 1 */
	tU16 pad2; /* 2 */
} output_dr_calib_t;
#define output_dr_calib_t_size_send 1

//Frame output_dr_gyro_offset (cid=0x4 mid=0x2C)
typedef struct output_dr_gyro_offset {
	tS32 last_stopped_value; /* 0 */
	tS32 error; /* 4 */
	tS32 calibrated_time; /* 8 */
	tS32 temperature_correction; /* 12 */
	tS16 yaw_rate_signal_std_dev; /* 16 */
	tU8 calib_flags; /* 18 */
	tU8 pad1; /* 19 */
} output_dr_gyro_offset_t;
#define output_dr_gyro_offset_t_size_send 19

//Frame output_dr_ahrs (cid=0x4 mid=0x2D)
typedef struct output_dr_ahrs {
	tU32 angle_pitch; /* 0 */
	tU32 angle_roll; /* 4 */
	tU32 angle_yaw; /* 8 */
	tU32 slope; /* 12 */
	tU32 slope_accuracy; /* 16 */
	tU32 delta_height; /* 20 */
} output_dr_ahrs_t;
#define output_dr_ahrs_t_size_send 24

//Frame output_dr_mmfb (cid=0x4 mid=0x2E)
typedef struct output_dr_mmfb {
	tS32 hhmmss; /* 0 */
	tU32 ms; /* 4 */
	tS32 lon; /* 8 */
	tS32 lat; /* 12 */
	tU32 height; /* 16 */
	tU32 heading; /* 20 */
	tU32 height_err; /* 24 */
	tU32 heading_err; /* 28 */
	tU32 lon_err; /* 32 */
	tU32 lat_err; /* 36 */
	tU8 validity_flags; /* 40 */
	tU8 pad1; /* 41 */
	tU16 pad2; /* 42 */
} output_dr_mmfb_t;
#define output_dr_mmfb_t_size_send 41

//Frame output_dr_sensor_odo_data (cid=0x4 mid=0x50)
typedef struct output_dr_sensor_odo_data {
	tU32 timestamp; /* 0 */
	tU32 odometer; /* 4 */
} output_dr_sensor_odo_data_t;
#define output_dr_sensor_odo_data_t_size_send 8

//Frame output_dr_sensor_rev_data (cid=0x4 mid=0x51)
typedef struct output_dr_sensor_rev_data {
	tU32 timestamp; /* 0 */
	tU8 rev; /* 4 */
	tU8 pad1; /* 5 */
	tU16 pad2; /* 6 */
} output_dr_sensor_rev_data_t;
#define output_dr_sensor_rev_data_t_size_send 5

//Frame output_dr_sensor_odo_rev_data (cid=0x4 mid=0x52)
typedef struct output_dr_sensor_odo_rev_data {
	tU32 timestamp; /* 0 */
	tU32 odometer; /* 4 */
	tU8 rev; /* 8 */
	tU8 pad1; /* 9 */
	tU16 pad2; /* 10 */
} output_dr_sensor_odo_rev_data_t;
#define output_dr_sensor_odo_rev_data_t_size_send 9

//Frame output_dr_sensor_gyro_data (cid=0x4 mid=0x53)
typedef struct output_dr_sensor_gyro_data {
	tU32 timestamp; /* 0 */
	tU16 gyroRate; /* 4 */
	tU16 pad2; /* 6 */
} output_dr_sensor_gyro_data_t;
#define output_dr_sensor_gyro_data_t_size_send 6

//Frame output_dr_sensor_gyro_odo_rev (cid=0x4 mid=0x54)
typedef struct output_dr_sensor_gyro_odo_rev {
	tU32 timestamp; /* 0 */
	tU32 odometer; /* 4 */
	tU16 gyroRate; /* 8 */
	tU8 rev; /* 10 */
	tU8 pad1; /* 11 */
} output_dr_sensor_gyro_odo_rev_t;
#define output_dr_sensor_gyro_odo_rev_t_size_send 11

//Frame output_dr_sensor_2w_r_data (cid=0x4 mid=0x58)
typedef struct output_dr_sensor_2w_r_data {
	tU32 timestamp; /* 0 */
	tU32 left_wheel; /* 4 */
	tU32 right_wheel; /* 8 */
} output_dr_sensor_2w_r_data_t;
#define output_dr_sensor_2w_r_data_t_size_send 12

//Frame output_dr_sensor_2w_r_rev_data (cid=0x4 mid=0x59)
typedef struct output_dr_sensor_2w_r_rev_data {
	tU32 timestamp; /* 0 */
	tU32 left_wheel; /* 4 */
	tU32 right_wheel; /* 8 */
	tU8 rev_flags; /* 12 */
	tU8 pad1; /* 13 */
	tU16 pad2; /* 14 */
} output_dr_sensor_2w_r_rev_data_t;
#define output_dr_sensor_2w_r_rev_data_t_size_send 13

//Frame output_dr_sensor_4w_data (cid=0x4 mid=0x5A)
typedef struct output_dr_sensor_4w_data {
	tU32 timestamp; /* 0 */
	tU32 front_left_wheel; /* 4 */
	tU32 front_right_wheel; /* 8 */
	tU32 rear_left_wheel; /* 12 */
	tU32 rear_right_wheel; /* 16 */
} output_dr_sensor_4w_data_t;
#define output_dr_sensor_4w_data_t_size_send 20

//Frame output_dr_sensor_4w_rev_data (cid=0x4 mid=0x5B)
typedef struct output_dr_sensor_4w_rev_data {
	tU32 timestamp; /* 0 */
	tU32 front_left_wheel; /* 4 */
	tU32 front_right_wheel; /* 8 */
	tU32 rear_left_wheel; /* 12 */
	tU32 rear_right_wheel; /* 16 */
	tU8 rev_flags; /* 20 */
	tU8 pad1; /* 21 */
	tU16 pad2; /* 22 */
} output_dr_sensor_4w_rev_data_t;
#define output_dr_sensor_4w_rev_data_t_size_send 21

//Frame output_dr_sensor_speed_data (cid=0x4 mid=0x5C)
typedef struct output_dr_sensor_speed_data {
	tU32 timestamp; /* 0 */
	tU16 speed_kmh; /* 4 */
	tU16 pad2; /* 6 */
} output_dr_sensor_speed_data_t;
#define output_dr_sensor_speed_data_t_size_send 6

//Frame output_dr_sensor_2w_r_speed_data (cid=0x4 mid=0x60)
typedef struct output_dr_sensor_2w_r_speed_data {
	tU32 timestamp; /* 0 */
	tU32 left_wheel_speed; /* 4 */
	tU32 right_wheel_speed; /* 8 */
} output_dr_sensor_2w_r_speed_data_t;
#define output_dr_sensor_2w_r_speed_data_t_size_send 12

//Frame output_dr_sensor_2w_r_rev_speed_data (cid=0x4 mid=0x61)
typedef struct output_dr_sensor_2w_r_rev_speed_data {
	tU32 timestamp; /* 0 */
	tU32 left_wheel_speed; /* 4 */
	tU32 right_wheel_speed; /* 8 */
	tU8 rev_flags; /* 12 */
	tU8 pad1; /* 13 */
	tU16 pad2; /* 14 */
} output_dr_sensor_2w_r_rev_speed_data_t;
#define output_dr_sensor_2w_r_rev_speed_data_t_size_send 13

//Frame output_dr_sensor_4w_speed (cid=0x4 mid=0x62)
typedef struct output_dr_sensor_4w_speed {
	tU32 timestamp; /* 0 */
	tU32 front_left_wheel_speed; /* 4 */
	tU32 front_right_wheel_speed; /* 8 */
	tU32 rear_left_wheel_speed; /* 12 */
	tU32 rear_right_wheel_speed; /* 16 */
} output_dr_sensor_4w_speed_t;
#define output_dr_sensor_4w_speed_t_size_send 20

//Frame output_dr_sensor_4w_rev_speed (cid=0x4 mid=0x63)
typedef struct output_dr_sensor_4w_rev_speed {
	tU32 timestamp; /* 0 */
	tU32 front_left_wheel_speed; /* 4 */
	tU32 front_right_wheel_speed; /* 8 */
	tU32 rear_left_wheel_speed; /* 12 */
	tU32 rear_right_wheel_speed; /* 16 */
	tU8 rev_flags; /* 20 */
	tU8 pad1; /* 21 */
	tU16 pad2; /* 22 */
} output_dr_sensor_4w_rev_speed_t;
#define output_dr_sensor_4w_rev_speed_t_size_send 21

//Frame output_dr_sensor_temperature_data (cid=0x4 mid=0x64)
typedef struct output_dr_sensor_temperature_data {
	tU32 timestamp; /* 0 */
	tS16 temperature; /* 4 */
	tU8 temp_valid; /* 6 */
	tU8 pad1; /* 7 */
} output_dr_sensor_temperature_data_t;
#define output_dr_sensor_temperature_data_t_size_send 7

//Frame output_dr_sensor_3a_acc_data (cid=0x4 mid=0x65)
typedef struct output_dr_sensor_3a_acc_data {
	tU32 timestamp; /* 0 */
	tS16 x_volts; /* 4 */
	tS16 y_volts; /* 6 */
	tS16 z_volts; /* 8 */
	tU16 pad2; /* 10 */
} output_dr_sensor_3a_acc_data_t;
#define output_dr_sensor_3a_acc_data_t_size_send 10

//Frame output_dr_sensor_3a_gyro_data (cid=0x4 mid=0x66)
typedef struct output_dr_sensor_3a_gyro_data {
	tU32 timestamp; /* 0 */
	tS16 x_volts; /* 4 */
	tS16 y_volts; /* 6 */
	tS16 z_volts; /* 8 */
	tU16 pad2; /* 10 */
} output_dr_sensor_3a_gyro_data_t;
#define output_dr_sensor_3a_gyro_data_t_size_send 10

//Frame output_dr_sensor_odo_counter (cid=0x4 mid=0x68)
typedef struct output_dr_sensor_odo_counter {
	tU32 timestamp; /* 0 */
} output_dr_sensor_odo_counter_t;
#define output_dr_sensor_odo_counter_t_size_send 4

//Frame output_dr_sensor_unknown_id (cid=0x4 mid=0xF0)
typedef struct output_dr_sensor_unknown_id {
	tU32 unknown_id; /* 0 */
} output_dr_sensor_unknown_id_t;
#define output_dr_sensor_unknown_id_t_size_send 4

#define STBIN_WAAS_MAX_PAYLOAD_SIZE 73U
#ifndef STBIN_MAX_PAYLOAD_SIZE
#  error Maximal payload size must be defined when this code is reached
#endif
#if STBIN_MAX_PAYLOAD_SIZE < STBIN_WAAS_MAX_PAYLOAD_SIZE
#  error Maximal payload size must be reviewed
#endif
//Above code is automatically generated (See rep_crm/tools/stbin/generators)
