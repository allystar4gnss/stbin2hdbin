//This code is automatically generated (See rep_crm/tools/stbin/generators)
#define COMPILER_MIN_ARRAY_SIZE 1U
//Section : Interface Control Messages (ClassId 0x12)


//Frame stbin_return_in_nmea_communication (cid=0x12 mid=0x78)
#define stbin_return_in_nmea_communication_MAP(sname, msg, len, p_result)\
	/*lint -e{9087} cast performed between a pointer to object type and a pointer to a different object type */ \
	stbin_return_in_nmea_communication_t *sname = (stbin_return_in_nmea_communication_t *)msg;\
	GPS_DEBUG_MSG(("STBIN Received Frame stbin_return_in_nmea_communication\r\n"));\
	GPS_DEBUG_MSG(("STBIN control=0x%X\r\n", sname->control));\
	if(0U < sname->control) {\
		GPS_DEBUG_MSG(("STBIN invalid control=%d\r\n", sname->control));\
		*(p_result) = STBIN_FAILED; }\
	if(len != sizeof(*sname)) {\
		GPS_DEBUG_MSG(("STBIN frame stbin_return_in_nmea_communication received with Payload length %d vs %d\r\n", len, sizeof(*sname) - 0U));\
		*(p_result) = STBIN_FAILED; }

//Test structure size against computed size
typedef tS8 Teststbin_return_in_nmea_communication_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(stbin_return_in_nmea_communication_t)-1U)];
typedef tS8 Teststbin_return_in_nmea_communication_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+1U-sizeof(stbin_return_in_nmea_communication_t))];




//Frame stbin_control_output_req (cid=0x12 mid=0x81)
#define stbin_control_output_req_MAP(sname, msg, len, p_result)\
	/*lint -e{9087} cast performed between a pointer to object type and a pointer to a different object type */ \
	stbin_control_output_req_t *sname = (stbin_control_output_req_t *)msg;\
	GPS_DEBUG_MSG(("STBIN Received Frame stbin_control_output_req\r\n"));\
	GPS_DEBUG_MSG(("STBIN onOff=0x%X\r\n", sname->onOff));\
	if(1U < sname->onOff) {\
		GPS_DEBUG_MSG(("STBIN invalid onOff=%d\r\n", sname->onOff));\
		*(p_result) = STBIN_FAILED; }\
	if(len != sizeof(*sname)) {\
		GPS_DEBUG_MSG(("STBIN frame stbin_control_output_req received with Payload length %d vs %d\r\n", len, sizeof(*sname) - 0U));\
		*(p_result) = STBIN_FAILED; }

//Test structure size against computed size
typedef tS8 Teststbin_control_output_req_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(stbin_control_output_req_t)-1U)];
typedef tS8 Teststbin_control_output_req_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+1U-sizeof(stbin_control_output_req_t))];


//Section : Test Request Messages (ClassId 0x4A)


//Frame stbin_exec_test_on_req (cid=0x4A mid=0x16)
#define stbin_exec_test_on_req_MAP(sname, msg, len, p_result)\
	/*lint -e{9087} cast performed between a pointer to object type and a pointer to a different object type */ \
	stbin_exec_test_on_req_t *sname = (stbin_exec_test_on_req_t *)msg;\
	GPS_DEBUG_MSG(("STBIN Received Frame stbin_exec_test_on_req\r\n"));\
	GPS_DEBUG_MSG(("STBIN test_type=0x%X\r\n", sname->test_type));\
	if((1U > sname->test_type) || (3U < sname->test_type)) {\
		GPS_DEBUG_MSG(("STBIN invalid test_type=%d\r\n", sname->test_type));\
		*(p_result) = STBIN_FAILED; }\
	GPS_DEBUG_MSG(("STBIN threshold=%d\r\n", sname->threshold));\
	STBIN_FROM_LINK_ENDIAN_CONV_tU16(&(sname->satId));\
	GPS_DEBUG_MSG(("STBIN satId=%d\r\n", sname->satId));\
	if(len != sizeof(*sname)) {\
		GPS_DEBUG_MSG(("STBIN frame stbin_exec_test_on_req received with Payload length %d vs %d\r\n", len, sizeof(*sname) - 0U));\
		*(p_result) = STBIN_FAILED; }

//Test structure size against computed size
typedef tS8 Teststbin_exec_test_on_req_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(stbin_exec_test_on_req_t)-4U)];
typedef tS8 Teststbin_exec_test_on_req_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+4U-sizeof(stbin_exec_test_on_req_t))];




//Frame stbin_exec_test_add_req (cid=0x4A mid=0x17)
#define stbin_exec_test_add_req_MAP(sname, msg, len, p_result)\
	/*lint -e{9087} cast performed between a pointer to object type and a pointer to a different object type */ \
	stbin_exec_test_add_req_t *sname = (stbin_exec_test_add_req_t *)msg;\
	GPS_DEBUG_MSG(("STBIN Received Frame stbin_exec_test_add_req\r\n"));\
	GPS_DEBUG_MSG(("STBIN test_type=0x%X\r\n", sname->test_type));\
	if((1U > sname->test_type) || (3U < sname->test_type)) {\
		GPS_DEBUG_MSG(("STBIN invalid test_type=%d\r\n", sname->test_type));\
		*(p_result) = STBIN_FAILED; }\
	GPS_DEBUG_MSG(("STBIN threshold=%d\r\n", sname->threshold));\
	STBIN_FROM_LINK_ENDIAN_CONV_tU16(&(sname->satId));\
	GPS_DEBUG_MSG(("STBIN satId=%d\r\n", sname->satId));\
	if(len != sizeof(*sname)) {\
		GPS_DEBUG_MSG(("STBIN frame stbin_exec_test_add_req received with Payload length %d vs %d\r\n", len, sizeof(*sname) - 0U));\
		*(p_result) = STBIN_FAILED; }

//Test structure size against computed size
typedef tS8 Teststbin_exec_test_add_req_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(stbin_exec_test_add_req_t)-4U)];
typedef tS8 Teststbin_exec_test_add_req_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+4U-sizeof(stbin_exec_test_add_req_t))];




//Frame stbin_exec_test_del_req (cid=0x4A mid=0x18)
#define stbin_exec_test_del_req_MAP(sname, msg, len, p_result)\
	/*lint -e{9087} cast performed between a pointer to object type and a pointer to a different object type */ \
	stbin_exec_test_del_req_t *sname = (stbin_exec_test_del_req_t *)msg;\
	GPS_DEBUG_MSG(("STBIN Received Frame stbin_exec_test_del_req\r\n"));\
	STBIN_FROM_LINK_ENDIAN_CONV_tU16(&(sname->satId));\
	GPS_DEBUG_MSG(("STBIN satId=%d\r\n", sname->satId));\
	if(len != sizeof(*sname)) {\
		GPS_DEBUG_MSG(("STBIN frame stbin_exec_test_del_req received with Payload length %d vs %d\r\n", len, sizeof(*sname) - 0U));\
		*(p_result) = STBIN_FAILED; }

//Test structure size against computed size
typedef tS8 Teststbin_exec_test_del_req_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(stbin_exec_test_del_req_t)-2U)];
typedef tS8 Teststbin_exec_test_del_req_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+2U-sizeof(stbin_exec_test_del_req_t))];




//Frame stbin_exec_test_off_req (cid=0x4A mid=0x19)
#define stbin_exec_test_off_req_MAP(sname, msg, len, p_result)\
	GPS_DEBUG_MSG(("STBIN Received Frame stbin_exec_test_off_req\r\n"));\
	if(len != 0U) {\
		GPS_DEBUG_MSG(("STBIN Dataless frame stbin_exec_test_off_req received with Payload length %d\r\n", len));\
		*(p_result) = STBIN_FAILED; }



//Frame stbin_exec_test_rtc_testOnOff_req (cid=0x4A mid=0x1A)
#define stbin_exec_test_rtc_testOnOff_req_MAP(sname, msg, len, p_result)\
	/*lint -e{9087} cast performed between a pointer to object type and a pointer to a different object type */ \
	stbin_exec_test_rtc_testOnOff_req_t *sname = (stbin_exec_test_rtc_testOnOff_req_t *)msg;\
	GPS_DEBUG_MSG(("STBIN Received Frame stbin_exec_test_rtc_testOnOff_req\r\n"));\
	GPS_DEBUG_MSG(("STBIN onOff=0x%X\r\n", sname->onOff));\
	if(1U < sname->onOff) {\
		GPS_DEBUG_MSG(("STBIN invalid onOff=%d\r\n", sname->onOff));\
		*(p_result) = STBIN_FAILED; }\
	if(len != sizeof(*sname)) {\
		GPS_DEBUG_MSG(("STBIN frame stbin_exec_test_rtc_testOnOff_req received with Payload length %d vs %d\r\n", len, sizeof(*sname) - 0U));\
		*(p_result) = STBIN_FAILED; }

//Test structure size against computed size
typedef tS8 Teststbin_exec_test_rtc_testOnOff_req_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(stbin_exec_test_rtc_testOnOff_req_t)-1U)];
typedef tS8 Teststbin_exec_test_rtc_testOnOff_req_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+1U-sizeof(stbin_exec_test_rtc_testOnOff_req_t))];




//Frame stbin_exec_test_trkjammer_req (cid=0x4A mid=0x1B)
#define stbin_exec_test_trkjammer_req_MAP(sname, msg, len, p_result)\
	/*lint -e{9087} cast performed between a pointer to object type and a pointer to a different object type */ \
	stbin_exec_test_trkjammer_req_t *sname = (stbin_exec_test_trkjammer_req_t *)msg;\
	GPS_DEBUG_MSG(("STBIN Received Frame stbin_exec_test_trkjammer_req\r\n"));\
	GPS_DEBUG_MSG(("STBIN onOff=0x%X\r\n", sname->onOff));\
	if(1U < sname->onOff) {\
		GPS_DEBUG_MSG(("STBIN invalid onOff=%d\r\n", sname->onOff));\
		*(p_result) = STBIN_FAILED; }\
	if(len != sizeof(*sname)) {\
		GPS_DEBUG_MSG(("STBIN frame stbin_exec_test_trkjammer_req received with Payload length %d vs %d\r\n", len, sizeof(*sname) - 0U));\
		*(p_result) = STBIN_FAILED; }

//Test structure size against computed size
typedef tS8 Teststbin_exec_test_trkjammer_req_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(stbin_exec_test_trkjammer_req_t)-1U)];
typedef tS8 Teststbin_exec_test_trkjammer_req_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+1U-sizeof(stbin_exec_test_trkjammer_req_t))];




//Frame stbin_exec_test_rtc_err_req (cid=0x4A mid=0x1C)
#define stbin_exec_test_rtc_err_req_MAP(sname, msg, len, p_result)\
	/*lint -e{9087} cast performed between a pointer to object type and a pointer to a different object type */ \
	stbin_exec_test_rtc_err_req_t *sname = (stbin_exec_test_rtc_err_req_t *)msg;\
	GPS_DEBUG_MSG(("STBIN Received Frame stbin_exec_test_rtc_err_req\r\n"));\
	STBIN_FROM_LINK_ENDIAN_CONV_tU32(&(sname->error));\
	GPS_DEBUG_MSG(("STBIN error=%d\r\n", sname->error));\
	STBIN_FROM_LINK_ENDIAN_CONV_tU32(&(sname->accuracy));\
	GPS_DEBUG_MSG(("STBIN accuracy=%d\r\n", sname->accuracy));\
	if(len != sizeof(*sname)) {\
		GPS_DEBUG_MSG(("STBIN frame stbin_exec_test_rtc_err_req received with Payload length %d vs %d\r\n", len, sizeof(*sname) - 0U));\
		*(p_result) = STBIN_FAILED; }

//Test structure size against computed size
typedef tS8 Teststbin_exec_test_rtc_err_req_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(stbin_exec_test_rtc_err_req_t)-8U)];
typedef tS8 Teststbin_exec_test_rtc_err_req_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+8U-sizeof(stbin_exec_test_rtc_err_req_t))];


//Section : \PPSText Read Request Messages (ClassId 0x2D)


//Frame stbin_exec_pps_if_pulse_data_read_req (cid=0x2D mid=0x4A)
#define stbin_exec_pps_if_pulse_data_read_req_MAP(sname, msg, len, p_result)\
	GPS_DEBUG_MSG(("STBIN Received Frame stbin_exec_pps_if_pulse_data_read_req\r\n"));\
	if(len != 0U) {\
		GPS_DEBUG_MSG(("STBIN Dataless frame stbin_exec_pps_if_pulse_data_read_req received with Payload length %d\r\n", len));\
		*(p_result) = STBIN_FAILED; }



//Frame stbin_exec_pps_if_timing_data_read_req (cid=0x2D mid=0x4B)
#define stbin_exec_pps_if_timing_data_read_req_MAP(sname, msg, len, p_result)\
	GPS_DEBUG_MSG(("STBIN Received Frame stbin_exec_pps_if_timing_data_read_req\r\n"));\
	if(len != 0U) {\
		GPS_DEBUG_MSG(("STBIN Dataless frame stbin_exec_pps_if_timing_data_read_req received with Payload length %d\r\n", len));\
		*(p_result) = STBIN_FAILED; }



//Frame stbin_exec_pps_if_pos_hold_data_read_req (cid=0x2D mid=0x4C)
#define stbin_exec_pps_if_pos_hold_data_read_req_MAP(sname, msg, len, p_result)\
	GPS_DEBUG_MSG(("STBIN Received Frame stbin_exec_pps_if_pos_hold_data_read_req\r\n"));\
	if(len != 0U) {\
		GPS_DEBUG_MSG(("STBIN Dataless frame stbin_exec_pps_if_pos_hold_data_read_req received with Payload length %d\r\n", len));\
		*(p_result) = STBIN_FAILED; }



//Frame stbin_exec_pps_if_traim_read_req (cid=0x2D mid=0x4D)
#define stbin_exec_pps_if_traim_read_req_MAP(sname, msg, len, p_result)\
	GPS_DEBUG_MSG(("STBIN Received Frame stbin_exec_pps_if_traim_read_req\r\n"));\
	if(len != 0U) {\
		GPS_DEBUG_MSG(("STBIN Dataless frame stbin_exec_pps_if_traim_read_req received with Payload length %d\r\n", len));\
		*(p_result) = STBIN_FAILED; }

//Section : \PPSText Write Request Messages (ClassId 0x3D)


//Frame stbin_exec_pps_if_on_off_write_req (cid=0x3D mid=0x24)
#define stbin_exec_pps_if_on_off_write_req_MAP(sname, msg, len, p_result)\
	/*lint -e{9087} cast performed between a pointer to object type and a pointer to a different object type */ \
	stbin_exec_pps_if_on_off_write_req_t *sname = (stbin_exec_pps_if_on_off_write_req_t *)msg;\
	GPS_DEBUG_MSG(("STBIN Received Frame stbin_exec_pps_if_on_off_write_req\r\n"));\
	GPS_DEBUG_MSG(("STBIN onOff=0x%X\r\n", sname->onOff));\
	if(1U < sname->onOff) {\
		GPS_DEBUG_MSG(("STBIN invalid onOff=%d\r\n", sname->onOff));\
		*(p_result) = STBIN_FAILED; }\
	if(len != sizeof(*sname)) {\
		GPS_DEBUG_MSG(("STBIN frame stbin_exec_pps_if_on_off_write_req received with Payload length %d vs %d\r\n", len, sizeof(*sname) - 0U));\
		*(p_result) = STBIN_FAILED; }

//Test structure size against computed size
typedef tS8 Teststbin_exec_pps_if_on_off_write_req_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(stbin_exec_pps_if_on_off_write_req_t)-1U)];
typedef tS8 Teststbin_exec_pps_if_on_off_write_req_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+1U-sizeof(stbin_exec_pps_if_on_off_write_req_t))];




//Frame stbin_exec_pps_if_output_mode_write_req (cid=0x3D mid=0x25)
#define stbin_exec_pps_if_output_mode_write_req_MAP(sname, msg, len, p_result)\
	/*lint -e{9087} cast performed between a pointer to object type and a pointer to a different object type */ \
	stbin_exec_pps_if_output_mode_write_req_t *sname = (stbin_exec_pps_if_output_mode_write_req_t *)msg;\
	GPS_DEBUG_MSG(("STBIN Received Frame stbin_exec_pps_if_output_mode_write_req\r\n"));\
	GPS_DEBUG_MSG(("STBIN outMode=0x%X\r\n", sname->outMode));\
	if(2U < sname->outMode) {\
		GPS_DEBUG_MSG(("STBIN invalid outMode=%d\r\n", sname->outMode));\
		*(p_result) = STBIN_FAILED; }\
	if(len != sizeof(*sname)) {\
		GPS_DEBUG_MSG(("STBIN frame stbin_exec_pps_if_output_mode_write_req received with Payload length %d vs %d\r\n", len, sizeof(*sname) - 0U));\
		*(p_result) = STBIN_FAILED; }

//Test structure size against computed size
typedef tS8 Teststbin_exec_pps_if_output_mode_write_req_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(stbin_exec_pps_if_output_mode_write_req_t)-1U)];
typedef tS8 Teststbin_exec_pps_if_output_mode_write_req_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+1U-sizeof(stbin_exec_pps_if_output_mode_write_req_t))];




//Frame stbin_exec_pps_if_ref_constellation_write_req (cid=0x3D mid=0x26)
#define stbin_exec_pps_if_ref_constellation_write_req_MAP(sname, msg, len, p_result)\
	/*lint -e{9087} cast performed between a pointer to object type and a pointer to a different object type */ \
	stbin_exec_pps_if_ref_constellation_write_req_t *sname = (stbin_exec_pps_if_ref_constellation_write_req_t *)msg;\
	GPS_DEBUG_MSG(("STBIN Received Frame stbin_exec_pps_if_ref_constellation_write_req\r\n"));\
	GPS_DEBUG_MSG(("STBIN refConst=0x%X\r\n", sname->refConst));\
	if(6U < sname->refConst) {\
		GPS_DEBUG_MSG(("STBIN invalid refConst=%d\r\n", sname->refConst));\
		*(p_result) = STBIN_FAILED; }\
	if(len != sizeof(*sname)) {\
		GPS_DEBUG_MSG(("STBIN frame stbin_exec_pps_if_ref_constellation_write_req received with Payload length %d vs %d\r\n", len, sizeof(*sname) - 0U));\
		*(p_result) = STBIN_FAILED; }

//Test structure size against computed size
typedef tS8 Teststbin_exec_pps_if_ref_constellation_write_req_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(stbin_exec_pps_if_ref_constellation_write_req_t)-1U)];
typedef tS8 Teststbin_exec_pps_if_ref_constellation_write_req_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+1U-sizeof(stbin_exec_pps_if_ref_constellation_write_req_t))];




//Frame stbin_exec_pps_if_ref_time_write_req (cid=0x3D mid=0x27)
#define stbin_exec_pps_if_ref_time_write_req_MAP(sname, msg, len, p_result)\
	/*lint -e{9087} cast performed between a pointer to object type and a pointer to a different object type */ \
	stbin_exec_pps_if_ref_time_write_req_t *sname = (stbin_exec_pps_if_ref_time_write_req_t *)msg;\
	GPS_DEBUG_MSG(("STBIN Received Frame stbin_exec_pps_if_ref_time_write_req\r\n"));\
	GPS_DEBUG_MSG(("STBIN refTimeId=0x%X\r\n", sname->refTimeId));\
	if(4U < sname->refTimeId) {\
		GPS_DEBUG_MSG(("STBIN invalid refTimeId=%d\r\n", sname->refTimeId));\
		*(p_result) = STBIN_FAILED; }\
	if(len != sizeof(*sname)) {\
		GPS_DEBUG_MSG(("STBIN frame stbin_exec_pps_if_ref_time_write_req received with Payload length %d vs %d\r\n", len, sizeof(*sname) - 0U));\
		*(p_result) = STBIN_FAILED; }

//Test structure size against computed size
typedef tS8 Teststbin_exec_pps_if_ref_time_write_req_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(stbin_exec_pps_if_ref_time_write_req_t)-1U)];
typedef tS8 Teststbin_exec_pps_if_ref_time_write_req_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+1U-sizeof(stbin_exec_pps_if_ref_time_write_req_t))];




//Frame stbin_exec_pps_if_pulse_delay_write_req (cid=0x3D mid=0x28)
#define stbin_exec_pps_if_pulse_delay_write_req_MAP(sname, msg, len, p_result)\
	/*lint -e{9087} cast performed between a pointer to object type and a pointer to a different object type */ \
	stbin_exec_pps_if_pulse_delay_write_req_t *sname = (stbin_exec_pps_if_pulse_delay_write_req_t *)msg;\
	GPS_DEBUG_MSG(("STBIN Received Frame stbin_exec_pps_if_pulse_delay_write_req\r\n"));\
	STBIN_FROM_LINK_ENDIAN_CONV_tU16(&(sname->pulseDelay));\
	GPS_DEBUG_MSG(("STBIN pulseDelay=%d\r\n", sname->pulseDelay));\
	if(len != sizeof(*sname)) {\
		GPS_DEBUG_MSG(("STBIN frame stbin_exec_pps_if_pulse_delay_write_req received with Payload length %d vs %d\r\n", len, sizeof(*sname) - 0U));\
		*(p_result) = STBIN_FAILED; }

//Test structure size against computed size
typedef tS8 Teststbin_exec_pps_if_pulse_delay_write_req_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(stbin_exec_pps_if_pulse_delay_write_req_t)-2U)];
typedef tS8 Teststbin_exec_pps_if_pulse_delay_write_req_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+2U-sizeof(stbin_exec_pps_if_pulse_delay_write_req_t))];




//Frame stbin_exec_pps_if_pulse_duration_write_req (cid=0x3D mid=0x29)
#define stbin_exec_pps_if_pulse_duration_write_req_MAP(sname, msg, len, p_result)\
	/*lint -e{9087} cast performed between a pointer to object type and a pointer to a different object type */ \
	stbin_exec_pps_if_pulse_duration_write_req_t *sname = (stbin_exec_pps_if_pulse_duration_write_req_t *)msg;\
	GPS_DEBUG_MSG(("STBIN Received Frame stbin_exec_pps_if_pulse_duration_write_req\r\n"));\
	STBIN_FROM_LINK_ENDIAN_CONV_tU16(&(sname->pulseDuration));\
	GPS_DEBUG_MSG(("STBIN pulseDuration=0x%X\r\n", sname->pulseDuration));\
	if((100U > sname->pulseDuration) || (900U < sname->pulseDuration)) {\
		GPS_DEBUG_MSG(("STBIN invalid pulseDuration=%d\r\n", sname->pulseDuration));\
		*(p_result) = STBIN_FAILED; }\
	if(len != sizeof(*sname)) {\
		GPS_DEBUG_MSG(("STBIN frame stbin_exec_pps_if_pulse_duration_write_req received with Payload length %d vs %d\r\n", len, sizeof(*sname) - 0U));\
		*(p_result) = STBIN_FAILED; }

//Test structure size against computed size
typedef tS8 Teststbin_exec_pps_if_pulse_duration_write_req_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(stbin_exec_pps_if_pulse_duration_write_req_t)-2U)];
typedef tS8 Teststbin_exec_pps_if_pulse_duration_write_req_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+2U-sizeof(stbin_exec_pps_if_pulse_duration_write_req_t))];




//Frame stbin_exec_pps_if_pulse_polarity_write_req (cid=0x3D mid=0x2A)
#define stbin_exec_pps_if_pulse_polarity_write_req_MAP(sname, msg, len, p_result)\
	/*lint -e{9087} cast performed between a pointer to object type and a pointer to a different object type */ \
	stbin_exec_pps_if_pulse_polarity_write_req_t *sname = (stbin_exec_pps_if_pulse_polarity_write_req_t *)msg;\
	GPS_DEBUG_MSG(("STBIN Received Frame stbin_exec_pps_if_pulse_polarity_write_req\r\n"));\
	GPS_DEBUG_MSG(("STBIN pulsePolarity=0x%X\r\n", sname->pulsePolarity));\
	if(1U < sname->pulsePolarity) {\
		GPS_DEBUG_MSG(("STBIN invalid pulsePolarity=%d\r\n", sname->pulsePolarity));\
		*(p_result) = STBIN_FAILED; }\
	if(len != (sizeof(*sname) - 1U)) {\
		GPS_DEBUG_MSG(("STBIN frame stbin_exec_pps_if_pulse_polarity_write_req received with Payload length %d vs %d\r\n", len, sizeof(*sname) - 1U));\
		*(p_result) = STBIN_FAILED; }

//Test structure size against computed size
typedef tS8 Teststbin_exec_pps_if_pulse_polarity_write_req_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(stbin_exec_pps_if_pulse_polarity_write_req_t)-2U)];
typedef tS8 Teststbin_exec_pps_if_pulse_polarity_write_req_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+2U-sizeof(stbin_exec_pps_if_pulse_polarity_write_req_t))];




//Frame stbin_exec_pps_if_data_write_req (cid=0x3D mid=0x4A)
#define stbin_exec_pps_if_data_write_req_MAP(sname, msg, len, p_result)\
	/*lint -e{9087} cast performed between a pointer to object type and a pointer to a different object type */ \
	stbin_exec_pps_if_data_write_req_t *sname = (stbin_exec_pps_if_data_write_req_t *)msg;\
	GPS_DEBUG_MSG(("STBIN Received Frame stbin_exec_pps_if_data_write_req\r\n"));\
	GPS_DEBUG_MSG(("STBIN outMode=0x%X\r\n", sname->outMode));\
	if(2U < sname->outMode) {\
		GPS_DEBUG_MSG(("STBIN invalid outMode=%d\r\n", sname->outMode));\
		*(p_result) = STBIN_FAILED; }\
	GPS_DEBUG_MSG(("STBIN refTimeId=0x%X\r\n", sname->refTimeId));\
	if(4U < sname->refTimeId) {\
		GPS_DEBUG_MSG(("STBIN invalid refTimeId=%d\r\n", sname->refTimeId));\
		*(p_result) = STBIN_FAILED; }\
	STBIN_FROM_LINK_ENDIAN_CONV_tU16(&(sname->pulseDelay));\
	GPS_DEBUG_MSG(("STBIN pulseDelay=%d\r\n", sname->pulseDelay));\
	STBIN_FROM_LINK_ENDIAN_CONV_tU16(&(sname->pulseDuration));\
	GPS_DEBUG_MSG(("STBIN pulseDuration=0x%X\r\n", sname->pulseDuration));\
	if((100U > sname->pulseDuration) || (900U < sname->pulseDuration)) {\
		GPS_DEBUG_MSG(("STBIN invalid pulseDuration=%d\r\n", sname->pulseDuration));\
		*(p_result) = STBIN_FAILED; }\
	GPS_DEBUG_MSG(("STBIN pulsePolarity=0x%X\r\n", sname->pulsePolarity));\
	if(1U < sname->pulsePolarity) {\
		GPS_DEBUG_MSG(("STBIN invalid pulsePolarity=%d\r\n", sname->pulsePolarity));\
		*(p_result) = STBIN_FAILED; }\
	if(len != (sizeof(*sname) - 1U)) {\
		GPS_DEBUG_MSG(("STBIN frame stbin_exec_pps_if_data_write_req received with Payload length %d vs %d\r\n", len, sizeof(*sname) - 1U));\
		*(p_result) = STBIN_FAILED; }

//Test structure size against computed size
typedef tS8 Teststbin_exec_pps_if_data_write_req_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(stbin_exec_pps_if_data_write_req_t)-8U)];
typedef tS8 Teststbin_exec_pps_if_data_write_req_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+8U-sizeof(stbin_exec_pps_if_data_write_req_t))];




//Frame stbin_exec_pps_if_fix_condition_write_req (cid=0x3D mid=0x2C)
#define stbin_exec_pps_if_fix_condition_write_req_MAP(sname, msg, len, p_result)\
	/*lint -e{9087} cast performed between a pointer to object type and a pointer to a different object type */ \
	stbin_exec_pps_if_fix_condition_write_req_t *sname = (stbin_exec_pps_if_fix_condition_write_req_t *)msg;\
	GPS_DEBUG_MSG(("STBIN Received Frame stbin_exec_pps_if_fix_condition_write_req\r\n"));\
	GPS_DEBUG_MSG(("STBIN fixCondition=0x%X\r\n", sname->fixCondition));\
	if((1U > sname->fixCondition) || (3U < sname->fixCondition)) {\
		GPS_DEBUG_MSG(("STBIN invalid fixCondition=%d\r\n", sname->fixCondition));\
		*(p_result) = STBIN_FAILED; }\
	if(len != sizeof(*sname)) {\
		GPS_DEBUG_MSG(("STBIN frame stbin_exec_pps_if_fix_condition_write_req received with Payload length %d vs %d\r\n", len, sizeof(*sname) - 0U));\
		*(p_result) = STBIN_FAILED; }

//Test structure size against computed size
typedef tS8 Teststbin_exec_pps_if_fix_condition_write_req_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(stbin_exec_pps_if_fix_condition_write_req_t)-1U)];
typedef tS8 Teststbin_exec_pps_if_fix_condition_write_req_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+1U-sizeof(stbin_exec_pps_if_fix_condition_write_req_t))];




//Frame stbin_exec_pps_if_sat_threshold_write_req (cid=0x3D mid=0x2D)
#define stbin_exec_pps_if_sat_threshold_write_req_MAP(sname, msg, len, p_result)\
	/*lint -e{9087} cast performed between a pointer to object type and a pointer to a different object type */ \
	stbin_exec_pps_if_sat_threshold_write_req_t *sname = (stbin_exec_pps_if_sat_threshold_write_req_t *)msg;\
	GPS_DEBUG_MSG(("STBIN Received Frame stbin_exec_pps_if_sat_threshold_write_req\r\n"));\
	GPS_DEBUG_MSG(("STBIN satTh=%d\r\n", sname->satTh));\
	if(len != sizeof(*sname)) {\
		GPS_DEBUG_MSG(("STBIN frame stbin_exec_pps_if_sat_threshold_write_req received with Payload length %d vs %d\r\n", len, sizeof(*sname) - 0U));\
		*(p_result) = STBIN_FAILED; }

//Test structure size against computed size
typedef tS8 Teststbin_exec_pps_if_sat_threshold_write_req_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(stbin_exec_pps_if_sat_threshold_write_req_t)-1U)];
typedef tS8 Teststbin_exec_pps_if_sat_threshold_write_req_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+1U-sizeof(stbin_exec_pps_if_sat_threshold_write_req_t))];




//Frame stbin_exec_pps_if_constallation_rf_delay_write_req (cid=0x3D mid=0x2E)
#define stbin_exec_pps_if_constallation_rf_delay_write_req_MAP(sname, msg, len, p_result)\
	/*lint -e{9087} cast performed between a pointer to object type and a pointer to a different object type */ \
	stbin_exec_pps_if_constallation_rf_delay_write_req_t *sname = (stbin_exec_pps_if_constallation_rf_delay_write_req_t *)msg;\
	GPS_DEBUG_MSG(("STBIN Received Frame stbin_exec_pps_if_constallation_rf_delay_write_req\r\n"));\
	STBIN_FROM_LINK_ENDIAN_CONV_tU16(&(sname->rfDelay));\
	GPS_DEBUG_MSG(("STBIN rfDelay=%d\r\n", sname->rfDelay));\
	GPS_DEBUG_MSG(("STBIN constellation=0x%X\r\n", sname->constellation));\
	if(1U < sname->constellation) {\
		GPS_DEBUG_MSG(("STBIN invalid constellation=%d\r\n", sname->constellation));\
		*(p_result) = STBIN_FAILED; }\
	if(len != (sizeof(*sname) - 1U)) {\
		GPS_DEBUG_MSG(("STBIN frame stbin_exec_pps_if_constallation_rf_delay_write_req received with Payload length %d vs %d\r\n", len, sizeof(*sname) - 1U));\
		*(p_result) = STBIN_FAILED; }

//Test structure size against computed size
typedef tS8 Teststbin_exec_pps_if_constallation_rf_delay_write_req_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(stbin_exec_pps_if_constallation_rf_delay_write_req_t)-4U)];
typedef tS8 Teststbin_exec_pps_if_constallation_rf_delay_write_req_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+4U-sizeof(stbin_exec_pps_if_constallation_rf_delay_write_req_t))];




//Frame stbin_exec_pps_if_elevation_mask_write_req (cid=0x3D mid=0x2F)
#define stbin_exec_pps_if_elevation_mask_write_req_MAP(sname, msg, len, p_result)\
	/*lint -e{9087} cast performed between a pointer to object type and a pointer to a different object type */ \
	stbin_exec_pps_if_elevation_mask_write_req_t *sname = (stbin_exec_pps_if_elevation_mask_write_req_t *)msg;\
	GPS_DEBUG_MSG(("STBIN Received Frame stbin_exec_pps_if_elevation_mask_write_req\r\n"));\
	GPS_DEBUG_MSG(("STBIN elevationMask=0x%X\r\n", sname->elevationMask));\
	if(90U < sname->elevationMask) {\
		GPS_DEBUG_MSG(("STBIN invalid elevationMask=%d\r\n", sname->elevationMask));\
		*(p_result) = STBIN_FAILED; }\
	if(len != sizeof(*sname)) {\
		GPS_DEBUG_MSG(("STBIN frame stbin_exec_pps_if_elevation_mask_write_req received with Payload length %d vs %d\r\n", len, sizeof(*sname) - 0U));\
		*(p_result) = STBIN_FAILED; }

//Test structure size against computed size
typedef tS8 Teststbin_exec_pps_if_elevation_mask_write_req_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(stbin_exec_pps_if_elevation_mask_write_req_t)-1U)];
typedef tS8 Teststbin_exec_pps_if_elevation_mask_write_req_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+1U-sizeof(stbin_exec_pps_if_elevation_mask_write_req_t))];




//Frame stbin_exec_pps_if_constellation_mask_write_req (cid=0x3D mid=0x30)
#define stbin_exec_pps_if_constellation_mask_write_req_MAP(sname, msg, len, p_result)\
	/*lint -e{9087} cast performed between a pointer to object type and a pointer to a different object type */ \
	stbin_exec_pps_if_constellation_mask_write_req_t *sname = (stbin_exec_pps_if_constellation_mask_write_req_t *)msg;\
	GPS_DEBUG_MSG(("STBIN Received Frame stbin_exec_pps_if_constellation_mask_write_req\r\n"));\
	STBIN_FROM_LINK_ENDIAN_CONV_tU32(&(sname->constellationMask));\
	GPS_DEBUG_MSG(("STBIN constellationMask=%d\r\n", sname->constellationMask));\
	if(len != sizeof(*sname)) {\
		GPS_DEBUG_MSG(("STBIN frame stbin_exec_pps_if_constellation_mask_write_req received with Payload length %d vs %d\r\n", len, sizeof(*sname) - 0U));\
		*(p_result) = STBIN_FAILED; }

//Test structure size against computed size
typedef tS8 Teststbin_exec_pps_if_constellation_mask_write_req_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(stbin_exec_pps_if_constellation_mask_write_req_t)-4U)];
typedef tS8 Teststbin_exec_pps_if_constellation_mask_write_req_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+4U-sizeof(stbin_exec_pps_if_constellation_mask_write_req_t))];




//Frame stbin_exec_pps_if_timing_data_write_req (cid=0x3D mid=0x4B)
#define stbin_exec_pps_if_timing_data_write_req_MAP(sname, msg, len, p_result)\
	/*lint -e{9087} cast performed between a pointer to object type and a pointer to a different object type */ \
	stbin_exec_pps_if_timing_data_write_req_t *sname = (stbin_exec_pps_if_timing_data_write_req_t *)msg;\
	GPS_DEBUG_MSG(("STBIN Received Frame stbin_exec_pps_if_timing_data_write_req\r\n"));\
	STBIN_FROM_LINK_ENDIAN_CONV_tU32(&(sname->constellationMask));\
	GPS_DEBUG_MSG(("STBIN constellationMask=%d\r\n", sname->constellationMask));\
	GPS_DEBUG_MSG(("STBIN fixCondition=0x%X\r\n", sname->fixCondition));\
	if((1U > sname->fixCondition) || (3U < sname->fixCondition)) {\
		GPS_DEBUG_MSG(("STBIN invalid fixCondition=%d\r\n", sname->fixCondition));\
		*(p_result) = STBIN_FAILED; }\
	GPS_DEBUG_MSG(("STBIN satTh=%d\r\n", sname->satTh));\
	GPS_DEBUG_MSG(("STBIN elevationMask=0x%X\r\n", sname->elevationMask));\
	if(90U < sname->elevationMask) {\
		GPS_DEBUG_MSG(("STBIN invalid elevationMask=%d\r\n", sname->elevationMask));\
		*(p_result) = STBIN_FAILED; }\
	if(len != (sizeof(*sname) - 1U)) {\
		GPS_DEBUG_MSG(("STBIN frame stbin_exec_pps_if_timing_data_write_req received with Payload length %d vs %d\r\n", len, sizeof(*sname) - 1U));\
		*(p_result) = STBIN_FAILED; }

//Test structure size against computed size
typedef tS8 Teststbin_exec_pps_if_timing_data_write_req_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(stbin_exec_pps_if_timing_data_write_req_t)-8U)];
typedef tS8 Teststbin_exec_pps_if_timing_data_write_req_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+8U-sizeof(stbin_exec_pps_if_timing_data_write_req_t))];




//Frame stbin_exec_pps_if_hold_data_write_req (cid=0x3D mid=0x4C)
#define stbin_exec_pps_if_hold_data_write_req_MAP(sname, msg, len, p_result)\
	/*lint -e{9087} cast performed between a pointer to object type and a pointer to a different object type */ \
	stbin_exec_pps_if_hold_data_write_req_t *sname = (stbin_exec_pps_if_hold_data_write_req_t *)msg;\
	GPS_DEBUG_MSG(("STBIN Received Frame stbin_exec_pps_if_hold_data_write_req\r\n"));\
	STBIN_FROM_LINK_ENDIAN_CONV_tS32(&(sname->lat_val));\
	GPS_DEBUG_MSG(("STBIN lat_val=0x%X\r\n", sname->lat_val));\
	if((-900000000 > sname->lat_val) || (900000000 < sname->lat_val)) {\
		GPS_DEBUG_MSG(("STBIN invalid lat_val=%d\r\n", sname->lat_val));\
		*(p_result) = STBIN_FAILED; }\
	STBIN_FROM_LINK_ENDIAN_CONV_tS32(&(sname->lon_val));\
	GPS_DEBUG_MSG(("STBIN lon_val=0x%X\r\n", sname->lon_val));\
	if((-1800000000 > sname->lon_val) || (1800000000 < sname->lon_val)) {\
		GPS_DEBUG_MSG(("STBIN invalid lon_val=%d\r\n", sname->lon_val));\
		*(p_result) = STBIN_FAILED; }\
	STBIN_FROM_LINK_ENDIAN_CONV_tS32(&(sname->height));\
	GPS_DEBUG_MSG(("STBIN height=0x%X\r\n", sname->height));\
	if((0 > sname->height) || (10000000 < sname->height)) {\
		GPS_DEBUG_MSG(("STBIN invalid height=%d\r\n", sname->height));\
		*(p_result) = STBIN_FAILED; }\
	GPS_DEBUG_MSG(("STBIN posHoldOnOff=0x%X\r\n", sname->posHoldOnOff));\
	if(1U < sname->posHoldOnOff) {\
		GPS_DEBUG_MSG(("STBIN invalid posHoldOnOff=%d\r\n", sname->posHoldOnOff));\
		*(p_result) = STBIN_FAILED; }\
	if(len != (sizeof(*sname) - 3U)) {\
		GPS_DEBUG_MSG(("STBIN frame stbin_exec_pps_if_hold_data_write_req received with Payload length %d vs %d\r\n", len, sizeof(*sname) - 3U));\
		*(p_result) = STBIN_FAILED; }

//Test structure size against computed size
typedef tS8 Teststbin_exec_pps_if_hold_data_write_req_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(stbin_exec_pps_if_hold_data_write_req_t)-16U)];
typedef tS8 Teststbin_exec_pps_if_hold_data_write_req_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+16U-sizeof(stbin_exec_pps_if_hold_data_write_req_t))];




//Frame stbin_exec_pps_if_auto_hold_samples_write_req (cid=0x3D mid=0x33)
#define stbin_exec_pps_if_auto_hold_samples_write_req_MAP(sname, msg, len, p_result)\
	/*lint -e{9087} cast performed between a pointer to object type and a pointer to a different object type */ \
	stbin_exec_pps_if_auto_hold_samples_write_req_t *sname = (stbin_exec_pps_if_auto_hold_samples_write_req_t *)msg;\
	GPS_DEBUG_MSG(("STBIN Received Frame stbin_exec_pps_if_auto_hold_samples_write_req\r\n"));\
	STBIN_FROM_LINK_ENDIAN_CONV_tU16(&(sname->nbSamples));\
	GPS_DEBUG_MSG(("STBIN nbSamples=%d\r\n", sname->nbSamples));\
	if(len != sizeof(*sname)) {\
		GPS_DEBUG_MSG(("STBIN frame stbin_exec_pps_if_auto_hold_samples_write_req received with Payload length %d vs %d\r\n", len, sizeof(*sname) - 0U));\
		*(p_result) = STBIN_FAILED; }

//Test structure size against computed size
typedef tS8 Teststbin_exec_pps_if_auto_hold_samples_write_req_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(stbin_exec_pps_if_auto_hold_samples_write_req_t)-2U)];
typedef tS8 Teststbin_exec_pps_if_auto_hold_samples_write_req_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+2U-sizeof(stbin_exec_pps_if_auto_hold_samples_write_req_t))];




//Frame stbin_exec_pps_if_traim_data_write_req (cid=0x3D mid=0x4D)
#define stbin_exec_pps_if_traim_data_write_req_MAP(sname, msg, len, p_result)\
	/*lint -e{9087} cast performed between a pointer to object type and a pointer to a different object type */ \
	stbin_exec_pps_if_traim_data_write_req_t *sname = (stbin_exec_pps_if_traim_data_write_req_t *)msg;\
	GPS_DEBUG_MSG(("STBIN Received Frame stbin_exec_pps_if_traim_data_write_req\r\n"));\
	STBIN_FROM_LINK_ENDIAN_CONV_tU16(&(sname->alarm));\
	GPS_DEBUG_MSG(("STBIN alarm=%d\r\n", sname->alarm));\
	GPS_DEBUG_MSG(("STBIN enabled=0x%X\r\n", sname->enabled));\
	if(1U < sname->enabled) {\
		GPS_DEBUG_MSG(("STBIN invalid enabled=%d\r\n", sname->enabled));\
		*(p_result) = STBIN_FAILED; }\
	if(len != (sizeof(*sname) - 1U)) {\
		GPS_DEBUG_MSG(("STBIN frame stbin_exec_pps_if_traim_data_write_req received with Payload length %d vs %d\r\n", len, sizeof(*sname) - 1U));\
		*(p_result) = STBIN_FAILED; }

//Test structure size against computed size
typedef tS8 Teststbin_exec_pps_if_traim_data_write_req_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(stbin_exec_pps_if_traim_data_write_req_t)-4U)];
typedef tS8 Teststbin_exec_pps_if_traim_data_write_req_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+4U-sizeof(stbin_exec_pps_if_traim_data_write_req_t))];


//Section : Initialization messages (ClassId 0x20)


//Frame stbin_exec_init_GPS_params_req (cid=0x20 mid=0x1)
#define stbin_exec_init_GPS_params_req_MAP(sname, msg, len, p_result)\
	/*lint -e{9087} cast performed between a pointer to object type and a pointer to a different object type */ \
	stbin_exec_init_GPS_params_req_t *sname = (stbin_exec_init_GPS_params_req_t *)msg;\
	GPS_DEBUG_MSG(("STBIN Received Frame stbin_exec_init_GPS_params_req\r\n"));\
	STBIN_FROM_LINK_ENDIAN_CONV_tS32(&(sname->lat_val));\
	GPS_DEBUG_MSG(("STBIN lat_val=0x%X\r\n", sname->lat_val));\
	if((-900000000 > sname->lat_val) || (900000000 < sname->lat_val)) {\
		GPS_DEBUG_MSG(("STBIN invalid lat_val=%d\r\n", sname->lat_val));\
		*(p_result) = STBIN_FAILED; }\
	STBIN_FROM_LINK_ENDIAN_CONV_tS32(&(sname->lon_val));\
	GPS_DEBUG_MSG(("STBIN lon_val=0x%X\r\n", sname->lon_val));\
	if((-1800000000 > sname->lon_val) || (1800000000 < sname->lon_val)) {\
		GPS_DEBUG_MSG(("STBIN invalid lon_val=%d\r\n", sname->lon_val));\
		*(p_result) = STBIN_FAILED; }\
	STBIN_FROM_LINK_ENDIAN_CONV_tS32(&(sname->height));\
	GPS_DEBUG_MSG(("STBIN height=0x%X\r\n", sname->height));\
	if((0 > sname->height) || (10000000 < sname->height)) {\
		GPS_DEBUG_MSG(("STBIN invalid height=%d\r\n", sname->height));\
		*(p_result) = STBIN_FAILED; }\
	STBIN_FROM_LINK_ENDIAN_CONV_tS16(&(sname->year));\
	GPS_DEBUG_MSG(("STBIN year=0x%X\r\n", sname->year));\
	if((2009 > sname->year) || (2037 < sname->year)) {\
		GPS_DEBUG_MSG(("STBIN invalid year=%d\r\n", sname->year));\
		*(p_result) = STBIN_FAILED; }\
	GPS_DEBUG_MSG(("STBIN month=0x%X\r\n", sname->month));\
	if((1U > sname->month) || (12U < sname->month)) {\
		GPS_DEBUG_MSG(("STBIN invalid month=%d\r\n", sname->month));\
		*(p_result) = STBIN_FAILED; }\
	GPS_DEBUG_MSG(("STBIN day=0x%X\r\n", sname->day));\
	if((1U > sname->day) || (31U < sname->day)) {\
		GPS_DEBUG_MSG(("STBIN invalid day=%d\r\n", sname->day));\
		*(p_result) = STBIN_FAILED; }\
	GPS_DEBUG_MSG(("STBIN hour=0x%X\r\n", sname->hour));\
	if(23U < sname->hour) {\
		GPS_DEBUG_MSG(("STBIN invalid hour=%d\r\n", sname->hour));\
		*(p_result) = STBIN_FAILED; }\
	GPS_DEBUG_MSG(("STBIN min=0x%X\r\n", sname->min));\
	if(59U < sname->min) {\
		GPS_DEBUG_MSG(("STBIN invalid min=%d\r\n", sname->min));\
		*(p_result) = STBIN_FAILED; }\
	GPS_DEBUG_MSG(("STBIN sec=0x%X\r\n", sname->sec));\
	if(59U < sname->sec) {\
		GPS_DEBUG_MSG(("STBIN invalid sec=%d\r\n", sname->sec));\
		*(p_result) = STBIN_FAILED; }\
	GPS_DEBUG_MSG(("STBIN constel=%d\r\n", sname->constel));\
	if(len != sizeof(*sname)) {\
		GPS_DEBUG_MSG(("STBIN frame stbin_exec_init_GPS_params_req received with Payload length %d vs %d\r\n", len, sizeof(*sname) - 0U));\
		*(p_result) = STBIN_FAILED; }

//Test structure size against computed size
typedef tS8 Teststbin_exec_init_GPS_params_req_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(stbin_exec_init_GPS_params_req_t)-20U)];
typedef tS8 Teststbin_exec_init_GPS_params_req_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+20U-sizeof(stbin_exec_init_GPS_params_req_t))];




//Frame stbin_exec_init_GPS_time_req (cid=0x20 mid=0x6)
#define stbin_exec_init_GPS_time_req_MAP(sname, msg, len, p_result)\
	/*lint -e{9087} cast performed between a pointer to object type and a pointer to a different object type */ \
	stbin_exec_init_GPS_time_req_t *sname = (stbin_exec_init_GPS_time_req_t *)msg;\
	GPS_DEBUG_MSG(("STBIN Received Frame stbin_exec_init_GPS_time_req\r\n"));\
	STBIN_FROM_LINK_ENDIAN_CONV_tS16(&(sname->year));\
	GPS_DEBUG_MSG(("STBIN year=0x%X\r\n", sname->year));\
	if((2009 > sname->year) || (2037 < sname->year)) {\
		GPS_DEBUG_MSG(("STBIN invalid year=%d\r\n", sname->year));\
		*(p_result) = STBIN_FAILED; }\
	GPS_DEBUG_MSG(("STBIN month=0x%X\r\n", sname->month));\
	if((1U > sname->month) || (12U < sname->month)) {\
		GPS_DEBUG_MSG(("STBIN invalid month=%d\r\n", sname->month));\
		*(p_result) = STBIN_FAILED; }\
	GPS_DEBUG_MSG(("STBIN day=0x%X\r\n", sname->day));\
	if((1U > sname->day) || (31U < sname->day)) {\
		GPS_DEBUG_MSG(("STBIN invalid day=%d\r\n", sname->day));\
		*(p_result) = STBIN_FAILED; }\
	GPS_DEBUG_MSG(("STBIN hour=0x%X\r\n", sname->hour));\
	if(23U < sname->hour) {\
		GPS_DEBUG_MSG(("STBIN invalid hour=%d\r\n", sname->hour));\
		*(p_result) = STBIN_FAILED; }\
	GPS_DEBUG_MSG(("STBIN min=0x%X\r\n", sname->min));\
	if(59U < sname->min) {\
		GPS_DEBUG_MSG(("STBIN invalid min=%d\r\n", sname->min));\
		*(p_result) = STBIN_FAILED; }\
	GPS_DEBUG_MSG(("STBIN sec=0x%X\r\n", sname->sec));\
	if(59U < sname->sec) {\
		GPS_DEBUG_MSG(("STBIN invalid sec=%d\r\n", sname->sec));\
		*(p_result) = STBIN_FAILED; }\
	GPS_DEBUG_MSG(("STBIN constel=%d\r\n", sname->constel));\
	if(len != sizeof(*sname)) {\
		GPS_DEBUG_MSG(("STBIN frame stbin_exec_init_GPS_time_req received with Payload length %d vs %d\r\n", len, sizeof(*sname) - 0U));\
		*(p_result) = STBIN_FAILED; }

//Test structure size against computed size
typedef tS8 Teststbin_exec_init_GPS_time_req_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(stbin_exec_init_GPS_time_req_t)-8U)];
typedef tS8 Teststbin_exec_init_GPS_time_req_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+8U-sizeof(stbin_exec_init_GPS_time_req_t))];




//Frame stbin_exec_init_freq_req (cid=0x20 mid=0x2)
#define stbin_exec_init_freq_req_MAP(sname, msg, len, p_result)\
	/*lint -e{9087} cast performed between a pointer to object type and a pointer to a different object type */ \
	stbin_exec_init_freq_req_t *sname = (stbin_exec_init_freq_req_t *)msg;\
	GPS_DEBUG_MSG(("STBIN Received Frame stbin_exec_init_freq_req\r\n"));\
	STBIN_FROM_LINK_ENDIAN_CONV_tS32(&(sname->freq));\
	GPS_DEBUG_MSG(("STBIN freq=0x%X\r\n", sname->freq));\
	if((-132000 > sname->freq) || (132000 < sname->freq)) {\
		GPS_DEBUG_MSG(("STBIN invalid freq=%d\r\n", sname->freq));\
		*(p_result) = STBIN_FAILED; }\
	if(len != sizeof(*sname)) {\
		GPS_DEBUG_MSG(("STBIN frame stbin_exec_init_freq_req received with Payload length %d vs %d\r\n", len, sizeof(*sname) - 0U));\
		*(p_result) = STBIN_FAILED; }

//Test structure size against computed size
typedef tS8 Teststbin_exec_init_freq_req_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(stbin_exec_init_freq_req_t)-4U)];
typedef tS8 Teststbin_exec_init_freq_req_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+4U-sizeof(stbin_exec_init_freq_req_t))];




//Frame stbin_exec_init_cold_req (cid=0x20 mid=0x3)
#define stbin_exec_init_cold_req_MAP(sname, msg, len, p_result)\
	/*lint -e{9087} cast performed between a pointer to object type and a pointer to a different object type */ \
	stbin_exec_init_cold_req_t *sname = (stbin_exec_init_cold_req_t *)msg;\
	GPS_DEBUG_MSG(("STBIN Received Frame stbin_exec_init_cold_req\r\n"));\
	GPS_DEBUG_MSG(("STBIN type=%d\r\n", sname->type));\
	GPS_DEBUG_MSG(("STBIN use_fw=%d\r\n", sname->use_fw));\
	if(len != sizeof(*sname)) {\
		GPS_DEBUG_MSG(("STBIN frame stbin_exec_init_cold_req received with Payload length %d vs %d\r\n", len, sizeof(*sname) - 0U));\
		*(p_result) = STBIN_FAILED; }

//Test structure size against computed size
typedef tS8 Teststbin_exec_init_cold_req_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(stbin_exec_init_cold_req_t)-2U)];
typedef tS8 Teststbin_exec_init_cold_req_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+2U-sizeof(stbin_exec_init_cold_req_t))];




//Frame stbin_exec_init_warm_req (cid=0x20 mid=0x4)
#define stbin_exec_init_warm_req_MAP(sname, msg, len, p_result)\
	/*lint -e{9087} cast performed between a pointer to object type and a pointer to a different object type */ \
	stbin_exec_init_warm_req_t *sname = (stbin_exec_init_warm_req_t *)msg;\
	GPS_DEBUG_MSG(("STBIN Received Frame stbin_exec_init_warm_req\r\n"));\
	GPS_DEBUG_MSG(("STBIN control=0x%X\r\n", sname->control));\
	if(0U < sname->control) {\
		GPS_DEBUG_MSG(("STBIN invalid control=%d\r\n", sname->control));\
		*(p_result) = STBIN_FAILED; }\
	if(len != sizeof(*sname)) {\
		GPS_DEBUG_MSG(("STBIN frame stbin_exec_init_warm_req received with Payload length %d vs %d\r\n", len, sizeof(*sname) - 0U));\
		*(p_result) = STBIN_FAILED; }

//Test structure size against computed size
typedef tS8 Teststbin_exec_init_warm_req_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(stbin_exec_init_warm_req_t)-1U)];
typedef tS8 Teststbin_exec_init_warm_req_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+1U-sizeof(stbin_exec_init_warm_req_t))];




//Frame stbin_exec_init_hot_req (cid=0x20 mid=0x5)
#define stbin_exec_init_hot_req_MAP(sname, msg, len, p_result)\
	/*lint -e{9087} cast performed between a pointer to object type and a pointer to a different object type */ \
	stbin_exec_init_hot_req_t *sname = (stbin_exec_init_hot_req_t *)msg;\
	GPS_DEBUG_MSG(("STBIN Received Frame stbin_exec_init_hot_req\r\n"));\
	GPS_DEBUG_MSG(("STBIN control=0x%X\r\n", sname->control));\
	if(0U < sname->control) {\
		GPS_DEBUG_MSG(("STBIN invalid control=%d\r\n", sname->control));\
		*(p_result) = STBIN_FAILED; }\
	if(len != sizeof(*sname)) {\
		GPS_DEBUG_MSG(("STBIN frame stbin_exec_init_hot_req received with Payload length %d vs %d\r\n", len, sizeof(*sname) - 0U));\
		*(p_result) = STBIN_FAILED; }

//Test structure size against computed size
typedef tS8 Teststbin_exec_init_hot_req_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(stbin_exec_init_hot_req_t)-1U)];
typedef tS8 Teststbin_exec_init_hot_req_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+1U-sizeof(stbin_exec_init_hot_req_t))];




//Frame stbin_exec_init_clr_ephemes (cid=0x20 mid=0x7)
#define stbin_exec_init_clr_ephemes_MAP(sname, msg, len, p_result)\
	GPS_DEBUG_MSG(("STBIN Received Frame stbin_exec_init_clr_ephemes\r\n"));\
	if(len != 0U) {\
		GPS_DEBUG_MSG(("STBIN Dataless frame stbin_exec_init_clr_ephemes received with Payload length %d\r\n", len));\
		*(p_result) = STBIN_FAILED; }



//Frame stbin_exec_init_clr_almanacs (cid=0x20 mid=0x8)
#define stbin_exec_init_clr_almanacs_MAP(sname, msg, len, p_result)\
	GPS_DEBUG_MSG(("STBIN Received Frame stbin_exec_init_clr_almanacs\r\n"));\
	if(len != 0U) {\
		GPS_DEBUG_MSG(("STBIN Dataless frame stbin_exec_init_clr_almanacs received with Payload length %d\r\n", len));\
		*(p_result) = STBIN_FAILED; }

//Section : Reset messages (ClassId 0x5A)


//Frame stbin_exec_reset_gps_req (cid=0x5A mid=0x5C)
#define stbin_exec_reset_gps_req_MAP(sname, msg, len, p_result)\
	/*lint -e{9087} cast performed between a pointer to object type and a pointer to a different object type */ \
	stbin_exec_reset_gps_req_t *sname = (stbin_exec_reset_gps_req_t *)msg;\
	GPS_DEBUG_MSG(("STBIN Received Frame stbin_exec_reset_gps_req\r\n"));\
	GPS_DEBUG_MSG(("STBIN control=0x%X\r\n", sname->control));\
	if(0U < sname->control) {\
		GPS_DEBUG_MSG(("STBIN invalid control=%d\r\n", sname->control));\
		*(p_result) = STBIN_FAILED; }\
	if(len != sizeof(*sname)) {\
		GPS_DEBUG_MSG(("STBIN frame stbin_exec_reset_gps_req received with Payload length %d vs %d\r\n", len, sizeof(*sname) - 0U));\
		*(p_result) = STBIN_FAILED; }

//Test structure size against computed size
typedef tS8 Teststbin_exec_reset_gps_req_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(stbin_exec_reset_gps_req_t)-1U)];
typedef tS8 Teststbin_exec_reset_gps_req_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+1U-sizeof(stbin_exec_reset_gps_req_t))];




//Frame stbin_exec_reset_soft_req (cid=0x5A mid=0x5D)
#define stbin_exec_reset_soft_req_MAP(sname, msg, len, p_result)\
	/*lint -e{9087} cast performed between a pointer to object type and a pointer to a different object type */ \
	stbin_exec_reset_soft_req_t *sname = (stbin_exec_reset_soft_req_t *)msg;\
	GPS_DEBUG_MSG(("STBIN Received Frame stbin_exec_reset_soft_req\r\n"));\
	GPS_DEBUG_MSG(("STBIN control=0x%X\r\n", sname->control));\
	if(0U < sname->control) {\
		GPS_DEBUG_MSG(("STBIN invalid control=%d\r\n", sname->control));\
		*(p_result) = STBIN_FAILED; }\
	if(len != sizeof(*sname)) {\
		GPS_DEBUG_MSG(("STBIN frame stbin_exec_reset_soft_req received with Payload length %d vs %d\r\n", len, sizeof(*sname) - 0U));\
		*(p_result) = STBIN_FAILED; }

//Test structure size against computed size
typedef tS8 Teststbin_exec_reset_soft_req_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(stbin_exec_reset_soft_req_t)-1U)];
typedef tS8 Teststbin_exec_reset_soft_req_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+1U-sizeof(stbin_exec_reset_soft_req_t))];




//Frame stbin_exec_reset_stack_check_req (cid=0x5A mid=0x5E)
#define stbin_exec_reset_stack_check_req_MAP(sname, msg, len, p_result)\
	/*lint -e{9087} cast performed between a pointer to object type and a pointer to a different object type */ \
	stbin_exec_reset_stack_check_req_t *sname = (stbin_exec_reset_stack_check_req_t *)msg;\
	GPS_DEBUG_MSG(("STBIN Received Frame stbin_exec_reset_stack_check_req\r\n"));\
	GPS_DEBUG_MSG(("STBIN control=0x%X\r\n", sname->control));\
	if(0U < sname->control) {\
		GPS_DEBUG_MSG(("STBIN invalid control=%d\r\n", sname->control));\
		*(p_result) = STBIN_FAILED; }\
	if(len != sizeof(*sname)) {\
		GPS_DEBUG_MSG(("STBIN frame stbin_exec_reset_stack_check_req received with Payload length %d vs %d\r\n", len, sizeof(*sname) - 0U));\
		*(p_result) = STBIN_FAILED; }

//Test structure size against computed size
typedef tS8 Teststbin_exec_reset_stack_check_req_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(stbin_exec_reset_stack_check_req_t)-1U)];
typedef tS8 Teststbin_exec_reset_stack_check_req_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+1U-sizeof(stbin_exec_reset_stack_check_req_t))];




//Frame stbin_exec_gps_suspend (cid=0x5A mid=0x5F)
#define stbin_exec_gps_suspend_MAP(sname, msg, len, p_result)\
	GPS_DEBUG_MSG(("STBIN Received Frame stbin_exec_gps_suspend\r\n"));\
	if(len != 0U) {\
		GPS_DEBUG_MSG(("STBIN Dataless frame stbin_exec_gps_suspend received with Payload length %d\r\n", len));\
		*(p_result) = STBIN_FAILED; }



//Frame stbin_exec_gps_resume (cid=0x5A mid=0x60)
#define stbin_exec_gps_resume_MAP(sname, msg, len, p_result)\
	GPS_DEBUG_MSG(("STBIN Received Frame stbin_exec_gps_resume\r\n"));\
	if(len != 0U) {\
		GPS_DEBUG_MSG(("STBIN Dataless frame stbin_exec_gps_resume received with Payload length %d\r\n", len));\
		*(p_result) = STBIN_FAILED; }

//Section : Read Requests (ClassId 0x2A)


//Frame stbin_exec_get_sw_ver (cid=0x2A mid=0x20)
#define stbin_exec_get_sw_ver_MAP(sname, msg, len, p_result)\
	/*lint -e{9087} cast performed between a pointer to object type and a pointer to a different object type */ \
	stbin_exec_get_sw_ver_t *sname = (stbin_exec_get_sw_ver_t *)msg;\
	GPS_DEBUG_MSG(("STBIN Received Frame stbin_exec_get_sw_ver\r\n"));\
	GPS_DEBUG_MSG(("STBIN control=0x%X\r\n", sname->control));\
	if(11U < sname->control) {\
		GPS_DEBUG_MSG(("STBIN invalid control=%d\r\n", sname->control));\
		*(p_result) = STBIN_FAILED; }\
	if(len != sizeof(*sname)) {\
		GPS_DEBUG_MSG(("STBIN frame stbin_exec_get_sw_ver received with Payload length %d vs %d\r\n", len, sizeof(*sname) - 0U));\
		*(p_result) = STBIN_FAILED; }

//Test structure size against computed size
typedef tS8 Teststbin_exec_get_sw_ver_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(stbin_exec_get_sw_ver_t)-1U)];
typedef tS8 Teststbin_exec_get_sw_ver_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+1U-sizeof(stbin_exec_get_sw_ver_t))];




//Frame stbin_exec_check_task (cid=0x2A mid=0x21)
#define stbin_exec_check_task_MAP(sname, msg, len, p_result)\
	GPS_DEBUG_MSG(("STBIN Received Frame stbin_exec_check_task\r\n"));\
	if(len != 0U) {\
		GPS_DEBUG_MSG(("STBIN Dataless frame stbin_exec_check_task received with Payload length %d\r\n", len));\
		*(p_result) = STBIN_FAILED; }



//Frame stbin_exec_check_cpu_usage (cid=0x2A mid=0x22)
#define stbin_exec_check_cpu_usage_MAP(sname, msg, len, p_result)\
	GPS_DEBUG_MSG(("STBIN Received Frame stbin_exec_check_cpu_usage\r\n"));\
	if(len != 0U) {\
		GPS_DEBUG_MSG(("STBIN Dataless frame stbin_exec_check_cpu_usage received with Payload length %d\r\n", len));\
		*(p_result) = STBIN_FAILED; }



//Frame stbin_exec_check_heap (cid=0x2A mid=0x23)
#define stbin_exec_check_heap_MAP(sname, msg, len, p_result)\
	GPS_DEBUG_MSG(("STBIN Received Frame stbin_exec_check_heap\r\n"));\
	if(len != 0U) {\
		GPS_DEBUG_MSG(("STBIN Dataless frame stbin_exec_check_heap received with Payload length %d\r\n", len));\
		*(p_result) = STBIN_FAILED; }



//Frame stbin_exec_read_rtc_time (cid=0x2A mid=0x30)
#define stbin_exec_read_rtc_time_MAP(sname, msg, len, p_result)\
	GPS_DEBUG_MSG(("STBIN Received Frame stbin_exec_read_rtc_time\r\n"));\
	if(len != 0U) {\
		GPS_DEBUG_MSG(("STBIN Dataless frame stbin_exec_read_rtc_time received with Payload length %d\r\n", len));\
		*(p_result) = STBIN_FAILED; }



//Frame stbin_exec_read_datum_selection (cid=0x2A mid=0xF4)
#define stbin_exec_read_datum_selection_MAP(sname, msg, len, p_result)\
	GPS_DEBUG_MSG(("STBIN Received Frame stbin_exec_read_datum_selection\r\n"));\
	if(len != 0U) {\
		GPS_DEBUG_MSG(("STBIN Dataless frame stbin_exec_read_datum_selection received with Payload length %d\r\n", len));\
		*(p_result) = STBIN_FAILED; }



//Frame stbin_exec_get_algo_status (cid=0x2A mid=0xF5)
#define stbin_exec_get_algo_status_MAP(sname, msg, len, p_result)\
	/*lint -e{9087} cast performed between a pointer to object type and a pointer to a different object type */ \
	stbin_exec_get_algo_status_t *sname = (stbin_exec_get_algo_status_t *)msg;\
	GPS_DEBUG_MSG(("STBIN Received Frame stbin_exec_get_algo_status\r\n"));\
	GPS_DEBUG_MSG(("STBIN control=0x%X\r\n", sname->control));\
	if((1U > sname->control) || (1U < sname->control)) {\
		GPS_DEBUG_MSG(("STBIN invalid control=%d\r\n", sname->control));\
		*(p_result) = STBIN_FAILED; }\
	if(len != sizeof(*sname)) {\
		GPS_DEBUG_MSG(("STBIN frame stbin_exec_get_algo_status received with Payload length %d vs %d\r\n", len, sizeof(*sname) - 0U));\
		*(p_result) = STBIN_FAILED; }

//Test structure size against computed size
typedef tS8 Teststbin_exec_get_algo_status_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(stbin_exec_get_algo_status_t)-1U)];
typedef tS8 Teststbin_exec_get_algo_status_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+1U-sizeof(stbin_exec_get_algo_status_t))];




//Frame stbin_exec_sw_config_get_par (cid=0x2A mid=0xFC)
#define stbin_exec_sw_config_get_par_MAP(sname, msg, len, p_result)\
	/*lint -e{9087} cast performed between a pointer to object type and a pointer to a different object type */ \
	stbin_exec_sw_config_get_par_t *sname = (stbin_exec_sw_config_get_par_t *)msg;\
	GPS_DEBUG_MSG(("STBIN Received Frame stbin_exec_sw_config_get_par\r\n"));\
	GPS_DEBUG_MSG(("STBIN ConfigBlock=0x%X\r\n", sname->ConfigBlock));\
	if((1U > sname->ConfigBlock) || (3U < sname->ConfigBlock)) {\
		GPS_DEBUG_MSG(("STBIN invalid ConfigBlock=%d\r\n", sname->ConfigBlock));\
		*(p_result) = STBIN_FAILED; }\
	GPS_DEBUG_MSG(("STBIN SectionId=0x%X\r\n", sname->SectionId));\
	if(6U < sname->SectionId) {\
		GPS_DEBUG_MSG(("STBIN invalid SectionId=%d\r\n", sname->SectionId));\
		*(p_result) = STBIN_FAILED; }\
	GPS_DEBUG_MSG(("STBIN ParamId=0x%X\r\n", sname->ParamId));\
	if(99U < sname->ParamId) {\
		GPS_DEBUG_MSG(("STBIN invalid ParamId=%d\r\n", sname->ParamId));\
		*(p_result) = STBIN_FAILED; }\
	if(len != sizeof(*sname)) {\
		GPS_DEBUG_MSG(("STBIN frame stbin_exec_sw_config_get_par received with Payload length %d vs %d\r\n", len, sizeof(*sname) - 0U));\
		*(p_result) = STBIN_FAILED; }

//Test structure size against computed size
typedef tS8 Teststbin_exec_sw_config_get_par_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(stbin_exec_sw_config_get_par_t)-3U)];
typedef tS8 Teststbin_exec_sw_config_get_par_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+3U-sizeof(stbin_exec_sw_config_get_par_t))];




//Frame stbin_exec_dump_almans (cid=0x2A mid=0xFD)
#define stbin_exec_dump_almans_MAP(sname, msg, len, p_result)\
	/*lint -e{9087} cast performed between a pointer to object type and a pointer to a different object type */ \
	stbin_exec_dump_almans_t *sname = (stbin_exec_dump_almans_t *)msg;\
	GPS_DEBUG_MSG(("STBIN Received Frame stbin_exec_dump_almans\r\n"));\
	GPS_DEBUG_MSG(("STBIN Constellation=0x%X\r\n", sname->Constellation));\
	if(3U < sname->Constellation) {\
		GPS_DEBUG_MSG(("STBIN invalid Constellation=%d\r\n", sname->Constellation));\
		*(p_result) = STBIN_FAILED; }\
	if(len != sizeof(*sname)) {\
		GPS_DEBUG_MSG(("STBIN frame stbin_exec_dump_almans received with Payload length %d vs %d\r\n", len, sizeof(*sname) - 0U));\
		*(p_result) = STBIN_FAILED; }

//Test structure size against computed size
typedef tS8 Teststbin_exec_dump_almans_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(stbin_exec_dump_almans_t)-1U)];
typedef tS8 Teststbin_exec_dump_almans_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+1U-sizeof(stbin_exec_dump_almans_t))];




//Frame stbin_exec_dump_ephems (cid=0x2A mid=0xFE)
#define stbin_exec_dump_ephems_MAP(sname, msg, len, p_result)\
	/*lint -e{9087} cast performed between a pointer to object type and a pointer to a different object type */ \
	stbin_exec_dump_ephems_t *sname = (stbin_exec_dump_ephems_t *)msg;\
	GPS_DEBUG_MSG(("STBIN Received Frame stbin_exec_dump_ephems\r\n"));\
	GPS_DEBUG_MSG(("STBIN Constellation=0x%X\r\n", sname->Constellation));\
	if(3U < sname->Constellation) {\
		GPS_DEBUG_MSG(("STBIN invalid Constellation=%d\r\n", sname->Constellation));\
		*(p_result) = STBIN_FAILED; }\
	if(len != sizeof(*sname)) {\
		GPS_DEBUG_MSG(("STBIN frame stbin_exec_dump_ephems received with Payload length %d vs %d\r\n", len, sizeof(*sname) - 0U));\
		*(p_result) = STBIN_FAILED; }

//Test structure size against computed size
typedef tS8 Teststbin_exec_dump_ephems_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(stbin_exec_dump_ephems_t)-1U)];
typedef tS8 Teststbin_exec_dump_ephems_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+1U-sizeof(stbin_exec_dump_ephems_t))];




//Frame stbin_exec_read_sw_config_all_blocks (cid=0x2A mid=0xF3)
#define stbin_exec_read_sw_config_all_blocks_MAP(sname, msg, len, p_result)\
	/*lint -e{9087} cast performed between a pointer to object type and a pointer to a different object type */ \
	stbin_exec_read_sw_config_all_blocks_t *sname = (stbin_exec_read_sw_config_all_blocks_t *)msg;\
	GPS_DEBUG_MSG(("STBIN Received Frame stbin_exec_read_sw_config_all_blocks\r\n"));\
	GPS_DEBUG_MSG(("STBIN config_type=0x%X\r\n", sname->config_type));\
	if((1U > sname->config_type) || (3U < sname->config_type)) {\
		GPS_DEBUG_MSG(("STBIN invalid config_type=%d\r\n", sname->config_type));\
		*(p_result) = STBIN_FAILED; }\
	if(len != sizeof(*sname)) {\
		GPS_DEBUG_MSG(("STBIN frame stbin_exec_read_sw_config_all_blocks received with Payload length %d vs %d\r\n", len, sizeof(*sname) - 0U));\
		*(p_result) = STBIN_FAILED; }

//Test structure size against computed size
typedef tS8 Teststbin_exec_read_sw_config_all_blocks_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(stbin_exec_read_sw_config_all_blocks_t)-1U)];
typedef tS8 Teststbin_exec_read_sw_config_all_blocks_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+1U-sizeof(stbin_exec_read_sw_config_all_blocks_t))];




//Frame stbin_exec_dump_fe (cid=0x2A mid=0x2E)
#define stbin_exec_dump_fe_MAP(sname, msg, len, p_result)\
	GPS_DEBUG_MSG(("STBIN Received Frame stbin_exec_dump_fe\r\n"));\
	if(len != 0U) {\
		GPS_DEBUG_MSG(("STBIN Dataless frame stbin_exec_dump_fe received with Payload length %d\r\n", len));\
		*(p_result) = STBIN_FAILED; }



//Frame stbin_exec_get_diff_source (cid=0x2A mid=0xF2)
#define stbin_exec_get_diff_source_MAP(sname, msg, len, p_result)\
	GPS_DEBUG_MSG(("STBIN Received Frame stbin_exec_get_diff_source\r\n"));\
	if(len != 0U) {\
		GPS_DEBUG_MSG(("STBIN Dataless frame stbin_exec_get_diff_source received with Payload length %d\r\n", len));\
		*(p_result) = STBIN_FAILED; }



//Frame stbin_exec_adc_read (cid=0x2A mid=0x24)
#define stbin_exec_adc_read_MAP(sname, msg, len, p_result)\
	/*lint -e{9087} cast performed between a pointer to object type and a pointer to a different object type */ \
	stbin_exec_adc_read_t *sname = (stbin_exec_adc_read_t *)msg;\
	GPS_DEBUG_MSG(("STBIN Received Frame stbin_exec_adc_read\r\n"));\
	GPS_DEBUG_MSG(("STBIN sel_line=%d\r\n", sname->sel_line));\
	GPS_DEBUG_MSG(("STBIN ain=%d\r\n", sname->ain));\
	if(len != (sizeof(*sname) - 2U)) {\
		GPS_DEBUG_MSG(("STBIN frame stbin_exec_adc_read received with Payload length %d vs %d\r\n", len, sizeof(*sname) - 2U));\
		*(p_result) = STBIN_FAILED; }

//Test structure size against computed size
typedef tS8 Teststbin_exec_adc_read_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(stbin_exec_adc_read_t)-4U)];
typedef tS8 Teststbin_exec_adc_read_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+4U-sizeof(stbin_exec_adc_read_t))];




//Frame stbin_exec_get_all_sw_ver (cid=0x2A mid=0x25)
#define stbin_exec_get_all_sw_ver_MAP(sname, msg, len, p_result)\
	GPS_DEBUG_MSG(("STBIN Received Frame stbin_exec_get_all_sw_ver\r\n"));\
	if(len != 0U) {\
		GPS_DEBUG_MSG(("STBIN Dataless frame stbin_exec_get_all_sw_ver received with Payload length %d\r\n", len));\
		*(p_result) = STBIN_FAILED; }

//Section : Customer Flash Storage Read Requests (ClassId 0x2B)


//Frame stbin_exec_sqi_data_get (cid=0x2B mid=0x4E)
#define stbin_exec_sqi_data_get_MAP(sname, msg, len, p_result)\
	/*lint -e{9087} cast performed between a pointer to object type and a pointer to a different object type */ \
	stbin_exec_sqi_data_get_t *sname = (stbin_exec_sqi_data_get_t *)msg;\
	GPS_DEBUG_MSG(("STBIN Received Frame stbin_exec_sqi_data_get\r\n"));\
	STBIN_FROM_LINK_ENDIAN_CONV_tU16(&(sname->offset));\
	GPS_DEBUG_MSG(("STBIN offset=0x%X\r\n", sname->offset));\
	if(65504U < sname->offset) {\
		GPS_DEBUG_MSG(("STBIN invalid offset=%d\r\n", sname->offset));\
		*(p_result) = STBIN_FAILED; }\
	if(len != sizeof(*sname)) {\
		GPS_DEBUG_MSG(("STBIN frame stbin_exec_sqi_data_get received with Payload length %d vs %d\r\n", len, sizeof(*sname) - 0U));\
		*(p_result) = STBIN_FAILED; }

//Test structure size against computed size
typedef tS8 Teststbin_exec_sqi_data_get_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(stbin_exec_sqi_data_get_t)-2U)];
typedef tS8 Teststbin_exec_sqi_data_get_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+2U-sizeof(stbin_exec_sqi_data_get_t))];


//Section : Write Requests (ClassId 0x3A)


//Frame stbin_exec_load_ephemes (cid=0x3A mid=0x1C)
#define stbin_exec_load_ephemes_MAP(sname, msg, len, p_result)\
	GPS_DEBUG_MSG(("STBIN Received Frame stbin_exec_load_ephemes\r\n"));\
	if(len != 0U) {\
		GPS_DEBUG_MSG(("STBIN Dataless frame stbin_exec_load_ephemes received with Payload length %d\r\n", len));\
		*(p_result) = STBIN_FAILED; }



//Frame stbin_exec_save_ephems (cid=0x3A mid=0xFE)
#define stbin_exec_save_ephems_MAP(sname, msg, len, p_result)\
	/*lint -e{9087} cast performed between a pointer to object type and a pointer to a different object type */ \
	stbin_exec_save_ephems_t *sname = (stbin_exec_save_ephems_t *)msg;\
	GPS_DEBUG_MSG(("STBIN Received Frame stbin_exec_save_ephems\r\n"));\
	GPS_DEBUG_MSG(("STBIN value=<arrays are not traced>\r\n"));\
	GPS_DEBUG_MSG(("STBIN dsp_satid=%d\r\n", sname->dsp_satid));\
	if(len != (sizeof(*sname) - 3U)) {\
		GPS_DEBUG_MSG(("STBIN frame stbin_exec_save_ephems received with Payload length %d vs %d\r\n", len, sizeof(*sname) - 3U));\
		*(p_result) = STBIN_FAILED; }

//Test structure size against computed size
typedef tS8 Teststbin_exec_save_ephems_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(stbin_exec_save_ephems_t)-68U)];
typedef tS8 Teststbin_exec_save_ephems_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+68U-sizeof(stbin_exec_save_ephems_t))];




//Frame stbin_exec_real_ephems_on_off (cid=0x3A mid=0x1F)
#define stbin_exec_real_ephems_on_off_MAP(sname, msg, len, p_result)\
	/*lint -e{9087} cast performed between a pointer to object type and a pointer to a different object type */ \
	stbin_exec_real_ephems_on_off_t *sname = (stbin_exec_real_ephems_on_off_t *)msg;\
	GPS_DEBUG_MSG(("STBIN Received Frame stbin_exec_real_ephems_on_off\r\n"));\
	GPS_DEBUG_MSG(("STBIN sat_id=0x%X\r\n", sname->sat_id));\
	if(255U < sname->sat_id) {\
		GPS_DEBUG_MSG(("STBIN invalid sat_id=%d\r\n", sname->sat_id));\
		*(p_result) = STBIN_FAILED; }\
	GPS_DEBUG_MSG(("STBIN param=%d\r\n", sname->param));\
	if(len != (sizeof(*sname) - 2U)) {\
		GPS_DEBUG_MSG(("STBIN frame stbin_exec_real_ephems_on_off received with Payload length %d vs %d\r\n", len, sizeof(*sname) - 2U));\
		*(p_result) = STBIN_FAILED; }

//Test structure size against computed size
typedef tS8 Teststbin_exec_real_ephems_on_off_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(stbin_exec_real_ephems_on_off_t)-4U)];
typedef tS8 Teststbin_exec_real_ephems_on_off_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+4U-sizeof(stbin_exec_real_ephems_on_off_t))];




//Frame stbin_exec_load_almanac (cid=0x3A mid=0x1D)
#define stbin_exec_load_almanac_MAP(sname, msg, len, p_result)\
	GPS_DEBUG_MSG(("STBIN Received Frame stbin_exec_load_almanac\r\n"));\
	if(len != 0U) {\
		GPS_DEBUG_MSG(("STBIN Dataless frame stbin_exec_load_almanac received with Payload length %d\r\n", len));\
		*(p_result) = STBIN_FAILED; }



//Frame stbin_exec_save_alams (cid=0x3A mid=0xFD)
#define stbin_exec_save_alams_MAP(sname, msg, len, p_result)\
	/*lint -e{9087} cast performed between a pointer to object type and a pointer to a different object type */ \
	stbin_exec_save_alams_t *sname = (stbin_exec_save_alams_t *)msg;\
	GPS_DEBUG_MSG(("STBIN Received Frame stbin_exec_save_alams\r\n"));\
	GPS_DEBUG_MSG(("STBIN value=<arrays are not traced>\r\n"));\
	GPS_DEBUG_MSG(("STBIN dsp_satid=%d\r\n", sname->dsp_satid));\
	if(len != (sizeof(*sname) - 3U)) {\
		GPS_DEBUG_MSG(("STBIN frame stbin_exec_save_alams received with Payload length %d vs %d\r\n", len, sizeof(*sname) - 3U));\
		*(p_result) = STBIN_FAILED; }

//Test structure size against computed size
typedef tS8 Teststbin_exec_save_alams_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(stbin_exec_save_alams_t)-44U)];
typedef tS8 Teststbin_exec_save_alams_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+44U-sizeof(stbin_exec_save_alams_t))];




//Frame sw_config_set_par_val_Char (cid=0x3A mid=0xFB)
#define sw_config_set_par_val_Char_MAP(sname, msg, len, p_result)\
	/*lint -e{9087} cast performed between a pointer to object type and a pointer to a different object type */ \
	sw_config_set_par_val_Char_t *sname = (sw_config_set_par_val_Char_t *)msg;\
	GPS_DEBUG_MSG(("STBIN Received Frame sw_config_set_par_val_Char\r\n"));\
	GPS_DEBUG_MSG(("STBIN value=0x%X\r\n", sname->value));\
	if(255U < sname->value) {\
		GPS_DEBUG_MSG(("STBIN invalid value=%d\r\n", sname->value));\
		*(p_result) = STBIN_FAILED; }\
	GPS_DEBUG_MSG(("STBIN configParamId=0x%X\r\n", sname->configParamId));\
	if(99U < sname->configParamId) {\
		GPS_DEBUG_MSG(("STBIN invalid configParamId=%d\r\n", sname->configParamId));\
		*(p_result) = STBIN_FAILED; }\
	if(len != (sizeof(*sname) - 2U)) {\
		GPS_DEBUG_MSG(("STBIN frame sw_config_set_par_val_Char received with Payload length %d vs %d\r\n", len, sizeof(*sname) - 2U));\
		*(p_result) = STBIN_FAILED; }

//Test structure size against computed size
typedef tS8 Testsw_config_set_par_val_Char_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(sw_config_set_par_val_Char_t)-4U)];
typedef tS8 Testsw_config_set_par_val_Char_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+4U-sizeof(sw_config_set_par_val_Char_t))];




//Frame sw_config_set_par_val_Int (cid=0x3A mid=0xFA)
#define sw_config_set_par_val_Int_MAP(sname, msg, len, p_result)\
	/*lint -e{9087} cast performed between a pointer to object type and a pointer to a different object type */ \
	sw_config_set_par_val_Int_t *sname = (sw_config_set_par_val_Int_t *)msg;\
	GPS_DEBUG_MSG(("STBIN Received Frame sw_config_set_par_val_Int\r\n"));\
	STBIN_FROM_LINK_ENDIAN_CONV_tS32(&(sname->value));\
	GPS_DEBUG_MSG(("STBIN value=%d\r\n", sname->value));\
	GPS_DEBUG_MSG(("STBIN configParamId=0x%X\r\n", sname->configParamId));\
	if((2U > sname->configParamId) || (5U < sname->configParamId)) {\
		GPS_DEBUG_MSG(("STBIN invalid configParamId=%d\r\n", sname->configParamId));\
		*(p_result) = STBIN_FAILED; }\
	if(len != (sizeof(*sname) - 3U)) {\
		GPS_DEBUG_MSG(("STBIN frame sw_config_set_par_val_Int received with Payload length %d vs %d\r\n", len, sizeof(*sname) - 3U));\
		*(p_result) = STBIN_FAILED; }

//Test structure size against computed size
typedef tS8 Testsw_config_set_par_val_Int_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(sw_config_set_par_val_Int_t)-8U)];
typedef tS8 Testsw_config_set_par_val_Int_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+8U-sizeof(sw_config_set_par_val_Int_t))];




//Frame sw_config_set_par_val_UInt (cid=0x3A mid=0xF9)
#define sw_config_set_par_val_UInt_MAP(sname, msg, len, p_result)\
	/*lint -e{9087} cast performed between a pointer to object type and a pointer to a different object type */ \
	sw_config_set_par_val_UInt_t *sname = (sw_config_set_par_val_UInt_t *)msg;\
	GPS_DEBUG_MSG(("STBIN Received Frame sw_config_set_par_val_UInt\r\n"));\
	STBIN_FROM_LINK_ENDIAN_CONV_tU32(&(sname->value));\
	GPS_DEBUG_MSG(("STBIN value=%d\r\n", sname->value));\
	GPS_DEBUG_MSG(("STBIN mode=0x%X\r\n", sname->mode));\
	if(2U < sname->mode) {\
		GPS_DEBUG_MSG(("STBIN invalid mode=%d\r\n", sname->mode));\
		*(p_result) = STBIN_FAILED; }\
	GPS_DEBUG_MSG(("STBIN configSection=0x%X\r\n", sname->configSection));\
	if((2U > sname->configSection) || (6U < sname->configSection)) {\
		GPS_DEBUG_MSG(("STBIN invalid configSection=%d\r\n", sname->configSection));\
		*(p_result) = STBIN_FAILED; }\
	GPS_DEBUG_MSG(("STBIN configParamId=0x%X\r\n", sname->configParamId));\
	if(70U < sname->configParamId) {\
		GPS_DEBUG_MSG(("STBIN invalid configParamId=%d\r\n", sname->configParamId));\
		*(p_result) = STBIN_FAILED; }\
	if(len != (sizeof(*sname) - 1U)) {\
		GPS_DEBUG_MSG(("STBIN frame sw_config_set_par_val_UInt received with Payload length %d vs %d\r\n", len, sizeof(*sname) - 1U));\
		*(p_result) = STBIN_FAILED; }

//Test structure size against computed size
typedef tS8 Testsw_config_set_par_val_UInt_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(sw_config_set_par_val_UInt_t)-8U)];
typedef tS8 Testsw_config_set_par_val_UInt_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+8U-sizeof(sw_config_set_par_val_UInt_t))];




//Frame sw_config_set_par_val_Double (cid=0x3A mid=0xF8)
#define sw_config_set_par_val_Double_MAP(sname, msg, len, p_result)\
	/*lint -e{9087} cast performed between a pointer to object type and a pointer to a different object type */ \
	sw_config_set_par_val_Double_t *sname = (sw_config_set_par_val_Double_t *)msg;\
	GPS_DEBUG_MSG(("STBIN Received Frame sw_config_set_par_val_Double\r\n"));\
	STBIN_FROM_LINK_ENDIAN_CONV_double(&(sname->value));\
	GPS_DEBUG_MSG(("STBIN value=%d\r\n", sname->value));\
	GPS_DEBUG_MSG(("STBIN configParamId=0x%X\r\n", sname->configParamId));\
	if(9U < sname->configParamId) {\
		GPS_DEBUG_MSG(("STBIN invalid configParamId=%d\r\n", sname->configParamId));\
		*(p_result) = STBIN_FAILED; }\
	if(len != (sizeof(*sname) - 7U)) {\
		GPS_DEBUG_MSG(("STBIN frame sw_config_set_par_val_Double received with Payload length %d vs %d\r\n", len, sizeof(*sname) - 7U));\
		*(p_result) = STBIN_FAILED; }

//Test structure size against computed size
typedef tS8 Testsw_config_set_par_val_Double_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(sw_config_set_par_val_Double_t)-16U)];
typedef tS8 Testsw_config_set_par_val_Double_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+16U-sizeof(sw_config_set_par_val_Double_t))];




//Frame sw_config_set_par_val_Dops (cid=0x3A mid=0xF7)
#define sw_config_set_par_val_Dops_MAP(sname, msg, len, p_result)\
	/*lint -e{9087} cast performed between a pointer to object type and a pointer to a different object type */ \
	sw_config_set_par_val_Dops_t *sname = (sw_config_set_par_val_Dops_t *)msg;\
	GPS_DEBUG_MSG(("STBIN Received Frame sw_config_set_par_val_Dops\r\n"));\
	GPS_DEBUG_MSG(("STBIN pdop=0x%X\r\n", sname->pdop));\
	if(255U < sname->pdop) {\
		GPS_DEBUG_MSG(("STBIN invalid pdop=%d\r\n", sname->pdop));\
		*(p_result) = STBIN_FAILED; }\
	GPS_DEBUG_MSG(("STBIN vdop=0x%X\r\n", sname->vdop));\
	if(255U < sname->vdop) {\
		GPS_DEBUG_MSG(("STBIN invalid vdop=%d\r\n", sname->vdop));\
		*(p_result) = STBIN_FAILED; }\
	GPS_DEBUG_MSG(("STBIN hdop=0x%X\r\n", sname->hdop));\
	if(255U < sname->hdop) {\
		GPS_DEBUG_MSG(("STBIN invalid hdop=%d\r\n", sname->hdop));\
		*(p_result) = STBIN_FAILED; }\
	GPS_DEBUG_MSG(("STBIN gdop=0x%X\r\n", sname->gdop));\
	if(255U < sname->gdop) {\
		GPS_DEBUG_MSG(("STBIN invalid gdop=%d\r\n", sname->gdop));\
		*(p_result) = STBIN_FAILED; }\
	GPS_DEBUG_MSG(("STBIN configParamId=0x%X\r\n", sname->configParamId));\
	if(3U < sname->configParamId) {\
		GPS_DEBUG_MSG(("STBIN invalid configParamId=%d\r\n", sname->configParamId));\
		*(p_result) = STBIN_FAILED; }\
	if(len != (sizeof(*sname) - 3U)) {\
		GPS_DEBUG_MSG(("STBIN frame sw_config_set_par_val_Dops received with Payload length %d vs %d\r\n", len, sizeof(*sname) - 3U));\
		*(p_result) = STBIN_FAILED; }

//Test structure size against computed size
typedef tS8 Testsw_config_set_par_val_Dops_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(sw_config_set_par_val_Dops_t)-8U)];
typedef tS8 Testsw_config_set_par_val_Dops_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+8U-sizeof(sw_config_set_par_val_Dops_t))];




//Frame sw_config_set_par_val_String (cid=0x3A mid=0xF6)
#define sw_config_set_par_val_String_MAP(sname, msg, len, p_result)\
	/*lint -e{9087} cast performed between a pointer to object type and a pointer to a different object type */ \
	sw_config_set_par_val_String_t *sname = (sw_config_set_par_val_String_t *)msg;\
	GPS_DEBUG_MSG(("STBIN Received Frame sw_config_set_par_val_String\r\n"));\
	GPS_DEBUG_MSG(("STBIN value=<strings are not traced>\r\n"));\
	GPS_DEBUG_MSG(("STBIN configParamId=0x%X\r\n", sname->configParamId));\
	if(0U < sname->configParamId) {\
		GPS_DEBUG_MSG(("STBIN invalid configParamId=%d\r\n", sname->configParamId));\
		*(p_result) = STBIN_FAILED; }\
	if(len != (sizeof(*sname) - 3U)) {\
		GPS_DEBUG_MSG(("STBIN frame sw_config_set_par_val_String received with Payload length %d vs %d\r\n", len, sizeof(*sname) - 3U));\
		*(p_result) = STBIN_FAILED; }

//Test structure size against computed size
typedef tS8 Testsw_config_set_par_val_String_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(sw_config_set_par_val_String_t)-76U)];
typedef tS8 Testsw_config_set_par_val_String_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+76U-sizeof(sw_config_set_par_val_String_t))];




//Frame set_algo_status (cid=0x3A mid=0xF5)
#define set_algo_status_MAP(sname, msg, len, p_result)\
	/*lint -e{9087} cast performed between a pointer to object type and a pointer to a different object type */ \
	set_algo_status_t *sname = (set_algo_status_t *)msg;\
	GPS_DEBUG_MSG(("STBIN Received Frame set_algo_status\r\n"));\
	GPS_DEBUG_MSG(("STBIN algo_type=0x%X\r\n", sname->algo_type));\
	if((1U > sname->algo_type) || (1U < sname->algo_type)) {\
		GPS_DEBUG_MSG(("STBIN invalid algo_type=%d\r\n", sname->algo_type));\
		*(p_result) = STBIN_FAILED; }\
	GPS_DEBUG_MSG(("STBIN algo_status=0x%X\r\n", sname->algo_status));\
	if(1U < sname->algo_status) {\
		GPS_DEBUG_MSG(("STBIN invalid algo_status=%d\r\n", sname->algo_status));\
		*(p_result) = STBIN_FAILED; }\
	if(len != (sizeof(*sname) - 2U)) {\
		GPS_DEBUG_MSG(("STBIN frame set_algo_status received with Payload length %d vs %d\r\n", len, sizeof(*sname) - 2U));\
		*(p_result) = STBIN_FAILED; }

//Test structure size against computed size
typedef tS8 Testset_algo_status_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(set_algo_status_t)-4U)];
typedef tS8 Testset_algo_status_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+4U-sizeof(set_algo_status_t))];




//Frame stbin_exec_write_datum_selection (cid=0x3A mid=0xF4)
#define stbin_exec_write_datum_selection_MAP(sname, msg, len, p_result)\
	/*lint -e{9087} cast performed between a pointer to object type and a pointer to a different object type */ \
	stbin_exec_write_datum_selection_t *sname = (stbin_exec_write_datum_selection_t *)msg;\
	GPS_DEBUG_MSG(("STBIN Received Frame stbin_exec_write_datum_selection\r\n"));\
	GPS_DEBUG_MSG(("STBIN datum=0x%X\r\n", sname->datum));\
	if(228U < sname->datum) {\
		GPS_DEBUG_MSG(("STBIN invalid datum=%d\r\n", sname->datum));\
		*(p_result) = STBIN_FAILED; }\
	if(len != sizeof(*sname)) {\
		GPS_DEBUG_MSG(("STBIN frame stbin_exec_write_datum_selection received with Payload length %d vs %d\r\n", len, sizeof(*sname) - 0U));\
		*(p_result) = STBIN_FAILED; }

//Test structure size against computed size
typedef tS8 Teststbin_exec_write_datum_selection_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(stbin_exec_write_datum_selection_t)-1U)];
typedef tS8 Teststbin_exec_write_datum_selection_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+1U-sizeof(stbin_exec_write_datum_selection_t))];




//Frame stbin_exec_define_datum (cid=0x3A mid=0x7)
#define stbin_exec_define_datum_MAP(sname, msg, len, p_result)\
	/*lint -e{9087} cast performed between a pointer to object type and a pointer to a different object type */ \
	stbin_exec_define_datum_t *sname = (stbin_exec_define_datum_t *)msg;\
	GPS_DEBUG_MSG(("STBIN Received Frame stbin_exec_define_datum\r\n"));\
	STBIN_FROM_LINK_ENDIAN_CONV_double(&(sname->d_x));\
	GPS_DEBUG_MSG(("STBIN d_x=%d\r\n", sname->d_x));\
	STBIN_FROM_LINK_ENDIAN_CONV_double(&(sname->d_y));\
	GPS_DEBUG_MSG(("STBIN d_y=%d\r\n", sname->d_y));\
	STBIN_FROM_LINK_ENDIAN_CONV_double(&(sname->d_z));\
	GPS_DEBUG_MSG(("STBIN d_z=%d\r\n", sname->d_z));\
	STBIN_FROM_LINK_ENDIAN_CONV_double(&(sname->d_a));\
	GPS_DEBUG_MSG(("STBIN d_a=%d\r\n", sname->d_a));\
	STBIN_FROM_LINK_ENDIAN_CONV_double(&(sname->d_f));\
	GPS_DEBUG_MSG(("STBIN d_f=%d\r\n", sname->d_f));\
	if(len != sizeof(*sname)) {\
		GPS_DEBUG_MSG(("STBIN frame stbin_exec_define_datum received with Payload length %d vs %d\r\n", len, sizeof(*sname) - 0U));\
		*(p_result) = STBIN_FAILED; }

//Test structure size against computed size
typedef tS8 Teststbin_exec_define_datum_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(stbin_exec_define_datum_t)-40U)];
typedef tS8 Teststbin_exec_define_datum_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+40U-sizeof(stbin_exec_define_datum_t))];




//Frame stbin_exec_sw_config_save_param (cid=0x3A mid=0x16)
#define stbin_exec_sw_config_save_param_MAP(sname, msg, len, p_result)\
	/*lint -e{9087} cast performed between a pointer to object type and a pointer to a different object type */ \
	stbin_exec_sw_config_save_param_t *sname = (stbin_exec_sw_config_save_param_t *)msg;\
	GPS_DEBUG_MSG(("STBIN Received Frame stbin_exec_sw_config_save_param\r\n"));\
	GPS_DEBUG_MSG(("STBIN control=0x%X\r\n", sname->control));\
	if(0U < sname->control) {\
		GPS_DEBUG_MSG(("STBIN invalid control=%d\r\n", sname->control));\
		*(p_result) = STBIN_FAILED; }\
	if(len != sizeof(*sname)) {\
		GPS_DEBUG_MSG(("STBIN frame stbin_exec_sw_config_save_param received with Payload length %d vs %d\r\n", len, sizeof(*sname) - 0U));\
		*(p_result) = STBIN_FAILED; }

//Test structure size against computed size
typedef tS8 Teststbin_exec_sw_config_save_param_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(stbin_exec_sw_config_save_param_t)-1U)];
typedef tS8 Teststbin_exec_sw_config_save_param_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+1U-sizeof(stbin_exec_sw_config_save_param_t))];




//Frame stbin_exec_sw_config_restore_param (cid=0x3A mid=0x17)
#define stbin_exec_sw_config_restore_param_MAP(sname, msg, len, p_result)\
	/*lint -e{9087} cast performed between a pointer to object type and a pointer to a different object type */ \
	stbin_exec_sw_config_restore_param_t *sname = (stbin_exec_sw_config_restore_param_t *)msg;\
	GPS_DEBUG_MSG(("STBIN Received Frame stbin_exec_sw_config_restore_param\r\n"));\
	GPS_DEBUG_MSG(("STBIN control=0x%X\r\n", sname->control));\
	if(0U < sname->control) {\
		GPS_DEBUG_MSG(("STBIN invalid control=%d\r\n", sname->control));\
		*(p_result) = STBIN_FAILED; }\
	if(len != sizeof(*sname)) {\
		GPS_DEBUG_MSG(("STBIN frame stbin_exec_sw_config_restore_param received with Payload length %d vs %d\r\n", len, sizeof(*sname) - 0U));\
		*(p_result) = STBIN_FAILED; }

//Test structure size against computed size
typedef tS8 Teststbin_exec_sw_config_restore_param_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(stbin_exec_sw_config_restore_param_t)-1U)];
typedef tS8 Teststbin_exec_sw_config_restore_param_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+1U-sizeof(stbin_exec_sw_config_restore_param_t))];




//Frame stbin_exec_set_range (cid=0x3A mid=0x2)
#define stbin_exec_set_range_MAP(sname, msg, len, p_result)\
	/*lint -e{9087} cast performed between a pointer to object type and a pointer to a different object type */ \
	stbin_exec_set_range_t *sname = (stbin_exec_set_range_t *)msg;\
	GPS_DEBUG_MSG(("STBIN Received Frame stbin_exec_set_range\r\n"));\
	STBIN_FROM_LINK_ENDIAN_CONV_tS32(&(sname->min));\
	GPS_DEBUG_MSG(("STBIN min=0x%X\r\n", sname->min));\
	if((-132000 > sname->min) || (132000 < sname->min)) {\
		GPS_DEBUG_MSG(("STBIN invalid min=%d\r\n", sname->min));\
		*(p_result) = STBIN_FAILED; }\
	STBIN_FROM_LINK_ENDIAN_CONV_tS32(&(sname->max));\
	GPS_DEBUG_MSG(("STBIN max=0x%X\r\n", sname->max));\
	if((-132000 > sname->max) || (132000 < sname->max)) {\
		GPS_DEBUG_MSG(("STBIN invalid max=%d\r\n", sname->max));\
		*(p_result) = STBIN_FAILED; }\
	if(len != sizeof(*sname)) {\
		GPS_DEBUG_MSG(("STBIN frame stbin_exec_set_range received with Payload length %d vs %d\r\n", len, sizeof(*sname) - 0U));\
		*(p_result) = STBIN_FAILED; }

//Test structure size against computed size
typedef tS8 Teststbin_exec_set_range_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(stbin_exec_set_range_t)-8U)];
typedef tS8 Teststbin_exec_set_range_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+8U-sizeof(stbin_exec_set_range_t))];




//Frame stbin_exec_set_constellation_mask (cid=0x3A mid=0x6)
#define stbin_exec_set_constellation_mask_MAP(sname, msg, len, p_result)\
	/*lint -e{9087} cast performed between a pointer to object type and a pointer to a different object type */ \
	stbin_exec_set_constellation_mask_t *sname = (stbin_exec_set_constellation_mask_t *)msg;\
	GPS_DEBUG_MSG(("STBIN Received Frame stbin_exec_set_constellation_mask\r\n"));\
	STBIN_FROM_LINK_ENDIAN_CONV_tU32(&(sname->constellation_mask));\
	GPS_DEBUG_MSG(("STBIN constellation_mask=%d\r\n", sname->constellation_mask));\
	GPS_DEBUG_MSG(("STBIN slave_reset=%d\r\n", sname->slave_reset));\
	if(len != (sizeof(*sname) - 3U)) {\
		GPS_DEBUG_MSG(("STBIN frame stbin_exec_set_constellation_mask received with Payload length %d vs %d\r\n", len, sizeof(*sname) - 3U));\
		*(p_result) = STBIN_FAILED; }

//Test structure size against computed size
typedef tS8 Teststbin_exec_set_constellation_mask_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(stbin_exec_set_constellation_mask_t)-8U)];
typedef tS8 Teststbin_exec_set_constellation_mask_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+8U-sizeof(stbin_exec_set_constellation_mask_t))];




//Frame stbin_exec_debug_on_off (cid=0x3A mid=0xB)
#define stbin_exec_debug_on_off_MAP(sname, msg, len, p_result)\
	/*lint -e{9087} cast performed between a pointer to object type and a pointer to a different object type */ \
	stbin_exec_debug_on_off_t *sname = (stbin_exec_debug_on_off_t *)msg;\
	GPS_DEBUG_MSG(("STBIN Received Frame stbin_exec_debug_on_off\r\n"));\
	GPS_DEBUG_MSG(("STBIN on_off=%d\r\n", sname->on_off));\
	if(len != (sizeof(*sname) - 3U)) {\
		GPS_DEBUG_MSG(("STBIN frame stbin_exec_debug_on_off received with Payload length %d vs %d\r\n", len, sizeof(*sname) - 3U));\
		*(p_result) = STBIN_FAILED; }

//Test structure size against computed size
typedef tS8 Teststbin_exec_debug_on_off_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(stbin_exec_debug_on_off_t)-4U)];
typedef tS8 Teststbin_exec_debug_on_off_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+4U-sizeof(stbin_exec_debug_on_off_t))];




//Frame stbin_exec_time_inv (cid=0x3A mid=0xC)
#define stbin_exec_time_inv_MAP(sname, msg, len, p_result)\
	GPS_DEBUG_MSG(("STBIN Received Frame stbin_exec_time_inv\r\n"));\
	if(len != 0U) {\
		GPS_DEBUG_MSG(("STBIN Dataless frame stbin_exec_time_inv received with Payload length %d\r\n", len));\
		*(p_result) = STBIN_FAILED; }



//Frame stbin_exec_nvm_swap (cid=0x3A mid=0xF)
#define stbin_exec_nvm_swap_MAP(sname, msg, len, p_result)\
	GPS_DEBUG_MSG(("STBIN Received Frame stbin_exec_nvm_swap\r\n"));\
	if(len != 0U) {\
		GPS_DEBUG_MSG(("STBIN Dataless frame stbin_exec_nvm_swap received with Payload length %d\r\n", len));\
		*(p_result) = STBIN_FAILED; }



//Frame stbin_exec_fix2d_on_off (cid=0x3A mid=0x12)
#define stbin_exec_fix2d_on_off_MAP(sname, msg, len, p_result)\
	/*lint -e{9087} cast performed between a pointer to object type and a pointer to a different object type */ \
	stbin_exec_fix2d_on_off_t *sname = (stbin_exec_fix2d_on_off_t *)msg;\
	GPS_DEBUG_MSG(("STBIN Received Frame stbin_exec_fix2d_on_off\r\n"));\
	GPS_DEBUG_MSG(("STBIN on_off=%d\r\n", sname->on_off));\
	if(len != (sizeof(*sname) - 3U)) {\
		GPS_DEBUG_MSG(("STBIN frame stbin_exec_fix2d_on_off received with Payload length %d vs %d\r\n", len, sizeof(*sname) - 3U));\
		*(p_result) = STBIN_FAILED; }

//Test structure size against computed size
typedef tS8 Teststbin_exec_fix2d_on_off_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(stbin_exec_fix2d_on_off_t)-4U)];
typedef tS8 Teststbin_exec_fix2d_on_off_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+4U-sizeof(stbin_exec_fix2d_on_off_t))];




//Frame stbin_exec_notch_enable (cid=0x3A mid=0x1B)
#define stbin_exec_notch_enable_MAP(sname, msg, len, p_result)\
	/*lint -e{9087} cast performed between a pointer to object type and a pointer to a different object type */ \
	stbin_exec_notch_enable_t *sname = (stbin_exec_notch_enable_t *)msg;\
	GPS_DEBUG_MSG(("STBIN Received Frame stbin_exec_notch_enable\r\n"));\
	STBIN_FROM_LINK_ENDIAN_CONV_tS32(&(sname->Reserved));\
	GPS_DEBUG_MSG(("STBIN Reserved=%d\r\n", sname->Reserved));\
	GPS_DEBUG_MSG(("STBIN sat_type=%d\r\n", sname->sat_type));\
	GPS_DEBUG_MSG(("STBIN mode=%d\r\n", sname->mode));\
	if(len != (sizeof(*sname) - 2U)) {\
		GPS_DEBUG_MSG(("STBIN frame stbin_exec_notch_enable received with Payload length %d vs %d\r\n", len, sizeof(*sname) - 2U));\
		*(p_result) = STBIN_FAILED; }

//Test structure size against computed size
typedef tS8 Teststbin_exec_notch_enable_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(stbin_exec_notch_enable_t)-8U)];
typedef tS8 Teststbin_exec_notch_enable_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+8U-sizeof(stbin_exec_notch_enable_t))];




//Frame stbin_exec_enable_disable_position_hold (cid=0x3A mid=0x1E)
#define stbin_exec_enable_disable_position_hold_MAP(sname, msg, len, p_result)\
	/*lint -e{9087} cast performed between a pointer to object type and a pointer to a different object type */ \
	stbin_exec_enable_disable_position_hold_t *sname = (stbin_exec_enable_disable_position_hold_t *)msg;\
	GPS_DEBUG_MSG(("STBIN Received Frame stbin_exec_enable_disable_position_hold\r\n"));\
	STBIN_FROM_LINK_ENDIAN_CONV_tS32(&(sname->lat));\
	GPS_DEBUG_MSG(("STBIN lat=0x%X\r\n", sname->lat));\
	if((-900000000 > sname->lat) || (900000000 < sname->lat)) {\
		GPS_DEBUG_MSG(("STBIN invalid lat=%d\r\n", sname->lat));\
		*(p_result) = STBIN_FAILED; }\
	STBIN_FROM_LINK_ENDIAN_CONV_tS32(&(sname->lon));\
	GPS_DEBUG_MSG(("STBIN lon=0x%X\r\n", sname->lon));\
	if((-1800000000 > sname->lon) || (1800000000 < sname->lon)) {\
		GPS_DEBUG_MSG(("STBIN invalid lon=%d\r\n", sname->lon));\
		*(p_result) = STBIN_FAILED; }\
	STBIN_FROM_LINK_ENDIAN_CONV_tS32(&(sname->alt));\
	GPS_DEBUG_MSG(("STBIN alt=0x%X\r\n", sname->alt));\
	if((-1500000 > sname->alt) || (100000000 < sname->alt)) {\
		GPS_DEBUG_MSG(("STBIN invalid alt=%d\r\n", sname->alt));\
		*(p_result) = STBIN_FAILED; }\
	GPS_DEBUG_MSG(("STBIN on_off=%d\r\n", sname->on_off));\
	if(len != (sizeof(*sname) - 3U)) {\
		GPS_DEBUG_MSG(("STBIN frame stbin_exec_enable_disable_position_hold received with Payload length %d vs %d\r\n", len, sizeof(*sname) - 3U));\
		*(p_result) = STBIN_FAILED; }

//Test structure size against computed size
typedef tS8 Teststbin_exec_enable_disable_position_hold_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(stbin_exec_enable_disable_position_hold_t)-16U)];
typedef tS8 Teststbin_exec_enable_disable_position_hold_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+16U-sizeof(stbin_exec_enable_disable_position_hold_t))];




//Frame stbin_exec_write_sw_config_all_blocks (cid=0x3A mid=0xF3)
#define stbin_exec_write_sw_config_all_blocks_MAP(sname, msg, len, p_result)\
	/*lint -e{9087} cast performed between a pointer to object type and a pointer to a different object type */ \
	stbin_exec_write_sw_config_all_blocks_t *sname = (stbin_exec_write_sw_config_all_blocks_t *)msg;\
	GPS_DEBUG_MSG(("STBIN Received Frame stbin_exec_write_sw_config_all_blocks\r\n"));\
	STBIN_FROM_LINK_ENDIAN_CONV_tU16(&(sname->length));\
	GPS_DEBUG_MSG(("STBIN length=0x%X\r\n", sname->length));\
	if(905U < sname->length) {\
		GPS_DEBUG_MSG(("STBIN invalid length=%d\r\n", sname->length));\
		*(p_result) = STBIN_FAILED; }\
	GPS_DEBUG_MSG(("STBIN value=<arrays are not traced>\r\n"));\
	if(len != (sizeof(*sname) - 1U)) {\
		GPS_DEBUG_MSG(("STBIN frame stbin_exec_write_sw_config_all_blocks received with Payload length %d vs %d\r\n", len, sizeof(*sname) - 1U));\
		*(p_result) = STBIN_FAILED; }

//Test structure size against computed size
typedef tS8 Teststbin_exec_write_sw_config_all_blocks_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(stbin_exec_write_sw_config_all_blocks_t)-908U)];
typedef tS8 Teststbin_exec_write_sw_config_all_blocks_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+908U-sizeof(stbin_exec_write_sw_config_all_blocks_t))];




//Frame stbin_exec_set_gps_pos (cid=0x3A mid=0x1)
#define stbin_exec_set_gps_pos_MAP(sname, msg, len, p_result)\
	/*lint -e{9087} cast performed between a pointer to object type and a pointer to a different object type */ \
	stbin_exec_set_gps_pos_t *sname = (stbin_exec_set_gps_pos_t *)msg;\
	GPS_DEBUG_MSG(("STBIN Received Frame stbin_exec_set_gps_pos\r\n"));\
	STBIN_FROM_LINK_ENDIAN_CONV_tS32(&(sname->lat));\
	GPS_DEBUG_MSG(("STBIN lat=0x%X\r\n", sname->lat));\
	if((-900000000 > sname->lat) || (900000000 < sname->lat)) {\
		GPS_DEBUG_MSG(("STBIN invalid lat=%d\r\n", sname->lat));\
		*(p_result) = STBIN_FAILED; }\
	STBIN_FROM_LINK_ENDIAN_CONV_tS32(&(sname->lon));\
	GPS_DEBUG_MSG(("STBIN lon=0x%X\r\n", sname->lon));\
	if((-1800000000 > sname->lon) || (1800000000 < sname->lon)) {\
		GPS_DEBUG_MSG(("STBIN invalid lon=%d\r\n", sname->lon));\
		*(p_result) = STBIN_FAILED; }\
	STBIN_FROM_LINK_ENDIAN_CONV_tS32(&(sname->alt));\
	GPS_DEBUG_MSG(("STBIN alt=0x%X\r\n", sname->alt));\
	if((-1500000 > sname->alt) || (100000000 < sname->alt)) {\
		GPS_DEBUG_MSG(("STBIN invalid alt=%d\r\n", sname->alt));\
		*(p_result) = STBIN_FAILED; }\
	if(len != sizeof(*sname)) {\
		GPS_DEBUG_MSG(("STBIN frame stbin_exec_set_gps_pos received with Payload length %d vs %d\r\n", len, sizeof(*sname) - 0U));\
		*(p_result) = STBIN_FAILED; }

//Test structure size against computed size
typedef tS8 Teststbin_exec_set_gps_pos_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(stbin_exec_set_gps_pos_t)-12U)];
typedef tS8 Teststbin_exec_set_gps_pos_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+12U-sizeof(stbin_exec_set_gps_pos_t))];




//Frame stbin_exec_set_diff_source (cid=0x3A mid=0xF2)
#define stbin_exec_set_diff_source_MAP(sname, msg, len, p_result)\
	/*lint -e{9087} cast performed between a pointer to object type and a pointer to a different object type */ \
	stbin_exec_set_diff_source_t *sname = (stbin_exec_set_diff_source_t *)msg;\
	GPS_DEBUG_MSG(("STBIN Received Frame stbin_exec_set_diff_source\r\n"));\
	GPS_DEBUG_MSG(("STBIN diff_source=0x%X\r\n", sname->diff_source));\
	if(3U < sname->diff_source) {\
		GPS_DEBUG_MSG(("STBIN invalid diff_source=%d\r\n", sname->diff_source));\
		*(p_result) = STBIN_FAILED; }\
	if(len != (sizeof(*sname) - 3U)) {\
		GPS_DEBUG_MSG(("STBIN frame stbin_exec_set_diff_source received with Payload length %d vs %d\r\n", len, sizeof(*sname) - 3U));\
		*(p_result) = STBIN_FAILED; }

//Test structure size against computed size
typedef tS8 Teststbin_exec_set_diff_source_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(stbin_exec_set_diff_source_t)-4U)];
typedef tS8 Teststbin_exec_set_diff_source_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+4U-sizeof(stbin_exec_set_diff_source_t))];




//Frame stbin_exec_set_fix_rate (cid=0x3A mid=0x5)
#define stbin_exec_set_fix_rate_MAP(sname, msg, len, p_result)\
	/*lint -e{9087} cast performed between a pointer to object type and a pointer to a different object type */ \
	stbin_exec_set_fix_rate_t *sname = (stbin_exec_set_fix_rate_t *)msg;\
	GPS_DEBUG_MSG(("STBIN Received Frame stbin_exec_set_fix_rate\r\n"));\
	STBIN_FROM_LINK_ENDIAN_CONV_tU16(&(sname->fix_rate));\
	GPS_DEBUG_MSG(("STBIN fix_rate=0x%X\r\n", sname->fix_rate));\
	if((100U > sname->fix_rate) || (30000U < sname->fix_rate)) {\
		GPS_DEBUG_MSG(("STBIN invalid fix_rate=%d\r\n", sname->fix_rate));\
		*(p_result) = STBIN_FAILED; }\
	if(len != (sizeof(*sname) - 2U)) {\
		GPS_DEBUG_MSG(("STBIN frame stbin_exec_set_fix_rate received with Payload length %d vs %d\r\n", len, sizeof(*sname) - 2U));\
		*(p_result) = STBIN_FAILED; }

//Test structure size against computed size
typedef tS8 Teststbin_exec_set_fix_rate_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(stbin_exec_set_fix_rate_t)-4U)];
typedef tS8 Teststbin_exec_set_fix_rate_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+4U-sizeof(stbin_exec_set_fix_rate_t))];




//Frame stbin_exec_nvm_item_inv (cid=0x3A mid=0x10)
#define stbin_exec_nvm_item_inv_MAP(sname, msg, len, p_result)\
	/*lint -e{9087} cast performed between a pointer to object type and a pointer to a different object type */ \
	stbin_exec_nvm_item_inv_t *sname = (stbin_exec_nvm_item_inv_t *)msg;\
	GPS_DEBUG_MSG(("STBIN Received Frame stbin_exec_nvm_item_inv\r\n"));\
	STBIN_FROM_LINK_ENDIAN_CONV_tS32(&(sname->item_number));\
	GPS_DEBUG_MSG(("STBIN item_number=%d\r\n", sname->item_number));\
	GPS_DEBUG_MSG(("STBIN nvm_id=0x%X\r\n", sname->nvm_id));\
	if((1U > sname->nvm_id) || (255U < sname->nvm_id)) {\
		GPS_DEBUG_MSG(("STBIN invalid nvm_id=%d\r\n", sname->nvm_id));\
		*(p_result) = STBIN_FAILED; }\
	GPS_DEBUG_MSG(("STBIN sat_id=%d\r\n", sname->sat_id));\
	if(len != (sizeof(*sname) - 2U)) {\
		GPS_DEBUG_MSG(("STBIN frame stbin_exec_nvm_item_inv received with Payload length %d vs %d\r\n", len, sizeof(*sname) - 2U));\
		*(p_result) = STBIN_FAILED; }

//Test structure size against computed size
typedef tS8 Teststbin_exec_nvm_item_inv_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(stbin_exec_nvm_item_inv_t)-8U)];
typedef tS8 Teststbin_exec_nvm_item_inv_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+8U-sizeof(stbin_exec_nvm_item_inv_t))];




//Frame stbin_exec_gps_fw_update (cid=0x3A mid=0x11)
#define stbin_exec_gps_fw_update_MAP(sname, msg, len, p_result)\
	GPS_DEBUG_MSG(("STBIN Received Frame stbin_exec_gps_fw_update\r\n"));\
	if(len != 0U) {\
		GPS_DEBUG_MSG(("STBIN Dataless frame stbin_exec_gps_fw_update received with Payload length %d\r\n", len));\
		*(p_result) = STBIN_FAILED; }



//Frame stbin_exec_stop_detection_on_off (cid=0x3A mid=0x13)
#define stbin_exec_stop_detection_on_off_MAP(sname, msg, len, p_result)\
	/*lint -e{9087} cast performed between a pointer to object type and a pointer to a different object type */ \
	stbin_exec_stop_detection_on_off_t *sname = (stbin_exec_stop_detection_on_off_t *)msg;\
	GPS_DEBUG_MSG(("STBIN Received Frame stbin_exec_stop_detection_on_off\r\n"));\
	GPS_DEBUG_MSG(("STBIN on_off=0x%X\r\n", sname->on_off));\
	if(1U < sname->on_off) {\
		GPS_DEBUG_MSG(("STBIN invalid on_off=%d\r\n", sname->on_off));\
		*(p_result) = STBIN_FAILED; }\
	if(len != (sizeof(*sname) - 3U)) {\
		GPS_DEBUG_MSG(("STBIN frame stbin_exec_stop_detection_on_off received with Payload length %d vs %d\r\n", len, sizeof(*sname) - 3U));\
		*(p_result) = STBIN_FAILED; }

//Test structure size against computed size
typedef tS8 Teststbin_exec_stop_detection_on_off_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(stbin_exec_stop_detection_on_off_t)-4U)];
typedef tS8 Teststbin_exec_stop_detection_on_off_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+4U-sizeof(stbin_exec_stop_detection_on_off_t))];




//Frame stbin_exec_walking_mode_on_off (cid=0x3A mid=0x14)
#define stbin_exec_walking_mode_on_off_MAP(sname, msg, len, p_result)\
	/*lint -e{9087} cast performed between a pointer to object type and a pointer to a different object type */ \
	stbin_exec_walking_mode_on_off_t *sname = (stbin_exec_walking_mode_on_off_t *)msg;\
	GPS_DEBUG_MSG(("STBIN Received Frame stbin_exec_walking_mode_on_off\r\n"));\
	GPS_DEBUG_MSG(("STBIN on_off=0x%X\r\n", sname->on_off));\
	if(1U < sname->on_off) {\
		GPS_DEBUG_MSG(("STBIN invalid on_off=%d\r\n", sname->on_off));\
		*(p_result) = STBIN_FAILED; }\
	if(len != (sizeof(*sname) - 3U)) {\
		GPS_DEBUG_MSG(("STBIN frame stbin_exec_walking_mode_on_off received with Payload length %d vs %d\r\n", len, sizeof(*sname) - 3U));\
		*(p_result) = STBIN_FAILED; }

//Test structure size against computed size
typedef tS8 Teststbin_exec_walking_mode_on_off_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(stbin_exec_walking_mode_on_off_t)-4U)];
typedef tS8 Teststbin_exec_walking_mode_on_off_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+4U-sizeof(stbin_exec_walking_mode_on_off_t))];




//Frame stbin_exec_rtc_write (cid=0x3A mid=0x18)
#define stbin_exec_rtc_write_MAP(sname, msg, len, p_result)\
	/*lint -e{9087} cast performed between a pointer to object type and a pointer to a different object type */ \
	stbin_exec_rtc_write_t *sname = (stbin_exec_rtc_write_t *)msg;\
	GPS_DEBUG_MSG(("STBIN Received Frame stbin_exec_rtc_write\r\n"));\
	STBIN_FROM_LINK_ENDIAN_CONV_tS32(&(sname->time_delta));\
	GPS_DEBUG_MSG(("STBIN time_delta=%d\r\n", sname->time_delta));\
	if(len != sizeof(*sname)) {\
		GPS_DEBUG_MSG(("STBIN frame stbin_exec_rtc_write received with Payload length %d vs %d\r\n", len, sizeof(*sname) - 0U));\
		*(p_result) = STBIN_FAILED; }

//Test structure size against computed size
typedef tS8 Teststbin_exec_rtc_write_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(stbin_exec_rtc_write_t)-4U)];
typedef tS8 Teststbin_exec_rtc_write_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+4U-sizeof(stbin_exec_rtc_write_t))];




//Frame stbin_exec_fe_write (cid=0x3A mid=0x19)
#define stbin_exec_fe_write_MAP(sname, msg, len, p_result)\
	/*lint -e{9087} cast performed between a pointer to object type and a pointer to a different object type */ \
	stbin_exec_fe_write_t *sname = (stbin_exec_fe_write_t *)msg;\
	GPS_DEBUG_MSG(("STBIN Received Frame stbin_exec_fe_write\r\n"));\
	GPS_DEBUG_MSG(("STBIN addr=0x%X\r\n", sname->addr));\
	if(24U < sname->addr) {\
		GPS_DEBUG_MSG(("STBIN invalid addr=%d\r\n", sname->addr));\
		*(p_result) = STBIN_FAILED; }\
	GPS_DEBUG_MSG(("STBIN data=0x%X\r\n", sname->data));\
	if(255U < sname->data) {\
		GPS_DEBUG_MSG(("STBIN invalid data=%d\r\n", sname->data));\
		*(p_result) = STBIN_FAILED; }\
	if(len != (sizeof(*sname) - 2U)) {\
		GPS_DEBUG_MSG(("STBIN frame stbin_exec_fe_write received with Payload length %d vs %d\r\n", len, sizeof(*sname) - 2U));\
		*(p_result) = STBIN_FAILED; }

//Test structure size against computed size
typedef tS8 Teststbin_exec_fe_write_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(stbin_exec_fe_write_t)-4U)];
typedef tS8 Teststbin_exec_fe_write_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+4U-sizeof(stbin_exec_fe_write_t))];




//Frame stbin_exec_sf_recovery (cid=0x3A mid=0x1A)
#define stbin_exec_sf_recovery_MAP(sname, msg, len, p_result)\
	/*lint -e{9087} cast performed between a pointer to object type and a pointer to a different object type */ \
	stbin_exec_sf_recovery_t *sname = (stbin_exec_sf_recovery_t *)msg;\
	GPS_DEBUG_MSG(("STBIN Received Frame stbin_exec_sf_recovery\r\n"));\
	GPS_DEBUG_MSG(("STBIN on_off=0x%X\r\n", sname->on_off));\
	if(1U < sname->on_off) {\
		GPS_DEBUG_MSG(("STBIN invalid on_off=%d\r\n", sname->on_off));\
		*(p_result) = STBIN_FAILED; }\
	if(len != (sizeof(*sname) - 3U)) {\
		GPS_DEBUG_MSG(("STBIN frame stbin_exec_sf_recovery received with Payload length %d vs %d\r\n", len, sizeof(*sname) - 3U));\
		*(p_result) = STBIN_FAILED; }

//Test structure size against computed size
typedef tS8 Teststbin_exec_sf_recovery_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(stbin_exec_sf_recovery_t)-4U)];
typedef tS8 Teststbin_exec_sf_recovery_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+4U-sizeof(stbin_exec_sf_recovery_t))];




//Frame stbin_exec_adc_start (cid=0x3A mid=0x3)
#define stbin_exec_adc_start_MAP(sname, msg, len, p_result)\
	/*lint -e{9087} cast performed between a pointer to object type and a pointer to a different object type */ \
	stbin_exec_adc_start_t *sname = (stbin_exec_adc_start_t *)msg;\
	GPS_DEBUG_MSG(("STBIN Received Frame stbin_exec_adc_start\r\n"));\
	GPS_DEBUG_MSG(("STBIN sel_line=%d\r\n", sname->sel_line));\
	GPS_DEBUG_MSG(("STBIN adc_functional_mode=0x%X\r\n", sname->adc_functional_mode));\
	if(1U < sname->adc_functional_mode) {\
		GPS_DEBUG_MSG(("STBIN invalid adc_functional_mode=%d\r\n", sname->adc_functional_mode));\
		*(p_result) = STBIN_FAILED; }\
	if(len != (sizeof(*sname) - 2U)) {\
		GPS_DEBUG_MSG(("STBIN frame stbin_exec_adc_start received with Payload length %d vs %d\r\n", len, sizeof(*sname) - 2U));\
		*(p_result) = STBIN_FAILED; }

//Test structure size against computed size
typedef tS8 Teststbin_exec_adc_start_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(stbin_exec_adc_start_t)-4U)];
typedef tS8 Teststbin_exec_adc_start_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+4U-sizeof(stbin_exec_adc_start_t))];




//Frame stbin_exec_lowpower_onoff (cid=0x3A mid=0x20)
#define stbin_exec_lowpower_onoff_MAP(sname, msg, len, p_result)\
	/*lint -e{9087} cast performed between a pointer to object type and a pointer to a different object type */ \
	stbin_exec_lowpower_onoff_t *sname = (stbin_exec_lowpower_onoff_t *)msg;\
	GPS_DEBUG_MSG(("STBIN Received Frame stbin_exec_lowpower_onoff\r\n"));\
	STBIN_FROM_LINK_ENDIAN_CONV_tU32(&(sname->fix_period));\
	GPS_DEBUG_MSG(("STBIN fix_period=%d\r\n", sname->fix_period));\
	STBIN_FROM_LINK_ENDIAN_CONV_tU16(&(sname->ms_off));\
	GPS_DEBUG_MSG(("STBIN ms_off=%d\r\n", sname->ms_off));\
	STBIN_FROM_LINK_ENDIAN_CONV_tU16(&(sname->fix_on_time));\
	GPS_DEBUG_MSG(("STBIN fix_on_time=%d\r\n", sname->fix_on_time));\
	STBIN_FROM_LINK_ENDIAN_CONV_tU16(&(sname->NoFixTimeout));\
	GPS_DEBUG_MSG(("STBIN NoFixTimeout=%d\r\n", sname->NoFixTimeout));\
	STBIN_FROM_LINK_ENDIAN_CONV_tU16(&(sname->NoFixOffTime));\
	GPS_DEBUG_MSG(("STBIN NoFixOffTime=%d\r\n", sname->NoFixOffTime));\
	GPS_DEBUG_MSG(("STBIN on_off=%d\r\n", sname->on_off));\
	GPS_DEBUG_MSG(("STBIN reduced_type=%d\r\n", sname->reduced_type));\
	GPS_DEBUG_MSG(("STBIN duty_cycle_on_off=%d\r\n", sname->duty_cycle_on_off));\
	GPS_DEBUG_MSG(("STBIN const_type=%d\r\n", sname->const_type));\
	GPS_DEBUG_MSG(("STBIN ehpe_threshold=%d\r\n", sname->ehpe_threshold));\
	GPS_DEBUG_MSG(("STBIN N_sats_reduced=%d\r\n", sname->N_sats_reduced));\
	GPS_DEBUG_MSG(("STBIN periodic_mode=%d\r\n", sname->periodic_mode));\
	GPS_DEBUG_MSG(("STBIN EPH_refresh=%d\r\n", sname->EPH_refresh));\
	GPS_DEBUG_MSG(("STBIN RTC_refresh=%d\r\n", sname->RTC_refresh));\
	if(len != (sizeof(*sname) - 3U)) {\
		GPS_DEBUG_MSG(("STBIN frame stbin_exec_lowpower_onoff received with Payload length %d vs %d\r\n", len, sizeof(*sname) - 3U));\
		*(p_result) = STBIN_FAILED; }

//Test structure size against computed size
typedef tS8 Teststbin_exec_lowpower_onoff_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(stbin_exec_lowpower_onoff_t)-24U)];
typedef tS8 Teststbin_exec_lowpower_onoff_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+24U-sizeof(stbin_exec_lowpower_onoff_t))];


//Section : Customer Flash Storage Write Requests (ClassId 0x3B)


//Frame stbin_exec_sqi_data_set (cid=0x3B mid=0x39)
#define stbin_exec_sqi_data_set_MAP(sname, msg, len, p_result)\
	/*lint -e{9087} cast performed between a pointer to object type and a pointer to a different object type */ \
	stbin_exec_sqi_data_set_t *sname = (stbin_exec_sqi_data_set_t *)msg;\
	GPS_DEBUG_MSG(("STBIN Received Frame stbin_exec_sqi_data_set\r\n"));\
	STBIN_FROM_LINK_ENDIAN_CONV_tU32(&(sname->word1));\
	GPS_DEBUG_MSG(("STBIN word1=%d\r\n", sname->word1));\
	STBIN_FROM_LINK_ENDIAN_CONV_tU32(&(sname->word2));\
	GPS_DEBUG_MSG(("STBIN word2=%d\r\n", sname->word2));\
	STBIN_FROM_LINK_ENDIAN_CONV_tU32(&(sname->word3));\
	GPS_DEBUG_MSG(("STBIN word3=%d\r\n", sname->word3));\
	STBIN_FROM_LINK_ENDIAN_CONV_tU32(&(sname->word4));\
	GPS_DEBUG_MSG(("STBIN word4=%d\r\n", sname->word4));\
	STBIN_FROM_LINK_ENDIAN_CONV_tU32(&(sname->word5));\
	GPS_DEBUG_MSG(("STBIN word5=%d\r\n", sname->word5));\
	STBIN_FROM_LINK_ENDIAN_CONV_tU32(&(sname->word6));\
	GPS_DEBUG_MSG(("STBIN word6=%d\r\n", sname->word6));\
	STBIN_FROM_LINK_ENDIAN_CONV_tU32(&(sname->word7));\
	GPS_DEBUG_MSG(("STBIN word7=%d\r\n", sname->word7));\
	STBIN_FROM_LINK_ENDIAN_CONV_tU32(&(sname->word8));\
	GPS_DEBUG_MSG(("STBIN word8=%d\r\n", sname->word8));\
	STBIN_FROM_LINK_ENDIAN_CONV_tU16(&(sname->offset));\
	GPS_DEBUG_MSG(("STBIN offset=0x%X\r\n", sname->offset));\
	if(65504U < sname->offset) {\
		GPS_DEBUG_MSG(("STBIN invalid offset=%d\r\n", sname->offset));\
		*(p_result) = STBIN_FAILED; }\
	if(len != (sizeof(*sname) - 2U)) {\
		GPS_DEBUG_MSG(("STBIN frame stbin_exec_sqi_data_set received with Payload length %d vs %d\r\n", len, sizeof(*sname) - 2U));\
		*(p_result) = STBIN_FAILED; }

//Test structure size against computed size
typedef tS8 Teststbin_exec_sqi_data_set_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(stbin_exec_sqi_data_set_t)-36U)];
typedef tS8 Teststbin_exec_sqi_data_set_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+36U-sizeof(stbin_exec_sqi_data_set_t))];




//Frame stbin_exec_sqi_data_erase (cid=0x3B mid=0x38)
#define stbin_exec_sqi_data_erase_MAP(sname, msg, len, p_result)\
	GPS_DEBUG_MSG(("STBIN Received Frame stbin_exec_sqi_data_erase\r\n"));\
	if(len != 0U) {\
		GPS_DEBUG_MSG(("STBIN Dataless frame stbin_exec_sqi_data_erase received with Payload length %d\r\n", len));\
		*(p_result) = STBIN_FAILED; }

//Section : Output Messages Request (ClassId 0x01)
//Section : Error Messages (ClassId 0x00)
//Section : Output Messages (ClassId 0x01)
//Send helper
#define outprocess_ecef_send(buff, frameQ) {\
	 outprocess_ecef_t *__msg = buff; \
	STBIN_TO_LINK_ENDIAN_CONV_double(&((__msg)->ecefZ)); \
	STBIN_TO_LINK_ENDIAN_CONV_double(&((__msg)->ecefY)); \
	STBIN_TO_LINK_ENDIAN_CONV_double(&((__msg)->ecefX)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->pAcc)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->iTOW)); \
	_stbin_msg_send((tUChar *)(__msg), \
				outprocess_ecef_t_size_send, \
				frameQ); \
	}

//Test structure size against computed size
typedef tS8 Testoutprocess_ecef_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(outprocess_ecef_t)-32U)];
typedef tS8 Testoutprocess_ecef_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+32U-sizeof(outprocess_ecef_t))];


//Send helper
#define outProcess_pos_llh_send(buff, frameQ) {\
	 outProcess_pos_llh_t *__msg = buff; \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->vAcc)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->hAcc)); \
	STBIN_TO_LINK_ENDIAN_CONV_tS32(&((__msg)->rms_pos_res)); \
	STBIN_TO_LINK_ENDIAN_CONV_tS32(&((__msg)->hMSL)); \
	STBIN_TO_LINK_ENDIAN_CONV_tS32(&((__msg)->height)); \
	STBIN_TO_LINK_ENDIAN_CONV_tS32(&((__msg)->lat)); \
	STBIN_TO_LINK_ENDIAN_CONV_tS32(&((__msg)->lon)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->iTOW)); \
	_stbin_msg_send((tUChar *)(__msg), \
				outProcess_pos_llh_t_size_send, \
				frameQ); \
	}

//Test structure size against computed size
typedef tS8 TestoutProcess_pos_llh_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(outProcess_pos_llh_t)-32U)];
typedef tS8 TestoutProcess_pos_llh_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+32U-sizeof(outProcess_pos_llh_t))];


//Send helper
#define outputprocess_status_send(buff, frameQ) {\
	 outputprocess_status_t *__msg = buff; \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->msss)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->ttff_ms)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->iTOW)); \
	_stbin_msg_send((tUChar *)(__msg), \
				outputprocess_status_t_size_send, \
				frameQ); \
	}

//Test structure size against computed size
typedef tS8 Testoutputprocess_status_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(outputprocess_status_t)-16U)];
typedef tS8 Testoutputprocess_status_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+16U-sizeof(outputprocess_status_t))];


//Send helper
#define outputprocess_dop_send(buff, frameQ) {\
	 outputprocess_dop_t *__msg = buff; \
	STBIN_TO_LINK_ENDIAN_CONV_tU16(&((__msg)->hDOP)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU16(&((__msg)->vDOP)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU16(&((__msg)->tDOP)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU16(&((__msg)->pDOP)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU16(&((__msg)->gDOP)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->iTOW)); \
	_stbin_msg_send((tUChar *)(__msg), \
				outputprocess_dop_t_size_send, \
				frameQ); \
	}

//Test structure size against computed size
typedef tS8 Testoutputprocess_dop_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(outputprocess_dop_t)-16U)];
typedef tS8 Testoutputprocess_dop_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+16U-sizeof(outputprocess_dop_t))];


//Send helper
#define outputprocess_velecef_send(buff, frameQ) {\
	 outputprocess_velecef_t *__msg = buff; \
	STBIN_TO_LINK_ENDIAN_CONV_tS32(&((__msg)->sAcc)); \
	STBIN_TO_LINK_ENDIAN_CONV_tS32(&((__msg)->ecefVZ)); \
	STBIN_TO_LINK_ENDIAN_CONV_tS32(&((__msg)->ecefVY)); \
	STBIN_TO_LINK_ENDIAN_CONV_tS32(&((__msg)->ecefVX)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->iTOW)); \
	_stbin_msg_send((tUChar *)(__msg), \
				outputprocess_velecef_t_size_send, \
				frameQ); \
	}

//Test structure size against computed size
typedef tS8 Testoutputprocess_velecef_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(outputprocess_velecef_t)-20U)];
typedef tS8 Testoutputprocess_velecef_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+20U-sizeof(outputprocess_velecef_t))];


//Send helper
#define outputprocess_velneu_send(buff, frameQ) {\
	 outputprocess_velneu_t *__msg = buff; \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->cAcc)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->sAcc)); \
	STBIN_TO_LINK_ENDIAN_CONV_tS32(&((__msg)->rms_vel_res)); \
	STBIN_TO_LINK_ENDIAN_CONV_tS32(&((__msg)->heading)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->gSpeed)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->speed)); \
	STBIN_TO_LINK_ENDIAN_CONV_tS32(&((__msg)->velU)); \
	STBIN_TO_LINK_ENDIAN_CONV_tS32(&((__msg)->velE)); \
	STBIN_TO_LINK_ENDIAN_CONV_tS32(&((__msg)->velN)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->iTOW)); \
	_stbin_msg_send((tUChar *)(__msg), \
				outputprocess_velneu_t_size_send, \
				frameQ); \
	}

//Test structure size against computed size
typedef tS8 Testoutputprocess_velneu_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(outputprocess_velneu_t)-40U)];
typedef tS8 Testoutputprocess_velneu_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+40U-sizeof(outputprocess_velneu_t))];


//Send helper
#define outputprocess_timegnss_send(buff, frameQ) {\
	 outputprocess_timegnss_t *__msg = buff; \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->tAcc)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU16(&((__msg)->week)); \
	STBIN_TO_LINK_ENDIAN_CONV_tS32(&((__msg)->fTOW)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->iTOW)); \
	_stbin_msg_send((tUChar *)(__msg), \
				outputprocess_timegnss_t_size_send, \
				frameQ); \
	}

//Test structure size against computed size
typedef tS8 Testoutputprocess_timegnss_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(outputprocess_timegnss_t)-16U)];
typedef tS8 Testoutputprocess_timegnss_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+16U-sizeof(outputprocess_timegnss_t))];


//Send helper
#define outputprocess_timeutc_send(buff, frameQ) {\
	 outputprocess_timeutc_t *__msg = buff; \
	STBIN_TO_LINK_ENDIAN_CONV_tU16(&((__msg)->year)); \
	STBIN_TO_LINK_ENDIAN_CONV_tS32(&((__msg)->nano)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->tAcc)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->iTOW)); \
	_stbin_msg_send((tUChar *)(__msg), \
				outputprocess_timeutc_t_size_send, \
				frameQ); \
	}

//Test structure size against computed size
typedef tS8 Testoutputprocess_timeutc_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(outputprocess_timeutc_t)-20U)];
typedef tS8 Testoutputprocess_timeutc_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+20U-sizeof(outputprocess_timeutc_t))];


//Send helper
#define outputprocess_svinfo_send(buff, frameQ) {\
	 outputprocess_svinfo_t *__msg = buff; \
	STBIN_TO_LINK_ENDIAN_CONV_tU16(&((__msg)->azim)); \
	_stbin_msg_send((tUChar *)(__msg), \
				outputprocess_svinfo_t_size_send, \
				frameQ); \
	}

//Test structure size against computed size
typedef tS8 Testoutputprocess_svinfo_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(outputprocess_svinfo_t)-8U)];
typedef tS8 Testoutputprocess_svinfo_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+8U-sizeof(outputprocess_svinfo_t))];


//Send helper
#define outputprocess_dgps_send(buff, frameQ) {\
	 outputprocess_dgps_t *__msg = buff; \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->baseId)); \
	STBIN_TO_LINK_ENDIAN_CONV_tS32(&((__msg)->age)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->iTOW)); \
	_stbin_msg_send((tUChar *)(__msg), \
				outputprocess_dgps_t_size_send, \
				frameQ); \
	}

//Test structure size against computed size
typedef tS8 Testoutputprocess_dgps_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(outputprocess_dgps_t)-16U)];
typedef tS8 Testoutputprocess_dgps_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+16U-sizeof(outputprocess_dgps_t))];


//Send helper
#define outputprocess_dgps_data_send(buff, frameQ) {\
	 outputprocess_dgps_data_t *__msg = buff; \
	STBIN_TO_LINK_ENDIAN_CONV_tS32(&((__msg)->prrc)); \
	STBIN_TO_LINK_ENDIAN_CONV_tS32(&((__msg)->prc)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU16(&((__msg)->ageC)); \
	_stbin_msg_send((tUChar *)(__msg), \
				outputprocess_dgps_data_t_size_send, \
				frameQ); \
	}

//Test structure size against computed size
typedef tS8 Testoutputprocess_dgps_data_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(outputprocess_dgps_data_t)-12U)];
typedef tS8 Testoutputprocess_dgps_data_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+12U-sizeof(outputprocess_dgps_data_t))];


//Send helper
#define outputprocess_ts_send(buff, frameQ) {\
	 outputprocess_ts_t *__msg = buff; \
	STBIN_TO_LINK_ENDIAN_CONV_tS32(&((__msg)->diff_range_rate_corr)); \
	STBIN_TO_LINK_ENDIAN_CONV_tS32(&((__msg)->diff_range_corr)); \
	STBIN_TO_LINK_ENDIAN_CONV_tS32(&((__msg)->sat_atmos_corr)); \
	STBIN_TO_LINK_ENDIAN_CONV_tS32(&((__msg)->sat_range_corr)); \
	STBIN_TO_LINK_ENDIAN_CONV_tS32(&((__msg)->sat_vel_z)); \
	STBIN_TO_LINK_ENDIAN_CONV_tS32(&((__msg)->sat_vel_y)); \
	STBIN_TO_LINK_ENDIAN_CONV_tS32(&((__msg)->sat_vel_x)); \
	STBIN_TO_LINK_ENDIAN_CONV_tS32(&((__msg)->sat_pos_z)); \
	STBIN_TO_LINK_ENDIAN_CONV_tS32(&((__msg)->sat_pos_y)); \
	STBIN_TO_LINK_ENDIAN_CONV_tS32(&((__msg)->sat_pos_x)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->dsp_tracked_time)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->dsp_signal_strength)); \
	STBIN_TO_LINK_ENDIAN_CONV_double(&((__msg)->dsp_pseudorange)); \
	STBIN_TO_LINK_ENDIAN_CONV_tS32(&((__msg)->dsp_frequency)); \
	_stbin_msg_send((tUChar *)(__msg), \
				outputprocess_ts_t_size_send, \
				frameQ); \
	}

//Test structure size against computed size
typedef tS8 Testoutputprocess_ts_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(outputprocess_ts_t)-72U)];
typedef tS8 Testoutputprocess_ts_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+72U-sizeof(outputprocess_ts_t))];


//Send helper
#define outputprocess_tg_send(buff, frameQ) {\
	 outputprocess_tg_t *__msg = buff; \
	STBIN_TO_LINK_ENDIAN_CONV_tS32(&((__msg)->nco)); \
	STBIN_TO_LINK_ENDIAN_CONV_tS16(&((__msg)->week)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->cpuTime)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->iTOW)); \
	_stbin_msg_send((tUChar *)(__msg), \
				outputprocess_tg_t_size_send, \
				frameQ); \
	}

//Test structure size against computed size
typedef tS8 Testoutputprocess_tg_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(outputprocess_tg_t)-16U)];
typedef tS8 Testoutputprocess_tg_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+16U-sizeof(outputprocess_tg_t))];


//Send helper
#define outputprocess_Pos_Algo_send(buff, frameQ) {\
	 outputprocess_Pos_Algo_t *__msg = buff; \
	STBIN_TO_LINK_ENDIAN_CONV_tS32(&((__msg)->stoppedDuration)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->iTOW)); \
	_stbin_msg_send((tUChar *)(__msg), \
				outputprocess_Pos_Algo_t_size_send, \
				frameQ); \
	}

//Test structure size against computed size
typedef tS8 Testoutputprocess_Pos_Algo_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(outputprocess_Pos_Algo_t)-12U)];
typedef tS8 Testoutputprocess_Pos_Algo_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+12U-sizeof(outputprocess_Pos_Algo_t))];


//Send helper
#define outputprocess_RF_send(buff, frameQ) {\
	 outputprocess_RF_t *__msg = buff; \
	STBIN_TO_LINK_ENDIAN_CONV_tS32(&((__msg)->dsp_frequency)); \
	STBIN_TO_LINK_ENDIAN_CONV_tS32(&((__msg)->ave_phase_noise)); \
	_stbin_msg_send((tUChar *)(__msg), \
				outputprocess_RF_t_size_send, \
				frameQ); \
	}

//Test structure size against computed size
typedef tS8 Testoutputprocess_RF_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(outputprocess_RF_t)-12U)];
typedef tS8 Testoutputprocess_RF_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+12U-sizeof(outputprocess_RF_t))];


//Send helper
#define outputprocess_Cov_send(buff, frameQ) {\
	 outputprocess_Cov_t *__msg = buff; \
	STBIN_TO_LINK_ENDIAN_CONV_tU16(&((__msg)->Vel_V_cov)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU16(&((__msg)->Vel_E_cov)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU16(&((__msg)->Vel_N_cov)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU16(&((__msg)->Vel_H_cov)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU16(&((__msg)->Pos_V_cov)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU16(&((__msg)->Pos_E_cov)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU16(&((__msg)->Pos_N_cov)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU16(&((__msg)->Pos_H_cov)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->iTOW)); \
	_stbin_msg_send((tUChar *)(__msg), \
				outputprocess_Cov_t_size_send, \
				frameQ); \
	}

//Test structure size against computed size
typedef tS8 Testoutputprocess_Cov_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(outputprocess_Cov_t)-20U)];
typedef tS8 Testoutputprocess_Cov_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+20U-sizeof(outputprocess_Cov_t))];


//Send helper
#define outputprocess_GST_send(buff, frameQ) {\
	 outputprocess_GST_t *__msg = buff; \
	STBIN_TO_LINK_ENDIAN_CONV_tU16(&((__msg)->alt_err_dev)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU16(&((__msg)->lon_err_dev)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU16(&((__msg)->lat_err_dev)); \
	STBIN_TO_LINK_ENDIAN_CONV_tS16(&((__msg)->angle)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU16(&((__msg)->minor_axis)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU16(&((__msg)->major_axis)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU16(&((__msg)->ehpe)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU16(&((__msg)->msec)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->iTOW)); \
	_stbin_msg_send((tUChar *)(__msg), \
				outputprocess_GST_t_size_send, \
				frameQ); \
	}

//Test structure size against computed size
typedef tS8 Testoutputprocess_GST_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(outputprocess_GST_t)-24U)];
typedef tS8 Testoutputprocess_GST_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+24U-sizeof(outputprocess_GST_t))];


//Send helper
#define outputprocess_PPSData_send(buff, frameQ) {\
	 outputprocess_PPSData_t *__msg = buff; \
	STBIN_TO_LINK_ENDIAN_CONV_tU16(&((__msg)->quantErr)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->gpsUtcDelta_ns)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->glonassUtcDelta_ns)); \
	STBIN_TO_LINK_ENDIAN_CONV_double(&((__msg)->tcxoClockFreq)); \
	STBIN_TO_LINK_ENDIAN_CONV_double(&((__msg)->ppsClockFreq)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->constellationMask)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU16(&((__msg)->glonassRfDelay)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU16(&((__msg)->gpsRfDelay)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU16(&((__msg)->pulseDelay)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU16(&((__msg)->pulseDuration)); \
	_stbin_msg_send((tUChar *)(__msg), \
				outputprocess_PPSData_t_size_send, \
				frameQ); \
	}

//Test structure size against computed size
typedef tS8 Testoutputprocess_PPSData_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(outputprocess_PPSData_t)-56U)];
typedef tS8 Testoutputprocess_PPSData_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+56U-sizeof(outputprocess_PPSData_t))];


//Send helper
#define outputprocess_HoldData_send(buff, frameQ) {\
	 outputprocess_HoldData_t *__msg = buff; \
	STBIN_TO_LINK_ENDIAN_CONV_tS32(&((__msg)->height)); \
	STBIN_TO_LINK_ENDIAN_CONV_tS32(&((__msg)->lon_val)); \
	STBIN_TO_LINK_ENDIAN_CONV_tS32(&((__msg)->lat_val)); \
	_stbin_msg_send((tUChar *)(__msg), \
				outputprocess_HoldData_t_size_send, \
				frameQ); \
	}

//Test structure size against computed size
typedef tS8 Testoutputprocess_HoldData_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(outputprocess_HoldData_t)-16U)];
typedef tS8 Testoutputprocess_HoldData_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+16U-sizeof(outputprocess_HoldData_t))];


//Send helper
#define outputprocess_TraimData_send(buff, frameQ) {\
	 outputprocess_TraimData_t *__msg = buff; \
	STBIN_TO_LINK_ENDIAN_CONV_tU16(&((__msg)->alarm)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->ave_error)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU16_ARRAY(&((__msg)->residual_tab), 24); \
	_stbin_msg_send((tUChar *)(__msg), \
				outputprocess_TraimData_t_size_send, \
				frameQ); \
	}

//Test structure size against computed size
typedef tS8 Testoutputprocess_TraimData_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(outputprocess_TraimData_t)-108U)];
typedef tS8 Testoutputprocess_TraimData_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+108U-sizeof(outputprocess_TraimData_t))];


//Send helper
#define outputprocess_lowpowerData_send(buff, frameQ) {\
	 outputprocess_lowpowerData_t *__msg = buff; \
	STBIN_TO_LINK_ENDIAN_CONV_tS32(&((__msg)->eng8)); \
	STBIN_TO_LINK_ENDIAN_CONV_tS16(&((__msg)->eng5)); \
	STBIN_TO_LINK_ENDIAN_CONV_tS16(&((__msg)->eng4)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU16(&((__msg)->ehpe_average)); \
	STBIN_TO_LINK_ENDIAN_CONV_tS16(&((__msg)->eng3)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU16(&((__msg)->ehpe)); \
	STBIN_TO_LINK_ENDIAN_CONV_tS16(&((__msg)->eng2)); \
	STBIN_TO_LINK_ENDIAN_CONV_tS16(&((__msg)->eng1)); \
	_stbin_msg_send((tUChar *)(__msg), \
				outputprocess_lowpowerData_t_size_send, \
				frameQ); \
	}

//Test structure size against computed size
typedef tS8 Testoutputprocess_lowpowerData_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(outputprocess_lowpowerData_t)-28U)];
typedef tS8 Testoutputprocess_lowpowerData_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+28U-sizeof(outputprocess_lowpowerData_t))];


//Send helper
#define outputprocess_cpuData_send(buff, frameQ) {\
	 outputprocess_cpuData_t *__msg = buff; \
	STBIN_TO_LINK_ENDIAN_CONV_tU16(&((__msg)->cpu_freq)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU16(&((__msg)->cpu_usage)); \
	_stbin_msg_send((tUChar *)(__msg), \
				outputprocess_cpuData_t_size_send, \
				frameQ); \
	}

//Test structure size against computed size
typedef tS8 Testoutputprocess_cpuData_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(outputprocess_cpuData_t)-6U)];
typedef tS8 Testoutputprocess_cpuData_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+6U-sizeof(outputprocess_cpuData_t))];


//Send helper
#define outprocess_test_rf_send(buff, frameQ) {\
	 outprocess_test_rf_t *__msg = buff; \
	STBIN_TO_LINK_ENDIAN_CONV_tS32(&((__msg)->phase_noise)); \
	STBIN_TO_LINK_ENDIAN_CONV_tS32(&((__msg)->frequency)); \
	_stbin_msg_send((tUChar *)(__msg), \
				outprocess_test_rf_t_size_send, \
				frameQ); \
	}

//Test structure size against computed size
typedef tS8 Testoutprocess_test_rf_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(outprocess_test_rf_t)-12U)];
typedef tS8 Testoutprocess_test_rf_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+12U-sizeof(outprocess_test_rf_t))];


//Send helper
#define outputprocess_posres_send(buff, frameQ) {\
	 outputprocess_posres_t *__msg = buff; \
	STBIN_TO_LINK_ENDIAN_CONV_tU16(&((__msg)->rmsRes)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU16_ARRAY(&((__msg)->posRes), 24); \
	_stbin_msg_send((tUChar *)(__msg), \
				outputprocess_posres_t_size_send, \
				frameQ); \
	}

//Test structure size against computed size
typedef tS8 Testoutputprocess_posres_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(outputprocess_posres_t)-52U)];
typedef tS8 Testoutputprocess_posres_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+52U-sizeof(outputprocess_posres_t))];


//Send helper
#define outputprocess_velres_send(buff, frameQ) {\
	 outputprocess_velres_t *__msg = buff; \
	STBIN_TO_LINK_ENDIAN_CONV_tU16(&((__msg)->rmsRes)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU16_ARRAY(&((__msg)->velRes), 24); \
	_stbin_msg_send((tUChar *)(__msg), \
				outputprocess_velres_t_size_send, \
				frameQ); \
	}

//Test structure size against computed size
typedef tS8 Testoutputprocess_velres_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(outputprocess_velres_t)-52U)];
typedef tS8 Testoutputprocess_velres_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+52U-sizeof(outputprocess_velres_t))];


//Send helper
#define outputprocess_notch_filter_status_send(buff, frameQ) {\
	 outputprocess_notch_filter_status_t *__msg = buff; \
	STBIN_TO_LINK_ENDIAN_CONV_tU16(&((__msg)->pwr_gln)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU16(&((__msg)->pwr_gps)); \
	STBIN_TO_LINK_ENDIAN_CONV_tS32(&((__msg)->kfreq_now_gln)); \
	STBIN_TO_LINK_ENDIAN_CONV_tS32(&((__msg)->kfreq_now_gps)); \
	_stbin_msg_send((tUChar *)(__msg), \
				outputprocess_notch_filter_status_t_size_send, \
				frameQ); \
	}

//Test structure size against computed size
typedef tS8 Testoutputprocess_notch_filter_status_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(outputprocess_notch_filter_status_t)-16U)];
typedef tS8 Testoutputprocess_notch_filter_status_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+16U-sizeof(outputprocess_notch_filter_status_t))];


//Send helper
#define outputprocess_read_errors_send(buff, frameQ) {\
	 outputprocess_read_errors_t *__msg = buff; \
        STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->param6)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->param5)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->param4)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->param3)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->param2)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->param1)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->error_code)); \
	_stbin_msg_send((tUChar *)(__msg), \
				outputprocess_read_errors_t_size_send, \
				frameQ); \
	}

//Test structure size against computed size
typedef tS8 Testoutputprocess_read_errors_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(outputprocess_read_errors_t)-28U)];
typedef tS8 Testoutputprocess_read_errors_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+28U-sizeof(outputprocess_read_errors_t))];


//Section : Test Response Messages (ClassId 0x4A)
//Send helper
#define stbin_exec_test_rtc_err_rsp_send(buff, frameQ) {\
	 stbin_exec_test_rtc_err_rsp_t *__msg = buff; \
	STBIN_TO_LINK_ENDIAN_CONV_tU16(&((__msg)->week)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->tow)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->accuracy)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->error)); \
	_stbin_msg_send((tUChar *)(__msg), \
				stbin_exec_test_rtc_err_rsp_t_size_send, \
				frameQ); \
	}

//Test structure size against computed size
typedef tS8 Teststbin_exec_test_rtc_err_rsp_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(stbin_exec_test_rtc_err_rsp_t)-16U)];
typedef tS8 Teststbin_exec_test_rtc_err_rsp_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+16U-sizeof(stbin_exec_test_rtc_err_rsp_t))];


//Section : Initialization Messages Responses (ClassId 0x20)
//Section : Control Messages Responses (ClassId 0x12)
//Section : Read \PPSText Response Messages (ClassId 0x2D)
//Send helper
#define stbin_exec_pps_if_pulse_data_read_rsp_send(buff, frameQ) {\
	 stbin_exec_pps_if_pulse_data_read_rsp_t *__msg = buff; \
	STBIN_TO_LINK_ENDIAN_CONV_tU16(&((__msg)->pulsePolarity)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU16(&((__msg)->pulseDuration)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU16(&((__msg)->pulseDelay)); \
	_stbin_msg_send((tUChar *)(__msg), \
				stbin_exec_pps_if_pulse_data_read_rsp_t_size_send, \
				frameQ); \
	}

//Test structure size against computed size
typedef tS8 Teststbin_exec_pps_if_pulse_data_read_rsp_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(stbin_exec_pps_if_pulse_data_read_rsp_t)-8U)];
typedef tS8 Teststbin_exec_pps_if_pulse_data_read_rsp_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+8U-sizeof(stbin_exec_pps_if_pulse_data_read_rsp_t))];


//Send helper
#define stbin_exec_pps_if_timing_data_read_rsp_send(buff, frameQ) {\
	 stbin_exec_pps_if_timing_data_read_rsp_t *__msg = buff; \
	STBIN_TO_LINK_ENDIAN_CONV_tU16(&((__msg)->glonassRfDelay)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU16(&((__msg)->gpsRfDelay)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->constellationMask)); \
	_stbin_msg_send((tUChar *)(__msg), \
				stbin_exec_pps_if_timing_data_read_rsp_t_size_send, \
				frameQ); \
	}

//Test structure size against computed size
typedef tS8 Teststbin_exec_pps_if_timing_data_read_rsp_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(stbin_exec_pps_if_timing_data_read_rsp_t)-12U)];
typedef tS8 Teststbin_exec_pps_if_timing_data_read_rsp_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+12U-sizeof(stbin_exec_pps_if_timing_data_read_rsp_t))];


//Send helper
#define stbin_exec_pps_if_pos_hold_data_read_rsp_send(buff, frameQ) {\
	 stbin_exec_pps_if_pos_hold_data_read_rsp_t *__msg = buff; \
	STBIN_TO_LINK_ENDIAN_CONV_tS32(&((__msg)->height)); \
	STBIN_TO_LINK_ENDIAN_CONV_tS32(&((__msg)->lon_val)); \
	STBIN_TO_LINK_ENDIAN_CONV_tS32(&((__msg)->lat_val)); \
	_stbin_msg_send((tUChar *)(__msg), \
				stbin_exec_pps_if_pos_hold_data_read_rsp_t_size_send, \
				frameQ); \
	}

//Test structure size against computed size
typedef tS8 Teststbin_exec_pps_if_pos_hold_data_read_rsp_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(stbin_exec_pps_if_pos_hold_data_read_rsp_t)-16U)];
typedef tS8 Teststbin_exec_pps_if_pos_hold_data_read_rsp_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+16U-sizeof(stbin_exec_pps_if_pos_hold_data_read_rsp_t))];


//Send helper
#define stbin_exec_pps_if_traim_read_rsp_send(buff, frameQ) {\
	 stbin_exec_pps_if_traim_read_rsp_t *__msg = buff; \
	STBIN_TO_LINK_ENDIAN_CONV_tU16_ARRAY(&((__msg)->residual_tab), 24); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->ave_error)); \
	_stbin_msg_send((tUChar *)(__msg), \
				stbin_exec_pps_if_traim_read_rsp_t_size_send, \
				frameQ); \
	}

//Test structure size against computed size
typedef tS8 Teststbin_exec_pps_if_traim_read_rsp_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(stbin_exec_pps_if_traim_read_rsp_t)-104U)];
typedef tS8 Teststbin_exec_pps_if_traim_read_rsp_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+104U-sizeof(stbin_exec_pps_if_traim_read_rsp_t))];


//Section : Write \PPSText Response Messages (ClassId 0x3D)
//Section : Read Messages Responses (ClassId 0x2A)
//Send helper
#define dumpEphe_send(buff, frameQ) {\
	 dumpEphe_t *__msg = buff; \
	_stbin_msg_send((tUChar *)(__msg), \
				dumpEphe_t_size_send, \
				frameQ); \
	}

//Test structure size against computed size
typedef tS8 TestdumpEphe_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(dumpEphe_t)-68U)];
typedef tS8 TestdumpEphe_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+68U-sizeof(dumpEphe_t))];


//Send helper
#define dumpAlmans_send(buff, frameQ) {\
	 dumpAlmans_t *__msg = buff; \
	_stbin_msg_send((tUChar *)(__msg), \
				dumpAlmans_t_size_send, \
				frameQ); \
	}

//Test structure size against computed size
typedef tS8 TestdumpAlmans_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(dumpAlmans_t)-44U)];
typedef tS8 TestdumpAlmans_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+44U-sizeof(dumpAlmans_t))];


//Send helper
#define getSwVers_send(buff, frameQ) {\
	 getSwVers_t *__msg = buff; \
	_stbin_msg_send((tUChar *)(__msg), \
				getSwVers_t_size_send, \
				frameQ); \
	}

//Test structure size against computed size
typedef tS8 TestgetSwVers_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(getSwVers_t)-24U)];
typedef tS8 TestgetSwVers_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+24U-sizeof(getSwVers_t))];


//Send helper
#define checkTask_send(buff, frameQ) {\
	 checkTask_t *__msg = buff; \
	STBIN_TO_LINK_ENDIAN_CONV_tS32(&((__msg)->used)); \
	STBIN_TO_LINK_ENDIAN_CONV_tS32(&((__msg)->size)); \
	STBIN_TO_LINK_ENDIAN_CONV_tS32(&((__msg)->task_get_stack_ptr)); \
	STBIN_TO_LINK_ENDIAN_CONV_tS32(&((__msg)->task_get_stack_base)); \
	STBIN_TO_LINK_ENDIAN_CONV_tS32(&((__msg)->task_get_priority)); \
	_stbin_msg_send((tUChar *)(__msg), \
				checkTask_t_size_send, \
				frameQ); \
	}

//Test structure size against computed size
typedef tS8 TestcheckTask_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(checkTask_t)-44U)];
typedef tS8 TestcheckTask_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+44U-sizeof(checkTask_t))];


//Send helper
#define checkCpuUsage_send(buff, frameQ) {\
	 checkCpuUsage_t *__msg = buff; \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->cpuUsage_CurrentTask)); \
	_stbin_msg_send((tUChar *)(__msg), \
				checkCpuUsage_t_size_send, \
				frameQ); \
	}

//Test structure size against computed size
typedef tS8 TestcheckCpuUsage_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(checkCpuUsage_t)-28U)];
typedef tS8 TestcheckCpuUsage_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+28U-sizeof(checkCpuUsage_t))];


//Send helper
#define check_heap_send(buff, frameQ) {\
	 check_heap_t *__msg = buff; \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->memory_getheapfree)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->memory_getheapsize)); \
	_stbin_msg_send((tUChar *)(__msg), \
				check_heap_t_size_send, \
				frameQ); \
	}

//Test structure size against computed size
typedef tS8 Testcheck_heap_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(check_heap_t)-8U)];
typedef tS8 Testcheck_heap_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+8U-sizeof(check_heap_t))];


//Send helper
#define read_rtc_time_send(buff, frameQ) {\
	 read_rtc_time_t *__msg = buff; \
	STBIN_TO_LINK_ENDIAN_CONV_tU16(&((__msg)->year)); \
	_stbin_msg_send((tUChar *)(__msg), \
				read_rtc_time_t_size_send, \
				frameQ); \
	}

//Test structure size against computed size
typedef tS8 Testread_rtc_time_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(read_rtc_time_t)-12U)];
typedef tS8 Testread_rtc_time_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+12U-sizeof(read_rtc_time_t))];


//Send helper
#define sw_config_get_par_val_Char_send(buff, frameQ) {\
	 sw_config_get_par_val_Char_t *__msg = buff; \
	_stbin_msg_send((tUChar *)(__msg), \
				sw_config_get_par_val_Char_t_size_send, \
				frameQ); \
	}

//Test structure size against computed size
typedef tS8 Testsw_config_get_par_val_Char_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(sw_config_get_par_val_Char_t)-4U)];
typedef tS8 Testsw_config_get_par_val_Char_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+4U-sizeof(sw_config_get_par_val_Char_t))];


//Send helper
#define sw_config_get_par_val_Int_send(buff, frameQ) {\
	 sw_config_get_par_val_Int_t *__msg = buff; \
	STBIN_TO_LINK_ENDIAN_CONV_tS32(&((__msg)->value)); \
	_stbin_msg_send((tUChar *)(__msg), \
				sw_config_get_par_val_Int_t_size_send, \
				frameQ); \
	}

//Test structure size against computed size
typedef tS8 Testsw_config_get_par_val_Int_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(sw_config_get_par_val_Int_t)-8U)];
typedef tS8 Testsw_config_get_par_val_Int_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+8U-sizeof(sw_config_get_par_val_Int_t))];


//Send helper
#define sw_config_get_par_val_UInt_send(buff, frameQ) {\
	 sw_config_get_par_val_UInt_t *__msg = buff; \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->value)); \
	_stbin_msg_send((tUChar *)(__msg), \
				sw_config_get_par_val_UInt_t_size_send, \
				frameQ); \
	}

//Test structure size against computed size
typedef tS8 Testsw_config_get_par_val_UInt_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(sw_config_get_par_val_UInt_t)-8U)];
typedef tS8 Testsw_config_get_par_val_UInt_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+8U-sizeof(sw_config_get_par_val_UInt_t))];


//Send helper
#define sw_config_get_par_val_Double_send(buff, frameQ) {\
	 sw_config_get_par_val_Double_t *__msg = buff; \
	STBIN_TO_LINK_ENDIAN_CONV_double(&((__msg)->value)); \
	_stbin_msg_send((tUChar *)(__msg), \
				sw_config_get_par_val_Double_t_size_send, \
				frameQ); \
	}

//Test structure size against computed size
typedef tS8 Testsw_config_get_par_val_Double_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(sw_config_get_par_val_Double_t)-16U)];
typedef tS8 Testsw_config_get_par_val_Double_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+16U-sizeof(sw_config_get_par_val_Double_t))];


//Send helper
#define sw_config_get_par_val_Dops_send(buff, frameQ) {\
	 sw_config_get_par_val_Dops_t *__msg = buff; \
	_stbin_msg_send((tUChar *)(__msg), \
				sw_config_get_par_val_Dops_t_size_send, \
				frameQ); \
	}

//Test structure size against computed size
typedef tS8 Testsw_config_get_par_val_Dops_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(sw_config_get_par_val_Dops_t)-8U)];
typedef tS8 Testsw_config_get_par_val_Dops_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+8U-sizeof(sw_config_get_par_val_Dops_t))];


//Send helper
#define sw_config_get_par_val_String_send(buff, frameQ) {\
	 sw_config_get_par_val_String_t *__msg = buff; \
	_stbin_msg_send((tUChar *)(__msg), \
				sw_config_get_par_val_String_t_size_send, \
				frameQ); \
	}

//Test structure size against computed size
typedef tS8 Testsw_config_get_par_val_String_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(sw_config_get_par_val_String_t)-76U)];
typedef tS8 Testsw_config_get_par_val_String_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+76U-sizeof(sw_config_get_par_val_String_t))];


//Send helper
#define get_algo_status_send(buff, frameQ) {\
	 get_algo_status_t *__msg = buff; \
	_stbin_msg_send((tUChar *)(__msg), \
				get_algo_status_t_size_send, \
				frameQ); \
	}

//Test structure size against computed size
typedef tS8 Testget_algo_status_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(get_algo_status_t)-4U)];
typedef tS8 Testget_algo_status_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+4U-sizeof(get_algo_status_t))];


//Send helper
#define read_datum_selection_send(buff, frameQ) {\
	 read_datum_selection_t *__msg = buff; \
	_stbin_msg_send((tUChar *)(__msg), \
				read_datum_selection_t_size_send, \
				frameQ); \
	}

//Test structure size against computed size
typedef tS8 Testread_datum_selection_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(read_datum_selection_t)-4U)];
typedef tS8 Testread_datum_selection_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+4U-sizeof(read_datum_selection_t))];


//Send helper
#define read_sw_config_all_blocks_send(buff, frameQ) {\
	 read_sw_config_all_blocks_t *__msg = buff; \
	STBIN_TO_LINK_ENDIAN_CONV_tU16(&((__msg)->length)); \
	_stbin_msg_send((tUChar *)(__msg), \
				read_sw_config_all_blocks_t_size_send, \
				frameQ); \
	}

//Test structure size against computed size
typedef tS8 Testread_sw_config_all_blocks_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(read_sw_config_all_blocks_t)-908U)];
typedef tS8 Testread_sw_config_all_blocks_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+908U-sizeof(read_sw_config_all_blocks_t))];


//Send helper
#define stbin_exec_dump_fe_send(buff, frameQ) {\
	 stbin_exec_dump_fe_t *__msg = buff; \
	_stbin_msg_send((tUChar *)(__msg), \
				stbin_exec_dump_fe_t_size_send, \
				frameQ); \
	}

//Test structure size against computed size
typedef tS8 Teststbin_exec_dump_fe_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(stbin_exec_dump_fe_t)-60U)];
typedef tS8 Teststbin_exec_dump_fe_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+60U-sizeof(stbin_exec_dump_fe_t))];


//Send helper
#define get_diff_source_send(buff, frameQ) {\
	 get_diff_source_t *__msg = buff; \
	_stbin_msg_send((tUChar *)(__msg), \
				get_diff_source_t_size_send, \
				frameQ); \
	}

//Test structure size against computed size
typedef tS8 Testget_diff_source_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(get_diff_source_t)-4U)];
typedef tS8 Testget_diff_source_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+4U-sizeof(get_diff_source_t))];


//Send helper
#define adc_read_send(buff, frameQ) {\
	 adc_read_t *__msg = buff; \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->data_read)); \
	_stbin_msg_send((tUChar *)(__msg), \
				adc_read_t_size_send, \
				frameQ); \
	}

//Test structure size against computed size
typedef tS8 Testadc_read_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(adc_read_t)-8U)];
typedef tS8 Testadc_read_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+8U-sizeof(adc_read_t))];


//Send helper
#define getAllSwVers_send(buff, frameQ) {\
	 getAllSwVers_t *__msg = buff; \
	_stbin_msg_send((tUChar *)(__msg), \
				getAllSwVers_t_size_send, \
				frameQ); \
	}

//Test structure size against computed size
typedef tS8 TestgetAllSwVers_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(getAllSwVers_t)-28U)];
typedef tS8 TestgetAllSwVers_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+28U-sizeof(getAllSwVers_t))];


//Section : Read Messages Responses (ClassId 0x2B)
//Send helper
#define sqi_data_get_send(buff, frameQ) {\
	 sqi_data_get_t *__msg = buff; \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->word8)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->word7)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->word6)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->word5)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->word4)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->word3)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->word2)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->word1)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->dest_addr)); \
	_stbin_msg_send((tUChar *)(__msg), \
				sqi_data_get_t_size_send, \
				frameQ); \
	}

//Test structure size against computed size
typedef tS8 Testsqi_data_get_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(sqi_data_get_t)-36U)];
typedef tS8 Testsqi_data_get_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+36U-sizeof(sqi_data_get_t))];


//Section : Write Responses (ClassId 0x3A)
//Section : Customer Flash Storage Write Responses (ClassId 0x3B)
//Send helper
#define sqi_data_set_send(buff, frameQ) {\
	 sqi_data_set_t *__msg = buff; \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->dest_addr)); \
	_stbin_msg_send((tUChar *)(__msg), \
				sqi_data_set_t_size_send, \
				frameQ); \
	}

//Test structure size against computed size
typedef tS8 Testsqi_data_set_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(sqi_data_set_t)-4U)];
typedef tS8 Testsqi_data_set_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+4U-sizeof(sqi_data_set_t))];


//Section : Reset messages (ClassId 0x5A)
//Above code is automatically generated (See rep_crm/tools/stbin/generators)
