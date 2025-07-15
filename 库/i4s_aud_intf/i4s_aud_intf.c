#include "i4s_aud_intf.h"


#include "stdlib.h"
#include <driver/audio_ring_buff.h>
#include <modules/g711.h>
#include "aud_tras_drv.h"

#include <sdkconfig.h>

#include "aud_intf.h"

#if CONFIG_AUD_INTF_SUPPORT_G722
#include <modules/g722.h>
#endif

RingBufferContext *g_i4s_spk_rb = NULL;

#if CONFIG_AUD_INTF_SUPPORT_G722
static g722_decode_state_t g722_dec = {0};
#endif

#define TRANS_MAX_LEN	2048

/* 麦克风 一帧数据 调用一次这个函数 */
static _mic_cb mic_cb = NULL;
static _spk_cb spk_cb = NULL;


int i4s_mic_set_callback(_mic_cb cb)
{
	if (cb) {
		mic_cb = cb;
		return 0;
	} 
	return -1;
}

int i4s_spk_set_callback(_spk_cb cb)
{
#if CONFIG_AUD_INTF_SUPPORT_G722
	g722_decode_init(&g722_dec, 64000, 0);
#endif
	if (cb) {
		spk_cb = cb;
		return 0;
	}
#if CONFIG_AUD_INTF_SUPPORT_G722
	g722_decode_release(&g722_dec);
#endif
	return -1;
}

int i4s_mic_push_cb(aud_intf_voc_data_type_t type, uint8_t *data, uint32_t data_len)
{
	if(mic_cb) {
		(*mic_cb)(type, data, data_len);
		return 0;
	}
	return -1;
}

int i4s_spk_push_cb(aud_intf_voc_data_type_t type, uint8_t *data, uint32_t data_len)
{
	int ret = 0;
	if(spk_cb) {
		ret = (*spk_cb)(type, data, data_len);
		return ret;
	}
	bk_printf("func not register\r\n");
	return -1;
}

int i4s_spk_clear_cb(void)
{
	if (g_i4s_spk_rb) {
		ring_buffer_clear(g_i4s_spk_rb);
		return 0;	
	}
	return -1;
}



static int i4s_write_speak_data(int16_t *pcm_data, uint32_t data_len)
{
	uint32_t ret = 0;
#if 0 /* REVIEW address */
	if (g_i4s_spk_rb) { 
		bk_printf("g_i4s_spk_rb is %p\r\n", g_i4s_spk_rb);
	}
	if (g_i4s_spk_rb && ring_buffer_get_free_size(g_i4s_spk_rb) >= data_len) {
		ret = ring_buffer_write(g_i4s_spk_rb, (uint8_t *)pcm_data, data_len);
		if (ret != data_len) {
			return -5;
		}		
	} else {
		return -6;
	}
#else
	ret = bk_aud_intf_write_spk_data((uint8_t *)pcm_data, data_len);
	if (ret == 0) {
		return data_len;
	}
	return -7;
#endif
}

int i4s_spk_callback_func(aud_intf_voc_data_type_t type, uint8_t *data, uint32_t data_len)
{
	if (!data || data_len <= 0) {
		bk_printf("data is NULL ot data_len is not right\r\n");
		bk_printf("data_len is %d\r\n", data_len);
		return -1;
	}

	if (data_len > TRANS_MAX_LEN) {  /* NOTE 考虑压缩 */
		bk_printf("please trans less data\r\n");
		return -2;
	}

	int16_t data_temp[TRANS_MAX_LEN] = {0}; /* PCM数据 临时缓冲区 */
	uint32_t i = 0, ret = 0;

	switch (type) 
	{
	case AUD_INTF_VOC_DATA_TYPE_G711A: /**< the data of voice transfer encoded by G711A */
		for (i = 0; i < data_len; i++) {
			data_temp[i] = alaw2linear((unsigned char)data[i]);
		}
		break;
	case AUD_INTF_VOC_DATA_TYPE_PCM: /**< the data of voice transfer is PCM 未压缩 */
		memcpy(data_temp, (const void *)data, data_len);
		break;
	case AUD_INTF_VOC_DATA_TYPE_G711U: /**< the data of voice transfer encoded by G711U */
		for (i = 0; i < data_len; i++) {
			data_temp[i] = ulaw2linear((unsigned char)data[i]);
		}
		break;
#if CONFIG_AUD_INTF_SUPPORT_G722
	case AUD_INTF_VOC_DATA_TYPE_G722: // NOTE 4：1
		if (data_len > (TRANS_MAX_LEN/4)) {
			bk_printf("G722 compression room is not enough\r\n");
			return -8;
		}
		g722_decode(&g722_dec, data_temp, data, data_len);
		break;
#endif
	case AUD_INTF_VOC_DATA_TYPE_MAX:
		bk_printf("data type is wrong\r\n");
		return -3;
		break;
	default:
		bk_printf("data type is no match\r\n");
		return -4;
	}

	ret = i4s_write_speak_data(data_temp, data_len);

	return ret;
}


/* blow code is test code */
int i4s_mic_callback_func(aud_intf_voc_data_type_t type, uint8_t *data, uint32_t data_len)
{
	// TODO 默认PCM格式
	i4s_spk_push_cb(AUD_INTF_VOC_DATA_TYPE_PCM, data, data_len);
	return 0;
}

