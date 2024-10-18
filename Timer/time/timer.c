#include "timer.h"

typedef void (*timer_callback)(void);

typedef struct Timer
{
	uint_8 timer_type; //
	timer_callback timer_cb;
}TIMER_CLASS_T;


volatile TIMER_CLASS_T timer_1;
int timer_node_num = 0;


typedef struct TimerNode {
	TIMER_CLASS_T timer;
	struct TimerNode* prev;
	struct TiemrNode* next;
}TimerNode;

TimerNode* Timer_Create_Node(TIMER_CLASS_T* timer)
{
	TimerNode* t_node = (TimerNode*)malloc(sizeof(TimerNode));
	t_node->timer = timer;
	t_node->prev = NULL;
	t_node->next = NULL;
	return t_node;
}

void TimerNodeAppend(TimerNode** head, TIMER_CLASS_T* timer)
{
	TimerNode* new_node = Timer_Create_Node(timer);
	TimerNode* last = *head;

	if (*head == NULL) { // head is NULL,then put new_node in here
		*head = new_node;
		return;
	}

	/* search the NULL place */
	while (last->next != NULL) {
		last = last->next;
	}

	last->next = new_node;
	new_node->prev = last;

	timer_node_num++;
}

void TimerNodeDelete(TimerNode** head, TimerNode* timer)
{
	if (*head == NULL || timer == NULL) return;

	TimerNode* last = *head;
	if (*head == timer) {
		*head = NULL;
	}
	/*change the next node prev*/
	if (timer->next != NULL) {
		timer->next->prev = timer->prev;
	}
	/*change the prev node next*/
	if (timer->prev != NULL) {
		timer->prev->next = timer->next;
	}

	free(timer);
}


void Timer_set(TIMER_CLASS_T *this, uint_8 type, timer_callback timer_cb)
{
	if (!this) {
		printf("timer is NULL,Timer_set is invaild\r\n");
		return;
	}
	this->timer_type = type;
	this->timer_callback = timer_cb;
}

void Timer_proc(TIMER_CLASS_T *timer)
{
	if (!timer) {
		return;
	}
	switch(timer->timer_type)
	{
	case TIMER_CLOSE:
		break;
	case TIMER_REPEAT:
		timer->timer_cb();
		break;
	case TIMER_ONCE:
		timer->timer_cb();
		timer->timer_type = TIMER_CLOSE;
		break;
	default:
		printf("no correct command for %d\r\n", timer->timer_type);
		break;
	}
}

void TimerForEach(TimerNode** head)
{
	TimerNode* last = *head;
	int temp = timer_node_num;
	while(temp) {
		Timer_proc(&last->timer);
		temp--;
		last = last->next;
	}
}