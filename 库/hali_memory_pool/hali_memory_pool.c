#include "hali_memory_pool.h"
#include <string.h>
#include <stdlib.h>

/**
 * 内存池 优点：更高的速度，更低的碎片，更低的系统开销
 * 缺点： 对于空间管理上的冗余字段的浪费现象
 *
 * 力求 设计一种较好的内存池管理
 */

#define TAG "hali_memory_pool"
#define HALI_MEMORY_DEBUG_SWITCH_FLAG	(1)
#ifdef HALI_MEMORY_DEBUG_SWITCH_FLAG
 #define HALI_MD_LOGE	printf // error
 #define HALI_MD_LOGW	printf // warning
 #define HALI_MD_LOGI	printf // info
 #define HALI_MD_LOGD	printf // debug
 #define HALI_MD_LOGV	printf // verbose
#else
 #define HALI_MD_LOGE	
 #define HALI_MD_LOGW	
 #define HALI_MD_LOGI	
 #define HALI_MD_LOGD	
 #define HALI_MD_LOGV	
#endif

#define DIFF_MAX_VALUE (unsigned int)(-1)

enum HALI_RETURN_TYPE {
	HALI_RETURN_ERROR = -1,
	HALI_RETURN_OK = 0,
};

struct Hali_SubModule_Pool {
	struct Hali_SubModule_Pool *next; /* 指向下一个可用内存块的位置，为NULL就是没有下一个 */

	unsigned short module_size; /* 该内存区域块的大小 ，柔性数组指向空间的大小 */
	unsigned char used; /* 该内存区域是否有使用 */
	unsigned char reserved;

	unsigned char *data[]; /* 柔性数组，指向真实可分配使用空间 */
};

#define SUB_MODULE_HEAD_SIZE sizeof(struct Hali_SubModule_Pool)

typedef struct Hali_Memory_Pool {
	unsigned char *pool_start_address; /* 内存池起始地址 */

	unsigned char *pool_rightmost_address;

	struct Hali_SubModule_Pool *list;
}Hali_Memory_Pool;
Hali_Memory_Pool hali_p;

static unsigned char hali_memory_pool_inited = 0;


static void* hali_malloc(int size)
{
#if HALI_POOL_MEMORY_USE_PSRAM
	psram_malloc(size);
#else
	malloc(size);
#endif
}

static void hali_free(void *data) 
{
#if HALI_POOL_MEMORY_USE_PSRAM
	psram_free(data);
#else
	free(data);
#endif	
}

static void ensure_rightmost_address(void)
{
	struct Hali_SubModule_Pool *pos = (struct Hali_SubModule_Pool *)hali_p.pool_start_address;
	struct Hali_SubModule_Pool *pos_last = NULL;

	do {
		pos_last = pos;
		hali_p.pool_rightmost_address = (unsigned char*)pos_last;
		pos = (struct Hali_SubModule_Pool *)((unsigned char*)pos + SUB_MODULE_HEAD_SIZE + pos->module_size);
		if (pos && pos->next != pos_last) { // 说明这就是最右边的 block 了
			break;
		} else if (!pos) {
			break;
		}
	} while(1);
}

static struct Hali_SubModule_Pool *get_last_node(struct Hali_SubModule_Pool *node)
{
	ensure_rightmost_address();

	struct Hali_SubModule_Pool *pos = (struct Hali_SubModule_Pool *)hali_p.pool_rightmost_address;

	for (; pos; pos = pos->next) {
		if (pos->next == node) {
			return pos;
		}
	}

	return NULL; // 说明并没有前一个
}

void *hali_memory_pool_alloc(int size)
{
	if (size < 0) {
		HALI_MD_LOGE("%s -> args is invalid\r\n", TAG);
		return NULL;
	}
	ensure_rightmost_address();
	
	// NOTE 寻找最适合的 块，分配空间
	struct Hali_SubModule_Pool *pos = (struct Hali_SubModule_Pool *)hali_p.pool_rightmost_address;
	struct Hali_SubModule_Pool *new = NULL;
	struct Hali_SubModule_Pool *pos_last = NULL;
	struct Hali_SubModule_Pool *match_pos = NULL;
	unsigned int diff_min_size = DIFF_MAX_VALUE;

	// REVIEW 或许后面这个算法还可以优化???
	for (; pos; pos = pos->next) { // 轮询一周，找到大小与size最接近的 block
		if (pos->used == 0 && pos->module_size >= size) {
			if ((pos->module_size - size) < diff_min_size) {
				diff_min_size = pos->module_size - size;
				match_pos = pos;
			}
		} else { 
			continue;
		}
	}

	// NOTE 融合操作只在free的时候才有，也就是代表申请空间时，不存在融合操作，只有分块操作
	if (diff_min_size != DIFF_MAX_VALUE) { // NOTE 这原本就是一个块，是已经分为了块的
		new = match_pos;
		// new->data = match_pos->data; // 柔性数组 本身就是指向这个位置 显示表达就是如此
		new->next = match_pos->next;
		new->module_size = size;
		new->used = 1;

		if (diff_min_size >= SUB_MODULE_HEAD_SIZE) { // 说明剩余大小还可以成块
			match_pos = (struct Hali_SubModule_Pool *)((unsigned char*)match_pos + SUB_MODULE_HEAD_SIZE + size);
			match_pos->module_size = diff_min_size - SUB_MODULE_HEAD_SIZE; // 此值可以为0
			match_pos->used = 0;
			// match_pos->data = (unsigned char*)match_pos + SUB_MODULE_HEAD_SIZE; // 同上柔性数组解释
			match_pos->next = new;
			pos_last = get_last_node(match_pos);
			if (pos_last) {
				pos_last->next = match_pos;
			}
		} else { // 剩余空间大小不足以成块，直接冗余分配出去 (因为无法形成头即无法执行融合块操作)
			new->module_size += diff_min_size;
		}

		return (void *)new->data;
	}

	return NULL; // 分配不了
}

int hali_memory_pool_free(void *data) // 释放空间需要注意 （ 标记为不合法时，需要再自动归碎为整数 ）
{
	if (data == NULL) {
		HALI_MD_LOGE("%s -> args is invalid\r\n", TAG);
		return HALI_RETURN_ERROR;
	}
	ensure_rightmost_address();

	struct Hali_SubModule_Pool *pos = (struct Hali_SubModule_Pool *)hali_p.pool_rightmost_address;
	struct Hali_SubModule_Pool *pos_last = NULL;
	struct Hali_SubModule_Pool *pos_last_last = NULL;
	struct Hali_SubModule_Pool *pos_next = NULL;

	for (; pos; pos = pos->next) {
		if (pos->data == data) { // 找到了
			pos_last = get_last_node(pos);
			if (pos->next) { // 存在两边都有的情况
				pos_next = pos->next;
				if (pos_next->used == 0) { // 左边可融合
					if (pos_last && pos_last->used == 0) { // 左边右边都可以融合 就融合成一个大的
						pos_next->module_size = pos_next->module_size + SUB_MODULE_HEAD_SIZE + pos->module_size + SUB_MODULE_HEAD_SIZE + pos_last->module_size;
						memset(pos_next->data, 0, pos_next->module_size);
						return HALI_RETURN_OK;
					} else { // 只能和左边融合
						pos_next->module_size = pos_next->module_size + SUB_MODULE_HEAD_SIZE + pos->module_size;
						memset(pos_next->data, 0, pos_next->module_size);
						return HALI_RETURN_OK;
					}
				} else { // 只需要考虑右边可不可以融合
					goto JUST_RIGHT;
				}	
			} else { // 只有右边节点指向过来
JUST_RIGHT:
				if (pos_last && pos_last->used == 0) { // 前面一个节点是未使用的 合并
					pos_last_last = get_last_node(pos_last);
					if (pos_last_last) {
						pos_last_last->next = pos;
					}
					pos->module_size = pos->module_size + SUB_MODULE_HEAD_SIZE + pos_last->module_size;
					pos->used = 0;
					memset(pos->data, 0, pos->module_size);
					return HALI_RETURN_OK;
				} else { // 前面一个节点是使用了的，无法合并，直接表示未再使用即可
					pos->used = 0;
					memset(pos->data, 0, pos->module_size);
					return HALI_RETURN_OK;
				}
			}

		} else {
			continue;
		}
	}

	// 这里返回 说明根本就找不到这个block
	return HALI_RETURN_ERROR;
}

/**
 * 为线程池总初始化，并分配成一个 “块”
 * @return  HALI_RETURN_OK:成功 HALI_RETURN_ERROR：失败
 */
static int hali_memory_pool_malloc(void)
{
	hali_p.pool_start_address = hali_malloc(HALI_POOL_MEMORY_SIZE);
	if (hali_p.pool_start_address == NULL) {
		HALI_MD_LOGE("%s -> malloc failed,please ensure\r\n", TAG);
		return HALI_RETURN_ERROR;
	}
	hali_p.pool_rightmost_address = hali_p.pool_start_address;

	hali_p.list = (struct Hali_SubModule_Pool *)hali_p.pool_start_address;
	hali_p.list->next = NULL;
	hali_p.list->module_size = HALI_POOL_MEMORY_SIZE - SUB_MODULE_HEAD_SIZE;
	hali_p.list->used = 0;
	// hali_p.list->data = hali_p.pool_start_address + SUB_MODULE_HEAD_SIZE; // 同上柔性数组解释

	return HALI_RETURN_OK;
}

/**
 * 释放整个线程池
 * @return  HALI_RETURN_OK:成功 HALI_RETURN_ERROR：失败
 */
static int hali_memory_pool_free_all(void)
{
	if (hali_p.pool_start_address) {
		hali_free(hali_p.pool_start_address);
	} else {
		return HALI_RETURN_ERROR;
	}

	return HALI_RETURN_OK;
}

int hali_memory_pool_init(void)
{
	if (hali_memory_pool_inited == 1) {
		HALI_MD_LOGW("%s -> pool init already init\r\n", TAG);
		return HALI_RETURN_ERROR;
	}
	int ret = -1;

	ret = hali_memory_pool_malloc();
	if (ret != HALI_RETURN_OK) {
		HALI_MD_LOGD("%s -> malloc module failed,memory pool init failed\r\n\r\n", TAG);
		return HALI_RETURN_ERROR;
	}

	return HALI_RETURN_OK;
}


int hali_memory_pool_deinit(void)
{
	if (hali_memory_pool_inited == 1) {
		HALI_MD_LOGW("%s -> pool deinit not init yet\r\n", TAG);
		return HALI_RETURN_ERROR;
	}

	int ret = -1;

	ret = hali_memory_pool_free_all();
	if (ret != HALI_RETURN_OK) {
		HALI_MD_LOGD("%s -> free module failed,memory pool deinit failed\r\n\r\n", TAG);
		return HALI_RETURN_ERROR;
	}

	return HALI_RETURN_OK;
}

// test code under

static void print_pool_free_size(void)
{
	unsigned int free_sum_size = 0;
	unsigned short block_num = 0;
	struct Hali_SubModule_Pool *pos = NULL;

	ensure_rightmost_address();
	pos = (struct Hali_SubModule_Pool *)hali_p.pool_rightmost_address;

	for (; pos; pos = pos->next) {
		if (pos->used == 0) {
			free_sum_size += (pos->module_size + SUB_MODULE_HEAD_SIZE);
		}
		block_num++;
	}

	HALI_MD_LOGD("%s -> free sum size is %d\r\n", TAG, free_sum_size);
	HALI_MD_LOGD("%s -> block num is %d\r\n", TAG, block_num);
}

int main(void)
{
	HALI_MD_LOGD("%s -> test begin\r\n", TAG);

	hali_memory_pool_init();
	print_pool_free_size();

	void *data_0 = hali_memory_pool_alloc(200); 
	if (data_0 != NULL) {
		HALI_MD_LOGD("%s -> alloc data_0 ok\r\n", TAG);
	}
	print_pool_free_size();
	if (hali_memory_pool_free(data_0) == HALI_RETURN_OK) {
		HALI_MD_LOGD("%s -> free data_0 ok\r\n", TAG);
	}
	print_pool_free_size();

	void *data_1 = hali_memory_pool_alloc(100); 
	if (data_1 != NULL) {
		HALI_MD_LOGD("%s -> alloc data_1 ok\r\n", TAG);
	}
	print_pool_free_size();
	void *data_2 = hali_memory_pool_alloc(100); 
	if (data_2 != NULL) {
		HALI_MD_LOGD("%s -> alloc data_2 ok\r\n", TAG);
	}
	print_pool_free_size();
	if (hali_memory_pool_free(data_1) == HALI_RETURN_OK) {
		HALI_MD_LOGD("%s -> free data_1 ok\r\n", TAG);
	}
	print_pool_free_size();
	if (hali_memory_pool_free(data_2) == HALI_RETURN_OK) {
		HALI_MD_LOGD("%s -> free data_2 ok\r\n", TAG);
	}
	print_pool_free_size();

	return 0;
}

