#ifndef __I4S_BK_OTA_H__
#define __I4S_BK_OTA_H__

#ifdef __cplusplus
extern "C"
{
#endif


/* OTA 升级前必备初始化，可以做一些操作约束什么条件下初始化 启动 OTA 线程*/
int i4s_bk_ota_init(void);

/* 任何时间 需要停止OTA 一些操作 */
int i4s_bk_ota_deinit(void);

/* 通知开始 WIFI OTA 操作 */
int i4s_bk_ota_start(void);









#ifdef __cplusplus
}
#endif /* End of #ifdef __cplusplus */

#endif