#ifndef __HALI_LIST_NODE_H__
#define __HALI_LIST_NODE_H__

#include "stdio.h"

enum INSERT_TYPE {
	LED_TYPE = 0,
	BUTTON_TYPE = 1,
};

struct G_BK_Double_link{
    uint8_t is_init:1;
    uint8_t reserve:7;
}__attribute__((packed));
struct G_BK_Double_link bk_double_link;

typedef struct Double_link_list{
    struct G_BK_LED *led;
	// struct G_BK_Button *button;
	/* if you want add then add member in there */

	uint8_t type; 

	struct Double_link_list *prev;
	struct Double_link_list *next;
}Double_link_list_t;
extern struct Double_link_list *bk_dlink_head;
extern struct Double_link_list *bk_dlink_tail;
/*  head->prev -> tail     tail->next -> head */


void i4s_bk_double_link_init(void);
void i4s_bk_double_link_deinit(void);
struct Double_link_list* double_button_link_insert(enum INSERT_TYPE type, void *data);


#endif