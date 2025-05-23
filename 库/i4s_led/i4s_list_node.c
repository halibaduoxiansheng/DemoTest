#include "i4s_list_node.h"



struct Double_link_list *bk_dlink_head = NULL;
struct Double_link_list *bk_dlink_tail = NULL;
uint8_t button_structure_size = 0;

void i4s_bk_double_link_init(void)
{
	if (bk_double_link.is_init == 0) {
		bk_dlink_head = (struct Double_link_list *)os_malloc(sizeof(struct Double_link_list));
		bk_dlink_tail = (struct Double_link_list *)os_malloc(sizeof(struct Double_link_list));

		bk_dlink_head->prev = bk_dlink_tail;
		bk_dlink_head->next = NULL;

		bk_dlink_tail->next = bk_dlink_head;
		bk_dlink_tail->prev = NULL;
		bk_double_link.is_init = 1;
	} else {
		bk_printf("we already init double link list\r\n");
	}
}


void i4s_bk_double_link_deinit(void) /* Regardless of type， all deinit */
{
	if (bk_double_link.is_init == 0) {
		printf("double link list not init\r\n");
	} else {
		struct Double_link_list *temp = bk_dlink_head->next;
		while(temp) {
			if (temp->next) {
				temp = temp->next;
				free(temp->prev);
				temp->prev = NULL;
			} else {
				free(temp);
				temp = NULL;
			}
		}
		if (bk_dlink_head)
			free(bk_dlink_head);
		bk_dlink_head = NULL;
		bk_double_link.is_init = 0;
	}
}

struct Double_link_list* double_button_link_insert(enum INSERT_TYPE type, void *data)
{
	struct Double_link_list *temp = bk_dlink_head;
	struct Double_link_list *node = NULL;

	/* is this first node add to list */
	if (bk_dlink_head->next == NULL && bk_dlink_tail->prev == NULL) { 
		node = (struct Double_link_list*)malloc(sizeof(struct Double_link_list)); // the new add node
		if (node == NULL) {
			printf("malloc node failed\r\n");
			return NULL;
		}
		bk_dlink_head->next = node;
		bk_dlink_tail->prev = node;
		node->prev = bk_dlink_head;
		node->next = bk_dlink_tail;
	} else {
		node = (struct Double_link_list*)malloc(sizeof(struct Double_link_list)); // the new add node
		while(temp->next != bk_dlink_tail) { // find the last one
			temp = temp->next;
		}
		temp->next = node;
		bk_dlink_tail->prev = node;
		node->next = bk_dlink_tail;
		node->prev = temp;
	}

	node->type = type; /* 这里可扩展 */

	if (type == LED_TYPE) {
		node->led = (struct G_BK_LED *)malloc(sizeof(struct G_BK_LED)); // never failed,if failed, just die
		node->led = (struct G_BK_LED *)data;
	}
	return node;
}



