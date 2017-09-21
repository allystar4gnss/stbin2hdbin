//This code is automatically generated (See rep_crm/tools/stbin/generators)
//Section : SBAS Read Request Messages (ClassId 0x2C)
//Frame stbin_exec_waas_get_multi_ch (cid=0x2C mid=0x13)
typedef struct stbin_exec_waas_get_multi_ch {
	tU8 chan_id; /* 0 */
} stbin_exec_waas_get_multi_ch_t;
#define stbin_exec_waas_get_multi_ch_t_size_send 1

//Frame stbin_exec_waas_get_prn_to_decode (cid=0x2C mid=0x14)
	// Have no payload
//Section : SBAS Write Request Messages (ClassId 0x3C)
//Frame stbin_exec_waas_if_on_off_write_req (cid=0x3C mid=0x30)
typedef struct stbin_exec_waas_if_on_off_write_req {
	tU8 onOff; /* 0 */
} stbin_exec_waas_if_on_off_write_req_t;
#define stbin_exec_waas_if_on_off_write_req_t_size_send 1

//Frame stbin_exec_waas_if_sat_write_req (cid=0x3C mid=0x31)
typedef struct stbin_exec_waas_if_sat_write_req {
	tU8 sbasSatId; /* 0 */
} stbin_exec_waas_if_sat_write_req_t;
#define stbin_exec_waas_if_sat_write_req_t_size_send 1

//Frame stbin_exec_sbas_sat_list_req (cid=0x3C mid=0x32)
	// Have no payload
//Frame stbin_exec_sbas_periodic_backup_req (cid=0x3C mid=0x33)
typedef struct stbin_exec_sbas_periodic_backup_req {
	tU8 onOff; /* 0 */
} stbin_exec_sbas_periodic_backup_req_t;
#define stbin_exec_sbas_periodic_backup_req_t_size_send 1

//Frame stbin_exec_sbas_backup_req (cid=0x3C mid=0x34)
	// Have no payload
//Frame stbin_exec_waas_set_multi_ch_prn_write_req (cid=0x3C mid=0x35)
typedef struct stbin_exec_waas_set_multi_ch_prn_write_req {
	tU8 chan_id; /* 0 */
	tU8 sat_id; /* 1 */
	tU8 sbas_status; /* 2 */
	tU8 padding1; /* 3 */
} stbin_exec_waas_set_multi_ch_prn_write_req_t;
#define stbin_exec_waas_set_multi_ch_prn_write_req_t_size_send 3

//Frame stbin_exec_waas_set_prn_to_decode_write_req (cid=0x3C mid=0x36)
typedef struct stbin_exec_waas_set_prn_to_decode_write_req {
	tU8 sat_id; /* 0 */
	tU8 padding1; /* 1 */
	tU16 padding2; /* 2 */
} stbin_exec_waas_set_prn_to_decode_write_req_t;
#define stbin_exec_waas_set_prn_to_decode_write_req_t_size_send 1

//Frame stbin_exec_waas_autosearch_on_off_write_req (cid=0x3C mid=0x37)
typedef struct stbin_exec_waas_autosearch_on_off_write_req {
	tU8 onOff; /* 0 */
} stbin_exec_waas_autosearch_on_off_write_req_t;
#define stbin_exec_waas_autosearch_on_off_write_req_t_size_send 1

//Section : SBAS Tests Request Messages (ClassId 0x4B)
//Frame stbin_exec_waastest_req (cid=0x4B mid=0x1D)
	// Have no payload
//Section : SBAS Output Messages (ClassId 0x03)
//Section : SBAS Output Messages (ClassId 0x03)
//Frame outputprocess_sbas (cid=0x3 mid=0x33)
typedef struct outputprocess_sbas {
	tU32 iTOW; /* 0 */
	tU8 geoPrn; /* 4 */
	tS8 sys; /* 5 */
	tU8 service; /* 6 */
	tS8 cno; /* 7 */
	tU16 azimuth; /* 8 */
	tU8 elevation; /* 10 */
	tU8 cnt; /* 11 */
} outputprocess_sbas_t;
#define outputprocess_sbas_t_size_send 12

//Frame outputprocess_sbas_data (cid=0x3 mid=0x34)
typedef struct outputprocess_sbas_data {
	tS32 total; /* 0 */
	tS32 sat; /* 4 */
	tS32 iono; /* 8 */
	tS32 tropo; /* 12 */
	tS32 iod; /* 16 */
	tS32 diff_epoch; /* 20 */
	tS32 delta_range; /* 24 */
	tS32 delta_range_rate; /* 28 */
	tU8 svid; /* 32 */
	tU8 padding1; /* 33 */
	tU16 padding2; /* 34 */
} outputprocess_sbas_data_t;
#define outputprocess_sbas_data_t_size_send 33

//Section : SBAS Write Responses (ClassId 0x3C)
//Section : SBAS Read Messages Responses (ClassId 0x2C)
//Frame waas_get_multi_ch (cid=0x2C mid=0x13)
typedef struct waas_get_multi_ch {
	tU8 chan_id; /* 0 */
	tU8 sat_id; /* 1 */
	tU8 sbas_status; /* 2 */
	tU8 padding1; /* 3 */
} waas_get_multi_ch_t;
#define waas_get_multi_ch_t_size_send 3

//Frame waas_get_prn_to_decode (cid=0x2C mid=0x14)
typedef struct waas_get_prn_to_decode {
	tU8 sat_id; /* 0 */
	tU8 padding1; /* 1 */
	tU16 padding2; /* 2 */
} waas_get_prn_to_decode_t;
#define waas_get_prn_to_decode_t_size_send 1

//Section : SBAS Write Responses (ClassId 0x4B)
#define STBIN_WAAS_MAX_PAYLOAD_SIZE 33U
#ifndef STBIN_MAX_PAYLOAD_SIZE
#  error Maximal payload size must be defined when this code is reached
#endif
#if STBIN_MAX_PAYLOAD_SIZE < STBIN_WAAS_MAX_PAYLOAD_SIZE
#  error Maximal payload size must be reviewed
#endif
//Above code is automatically generated (See rep_crm/tools/stbin/generators)
