//This code is automatically generated (See rep_crm/tools/stbin/generators)
#define COMPILER_MIN_ARRAY_SIZE 1U
//Section : SBAS Read Request Messages (ClassId 0x2C)


//Frame stbin_exec_waas_get_multi_ch (cid=0x2C mid=0x13)
#define stbin_exec_waas_get_multi_ch_MAP(sname, msg, len, p_result)\
	/*lint -e{9087} cast performed between a pointer to object type and a pointer to a different object type */ \
	stbin_exec_waas_get_multi_ch_t *sname = (stbin_exec_waas_get_multi_ch_t *)msg;\
	GPS_DEBUG_MSG(("STBIN Received Frame stbin_exec_waas_get_multi_ch\r\n"));\
	GPS_DEBUG_MSG(("STBIN chan_id=0x%X\r\n", sname->chan_id));\
	if(1U < sname->chan_id) {\
		GPS_DEBUG_MSG(("STBIN invalid chan_id=%d\r\n", sname->chan_id));\
		*(p_result) = STBIN_FAILED; }\
	if(len != sizeof(*sname)) {\
		GPS_DEBUG_MSG(("STBIN frame stbin_exec_waas_get_multi_ch received with Payload length %d vs %d\r\n", len, sizeof(*sname) - 0U));\
		*(p_result) = STBIN_FAILED; }

//Test structure size against computed size
typedef tS8 Teststbin_exec_waas_get_multi_ch_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(stbin_exec_waas_get_multi_ch_t)-1U)];
typedef tS8 Teststbin_exec_waas_get_multi_ch_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+1U-sizeof(stbin_exec_waas_get_multi_ch_t))];




//Frame stbin_exec_waas_get_prn_to_decode (cid=0x2C mid=0x14)
#define stbin_exec_waas_get_prn_to_decode_MAP(sname, msg, len, p_result)\
	GPS_DEBUG_MSG(("STBIN Received Frame stbin_exec_waas_get_prn_to_decode\r\n"));\
	if(len != 0U) {\
		GPS_DEBUG_MSG(("STBIN Dataless frame stbin_exec_waas_get_prn_to_decode received with Payload length %d\r\n", len));\
		*(p_result) = STBIN_FAILED; }

//Section : SBAS Write Request Messages (ClassId 0x3C)


//Frame stbin_exec_waas_if_on_off_write_req (cid=0x3C mid=0x30)
#define stbin_exec_waas_if_on_off_write_req_MAP(sname, msg, len, p_result)\
	/*lint -e{9087} cast performed between a pointer to object type and a pointer to a different object type */ \
	stbin_exec_waas_if_on_off_write_req_t *sname = (stbin_exec_waas_if_on_off_write_req_t *)msg;\
	GPS_DEBUG_MSG(("STBIN Received Frame stbin_exec_waas_if_on_off_write_req\r\n"));\
	GPS_DEBUG_MSG(("STBIN onOff=0x%X\r\n", sname->onOff));\
	if(1U < sname->onOff) {\
		GPS_DEBUG_MSG(("STBIN invalid onOff=%d\r\n", sname->onOff));\
		*(p_result) = STBIN_FAILED; }\
	if(len != sizeof(*sname)) {\
		GPS_DEBUG_MSG(("STBIN frame stbin_exec_waas_if_on_off_write_req received with Payload length %d vs %d\r\n", len, sizeof(*sname) - 0U));\
		*(p_result) = STBIN_FAILED; }

//Test structure size against computed size
typedef tS8 Teststbin_exec_waas_if_on_off_write_req_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(stbin_exec_waas_if_on_off_write_req_t)-1U)];
typedef tS8 Teststbin_exec_waas_if_on_off_write_req_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+1U-sizeof(stbin_exec_waas_if_on_off_write_req_t))];




//Frame stbin_exec_waas_if_sat_write_req (cid=0x3C mid=0x31)
#define stbin_exec_waas_if_sat_write_req_MAP(sname, msg, len, p_result)\
	/*lint -e{9087} cast performed between a pointer to object type and a pointer to a different object type */ \
	stbin_exec_waas_if_sat_write_req_t *sname = (stbin_exec_waas_if_sat_write_req_t *)msg;\
	GPS_DEBUG_MSG(("STBIN Received Frame stbin_exec_waas_if_sat_write_req\r\n"));\
	GPS_DEBUG_MSG(("STBIN sbasSatId=%d\r\n", sname->sbasSatId));\
	if(len != sizeof(*sname)) {\
		GPS_DEBUG_MSG(("STBIN frame stbin_exec_waas_if_sat_write_req received with Payload length %d vs %d\r\n", len, sizeof(*sname) - 0U));\
		*(p_result) = STBIN_FAILED; }

//Test structure size against computed size
typedef tS8 Teststbin_exec_waas_if_sat_write_req_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(stbin_exec_waas_if_sat_write_req_t)-1U)];
typedef tS8 Teststbin_exec_waas_if_sat_write_req_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+1U-sizeof(stbin_exec_waas_if_sat_write_req_t))];




//Frame stbin_exec_sbas_sat_list_req (cid=0x3C mid=0x32)
#define stbin_exec_sbas_sat_list_req_MAP(sname, msg, len, p_result)\
	GPS_DEBUG_MSG(("STBIN Received Frame stbin_exec_sbas_sat_list_req\r\n"));\
	if(len != 0U) {\
		GPS_DEBUG_MSG(("STBIN Dataless frame stbin_exec_sbas_sat_list_req received with Payload length %d\r\n", len));\
		*(p_result) = STBIN_FAILED; }



//Frame stbin_exec_sbas_periodic_backup_req (cid=0x3C mid=0x33)
#define stbin_exec_sbas_periodic_backup_req_MAP(sname, msg, len, p_result)\
	/*lint -e{9087} cast performed between a pointer to object type and a pointer to a different object type */ \
	stbin_exec_sbas_periodic_backup_req_t *sname = (stbin_exec_sbas_periodic_backup_req_t *)msg;\
	GPS_DEBUG_MSG(("STBIN Received Frame stbin_exec_sbas_periodic_backup_req\r\n"));\
	GPS_DEBUG_MSG(("STBIN onOff=0x%X\r\n", sname->onOff));\
	if(1U < sname->onOff) {\
		GPS_DEBUG_MSG(("STBIN invalid onOff=%d\r\n", sname->onOff));\
		*(p_result) = STBIN_FAILED; }\
	if(len != sizeof(*sname)) {\
		GPS_DEBUG_MSG(("STBIN frame stbin_exec_sbas_periodic_backup_req received with Payload length %d vs %d\r\n", len, sizeof(*sname) - 0U));\
		*(p_result) = STBIN_FAILED; }

//Test structure size against computed size
typedef tS8 Teststbin_exec_sbas_periodic_backup_req_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(stbin_exec_sbas_periodic_backup_req_t)-1U)];
typedef tS8 Teststbin_exec_sbas_periodic_backup_req_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+1U-sizeof(stbin_exec_sbas_periodic_backup_req_t))];




//Frame stbin_exec_sbas_backup_req (cid=0x3C mid=0x34)
#define stbin_exec_sbas_backup_req_MAP(sname, msg, len, p_result)\
	GPS_DEBUG_MSG(("STBIN Received Frame stbin_exec_sbas_backup_req\r\n"));\
	if(len != 0U) {\
		GPS_DEBUG_MSG(("STBIN Dataless frame stbin_exec_sbas_backup_req received with Payload length %d\r\n", len));\
		*(p_result) = STBIN_FAILED; }



//Frame stbin_exec_waas_set_multi_ch_prn_write_req (cid=0x3C mid=0x35)
#define stbin_exec_waas_set_multi_ch_prn_write_req_MAP(sname, msg, len, p_result)\
	/*lint -e{9087} cast performed between a pointer to object type and a pointer to a different object type */ \
	stbin_exec_waas_set_multi_ch_prn_write_req_t *sname = (stbin_exec_waas_set_multi_ch_prn_write_req_t *)msg;\
	GPS_DEBUG_MSG(("STBIN Received Frame stbin_exec_waas_set_multi_ch_prn_write_req\r\n"));\
	GPS_DEBUG_MSG(("STBIN chan_id=0x%X\r\n", sname->chan_id));\
	if(1U < sname->chan_id) {\
		GPS_DEBUG_MSG(("STBIN invalid chan_id=%d\r\n", sname->chan_id));\
		*(p_result) = STBIN_FAILED; }\
	GPS_DEBUG_MSG(("STBIN sat_id=0x%X\r\n", sname->sat_id));\
	if((120U > sname->sat_id) || (138U < sname->sat_id)) {\
		GPS_DEBUG_MSG(("STBIN invalid sat_id=%d\r\n", sname->sat_id));\
		*(p_result) = STBIN_FAILED; }\
	GPS_DEBUG_MSG(("STBIN sbas_status=0x%X\r\n", sname->sbas_status));\
	if(1U < sname->sbas_status) {\
		GPS_DEBUG_MSG(("STBIN invalid sbas_status=%d\r\n", sname->sbas_status));\
		*(p_result) = STBIN_FAILED; }\
	if(len != (sizeof(*sname) - 1U)) {\
		GPS_DEBUG_MSG(("STBIN frame stbin_exec_waas_set_multi_ch_prn_write_req received with Payload length %d vs %d\r\n", len, sizeof(*sname) - 1U));\
		*(p_result) = STBIN_FAILED; }

//Test structure size against computed size
typedef tS8 Teststbin_exec_waas_set_multi_ch_prn_write_req_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(stbin_exec_waas_set_multi_ch_prn_write_req_t)-4U)];
typedef tS8 Teststbin_exec_waas_set_multi_ch_prn_write_req_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+4U-sizeof(stbin_exec_waas_set_multi_ch_prn_write_req_t))];




//Frame stbin_exec_waas_set_prn_to_decode_write_req (cid=0x3C mid=0x36)
#define stbin_exec_waas_set_prn_to_decode_write_req_MAP(sname, msg, len, p_result)\
	/*lint -e{9087} cast performed between a pointer to object type and a pointer to a different object type */ \
	stbin_exec_waas_set_prn_to_decode_write_req_t *sname = (stbin_exec_waas_set_prn_to_decode_write_req_t *)msg;\
	GPS_DEBUG_MSG(("STBIN Received Frame stbin_exec_waas_set_prn_to_decode_write_req\r\n"));\
	GPS_DEBUG_MSG(("STBIN sat_id=0x%X\r\n", sname->sat_id));\
	if((120U > sname->sat_id) || (138U < sname->sat_id)) {\
		GPS_DEBUG_MSG(("STBIN invalid sat_id=%d\r\n", sname->sat_id));\
		*(p_result) = STBIN_FAILED; }\
	if(len != (sizeof(*sname) - 3U)) {\
		GPS_DEBUG_MSG(("STBIN frame stbin_exec_waas_set_prn_to_decode_write_req received with Payload length %d vs %d\r\n", len, sizeof(*sname) - 3U));\
		*(p_result) = STBIN_FAILED; }

//Test structure size against computed size
typedef tS8 Teststbin_exec_waas_set_prn_to_decode_write_req_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(stbin_exec_waas_set_prn_to_decode_write_req_t)-4U)];
typedef tS8 Teststbin_exec_waas_set_prn_to_decode_write_req_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+4U-sizeof(stbin_exec_waas_set_prn_to_decode_write_req_t))];




//Frame stbin_exec_waas_autosearch_on_off_write_req (cid=0x3C mid=0x37)
#define stbin_exec_waas_autosearch_on_off_write_req_MAP(sname, msg, len, p_result)\
	/*lint -e{9087} cast performed between a pointer to object type and a pointer to a different object type */ \
	stbin_exec_waas_autosearch_on_off_write_req_t *sname = (stbin_exec_waas_autosearch_on_off_write_req_t *)msg;\
	GPS_DEBUG_MSG(("STBIN Received Frame stbin_exec_waas_autosearch_on_off_write_req\r\n"));\
	GPS_DEBUG_MSG(("STBIN onOff=0x%X\r\n", sname->onOff));\
	if(1U < sname->onOff) {\
		GPS_DEBUG_MSG(("STBIN invalid onOff=%d\r\n", sname->onOff));\
		*(p_result) = STBIN_FAILED; }\
	if(len != sizeof(*sname)) {\
		GPS_DEBUG_MSG(("STBIN frame stbin_exec_waas_autosearch_on_off_write_req received with Payload length %d vs %d\r\n", len, sizeof(*sname) - 0U));\
		*(p_result) = STBIN_FAILED; }

//Test structure size against computed size
typedef tS8 Teststbin_exec_waas_autosearch_on_off_write_req_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(stbin_exec_waas_autosearch_on_off_write_req_t)-1U)];
typedef tS8 Teststbin_exec_waas_autosearch_on_off_write_req_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+1U-sizeof(stbin_exec_waas_autosearch_on_off_write_req_t))];


//Section : SBAS Tests Request Messages (ClassId 0x4B)


//Frame stbin_exec_waastest_req (cid=0x4B mid=0x1D)
#define stbin_exec_waastest_req_MAP(sname, msg, len, p_result)\
	GPS_DEBUG_MSG(("STBIN Received Frame stbin_exec_waastest_req\r\n"));\
	if(len != 0U) {\
		GPS_DEBUG_MSG(("STBIN Dataless frame stbin_exec_waastest_req received with Payload length %d\r\n", len));\
		*(p_result) = STBIN_FAILED; }

//Section : SBAS Output Messages (ClassId 0x03)
//Section : SBAS Output Messages (ClassId 0x03)
//Send helper
#define outputprocess_sbas_send(buff, frameQ) {\
	 outputprocess_sbas_t *__msg = buff; \
	STBIN_TO_LINK_ENDIAN_CONV_tU16(&((__msg)->azimuth)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU32(&((__msg)->iTOW)); \
	_stbin_msg_send((tUChar *)(__msg), \
				outputprocess_sbas_t_size_send, \
				frameQ); \
	}

//Test structure size against computed size
typedef tS8 Testoutputprocess_sbas_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(outputprocess_sbas_t)-12U)];
typedef tS8 Testoutputprocess_sbas_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+12U-sizeof(outputprocess_sbas_t))];


//Send helper
#define outputprocess_sbas_data_send(buff, frameQ) {\
	 outputprocess_sbas_data_t *__msg = buff; \
	STBIN_TO_LINK_ENDIAN_CONV_tS32(&((__msg)->delta_range_rate)); \
	STBIN_TO_LINK_ENDIAN_CONV_tS32(&((__msg)->delta_range)); \
	STBIN_TO_LINK_ENDIAN_CONV_tS32(&((__msg)->diff_epoch)); \
	STBIN_TO_LINK_ENDIAN_CONV_tS32(&((__msg)->iod)); \
	STBIN_TO_LINK_ENDIAN_CONV_tS32(&((__msg)->tropo)); \
	STBIN_TO_LINK_ENDIAN_CONV_tS32(&((__msg)->iono)); \
	STBIN_TO_LINK_ENDIAN_CONV_tS32(&((__msg)->sat)); \
	STBIN_TO_LINK_ENDIAN_CONV_tS32(&((__msg)->total)); \
	_stbin_msg_send((tUChar *)(__msg), \
				outputprocess_sbas_data_t_size_send, \
				frameQ); \
	}

//Test structure size against computed size
typedef tS8 Testoutputprocess_sbas_data_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(outputprocess_sbas_data_t)-36U)];
typedef tS8 Testoutputprocess_sbas_data_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+36U-sizeof(outputprocess_sbas_data_t))];


//Section : SBAS Write Responses (ClassId 0x3C)
//Section : SBAS Read Messages Responses (ClassId 0x2C)
//Send helper
#define waas_get_multi_ch_send(buff, frameQ) {\
	 waas_get_multi_ch_t *__msg = buff; \
	_stbin_msg_send((tUChar *)(__msg), \
				waas_get_multi_ch_t_size_send, \
				frameQ); \
	}

//Test structure size against computed size
typedef tS8 Testwaas_get_multi_ch_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(waas_get_multi_ch_t)-4U)];
typedef tS8 Testwaas_get_multi_ch_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+4U-sizeof(waas_get_multi_ch_t))];


//Send helper
#define waas_get_prn_to_decode_send(buff, frameQ) {\
	 waas_get_prn_to_decode_t *__msg = buff; \
	_stbin_msg_send((tUChar *)(__msg), \
				waas_get_prn_to_decode_t_size_send, \
				frameQ); \
	}

//Test structure size against computed size
typedef tS8 Testwaas_get_prn_to_decode_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(waas_get_prn_to_decode_t)-4U)];
typedef tS8 Testwaas_get_prn_to_decode_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+4U-sizeof(waas_get_prn_to_decode_t))];


//Section : SBAS Write Responses (ClassId 0x4B)
//Above code is automatically generated (See rep_crm/tools/stbin/generators)
