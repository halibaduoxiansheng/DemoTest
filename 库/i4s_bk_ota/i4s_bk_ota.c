#include "i4s_bk_ota.h"
#include "i4s_ble_net.h"

#include "ota.h"
#include "stdio.h"
#include <os/os.h>
#include "app_event.h"
#include "bk_ota_private.h"
#include "media_app.h"
#include "media_evt.h"

enum I4S_OTA_STATE {
	OTA_PREPARE, /* 准备阶段 -> 开始讯号 -> 网络 */
	OTA_START,
	OTA_DOING, /* 升级中 */
	OTA_END,
	OTA_MAX,
};

enum URL_TYPE {
	IS_HTTP,
	IS_HTTPS,
	IS_MAX,
};

// http://47.106.242.237:80/app_pack.rbl  http://www.halibaduo.cn:80/app_pack.rbl
#define I4S_OTA_URL "http://www.halibaduo.cn:80/app_pack.rbl" 

static beken_thread_t i4s_ota_th_hd = NULL;
static beken_semaphore_t i4s_bk_ota_init_sem = NULL;
static uint8_t i4s_bk_ota_inited = 0;

static uint8_t start_flag = 0; /* */
static uint8_t ota_doing = 0; /* 是否升级中标识 */

enum I4S_OTA_STATE i4s_ota_state = {0};


static uint8_t ota_url_check(char *url)
{
	if (strncmp(url, "https://", 8) == 0) {
        return IS_HTTPS;
    } else if (strncmp(url, "http://", 7) == 0) {
        return IS_HTTP;
    } else {
    	return IS_MAX;
    }
}

/* ota 发起升级包前的准备工作 -> 例如LVGL显示 */
static int i4s_ota_prepare(void)
{
	/* NOTE do work after wack up */
	bk_printf("%s start\r\n", __func__);
	app_event_send_msg(APP_EVT_OTA_START, 0);
	media_send_msg_sync(EVENT_LVCAM_LVGL_OTA, 0);

	return 0;
}

static uint8_t ota_event_callback(evt_ota event_param)
{

    switch(event_param)
    {
        case EVT_OTA_START:
        	bk_printf("i4s ota start\r\n");
            app_event_send_msg(APP_EVT_OTA_START, 0); /* 通知停止定时关机函数 */
            break;
        case EVT_OTA_FAIL:
        	bk_printf("i4s ota failed\r\n");
        	i4s_ota_state = OTA_PREPARE;
            app_event_send_msg(APP_EVT_OTA_FAIL, 0);
            break;  
        case EVT_OTA_SUCCESS:
        	bk_printf("i4s ota success\r\n");
        	i4s_ota_state = OTA_END;
            app_event_send_msg(APP_EVT_OTA_SUCCESS, 0);
            break;
        default :
            break;
    }
    return 0;
}

extern int bk_https_ota_download(const char *url);
static uint8_t i4s_bk_ota_func(void)
{
	int ret = 0;
	ret = ota_url_check(I4S_OTA_URL);
	if (ret == IS_HTTPS) {
		bk_printf("is https\r\n");
		ret = bk_https_ota_download(I4S_OTA_URL);
	} else if (ret == IS_HTTP) {
		bk_printf("is http\r\n");
		ret = bk_http_ota_download(I4S_OTA_URL);
	} else {
		return 1;
	}

	return ret;
}

/* NOTE thread func */
static void i4s_ota_thread(void *arg)
{
	uint8_t ret = 0;
	i4s_bk_ota_inited = 1;
	rtos_set_semaphore(&i4s_bk_ota_init_sem);

	while(1) {
		switch (i4s_ota_state) {
		case OTA_PREPARE:
			if (start_flag && i4s_net.net_is_connected) {
				i4s_ota_state = OTA_START;
			} else {
				rtos_delay_milliseconds(500);
			}
			break;
		case OTA_START:
			if (start_flag && i4s_net.net_is_connected) {
				i4s_ota_prepare(); /* NOTE 不论结果，继续升级 */
				i4s_ota_state = OTA_DOING;
			} else {
				i4s_ota_state = OTA_PREPARE;
			}
			break;
		case OTA_DOING:
				if (ota_doing == 0) {
					ota_doing = 1;
					ret = i4s_bk_ota_func();
					if (ret != 0) {  
						ota_doing = 0;
						bk_printf("ota failed,please check\r\n");
						i4s_ota_state = OTA_PREPARE;
					}
				}
			break;
		case OTA_END:
				bk_printf("ota success 0\r\n");
				bk_printf("ota success 1\r\n");
				bk_printf("ota success 2\r\n");
				bk_reboot();
			break;
		case OTA_MAX:
			bk_printf("wrong ota_state\r\n");
			i4s_ota_state = OTA_PREPARE;
			break;
		default:
			bk_printf("i4s ota no match case\r\n");
			goto exit;
		}
	}

exit:
	bk_printf("ota thread meet error\r\n");
	i4s_bk_ota_deinit();

	i4s_ota_th_hd = NULL;

	bk_printf("delete i4s_ota_thread complete\r\n");
	rtos_delete_thread(NULL);	
}

int i4s_bk_ota_init(void)
{
	int ret = 0;
	if (i4s_bk_ota_inited != 0) {
		bk_printf("i4s_bk_ota_init already inited\r\n");
		return 0;
	}

	ota_event_callback_register(ota_event_callback);

	ret = rtos_init_semaphore(&i4s_bk_ota_init_sem, 1); /* NOTE ensure thread safe semaphore */
	if (ret != 0)
	{
		bk_printf("create i4s_bk_ota_init_sem failed\n");
		goto exit;
	}

	ret = rtos_create_thread(&i4s_ota_th_hd,
             BEKEN_DEFAULT_WORKER_PRIORITY - 1,
             "i4s_ota",
             (beken_thread_function_t)i4s_ota_thread,
             5120,
             NULL);

	if (ret != 0)
	{
		bk_printf("create i4s ota thread fail\r\n");
		goto exit;
	}

	rtos_get_semaphore(&i4s_bk_ota_init_sem, BEKEN_WAIT_FOREVER);

	return 0;

exit:
	i4s_bk_ota_deinit();

	return ret;
}


int i4s_bk_ota_deinit(void)
{
	if (i4s_bk_ota_inited != 1) {
		bk_printf("not need deinit\r\n");
		return 0;
	}

	if (i4s_bk_ota_init_sem)
	{
		rtos_deinit_semaphore(&i4s_bk_ota_init_sem);
		i4s_bk_ota_init_sem = NULL;
	}

	rtos_delete_thread(&i4s_ota_th_hd);

	i4s_bk_ota_inited = 0;
	start_flag = 0;
	return 0;
}


int i4s_bk_ota_start(void)
{
	if (i4s_bk_ota_inited != 1) {
		bk_printf("ota thread not start\r\n");
		return -1;
	}
	start_flag = 1;
	return 0;
}