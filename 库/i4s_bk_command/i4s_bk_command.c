#include "i4s_bk_command.h"

#include <common/bk_include.h>

#include <os/mem.h>
#include <os/str.h>
#include <os/os.h>
#include <driver/int.h>
#include <common/bk_err.h>

#include <driver/psram.h>
#include <driver/jpeg_enc.h>
#include <components/video_transfer.h>

#if (CONFIG_FATFS)
#include "ff.h"
#include "diskio.h"
#endif

#if CONFIG_GENERAL_DMA
#include "bk_general_dma.h"
#endif

#include "bk_ef.h"

#include "cli.h"

#include "i4s/i4s_flash.h"

#define CLI_CMD_RSP_PRE 	"CMDRSP: "
#define CLI_CMD_RSP_TAIL	"\r\n"

userCache_t cache_temp = {0};
userData_t data_temp = {0};

static void i4s_help(void)
{
	bk_printf("i4s_help i4s {init/deinit userdata/usercache} | {userdata write/read <sn> <sig> <lic>} | {usercache write/read <url> <token> <ssid> <password>}\r\n");
}

/**
 * 使用教程
 * i4s init userdata
 * i4s deinit
 * i4s userdata read
 * i4s userdata write <sn> <sig> <lic>
 * i4s usercache read
 * i4s usercache write <bizuserId> <websocket_url> <https_url> <token> <ssid> <password>
 */

/**
 * TODO 保留了 init/deinit接口 但是暂未使用
 * i4s client commands  [ shell 命令回调函数 ]
 * @param pcWriteBuffer   输出缓冲区 CLI系统将打印的内容返回给终端
 * @param xWriteBufferLen 输出缓冲区的长度
 * @param argc            参数的个数
 * @param argv            数组 从 0 开始
 */
void i4s_save_commands(char *pcWriteBuffer, int xWriteBufferLen, int argc, char **argv)
{
	char *msg = CLI_CMD_RSP_SUCCEED;
	int ret = 0;

	if (argc < 2) {
		i4s_help();
		goto error;
	}

	if (os_strcmp(argv[1], "init") == 0) {
		if (argc < 3) {
			i4s_help();
			goto error;
		}
		if (os_strcmp(argv[2], "userdata") == 0) {
			os_memcpy(pcWriteBuffer, msg, os_strlen(msg));
			return ;
		} else if (os_strcmp(argv[2], "usercache") == 0) {
			os_memcpy(pcWriteBuffer, msg, os_strlen(msg));
			return ;
		} else {
			msg = WIFI_CMDMSG_ERROR_RSP;
			os_memcpy(pcWriteBuffer, msg, os_strlen(msg));
			return ;
		}
	} else if (os_strcmp(argv[1], "deinit") == 0) {
		if (argc < 3) {
			i4s_help();
			goto error;
		}
		if (os_strcmp(argv[2], "userdata") == 0) {
			os_memcpy(pcWriteBuffer, msg, os_strlen(msg));
			return ;
		} else if (os_strcmp(argv[2], "usercache") == 0) {
			os_memcpy(pcWriteBuffer, msg, os_strlen(msg));
			return ;
		} else {
			msg = WIFI_CMDMSG_ERROR_RSP;
			os_memcpy(pcWriteBuffer, msg, os_strlen(msg));
			return ;
		}
	} else if (os_strcmp(argv[1], "userdata") == 0) {
		if (argc < 3) {
			i4s_help();
			goto error;
		}
		if (os_strcmp(argv[2], "read") == 0) {
			memset(&data_temp, 0x0, sizeof(userData_t));
			ret = userData_init(&data_temp);
			if (ret) {
				msg = WIFI_CMDMSG_ERROR_RSP;
				os_memcpy(pcWriteBuffer, msg, os_strlen(msg));
				return ;
			}
			bk_printf("sn is %s, sig is %s, lic is %s\r\n", data_temp.sn, data_temp.sig, data_temp.lic);
			os_memcpy(pcWriteBuffer, msg, os_strlen(msg));
			return ;
		} else if (os_strcmp(argv[2], "write") == 0) {
			if (argc < 6) {
				i4s_help();
				goto error;
			} else {
				os_memset(&data_temp, 0x0, sizeof(userData_t));
				os_strncpy(data_temp.sn, (const char *)argv[3], sizeof(data_temp.sn));
				os_strncpy(data_temp.sig, (const char *)argv[4], sizeof(data_temp.sig));
				os_strncpy(data_temp.lic, (const char *)argv[5], sizeof(data_temp.lic));				
				ret = userData_save(&data_temp);
				if (ret) {
					msg = WIFI_CMDMSG_ERROR_RSP;
					os_memcpy(pcWriteBuffer, msg, os_strlen(msg));
					return ;
				}
				os_memcpy(pcWriteBuffer, msg, os_strlen(msg));
				return ;
			}
		} else { /* not i4s userdata read|write */
			i4s_help();
			goto error;
		}
	} else if (os_strcmp(argv[1], "usercache") == 0) {
		if (argc < 3) {
			i4s_help();
			goto error;
		}
		if (os_strcmp(argv[2], "read") == 0) {
			memset(&cache_temp, 0x0, sizeof(userCache_t));
			ret = userCache_init(&cache_temp);
			// ret = userCache_init(&cache_temp);
			if (ret) {
				msg = WIFI_CMDMSG_ERROR_RSP;
				os_memcpy(pcWriteBuffer, msg, os_strlen(msg));
				return ;
			}
			bk_printf("https_url is %s, token is %s, ssid is %s, passwork is %s\r\n", cache_temp.https_url, cache_temp.token,
				 cache_temp.ssid, cache_temp.password);
			/* BUG 下面的语句不能使用 */
			// sprintf(msg, "%s \r\n url is %s, token is %s, ssid is %s, passwd is %s %s", CLI_CMD_RSP_PRE,
			// 		cache_temp.url, cache_temp.token, cache_temp.ssid, cache_temp.password, CLI_CMD_RSP_TAIL);
			os_memcpy(pcWriteBuffer, msg, os_strlen(msg));
			return ;
		} else if (os_strcmp(argv[2], "write") == 0) {
			if (argc < 9) {
				i4s_help();
				goto error;
			} else {
				os_memset(&cache_temp, 0x0, sizeof(userCache_t));
				os_strncpy(cache_temp.bizuserId, (const char *)argv[3], sizeof(cache_temp.bizuserId));
				os_strncpy(cache_temp.websocket_url, (const char *)argv[4], sizeof(cache_temp.websocket_url));
				os_strncpy(cache_temp.https_url, (const char *)argv[5], sizeof(cache_temp.https_url));
				os_strncpy(cache_temp.token, (const char *)argv[6], sizeof(cache_temp.token));
				os_strncpy(cache_temp.ssid, (const char *)argv[7], sizeof(cache_temp.ssid));
				os_strncpy(cache_temp.password, (const char *)argv[8], sizeof(cache_temp.password));
				ret = userCache_save(&cache_temp);
				if (ret) {
					msg = WIFI_CMDMSG_ERROR_RSP;
					os_memcpy(pcWriteBuffer, msg, os_strlen(msg));
					return ;
				}
				os_memcpy(pcWriteBuffer, msg, os_strlen(msg));
				return ;
			}
		} else { /* not i4s usercache read|write */
			i4s_help();
			goto error;
		}
	} else { /* not i4s init|deinit|userdata|usercache */
		i4s_help();
		goto error;
	}

	os_memcpy(pcWriteBuffer, msg, os_strlen(msg));
	return ;

error:
	msg = CLI_CMD_RSP_ERROR;
	os_memcpy(pcWriteBuffer, msg, os_strlen(msg));
}


/* NOTE 注册一个 i4s 的命令 执行时调用 i4s_save_commands */
#define I4S_SAVE_CMD_CNT (sizeof(s_i4s_save_commands) / sizeof(struct cli_command))
static const struct cli_command s_i4s_save_commands[] = {
	{"i4s", "i4s {init/deinit userdata/usercache} | {userdata write/read <sn> <sig> <lic>} | {usercache write/read <bizuserId> <websocket_url> <https_url> <token> <ssid> <password>}", i4s_save_commands},
};

int i4s_cli_init(void)
{
	return cli_register_commands(s_i4s_save_commands, I4S_SAVE_CMD_CNT);
}
