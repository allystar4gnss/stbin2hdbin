//This code is automatically generated (See rep_crm/tools/stbin/generators)
#define STBIN_LEN_STRING 24
#define STBIN_SW_CONFIG_TEXT_LENGTH 72
#define STBIN_WGS84_INDEX 228
#define STBIN_FE_NB_REG_MAX 30
//Section : Interface Control Messages (ClassId 0x12)
//Frame stbin_return_in_nmea_communication (cid=0x12 mid=0x78)
typedef struct stbin_return_in_nmea_communication {
	tU8 control; /* 0 */
} stbin_return_in_nmea_communication_t;
#define stbin_return_in_nmea_communication_t_size_send 1

//Frame stbin_control_output_req (cid=0x12 mid=0x81)
typedef struct stbin_control_output_req {
	tU8 onOff; /* 0 */
} stbin_control_output_req_t;
#define stbin_control_output_req_t_size_send 1

//Section : Test Request Messages (ClassId 0x4A)
//Frame stbin_exec_test_on_req (cid=0x4A mid=0x16)
typedef struct stbin_exec_test_on_req {
	tU8 test_type; /* 0 */
	tU8 threshold; /* 1 */
	tU16 satId; /* 2 */
} stbin_exec_test_on_req_t;
#define stbin_exec_test_on_req_t_size_send 4

//Frame stbin_exec_test_add_req (cid=0x4A mid=0x17)
typedef struct stbin_exec_test_add_req {
	tU8 test_type; /* 0 */
	tU8 threshold; /* 1 */
	tU16 satId; /* 2 */
} stbin_exec_test_add_req_t;
#define stbin_exec_test_add_req_t_size_send 4

//Frame stbin_exec_test_del_req (cid=0x4A mid=0x18)
typedef struct stbin_exec_test_del_req {
	tU16 satId; /* 0 */
} stbin_exec_test_del_req_t;
#define stbin_exec_test_del_req_t_size_send 2

//Frame stbin_exec_test_off_req (cid=0x4A mid=0x19)
	// Have no payload
//Frame stbin_exec_test_rtc_testOnOff_req (cid=0x4A mid=0x1A)
typedef struct stbin_exec_test_rtc_testOnOff_req {
	tU8 onOff; /* 0 */
} stbin_exec_test_rtc_testOnOff_req_t;
#define stbin_exec_test_rtc_testOnOff_req_t_size_send 1

//Frame stbin_exec_test_trkjammer_req (cid=0x4A mid=0x1B)
typedef struct stbin_exec_test_trkjammer_req {
	tU8 onOff; /* 0 */
} stbin_exec_test_trkjammer_req_t;
#define stbin_exec_test_trkjammer_req_t_size_send 1

//Frame stbin_exec_test_rtc_err_req (cid=0x4A mid=0x1C)
typedef struct stbin_exec_test_rtc_err_req {
	tU32 error; /* 0 */
	tU32 accuracy; /* 4 */
} stbin_exec_test_rtc_err_req_t;
#define stbin_exec_test_rtc_err_req_t_size_send 8

//Section : \PPSText Read Request Messages (ClassId 0x2D)
//Frame stbin_exec_pps_if_pulse_data_read_req (cid=0x2D mid=0x4A)
	// Have no payload
//Frame stbin_exec_pps_if_timing_data_read_req (cid=0x2D mid=0x4B)
	// Have no payload
//Frame stbin_exec_pps_if_pos_hold_data_read_req (cid=0x2D mid=0x4C)
	// Have no payload
//Frame stbin_exec_pps_if_traim_read_req (cid=0x2D mid=0x4D)
	// Have no payload
//Section : \PPSText Write Request Messages (ClassId 0x3D)
//Frame stbin_exec_pps_if_on_off_write_req (cid=0x3D mid=0x24)
typedef struct stbin_exec_pps_if_on_off_write_req {
	tU8 onOff; /* 0 */
} stbin_exec_pps_if_on_off_write_req_t;
#define stbin_exec_pps_if_on_off_write_req_t_size_send 1

//Frame stbin_exec_pps_if_output_mode_write_req (cid=0x3D mid=0x25)
typedef struct stbin_exec_pps_if_output_mode_write_req {
	tU8 outMode; /* 0 */
} stbin_exec_pps_if_output_mode_write_req_t;
#define stbin_exec_pps_if_output_mode_write_req_t_size_send 1

//Frame stbin_exec_pps_if_ref_constellation_write_req (cid=0x3D mid=0x26)
typedef struct stbin_exec_pps_if_ref_constellation_write_req {
	tU8 refConst; /* 0 */
} stbin_exec_pps_if_ref_constellation_write_req_t;
#define stbin_exec_pps_if_ref_constellation_write_req_t_size_send 1

//Frame stbin_exec_pps_if_ref_time_write_req (cid=0x3D mid=0x27)
typedef struct stbin_exec_pps_if_ref_time_write_req {
	tU8 refTimeId; /* 0 */
} stbin_exec_pps_if_ref_time_write_req_t;
#define stbin_exec_pps_if_ref_time_write_req_t_size_send 1

//Frame stbin_exec_pps_if_pulse_delay_write_req (cid=0x3D mid=0x28)
typedef struct stbin_exec_pps_if_pulse_delay_write_req {
	tU16 pulseDelay; /* 0 */
} stbin_exec_pps_if_pulse_delay_write_req_t;
#define stbin_exec_pps_if_pulse_delay_write_req_t_size_send 2

//Frame stbin_exec_pps_if_pulse_duration_write_req (cid=0x3D mid=0x29)
typedef struct stbin_exec_pps_if_pulse_duration_write_req {
	tU16 pulseDuration; /* 0 */
} stbin_exec_pps_if_pulse_duration_write_req_t;
#define stbin_exec_pps_if_pulse_duration_write_req_t_size_send 2

//Frame stbin_exec_pps_if_pulse_polarity_write_req (cid=0x3D mid=0x2A)
typedef struct stbin_exec_pps_if_pulse_polarity_write_req {
	tU8 pulsePolarity; /* 0 */
	tU8 pad1; /* 1 */
} stbin_exec_pps_if_pulse_polarity_write_req_t;
#define stbin_exec_pps_if_pulse_polarity_write_req_t_size_send 1

//Frame stbin_exec_pps_if_data_write_req (cid=0x3D mid=0x4A)
typedef struct stbin_exec_pps_if_data_write_req {
	tU8 outMode; /* 0 */
	tU8 refTimeId; /* 1 */
	tU16 pulseDelay; /* 2 */
	tU16 pulseDuration; /* 4 */
	tU8 pulsePolarity; /* 6 */
	tU8 pad1; /* 7 */
} stbin_exec_pps_if_data_write_req_t;
#define stbin_exec_pps_if_data_write_req_t_size_send 7

//Frame stbin_exec_pps_if_fix_condition_write_req (cid=0x3D mid=0x2C)
typedef struct stbin_exec_pps_if_fix_condition_write_req {
	tU8 fixCondition; /* 0 */
} stbin_exec_pps_if_fix_condition_write_req_t;
#define stbin_exec_pps_if_fix_condition_write_req_t_size_send 1

//Frame stbin_exec_pps_if_sat_threshold_write_req (cid=0x3D mid=0x2D)
typedef struct stbin_exec_pps_if_sat_threshold_write_req {
	tU8 satTh; /* 0 */
} stbin_exec_pps_if_sat_threshold_write_req_t;
#define stbin_exec_pps_if_sat_threshold_write_req_t_size_send 1

//Frame stbin_exec_pps_if_constallation_rf_delay_write_req (cid=0x3D mid=0x2E)
typedef struct stbin_exec_pps_if_constallation_rf_delay_write_req {
	tU16 rfDelay; /* 0 */
	tU8 constellation; /* 2 */
	tU8 pad1; /* 3 */
} stbin_exec_pps_if_constallation_rf_delay_write_req_t;
#define stbin_exec_pps_if_constallation_rf_delay_write_req_t_size_send 3

//Frame stbin_exec_pps_if_elevation_mask_write_req (cid=0x3D mid=0x2F)
typedef struct stbin_exec_pps_if_elevation_mask_write_req {
	tU8 elevationMask; /* 0 */
} stbin_exec_pps_if_elevation_mask_write_req_t;
#define stbin_exec_pps_if_elevation_mask_write_req_t_size_send 1

//Frame stbin_exec_pps_if_constellation_mask_write_req (cid=0x3D mid=0x30)
typedef struct stbin_exec_pps_if_constellation_mask_write_req {
	tU32 constellationMask; /* 0 */
} stbin_exec_pps_if_constellation_mask_write_req_t;
#define stbin_exec_pps_if_constellation_mask_write_req_t_size_send 4

//Frame stbin_exec_pps_if_timing_data_write_req (cid=0x3D mid=0x4B)
typedef struct stbin_exec_pps_if_timing_data_write_req {
	tU32 constellationMask; /* 0 */
	tU8 fixCondition; /* 4 */
	tU8 satTh; /* 5 */
	tU8 elevationMask; /* 6 */
	tU8 pad1; /* 7 */
} stbin_exec_pps_if_timing_data_write_req_t;
#define stbin_exec_pps_if_timing_data_write_req_t_size_send 7

//Frame stbin_exec_pps_if_hold_data_write_req (cid=0x3D mid=0x4C)
typedef struct stbin_exec_pps_if_hold_data_write_req {
	tS32 lat_val; /* 0 */
	tS32 lon_val; /* 4 */
	tS32 height; /* 8 */
	tU8 posHoldOnOff; /* 12 */
	tU8 pad1; /* 13 */
	tU16 pad2; /* 14 */
} stbin_exec_pps_if_hold_data_write_req_t;
#define stbin_exec_pps_if_hold_data_write_req_t_size_send 13

//Frame stbin_exec_pps_if_auto_hold_samples_write_req (cid=0x3D mid=0x33)
typedef struct stbin_exec_pps_if_auto_hold_samples_write_req {
	tU16 nbSamples; /* 0 */
} stbin_exec_pps_if_auto_hold_samples_write_req_t;
#define stbin_exec_pps_if_auto_hold_samples_write_req_t_size_send 2

//Frame stbin_exec_pps_if_traim_data_write_req (cid=0x3D mid=0x4D)
typedef struct stbin_exec_pps_if_traim_data_write_req {
	tU16 alarm; /* 0 */
	tU8 enabled; /* 2 */
	tU8 pad1; /* 3 */
} stbin_exec_pps_if_traim_data_write_req_t;
#define stbin_exec_pps_if_traim_data_write_req_t_size_send 3

//Section : Initialization messages (ClassId 0x20)
//Frame stbin_exec_init_GPS_params_req (cid=0x20 mid=0x1)
typedef struct stbin_exec_init_GPS_params_req {
	tS32 lat_val; /* 0 */
	tS32 lon_val; /* 4 */
	tS32 height; /* 8 */
	tS16 year; /* 12 */
	tU8 month; /* 14 */
	tU8 day; /* 15 */
	tU8 hour; /* 16 */
	tU8 min; /* 17 */
	tU8 sec; /* 18 */
	tU8 constel; /* 19 */
} stbin_exec_init_GPS_params_req_t;
#define stbin_exec_init_GPS_params_req_t_size_send 20

//Frame stbin_exec_init_GPS_time_req (cid=0x20 mid=0x6)
typedef struct stbin_exec_init_GPS_time_req {
	tS16 year; /* 0 */
	tU8 month; /* 2 */
	tU8 day; /* 3 */
	tU8 hour; /* 4 */
	tU8 min; /* 5 */
	tU8 sec; /* 6 */
	tU8 constel; /* 7 */
} stbin_exec_init_GPS_time_req_t;
#define stbin_exec_init_GPS_time_req_t_size_send 8

//Frame stbin_exec_init_freq_req (cid=0x20 mid=0x2)
typedef struct stbin_exec_init_freq_req {
	tS32 freq; /* 0 */
} stbin_exec_init_freq_req_t;
#define stbin_exec_init_freq_req_t_size_send 4

//Frame stbin_exec_init_cold_req (cid=0x20 mid=0x3)
typedef struct stbin_exec_init_cold_req {
	tU8 type; /* 0 */
	tU8 use_fw; /* 1 */
} stbin_exec_init_cold_req_t;
#define stbin_exec_init_cold_req_t_size_send 2

//Frame stbin_exec_init_warm_req (cid=0x20 mid=0x4)
typedef struct stbin_exec_init_warm_req {
	tU8 control; /* 0 */
} stbin_exec_init_warm_req_t;
#define stbin_exec_init_warm_req_t_size_send 1

//Frame stbin_exec_init_hot_req (cid=0x20 mid=0x5)
typedef struct stbin_exec_init_hot_req {
	tU8 control; /* 0 */
} stbin_exec_init_hot_req_t;
#define stbin_exec_init_hot_req_t_size_send 1

//Frame stbin_exec_init_clr_ephemes (cid=0x20 mid=0x7)
	// Have no payload
//Frame stbin_exec_init_clr_almanacs (cid=0x20 mid=0x8)
	// Have no payload
//Section : Reset messages (ClassId 0x5A)
//Frame stbin_exec_reset_gps_req (cid=0x5A mid=0x5C)
typedef struct stbin_exec_reset_gps_req {
	tU8 control; /* 0 */
} stbin_exec_reset_gps_req_t;
#define stbin_exec_reset_gps_req_t_size_send 1

//Frame stbin_exec_reset_soft_req (cid=0x5A mid=0x5D)
typedef struct stbin_exec_reset_soft_req {
	tU8 control; /* 0 */
} stbin_exec_reset_soft_req_t;
#define stbin_exec_reset_soft_req_t_size_send 1

//Frame stbin_exec_reset_stack_check_req (cid=0x5A mid=0x5E)
typedef struct stbin_exec_reset_stack_check_req {
	tU8 control; /* 0 */
} stbin_exec_reset_stack_check_req_t;
#define stbin_exec_reset_stack_check_req_t_size_send 1

//Frame stbin_exec_gps_suspend (cid=0x5A mid=0x5F)
	// Have no payload
//Frame stbin_exec_gps_resume (cid=0x5A mid=0x60)
	// Have no payload
//Section : Read Requests (ClassId 0x2A)
//Frame stbin_exec_get_sw_ver (cid=0x2A mid=0x20)
typedef struct stbin_exec_get_sw_ver {
	tU8 control; /* 0 */
} stbin_exec_get_sw_ver_t;
#define stbin_exec_get_sw_ver_t_size_send 1

//Frame stbin_exec_check_task (cid=0x2A mid=0x21)
	// Have no payload
//Frame stbin_exec_check_cpu_usage (cid=0x2A mid=0x22)
	// Have no payload
//Frame stbin_exec_check_heap (cid=0x2A mid=0x23)
	// Have no payload
//Frame stbin_exec_read_rtc_time (cid=0x2A mid=0x30)
	// Have no payload
//Frame stbin_exec_read_datum_selection (cid=0x2A mid=0xF4)
	// Have no payload
//Frame stbin_exec_get_algo_status (cid=0x2A mid=0xF5)
typedef struct stbin_exec_get_algo_status {
	tU8 control; /* 0 */
} stbin_exec_get_algo_status_t;
#define stbin_exec_get_algo_status_t_size_send 1

//Frame stbin_exec_sw_config_get_par (cid=0x2A mid=0xFC)
typedef struct stbin_exec_sw_config_get_par {
	tU8 ConfigBlock; /* 0 */
	tU8 SectionId; /* 1 */
	tU8 ParamId; /* 2 */
} stbin_exec_sw_config_get_par_t;
#define stbin_exec_sw_config_get_par_t_size_send 3

//Frame stbin_exec_dump_almans (cid=0x2A mid=0xFD)
typedef struct stbin_exec_dump_almans {
	tU8 Constellation; /* 0 */
} stbin_exec_dump_almans_t;
#define stbin_exec_dump_almans_t_size_send 1

//Frame stbin_exec_dump_ephems (cid=0x2A mid=0xFE)
typedef struct stbin_exec_dump_ephems {
	tU8 Constellation; /* 0 */
} stbin_exec_dump_ephems_t;
#define stbin_exec_dump_ephems_t_size_send 1

//Frame stbin_exec_read_sw_config_all_blocks (cid=0x2A mid=0xF3)
typedef struct stbin_exec_read_sw_config_all_blocks {
	tU8 config_type; /* 0 */
} stbin_exec_read_sw_config_all_blocks_t;
#define stbin_exec_read_sw_config_all_blocks_t_size_send 1

//Frame stbin_exec_dump_fe (cid=0x2A mid=0x2E)
	// Have no payload
//Frame stbin_exec_get_diff_source (cid=0x2A mid=0xF2)
	// Have no payload
//Frame stbin_exec_adc_read (cid=0x2A mid=0x24)
typedef struct stbin_exec_adc_read {
	tU8 sel_line; /* 0 */
	tU8 ain; /* 1 */
	tU16 padding2; /* 2 */
} stbin_exec_adc_read_t;
#define stbin_exec_adc_read_t_size_send 2

//Frame stbin_exec_get_all_sw_ver (cid=0x2A mid=0x25)
	// Have no payload
//Section : Customer Flash Storage Read Requests (ClassId 0x2B)
//Frame stbin_exec_sqi_data_get (cid=0x2B mid=0x4E)
typedef struct stbin_exec_sqi_data_get {
	tU16 offset; /* 0 */
} stbin_exec_sqi_data_get_t;
#define stbin_exec_sqi_data_get_t_size_send 2

//Section : Write Requests (ClassId 0x3A)
//Frame stbin_exec_load_ephemes (cid=0x3A mid=0x1C)
	// Have no payload
//Frame stbin_exec_save_ephems (cid=0x3A mid=0xFE)
typedef struct stbin_exec_save_ephems {
	tU8 value[64]; /* 0 */
	tU8 dsp_satid; /* 64 */
	tU8 padding1; /* 65 */
	tU16 padding2; /* 66 */
} stbin_exec_save_ephems_t;
#define stbin_exec_save_ephems_t_size_send 65

//Frame stbin_exec_real_ephems_on_off (cid=0x3A mid=0x1F)
typedef struct stbin_exec_real_ephems_on_off {
	tU8 sat_id; /* 0 */
	tU8 param; /* 1 */
	tU16 padding1; /* 2 */
} stbin_exec_real_ephems_on_off_t;
#define stbin_exec_real_ephems_on_off_t_size_send 2

//Frame stbin_exec_load_almanac (cid=0x3A mid=0x1D)
	// Have no payload
//Frame stbin_exec_save_alams (cid=0x3A mid=0xFD)
typedef struct stbin_exec_save_alams {
	tU8 value[40]; /* 0 */
	tU8 dsp_satid; /* 40 */
	tU8 padding1; /* 41 */
	tU16 padding2; /* 42 */
} stbin_exec_save_alams_t;
#define stbin_exec_save_alams_t_size_send 41

//Frame sw_config_set_par_val_Char (cid=0x3A mid=0xFB)
typedef struct sw_config_set_par_val_Char {
	tU8 value; /* 0 */
	tU8 configParamId; /* 1 */
	tU16 padding; /* 2 */
} sw_config_set_par_val_Char_t;
#define sw_config_set_par_val_Char_t_size_send 2

//Frame sw_config_set_par_val_Int (cid=0x3A mid=0xFA)
typedef struct sw_config_set_par_val_Int {
	tS32 value; /* 0 */
	tU8 configParamId; /* 4 */
	tU8 padding1; /* 5 */
	tU16 padding2; /* 6 */
} sw_config_set_par_val_Int_t;
#define sw_config_set_par_val_Int_t_size_send 5

//Frame sw_config_set_par_val_UInt (cid=0x3A mid=0xF9)
typedef struct sw_config_set_par_val_UInt {
	tU32 value; /* 0 */
	tU8 mode; /* 4 */
	tU8 configSection; /* 5 */
	tU8 configParamId; /* 6 */
	tU8 padding; /* 7 */
} sw_config_set_par_val_UInt_t;
#define sw_config_set_par_val_UInt_t_size_send 7

//Frame sw_config_set_par_val_Double (cid=0x3A mid=0xF8)
typedef struct sw_config_set_par_val_Double {
	tDouble value; /* 0 */
	tU8 configParamId; /* 8 */
	tU8 padding1; /* 9 */
	tU16 padding2; /* 10 */
	tU32 padding3; /* 12 */
} sw_config_set_par_val_Double_t;
#define sw_config_set_par_val_Double_t_size_send 9

//Frame sw_config_set_par_val_Dops (cid=0x3A mid=0xF7)
typedef struct sw_config_set_par_val_Dops {
	tU8 pdop; /* 0 */
	tU8 vdop; /* 1 */
	tU8 hdop; /* 2 */
	tU8 gdop; /* 3 */
	tU8 configParamId; /* 4 */
	tU8 padding1; /* 5 */
	tU16 padding2; /* 6 */
} sw_config_set_par_val_Dops_t;
#define sw_config_set_par_val_Dops_t_size_send 5

//Frame sw_config_set_par_val_String (cid=0x3A mid=0xF6)
typedef struct sw_config_set_par_val_String {
	tChar value[STBIN_SW_CONFIG_TEXT_LENGTH]; /* 0 */
	tU8 configParamId; /* 72 */
	tU8 padding1; /* 73 */
	tU16 padding2; /* 74 */
} sw_config_set_par_val_String_t;
#define sw_config_set_par_val_String_t_size_send 73

//Frame set_algo_status (cid=0x3A mid=0xF5)
typedef struct set_algo_status {
	tU8 algo_type; /* 0 */
	tU8 algo_status; /* 1 */
	tU16 padding; /* 2 */
} set_algo_status_t;
#define set_algo_status_t_size_send 2

//Frame stbin_exec_write_datum_selection (cid=0x3A mid=0xF4)
typedef struct stbin_exec_write_datum_selection {
	tU8 datum; /* 0 */
} stbin_exec_write_datum_selection_t;
#define stbin_exec_write_datum_selection_t_size_send 1

//Frame stbin_exec_define_datum (cid=0x3A mid=0x7)
typedef struct stbin_exec_define_datum {
	tDouble d_x; /* 0 */
	tDouble d_y; /* 8 */
	tDouble d_z; /* 16 */
	tDouble d_a; /* 24 */
	tDouble d_f; /* 32 */
} stbin_exec_define_datum_t;
#define stbin_exec_define_datum_t_size_send 40

//Frame stbin_exec_sw_config_save_param (cid=0x3A mid=0x16)
typedef struct stbin_exec_sw_config_save_param {
	tU8 control; /* 0 */
} stbin_exec_sw_config_save_param_t;
#define stbin_exec_sw_config_save_param_t_size_send 1

//Frame stbin_exec_sw_config_restore_param (cid=0x3A mid=0x17)
typedef struct stbin_exec_sw_config_restore_param {
	tU8 control; /* 0 */
} stbin_exec_sw_config_restore_param_t;
#define stbin_exec_sw_config_restore_param_t_size_send 1

//Frame stbin_exec_set_range (cid=0x3A mid=0x2)
typedef struct stbin_exec_set_range {
	tS32 min; /* 0 */
	tS32 max; /* 4 */
} stbin_exec_set_range_t;
#define stbin_exec_set_range_t_size_send 8

//Frame stbin_exec_set_constellation_mask (cid=0x3A mid=0x6)
typedef struct stbin_exec_set_constellation_mask {
	tU32 constellation_mask; /* 0 */
	tU8 slave_reset; /* 4 */
	tU8 padding1; /* 5 */
	tU16 padding2; /* 6 */
} stbin_exec_set_constellation_mask_t;
#define stbin_exec_set_constellation_mask_t_size_send 5

//Frame stbin_exec_debug_on_off (cid=0x3A mid=0xB)
typedef struct stbin_exec_debug_on_off {
	tU8 on_off; /* 0 */
	tU8 padding1; /* 1 */
	tU16 padding2; /* 2 */
} stbin_exec_debug_on_off_t;
#define stbin_exec_debug_on_off_t_size_send 1

//Frame stbin_exec_time_inv (cid=0x3A mid=0xC)
	// Have no payload
//Frame stbin_exec_nvm_swap (cid=0x3A mid=0xF)
	// Have no payload
//Frame stbin_exec_fix2d_on_off (cid=0x3A mid=0x12)
typedef struct stbin_exec_fix2d_on_off {
	tU8 on_off; /* 0 */
	tU8 padding1; /* 1 */
	tU16 padding2; /* 2 */
} stbin_exec_fix2d_on_off_t;
#define stbin_exec_fix2d_on_off_t_size_send 1

//Frame stbin_exec_notch_enable (cid=0x3A mid=0x1B)
typedef struct stbin_exec_notch_enable {
	tS32 Reserved; /* 0 */
	tS8 sat_type; /* 4 */
	tS8 mode; /* 5 */
	tU16 padding1; /* 6 */
} stbin_exec_notch_enable_t;
#define stbin_exec_notch_enable_t_size_send 6

//Frame stbin_exec_enable_disable_position_hold (cid=0x3A mid=0x1E)
typedef struct stbin_exec_enable_disable_position_hold {
	tS32 lat; /* 0 */
	tS32 lon; /* 4 */
	tS32 alt; /* 8 */
	tU8 on_off; /* 12 */
	tU8 padding1; /* 13 */
	tU16 padding2; /* 14 */
} stbin_exec_enable_disable_position_hold_t;
#define stbin_exec_enable_disable_position_hold_t_size_send 13

//Frame stbin_exec_write_sw_config_all_blocks (cid=0x3A mid=0xF3)
typedef struct stbin_exec_write_sw_config_all_blocks {
	tU16 length; /* 0 */
	tU8 value[905]; /* 2 */
	tU8 padding1; /* 907 */
} stbin_exec_write_sw_config_all_blocks_t;
#define stbin_exec_write_sw_config_all_blocks_t_size_send 907

//Frame stbin_exec_set_gps_pos (cid=0x3A mid=0x1)
typedef struct stbin_exec_set_gps_pos {
	tS32 lat; /* 0 */
	tS32 lon; /* 4 */
	tS32 alt; /* 8 */
} stbin_exec_set_gps_pos_t;
#define stbin_exec_set_gps_pos_t_size_send 12

//Frame stbin_exec_set_diff_source (cid=0x3A mid=0xF2)
typedef struct stbin_exec_set_diff_source {
	tU8 diff_source; /* 0 */
	tU8 padding1; /* 1 */
	tU16 padding2; /* 2 */
} stbin_exec_set_diff_source_t;
#define stbin_exec_set_diff_source_t_size_send 1

//Frame stbin_exec_set_fix_rate (cid=0x3A mid=0x5)
typedef struct stbin_exec_set_fix_rate {
	tU16 fix_rate; /* 0 */
	tU16 padding2; /* 2 */
} stbin_exec_set_fix_rate_t;
#define stbin_exec_set_fix_rate_t_size_send 2

//Frame stbin_exec_nvm_item_inv (cid=0x3A mid=0x10)
typedef struct stbin_exec_nvm_item_inv {
	tS32 item_number; /* 0 */
	tU8 nvm_id; /* 4 */
	tU8 sat_id; /* 5 */
	tU16 padding2; /* 6 */
} stbin_exec_nvm_item_inv_t;
#define stbin_exec_nvm_item_inv_t_size_send 6

//Frame stbin_exec_gps_fw_update (cid=0x3A mid=0x11)
	// Have no payload
//Frame stbin_exec_stop_detection_on_off (cid=0x3A mid=0x13)
typedef struct stbin_exec_stop_detection_on_off {
	tU8 on_off; /* 0 */
	tU8 padding1; /* 1 */
	tU16 padding2; /* 2 */
} stbin_exec_stop_detection_on_off_t;
#define stbin_exec_stop_detection_on_off_t_size_send 1

//Frame stbin_exec_walking_mode_on_off (cid=0x3A mid=0x14)
typedef struct stbin_exec_walking_mode_on_off {
	tU8 on_off; /* 0 */
	tU8 padding1; /* 1 */
	tU16 padding2; /* 2 */
} stbin_exec_walking_mode_on_off_t;
#define stbin_exec_walking_mode_on_off_t_size_send 1

//Frame stbin_exec_rtc_write (cid=0x3A mid=0x18)
typedef struct stbin_exec_rtc_write {
	tS32 time_delta; /* 0 */
} stbin_exec_rtc_write_t;
#define stbin_exec_rtc_write_t_size_send 4

//Frame stbin_exec_fe_write (cid=0x3A mid=0x19)
typedef struct stbin_exec_fe_write {
	tU8 addr; /* 0 */
	tU8 data; /* 1 */
	tU16 padding2; /* 2 */
} stbin_exec_fe_write_t;
#define stbin_exec_fe_write_t_size_send 2

//Frame stbin_exec_sf_recovery (cid=0x3A mid=0x1A)
typedef struct stbin_exec_sf_recovery {
	tU8 on_off; /* 0 */
	tU8 padding1; /* 1 */
	tU16 padding2; /* 2 */
} stbin_exec_sf_recovery_t;
#define stbin_exec_sf_recovery_t_size_send 1

//Frame stbin_exec_adc_start (cid=0x3A mid=0x3)
typedef struct stbin_exec_adc_start {
	tU8 sel_line; /* 0 */
	tU8 adc_functional_mode; /* 1 */
	tU16 padding2; /* 2 */
} stbin_exec_adc_start_t;
#define stbin_exec_adc_start_t_size_send 2

//Frame stbin_exec_lowpower_onoff (cid=0x3A mid=0x20)
typedef struct stbin_exec_lowpower_onoff {
	tU32 fix_period; /* 0 */
	tU16 ms_off; /* 4 */
	tU16 fix_on_time; /* 6 */
	tU16 NoFixTimeout; /* 8 */
	tU16 NoFixOffTime; /* 10 */
	tU8 on_off; /* 12 */
	tU8 reduced_type; /* 13 */
	tU8 duty_cycle_on_off; /* 14 */
	tU8 const_type; /* 15 */
	tU8 ehpe_threshold; /* 16 */
	tU8 N_sats_reduced; /* 17 */
	tU8 periodic_mode; /* 18 */
	tU8 EPH_refresh; /* 19 */
	tU8 RTC_refresh; /* 20 */
	tU8 padding1; /* 21 */
	tU16 padding2; /* 22 */
} stbin_exec_lowpower_onoff_t;
#define stbin_exec_lowpower_onoff_t_size_send 21

//Section : Customer Flash Storage Write Requests (ClassId 0x3B)
//Frame stbin_exec_sqi_data_set (cid=0x3B mid=0x39)
typedef struct stbin_exec_sqi_data_set {
	tU32 word1; /* 0 */
	tU32 word2; /* 4 */
	tU32 word3; /* 8 */
	tU32 word4; /* 12 */
	tU32 word5; /* 16 */
	tU32 word6; /* 20 */
	tU32 word7; /* 24 */
	tU32 word8; /* 28 */
	tU16 offset; /* 32 */
	tU16 padding2; /* 34 */
} stbin_exec_sqi_data_set_t;
#define stbin_exec_sqi_data_set_t_size_send 34

//Frame stbin_exec_sqi_data_erase (cid=0x3B mid=0x38)
	// Have no payload
//Section : Output Messages Request (ClassId 0x01)
//Section : Error Messages (ClassId 0x00)
//Frame error_response (cid=0x0 mid=0x19)
	// Have no payload
//Section : Output Messages (ClassId 0x01)
#if defined(L2C_LINKED) && defined(L2C_LINKED_CHAN_ENABLED)
#define NB_MAX_TRAIM_SATS_REPORTED 32U
#define NB_MAX_TRK_REPORTED 32U
#else
#define NB_MAX_TRAIM_SATS_REPORTED 24U
#define NB_MAX_TRK_REPORTED 24U
#endif
//Frame outprocess_ecef (cid=0x1 mid=0x1)
typedef struct outprocess_ecef {
	tU32 iTOW; /* 0 */
	tU32 pAcc; /* 4 */
	tDouble ecefX; /* 8 */
	tDouble ecefY; /* 16 */
	tDouble ecefZ; /* 24 */
} outprocess_ecef_t;
#define outprocess_ecef_t_size_send 32

//Frame outProcess_pos_llh (cid=0x1 mid=0x2)
typedef struct outProcess_pos_llh {
	tU32 iTOW; /* 0 */
	tS32 lon; /* 4 */
	tS32 lat; /* 8 */
	tS32 height; /* 12 */
	tS32 hMSL; /* 16 */
	tS32 rms_pos_res; /* 20 */
	tU32 hAcc; /* 24 */
	tU32 vAcc; /* 28 */
} outProcess_pos_llh_t;
#define outProcess_pos_llh_t_size_send 32

//Frame outputprocess_status (cid=0x1 mid=0x3)
typedef struct outputprocess_status {
	tU32 iTOW; /* 0 */
	tU32 ttff_ms; /* 4 */
	tU32 msss; /* 8 */
	tU8 flags; /* 12 */
	tU8 fixStat; /* 13 */
	tU16 padding; /* 14 */
} outputprocess_status_t;
#define outputprocess_status_t_size_send 14

//Frame outputprocess_dop (cid=0x1 mid=0x4)
typedef struct outputprocess_dop {
	tU32 iTOW; /* 0 */
	tU16 gDOP; /* 4 */
	tU16 pDOP; /* 6 */
	tU16 tDOP; /* 8 */
	tU16 vDOP; /* 10 */
	tU16 hDOP; /* 12 */
	tU16 padding; /* 14 */
} outputprocess_dop_t;
#define outputprocess_dop_t_size_send 14

//Frame outputprocess_velecef (cid=0x1 mid=0x11)
typedef struct outputprocess_velecef {
	tU32 iTOW; /* 0 */
	tS32 ecefVX; /* 4 */
	tS32 ecefVY; /* 8 */
	tS32 ecefVZ; /* 12 */
	tS32 sAcc; /* 16 */
} outputprocess_velecef_t;
#define outputprocess_velecef_t_size_send 20

//Frame outputprocess_velneu (cid=0x1 mid=0x12)
typedef struct outputprocess_velneu {
	tU32 iTOW; /* 0 */
	tS32 velN; /* 4 */
	tS32 velE; /* 8 */
	tS32 velU; /* 12 */
	tU32 speed; /* 16 */
	tU32 gSpeed; /* 20 */
	tS32 heading; /* 24 */
	tS32 rms_vel_res; /* 28 */
	tU32 sAcc; /* 32 */
	tU32 cAcc; /* 36 */
} outputprocess_velneu_t;
#define outputprocess_velneu_t_size_send 40

//Frame outputprocess_timegnss (cid=0x1 mid=0x20)
typedef struct outputprocess_timegnss {
	tU32 iTOW; /* 0 */
	tS32 fTOW; /* 4 */
	tU16 week; /* 8 */
	tS8 leapS; /* 10 */
	tU8 valid; /* 11 */
	tU32 tAcc; /* 12 */
} outputprocess_timegnss_t;
#define outputprocess_timegnss_t_size_send 16

//Frame outputprocess_timeutc (cid=0x1 mid=0x21)
typedef struct outputprocess_timeutc {
	tU32 iTOW; /* 0 */
	tU32 tAcc; /* 4 */
	tS32 nano; /* 8 */
	tU16 year; /* 12 */
	tU8 month; /* 14 */
	tU8 day; /* 15 */
	tU8 hour; /* 16 */
	tU8 min; /* 17 */
	tU8 sec; /* 18 */
	tU8 valid; /* 19 */
} outputprocess_timeutc_t;
#define outputprocess_timeutc_t_size_send 20

//Frame outputprocess_svinfo (cid=0x1 mid=0x30)
typedef struct outputprocess_svinfo {
	tU8 chn; /* 0 */
	tU8 svid; /* 1 */
	tU8 flags; /* 2 */
	tS8 quality; /* 3 */
	tU16 azim; /* 4 */
	tS8 cno; /* 6 */
	tU8 elev; /* 7 */
} outputprocess_svinfo_t;
#define outputprocess_svinfo_t_size_send 8

//Frame outputprocess_dgps (cid=0x1 mid=0x31)
typedef struct outputprocess_dgps {
	tU32 iTOW; /* 0 */
	tS32 age; /* 4 */
	tU32 baseId; /* 8 */
	tU8 baseHealth; /* 12 */
	tU8 numCh; /* 13 */
	tS8 status; /* 14 */
	tU8 padding; /* 15 */
} outputprocess_dgps_t;
#define outputprocess_dgps_t_size_send 15

//Frame outputprocess_dgps_data (cid=0x1 mid=0x32)
typedef struct outputprocess_dgps_data {
	tU8 svid; /* 0 */
	tU8 chNum; /* 1 */
	tU16 ageC; /* 2 */
	tS32 prc; /* 4 */
	tS32 prrc; /* 8 */
} outputprocess_dgps_data_t;
#define outputprocess_dgps_data_t_size_send 12

//Frame outputprocess_ts (cid=0x1 mid=0x80)
typedef struct outputprocess_ts {
	tU8 dsp_satid; /* 0 */
	tU8 chn_id; /* 1 */
	tU8 flag_availability; /* 2 */
	tU8 pred_age_h; /* 3 */
	tS32 dsp_frequency; /* 4 */
	tDouble dsp_pseudorange; /* 8 */
	tU32 dsp_signal_strength; /* 16 */
	tU32 dsp_tracked_time; /* 20 */
	tS32 sat_pos_x; /* 24 */
	tS32 sat_pos_y; /* 28 */
	tS32 sat_pos_z; /* 32 */
	tS32 sat_vel_x; /* 36 */
	tS32 sat_vel_y; /* 40 */
	tS32 sat_vel_z; /* 44 */
	tS32 sat_range_corr; /* 48 */
	tS32 sat_atmos_corr; /* 52 */
	tS32 diff_range_corr; /* 56 */
	tS32 diff_range_rate_corr; /* 60 */
	tS8 pred_ephems_n; /* 64 */
	tS8 pred_time_distance_h; /* 65 */
	tU16 padding1; /* 66 */
	tU32 padding2; /* 68 */
} outputprocess_ts_t;
#define outputprocess_ts_t_size_send 66

//Frame outputprocess_tg (cid=0x1 mid=0x81)
typedef struct outputprocess_tg {
	tU32 iTOW; /* 0 */
	tU32 cpuTime; /* 4 */
	tS16 week; /* 8 */
	tS8 timeValidity; /* 10 */
	tS8 numSatUsed; /* 11 */
	tS32 nco; /* 12 */
} outputprocess_tg_t;
#define outputprocess_tg_t_size_send 16

//Frame outputprocess_Pos_Algo (cid=0x1 mid=0x85)
typedef struct outputprocess_Pos_Algo {
	tU32 iTOW; /* 0 */
	tS32 stoppedDuration; /* 4 */
	tU8 posAlgo; /* 8 */
	tU8 padding1; /* 9 */
	tU16 padding2; /* 10 */
} outputprocess_Pos_Algo_t;
#define outputprocess_Pos_Algo_t_size_send 9

//Frame outputprocess_RF (cid=0x1 mid=0x86)
typedef struct outputprocess_RF {
	tS32 ave_phase_noise; /* 0 */
	tS32 dsp_frequency; /* 4 */
	tS8 cno; /* 8 */
	tU8 dsp_satid; /* 9 */
	tU8 chn_id; /* 10 */
	tU8 padding; /* 11 */
} outputprocess_RF_t;
#define outputprocess_RF_t_size_send 11

//Frame outputprocess_Cov (cid=0x1 mid=0x87)
typedef struct outputprocess_Cov {
	tU32 iTOW; /* 0 */
	tU16 Pos_H_cov; /* 4 */
	tU16 Pos_N_cov; /* 6 */
	tU16 Pos_E_cov; /* 8 */
	tU16 Pos_V_cov; /* 10 */
	tU16 Vel_H_cov; /* 12 */
	tU16 Vel_N_cov; /* 14 */
	tU16 Vel_E_cov; /* 16 */
	tU16 Vel_V_cov; /* 18 */
} outputprocess_Cov_t;
#define outputprocess_Cov_t_size_send 20

//Frame outputprocess_GST (cid=0x1 mid=0x88)
typedef struct outputprocess_GST {
	tU32 iTOW; /* 0 */
	tU16 msec; /* 4 */
	tU16 ehpe; /* 6 */
	tU16 major_axis; /* 8 */
	tU16 minor_axis; /* 10 */
	tS16 angle; /* 12 */
	tU16 lat_err_dev; /* 14 */
	tU16 lon_err_dev; /* 16 */
	tU16 alt_err_dev; /* 18 */
	tU8 hour; /* 20 */
	tU8 min; /* 21 */
	tU8 sec; /* 22 */
	tU8 padding; /* 23 */
} outputprocess_GST_t;
#define outputprocess_GST_t_size_send 23

//Frame outputprocess_PPSData (cid=0x1 mid=0x89)
typedef struct outputprocess_PPSData {
	tU8 onOff; /* 0 */
	tU8 pps_valid; /* 1 */
	tU8 synch_valid; /* 2 */
	tU8 outMode; /* 3 */
	tU8 refTimeId; /* 4 */
	tU8 refConst; /* 5 */
	tU16 pulseDuration; /* 6 */
	tU16 pulseDelay; /* 8 */
	tU16 gpsRfDelay; /* 10 */
	tU16 glonassRfDelay; /* 12 */
	tU8 pulsePolarity; /* 14 */
	tU8 fixCondition; /* 15 */
	tU8 satTh; /* 16 */
	tU8 elevationMask; /* 17 */
	tU8 refsec; /* 18 */
	tU8 fixStat; /* 19 */
	tU32 constellationMask; /* 20 */
	tDouble ppsClockFreq; /* 24 */
	tDouble tcxoClockFreq; /* 32 */
	tU32 glonassUtcDelta_ns; /* 40 */
	tU32 gpsUtcDelta_ns; /* 44 */
	tU16 quantErr; /* 48 */
	tU8 gpsUtcDelta_s; /* 50 */
	tU8 used_sat; /* 51 */
	tU16 pad1; /* 52 */
	tU16 pad2; /* 54 */
} outputprocess_PPSData_t;
#define outputprocess_PPSData_t_size_send 52

//Frame outputprocess_HoldData (cid=0x1 mid=0x90)
typedef struct outputprocess_HoldData {
	tS32 lat_val; /* 0 */
	tS32 lon_val; /* 4 */
	tS32 height; /* 8 */
	tU8 onOff; /* 12 */
	tU8 pad1; /* 13 */
	tU16 pad2; /* 14 */
} outputprocess_HoldData_t;
#define outputprocess_HoldData_t_size_send 13

//Frame outputprocess_TraimData (cid=0x1 mid=0x91)
typedef struct outputprocess_TraimData {
	tU8 enabled; /* 0 */
	tU8 algo_state; /* 1 */
	tU8 used_sat; /* 2 */
	tU8 removed_sat; /* 3 */
	tU8 used_sats[24]; /* 4 */
	tU16 residual_tab[24]; /* 28 */
	tU8 removed_sats[24]; /* 76 */
	tU32 ave_error; /* 100 */
	tU16 alarm; /* 104 */
	tU8 refsec; /* 106 */
	tU8 pad1; /* 107 */
} outputprocess_TraimData_t;
#define outputprocess_TraimData_t_size_send 107

//Frame outputprocess_lowpowerData (cid=0x1 mid=0x92)
typedef struct outputprocess_lowpowerData {
	tU8 state; /* 0 */
	tU8 steadyState; /* 1 */
	tS16 eng1; /* 2 */
	tS16 eng2; /* 4 */
	tU16 ehpe; /* 6 */
	tS16 eng3; /* 8 */
	tU16 ehpe_average; /* 10 */
	tS16 eng4; /* 12 */
	tS16 eng5; /* 14 */
	tU8 gps_eph; /* 16 */
	tU8 glonass_eph; /* 17 */
	tU8 eng6; /* 18 */
	tU8 eng7; /* 19 */
	tS32 eng8; /* 20 */
	tU8 eng9; /* 24 */
	tU8 pad1; /* 25 */
	tU16 pad2; /* 26 */
} outputprocess_lowpowerData_t;
#define outputprocess_lowpowerData_t_size_send 25

//Frame outputprocess_cpuData (cid=0x1 mid=0x93)
typedef struct outputprocess_cpuData {
	tU16 cpu_usage; /* 0 */
	tU16 cpu_freq; /* 2 */
	tU8 pll_state; /* 4 */
	tU8 pad1; /* 5 */
} outputprocess_cpuData_t;
#define outputprocess_cpuData_t_size_send 5

//Frame outprocess_test_rf (cid=0x1 mid=0x94)
typedef struct outprocess_test_rf {
	tS32 frequency; /* 0 */
	tS32 phase_noise; /* 4 */
	tS8 cno; /* 8 */
	tU8 satid; /* 9 */
	tU16 pad1; /* 10 */
} outprocess_test_rf_t;
#define outprocess_test_rf_t_size_send 10

//Frame outputprocess_posres (cid=0x1 mid=0x95)
typedef struct outputprocess_posres {
	tU16 posRes[24]; /* 0 */
	tU16 rmsRes; /* 48 */
	tU8 cnt; /* 50 */
	tU8 pad1; /* 51 */
} outputprocess_posres_t;
#define outputprocess_posres_t_size_send 51

//Frame outputprocess_velres (cid=0x1 mid=0x96)
typedef struct outputprocess_velres {
	tU16 velRes[24]; /* 0 */
	tU16 rmsRes; /* 48 */
	tU8 cnt; /* 50 */
	tU8 pad1; /* 51 */
} outputprocess_velres_t;
#define outputprocess_velres_t_size_send 51

//Frame outputprocess_notch_filter_status (cid=0x1 mid=0x97)
typedef struct outputprocess_notch_filter_status {
	tS32 kfreq_now_gps; /* 0 */
	tS32 kfreq_now_gln; /* 4 */
	tU16 pwr_gps; /* 8 */
	tU16 pwr_gln; /* 10 */
	tU8 flags_gps; /* 12 */
	tU8 flags_gln; /* 13 */
	tU16 pad2; /* 14 */
} outputprocess_notch_filter_status_t;
#define outputprocess_notch_filter_status_t_size_send 14

//Frame outputprocess_read_errors (cid=0x1 mid=0x98)
typedef struct outputprocess_read_errors {
	tU32 error_code; /* 0 */
	tU32 param1; /* 4*/
	tU32 param2; /* 8*/
  tU32 param3; /* 12*/
	tU32 param4; /* 16*/
	tU32 param5; /* 20*/
  tU32 param6; /* 24*/
} outputprocess_read_errors_t;
#define outputprocess_read_errors_t_size_send 28

//Section : Test Response Messages (ClassId 0x4A)
//Frame stbin_exec_test_rtc_err_rsp (cid=0x4A mid=0x1C)
typedef struct stbin_exec_test_rtc_err_rsp {
	tU32 error; /* 0 */
	tU32 accuracy; /* 4 */
	tU32 tow; /* 8 */
	tU16 week; /* 12 */
	tU16 padding; /* 14 */
} stbin_exec_test_rtc_err_rsp_t;
#define stbin_exec_test_rtc_err_rsp_t_size_send 14

//Section : Initialization Messages Responses (ClassId 0x20)
//Section : Control Messages Responses (ClassId 0x12)
//Section : Read \PPSText Response Messages (ClassId 0x2D)
//Frame stbin_exec_pps_if_pulse_data_read_rsp (cid=0x2D mid=0x4A)
typedef struct stbin_exec_pps_if_pulse_data_read_rsp {
	tU8 outMode; /* 0 */
	tU8 refTimeId; /* 1 */
	tU16 pulseDelay; /* 2 */
	tU16 pulseDuration; /* 4 */
	tU16 pulsePolarity; /* 6 */
} stbin_exec_pps_if_pulse_data_read_rsp_t;
#define stbin_exec_pps_if_pulse_data_read_rsp_t_size_send 8

//Frame stbin_exec_pps_if_timing_data_read_rsp (cid=0x2D mid=0x4B)
typedef struct stbin_exec_pps_if_timing_data_read_rsp {
	tU32 constellationMask; /* 0 */
	tU16 gpsRfDelay; /* 4 */
	tU16 glonassRfDelay; /* 6 */
	tU8 fixCondition; /* 8 */
	tU8 satTh; /* 9 */
	tU8 elevationMask; /* 10 */
	tU8 pad1; /* 11 */
} stbin_exec_pps_if_timing_data_read_rsp_t;
#define stbin_exec_pps_if_timing_data_read_rsp_t_size_send 11

//Frame stbin_exec_pps_if_pos_hold_data_read_rsp (cid=0x2D mid=0x4C)
typedef struct stbin_exec_pps_if_pos_hold_data_read_rsp {
	tS32 lat_val; /* 0 */
	tS32 lon_val; /* 4 */
	tS32 height; /* 8 */
	tU8 posHoldOnOff; /* 12 */
	tU8 pad1; /* 13 */
	tU16 pad2; /* 14 */
} stbin_exec_pps_if_pos_hold_data_read_rsp_t;
#define stbin_exec_pps_if_pos_hold_data_read_rsp_t_size_send 13

//Frame stbin_exec_pps_if_traim_read_rsp (cid=0x2D mid=0x4D)
typedef struct stbin_exec_pps_if_traim_read_rsp {
	tU8 enabled; /* 0 */
	tU8 algo_state; /* 1 */
	tU8 used_sat; /* 2 */
	tU8 removed_sat; /* 3 */
	tU32 ave_error; /* 4 */
	tU8 used_sats[24]; /* 8 */
	tU16 residual_tab[24]; /* 32 */
	tU8 removed_sats[24]; /* 80 */
} stbin_exec_pps_if_traim_read_rsp_t;
#define stbin_exec_pps_if_traim_read_rsp_t_size_send 104

//Section : Write \PPSText Response Messages (ClassId 0x3D)
//Section : Read Messages Responses (ClassId 0x2A)
//Frame dumpEphe (cid=0x2A mid=0xFE)
typedef struct dumpEphe {
	tU8 value[64]; /* 0 */
	tU8 dsp_satid; /* 64 */
	tU8 padding1; /* 65 */
	tU16 padding2; /* 66 */
} dumpEphe_t;
#define dumpEphe_t_size_send 65

//Frame dumpAlmans (cid=0x2A mid=0xFD)
typedef struct dumpAlmans {
	tU8 value[40]; /* 0 */
	tU8 dsp_satid; /* 40 */
	tU8 padding1; /* 41 */
	tU16 padding2; /* 42 */
} dumpAlmans_t;
#define dumpAlmans_t_size_send 41

//Frame getSwVers (cid=0x2A mid=0x20)
typedef struct getSwVers {
	tChar swVersID[STBIN_LEN_STRING]; /* 0 */
} getSwVers_t;
#define getSwVers_t_size_send 24

//Frame checkTask (cid=0x2A mid=0x21)
typedef struct checkTask {
	tChar taskIdStr[STBIN_LEN_STRING]; /* 0 */
	tS32 task_get_priority; /* 24 */
	tS32 task_get_stack_base; /* 28 */
	tS32 task_get_stack_ptr; /* 32 */
	tS32 size; /* 36 */
	tS32 used; /* 40 */
} checkTask_t;
#define checkTask_t_size_send 44

//Frame checkCpuUsage (cid=0x2A mid=0x22)
typedef struct checkCpuUsage {
	tChar taskNameId[STBIN_LEN_STRING]; /* 0 */
	tU32 cpuUsage_CurrentTask; /* 24 */
} checkCpuUsage_t;
#define checkCpuUsage_t_size_send 28

//Frame check_heap (cid=0x2A mid=0x23)
typedef struct check_heap {
	tU32 memory_getheapsize; /* 0 */
	tU32 memory_getheapfree; /* 4 */
} check_heap_t;
#define check_heap_t_size_send 8

//Frame read_rtc_time (cid=0x2A mid=0x30)
typedef struct read_rtc_time {
	tU16 year; /* 0 */
	tU8 month; /* 2 */
	tU8 day; /* 3 */
	tU8 hour; /* 4 */
	tU8 min; /* 5 */
	tU8 sec; /* 6 */
	tU8 millisec; /* 7 */
	tU8 time_valid; /* 8 */
	tU8 rtc_status; /* 9 */
	tU16 padding; /* 10 */
} read_rtc_time_t;
#define read_rtc_time_t_size_send 10

//Frame sw_config_get_par_val_Char (cid=0x2A mid=0xFB)
typedef struct sw_config_get_par_val_Char {
	tU8 value; /* 0 */
	tU8 configType; /* 1 */
	tU8 configSection; /* 2 */
	tU8 configParamId; /* 3 */
} sw_config_get_par_val_Char_t;
#define sw_config_get_par_val_Char_t_size_send 4

//Frame sw_config_get_par_val_Int (cid=0x2A mid=0xFA)
typedef struct sw_config_get_par_val_Int {
	tS32 value; /* 0 */
	tU8 configType; /* 4 */
	tU8 configSection; /* 5 */
	tU8 configParamId; /* 6 */
	tU8 padding; /* 7 */
} sw_config_get_par_val_Int_t;
#define sw_config_get_par_val_Int_t_size_send 7

//Frame sw_config_get_par_val_UInt (cid=0x2A mid=0xF9)
typedef struct sw_config_get_par_val_UInt {
	tU32 value; /* 0 */
	tU8 configType; /* 4 */
	tU8 configSection; /* 5 */
	tU8 configParamId; /* 6 */
	tU8 padding; /* 7 */
} sw_config_get_par_val_UInt_t;
#define sw_config_get_par_val_UInt_t_size_send 7

//Frame sw_config_get_par_val_Double (cid=0x2A mid=0xF8)
typedef struct sw_config_get_par_val_Double {
	tDouble value; /* 0 */
	tU8 configType; /* 8 */
	tU8 configSection; /* 9 */
	tU8 configParamId; /* 10 */
	tU8 padding1; /* 11 */
	tU32 padding2; /* 12 */
} sw_config_get_par_val_Double_t;
#define sw_config_get_par_val_Double_t_size_send 11

//Frame sw_config_get_par_val_Dops (cid=0x2A mid=0xF7)
typedef struct sw_config_get_par_val_Dops {
	tU8 pdop; /* 0 */
	tU8 vdop; /* 1 */
	tU8 hdop; /* 2 */
	tU8 gdop; /* 3 */
	tU8 configType; /* 4 */
	tU8 configSection; /* 5 */
	tU8 configParamId; /* 6 */
	tU8 padding; /* 7 */
} sw_config_get_par_val_Dops_t;
#define sw_config_get_par_val_Dops_t_size_send 7

//Frame sw_config_get_par_val_String (cid=0x2A mid=0xF6)
typedef struct sw_config_get_par_val_String {
	tChar value[STBIN_SW_CONFIG_TEXT_LENGTH]; /* 0 */
	tU8 configType; /* 72 */
	tU8 configSection; /* 73 */
	tU8 configParamId; /* 74 */
	tU8 padding; /* 75 */
} sw_config_get_par_val_String_t;
#define sw_config_get_par_val_String_t_size_send 75

//Frame get_algo_status (cid=0x2A mid=0xF5)
typedef struct get_algo_status {
	tU8 algo_type; /* 0 */
	tU8 algo_status; /* 1 */
	tU16 padding; /* 2 */
} get_algo_status_t;
#define get_algo_status_t_size_send 2

//Frame read_datum_selection (cid=0x2A mid=0xF4)
typedef struct read_datum_selection {
	tU8 datum; /* 0 */
	tU8 padding1; /* 1 */
	tU16 padding2; /* 2 */
} read_datum_selection_t;
#define read_datum_selection_t_size_send 1

//Frame read_sw_config_all_blocks (cid=0x2A mid=0xF3)
typedef struct read_sw_config_all_blocks {
	tU16 length; /* 0 */
	tU8 config_type; /* 2 */
	tU8 value[905]; /* 3 */
} read_sw_config_all_blocks_t;
#define read_sw_config_all_blocks_t_size_send 908

//Frame stbin_exec_dump_fe (cid=0x2A mid=0x2E)
typedef struct stbin_exec_dump_fe {
	tU8 value[60]; /* 0 */
} stbin_exec_dump_fe_t;
#define stbin_exec_dump_fe_t_size_send 60

//Frame get_diff_source (cid=0x2A mid=0xF2)
typedef struct get_diff_source {
	tU8 diff_source_selected; /* 0 */
	tU8 padding1; /* 1 */
	tU16 padding2; /* 2 */
} get_diff_source_t;
#define get_diff_source_t_size_send 1

//Frame adc_read (cid=0x2A mid=0x24)
typedef struct adc_read {
	tU32 data_read; /* 0 */
	tU8 ain; /* 4 */
	tU8 padding1; /* 5 */
	tU16 padding2; /* 6 */
} adc_read_t;
#define adc_read_t_size_send 5

//Frame getAllSwVers (cid=0x2A mid=0x25)
typedef struct getAllSwVers {
	tU8 idx; /* 0 */
	tChar SWID[STBIN_LEN_STRING]; /* 1 */
	tU8 padding1; /* 25 */
	tU16 padding2; /* 26 */
} getAllSwVers_t;
#define getAllSwVers_t_size_send 25

//Section : Read Messages Responses (ClassId 0x2B)
//Frame sqi_data_get (cid=0x2B mid=0x4E)
typedef struct sqi_data_get {
	tU32 dest_addr; /* 0 */
	tU32 word1; /* 4 */
	tU32 word2; /* 8 */
	tU32 word3; /* 12 */
	tU32 word4; /* 16 */
	tU32 word5; /* 20 */
	tU32 word6; /* 24 */
	tU32 word7; /* 28 */
	tU32 word8; /* 32 */
} sqi_data_get_t;
#define sqi_data_get_t_size_send 36

//Section : Write Responses (ClassId 0x3A)
//Section : Customer Flash Storage Write Responses (ClassId 0x3B)
//Frame sqi_data_set (cid=0x3B mid=0x39)
typedef struct sqi_data_set {
	tU32 dest_addr; /* 0 */
} sqi_data_set_t;
#define sqi_data_set_t_size_send 4

//Section : Reset messages (ClassId 0x5A)
#define STBIN_BASE_MAX_PAYLOAD_SIZE 908U
#ifndef STBIN_MAX_PAYLOAD_SIZE
#  error Maximal payload size must be defined when this code is reached
#endif
#if STBIN_MAX_PAYLOAD_SIZE < STBIN_BASE_MAX_PAYLOAD_SIZE
#  error Maximal payload size must be reviewed
#endif
//Above code is automatically generated (See rep_crm/tools/stbin/generators)
