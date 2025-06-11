#ifndef __I4S_BK_LED_H__
#define __I4S_BK_LED_H__
/**
 * This led library is temporarily adapted to bk7258
 */
#include "stdio.h"

#define LED_BREATH_SUPPORT  (1) /* 是否支持呼吸灯 */
#define USE_DEFINE_FIAMREWORK   (0) /* 是否使用 i4s_led_def_by_youself 架构 */


#define LED_NOT_BLINK   0
#define LED_IS_BLINK    1
#define LED_NEED_LINGHT 1
#define LED_NEED_DARK   0

#if LED_BREATH_SUPPORT
 #define DUTY_MAX_INDEX  10
 #define PWM_USE_ID    PWM_ID_2
#endif

enum {
    LED_IDLE = 0,   
    LED_CHECK = 1,
    LED_LIGHT_CHECK = 2,
    LED_DARK_CHECK = 3,
};

#if LED_BREATH_SUPPORT
struct G_BK_Breath {
    uint8_t is_breath : 1;
    uint8_t breath_inited : 1;
    uint8_t is_breathing : 1;
    uint8_t should_succeed : 1;
    uint8_t duty_arry_index : 4; /* NOTE MAX index 14 */
    uint16_t duty_arry[DUTY_MAX_INDEX];
    uint16_t period;
}__attribute__((packed));
#endif


struct G_BK_LED {
    uint8_t led_show : 1; /* control power, if is 0, then this lib lost its control power
        then the led will keep last state forever until we can control it */
    uint8_t is_blink : 1;
    uint8_t active_level : 1;
    uint8_t led_level : 1;
    uint8_t need_level : 1;
    uint8_t is_light : 1; /* just blink mode use and change */

    uint8_t reserve : 2;

#if LED_BREATH_SUPPORT
    struct G_BK_Breath *breath;    
#endif

    uint16_t blink_count;

    /*  
     led_thd.interval * ticks * unit Vs time
    */
    uint8_t basic_unit; /* basic unit of time  -> ms 函数的 执行周期*/
    uint16_t brignt_time; // ms
    uint16_t dark_time;

    uint8_t state;

    uint16_t bright_ticks;
    uint16_t dark_ticks;

    uint8_t led_io;

    void (*turn_on)(struct G_BK_LED*);
    void (*turn_off)(struct G_BK_LED*);
    uint8_t (*read_level)(struct G_BK_LED*);
    void (*set_light)(struct G_BK_LED*);

    // uint8_t led_name[10]; // if you want debug ,you can choose open it
}__attribute__((packed));

/**
 * Step1
 * @brief  register led object
 * 
 * struct G_BK_LED led_arrays[] = {
 *     {
 *          .led_show = 1,
            .led_io = PA_4,
            .active_level = 1,
            .state = LED_IDLE,
            .basic_unit = 1,
 *     }, {
 *          .led_show = 1,
            .led_io = PA_5,
            .active_level = 1,
            .state = LED_IDLE,
            .basic_unit = 1,
 *     }, {
 *          .led_show = 1,
            .led_io = PA_3,
            .active_level = 1,
            .state = LED_IDLE,
            .basic_unit = 1,
 *     }
 * };
 */
void i4s_bk_led_register(struct G_BK_LED led_arrays[], uint8_t size);

/**
 * @brief  set led mode , if someone arg you do not use,you can choose input 0
 * @param  led object
 * @param  is_blink: 1:blink,0:not blink （just set this is 1, or we will not check blink_count）
 * @param  blink_count: If you want it to blink forever, please set it to I4S_BLINK_FOREVER .
 * @param  basic_unit: basic unit of time  -> ms
 * @param  brignt_time: brightness time  -> ms
 * @param  dark_time: dark time  -> ms
 * @param  need_light   >=1: should to light(always on)  0: should not
 */
// void i4s_set_linght_mode(struct G_BK_LED *param1, uint8_t param2, ...);

void i4s_bk_led_thread_init(void);

#if USE_DEFINE_FIAMREWORK
/* NOTE 启动一个线程 为led状态 运行 （这个功能如果不需要 可以不使用） */
void i4s_led_def_by_youself(void); /* 启动线程 i4s_led_check_thread */
#endif

/* 设置灯光闪烁 */
void i4s_set_linght_mode_blink(struct G_BK_LED *led, uint8_t is_blink, uint16_t blink_count 
    , uint8_t basic_unit, uint16_t brignt_time, uint16_t dark_time);

/* 设置灯光常亮、灭 */
void i4s_set_linght_mode_steady(struct G_BK_LED *led, uint8_t is_blink, uint8_t need_status);

#if LED_BREATH_SUPPORT
void i4s_set_linght_mode_breath(struct G_BK_LED *led, uint16_t duty_arry[DUTY_MAX_INDEX], uint16_t period, uint8_t basic_unit);
#endif

#endif // end __I4S_BK_LED_H__