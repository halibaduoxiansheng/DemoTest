// /**
//  * 可以分情况的 枚举
//  * 对于较复杂的情况采用 switch case，简单的使用 if…else
//  * 对于可以增加、可以减少的任何东西 使用链表
//  */
// #define INIT
// 	#define __init 
// 	#define bool int
// #endif

// #define TRUE 1
// #define FALSE 0
// #define NORMAL 0
// #define ERROR 1

// void hardware_init(void);
// bool button_register(void (*fun)(int));
// static void button_apply(int choice);
// bool check_isempty(void *p);
// void free_power_allpointer(Power *power)

// typedef void (*led_control)(int);
// typedef void (*button_control)(int);

// typedef enum COLOR{
// 	WHITE = 0,
// 	RED,
// 	YELLOW,
// 	BLUE,
// 	ORANGE
// }Color_t;
// Color_t color = WHITE;

// typedef struct {
// 	int age;
// 	led_control led_ctl;
// 	Button *button;
// }Power;
// Power *power;

// typedef struct BUTTON{
// 	struct BUTTON *prev;
// 	struct BUTTON *next;
// 	int count;
// 	button_control button_ctl; // 难不成每增加一个按钮都需要设置一个注册函数
// 	int status : 1; // 设置位的大小 空间的大小是十分可贵的
// }Button;

// int g_status = 0; // 全局变量
// /* （见名知意）
//  * 起名规范 先 g 或 l 表示 全局 还是 局部
//  * 再 功能 设置就set 标志就flag
//  * 最后 作用谁 灯就led 按钮就button
//  * 例如：g_flag_led
//  */


// int main(void)
// {
// 	hardware_init();

// 	button_register(button_apply);

// 	free_power_allpointer(power);
// 	return 0;
// }

// __init void hardware_init(void)
// {
// 	int l_status; // 局部变量
// 	// code
// }

// static void button_apply(int choice)
// {
// 	//code
// }

// bool button_register(void (*fun)(int))
// {
// 	if(check_isempty(power)) {
// 		power = (Power *)malloc(sizeof(Power));
// 		if (power == NULL) {
// 			printf("power申请空间失败");
// 			return ERROR;
// 		} else {
// 			if (check_isempty(power->button)) {
// 				power->button = (Button *)malloc(sizeof(Button));
// 				if (power->button == NULL) {
// 					printf("power->button申请空间失败");
// 					return ERROR;
// 				}
// 			}
// 		}
// 	} else {
// 		if (check_isempty(power->button)) {
// 			power->button = (Button *)malloc(sizeof(Button));
// 			if (power->button == NULL) {
// 				printf("power->button申请空间失败");
// 				return ERROR;
// 			}
// 		}
// 	}
// 	power->button->button_ctl = fun;
// 	return NORMAL;
// }

// Button *button_add(void)
// {
// 	Button *button = (Button *)malloc(sizeof(Button));
// 	// TODO 链表的结构体如何写 还有删除 还有 对对应的按钮的操作
// 	// 还缺好init函数、按钮事件枚举类型
// 	// 按钮既然会有多个、就说明需要编号
// 	// cnt、像这种都是需要做到防抖 那么需要一个匹配的计数值
// 	// 创建一个静态的头节点（按钮）
// 	// 有加就有删、有设置就有得到、
// 	// 安全、是否已经存在、是否为空、
// 	// 一个统一的处理事件（优先级自己考虑）
// 	return button;
// }

// bool check_isempty(void *p)
// {
// 	if (p == NULL) {
// 		return TRUE; 
// 	} else {
// 		return FALSE;
// 	}
// }
// /**
//  * [free_power_allpointer 释放内存] 
//  * @param power [指针]
//  */
// void free_power_allpointer(Power *power) {
//     if (power == NULL) { // 避免未定义行为 && 避免 power=>button野指针错误
//         return;
//     }

//     if (power->button != NULL) { // 注意释放顺序
//         free(power->button);
//     }

//     free(power);
// }

// // 用法：  uint_t bro; NAME(bro);
// #define ERR -1
// #define NAME(name) NAMEFOR(name, ERR)
// #define NAMEFOR(name, ret) NAMEFOR2(name, return ret)
// #define NAMEFOR2(name, hello) do { \
// 							name = balabala(); \
// 							hello; \
// 						} while(0)


// // 比较常使用的for循环可以使用宏定义代替
// // 双向链表的遍历 (如此，n始终是pos的next)
// // safe的原因是：即使过程中删除了pos，仍旧可以使用n来继续下一个遍历
// #define list_for_each_safe(pos, n, head) \
// 				for (pos = (head)->next, n = pos->next; pos != head; \
// 					pos = n, n = pos->next)

// // 函数指针
// typedef int (*commom_id)(int );
// commom_id commom_id1; // 此时的commom_id1 还是NULL的
// int common(int cnt) {
// 	return ++cnt;
// }
// commom_id1 = common;
// if(commom_id1) { 
//  // code 
// } // 判断是否指向一个 有效 函数地址
