#include "i4s_ble_net.h"
#include <common/sys_config.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <components/log.h>
#include <os/mem.h>
#include <os/str.h>
#include <os/os.h>

#include <common/bk_err.h>
#include "modules/wifi.h"
#include "components/event.h"
#include <modules/wifi_types.h>
#include "app_event.h"
#include "bk_private/bk_wifi.h"

#include "bk_genie_smart_config.h"
#include "bk_ef.h"

#include "wifi_boarding_internal.h"
#include "wifi_boarding_utils.h"

#define HEAD_MAGIC_NUMBER	0xaa55

struct i4s_ble_info i4s_ble;
struct i4s_net_info i4s_net;

#define BK_ERR_BLE_SUCCESS 	(0)
// #define WIFI_CON_SLEEP_CNT	800

#define CRC_LEN			(1)

#define DEBUG_BLE_NET	1
#if DEBUG_BLE_NET
#define BK_DEBUG bk_printf
#else
#define BK_DEBUG
#endif

static uint8_t l_g_seqNo = 0;

typedef struct ble_devinfo{ // head
	uint16_t head; // must be 0x55aa
	int8_t ver; // 版本
	int8_t seqNo; // message mark
	int8_t cid; /* command ID  look for enum Command_ID */
	int8_t reFlag; // error mark
	uint16_t len; // data len
	uint8_t data[]; // 
}__attribute__((__packed__)) ble_devinfo_t;
#define BLE_PACK_SIZE sizeof(struct ble_devinfo)

#define PACKET_HEAD_SIZE	(sizeof(struct ble_devinfo))

enum Command_ID{
	BLE_PRO_information = 1,
	BLE_PRO_notifybyself = 3,
	BLE_PRO_wifialllist = 4,
	BLE_PRO_setwifiinfo = 5,
	BLE_PRO_getwifiinfo = 9, // 0x09
	BLE_PRO_sethostinfo = 16, //0x10

};

#define HOST_PATH_SIZE 	(39)
struct host_protocol {
	char http_host[HOST_PATH_SIZE]; /* 服务器域名字符串 */
	char mqtt_host[HOST_PATH_SIZE]; /* mqtt域名 */
	char host[HOST_PATH_SIZE]; /* 保留域名 */
};
struct host_protocol *host_pro = NULL;


#define WIFI_INFO_LEN	(33)
struct sta_wifi_information {
	char ssid[WIFI_INFO_LEN];
	char passwd[WIFI_INFO_LEN];
};
struct sta_wifi_information *sta_wifi_info = NULL;

uint8_t g_i4s_sta_ssid[33] = {0};
uint8_t g_i4s_sta_passwd[33] = {0};

uint16_t local_seq = 0;
static bk_gatt_if_t i4s_gatts_if = 0;
static uint16_t i4s_conn_id = 0;
beken_timer_t ble_off_timer = {0}; /* bluetooth */

struct current_wifi_status {
	char ssid[WIFI_INFO_LEN];
	char passwd[WIFI_INFO_LEN];
	int8_t wifi_state; /* enum Notify_Status  */
}__attribute__((__packed__));

#define CURRENT_WIFI_STATUS_SIZE sizeof(struct current_wifi_status)


struct wifi_list_info {
	int8_t is_last_package;
	uint8_t ssid[WIFI_INFO_LEN];
	int8_t is_security;
	int8_t channel;
	int8_t rssi;
}__attribute__((__packed__));
#define WIFI_LIST_INFO_SIZE sizeof(struct wifi_list_info)

enum Notify_Status {
	CURRENT_IS_AP = 0,
	/* 下面是 STA 的配置 */
	STA_IS_NOT_CONG = 1, /* 无 Wifi配置 */
	STA_IS_NOT_CONN, /* 有 Wifi 配置，连接中 */
	STA_IS_CONNECTED, /* 连接上了 */

	/* NOTE 对方认准 返回设置 */
	SERVER_IS_CONNECTED,
	SERVER_IS_DISCONNECT, /* 增加 连接不上 */
	ERROR_FLAG,
};

struct Some_information {
	uint8_t product_info[10];
	uint8_t model[10];
	uint8_t sn[33];
	uint8_t mac[6];
	uint8_t version[10];
}__attribute__((__packed__));
#define INFO_PACK_SIZE sizeof(struct Some_information)

#define WIFI_CHINESE_DEBUG 0

#if USE_IDLE_RETURN
static void i4s_idle_ble_error_return(bk_gatt_if_t gatts_if, uint16_t conn_id, uint32_t trans_id, bk_gatt_rsp_t rsp)
{
	uint8_t unified_str[1] = {0};
	rsp.attr_value.value = (uint8_t *)unified_str;
	rsp.attr_value.len = 1;

	bk_ble_gatts_send_response(gatts_if, conn_id, trans_id, 0, &rsp);
}
#endif

static uint8_t get_ble_crc(uint8_t* buf, int buf_size)
{
    if (buf == NULL || buf_size <= 0) {
        bk_printf("get_ble_crc: buf is NULL or buf_size <= 0\n");
        return REMOTE_ERROR;
    }
	uint8_t crc = 0;
	int i = 0;
	for(i = 0; i < buf_size; i++) {
		crc += buf[i];
	}
	crc %= 256;
	return crc;
}

/* 计算 crc 值 加入到 数据背后 */
static uint8_t i4s_ble_net_add_crc(uint8_t* buf, int buf_size) 
{
	if (!buf || buf_size < 0) {
		return -1;
	}
	uint8_t crc = 0;
	crc = get_ble_crc(buf, buf_size);
	buf[buf_size] = crc;
	return 0;
}

/* TODO 未处理完 */
static enum Notify_Status Wifi_adaptation(int status)
{
	if (status < WIFI_LINKSTATE_STA_IDLE || status > WIFI_LINKSTATE_MAX) {
		return ERROR_FLAG;
	}
	enum Notify_Status ret = 0;
	switch (status)
	{
	case WIFI_LINKSTATE_STA_IDLE:
		ret = STA_IS_NOT_CONG;
		break;
	case WIFI_LINKSTATE_STA_CONNECTING:
		ret = STA_IS_NOT_CONN;
		break;
	case WIFI_LINKSTATE_STA_DISCONNECTED:
	case WIFI_LINKSTATE_STA_CONNECT_FAILED:
		ret = SERVER_IS_DISCONNECT;
		break;
	case WIFI_LINKSTATE_STA_CONNECTED:
	case WIFI_LINKSTATE_STA_GOT_IP:
		ret = STA_IS_CONNECTED;
		break;
	default:
		bk_printf("error status(%d)\r\n", status);
		ret = ERROR_FLAG;
	}


	return ret;
}

static int8_t security_adaptation(wifi_security_t security)
{
	int ret = 0;
	if (security < WIFI_SECURITY_NONE || security > WIFI_SECURITY_TYPE_WAPI_UNKNOWN) {
		bk_printf("somthing error\r\n");
		ret = 1;
	}

	switch (security) {
	case WIFI_SECURITY_NONE:
		ret = 0;
		break;
	default: 
		ret = 1;
	}

	return ret;
}

static int send_notify(bk_gatt_if_t gatts_if, uint16_t conn_id, uint8_t *data, uint16_t data_len) {
	int ret = 0;
	extern uint16_t *i4s_s_char_notify_handle;
	ret = bk_ble_gatts_send_indicate(gatts_if, conn_id, *i4s_s_char_notify_handle,
                                     data_len, data, 0);
	return ret;
}

static int i4s_bk_bt_notify(uint8_t *data, int len, bk_gatt_if_t gatts_if, uint16_t conn_id, uint32_t trans_id, bk_gatt_rsp_t rsp)
{
	/* 内容只有 一个字节 Notify_Status */
	if (!data || len < 0) {
		return -1;
	}

	int ret = 0;
	wifi_link_status_t link_status = {0}; /* STA connect status */
	os_memset(&link_status, 0x0, sizeof(link_status));

	struct ble_devinfo* ble_devinfo_temp = (struct ble_devinfo*)psram_malloc(sizeof(struct ble_devinfo) + 1 + CRC_LEN);
	os_memcpy(ble_devinfo_temp, data, sizeof(struct ble_devinfo));

	ret = bk_wifi_sta_get_link_status(&link_status);

	enum Notify_Status status = Wifi_adaptation(link_status.state);
	// uint8_t *send_data_temp = (uint8_t *)malloc(1);
	// ble_devinfo_temp->data = send_data_temp;
	ble_devinfo_temp->data[0] = status;
	

	ble_devinfo_temp->seqNo++;
	ble_devinfo_temp->len = 1;
	ble_devinfo_temp->reFlag = 0;

	rsp.attr_value.value = (uint8_t *)ble_devinfo_temp;
	rsp.attr_value.len = BLE_PACK_SIZE + 1 + CRC_LEN;

	i4s_ble_net_add_crc(rsp.attr_value.value, BLE_PACK_SIZE + 1);

	ret = send_notify(gatts_if, conn_id, rsp.attr_value.value, rsp.attr_value.len);
	ret = bk_ble_gatts_send_response(gatts_if, conn_id, trans_id, 0, &rsp);
	if (ret == BK_ERR_BLE_SUCCESS) {
		BK_DEBUG("rsp success\r\n");
	}

	if (ble_devinfo_temp) {
		psram_free(ble_devinfo_temp);
		ble_devinfo_temp = NULL;
	}
	return 0;
}

wifi_scan_result_t scan_result = {0};
uint8_t scan_is_over = 0;
static int scan_done_handler(void *arg, event_module_t event_module, int event_id, void *event_data)
{
	bk_wifi_scan_get_result(&scan_result);
	bk_wifi_scan_dump_result(&scan_result);

	scan_is_over = 1;

	return BK_OK;
}

static int i4s_bk_bt_wifilist(uint8_t *data, int len, bk_gatt_if_t gatts_if, uint16_t conn_id, uint32_t trans_id, bk_gatt_rsp_t rsp)
{
	if (!data || len < 0) {
		return -1;
	}

	int ret = 0, i = 0;
	uint8_t wait_seconds = 10; /* 10 seconds 还没有扫描完成，那就无所谓了 */
	// wifi_scan_config_t scan_config;

	struct ble_devinfo* ble_devinfo_temp = (struct ble_devinfo*)psram_malloc(sizeof(struct ble_devinfo) + sizeof(struct wifi_list_info) + CRC_LEN);
 	os_memcpy(ble_devinfo_temp, data, sizeof(struct ble_devinfo));

 	/* 注册扫描完成回调 */
 	bk_event_register_cb(EVENT_MOD_WIFI, EVENT_WIFI_SCAN_DONE, scan_done_handler, NULL);
 	// bk_wifi_scan_start(&scan_config);
 	bk_wifi_scan_start(NULL);


 	do {
 		rtos_thread_sleep(1);
 		if (!(wait_seconds--)) {
 			break;
 		}
 	}while(scan_is_over != 1);
 	scan_is_over = 0;

	struct wifi_list_info wifi_list[scan_result.ap_num];
	for (int i = 0; i < scan_result.ap_num; i++) {
		os_memset(&wifi_list[i], 0x0, sizeof(struct wifi_list_info));
	}

	/*  */
	for (i = 0; i < scan_result.ap_num; i++) {
		if (i != (scan_result.ap_num - 1)) {
			wifi_list[i].is_last_package = 0;
		} else {
			wifi_list[i].is_last_package = 1; /* is last */
		}

		os_memcpy(wifi_list[i].ssid, scan_result.aps[i].ssid, WIFI_INFO_LEN);

#if WIFI_CHINESE_DEBUG
		int j = 0;
		for (j = 0; j < strlen(wifi_list[i].ssid); j++) {
			bk_printf("%02x\t", wifi_list[i].ssid[j]);
		}
		bk_printf("\n");
#endif
		wifi_list[i].is_security = security_adaptation(scan_result.aps[i].security);
		wifi_list[i].channel = scan_result.aps[i].channel;
		wifi_list[i].rssi = scan_result.aps[i].rssi;

		/* 准备发送 */
		ble_devinfo_temp->seqNo++;
		ble_devinfo_temp->len = WIFI_LIST_INFO_SIZE;
		ble_devinfo_temp->reFlag = 0;
		
		memcpy(ble_devinfo_temp->data, &wifi_list[i], sizeof(struct wifi_list_info));

		rsp.attr_value.value = (uint8_t *)ble_devinfo_temp;
		rsp.attr_value.len = BLE_PACK_SIZE + WIFI_LIST_INFO_SIZE + CRC_LEN;

		i4s_ble_net_add_crc(rsp.attr_value.value, BLE_PACK_SIZE + WIFI_LIST_INFO_SIZE);

		ret = send_notify(gatts_if, conn_id, rsp.attr_value.value, rsp.attr_value.len);
		ret = bk_ble_gatts_send_response(gatts_if, conn_id, trans_id, 0, &rsp);
		if (ret == BK_ERR_BLE_SUCCESS) {
			BK_DEBUG("rsp success\r\n");
		}
	}

	if (ble_devinfo_temp) {
		psram_free(ble_devinfo_temp);
		ble_devinfo_temp = NULL;
	}
	bk_wifi_scan_free_result(&scan_result);
	return ret;
}

extern bk_err_t agora_stop(void);
static int i4s_bk_bt_setwifiinfo(uint8_t *data, int len, bk_gatt_if_t gatts_if, uint16_t conn_id, uint32_t trans_id, bk_gatt_rsp_t rsp)
{
	if (!data || len < 0) {
		return -1;
	}

	int ret = 0;
	
	struct ble_devinfo* ble_devinfo_temp = (struct ble_devinfo*)data;

	struct sta_wifi_information *sta_wifi_information_temp = (struct sta_wifi_information*)(ble_devinfo_temp->data);
	if (!sta_wifi_info) {
		sta_wifi_info = (struct sta_wifi_information *)malloc(sizeof(struct sta_wifi_information));
		if (!sta_wifi_info) {
			return MALLOC_ERROR;
		}
	}
	os_memcpy(sta_wifi_info, sta_wifi_information_temp, sizeof(struct sta_wifi_information));

#if WIFI_CHINESE_DEBUG
	int i = 0;
	bk_printf("let connect wifi ssid is :\r\n");
	for (i = 0; i < strlen(sta_wifi_info->ssid); i++) {
		bk_printf("%02x\t", sta_wifi_info->ssid[i]);
	}
	bk_printf("\n");
	bk_printf("let connect wifi password is :\r\n");
	for (i = 0; i < strlen(sta_wifi_info->passwd); i++) {
		bk_printf("%02x\t", sta_wifi_info->passwd[i]);
	}
	bk_printf("\n");
#endif

	BK_DEBUG("set wifi ssid is %s\r\n", sta_wifi_info->ssid);
	BK_DEBUG("set wifi passwd is %s\r\n", sta_wifi_info->passwd);

	os_strcpy((char *)g_i4s_sta_ssid, (const char*)sta_wifi_info->ssid);
	os_strcpy((char *)g_i4s_sta_passwd, (const char*)sta_wifi_info->passwd);

	ble_devinfo_temp->seqNo++;
	ble_devinfo_temp->len = 0;
	ble_devinfo_temp->reFlag = 0;

	rsp.attr_value.value = (uint8_t *)ble_devinfo_temp;
	rsp.attr_value.len = BLE_PACK_SIZE + CRC_LEN;

	i4s_ble_net_add_crc(rsp.attr_value.value, BLE_PACK_SIZE);

	ret = send_notify(gatts_if, conn_id, rsp.attr_value.value, rsp.attr_value.len);
	ret = bk_ble_gatts_send_response(gatts_if, conn_id, trans_id, 0, &rsp);
	if (ret == BK_ERR_BLE_SUCCESS) {
		BK_DEBUG("rsp success\r\n");
	}

	app_event_send_msg(APP_EVT_NETWORK_PROVISIONING, 0);
    network_reconnect_stop_timeout_check(); // 关闭配网超时检测
	agora_stop(); 
    bk_wifi_sta_stop();

    demo_sta_app_init((char*)sta_wifi_info->ssid, sta_wifi_info->passwd);

    return ret;
}

/* NOTE this variable can not be inside,there is not enough space to run,so put it outside */
/* NOTE the func bk_wifi_sta_get_link_status is abnormal */
uint8_t ble_devinfo_temp_00[BLE_PACK_SIZE + CURRENT_WIFI_STATUS_SIZE + CRC_LEN] = {0};
static int i4s_bk_bt_getwifiinfo(uint8_t *data, int len, bk_gatt_if_t gatts_if, uint16_t conn_id, uint32_t trans_id, bk_gatt_rsp_t rsp)
{
	if (!data || len < 0) {
		return LOCAL_ERROR;
	}
	int ret = 0;
	wifi_link_status_t link_status = {0}; /* STA connect status */
	os_memset(&link_status, 0x0, sizeof(link_status));

	struct ble_devinfo* ble_devinfo_temp_0 = (struct ble_devinfo* )ble_devinfo_temp_00;

	os_memset(ble_devinfo_temp_0, 0x0, BLE_PACK_SIZE + CURRENT_WIFI_STATUS_SIZE + CRC_LEN);
	os_memcpy(ble_devinfo_temp_0, data, BLE_PACK_SIZE);

	struct current_wifi_status cur_wifi_info;
	os_memset(&cur_wifi_info, 0x00, CURRENT_WIFI_STATUS_SIZE);

	bk_printf("ready to get wifi info\r\n");
	/* TODO 此函数 并无法正常获取ssid和pwd，但是小程序暂且不需要这个数据 暂议~ */
	ret = bk_wifi_sta_get_link_status(&link_status);
	if (ret == BK_OK) { 
		bk_printf("get wifi info success\r\n");
		bk_printf("==================\r\n");
		bk_printf("state is %d\r\n", link_status.state);
		bk_printf("rssi is %d\r\n", link_status.rssi);
		bk_printf("ssid is %s\r\n", link_status.ssid); // TODO 
		bk_printf("password is %s\r\n", link_status.password);
		bk_printf("channel is %d\r\n", link_status.channel);
		bk_printf("==================\r\n");

		/**/
		enum Notify_Status status = Wifi_adaptation(link_status.state);
		if (status == STA_IS_CONNECTED) { // NOTE sdk func can not get normal,then use self way
			// os_strncpy((char *)cur_wifi_info.ssid, link_status.ssid, WIFI_INFO_LEN);
			// os_strncpy((char *)cur_wifi_info.passwd, link_status.password, WIFI_INFO_LEN);
			os_strncpy((char*)cur_wifi_info.ssid, g_i4s_sta_ssid, strlen(g_i4s_sta_ssid));
			os_strncpy((char*)cur_wifi_info.ssid, g_i4s_sta_passwd, strlen(g_i4s_sta_passwd));
			cur_wifi_info.wifi_state = SERVER_IS_CONNECTED; /* NOTE 对方等待这个恢复 */
		} else if (sta_wifi_info) { /* 有Wifi配置，只是没有连接上 */
			os_strncpy((char *)cur_wifi_info.ssid, sta_wifi_info->ssid, WIFI_INFO_LEN);
			os_strncpy((char *)cur_wifi_info.passwd, sta_wifi_info->passwd, WIFI_INFO_LEN);
			if (status == SERVER_IS_DISCONNECT) {
				cur_wifi_info.wifi_state = SERVER_IS_DISCONNECT;
			} else 
				cur_wifi_info.wifi_state = STA_IS_NOT_CONN;
		} else if (!sta_wifi_info) {
			cur_wifi_info.wifi_state = STA_IS_NOT_CONG;
		} /* TODO 这里暂且没有处理是否为AP模式 还是 连接上 服务器 */

		bk_printf("now state is %d\r\n", cur_wifi_info.wifi_state);
		os_memcpy(ble_devinfo_temp_00 + BLE_PACK_SIZE, &cur_wifi_info, CURRENT_WIFI_STATUS_SIZE);

		ble_devinfo_temp_0->seqNo++;
		ble_devinfo_temp_0->len = CURRENT_WIFI_STATUS_SIZE;
		ble_devinfo_temp_0->reFlag = 0;

		local_seq = ble_devinfo_temp_0->seqNo;

		rsp.attr_value.value = (uint8_t *)ble_devinfo_temp_00;
		rsp.attr_value.len = BLE_PACK_SIZE + CURRENT_WIFI_STATUS_SIZE + CRC_LEN;

		i4s_ble_net_add_crc(rsp.attr_value.value, BLE_PACK_SIZE + CURRENT_WIFI_STATUS_SIZE);

		bk_printf("crc is %02x\r\n", ble_devinfo_temp_00[BLE_PACK_SIZE + CURRENT_WIFI_STATUS_SIZE + CRC_LEN - 1]);
		i4s_gatts_if = gatts_if;
		i4s_conn_id = conn_id;

		ret = send_notify(gatts_if, conn_id, rsp.attr_value.value, rsp.attr_value.len);
		ret = bk_ble_gatts_send_response(gatts_if, conn_id, trans_id, 0, &rsp);
		if (ret == BK_ERR_BLE_SUCCESS) {
			BK_DEBUG("rsp success\r\n");
		}
	}

	return ret;
}

/* NOTE save room can two into one as ble_devinfo_temp_00 */
uint8_t g_infor[PACKET_HEAD_SIZE + INFO_PACK_SIZE + CRC_LEN] = {0};
static int i4s_bk_bt_getinformation(uint8_t *data, int len, bk_gatt_if_t gatts_if, uint16_t conn_id, uint32_t trans_id, bk_gatt_rsp_t rsp)
{
	if (!data) {
		return LOCAL_ERROR;
	}
	int ret = 0;

	os_memset(g_infor, 0x0, PACKET_HEAD_SIZE + INFO_PACK_SIZE + CRC_LEN);
	struct ble_devinfo* ble_devinfo_temp = (struct ble_devinfo*)g_infor;

	memcpy(g_infor, data, PACKET_HEAD_SIZE);

	ble_devinfo_temp->seqNo++;
	ble_devinfo_temp->len = INFO_PACK_SIZE;
	ble_devinfo_temp->reFlag = 0;

	/* NOTE put fack info */
	struct Some_information* info = (struct Some_information*)(g_infor + PACKET_HEAD_SIZE);
	os_strncpy((char *)info->product_info, "I4season", sizeof(info->product_info));
	os_strncpy((char *)info->model, "Ipc", sizeof(info->model));
	os_strncpy((char *)info->sn, "00c562b4da8066b98f6e2fe8f57aac67", sizeof(info->sn)); // 12345678 已经使用过
	os_strncpy((char *)info->mac, "ABCDEF", sizeof(info->mac));
	os_strncpy((char *)info->version, "0.0.1", sizeof(info->version));


	rsp.attr_value.value = (uint8_t *)g_infor;
	rsp.attr_value.len = PACKET_HEAD_SIZE + INFO_PACK_SIZE + CRC_LEN;

	i4s_ble_net_add_crc(rsp.attr_value.value, PACKET_HEAD_SIZE + INFO_PACK_SIZE);
	bk_printf("crc is %02x\r\n", g_infor[PACKET_HEAD_SIZE + INFO_PACK_SIZE + CRC_LEN - 1]);

	ret = send_notify(gatts_if, conn_id, rsp.attr_value.value, rsp.attr_value.len);
	ret = bk_ble_gatts_send_response(gatts_if, conn_id, trans_id, 0, &rsp);
	if (ret == BK_ERR_BLE_SUCCESS) {
		BK_DEBUG("rsp success\r\n");
	}
	return ret;
}

static int i4s_bk_bt_sethostinfo(uint8_t *data, int len, bk_gatt_if_t gatts_if, uint16_t conn_id, uint32_t trans_id, bk_gatt_rsp_t rsp)
{
	if (!data || len < 0) {
		return LOCAL_ERROR;
	}
	int ret = 0;

	struct ble_devinfo* ble_devinfo_temp = (struct ble_devinfo*)data;

	struct host_protocol *host_pro_temp = (struct host_protocol*)(ble_devinfo_temp->data);
	if (!host_pro) {
		host_pro = (struct host_protocol *)malloc(sizeof(struct host_protocol));
		if (!host_pro) {
			return MALLOC_ERROR;
		}
	}
	os_memcpy(host_pro, host_pro_temp, sizeof(struct host_protocol));

	BK_DEBUG("http_host is %s\r\n", host_pro->http_host); 
	BK_DEBUG("mqtt_host is %s\r\n", host_pro->mqtt_host);
	BK_DEBUG("host is %s\r\n", host_pro->host);

	ble_devinfo_temp->seqNo++;
	ble_devinfo_temp->len = 0;
	ble_devinfo_temp->reFlag = 0;

	rsp.attr_value.value = (uint8_t *)ble_devinfo_temp;
	rsp.attr_value.len = BLE_PACK_SIZE + CRC_LEN;

	i4s_ble_net_add_crc(rsp.attr_value.value, BLE_PACK_SIZE);

	ret = send_notify(gatts_if, conn_id, rsp.attr_value.value, rsp.attr_value.len);
	ret = bk_ble_gatts_send_response(gatts_if, conn_id, trans_id, 0, &rsp);
	if (ret == BK_ERR_BLE_SUCCESS) {
		BK_DEBUG("rsp success\r\n");
	}
	return ret;
}

int i4s_notify_wifi_status(void)
{
	if (!i4s_gatts_if && !i4s_conn_id) {
		return 0;
	}
	int ret = 0;
	bk_gatt_rsp_t rsp = {0};
	wifi_link_status_t link_status = {0}; /* STA connect status */
	os_memset(&link_status, 0x0, sizeof(link_status));

	struct ble_devinfo* ble_devinfo_temp = (struct ble_devinfo*)malloc(BLE_PACK_SIZE + CURRENT_WIFI_STATUS_SIZE + CRC_LEN);
	if (!ble_devinfo_temp) {
		return MALLOC_ERROR;
	}
	os_memset(ble_devinfo_temp, 0x0, BLE_PACK_SIZE);

	struct current_wifi_status cur_wifi_info;
	os_memset(&cur_wifi_info, 0x00, CURRENT_WIFI_STATUS_SIZE);

	ret = bk_wifi_sta_get_link_status(&link_status);
	if (ret == BK_OK) {
		enum Notify_Status status = Wifi_adaptation(link_status.state);
		if (status == STA_IS_CONNECTED) {
			os_memcpy(cur_wifi_info.ssid, link_status.ssid, sizeof(link_status.ssid));
			os_memcpy(cur_wifi_info.passwd, link_status.password, sizeof(link_status.password));
			cur_wifi_info.wifi_state = SERVER_IS_CONNECTED; /* NOTE 对方等待这个恢复 */
		} else if (sta_wifi_info) { /* 有Wifi配置，只是没有连接上 */
			os_memcpy(cur_wifi_info.ssid, sta_wifi_info->ssid, WIFI_INFO_LEN);
			os_memcpy(cur_wifi_info.passwd, sta_wifi_info->passwd, WIFI_INFO_LEN);
			if (status == SERVER_IS_DISCONNECT) {
				cur_wifi_info.wifi_state = SERVER_IS_DISCONNECT;
			} else 
				cur_wifi_info.wifi_state = STA_IS_NOT_CONN;
		} else if (!sta_wifi_info) {
			cur_wifi_info.wifi_state = STA_IS_NOT_CONG;
		} /* TODO 这里暂且没有处理是否为AP模式 还是 连接上 服务器 */

		os_memcpy(ble_devinfo_temp + BLE_PACK_SIZE, (const void *)&cur_wifi_info, CURRENT_WIFI_STATUS_SIZE);

		ble_devinfo_temp->seqNo = ++local_seq;
		ble_devinfo_temp->len = CURRENT_WIFI_STATUS_SIZE;
		ble_devinfo_temp->reFlag = 0;

		rsp.attr_value.value = (uint8_t *)ble_devinfo_temp;
		rsp.attr_value.len = BLE_PACK_SIZE + CURRENT_WIFI_STATUS_SIZE + CRC_LEN;

		i4s_ble_net_add_crc(rsp.attr_value.value, BLE_PACK_SIZE + CURRENT_WIFI_STATUS_SIZE);

		ret = send_notify(i4s_gatts_if, i4s_conn_id, rsp.attr_value.value, rsp.attr_value.len);
		if (ret == BK_ERR_BLE_SUCCESS) {
			BK_DEBUG("rsp success\r\n");
		}
	}

	if (ble_devinfo_temp) {
		free(ble_devinfo_temp);
	}

	return ret;
}

static void ble_timer_cb(void *arg)
{
	if (i4s_ble.ble_is_connected) {
		bk_printf("ble timer run once\r\n");
		i4s_notify_wifi_status();
		rtos_reload_timer(&ble_off_timer);
	}
}

void i4s_start_ble_timer(void)
{
	int ret = -1;
	if (ble_off_timer.handle == NULL) {
		ret = rtos_init_timer(&ble_off_timer, 1500, ble_timer_cb, NULL);
		rtos_start_timer(&ble_off_timer);
	}
	if (ret == 0) {
		bk_printf("ble timer start success\r\n");
	}
}

void i4s_safe_stop_ble_timer(void)
{
	int ret = -1;
	if (ble_off_timer.handle != NULL) {
		rtos_stop_timer(&ble_off_timer);
		ret = rtos_deinit_timer(&ble_off_timer);
		i4s_notify_wifi_status();
	}
	if (ret == 0) {
		bk_printf("ble timer stop success\r\n");
	}
}


int i4s_ble_proc_data(uint8_t* data, int len, bk_gatt_if_t gatts_if, uint16_t conn_id, uint32_t trans_id, bk_gatt_rsp_t rsp) 
{
    uint8_t crc = 0;
    struct ble_devinfo *head = NULL;
	int ret = 0;

    if (data == NULL || len <= 0) {
        bk_printf("data or len error\r\n");
        return REMOTE_ERROR; // TODO 
    }

	head = (struct ble_devinfo*)data;
	if (head->head != HEAD_MAGIC_NUMBER) {
		bk_printf("head is not correct(head->head = %x),the right is %x\r\n", head->head, HEAD_MAGIC_NUMBER);
#if USE_IDLE_RETURN
		i4s_idle_ble_error_return(gatts_if, conn_id, trans_id, rsp);
#endif
		return MAGIC_WRROR;
	} else {
		BK_DEBUG("head is correct\r\n");
	}
	
    /*crc check */
    crc = get_ble_crc(data, len - CRC_LEN); //
    // bk_printf("recv clac crc is %d\r\n", crc);
    if (crc == data[len - CRC_LEN]) { // crc check ok
        BK_DEBUG("crc check ok\r\n");
    } else {
        bk_printf("crc error (local crc is %d,remote crc is %d)\r\n", crc, data[len - 1]);
#if USE_IDLE_RETURN
        i4s_idle_ble_error_return(gatts_if, conn_id, trans_id, rsp);
#endif
        head->reFlag = CRC_ERROR;
        goto EXIT_0; /* NOTE crc错误 暂不搭理 */
    }
    len = len - CRC_LEN; // 除去了crc的长度

    bk_printf("head->cid is %d\r\n", head->cid);
	switch (head->cid) {
        case BLE_PRO_notifybyself: /* 这个函数是主动调用的 */ 
			ret = i4s_bk_bt_notify(data, len, gatts_if, conn_id, trans_id, rsp);
			break;
		case BLE_PRO_wifialllist: 
			ret = i4s_bk_bt_wifilist(data, len, gatts_if, conn_id, trans_id, rsp);
			break;
		case BLE_PRO_setwifiinfo:
			ret = i4s_bk_bt_setwifiinfo(data, len, gatts_if, conn_id, trans_id, rsp);
			break;
		case BLE_PRO_getwifiinfo: //
			ret = i4s_bk_bt_getwifiinfo(data, len, gatts_if, conn_id, trans_id, rsp);
			break;
		case BLE_PRO_sethostinfo:
			ret = i4s_bk_bt_sethostinfo(data, len, gatts_if, conn_id, trans_id, rsp);
			break;
		case BLE_PRO_information:
			ret = i4s_bk_bt_getinformation(data, len, gatts_if, conn_id, trans_id, rsp);
			break;
        default:
        	bk_printf("no right cid(%d)\r\n",head->cid);
            break;
    }
	return ret;
EXIT_0:
	return -1;
}


/* 注意 是已经连接上WIFI了才调用的这个函数 ！！！ */
/* 是通过APP配网的 保存配网信息 */
uint8_t i4s_save_sta_info(void)
{
	int ret = 0;
	if (strlen((const char*)g_i4s_sta_ssid) && strlen((const char *)g_i4s_sta_passwd)) {
		BK_FAST_CONNECT_D info = {0};

		info.flag |= 0x71l;
		os_strcpy((char *)info.sta_ssid, (const char *)g_i4s_sta_ssid);
		os_strcpy((char *)info.sta_pwd, (const char *)g_i4s_sta_passwd);

		BK_DEBUG("save ssid is %s\r\n", info.sta_ssid);
		BK_DEBUG("save passwd is %s\r\n", info.sta_pwd);

		if (!sta_wifi_info) {	
			sta_wifi_info = (struct sta_wifi_information *)malloc(sizeof(struct sta_wifi_information));
			if (!sta_wifi_info) {
				return 1;
			}
		}

		os_memcpy(sta_wifi_info->ssid, g_i4s_sta_ssid, WIFI_INFO_LEN);
		os_memcpy(sta_wifi_info->passwd, g_i4s_sta_passwd, WIFI_INFO_LEN);

#if (CONFIG_EASY_FLASH && CONFIG_EASY_FLASH_V4)
		/* NOTE 这里和 原厂的配网是使用的同一个 键值对 */
		ret = bk_set_env_enhance("d_network_id", (void *)&info, sizeof(BK_FAST_CONNECT_D));
		if (ret == 0) {
			bk_printf("save success\r\n");
		}
#endif
	}
	return ret;
}


/* notify 使用 */
/* need_confirm : */
int i4s_ble_net_indicate(bk_gatt_if_t gatts_if, uint16_t conn_id, uint16_t attr_handle,
                                     uint16_t value_len, uint8_t *value, bool need_confirm)
{

	int ret = 0;
	uint8_t *send_data = NULL;
	wifi_link_status_t link_status = {0}; /* STA connect status */
	os_memset(&link_status, 0x0, sizeof(link_status));

	ret = bk_wifi_sta_get_link_status(&link_status);

	enum Notify_Status status = Wifi_adaptation(link_status.state);
	char data_temp[2] = {0}; 
	data_temp[0] = status;
	data_temp[1] = '\0';

	struct ble_devinfo *ble_devinfo_temp = NULL;
	if (!ble_devinfo_temp) {
		/* data len is 1, crc len is 1,so add 2 */
		ble_devinfo_temp = (struct ble_devinfo*)malloc(sizeof(struct ble_devinfo) + 2);
		if (!ble_devinfo_temp) {
			bk_printf("malloc failed\r\n");
			return MAGIC_WRROR;
		}
	}

	ble_devinfo_temp->head = HEAD_MAGIC_NUMBER;
	ble_devinfo_temp->ver = 1;
	ble_devinfo_temp->seqNo = l_g_seqNo++;
	ble_devinfo_temp->cid = BLE_PRO_notifybyself;
	ble_devinfo_temp->reFlag = 0;
	ble_devinfo_temp->len = 1;
	ble_devinfo_temp->data[0] = data_temp[0];

	send_data = (uint8_t *)ble_devinfo_temp;

	get_ble_crc(send_data, BLE_PACK_SIZE + 1);

	ret = bk_ble_gatts_send_indicate(gatts_if, conn_id, attr_handle,
                                     BLE_PACK_SIZE + 1 + CRC_LEN, send_data, need_confirm);
	if (ble_devinfo_temp) {
		free(ble_devinfo_temp);
		ble_devinfo_temp = NULL;
	}
	return ret;
}


