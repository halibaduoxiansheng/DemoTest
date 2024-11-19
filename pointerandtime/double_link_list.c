#include <stdio.h>
#include <stdlib.h>

typedef struct Double_link_list{
	int data;
	struct Double_link_list *prev;
	struct Double_link_list *next;
}Double_link_list_t;


Double_link_list_t *head = NULL;


void double_link_init(void)
{
	head = (struct Double_link_list *)malloc(sizeof(struct Double_link_list));
	head->prev = head->next = NULL;
}

struct Double_link_list* double_link_insert(struct Double_link_list **node, int data)
{
	if (head == NULL) {
		printf("head is NULL,please init list first\r\n");
		return NULL;
	}
	(*node) = (struct Double_link_list *)malloc(sizeof(struct Double_link_list));
	// not have access any node to list
	if (head->next == NULL) {
		head->next = (*node);
		(*node)->prev = head;
		(*node)->next = NULL;
		(*node)->data = data;
	} else { // already have node in list
		head->next->prev = (*node);
		(*node)->next = head->next;
		head->next = (*node);
		(*node)->prev = head;
		(*node)->data = data;
	}

	return (*node);
}

int double_link_delete(struct Double_link_list *node)
{
	if (node == head) {
		printf("you can not delete the head node\r\n");
		return -1;
	}
	struct Double_link_list* temp = head->next;

	do {
		if (temp == node && node != NULL) {
			node->prev->next = node->next;
			node->next->prev = node->prev;
			printf("you delete this node which have data is %d\r\n", node->data);
			free(node);
			node = NULL;
			return 0;
		}
		temp = temp->next;
	} while(temp->next);
	printf("we can not find this node in list,please check your args\r\n");
	return 0;
}


void display_list(void)
{
	if (head == NULL) {
		printf("please init list first,because the head node is NULL\r\n");
		return;
	}
	struct Double_link_list* temp = head->next;
	printf("=========================================");
	while(temp) {
		printf("%d->", temp->data);
		temp = temp->next;
	}
}

int main(void)
{
	double_link_init();

	// insert
	struct Double_link_list *insert_node = double_link_insert(&insert_node, 4);
	if (insert_node == NULL) {
		printf("insert node failed\r\n");
	} else {
		printf("insert node success\r\n");
		printf("insert_node data is %d\r\n", insert_node->data);
	}

	struct Double_link_list *insert_node_1 = double_link_insert(&insert_node, 3);
	if (insert_node_1 == NULL) {
		printf("insert node failed\r\n");
	} else {
		printf("insert node success\r\n");
		printf("insert_node data is %d\r\n", insert_node_1->data);
	}

	struct Double_link_list *insert_node_2 = double_link_insert(&insert_node, 2);
	if (insert_node_2 == NULL) {
		printf("insert node failed\r\n");
	} else {
		printf("insert node success\r\n");
		printf("insert_node data is %d\r\n", insert_node_2->data);
	}

	double_link_delete(insert_node_1);

	display_list();

	return 0;
}


