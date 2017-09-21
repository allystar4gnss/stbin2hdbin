//This code is automatically generated (See rep_crm/tools/stbin/generators)
//Section : PGPS Control Request Messages (ClassId 0x5E)
#define STBIN_DOC_PASSGEN_ID_LEN 50
#define STBIN_DOC_SATSEED_MAX_SIZE 200
//Frame stbin_stagps_ctl_passgen_req (cid=0x5E mid=0x1)
typedef struct stbin_stagps_ctl_passgen_req {
	tU32 gps_seconds; /* 0 */
	tChar vendorId[STBIN_DOC_PASSGEN_ID_LEN]; /* 4 */
	tChar deviceId[STBIN_DOC_PASSGEN_ID_LEN]; /* 54 */
} stbin_stagps_ctl_passgen_req_t;
#define stbin_stagps_ctl_passgen_req_t_size_send 104

//Frame stbin_stagps_ctl_satseed_req (cid=0x5E mid=0x2)
typedef struct stbin_stagps_ctl_satseed_req {
	tU32 seed_t0; /* 0 */
	tU32 seed_tcur; /* 4 */
	tU32 seed_clkid; /* 8 */
	tU8 seed[200]; /* 12 */
	tU8 prn; /* 212 */
	tU8 no_seed; /* 213 */
	tU16 padding2; /* 214 */
} stbin_stagps_ctl_satseed_req_t;
#define stbin_stagps_ctl_satseed_req_t_size_send 214

//Frame stbin_stagps_ctl_satseed_nextPrn_req (cid=0x5E mid=0x3)
	// Have no payload
//Section : \stagpstext Write Request Messages (ClassId 0x3E)
//Frame stbin_stagps_onoff_req (cid=0x3E mid=0x1)
typedef struct stbin_stagps_onoff_req {
	tU8 onOff; /* 0 */
} stbin_stagps_onoff_req_t;
#define stbin_stagps_onoff_req_t_size_send 1

//Section : \stagpstext Test Request Messages (ClassId 0x4E)
//Frame stbin_stagps_test_invalidate_req (cid=0x4E mid=0x1)
typedef struct stbin_stagps_test_invalidate_req {
	tU8 selectionMask; /* 0 */
} stbin_stagps_test_invalidate_req_t;
#define stbin_stagps_test_invalidate_req_t_size_send 1

//Frame stbin_stagps_test_real_ephem_update_req (cid=0x4E mid=0x2)
typedef struct stbin_stagps_test_real_ephem_update_req {
	tU8 onOff; /* 0 */
} stbin_stagps_test_real_ephem_update_req_t;
#define stbin_stagps_test_real_ephem_update_req_t_size_send 1

//Frame stagps_stbin_test_use_pred_ephem_req (cid=0x4E mid=0x3)
typedef struct stagps_stbin_test_use_pred_ephem_req {
	tU8 onOff; /* 0 */
} stagps_stbin_test_use_pred_ephem_req_t;
#define stagps_stbin_test_use_pred_ephem_req_t_size_send 1

//Frame stagps_stbin_test_get_status (cid=0x4E mid=0x4)
	// Have no payload
//Frame stagps_stbin_test_ephems_upload (cid=0x4E mid=0x5)
typedef struct stagps_stbin_test_ephems_upload {
	tU8 value[64]; /* 0 */
	tU8 dsp_satid; /* 64 */
	tU8 padding1; /* 65 */
	tU16 padding2; /* 66 */
} stagps_stbin_test_ephems_upload_t;
#define stagps_stbin_test_ephems_upload_t_size_send 65

//Section : \stagpstext Output Messages request (ClassId 0x02)
//Section : PGPS Control Responses (ClassId 0x5E)
#define STBIN_DOC_PASSGEN_PASS_LEN 41
//Frame stbin_stagps_ctl_passgen_rsp (cid=0x5E mid=0x1)
typedef struct stbin_stagps_ctl_passgen_rsp {
	tChar password[STBIN_DOC_PASSGEN_PASS_LEN]; /* 0 */
} stbin_stagps_ctl_passgen_rsp_t;
#define stbin_stagps_ctl_passgen_rsp_t_size_send 41

//Frame stbin_stagps_ctl_satseed_nextPrn_rsp (cid=0x5E mid=0x3)
typedef struct stbin_stagps_ctl_satseed_nextPrn_rsp {
	tU8 nextPrn; /* 0 */
} stbin_stagps_ctl_satseed_nextPrn_rsp_t;
#define stbin_stagps_ctl_satseed_nextPrn_rsp_t_size_send 1

//Section : \stagpstext Write Responses (ClassId 0x3E)
//Section : \stagpstext Test Response Messages (ClassId 0x4E)
//Frame stagps_stbin_test_get_status (cid=0x4E mid=0x4)
typedef struct stagps_stbin_test_get_status {
	tS32 status; /* 0 */
} stagps_stbin_test_get_status_t;
#define stagps_stbin_test_get_status_t_size_send 4

//Section : \stagpstext Output Messages (ClassId 0x02)
#define NB_MAX_STAGPS_SATS_REPORTED 24
//Frame outputprocess_stagps_gps (cid=0x2 mid=0x1)
typedef struct outputprocess_stagps_gps {
	tU16 pDOP; /* 0 */
	tU16 hDOP; /* 2 */
	tU16 vDOP; /* 4 */
	tU8 fixMode; /* 6 */
	tU8 cnt; /* 7 */
	tU8 ids[24]; /* 8 */
	tS8 ages[24]; /* 32 */
} outputprocess_stagps_gps_t;
#define outputprocess_stagps_gps_t_size_send 56

//Frame outputprocess_stagps_glonass (cid=0x2 mid=0x2)
typedef struct outputprocess_stagps_glonass {
	tU16 pDOP; /* 0 */
	tU16 hDOP; /* 2 */
	tU16 vDOP; /* 4 */
	tU8 fixMode; /* 6 */
	tU8 cnt; /* 7 */
	tU8 ids[24]; /* 8 */
	tS8 ages[24]; /* 32 */
} outputprocess_stagps_glonass_t;
#define outputprocess_stagps_glonass_t_size_send 56

#define STBIN_STAGPS_MAX_PAYLOAD_SIZE 214U
#ifndef STBIN_MAX_PAYLOAD_SIZE
#  error Maximal payload size must be defined when this code is reached
#endif
#if STBIN_MAX_PAYLOAD_SIZE < STBIN_STAGPS_MAX_PAYLOAD_SIZE
#  error Maximal payload size must be reviewed
#endif
//Above code is automatically generated (See rep_crm/tools/stbin/generators)
