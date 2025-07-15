#ifndef __I4_BK_FLASH1_H__
#define __I4_BK_FLASH1_H__

#include <stdio.h>
#include <stdint.h>
#include "i4s_config.h"
#define USE_EASYFLASH	1  /* NOTE 是否采用 easy_flash 的方式存储 否即为直接指定存储地址 */



#ifdef __cplusplus
extern "C" {
#endif 

#define INTERRUPT_SUPPORT	(0) /* 需要在中断内开始的话，需要先初始化 init */

/* NOTE 根据 flash_driver.h 中描述 一个扇区 为 4K 所以下面两个结构体各占长度为 4K */
// #define FLASH_SECTOR_SIZE                0x1000 /* each sector has 4K bytes */

 typedef struct __userData{	  //
	 char sn[64];
	 char sig[64];
	 char lic[64];
	 uint32_t crc;
 }__attribute__((__packed__))userData_t; 
 typedef struct __userCache{
 	char bizuserId[32];//websocket url
	 char websocket_url[80];//websocket url
	 char https_url[80];//websocket url
	 char token[80]; //websockt的tocken
	 char ssid[33];
	 char password[64];   
	 char revert[128];
	 uint32_t crc;
 }__attribute__((__packed__))userCache_t;
 
typedef struct __userRunCache{ //
	unsigned short keep_alive;//心跳包时间
	unsigned char websocket_state;
	unsigned char netstatus;
	unsigned char rebind;
	int timeout;
	char id[64];
	char tts_status;
}userRunCache;

 


int userData_init(userData_t *data);
int userCache_init(userCache_t *cdata);

int userCache_reload(userCache_t *cdata);

int userData_save(userData_t *data);
int userCache_save(userCache_t *cdata);



#ifdef __cplusplus
}
#endif /* End of #ifdef __cplusplus */

#endif /* __VIDEO_ALG_PTS_V1_0_H__ */

