#include "timer.h"


void red_led_slow_blink(void);

TimerNode* head = NULL;

int (void)
{
	Timer_set(&timer_1, TIMER_REPEAT, red_led_slow_blink);
	// code
	TimerNode* timer_node1 = TimerNodeAppend(&head, timer_1);

	for(;;Timer_delay(50))
	{
		TimerForEach(&head);
		//Timer_proc();
	}
}

void red_led_slow_blink(void)
{
	//code
}