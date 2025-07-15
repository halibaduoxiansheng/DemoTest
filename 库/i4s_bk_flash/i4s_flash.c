#include "i4s_flash.h"
// #include "BkDriverFlash.h"
#include "driver/flash.h"
#include <driver/flash_types.h>
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <os/os.h>
/* NOTE 特意从原本 user_config 区域 取出8k 空间存储 分别从 0x7FA000 开始 和 0x7FB000 开始 */

#if USE_EASYFLASH
#include "bk_ef.h"
#endif

#if USE_EASYFLASH
#define USERDATA_KEY	"userdata"
#define USERCACHE_KEY	"usercache"
#endif

#define DEBUG_OPEN 1  /* 打印测试打开 */
#if DEBUG_OPEN
 #define FLASH_DEBUG bk_printf
#else
 #define FLASH_DEBUG 
#endif

#define USER_DATA_ADDR	0x7fa800
#define USER_CATCH_ADDR	0X7fb000

#define CRC_ERROR_VALUE	0xFFFFFFFF

#define FLASH_PAGE_SIZE	512//256

#define USER_DATA_SIZE sizeof(userData_t)
#define USER_CACHE_SIZE sizeof(userCache_t)


enum FLASH_RETURN {
	NO_ERROR = 0,
	CRC_ERROR,
	ARGS_ERROR,
	MUTEX_ERROR,
	FLASH_ERROR,
	EASYFLASH_ERROR,
	UNFOUND_ERROR,
};

#if INTERRUPT_SUPPORT
static beken_mutex_t i4s_flash_mutex;
#endif

static uint8_t data_temp[FLASH_PAGE_SIZE] = {0};

extern bk_err_t bk_flash_write_bytes(uint32_t address, const uint8_t *user_buf, uint32_t size);
extern bk_err_t bk_flash_read_bytes(uint32_t address, uint8_t *user_buf, uint32_t size);
extern __attribute__((section(".itcm_sec_code"))) bk_err_t bk_flash_erase_sector(uint32_t address);

#if INTERRUPT_SUPPORT 
static uint8_t i4s_mutex_inited = 0;
static void i4s_flash_mutex_init(void) 
{
	if (i4s_mutex_inited) {
		return ;
	}
	rtos_init_mutex(&i4s_flash_mutex);
	i4s_mutex_inited = 1;
}


static uint8_t i4s_flash_mutex_check(void)
{
	if (i4s_mutex_inited) {
		return 0;
	} else { /* 返回状态: 还未初始化 */
		return 1;
	}
}

static void i4s_flash_lock(void) 
{
	rtos_lock_mutex(&i4s_flash_mutex);
}

static void i4s_flash_unlock(void)
{
	rtos_unlock_mutex(&i4s_flash_mutex);
}
#endif
/**
 * 计算 crc 值并返回 (累加对256求余) 调用者自行保证 data的 data_size 全为合法空间
 * @param  data      [description]
 * @param  data_size [description]
 * @return           [description]
 */
static uint32_t flash_calc_crc(uint8_t *data, uint16_t data_size)
{
	if (!data || data_size <= 0) {
		return CRC_ERROR_VALUE;
	}
	uint16_t i = 0;
	uint32_t sum = 0;

	for (i = 0; i < data_size; i++) {
		sum += data[i];
	}

	return sum % data_size;
}

/**
 * 初始化 userData_t
 * @param  data 
 * @return      0： init ok   other else：fault
 */
int userData_init(userData_t *data)
{
#if INTERRUPT_SUPPORT
	i4s_flash_mutex_init();
#endif
	if (data == NULL) {
		return ARGS_ERROR;
	}
	int ret = 0;
#if INTERRUPT_SUPPORT
	i4s_flash_lock();
#endif

#if USE_EASYFLASH  /* read 虽有crc 但是不校验了 easyflash本身带有校验 */
 #if (CONFIG_EASY_FLASH && CONFIG_EASY_FLASH_V4)
	FLASH_DEBUG("easy ready to read\r\n");
	ret = bk_get_env_enhance(USERDATA_KEY, (void *)data, USER_DATA_SIZE);
	FLASH_DEBUG("easy read over\r\n");
	if (ret != USER_DATA_SIZE) {
		return UNFOUND_ERROR;
	} else {
		return NO_ERROR;
	}
 #else
	return EASYFLASH_ERROR;
 #endif
#endif

	memset(data_temp, 0x0, FLASH_PAGE_SIZE);

	FLASH_DEBUG("ready to read 1\r\n");
	ret = bk_flash_read_bytes((uint32_t)USER_DATA_ADDR, (uint8_t *)data_temp, (uint32_t)FLASH_PAGE_SIZE);
	FLASH_DEBUG("read over 1\r\n");
#if INTERRUPT_SUPPORT
	i4s_flash_unlock();
#endif

	memcpy(data, (const void *)data_temp, USER_DATA_SIZE);

	if (ret) {
		FLASH_DEBUG("read fault\r\n");
		return FLASH_ERROR;
	}

	uint32_t crc = flash_calc_crc((uint8_t *)data, (uint16_t)(USER_DATA_SIZE - sizeof(data->crc)));

	if (crc == CRC_ERROR_VALUE) {
		FLASH_DEBUG("crc check error 1\r\n");
		return ARGS_ERROR;
	}

	if (crc != data->crc) { /* NOTE crc check error */
		FLASH_DEBUG("crc check error 2\r\n");
		return CRC_ERROR;
	}

	return NO_ERROR;
}

/**
 * 初始化 userCache_t
 * @param  data 
 * @return      0： init ok   other else：fault
 */
int userCache_init(userCache_t *cdata)
{
#if INTERRUPT_SUPPORT
	i4s_flash_mutex_init();
#endif
	if (cdata == NULL) {
		return ARGS_ERROR;
	}
	int ret = 0;
#if INTERRUPT_SUPPORT
	i4s_flash_lock();
#endif

#if USE_EASYFLASH
 #if (CONFIG_EASY_FLASH && CONFIG_EASY_FLASH_V4)
	ret = bk_get_env_enhance(USERCACHE_KEY, (void *)cdata, USER_CACHE_SIZE);
	if (ret != USER_CACHE_SIZE) {
		return UNFOUND_ERROR;
	} else {
		return NO_ERROR;
	}
 #else
	return EASYFLASH_ERROR;
 #endif
#endif

	memset(data_temp, 0x0, FLASH_PAGE_SIZE);

	FLASH_DEBUG("ready to read 2\r\n");
	ret = bk_flash_read_bytes((uint32_t)USER_CATCH_ADDR, (uint8_t *)data_temp, (uint32_t)FLASH_PAGE_SIZE);
	FLASH_DEBUG("read over 2\r\n");
#if INTERRUPT_SUPPORT	
	i4s_flash_unlock();
#endif

	memcpy(cdata, (const void *)data_temp, USER_CACHE_SIZE);

	if (ret) {
		FLASH_DEBUG("read fault\r\n");
		return FLASH_ERROR;
	}

	uint32_t crc = flash_calc_crc((uint8_t *)cdata, (uint16_t)(USER_CACHE_SIZE - sizeof(cdata->crc)));

	if (crc == CRC_ERROR_VALUE) {
		FLASH_DEBUG("crc check error 1\r\n");
		return ARGS_ERROR;
	}	

	if (crc != cdata->crc) { /* NOTE crc check error */
		FLASH_DEBUG("crc check error 2\r\n");
		return CRC_ERROR;
	}

	return NO_ERROR;
}

/**
 * 覆写 userCache_t 讲变量 rewrite
 * @param  cdata data
 * @return     0： init ok   other else：fault  
 */
int userCache_reload(userCache_t *cdata)
{
	int ret = 0;
	ret = userCache_init(cdata);

	return ret;
}

/**
 * save data of userData_t
 * @param  data content
 * @return   0： init ok   other else：fault
 */
int userData_save(userData_t *data)
{
#if INTERRUPT_SUPPORT
	if (i4s_flash_mutex_check()) {
		return MUTEX_ERROR;
	}
#endif
	if (data == NULL) {
		return ARGS_ERROR;
	}
	int ret = 0;

	uint32_t crc = flash_calc_crc((uint8_t *)data, (uint16_t)(USER_DATA_SIZE - sizeof(data->crc)));
	if (crc == CRC_ERROR_VALUE) {
		FLASH_DEBUG("crc check error 1\r\n");
		return CRC_ERROR;
	}
	data->crc = crc;
#if INTERRUPT_SUPPORT
	i4s_flash_lock();
#endif

#if USE_EASYFLASH
 #if (CONFIG_EASY_FLASH && CONFIG_EASY_FLASH_V4)
	ret = bk_set_env_enhance(USERDATA_KEY, (void *)data, USER_DATA_SIZE);
	if (ret != 0) {
		return FLASH_ERROR;
	} else {
		return NO_ERROR;
	}
 #else
	return EASYFLASH_ERROR;
 #endif
#endif

	memset(data_temp, 0x0, FLASH_PAGE_SIZE);
	memcpy(data_temp, (const void *)data, USER_DATA_SIZE);

	flash_protect_type_t type = bk_flash_get_protect_type();
	bk_flash_set_protect_type(FLASH_PROTECT_NONE);
	FLASH_DEBUG("ready write 1\r\n");
	bk_flash_erase_sector((uint32_t)USER_DATA_ADDR);
	ret = bk_flash_write_bytes((uint32_t)USER_DATA_ADDR, (const uint8_t *)data_temp, FLASH_PAGE_SIZE);
	FLASH_DEBUG("write over 1\r\n");
	FLASH_DEBUG("ret is %d\r\n", ret);
	bk_flash_set_protect_type(type);	
#if INTERRUPT_SUPPORT	
	i4s_flash_unlock();
#endif
	if (ret) {
		return FLASH_ERROR;
	}

	return NO_ERROR;
}

/**
 * save cdata of userCache_t
 * @param  cdata content
 * @return   0： init ok   other else：fault
 */
int userCache_save(userCache_t *cdata)
{
#if INTERRUPT_SUPPORT
	if (i4s_flash_mutex_check()) {
		return MUTEX_ERROR;
	}
#endif
	if (cdata == NULL) {
		return ARGS_ERROR;
	}
	int ret = 0;

	uint32_t crc = flash_calc_crc((uint8_t *)cdata, (uint16_t)(USER_CACHE_SIZE - sizeof(cdata->crc)));
	if (crc == CRC_ERROR_VALUE) {
		FLASH_DEBUG("crc check error 1\r\n");
		return CRC_ERROR;
	}
	cdata->crc = crc;
#if INTERRUPT_SUPPORT
	i4s_flash_lock();
#endif

#if USE_EASYFLASH
 #if (CONFIG_EASY_FLASH && CONFIG_EASY_FLASH_V4)
	ret = bk_set_env_enhance(USERCACHE_KEY, (void *)cdata, USER_CACHE_SIZE);
	if (ret != 0) {
		return FLASH_ERROR;
	} else {
		return NO_ERROR;
	}
 #else
	return EASYFLASH_ERROR;
 #endif
#endif

	memset(data_temp, 0x0, FLASH_PAGE_SIZE);
	memcpy(data_temp, (const void *)cdata, USER_CACHE_SIZE);

	flash_protect_type_t type = bk_flash_get_protect_type();
	bk_flash_set_protect_type(FLASH_PROTECT_NONE);
	FLASH_DEBUG("ready write 2\r\n");
	bk_flash_erase_sector((uint32_t)USER_CATCH_ADDR);
	ret = bk_flash_write_bytes((uint32_t)USER_CATCH_ADDR, (const uint8_t *)data_temp, FLASH_PAGE_SIZE);
	FLASH_DEBUG("write over 2\r\n");
	FLASH_DEBUG("ret is %d\r\n", ret);
	bk_flash_set_protect_type(type);	
#if INTERRUPT_SUPPORT
	i4s_flash_unlock();
#endif

	if (ret) {
		return FLASH_ERROR;
	}

	return NO_ERROR;
}


