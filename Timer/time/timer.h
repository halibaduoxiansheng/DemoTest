#ifndef __TIMER_H__
#define __TIMER_H__


enum TIMER_TYPE
{
	TIMER_CLOSE = 0,
	TIMER_REPEAT,
	TIMER_ONCE,
};

/**
 * [Timer_Create_Node 创建定时器链表]
 * @param  timer [定时器变量]
 * @return       [链表成员]
 */
TimerNode* Timer_Create_Node(TIMER_CLASS_T timer);
/**
 * [TimerNodeAppend 增加定时器变量到链表中]
 * @param head  [链表头指针的指针]
 * @param timer [定时器变量]
 */
void TimerNodeAppend(TimerNode** head, TIMER_CLASS_T* timer);
/**
 * [TimerNodeDelete 将定时器从链表中删除]
 * @param head  [链表头指针的指针]
 * @param timer [定时器变量]
 */
void TimerNodeDelete(TimerNode** head, TimerNode* timer);
/**
 * [Timer_set 设置定时器]
 * @param this     [定时器指针变量]
 * @param type     [定时器类型 - TIMER_TYPE]
 * @param timer_cb [定时器回调函数]
 */
void Timer_set(TIMER_CLASS_T *this, uint_8 type, timer_callback timer_cb);
Timer_proc();


extern volatile TIMER_CLASS_T timer_1;
extern int timer_node_num = 0;

#endif