#include "i4s_lvgl_libs_0.h"
#include <os/os.h>
#include "lcd_act.h"
#include "media_app.h"
#if CONFIG_LVGL
#include "lv_vendor.h"
#include "lvgl.h"
#endif
#include "driver/drv_tp.h"
#include <driver/lcd.h>
#include "yuv_encode.h"
#include "modules/jpeg_decode_sw.h"
#include "media_evt.h"
#include "ota_display.h"
#if (CONFIG_SYS_CPU1)
#include "lv_jpeg_hw_decode.h"
#endif

#include "i4s/i4s_lvgl_display.h"

/**
	Code by wangjie
	screen is very strange, SPI distribution have problem
	Width： 160		Height：320

	******			****** 
	* 	 *			* up *
	*    *    	  	*	 *  ==> the up module pan to left screen
	*    *	 ==>	******  ==> the down module pan to right screen,and not just sample
	*    *			*down*
	*    *			*	 *
	******			******
	

*/


#if (CONFIG_SYS_CPU1)
typedef enum ui_state {
	UI_STATE_NONE = 0,
	UI_STATE_TEXT,
	UI_STATE_ANIMATION,
	UI_STATE_OTA,
	UI_STATE_AVI,
}ui_state_t;

struct Task_flag { /* start flag or what */
	uint8_t text_flag	:1;
	uint8_t anim_flag	:1;
	uint8_t ota_flag	:1;
	uint8_t avi_flag	:1;

	uint8_t reserved	:4;
}__attribute__((packed));
static struct Task_flag task_flag = {0};

/* Debug Choice */
#define I4S_LVGL_LIBS_DEBUG_FLAG	1 /* 1:OPEN 0:CLOSE */
#if I4S_LVGL_LIBS_DEBUG_FLAG
 #define LVGL_DEBUG bk_printf
#else
 #define LVGL_DEBUG
#endif

/* IMAGE src */
#define IMAGE_0_SRC_IN_SD "images/eyes/eye-0.jpeg"
#define IMAGE_1_SRC_IN_SD "ota_image.jpg" // default screen

/* AVI src */
#define I4S_AVI_SRC_IN_SD "/genie_eye.avi"

/* all lv objs */
static lv_obj_t *cont_text = NULL;
static lv_obj_t *cont_animation = NULL;
static lv_obj_t *cont_ota = NULL;
static lv_obj_t *cont_avi = NULL;

static ui_state_t current_ui_state = UI_STATE_NONE;
static uint8_t i4s_lvgl_ui_inited = 0;

/* text timer use */
static lv_timer_t *text_timer_left = NULL;
static lv_timer_t *text_timer_right = NULL;

/* avi use */
lv_img_dsc_t *g_i4s_img_dsc = NULL;
lv_vnd_config_t *g_i4s_lv_vnd_config = NULL;
bk_avi_play_t *g_i4s_bk_avi_play = NULL;

extern bk_err_t bk_avi_play_open(bk_avi_play_t *avi_play, const char *filename, uint8_t segment_flag);
extern void bk_avi_play_close(bk_avi_play_t *avi_play);
extern void bk_avi_play_start(void);
extern void bk_avi_play_stop(void);
extern void bk_avi_video_prase_to_rgb565(bk_avi_play_t *avi_play);

/* module init start */
/* NOTE 黑底白字 居中显示 */
#define EYES_DIAMETER_SIZE	(50)
#define LVGL_FONT_HEIGHT_CONSTRAINT		20
static void i4s_lvgl_text_screen_init(void) // cont_text TODO
{
	lv_vendor_disp_lock();

    // set text module background color black
    lv_obj_set_style_bg_color(cont_text, lv_color_black(), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(cont_text, LV_OPA_COVER, LV_PART_MAIN);

 	lv_obj_t *left_eye = lv_obj_get_child(cont_text, 0);
    lv_obj_align(left_eye, LV_ALIGN_TOP_MID, 0, (320/4 - EYES_DIAMETER_SIZE/2)); 

    lv_obj_t *right_eye = lv_obj_get_child(cont_text, 1);
    lv_obj_align(right_eye, LV_ALIGN_BOTTOM_MID, 0, (320/4 - EYES_DIAMETER_SIZE/2)); 

	lv_obj_set_size(left_eye, LV_HOR_RES, LVGL_FONT_HEIGHT_CONSTRAINT); 
	lv_obj_set_size(right_eye, LV_HOR_RES, LVGL_FONT_HEIGHT_CONSTRAINT); 

	lv_obj_set_style_text_align(left_eye, LV_TEXT_ALIGN_CENTER, 0);
	lv_obj_set_style_text_align(right_eye, LV_TEXT_ALIGN_CENTER, 0);

	lv_label_set_long_mode(left_eye, LV_LABEL_LONG_SCROLL_CIRCULAR);
	lv_label_set_long_mode(right_eye, LV_LABEL_LONG_SCROLL_CIRCULAR);
    
    // extern const lv_font_t my_font; 
    extern const lv_font_t Simplified_common_words;
    lv_obj_set_style_text_color(left_eye, lv_color_white(), 0);
    lv_obj_set_style_text_font(left_eye, &Simplified_common_words, 0);

    lv_obj_set_style_text_color(right_eye, lv_color_white(), 0);
    lv_obj_set_style_text_font(right_eye, &Simplified_common_words, 0);

    lv_obj_set_style_border_width(left_eye, 0, 0);  // remove border
    lv_obj_set_style_border_width(right_eye, 0, 0);  // remove border

    lv_vendor_disp_unlock();
}

/* NOTE 这里不设置 文件宽显示、超长设置 默认让其自动换行 */
/* 黑底白色动画效果 */
static void i4s_lvgl_anim_screen_init(void) // cont_animation TODO
{
	// TODO
	lv_vendor_disp_lock();

    // set background color black
    lv_obj_set_style_bg_color(cont_animation, lv_color_black(), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(cont_animation, LV_OPA_COVER, LV_PART_MAIN); // set not opacity

    // create left eye label
    lv_obj_t *left_eye = lv_obj_get_child(cont_animation, 0);
    lv_obj_set_size(left_eye, EYES_DIAMETER_SIZE, EYES_DIAMETER_SIZE);

    /* NOTE 在 LVGL 中，如果你设置了背景颜色，但不设置背景透明度，可能背景是默认“透明”的，你设置的颜色就不会显示出来 */
    lv_obj_set_style_bg_color(left_eye, lv_color_white(), 0);
    lv_obj_set_style_bg_opa(left_eye, LV_OPA_COVER, 0); /* 设置完全不透明 */
    
    // 居中显示
    lv_obj_set_style_text_align(left_eye, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_set_style_pad_all(left_eye, 0, 0);  
    lv_obj_set_style_radius(left_eye, LV_RADIUS_CIRCLE, 0); //设置圆角为半径，形成圆形
    lv_obj_align(left_eye, LV_ALIGN_TOP_MID, 0, (320/4 - EYES_DIAMETER_SIZE/2));  // 对齐，然后X（右正），Y（下正）方向位移
	lv_obj_set_style_border_width(left_eye, 0, 0);  // remove border



    // create right eye label
    lv_obj_t *right_eye = lv_obj_get_child(cont_animation, 1);
    lv_obj_set_size(right_eye, EYES_DIAMETER_SIZE, EYES_DIAMETER_SIZE);

    lv_obj_set_style_bg_color(right_eye, lv_color_white(), 0);
    lv_obj_set_style_bg_opa(right_eye , LV_OPA_COVER, 0); /* 设置完全不透明 */

    // 居中显示
    lv_obj_set_style_text_align(right_eye, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_set_style_pad_all(right_eye, 0, 0); 
    lv_obj_set_style_radius(right_eye, LV_RADIUS_CIRCLE, 0); //设置圆角为半径，形成圆形
    lv_obj_align(right_eye, LV_ALIGN_BOTTOM_MID, 0, -(320/4 - EYES_DIAMETER_SIZE/2)); // 右半部分中间
    lv_obj_set_style_border_width(right_eye, 0, 0); // remove border

    lv_vendor_disp_unlock();
}

static void i4s_lvgl_ota_screen_init(void) // cont_ota TODO
{
	// TODO
	lv_vendor_disp_lock();
	lv_vendor_disp_unlock();
}

static void i4s_lvgl_avi_screen_init(void)
{
	if (!g_i4s_img_dsc || !g_i4s_lv_vnd_config || !g_i4s_bk_avi_play) {
		bk_printf("i4s_lvgl_avi_screen_init args have NULL\r\n");
		return ;
	}
	int ret = 0;
	lv_vendor_disp_lock();
	g_i4s_img_dsc->header.w = g_i4s_lv_vnd_config->lcd_hor_res;
    g_i4s_img_dsc->header.h = g_i4s_lv_vnd_config->lcd_ver_res;
    g_i4s_img_dsc->data_size = g_i4s_img_dsc->header.w * g_i4s_img_dsc->header.h * 2;

    ret = bk_avi_play_open(g_i4s_bk_avi_play, I4S_AVI_SRC_IN_SD, 1);
    if (ret != BK_OK)
    {
        lcd_display_close();
        return ;
    }

    if (g_i4s_bk_avi_play->video_segment_flag == 1) // this
    {
        g_i4s_img_dsc->data = (const uint8_t *)g_i4s_bk_avi_play->segmentbuffer;
    }
    else
    {
        g_i4s_img_dsc->data = (const uint8_t *)g_i4s_bk_avi_play->framebuffer;
    }

    /* 将第一帧数据转换 后面靠 定时器 lv_timer_cb 转换  */
    bk_avi_video_prase_to_rgb565(g_i4s_bk_avi_play); 
    lv_vendor_disp_unlock();
}

/* module init end */

/* module task start */
static void update_chinese_words_left_task(lv_timer_t *timer) { 
    static uint8_t screen_words = 0; /* the words num of in screen */
    static uint8_t get_words = 0; /* the words num get from resource */
    static uint8_t _utf8_data[4*ONCE_NEED_WORDS+1] = {0}; /* the data which get words form resource */
    static uint8_t self_map[ONCE_NEED_WORDS] = {0}; /* words map */
    static uint8_t show_buf[4*ONCE_NEED_WORDS+1] = {0}; /* the data which need to show in screen */
    static uint16_t i4s_len = 0; /* the variable of to help calc */
    static uint8_t i4s_pos = 0; /* the variable of to help calc */

    if (screen_words == 0) {
        get_words = i4s_lvgl_font_left_demand(_utf8_data, self_map);
    }

    if (get_words <= 0) {
    	i4s_ui_show_eyes_anim();
    }

    if (screen_words < get_words) {
        i4s_len += self_map[i4s_pos++];
        memcpy(show_buf, _utf8_data, i4s_len);

        lv_label_set_text(lv_obj_get_child(cont_text, 0), (const char *)show_buf);
        screen_words++;
    } else {
        lv_label_set_text(lv_obj_get_child(cont_text, 0), "");
        i4s_len = i4s_pos = screen_words = 0;
    }
}

static void update_chinese_words_right_task(lv_timer_t *timer) {
    static uint8_t screen_words = 0; /* the words num of in screen */
    static uint8_t get_words = 0; /* the words num get from resource */
    static uint8_t _utf8_data[4*ONCE_NEED_WORDS+1] = {0}; /* the data which get words form resource */
    static uint8_t self_map[ONCE_NEED_WORDS] = {0}; /* words map */
    static uint8_t show_buf[4*ONCE_NEED_WORDS+1] = {0}; /* the data which need to show in screen */
    static uint16_t i4s_len = 0; /* the variable of to help calc */
    static uint8_t i4s_pos = 0; /* the variable of to help calc */

    if (screen_words == 0) {
        get_words = i4s_lvgl_font_right_demand(_utf8_data, self_map);
    }

    if (get_words <= 0) {
    	lv_label_set_text(lv_obj_get_child(cont_text, 1), "");
    }

    if (screen_words < get_words) {
        i4s_len += self_map[i4s_pos++];
        memcpy(show_buf, _utf8_data, i4s_len);

        lv_label_set_text(lv_obj_get_child(cont_text, 1), (const char *)show_buf);
        screen_words++;
    } else {
        lv_label_set_text(lv_obj_get_child(cont_text, 1), "");
        i4s_len = i4s_pos = screen_words = 0;
    }
}


static void lv_text_timer_close(void)
{
	if (text_timer_left) {
        lv_timer_del(text_timer_left);
        text_timer_left = NULL;
    }
    if (text_timer_right) {
        lv_timer_del(text_timer_right);
        text_timer_right = NULL;
    }
}

// set animation with width 
static void anim_set_width(void * obj, int32_t width)
{
    lv_obj_set_size((lv_obj_t *)obj, width, 50);  // 高度保持50，宽度变化
}

// set animation with place
static void anim_set_x_offset(void * obj, int32_t x)
{
    lv_obj_set_x((lv_obj_t *)obj, x);
}

static void lv_animation_close(void)
{
	lv_obj_t *child0 = lv_obj_get_child(cont_animation, 0);
	if (child0 != NULL) {
	    lv_anim_del(child0, anim_set_width);
	    lv_anim_del(child0, anim_set_x_offset);
	}

	lv_obj_t *child1 = lv_obj_get_child(cont_animation, 1);
	if (child1 != NULL) {
	    lv_anim_del(child1, anim_set_width);
	    lv_anim_del(child1, anim_set_x_offset);
	}
}

/* NOTE this is a demo animation ,if fature need more animation ,add it by youself */
static void start_eyes_animation(lv_obj_t* left_eye, lv_obj_t* right_eye)
{
	if (left_eye && right_eye) {
		LVGL_DEBUG("eyes animation start\r\n");
	}

/****************************  Animation_0   *****************************************/
	lv_label_set_text(left_eye, "");
	lv_label_set_text(right_eye, "");

    /* 创建一个动画 */
    static lv_anim_t anim_left_0, anim_right_0;

    // 创建动画 (左眼)
    lv_anim_init(&anim_left_0);
    lv_anim_set_var(&anim_left_0, left_eye);                  // 设置目标对象
    lv_anim_set_exec_cb(&anim_left_0, anim_set_width);     // 回调函数
    lv_anim_set_time(&anim_left_0, 600);                   // 动画时长：600ms
    lv_anim_set_values(&anim_left_0, 50, 65);              // 从宽度50变到65
    lv_anim_set_playback_time(&anim_left_0, 600);          // 播放回退动画（65回到50） 600ms
    lv_anim_set_repeat_delay(&anim_left_0, 400);           // 可选：循环间隔
    lv_anim_set_repeat_count(&anim_left_0, LV_ANIM_REPEAT_INFINITE);  // 无限循环
    lv_anim_start(&anim_left_0);

    // 创建动画 (右眼)
    lv_anim_init(&anim_right_0);
    lv_anim_set_var(&anim_right_0, right_eye);                  // 设置目标对象
    lv_anim_set_exec_cb(&anim_right_0, anim_set_width);     // 回调函数
    lv_anim_set_time(&anim_right_0, 600);                   // 动画时长：600ms
    lv_anim_set_values(&anim_right_0, 50, 65);              // 从宽度50变到65
    lv_anim_set_playback_time(&anim_right_0, 600);          // 播放回退动画（65回到50） 600ms
    lv_anim_set_repeat_delay(&anim_right_0, 400);           // 可选：循环间隔
    lv_anim_set_repeat_count(&anim_right_0, LV_ANIM_REPEAT_INFINITE);  // 无限循环
    lv_anim_start(&anim_right_0);


/****************************  Animation_1   *****************************************/
    static lv_anim_t anim_left_1, anim_right_1;
	// 左眼左右移动
	lv_anim_init(&anim_left_1);
	lv_anim_set_var(&anim_left_1, left_eye);
	lv_anim_set_exec_cb(&anim_left_1, anim_set_x_offset);
	lv_anim_set_values(&anim_left_1, -18, 18);  // 在中心左右来回移动
	lv_anim_set_time(&anim_left_1, 900);
	lv_anim_set_playback_time(&anim_left_1, 1000);
	lv_anim_set_repeat_count(&anim_left_1, LV_ANIM_REPEAT_INFINITE);
	lv_anim_start(&anim_left_1);

	// 右眼左右移动
	lv_anim_init(&anim_right_1);
	lv_anim_set_var(&anim_right_1, right_eye);
	lv_anim_set_exec_cb(&anim_right_1, anim_set_x_offset);
	lv_anim_set_values(&anim_right_1, -18, 18); 
	lv_anim_set_time(&anim_right_1, 900);
	lv_anim_set_playback_time(&anim_right_1, 1000);
	lv_anim_set_repeat_count(&anim_right_1, LV_ANIM_REPEAT_INFINITE);
	lv_anim_start(&anim_right_1);

}

static void i4s_image_all_stop(void)
{
    bk_printf("hide a picture\r\n");
    bk_ota_image_disp_close();
}

static void i4s_image_ctl_start(uint8_t *src)
{
	if (!src) {
		bk_printf("src is NULL\r\n");
		return ;
	}
	i4s_image_all_stop();
    bk_printf("show a picture\r\n");
    bk_ota_image_disp_open((char *)src); /* inside will check path validity */
}
/* module task end */

static void ui_switch_to(ui_state_t new_state)
{
    if (current_ui_state == new_state) /* burden code, delete it or not~ */
        return ;

    // 隐藏所有容器
    lv_obj_add_flag(cont_text, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(cont_animation, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(cont_ota, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(cont_avi, LV_OBJ_FLAG_HIDDEN);
    rtos_delay_milliseconds(200); /* give sometime ensure exchange prepare OK */

    if (current_ui_state == UI_STATE_TEXT) { /* close text resource */
	    lv_text_timer_close();
	    task_flag.text_flag = 0;
	    i4s_font_all_clear(); /* */
	} else if (current_ui_state == UI_STATE_ANIMATION) { /* close animation resource */
        lv_animation_close();
        task_flag.anim_flag = 0;
    } else if (current_ui_state == UI_STATE_OTA) { /* close ota images */
    	i4s_image_all_stop();
    	task_flag.ota_flag = 0;
    } else if (current_ui_state == UI_STATE_AVI) { /* close avi */
    	bk_avi_play_stop();
    	task_flag.avi_flag = 0;
    }

    current_ui_state = new_state;
}



void i4s_ui_show_text(void) /* 文字 */
{
	if (i4s_lvgl_ui_inited != 1) {
		bk_printf("i4s lvgl ui have not inited\r\n");
		return ;
	}
	if (task_flag.text_flag != 0) {
		bk_printf("current state already is text\r\n");
		return ;
	}
	task_flag.text_flag = 1;
	LVGL_DEBUG("i4s_ui_show_text start\r\n");
	ui_switch_to(UI_STATE_TEXT);
	lv_obj_clear_flag(cont_text, LV_OBJ_FLAG_HIDDEN);

	/* task start */
	text_timer_left = lv_timer_create(update_chinese_words_left_task, 250, NULL);
    text_timer_right = lv_timer_create(update_chinese_words_right_task, 250, NULL);
}

void i4s_ui_show_eyes_anim(void) /* 动画 */
{
	if (i4s_lvgl_ui_inited != 1) {
		bk_printf("i4s lvgl ui have not inited\r\n");
		return ;
	}
	if (task_flag.anim_flag != 0) {
		bk_printf("current state already is animation\r\n");
		return ;
	}
	task_flag.anim_flag = 1;
	LVGL_DEBUG("i4s_ui_show_eyes_anim start\r\n");
	ui_switch_to(UI_STATE_ANIMATION);
	lv_obj_clear_flag(cont_animation, LV_OBJ_FLAG_HIDDEN);

	/* task start */
	start_eyes_animation(lv_obj_get_child(cont_animation, 0), lv_obj_get_child(cont_animation, 1));
}

void i4s_ui_show_ota_hint(void) /* OTA */
{
	if (i4s_lvgl_ui_inited != 1) {
		bk_printf("i4s lvgl ui have not inited\r\n");
		return ;
	}
	if (task_flag.ota_flag != 0) {
		bk_printf("current state already is ota\r\n");
		return ;
	}
	task_flag.ota_flag = 1;
	LVGL_DEBUG("i4s_ui_show_ota_hint start\r\n");
	ui_switch_to(UI_STATE_OTA);
	lv_obj_clear_flag(cont_ota, LV_OBJ_FLAG_HIDDEN);

	/* task start */
	i4s_image_ctl_start((uint8_t *)IMAGE_1_SRC_IN_SD);
}

void i4s_ui_show_avi_display(void)
{
	if (i4s_lvgl_ui_inited != 1) {
		bk_printf("i4s lvgl ui have not inited\r\n");
		return ;
	}
	if (task_flag.avi_flag != 0) {
		bk_printf("current state already is avi\r\n");
		return ;
	}
	task_flag.avi_flag = 1;
	LVGL_DEBUG("i4s_ui_show_avi_display start\r\n");
	ui_switch_to(UI_STATE_AVI);
	lv_obj_clear_flag(cont_avi, LV_OBJ_FLAG_HIDDEN);

	/* task start */
	bk_avi_play_start();
}

enum Screen_state i4s_screen_which_showing(void)
{
	enum Screen_state state = 0;
	if (i4s_lvgl_ui_inited != 1) {
		state = SCREEN_IS_CLOSE;
		return state;
	}

	if (task_flag.text_flag == 1) {
		state = SCREEN_IS_TEXT;
	} else if (task_flag.anim_flag == 1) {
		state = SCREEN_IS_ANIMATION;
	} else if (task_flag.ota_flag == 1) {
		state == SCREEN_IS_OTA;
	} else if (task_flag.avi_flag == 1) {
		state == SCREEN_IS_AVI;
	} else {
		state = SCREEN_IS_NONE;
	}

	return state;
}

/* lv_label label default show Animation */
int i4s_lvgl_ui_init(void) // TODO
{
	if (i4s_lvgl_ui_inited != 0) {
		bk_printf("i4s lvgl ui already init\r\n");
		return 0;
	}
	if (!g_i4s_lv_vnd_config) {
		bk_printf("please check order\r\n");
		return 0;
	}
	/* NOTE create four page, take care youself about the space problem */
	
	// TEXT MODULE
	cont_text = lv_obj_create(lv_scr_act());
	lv_obj_set_size(cont_text, LV_HOR_RES, LV_VER_RES); // opposite
	lv_obj_align(cont_text, LV_ALIGN_CENTER, 0, 0);
	lv_obj_add_flag(cont_text, LV_OBJ_FLAG_HIDDEN);
	lv_obj_set_style_pad_all(cont_text, 0, LV_PART_MAIN);
	lv_obj_t *left_label_text = lv_label_create(cont_text);
	lv_obj_t *right_label_text = lv_label_create(cont_text);
	lv_obj_set_style_border_width(cont_text, 0, LV_PART_MAIN);
	if (left_label_text && right_label_text) {
		i4s_lvgl_text_screen_init();
	}

	// ANIMATION MODULE
	cont_animation = lv_obj_create(lv_scr_act());
	lv_obj_set_size(cont_animation, LV_HOR_RES, LV_VER_RES);
	lv_obj_align(cont_animation, LV_ALIGN_CENTER, 0, 0);
	lv_obj_add_flag(cont_animation, LV_OBJ_FLAG_HIDDEN);
	lv_obj_set_style_pad_all(cont_animation, 0, LV_PART_MAIN); /* NOTE if not set,it have a init value */
	lv_obj_t *left_label_anim = lv_label_create(cont_animation);
	lv_obj_t *right_label_anim = lv_label_create(cont_animation);
	// lv_obj_set_style_border_color(cont_animation, lv_color_make(0,255,0), LV_PART_MAIN);
	// lv_obj_set_style_border_width(cont_animation, 3, LV_PART_MAIN);
	// lv_obj_set_style_border_opa(cont_animation, LV_OPA_COVER, LV_PART_MAIN);
	lv_obj_set_style_border_width(cont_animation, 0, LV_PART_MAIN);
	if (left_label_anim && right_label_anim) {
		i4s_lvgl_anim_screen_init();
	}

	// OTA MODULE
	cont_ota = lv_obj_create(lv_scr_act());
	lv_obj_set_size(cont_ota, LV_HOR_RES, LV_VER_RES);
	lv_obj_align(cont_ota, LV_ALIGN_CENTER, 0, 0);
	lv_obj_add_flag(cont_ota, LV_OBJ_FLAG_HIDDEN);
	lv_obj_t *left_label_ota = lv_label_create(cont_ota);
	lv_obj_t *right_label_ota = lv_label_create(cont_ota);
	lv_obj_set_style_border_width(cont_ota, 0, LV_PART_MAIN);
	if (left_label_ota && right_label_ota) {
		i4s_lvgl_ota_screen_init();
	}

	cont_avi = lv_obj_create(lv_scr_act());
	lv_obj_set_size(cont_avi, LV_HOR_RES, LV_VER_RES);
	lv_obj_align(cont_avi, LV_ALIGN_CENTER, 0, 0);
	lv_obj_add_flag(cont_avi, LV_OBJ_FLAG_HIDDEN);
	lv_obj_set_style_border_width(cont_avi, 0, LV_PART_MAIN);
	i4s_lvgl_avi_screen_init();

	i4s_lvgl_ui_inited = 1;
	LVGL_DEBUG("i4s_lvgl_ui_init func complete\r\n");
	return 0;
}

int i4s_lvgl_ui_deinit(void)
{
	if (i4s_lvgl_ui_inited != 1) {
		bk_printf("i4s lvgl ui have not inited\r\n");
		return 0;
	}

	ui_clear();
	if (cont_text) {
	    lv_obj_del(cont_text);
	    cont_text = NULL;
	}
	if (cont_animation) {
	    lv_obj_del(cont_animation);
	    cont_animation = NULL;
	}
	if (cont_ota) {
	    lv_obj_del(cont_ota);
	    cont_ota = NULL;
	}
	if (cont_avi) {
		lv_obj_del(cont_avi);
	    cont_avi = NULL;
	}
	if (g_i4s_bk_avi_play) {
		bk_avi_play_close(g_i4s_bk_avi_play);
	}
	
	i4s_lvgl_ui_inited = 0;
	LVGL_DEBUG("i4s_lvgl_ui_deinit func complete\r\n");
	return 0;
}

void ui_clear(void)
{
	LVGL_DEBUG("ui clear start\r\n");
	if (i4s_lvgl_ui_inited != 1) {
		bk_printf("i4s lvgl ui have not inited\r\n");
		return ;
	}
	lv_obj_add_flag(cont_text, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(cont_animation, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(cont_ota, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(cont_avi, LV_OBJ_FLAG_HIDDEN);

	lv_text_timer_close();
	lv_animation_close();
	i4s_image_all_stop();
	bk_avi_play_stop();
	memset(&task_flag, 0x0, sizeof(struct Task_flag));

	LVGL_DEBUG("ui clear complete\r\n");
}
#endif 