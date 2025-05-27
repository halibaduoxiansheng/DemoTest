#include "i4s_list_node.h"
#include "bk_list.h"

/* 库中不要牵扯到 对应细节平台，目的是适配所有 Linux 平台 */



struct node_base {
	enum node_type type;
	struct list_head list;
};

struct node_data {
	struct node_base base;
	void* data;
}

struct list_head mixed_list;

static beken_mutex_t list_mutex; /* 适配BK 7258 平台 */
static uint8_t hali_link_list_inited = 0;

static inline void list_lock(void)
{
	rtos_lock_mutex(&list_mutex);
}

static inline void list_unlock(void)
{
	rtos_unlock_mutex(&list_mutex);
}

static uint8_t check_type_validity(enum node_type type) {
	if (type < 0 || type >= TYPE_MAX) {
		return ERROR_ARGS;
	}
	return ERROR_NONE;
}

static void hali_free_all_mem(void)
{
    struct list_head *pos, *n;
    struct node_base *base;
    struct node_data *n_data;

    list_for_each_safe(pos, n, &mixed_list) {
        base = list_entry(pos, struct node_base, list);
        n_data = container_of(base, struct node_data, base);

        if (n_data && n_data->data) {
            free(n_data->data);
        }

        list_del(pos);   // 正确删除节点
        free(n_data);    // 释放整个结构体
    }
}


uint8_t hali_link_list_add(void* user_data, uint16_t user_data_size, enum node_type type)
{
	if (!user_data || user_data_size <= 0 || check_type_validity(type)) {
		return ERROR_ARGS;
	}


	if (type == TYPE_LED) {
		struct node_data *node_d = (struct node_data *)malloc(sizoef(struct node_data));
		if (!node_d) {
			return ERROR_MALLOC;
		}
		node_d->data = (void *)malloc(user_data_size);
		if (!(node_d->data)) {
			free(node_d);
			return ERROR_MALLOC;
		}
		memcpy(node_d->data, user_data, user_data_size);
		node_d->base.type = type;
		list_lock();
#if LIST_ADD_TYPE /* 头插法 */
		list_add(&node_d->base.list, &mixed_list);
#else /* 尾插法 */
		list_add_tail(&node_d->base.list, &mixed_list);
#endif
		list_unlock();
	} else if (type == TYPE_BUTTON) {
		/* TODO */
	}

	return ERROR_NONE;
}

/* 返回NULL就是没有找到 pos_start 为传入的开始位置 第一次使用传NULL */
void *hali_link_list_traverse(enum node_type type, struct list_head *pos_start)
{
	if (pos_start == NULL) { /* 没有给开始位置，就自定义开始位置 */
		pos_start = mixed_list.next;
	}
	if (pos_start == &mixed_list) {
		return NULL;
	}
	struct node_data *n_data = NULL;

    do {
    	// TODO 
        struct node_base *base = list_entry(pos_start, struct node_base, list);

        if (type == base->type) {
			n_data = container_of(base, struct node_data, base);
			return n_data->data;
        } else {
        	pos_start = pos_start->next; /* 找不到，递归下一个 */
        }
    } while(pos_start != &mixed_list); /* 最多执行一轮询 */

    pos_start = NULL;
    return NULL;
}



uint8_t hali_link_list_init(void) 
{
	if (hali_link_list_inited) {
		return ERROR_NONE;
	}
	hali_link_list_inited = 1;

	INIT_LIST_HEAD(&mixed_list); /* TODO */
	rtos_init_mutex(&list_mutex);

	return ERROR_NONE;
	
}


uint8_t hali_link_list_deinit(void) {
	if (!hali_link_list_inited) {
		return ERROR_LOGIC;
	}
	hali_link_list_inited = 0;

	/* TODO 释放该释放的空间 */
	hali_free_all_mem();
	rtos_deinit_mutex(&list_mutex);
	
	return ERROR_NONE;
}


