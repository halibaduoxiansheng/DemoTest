#include "hali_loop_array.h"
#include "string.h"
#include "stdlib.h"

/* !!! WARNING !!!
 * code by wangjie, if you decided to use this lib,Take full responsibility on your behalf
 */
#define TAG "hali_loop_array"

enum HALI_LP_RETURN {
	HALI_RETURN_INVALID_ARGS = -10,
	HALI_RETURN_LOGICAL,
	HALI_RETURN_ERROR,

	HALI_RETURN_OK = 0,
	HALI_RETURN_MAX,
};

/*_______________    Debug Module _______________*/
#define HALI_LOOP_DEBUG_FLAG		1
#if HALI_LOOP_DEBUG_FLAG
 #define HALI_LOOP_DEBUG_L0 printf /* Level0 > Level1 */ 
 #define HALI_LOOP_DEBUG_L1 printf 
#else
 #define HALI_LOOP_DEBUG_L0 
 #define HALI_LOOP_DEBUG_L1 
#endif

/*_______________    Mutex Module _______________*/
#if HALI_LOOP_ARRAY_USE_MUTEX
static inline void hali_loop_array_lock_init(void* mutex)
{
	rtos_init_mutex(&mutex);
}
static inline void hali_loop_array_lock_deinit(void* mutex)
{
	rtos_deinit_mutex(&mutex);
}
static inline void hali_loop_array_lock(void* mutex)
{
	rtos_lock_mutex(&mutex);
}
static inline void hali_loop_array_unlock(void* mutex)
{
	rtos_unlock_mutex(&mutex);
}
#endif

/*_______________    Loop Array Module _______________*/
static inline int hali_get_array_max_index(_hali_loop_array_t *array)
{
	return array->maxSize - 1;
}

int hali_loop_array_get_freeSize(_hali_loop_array_t *array)
{
	if (!array) {
		HALI_LOOP_DEBUG_L0("%s -> please check args validity\r\n", TAG);
		return HALI_RETURN_INVALID_ARGS;
	}
	if (array->inited != 1) {
		HALI_LOOP_DEBUG_L1("%s -> looparray have not init\r\n", TAG);
		return HALI_RETURN_LOGICAL;
	}

#if HALI_LOOP_ARRAY_USE_MUTEX
	hali_loop_array_lock(array->mutex);
#endif
	int array_free_len = 0;
	int w_greater_r = array->wpos > array->rpos ? 1 : 0;
	int diff_value = w_greater_r ? (array->wpos - array->rpos) : (array->rpos - array->wpos);
	if (!diff_value && array->full_1_empty_0) {
		array_free_len = 0;
	} else if (!diff_value && !array->full_1_empty_0) {
		array_free_len = array->maxSize;
	} else {
		if (w_greater_r)
			array_free_len = array->maxSize - diff_value;
		else
			array_free_len = diff_value;
	}
#if HALI_LOOP_ARRAY_USE_MUTEX
	hali_loop_array_unlock(array->mutex);
#endif

	HALI_LOOP_DEBUG_L1("get array free size :%d\r\n", array_free_len);
	return array_free_len;
}

int hali_loop_array_get_fillSize(_hali_loop_array_t *array)
{
	if (!array) {
		HALI_LOOP_DEBUG_L0("%s -> please check args validity\r\n", TAG);
		return HALI_RETURN_INVALID_ARGS;
	}
	if (array->inited != 1) {
		HALI_LOOP_DEBUG_L1("%s -> looparray have not init\r\n", TAG);
		return HALI_RETURN_LOGICAL;
	}

	int array_fill_len = 0;
	array_fill_len = array->maxSize - hali_loop_array_get_freeSize(array);
	HALI_LOOP_DEBUG_L1("get array fill size :%d\r\n", array_fill_len);

	return array_fill_len;
}

int hali_loop_array_write(_hali_loop_array_t *array, unsigned char* src_start_address, uint32_t copySize)
{
	if (!array || !src_start_address || copySize < 0) {
		HALI_LOOP_DEBUG_L0("%s -> please check args validity\r\n", TAG);
		return HALI_RETURN_INVALID_ARGS;
	}
	if (array->inited != 1) {
		HALI_LOOP_DEBUG_L1("%s -> looparray have not init\r\n", TAG);
		return HALI_RETURN_LOGICAL;
	}
	
	uint32_t array_freeSize = hali_loop_array_get_freeSize(array);
	int array_right_writable_len = 0;
	int remain_left_writable_len = 0;

	if (array_freeSize >= copySize) {
#if HALI_LOOP_ARRAY_USE_MUTEX
		hali_loop_array_lock(array->mutex);
#endif
		array_right_writable_len = array->maxSize - array->wpos;
		if (array_right_writable_len >= copySize) {
			memcpy(&array->data[array->wpos], src_start_address, copySize);
			array->wpos += copySize;
		} else {
			memcpy(&array->data[array->wpos], src_start_address, array_right_writable_len);
			remain_left_writable_len = copySize - array_right_writable_len;
			memcpy(&array->data[0], src_start_address + array_right_writable_len, remain_left_writable_len);
			array->wpos = remain_left_writable_len;
		}

		if (array->wpos == array->rpos) {
			array->full_1_empty_0 = 1; /* NOTE 记录下是填充满导致的 wpos == rpos */
		}
#if HALI_LOOP_ARRAY_USE_MUTEX
		hali_loop_array_unlock(array->mutex);
#endif
	} else {
		HALI_LOOP_DEBUG_L1("array free size is not enough[%d->%d]\r\n", array_freeSize, copySize);
		return HALI_RETURN_ERROR;
	}

	return (int)copySize;
}

int hali_loop_array_read(_hali_loop_array_t *array, unsigned char* store_start_address, uint32_t maxSize)
{
	if (!array || !store_start_address || maxSize < 0) {
		HALI_LOOP_DEBUG_L0("%s -> please check args validity\r\n", TAG);
		return HALI_RETURN_INVALID_ARGS;
	}
	if (array->inited != 1) {
		HALI_LOOP_DEBUG_L1("%s -> looparray have not init\r\n", TAG);
		return HALI_RETURN_LOGICAL;
	}
	
	uint32_t array_fillSize = hali_loop_array_get_fillSize(array);
	int array_right_readable_len = 0;
	int remain_left_readable_len = 0;

	if (array_fillSize < maxSize) {
		HALI_LOOP_DEBUG_L1("array fill size is not enough[%d<-%d]\r\n", array_fillSize, maxSize);
		maxSize = array_fillSize;
	}

#if HALI_LOOP_ARRAY_USE_MUTEX
	hali_loop_array_lock(array->mutex);
#endif
	array_right_readable_len = array->maxSize - array->rpos;
	if (array_right_readable_len >= maxSize) {
		memcpy(store_start_address, &array->data[array->rpos], maxSize);
		array->rpos += maxSize;
	} else {
		memcpy(store_start_address, &array->data[array->rpos], array_right_readable_len);
		remain_left_readable_len = maxSize - array_right_readable_len;
		memcpy(store_start_address + array_right_readable_len, &array->data[0], remain_left_readable_len);
		array->rpos = remain_left_readable_len;
	}

	if (array->wpos == array->rpos) {
		array->full_1_empty_0 = 0; /* NOTE 记录下是读空导致的 wpos == rpos */
	}
#if HALI_LOOP_ARRAY_USE_MUTEX
	hali_loop_array_unlock(array->mutex);
#endif

	return maxSize;
}

int hali_loop_array_clear(_hali_loop_array_t *array)
{
	if (array == NULL) {
		HALI_LOOP_DEBUG_L0("%s -> please check args validity\r\n", TAG);
		return HALI_RETURN_INVALID_ARGS;
	}
	if (array->inited != 0) {
		HALI_LOOP_DEBUG_L1("%s -> looparray already init\r\n", TAG);
		return HALI_RETURN_LOGICAL;
	}

#if HALI_LOOP_ARRAY_USE_MUTEX
	hali_loop_array_lock(array->mutex);
#endif
	array->full_1_empty_0 = array->wpos = array->rpos = 0;
#if HALI_LOOP_ARRAY_USE_MUTEX
	hali_loop_array_lock(array->mutex);
#endif

	return HALI_RETURN_OK;
}


int hali_loop_array_init(_hali_loop_array_t *array, unsigned char *start_address, uint32_t initSize)
{
	if (!array || !start_address) {
		HALI_LOOP_DEBUG_L0("%s -> please check args validity\r\n", TAG);
		return HALI_RETURN_INVALID_ARGS;
	}
	if (array->inited != 0) {
		HALI_LOOP_DEBUG_L1("%s -> looparray already init\r\n", TAG);
		return HALI_RETURN_LOGICAL;
	}

#if HALI_LOOP_ARRAY_USE_MUTEX
	hali_loop_array_lock_init(array->mutex);
#endif

	array->data = start_address;
	array->maxSize = initSize;
	array->full_1_empty_0 = array->wpos = array->rpos = 0;

	array->inited = 1;

	return HALI_RETURN_OK;
}

int hali_loop_array_deinit(_hali_loop_array_t *array)
{
	if (!array) {
		HALI_LOOP_DEBUG_L0("%s -> please check args validity\r\n", TAG);
		return HALI_RETURN_INVALID_ARGS;
	}
	if (array->inited != 1) {
		HALI_LOOP_DEBUG_L1("%s -> looparray have not init\r\n", TAG);
		return HALI_RETURN_LOGICAL;
	}

#if HALI_LOOP_ARRAY_USE_MUTEX
	hali_loop_array_lock_deinit(&array->mutex);
#endif	

	array->data = NULL;
	array->full_1_empty_0 = array->maxSize = array->wpos = array->rpos = 0;

	array->inited = 0;

	return HALI_RETURN_OK;
}

#if HALI_LOOP_ARRAY_SELF_TEST
int main(void)
{
	uint8_t data0[10], data1[10];
	_hali_loop_array_t array[2] = {0};
	int ret = 0;

	memset(data0, 0x0, sizeof(data0));
	memset(data1, 0x0, sizeof(data1));
	hali_loop_array_init(&array[0], data0, sizeof(data0));
	hali_loop_array_write(&array[0], "12121212", 8);
	hali_loop_array_read(&array[0], data1, 8);
	printf("data1: %s\r\n", data1);
	printf("\r\n-----------------------------------------------------\r\n");

	memset(data0, 0x0, sizeof(data0));
	memset(data1, 0x0, sizeof(data1));
	hali_loop_array_init(&array[0], data0, sizeof(data0));
	hali_loop_array_write(&array[0], "12121212", 8);
	hali_loop_array_read(&array[0], data1, 10);
	printf("data1: %s\r\n", data1);
	printf("\r\n-----------------------------------------------------\r\n");

	memset(data0, 0x0, sizeof(data0));
	memset(data1, 0x0, sizeof(data1));
	hali_loop_array_init(&array[0], data0, sizeof(data0));
	hali_loop_array_write(&array[0], "12121212", 8);
	hali_loop_array_read(&array[0], data1, 20);
	printf("data1: %s\r\n", data1);
	hali_loop_array_write(&array[0], "23232323", 8);
	hali_loop_array_read(&array[0], data1, 20);
	printf("data1: %s\r\n", data1);
	printf("\r\n-----------------------------------------------------\r\n");

	memset(data0, 0x0, sizeof(data0));
	memset(data1, 0x0, sizeof(data1));
	hali_loop_array_init(&array[0], data0, sizeof(data0));
	hali_loop_array_write(&array[0], "12121212", 8);
	hali_loop_array_write(&array[0], "23232323", 8);
	hali_loop_array_read(&array[0], data1, 20);
	printf("data1: %s\r\n", data1);
	printf("\r\n-----------------------------------------------------\r\n");

	return 0;
}
#endif