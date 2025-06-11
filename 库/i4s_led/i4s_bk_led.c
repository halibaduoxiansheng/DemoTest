#include "i4s_bk_led.h"
#include "i4s_ble_net.h"
#include "i4s_bk_bat.h"
#include "i4s_list_node.h"

#include <driver/pwm_types.h>
#include <driver/pwm.h>
#include "gpio_driver.h"

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <driver/gpio.h>
#include <common/bk_include.h>
#include <common/bk_typedef.h>
#include <os/os.h>
#include <os/mem.h>
#include <driver/hal/hal_gpio_types.h>
#include "bk_uart.h"


/* 
 * i4s bk7258 led lib by wangjie on 2025.5.22
*/

#define I4S_BLINK_FOREVER   (66)

static beken_mutex_t s_i4s_mutex;

static uint8_t i4s_bk_led_thread_inited = 0;

/**
 * All button events are placed in this thread
 */
struct TX_LED_Thd {
    void *thread;
    uint16_t stack_size;
    char stack_name[15];
    uint8_t priority;
    uint16_t interval;
    void *args;

    void (*trd_func)(void*);
};
struct TX_LED_Thd led_thd;
#if USE_DEFINE_FIAMREWORK
struct TX_LED_Thd led_check_thd;
#endif

enum{
    OP_GET = 0,
    OP_SET = 1,
};

enum {
    OP_LED_OFF = 0,
    OP_LED_ON = 1,
};


#define SIMPLE_SET  (1)  /* NOTE 这里是两种点亮的方式开关 */
/* NOTE 这里适配一下 因为 高电平给的是 0x2，低电平是 0 */
static void gpio_set_val_alive(struct G_BK_LED *led) {
#if SIMPLE_SET
    if (led->active_level) {
        bk_gpio_set_output_high(led->led_io);
    } else {
        bk_gpio_set_output_low(led->led_io);
    }
#else
    if (led->active_level) {
        bk_gpio_set_value(led->led_io, 0x2);
    } else {
        bk_gpio_set_value(led->led_io, 0x0);
    }
#endif
}

static void gpio_set_val_die(struct G_BK_LED *led) {
#if SIMPLE_SET
    if (led->active_level) {
        bk_gpio_set_output_low(led->led_io);
    } else {
        bk_gpio_set_output_high(led->led_io);
    }
#else
    if (led->active_level) {
        bk_gpio_set_value(led->led_io, 0x0);
    } else {
        bk_gpio_set_value(led->led_io, 0x2);
    }
#endif
}

static void gpio_control_val_life(struct G_BK_LED *led) {
#if SIMPLE_SET
    if (led->need_level) {
        bk_gpio_set_output_high(led->led_io);
    } else {
        bk_gpio_set_output_low(led->led_io);
    }
#else
    if (led->need_level) {
        bk_gpio_set_value(led->led_io, 0x2);
    } else {
        bk_gpio_set_value(led->led_io, 0x0);
    }
#endif
}

static uint8_t gpio_get_val_life(struct G_BK_LED *led) {
// #if SIMPLE_SET
//     /* BUG 这里暂时没有办法获取电位高低 */
//     // return rt_pin_read(led->led_io); /* REVIEW */
// #else
//     uint32_t value = bk_gpio_get_value(led->led_io);
//     if (value) {
//         return 1;
//     } else {
//         return 0;
//     }
// #endif
    return led->is_light;  /* REVIEW 暂且没有找到能提供电压高低的函数 */
}

static void i4s_bk_led_init(struct G_BK_LED *led)
{
    uint8_t ret = 0;
    if (led == NULL) {
        bk_printf("i4s_led_init failed,this is a NULL arg\r\n");
        return ;
    }

    led->turn_on = gpio_set_val_alive;
    led->turn_off = gpio_set_val_die;
    led->set_light = gpio_control_val_life;
    led->read_level = gpio_get_val_life;
#if LED_BREATH_SUPPORT
    led->breath = NULL;
#endif

#if SIMPLE_SET
    gpio_dev_unmap(led->led_io);
    // bk_gpio_disable_input(led->led_io);
    // bk_gpio_enable_input(led->led_io);
    bk_gpio_disable_output(led->led_io);
    bk_gpio_enable_output(led->led_io);
    bk_gpio_disable_pull(led->led_io);
    bk_gpio_enable_pull(led->led_io);
    bk_gpio_set_capacity(led->led_io, 3); /* NOTE 驱动能力 */
#else
    bk_gpio_disable_input(led->led_io);
    bk_gpio_enable_input(led->led_io);
#endif

    if (led->active_level) { /* init level */
        led->turn_off(led);
        led->is_light = 0;
    } else {
        led->turn_on(led);
        led->is_light = 1;
    }

    if ((ret = hali_link_list_init()) != 0) {
        bk_printf("something error!\r\n");
    }

    bk_printf("add led->led_io (%d) to list \r\n", led->led_io);
    if (hali_link_list_add((void *)led, sizeof(struct G_BK_LED), TYPE_LED) != 0) {
        bk_printf("something error!\r\n");
    }
}
/* NOTE 注意指针退化问题 */
void i4s_bk_led_register(struct G_BK_LED led_arrays[], uint8_t size)
{
    uint8_t i = 0;
    for (i = 0; i < size; i++) {
        i4s_bk_led_init(&led_arrays[i]);
    }
}

#if LED_BREATH_SUPPORT
void i4s_set_linght_mode_breath(struct G_BK_LED *led, uint16_t duty_arry[DUTY_MAX_INDEX], uint16_t period, uint8_t basic_unit) {
    rtos_lock_mutex(&s_i4s_mutex);
    if (led == NULL) {
        rtos_unlock_mutex(&s_i4s_mutex);
        bk_printf("i4s_set_linght_mode_breath failed,this is a NULL arg\r\n"); 
        return ;
    }

    if (led->breath) {
        free(led->breath);
        led->breath = NULL;
    }
    led->breath = (struct G_BK_Breath *)malloc(sizeof(struct G_BK_Breath));
    if (!led->breath) {
        bk_printf("malloc led->breath error\r\n");
        return ;
    }
    os_memset(led->breath, 0x0, sizeof(struct G_BK_Breath));

    led->breath->is_breath = 1;
    led->breath->period = period;
    led->basic_unit = basic_unit; /* NOTE unit * led_thd.interval 跟换一次 duty */

    
    os_memcpy(led->breath->duty_arry, duty_arry, sizeof(uint16_t) * DUTY_MAX_INDEX);

    bk_printf("set led->led_io(%d) to breath\r\n", led->led_io);
    rtos_unlock_mutex(&s_i4s_mutex);
}
#endif

void i4s_set_linght_mode_blink(struct G_BK_LED *led, uint8_t is_blink, uint16_t blink_count 
    , uint8_t basic_unit, uint16_t brignt_time, uint16_t dark_time) 
{
    rtos_lock_mutex(&s_i4s_mutex);
    if (led == NULL) {
        bk_printf("i4s_set_linght_mode_blink failed,this is a NULL arg\r\n"); 
        rtos_unlock_mutex(&s_i4s_mutex);
        return ;
    }

    if (is_blink >= 1) {
        if (blink_count > 0 && basic_unit > 0 && brignt_time > 0 && dark_time > 0) {
            led->is_blink = 1;
            led->blink_count = blink_count;
            led->basic_unit = basic_unit;
            led->brignt_time = brignt_time;
            led->dark_time = dark_time;
            led->need_level = !led->read_level(led);
#if LED_BREATH_SUPPORT
            if (led->breath) {
                led->breath->is_breath = 0;
            }
#endif
        } else {
            bk_printf("i4s_set_linght_mode failed,some one of args is invail\r\n");
        }
    }

    bk_printf("set led->led_io(%d) to blink\r\n", led->led_io);
    rtos_unlock_mutex(&s_i4s_mutex);
}

void i4s_set_linght_mode_steady(struct G_BK_LED *led, uint8_t is_blink, uint8_t need_status) 
{   
    rtos_lock_mutex(&s_i4s_mutex);
    if (led == NULL) {
        bk_printf("i4s_set_linght_mode_steady failed,this is a NULL arg\r\n"); 
        rtos_unlock_mutex(&s_i4s_mutex);
        return ;
    }

    if (is_blink == 0) { // not blink
        led->is_blink = 0;
        if (need_status == 0) {
            led->need_level = !led->active_level;
        } else {
            led->need_level = led->active_level;
        }
    }

#if LED_BREATH_SUPPORT
    if (led->breath) {
        led->breath->is_breath = 0;
    }
#endif

    bk_printf("set led->led_io(%d) to steady\r\n", led->led_io);
    rtos_unlock_mutex(&s_i4s_mutex);
}

static uint16_t i4s_led_getLightTime(struct G_BK_LED *led) {
    return led->bright_ticks * led->basic_unit;
}

static uint16_t i4s_led_getDarkTime(struct G_BK_LED *led) {
    return led->dark_ticks * led->basic_unit;
}

#if LED_BREATH_SUPPORT /* TODO 待验证功能完整性 */
static uint8_t breath_dealwith(struct G_BK_LED *led)
{
    if (led == NULL) {
        return 0; /*  */
    }
    if (led->breath && led->breath->is_breath) { /* NOTE 呼吸灯优先级最高 */
        bk_printf("led->breath->is_breath is %d, led->breath->period is %d, led->breath->duty_arry_index is %d\r\n",
            led->breath->is_breath, led->breath->period, led->breath->duty_arry_index);
        if (!led->breath->is_breathing || led->breath->should_succeed) {
            led->breath->duty_arry_index = led->breath->duty_arry_index % DUTY_MAX_INDEX;

            /* init */ 
            if (!led->breath->breath_inited) { /* PWM_USE_ID */
                // gpio_dev_unmap(led->led_io);
                // gpio_dev_map(led->led_io, PWM_USE_ID); /* 下面 bk_pwm_init 已经做了 不需要手动 */
                // bk_gpio_pull_up(led->led_io);

                /* idle init */
                pwm_init_config_t config = {
                    .period_cycle = led->breath->period,
                    .duty_cycle = led->breath->duty_arry[led->breath->duty_arry_index],
                    .psc = 25,
                };
                
                bk_pwm_driver_deinit();
                bk_pwm_driver_init(); /* NOTE 线程安全的 可多次初始化 */
                bk_pwm_set_init_signal_high(PWM_USE_ID);
                bk_pwm_init(PWM_USE_ID, &config);
                // bk_pwm_set_init_signal_high(PWM_USE_ID);
                bk_pwm_start(PWM_USE_ID);
                led->breath->breath_inited = 1;
            }

            bk_pwm_stop(PWM_USE_ID);
            bk_printf("config1.duty_cycle is %d\r\n", led->breath->duty_arry[led->breath->duty_arry_index]);
            pwm_period_duty_config_t config1 = {
                .period_cycle = led->breath->period,
                .duty_cycle = led->breath->duty_arry[led->breath->duty_arry_index++],
                .psc = 25,
            };
            bk_pwm_set_period_duty(PWM_USE_ID, &config1);
            bk_pwm_start(PWM_USE_ID);

            if (led->breath->should_succeed) {
                led->breath->should_succeed = !led->breath->should_succeed;
            }
            if (!led->breath->is_breathing) {
                led->breath->is_breathing = !led->breath->is_breathing;
            }
        }
        /* 这里随便使用一个 ticks */
        if ((led->bright_ticks++) % led->basic_unit == 0) {
            led->breath->should_succeed = !led->breath->should_succeed;
        }

        return 0;
    } else {
        if (led->breath && led->breath->is_breathing) { /* NOTE 说明此时需要停止PWM */
            led->breath->should_succeed = 0;
            led->bright_ticks = 0;
            led->breath->is_breathing = 0;
            led->breath->duty_arry_index = 0; /* duty 复原位 */
            if (led->breath->breath_inited) {
                bk_pwm_stop(PWM_USE_ID);
                bk_pwm_driver_deinit();
                led->breath->breath_inited = 0;
            } 
        }
        if (led->breath) {
            free(led->breath);
            led->breath = NULL;
        }
        return 1;
    }
}
#endif

static void i4s_bk_led_hander(struct G_BK_LED **target) // 200ms
{
    // bk_printf("%s:%d\r\n", __FUNCTION__, __LINE__);    

    if (*target == NULL) {
        return;
    }
    struct G_BK_LED *led = *target;
    // bk_printf("led->led_io is %d\r\n", led->led_io);
    if (led == NULL) {
        return ;
    }

    if (!led->led_show) { 
        bk_printf("we do not have this led control power now\r\n");
        /* ==> 也就是之前是啥状态就啥状态 */
        return ;
    }


#if LED_BREATH_SUPPORT
    // bk_printf("start dealwith led breath\r\n");
    if (breath_dealwith(led) == 0) {
        return ;
    }
#endif

    if (led->read_level) {
        led->led_level = led->read_level(led); // read local led level
        // bk_printf("led->led_level is %d, led->need_level is %d\r\n", led->led_level, led->need_level);
    } else {
        bk_printf("big problem, please check the read_level\r\n");
        return ;
    }

    // calc ticks
    // bk_printf("led->is_blink is %d, led->blink_count is %d\r\n", led->is_blink, led->blink_count);
    if (led->is_blink && led->blink_count > 0) {
        if (led->led_level == led->active_level) { // light now then start ticks
            led->bright_ticks++;
            led->dark_ticks = 0;
            // led->is_light = 1;  /* TODO 不得已将此修改转移 加在了每个turn_on的位置 */
            // bk_printf("now is linght\r\n");
        } else {
            led->dark_ticks++;
            led->bright_ticks = 0;
            // led->is_light = 0; /* TODO 不得已将此修改转移 加在了每个turn_on的位置 */
            // bk_printf("now is dark\r\n");
        }
    } else if (led->is_blink && led->blink_count == 0){ 
        led->is_blink = 0;
        led->need_level = !led->active_level; // NOTE  闪动结束 以熄灭状态结尾
    } else { // is not blink
        led->bright_ticks = 0;
        led->dark_ticks = 0;
    }

    // bk_printf("led->bright_ticks is %d, led->dark_ticks is %d\r\n", led->bright_ticks, led->dark_ticks);
    // bk_printf("led->state is %d, led->brignt_time is %d, led->dark_time is %d, led->basic_unit is %d\r\n", led->state,
    //          led->brignt_time, led->dark_time, led->basic_unit);
    // bk_printf("led->active_level is %d\r\n", led->active_level);
    if (led->is_blink) {
        switch(led->state) {
            case LED_IDLE:
                led->state = LED_CHECK; /* NOTE 这里每次都会多走两轮 如果嫌弃费事 可以直接改这 */
                break;
            case LED_CHECK:
                // start ticks base on current light level
                if (led->is_light) {
                    led->state = LED_LIGHT_CHECK;
                } else {
                    led->state = LED_DARK_CHECK;
                }
                break;
            case LED_LIGHT_CHECK:
                 led->state = LED_IDLE;
                 // bk_printf("i4s_led_getLightTime(led) is %d\r\n", i4s_led_getLightTime(led));
                 if (i4s_led_getLightTime(led) >= led->brignt_time) {
                        // bk_printf("will turn off\r\n");
                        led->need_level = !led->need_level;
                        led->dark_ticks = 0;
                        if (led->turn_off) {
                            led->turn_off(led);
                            led->is_light = 0;
                        } else {
                            // bk_printf("please check youself 3\r\n");
                        }
                        if (led->blink_count != I4S_BLINK_FOREVER) { // I4S_BLINK_FOREVER meaning forever
                            led->blink_count--;
                        }
                 }
                 break;
            case LED_DARK_CHECK:
                 led->state = LED_IDLE;
                 // bk_printf("i4s_led_getDarkTime(led) is %d\r\n", i4s_led_getDarkTime(led));
                 if (i4s_led_getDarkTime(led) >= led->dark_time) {
                        // bk_printf("will turn on\r\n");
                        led->need_level = !led->need_level;
                        led->bright_ticks = 0;
                        if (led->turn_on) {
                            led->turn_on(led);
                            led->is_light = 1;
                        } else {
                            // bk_printf("please check youself 2\r\n");
                        }
                 }
                 break;
            default:
                led->state = LED_IDLE;
                break;
        }
    } else { // not blink
        if (led->set_light) {
            led->set_light(led);
        } else {
            // bk_printf("please check youself 1\r\n");
        }
    }
}

#if USE_DEFINE_FIAMREWORK
/// please use above frame, you just need put your needs in it (the function is i4s_set_linght_mode)
void i4s_led_def_by_youself(void)
{
    void *thread = NULL;
    if (!thread) {
        // bk_printf("%s:%d\r\n", __FUNCTION__, __LINE__);
        
        /* thread func is i4s_led_check_thread */
        rtos_create_thread((beken_thread_t)&thread, led_check_thd.priority, (const char *)led_check_thd.stack_name
                , ((beken_thread_function_t))led_check_thd.trd_func, led_check_thd.stack_size, led_check_thd.args);
    }
}
#endif


static void i4s_bk_led_thread(void *arg)
{
    if (!arg) {
        bk_printf("thread args is NULL");
        return ;
    }
    struct TX_LED_Thd *target = (struct TX_LED_Thd *)arg;
    if (!target->interval) {
        bk_printf("thread args->interval is 0");
        return ;
    }

    struct list_head *start_pos = NULL;
    void *data = NULL;

    for (;;rtos_delay_milliseconds(target->interval)) {
        data = hali_link_list_traverse(TYPE_LED, &start_pos);
        if (data) {
            struct G_BK_LED *led = (struct G_BK_LED *)data;
            rtos_lock_mutex(&s_i4s_mutex);
            i4s_bk_led_hander(&led);
            rtos_unlock_mutex(&s_i4s_mutex);
        }
    }
}

#if USE_DEFINE_FIAMREWORK
/* NOTE 想使用 这里就自己去适配 这里需要适配的 */
static void i4s_led_check_thread(void *args)
{
    // bk_printf("%s:%d\r\n", __FUNCTION__, __LINE__);
    struct TX_LED_Thd *led_ck = NULL;
    if (args) {
        led_ck = (struct TX_LED_Thd *)args;
    } else {
        bk_printf("%s args is NULL\r\n", __func__);
        return ;
    }
    for (;;rtos_delay_milliseconds((uint32_t)led_ck->interval)) {
        if (i4s_energy.is_powerOn) { // power on
            if (i4s_energy.is_charging) { // power on + is charging
                if (i4s_energy.is_full) { // power on + is charging + full
                    if (!i4s_net.net_is_connected) { // power on + is charging + full + wifi not connected
                        
                    } else {  // power on + is charging + full + wifi connected
                        
                    }
                } else { //power on + is charging + not full
                    if (!i4s_net.net_is_connected) { // power on + is charging + not full + wifi not connected
                        
                    } else {  // power on + is charging + not full + wifi connected
                        
                    }
                }
            } else { // poweron + not charging
                if (i4s_energy.low_bat_remind) { // power on + not charging + low battery
                    if (i4s_net.net_is_connected) { // poweron + not charging + low battery + wifi connected
                        
                    } else { // poweron  + not charging + low battery + wifi not connected
                        
                    }
                } else { // power on + not charging + not low battery
                    if (i4s_net.net_is_connected) { // poweron + not charging + not low battery + wifi connected
                        
                    } else { // poweron  + not charging + not low battery + wifi not connected
                        
                    }
                }
            }
        } else { // power off
            if (i4s_energy.is_charging) { // power off + is charging
                if (i4s_energy.is_full) { // power off + is charging + full
                    
                } else { // power off + is charging + not full
                    
                }
            } else { // power off + not charging
                
            }
        }
    }
}
#endif

/*  */
void i4s_bk_led_thread_init(void)
{
    if (!i4s_bk_led_thread_inited) {
        i4s_bk_led_thread_inited = 1;
    } else {
        return ;
    }

    void *thread;
    rtos_init_mutex(&s_i4s_mutex);

    os_memset(&led_thd, 0x0, sizeof(struct TX_LED_Thd));
    led_thd = (struct TX_LED_Thd) {
        .priority = 6,
        .stack_size = 1536,
        .trd_func = i4s_bk_led_thread,
        .interval = 200,
        .args = NULL,
    };
    os_memcpy(led_thd.stack_name, "led_task", strlen("led_task"));
    led_thd.args = &led_thd;

#if USE_DEFINE_FIAMREWORK
    memset(&led_check_thd, 0, sizeof(struct TX_LED_Thd));
    memcpy(led_check_thd.stack_name, "led_check_thd", strlen("led_check_thd"));
    led_check_thd = (struct TX_LED_Thd) {
        .priority = 6,
        .stack_size = 512,
        .trd_func = i4s_led_check_thread,
        .interval = 400,
        .args = &led_check_thd,
    };
#endif
    
    // bk_printf("led task ready to run\r\n");
    /* 两个线程 前一个线程必须需要执行， 后一个线程用户选择性自己增加 => USE_DEFINE_FIAMREWORK */
    rtos_create_thread((beken_thread_t)&thread, led_thd.priority, led_thd.stack_name
                , (beken_thread_function_t)led_thd.trd_func, led_thd.stack_size, led_thd.args);
}