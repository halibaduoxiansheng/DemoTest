#ifndef __HALI_LIST_NODE_H__
#define __HALI_LIST_NODE_H__

#include "stdio.h"
#include "bk_list.h"

#define LIST_ADD_TYPE	(1)  /* 1: 使用头插法  0：尾插法 */

enum RETURN_ARGS {
	ERROR_NONE = 0,
	ERROR_LOGIC = 1, /* 逻辑错误，混乱 */
	ERROR_ARGS = 2,
	ERROR_MALLOC = 3,

	ERROR_MAX,
};

enum node_type {
	TYPE_LED = 0,
	TYPE_BUTTON,

	TYPE_MAX,
};



uint8_t hali_link_list_init(void);

uint8_t hali_link_list_deinit(void);

uint8_t hali_link_list_add(void* user_data, uint16_t user_data_size, enum node_type type);

/* 返回NULL就是没有找到 pos_start 为传入的开始位置 第一次使用传NULL */
void *hali_link_list_traverse(enum node_type type, struct list_head **pos_start);



#endif