#ifndef __HALI_MEMORY_POOL_H__
#define __HALI_MEMORY_POOL_H__

#ifdef _cplusplus
extern "C" {
#endif

/**
 * 内存池
 */

#include "stdio.h"

#define HALI_POOL_MEMORY_USE_PSRAM	(0)

#define HALI_POOL_MEMORY_SIZE	8192 // memory pool size


void *hali_memory_pool_alloc(int size); 
int hali_memory_pool_free(void *data);

int hali_memory_pool_init(void); // 申请一大段区域用于使用
int hali_memory_pool_deinit(void); // 



#ifdef _cplusplus
}
#endif
#endif // end __HALI_MEMORY_POOL_H__