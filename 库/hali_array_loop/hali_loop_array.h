#ifndef __HALI_LOOP_ARRAY_H__
#define __HALI_LOOP_ARRAY_H__

#ifdef __cplusplus
extern "C" {
#endif
#include "stdio.h"

#define HALI_LOOP_ARRAY_USE_MUTEX	0 // 是否支持使用 锁
#define HALI_LOOP_ARRAY_SELF_TEST	0 // 自测开关

#if HALI_LOOP_ARRAY_SELF_TEST
typedef unsigned char uint8_t;
typedef unsigned int uint32_t;
#endif

typedef struct _hali_loop_array {
	uint8_t inited;
	uint8_t full_1_empty_0; /* use for wpos == rpos Condition */

	uint32_t wpos; /* write start index */
	uint32_t rpos; /* read start index */

	uint32_t maxSize;
	unsigned char *data;
#if HALI_LOOP_ARRAY_USE_MUTEX
	void* mutex;
#endif
}_hali_loop_array_t;

/**
 * 环形缓冲区初始化 
 * @param array         缓冲区 Obj
 * @param start_address 缓冲区存储内容使用地址
 * @param initSize      缓冲区存储内容可用大小
 * @return   =0:Success	!=0:Failed
 */
int hali_loop_array_init(_hali_loop_array_t *array, unsigned char *start_address, uint32_t initSize);

/**
 * 环形缓冲区反初始化
 * @param array 缓冲区 Obj
 * @return   =0:Success	!=0:Failed
 */
int hali_loop_array_deinit(_hali_loop_array_t *array);

/**
 * 环形缓冲区 读取
 * @param  array               缓冲区 Obj
 * @param  store_start_address 读取内容存储起始地址
 * @param  maxSize             最大读取大小
 * @return                     >=0:读取到的长度 <0:读取失败
 */
int hali_loop_array_read(_hali_loop_array_t *array, unsigned char* store_start_address, uint32_t maxSize);

/**
 * 环形缓冲区 写入
 * @param  array             缓冲区 Obj
 * @param  src_start_address 写入内容来源起始地址
 * @param  copySize          写入内容长度
 * @return                  =copySize:写入成功  !=copySize:写入失败
 */
int hali_loop_array_write(_hali_loop_array_t *array, unsigned char* src_start_address, uint32_t copySize);


/**
 * 环形缓冲区 清空
 * @param  array 缓冲区 Obj
 * @return       =0:清空成功  !=0:清空失败
 */
int hali_loop_array_clear(_hali_loop_array_t *array);

/**
 * 获取环形缓冲区剩余空间大小
 * @param  array 缓冲区 Obj
 * @return       >=0: 获取成功，返回大小 <0:获取失败
 */
int hali_loop_array_get_freeSize(_hali_loop_array_t *array);


/**
 * 获取环形缓冲区已填充大小
 * @param  array 缓冲区 Obj
 * @return       >=0: 获取成功，返回大小 <0:获取失败
 */
int hali_loop_array_get_fillSize(_hali_loop_array_t *array);

#ifdef __cplusplus
}
#endif
#endif