//This code is automatically generated (See rep_crm/tools/stbin/generators)
#define COMPILER_MIN_ARRAY_SIZE 1U
//Section : PGPS Control Request Messages (ClassId 0x5E)


//Frame stbin_stagps_ctl_passgen_req (cid=0x5E mid=0x1)
#define stbin_stagps_ctl_passgen_req_MAP(sname, msg, len, p_result)\
	/*lint -e{9087} cast performed between a pointer to object type and a pointer to a different object type */ \
	stbin_stagps_ctl_passgen_req_t *sname = (stbin_stagps_ctl_passgen_req_t *)msg;\
	GPS_DEBUG_MSG(("STBIN Received Frame stbin_stagps_ctl_passgen_req\r\n"));\
	STBIN_FROM_LINK_ENDIAN_CONV_tU32(&(sname->gps_seconds));\
	GPS_DEBUG_MSG(("STBIN gps_seconds=%d\r\n", sname->gps_seconds));\
	GPS_DEBUG_MSG(("STBIN vendorId=<strings are not traced>\r\n"));\
	GPS_DEBUG_MSG(("STBIN deviceId=<strings are not traced>\r\n"));\
	if(len != sizeof(*sname)) {\
		GPS_DEBUG_MSG(("STBIN frame stbin_stagps_ctl_passgen_req received with Payload length %d vs %d\r\n", len, sizeof(*sname) - 0U));\
		*(p_result) = STBIN_FAILED; }

//Test structure size against computed size
typedef tS8 Teststbin_stagps_ctl_passgen_req_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(stbin_stagps_ctl_passgen_req_t)-104U)];
typedef tS8 Teststbin_stagps_ctl_passgen_req_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+104U-sizeof(stbin_stagps_ctl_passgen_req_t))];




//Frame stbin_stagps_ctl_satseed_req (cid=0x5E mid=0x2)
#define stbin_stagps_ctl_satseed_req_MAP(sname, msg, len, p_result)\
	/*lint -e{9087} cast performed between a pointer to object type and a pointer to a different object type */ \
	stbin_stagps_ctl_satseed_req_t *sname = (stbin_stagps_ctl_satseed_req_t *)msg;\
	GPS_DEBUG_MSG(("STBIN Received Frame stbin_stagps_ctl_satseed_req\r\n"));\
	STBIN_FROM_LINK_ENDIAN_CONV_tU32(&(sname->seed_t0));\
	GPS_DEBUG_MSG(("STBIN seed_t0=%d\r\n", sname->seed_t0));\
	STBIN_FROM_LINK_ENDIAN_CONV_tU32(&(sname->seed_tcur));\
	GPS_DEBUG_MSG(("STBIN seed_tcur=%d\r\n", sname->seed_tcur));\
	STBIN_FROM_LINK_ENDIAN_CONV_tU32(&(sname->seed_clkid));\
	GPS_DEBUG_MSG(("STBIN seed_clkid=%d\r\n", sname->seed_clkid));\
	GPS_DEBUG_MSG(("STBIN seed=<arrays are not traced>\r\n"));\
	GPS_DEBUG_MSG(("STBIN prn=%d\r\n", sname->prn));\
	GPS_DEBUG_MSG(("STBIN no_seed=0x%X\r\n", sname->no_seed));\
	if(1U < sname->no_seed) {\
		GPS_DEBUG_MSG(("STBIN invalid no_seed=%d\r\n", sname->no_seed));\
		*(p_result) = STBIN_FAILED; }\
	if(len != (sizeof(*sname) - 2U)) {\
		GPS_DEBUG_MSG(("STBIN frame stbin_stagps_ctl_satseed_req received with Payload length %d vs %d\r\n", len, sizeof(*sname) - 2U));\
		*(p_result) = STBIN_FAILED; }

//Test structure size against computed size
typedef tS8 Teststbin_stagps_ctl_satseed_req_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(stbin_stagps_ctl_satseed_req_t)-216U)];
typedef tS8 Teststbin_stagps_ctl_satseed_req_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+216U-sizeof(stbin_stagps_ctl_satseed_req_t))];




//Frame stbin_stagps_ctl_satseed_nextPrn_req (cid=0x5E mid=0x3)
#define stbin_stagps_ctl_satseed_nextPrn_req_MAP(sname, msg, len, p_result)\
	GPS_DEBUG_MSG(("STBIN Received Frame stbin_stagps_ctl_satseed_nextPrn_req\r\n"));\
	if(len != 0U) {\
		GPS_DEBUG_MSG(("STBIN Dataless frame stbin_stagps_ctl_satseed_nextPrn_req received with Payload length %d\r\n", len));\
		*(p_result) = STBIN_FAILED; }

//Section : \stagpstext Write Request Messages (ClassId 0x3E)


//Frame stbin_stagps_onoff_req (cid=0x3E mid=0x1)
#define stbin_stagps_onoff_req_MAP(sname, msg, len, p_result)\
	/*lint -e{9087} cast performed between a pointer to object type and a pointer to a different object type */ \
	stbin_stagps_onoff_req_t *sname = (stbin_stagps_onoff_req_t *)msg;\
	GPS_DEBUG_MSG(("STBIN Received Frame stbin_stagps_onoff_req\r\n"));\
	GPS_DEBUG_MSG(("STBIN onOff=0x%X\r\n", sname->onOff));\
	if(1U < sname->onOff) {\
		GPS_DEBUG_MSG(("STBIN invalid onOff=%d\r\n", sname->onOff));\
		*(p_result) = STBIN_FAILED; }\
	if(len != sizeof(*sname)) {\
		GPS_DEBUG_MSG(("STBIN frame stbin_stagps_onoff_req received with Payload length %d vs %d\r\n", len, sizeof(*sname) - 0U));\
		*(p_result) = STBIN_FAILED; }

//Test structure size against computed size
typedef tS8 Teststbin_stagps_onoff_req_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(stbin_stagps_onoff_req_t)-1U)];
typedef tS8 Teststbin_stagps_onoff_req_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+1U-sizeof(stbin_stagps_onoff_req_t))];


//Section : \stagpstext Test Request Messages (ClassId 0x4E)


//Frame stbin_stagps_test_invalidate_req (cid=0x4E mid=0x1)
#define stbin_stagps_test_invalidate_req_MAP(sname, msg, len, p_result)\
	/*lint -e{9087} cast performed between a pointer to object type and a pointer to a different object type */ \
	stbin_stagps_test_invalidate_req_t *sname = (stbin_stagps_test_invalidate_req_t *)msg;\
	GPS_DEBUG_MSG(("STBIN Received Frame stbin_stagps_test_invalidate_req\r\n"));\
	GPS_DEBUG_MSG(("STBIN selectionMask=%d\r\n", sname->selectionMask));\
	if(len != sizeof(*sname)) {\
		GPS_DEBUG_MSG(("STBIN frame stbin_stagps_test_invalidate_req received with Payload length %d vs %d\r\n", len, sizeof(*sname) - 0U));\
		*(p_result) = STBIN_FAILED; }

//Test structure size against computed size
typedef tS8 Teststbin_stagps_test_invalidate_req_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(stbin_stagps_test_invalidate_req_t)-1U)];
typedef tS8 Teststbin_stagps_test_invalidate_req_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+1U-sizeof(stbin_stagps_test_invalidate_req_t))];




//Frame stbin_stagps_test_real_ephem_update_req (cid=0x4E mid=0x2)
#define stbin_stagps_test_real_ephem_update_req_MAP(sname, msg, len, p_result)\
	/*lint -e{9087} cast performed between a pointer to object type and a pointer to a different object type */ \
	stbin_stagps_test_real_ephem_update_req_t *sname = (stbin_stagps_test_real_ephem_update_req_t *)msg;\
	GPS_DEBUG_MSG(("STBIN Received Frame stbin_stagps_test_real_ephem_update_req\r\n"));\
	GPS_DEBUG_MSG(("STBIN onOff=0x%X\r\n", sname->onOff));\
	if(1U < sname->onOff) {\
		GPS_DEBUG_MSG(("STBIN invalid onOff=%d\r\n", sname->onOff));\
		*(p_result) = STBIN_FAILED; }\
	if(len != sizeof(*sname)) {\
		GPS_DEBUG_MSG(("STBIN frame stbin_stagps_test_real_ephem_update_req received with Payload length %d vs %d\r\n", len, sizeof(*sname) - 0U));\
		*(p_result) = STBIN_FAILED; }

//Test structure size against computed size
typedef tS8 Teststbin_stagps_test_real_ephem_update_req_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(stbin_stagps_test_real_ephem_update_req_t)-1U)];
typedef tS8 Teststbin_stagps_test_real_ephem_update_req_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+1U-sizeof(stbin_stagps_test_real_ephem_update_req_t))];




//Frame stagps_stbin_test_use_pred_ephem_req (cid=0x4E mid=0x3)
#define stagps_stbin_test_use_pred_ephem_req_MAP(sname, msg, len, p_result)\
	/*lint -e{9087} cast performed between a pointer to object type and a pointer to a different object type */ \
	stagps_stbin_test_use_pred_ephem_req_t *sname = (stagps_stbin_test_use_pred_ephem_req_t *)msg;\
	GPS_DEBUG_MSG(("STBIN Received Frame stagps_stbin_test_use_pred_ephem_req\r\n"));\
	GPS_DEBUG_MSG(("STBIN onOff=0x%X\r\n", sname->onOff));\
	if(1U < sname->onOff) {\
		GPS_DEBUG_MSG(("STBIN invalid onOff=%d\r\n", sname->onOff));\
		*(p_result) = STBIN_FAILED; }\
	if(len != sizeof(*sname)) {\
		GPS_DEBUG_MSG(("STBIN frame stagps_stbin_test_use_pred_ephem_req received with Payload length %d vs %d\r\n", len, sizeof(*sname) - 0U));\
		*(p_result) = STBIN_FAILED; }

//Test structure size against computed size
typedef tS8 Teststagps_stbin_test_use_pred_ephem_req_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(stagps_stbin_test_use_pred_ephem_req_t)-1U)];
typedef tS8 Teststagps_stbin_test_use_pred_ephem_req_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+1U-sizeof(stagps_stbin_test_use_pred_ephem_req_t))];




//Frame stagps_stbin_test_get_status (cid=0x4E mid=0x4)
#define stagps_stbin_test_get_status_MAP(sname, msg, len, p_result)\
	GPS_DEBUG_MSG(("STBIN Received Frame stagps_stbin_test_get_status\r\n"));\
	if(len != 0U) {\
		GPS_DEBUG_MSG(("STBIN Dataless frame stagps_stbin_test_get_status received with Payload length %d\r\n", len));\
		*(p_result) = STBIN_FAILED; }



//Frame stagps_stbin_test_ephems_upload (cid=0x4E mid=0x5)
#define stagps_stbin_test_ephems_upload_MAP(sname, msg, len, p_result)\
	/*lint -e{9087} cast performed between a pointer to object type and a pointer to a different object type */ \
	stagps_stbin_test_ephems_upload_t *sname = (stagps_stbin_test_ephems_upload_t *)msg;\
	GPS_DEBUG_MSG(("STBIN Received Frame stagps_stbin_test_ephems_upload\r\n"));\
	GPS_DEBUG_MSG(("STBIN value=<arrays are not traced>\r\n"));\
	GPS_DEBUG_MSG(("STBIN dsp_satid=%d\r\n", sname->dsp_satid));\
	if(len != (sizeof(*sname) - 3U)) {\
		GPS_DEBUG_MSG(("STBIN frame stagps_stbin_test_ephems_upload received with Payload length %d vs %d\r\n", len, sizeof(*sname) - 3U));\
		*(p_result) = STBIN_FAILED; }

//Test structure size against computed size
typedef tS8 Teststagps_stbin_test_ephems_upload_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(stagps_stbin_test_ephems_upload_t)-68U)];
typedef tS8 Teststagps_stbin_test_ephems_upload_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+68U-sizeof(stagps_stbin_test_ephems_upload_t))];


//Section : \stagpstext Output Messages request (ClassId 0x02)
//Section : PGPS Control Responses (ClassId 0x5E)
//Send helper
#define stbin_stagps_ctl_passgen_rsp_send(buff, frameQ) {\
	 stbin_stagps_ctl_passgen_rsp_t *__msg = buff; \
	_stbin_msg_send((tUChar *)(__msg), \
				stbin_stagps_ctl_passgen_rsp_t_size_send, \
				frameQ); \
	}

//Test structure size against computed size
typedef tS8 Teststbin_stagps_ctl_passgen_rsp_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(stbin_stagps_ctl_passgen_rsp_t)-41U)];
typedef tS8 Teststbin_stagps_ctl_passgen_rsp_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+41U-sizeof(stbin_stagps_ctl_passgen_rsp_t))];


//Send helper
#define stbin_stagps_ctl_satseed_nextPrn_rsp_send(buff, frameQ) {\
	 stbin_stagps_ctl_satseed_nextPrn_rsp_t *__msg = buff; \
	_stbin_msg_send((tUChar *)(__msg), \
				stbin_stagps_ctl_satseed_nextPrn_rsp_t_size_send, \
				frameQ); \
	}

//Test structure size against computed size
typedef tS8 Teststbin_stagps_ctl_satseed_nextPrn_rsp_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(stbin_stagps_ctl_satseed_nextPrn_rsp_t)-1U)];
typedef tS8 Teststbin_stagps_ctl_satseed_nextPrn_rsp_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+1U-sizeof(stbin_stagps_ctl_satseed_nextPrn_rsp_t))];


//Section : \stagpstext Write Responses (ClassId 0x3E)
//Section : \stagpstext Test Response Messages (ClassId 0x4E)
//Send helper
#define stagps_stbin_test_get_status_send(buff, frameQ) {\
	 stagps_stbin_test_get_status_t *__msg = buff; \
	STBIN_TO_LINK_ENDIAN_CONV_tS32(&((__msg)->status)); \
	_stbin_msg_send((tUChar *)(__msg), \
				stagps_stbin_test_get_status_t_size_send, \
				frameQ); \
	}

//Test structure size against computed size
typedef tS8 Teststagps_stbin_test_get_status_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(stagps_stbin_test_get_status_t)-4U)];
typedef tS8 Teststagps_stbin_test_get_status_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+4U-sizeof(stagps_stbin_test_get_status_t))];


//Section : \stagpstext Output Messages (ClassId 0x02)
//Send helper
#define outputprocess_stagps_gps_send(buff, frameQ) {\
	 outputprocess_stagps_gps_t *__msg = buff; \
	STBIN_TO_LINK_ENDIAN_CONV_tU16(&((__msg)->vDOP)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU16(&((__msg)->hDOP)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU16(&((__msg)->pDOP)); \
	_stbin_msg_send((tUChar *)(__msg), \
				outputprocess_stagps_gps_t_size_send, \
				frameQ); \
	}

//Test structure size against computed size
typedef tS8 Testoutputprocess_stagps_gps_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(outputprocess_stagps_gps_t)-56U)];
typedef tS8 Testoutputprocess_stagps_gps_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+56U-sizeof(outputprocess_stagps_gps_t))];


//Send helper
#define outputprocess_stagps_glonass_send(buff, frameQ) {\
	 outputprocess_stagps_glonass_t *__msg = buff; \
	STBIN_TO_LINK_ENDIAN_CONV_tU16(&((__msg)->vDOP)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU16(&((__msg)->hDOP)); \
	STBIN_TO_LINK_ENDIAN_CONV_tU16(&((__msg)->pDOP)); \
	_stbin_msg_send((tUChar *)(__msg), \
				outputprocess_stagps_glonass_t_size_send, \
				frameQ); \
	}

//Test structure size against computed size
typedef tS8 Testoutputprocess_stagps_glonass_min[(tS32)(COMPILER_MIN_ARRAY_SIZE+sizeof(outputprocess_stagps_glonass_t)-56U)];
typedef tS8 Testoutputprocess_stagps_glonass_max[(tS32)(COMPILER_MIN_ARRAY_SIZE+56U-sizeof(outputprocess_stagps_glonass_t))];


//Above code is automatically generated (See rep_crm/tools/stbin/generators)
