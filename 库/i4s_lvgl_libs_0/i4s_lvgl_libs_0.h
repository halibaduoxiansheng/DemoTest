#ifndef __I4S_LVGL_LIBS_0_H__
#define __I4S_LVGL_LIBS_0_H__

#ifdef __cplusplus
extern "C" {
#endif 

#include "stdio.h"
#include "modules/avilib.h"


enum Screen_state {
	SCREEN_IS_CLOSE = 0, /* lvgl is not init */
	SCREEN_IS_NONE, /* lvgl is open, just screen not show northing */

	SCREEN_IS_TEXT,
	SCREEN_IS_ANIMATION,
	SCREEN_IS_OTA,
	SCREEN_IS_AVI,

	SCREEN_IS_MAX,
};

/*
 * AVI Video Play Context
 */
typedef struct
{
    avi_t *avi;
    uint32_t *video_frame; 
    uint32_t video_len;
    uint32_t video_num; /* 视频帧 总数 */

    uint16_t *framebuffer; /*当前帧显示用的缓冲区*/
    uint16_t *segmentbuffer; /*当前帧分段显示的缓冲区*/

    uint32_t frame_size; /*每帧像素数据大小*/
    uint8_t video_segment_flag; /*视频帧分段处理 启动开关*/
    uint32_t pos; /*当前播放位置*/
} bk_avi_play_t;


/* init module */
int i4s_lvgl_ui_init(void);
int i4s_lvgl_ui_deinit(void);

/* show contents module */
void i4s_ui_show_text(void); /* 文字 */
void i4s_ui_show_eyes_anim(void); /* 动画 */
void i4s_ui_show_ota_hint(void); /* OTA */
void i4s_ui_show_avi_display(void); /* AVI播放 */

/* clear screen module */
void ui_clear(void);



enum Screen_state i4s_screen_which_showing(void);
#ifdef __cplusplus
}
#endif /* End of #ifdef __cplusplus */
#endif // end __I4S_LVGL_LIBS_0_H__