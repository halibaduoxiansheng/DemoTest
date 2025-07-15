#ifndef __I4S_AUD_INTF_H__
#define __I4S_AUD_INTF_H__

#include "stdio.h"
#include "aud_intf_types.h"

#ifdef __cplusplus
extern "C" {
#endif 

extern RingBufferContext *g_i4s_spk_rb;

typedef int (*_mic_cb)(aud_intf_voc_data_type_t type, uint8_t *data, uint32_t data_len);
typedef int (*_spk_cb)(aud_intf_voc_data_type_t type, uint8_t *data, uint32_t data_len);


/* 需要麦克风数据者 设置 这个函数，实现对应函数  */
int i4s_mic_set_callback(_mic_cb cb);

/* 拥有麦克风数据者 调用 这个函数 （当拥有一帧、多帧 麦克风数据） */
int i4s_mic_push_cb(aud_intf_voc_data_type_t type, uint8_t *data, uint32_t data_len);

/* 需要喇叭数据者 设置 这个函数，实现对应函数 */
int i4s_spk_set_callback(_spk_cb cb);

/* 拥有喇叭数据者 调用 这个函数 （当拥有一帧、多帧 喇叭数据） */
int i4s_spk_push_cb(aud_intf_voc_data_type_t type, uint8_t *data, uint32_t data_len);

int i4s_spk_clear_cb(void);




int i4s_spk_callback_func(aud_intf_voc_data_type_t type, uint8_t *data, uint32_t data_len);
int i4s_mic_callback_func(aud_intf_voc_data_type_t type, uint8_t *data, uint32_t data_len);

#ifdef __cplusplus
}
#endif /* End of #ifdef __cplusplus */
#endif /* __VIDEO_ALG_PTS_V1_0_H__ */