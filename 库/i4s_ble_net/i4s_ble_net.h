#ifndef __I4S_BLE_NET_H__
#define __I4S_BLE_NET_H__

#include <stdint.h>

#include "components/bluetooth/bk_dm_bluetooth_types.h"
#include "components/bluetooth/bk_dm_gap_ble_types.h"
#include "components/bluetooth/bk_dm_gap_ble.h"
#include "components/bluetooth/bk_dm_gatt_types.h"
#include "components/bluetooth/bk_dm_gatts.h"

#define USE_IDLE_RETURN		1

enum ERROR_TYPE
{
	LOCAL_ERROR = -1, /*本地运行异常错误 */
	CRC_ERROR = -2, /* crc校验值不对错误*/
	MAGIC_WRROR = -3, /*magic check different*/
	MALLOC_ERROR = -4, /*本地申请空间失败*/
	REMOTE_ERROR = -5, /*远程设置有误*/
	OTA_LEN_ERROR = -6, /*ota文件长度不对*/
	OTA_FRAME_ERROR = -7, /*ota文件帧不对*/
	OTA_THREAD_ERROR = -8, /*ota线程启动失败*/
	OTA_FAILED = -9, /*ota失败,如果依旧需要ota，需要从头开始走ota流程*/
};

struct i4s_ble_info {
	uint8_t ble_is_connected:1;
	uint8_t ble_is_open:1;

	uint8_t reserve:6;
}__attribute__((packed));
extern struct i4s_ble_info i4s_ble;

struct i4s_net_info {
	uint8_t net_is_connected:1; /* 目前为 STA 模式的是否已连接 */
	uint8_t net_is_open:1; /* TODO wifi开启否，模式等 暂不做涉及 */ 

	uint8_t reserve:6;
}__attribute__((packed));
extern struct i4s_net_info i4s_net;

/* NOTE 外放 因为发现并无法知道已连接的wifi的讯息(ssid可以，passwd不可以) */
extern uint8_t g_i4s_sta_ssid[33];
extern uint8_t g_i4s_sta_passwd[33];

int i4s_notify_wifi_status(void);

int i4s_ble_proc_data(uint8_t* data, int len, bk_gatt_if_t gatts_if, uint16_t conn_id, uint32_t trans_id, bk_gatt_rsp_t rsp);

int i4s_ble_net_indicate(bk_gatt_if_t gatts_if, uint16_t conn_id, uint16_t attr_handle,
                                     uint16_t value_len, uint8_t *value, bool need_confirm);


void i4s_start_ble_timer(void);
void i4s_safe_stop_ble_timer(void);
#endif