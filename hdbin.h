/*
	AllyStar 2017
*/

//extern nmea_inout_t NMEA_read_fun;
void hdbin_input_processing(void);
void hdbin_output_processing(void);

//entry point module
void hdbin_read_binary_msg(tUChar *);

//CFG
hdbin_status_t hd_decode_cfg_req(tU16, tUChar *, const hdbin_req_msg_parms *);

typedef struct __hdbin_req_msg_parms {
  tUChar *  out_buf;
  tUChar    group_Id;
  tUChar    sub_Id;
} hdbin_req_msg_parms;

typedef struct __hdbin_chkSum_t {
  tU8    cs_0;
  tU8    cs_1;
} hdbin_chkSum_t;

typedef tU8	hdbin_status_t;

//Start Sequence
#define SYNC_BYTE_1	0xF1U
#define SYNC_BYTE_2	0xD9U

//Status
#define HDBIN_FAILED	0U
#define HDBIN_OK        1U
#define HDBIN_NOTFOUND	2U

//TODO
#define HDBIN_GENERAL_ERROR_UNKNOW_ID	0x00

//Message ID - Group ID
#define HDBIN_GROUP_ID_CFG 0x06
#define HDBIN_GROUP_ID_NAV 0x01
#define HDBIN_GROUP_ID_ACK 0x05
#define HDBIN_GROUP_ID_MON 0x0A
#define HDBIN_GROUP_ID_AID 0x0B

//Message ID - Sub ID
#define HDBIN_SUB_ID_SIMPLERST 0x40
