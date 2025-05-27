#include "i4s_bk_led.h"

/* 
 * i4s bk7258 led lib by wangjie on 2025.5.22
*/

enum {
    LED_IDLE = 0,   
    LED_CHECK = 1,
    LED_LIGHT_CHECK = 2,
    LED_DARK_CHECK = 3,
};

#define I4S_BLINK_FOREVER   (66)

#if LED_BREATH_SUPPORT
static uint8_t duty_arry_index = 0;
#endif


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
struct TX_LED_Thd led_check_thd;

enum{
    OP_GET = 0,
    OP_SET = 1,
};

enum {
    OP_LED_OFF = 0,
    OP_LED_ON = 1,
};

static uint8_t gpio_set_val_alive(struct G_BK_LED *led) {
    return bk_gpio_set_value(led->led_io, led->active_level);
}

static uint8_t gpio_set_val_die(struct G_BK_LED *led) {
    return bk_gpio_set_value(led->led_io, !led->active_level);
}

static uint8_t gpio_control_val_life(struct G_BK_LED *led) {
    return bk_gpio_set_value(led->led_io, led->need_level);
}

static uint8_t gpio_get_val_life(struct G_BK_LED *led) {
    return bk_gpio_get_value(led->led_io);
}

void i4s_bk_led_init(struct G_BK_LED *led)
{
    uint8_t ret = 0;
    if (led == NULL) {
        bk_printf("i4s_led_init failed,this is a NULL arg\r\n");
    }

    led->turn_on = gpio_set_val_alive;
    led->turn_off = gpio_set_val_die;
    led->set_light = gpio_control_val_life;
    led->read_level = gpio_get_val_life;

    if (ret = hali_link_list_init() != 0) {
        bk_printf("something error!\r\n");
    }

    if (hali_link_list_add((void *)led, sizeof(struct G_BK_LED), TYPE_LED) != 0) {
        bk_printf("something error!\r\n");
    }
}

void i4s_bk_led_register(struct G_BK_LED led_arrays[])
{
    uint8_t i = 0;
    for (i = 0; i < sizeof(led_arrays)/sizeof(struct G_BK_LED); i++) {
        i4s_bk_led_init(&led_arrays[i]);
    }
}

#if LED_BREATH_SUPPORT
void i4s_set_linght_mode_breath(struct G_BK_LED *led, uint16_t duty_arry[DUTY_MAX_INDEX], uint16_t period, uint8_t basic_unit) {
    if (led == NULL) {
        bk_printf("i4s_set_linght_mode_breath failed,this is a NULL arg\r\n"); 
    }

    led->is_breath = 1;
    led->period = period;
    led->basic_unit = basic_unit; /* NOTE unit * led_thd.interval 跟换一次 duty */

    os_memset(led->duty_arry, 0x0, DUTY_MAX_INDEX);
    strcpy(led->duty_arry, duty_arry);
}
#endif

void i4s_set_linght_mode_blink(struct G_BK_LED *led, uint8_t is_blink, uint16_t blink_count 
    , uint8_t basic_unit, uint8_t brignt_time, uint8_t dark_time) 
{
    if (led == NULL) {
        bk_printf("i4s_set_linght_mode_blink failed,this is a NULL arg\r\n"); 
    }

    if (is_blink >= 1) {
        if (blink_count > 0 && basic_unit > 0 && brignt_time > 0 && dark_time > 0) {
            led->is_blink = 1;
            led->blink_count = blink_count;
            led->basic_unit = basic_unit;
            led->brignt_time = brignt_time;
            led->dark_time = dark_time;
            led->need_level = !led->read_level(led);
        } else {
            bk_printf("i4s_set_linght_mode failed,some one of args is invail\r\n");
        }
    }
}

void i4s_set_linght_mode_steady(struct G_BK_LED *led, uint8_t is_blink, uint8_t need_status) 
{
    if (led == NULL) {
        bk_printf("i4s_set_linght_mode_steady failed,this is a NULL arg\r\n"); 
    }

    if (is_blink == 0) { // not blink
        led->is_blink = 0;
        if (need_status == 0) {
                led->need_level = !led->active_level;
        } else {
            led->need_level = led->active_level;
        }
    }
}

static uint16_t i4s_led_getLightTime(struct G_BK_LED *led) {
    return led->bright_ticks * led->basic_unit;
}

static uint16_t i4s_led_getDarkTime(struct G_BK_LED *led) {
    return led->dark_ticks * led->basic_unit;
}

static void i4s_bk_led_hander(struct Double_link_list *target)
{
    // bk_printf("%s:%d\r\n", __FUNCTION__, __LINE__);
    if (target == NULL) {
        return;
    }
    struct G_BK_LED *led = target->led;
    if (led == NULL) {
        return ;
    }

    if (!led->led_show) { 
        // bk_printf("we do not have this led control power now\r\n");
        return ;
    }

#if LED_BREATH_SUPPORT
    static uint8_t is_breathing = 0, should_succeed = 0;
    if (led->is_breath) {
        if (!is_breathing || should_succeed) {
            pwm_init_config_t config = {0};
            config.period_cycle = led->period;
            config.duty_cycle = led->duty_arry[duty_arry_index++];
            duty_arry_index = duty_arry_index % DUTY_MAX_INDEX;
            bk_pwm_driver_init(); /* NOTE 线程安全的 可多次初始化 */
            bk_pwm_init(PWM_ID_1, &config);
            bk_pwm_start(PWM_ID_1);
            if (should_succeed) {
                should_succeed = !should_succeed;
            }
            is_breathing = !is_breathing;
        }
        /* 这里随便使用一个 ticks */
        if ((led->bright_ticks++) % led->basic_unit == 0) {
            should_succeed = !should_succeed;
        }

        return ;
    } else {
        if (is_breathing) { /* NOTE 说明此时需要停止PWM */
            if (should_succeed) {
                should_succeed = !should_succeed;
            }
            led->bright_ticks = 0;
            is_breathing = !is_breathing;
            duty_arry_index = 0; /* duty 复原位 */
            bk_pwm_stop(PWM_ID_1);
            bk_pwm_driver_deinit();
        }
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
            led->is_light = 1;
            // bk_printf("now is linght\r\n");
        } else {
            led->dark_ticks++;
            led->bright_ticks = 0;
            led->is_light = 0;
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
    if (led->led_level != led->need_level) { // mean led mode should change
         if (led->is_blink) {
            switch(led->state) {
                case LED_IDLE:
                    led->state = LED_CHECK;
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
                     if (i4s_led_getLightTime(led) >= led->brignt_time) {
                            led->need_level = !led->need_level;
                            led->dark_ticks = 0;
                            if (led->turn_off) {
                                led->turn_off(led);
                            }
                            if (led->blink_count != I4S_BLINK_FOREVER) { // I4S_BLINK_FOREVER meaning forever
                                led->blink_count--;
                            }
                     }
                     break;
                case LED_DARK_CHECK:
                     led->state = LED_IDLE;
                     if (i4s_led_getDarkTime(led) >= led->dark_time) {
                            led->need_level = !led->need_level;
                            led->bright_ticks = 0;
                            if (led->turn_on) {
                                led->turn_on(led);
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
            }
         }
    }
}

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


static void i4s_bk_led_thread(void *arg)
{
    if (!arg) {
        bk_printf("thread args is NULL");
        ASSERT(0);
    }
    struct TX_LED_Thd *target = (struct TX_LED_Thd *)arg;
    if (!target->interval) {
        bk_printf("thread args->interval is 0");
        ASSERT(0);
    }

    struct list_head *start_pos = NULL;

    for (;;rtos_delay_milliseconds(target->interval)) {
        void *data = hali_link_list_traverse(TYPE_LED, start_pos);
        if (data) {
            struct G_BK_LED *led = (struct G_BK_LED *)data;
            i4s_bk_led_hander(led);
        }
    }
}


/* NOTE 这里需要适配的 */
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
        if (tx_power.is_powerOn) { // power on
            if (tx_power.is_charging) { // power on + is charging
                if (tx_power.is_full) { // power on + is charging + full
                    if (!g_wifi.is_connected) { // power on + is charging + full + wifi not connected
                        
                    } else {  // power on + is charging + full + wifi connected
                        
                    }
                } else { //power on + is charging + not full
                    if (!g_wifi.is_connected) { // power on + is charging + not full + wifi not connected
                        
                    } else {  // power on + is charging + not full + wifi connected
                        
                    }
                }
            } else { // poweron + not charging
                if (tx_power.need_remind_battery) { // power on + not charging + low battery
                    if (g_wifi.is_connected) { // poweron + not charging + low battery + wifi connected
                        
                    } else { // poweron  + not charging + low battery + wifi not connected
                        
                    }
                } else { // power on + not charging + not low battery
                    if (g_wifi.is_connected) { // poweron + not charging + not low battery + wifi connected
                        
                    } else { // poweron  + not charging + not low battery + wifi not connected
                        
                    }
                }
            }
        } else { // power off
            if (tx_power.is_charging) { // power off + is charging
                if (tx_power.is_full) { // power off + is charging + full
                    
                } else { // power off + is charging + not full
                    
                }
            } else { // power off + not charging
                
            }
        }
    }
}


/*  */
void i4s_bk_led_thread_init(void)
{
    if (!i4s_bk_led_thread_inited) {
        i4s_bk_led_thread_inited = 1;
    } else {
        return ;
    }
    void *thread;
    os_memset(&led_thd, 0x0, sizeof(struct TX_LED_Thd));
    led_thd = (struct TX_LED_Thd) {
        .priority = 6,
        .stack_size = 512,
        .trd_func = i4s_bk_led_thread,
        .interval = 200,
        .args = NULL,
    };
    os_memcpy(led_thd.stack_name, "led_task", strlen("led_task"));
    led_thd.args = &led_thd;

    memset(&led_check_thd, 0, sizeof(struct TX_LED_Thd));
    memcpy(led_check_thd.stack_name, "led_check_thd", strlen("led_check_thd"));
    led_check_thd = (struct TX_LED_Thd) {
        .priority = 6,
        .stack_size = 512,
        .trd_func = i4s_led_check_thread,
        .interval = 400,
        .args = &led_check_thd,
    };
    
    bk_printf("led task ready to run\r\n");
    /* 两个线程 前一个线程必须需要执行， 后一个线程用户选择性自己增加  */
    rtos_create_thread((beken_thread_t)&thread, led_thd.priority, led_thd.stack_name
                , (beken_thread_function_t)led_thd.trd_func, led_thd.stack_size, led_thd.args);
}