#ifndef __I4S_LVGL_DISPLAY_H__
#define __I4S_LVGL_DISPLAY_H__

#ifdef __cplusplus
extern "C" {
#endif 

#include "stdio.h"

struct utf8_lvgl {
    uint8_t *data;
    uint16_t data_len;
};


/* 虽然 UTF-8 是向下兼容 ASCII 的，但是即使是ASCII，也请写UTF-8类型 */
typedef enum {
    FONT_TYPE_GB2312,           // 简体中文（国标常用）
    FONT_TYPE_UTF8,             // UTF-8（国际通用、变长）

    /* ！！！！！ NOTE 目前只支持上面两种格式 ！！！！！ */
    FONT_TYPE_ASCII = 0,        // 英文/数字/符号
    FONT_TYPE_GBK,              // 简体中文扩展
    FONT_TYPE_BIG5,             // 繁体中文
    FONT_TYPE_UTF16,            // UTF-16（Unicode）
    FONT_TYPE_ISO8859_1,        // 西欧语言编码
    FONT_TYPE_SHIFT_JIS,        // 日文编码
    FONT_TYPE_UNICODE = FONT_TYPE_UTF16, // 别名，用于兼容
    FONT_TYPE_AUTO,             // 自动识别（通过 BOM / 特征）
    FONT_TYPE_UNKNOWN,          // 未知或不支持的编码
} FONT_TYPE;

#define I4S_FONT_USE_PSRAM 1
#define LVGL_RING_BUFFER_SIZE 1024 

#define ONCE_NEED_WORDS	7 /* 每一次最多要的字体数 < sizeof(uint8_t) */

typedef int (*_font_push_cb)(FONT_TYPE type, uint8_t *data, uint32_t data_len);
typedef int (*_font_pop_cb)(FONT_TYPE type, uint8_t *data, uint32_t data_len);


/* 拥有字体数据者 调用此函数 给予数据 <= 0: 表示失败 >0: 成功加入 */
int i4s_font_push_cb(FONT_TYPE type, uint8_t *data, uint32_t data_len);

/* (明确需要多长数据者使用) 需要字体数据者 调用此函数 获取数据 <= 0: 表示失败 >0: 成功获取 */
int i4s_font_pop_cb(FONT_TYPE type, uint8_t *data, uint32_t data_len);

/* 任意人，认为之前的所有数据不再需要，需要清空 可调用 */
int i4s_font_clear(void);


/* 使用者 需要提供 初始化后的存储的空间(NOTE 按照一个字4个字节提供) 和 需要的字数 ONCE_NEED_WORDS
 * 然后自己逻辑判断这些,用完了再来取 （ 函数返回值：实际的获取到的字数 <= 0,就是没有获取到 ）
 * 所有标点符号全部不显示
*/
/**
 * LVGL 需要字体显示者调用这个函数
 * @param  data 回调缓冲区 (长度大于为 4*ONCE_NEED_WORDS+1 )
 * @param  map  每一个字对应的字节长度 (下标0对饮第一个字体)
 * @return      实际返回的字体数
 */
int i4s_lvgl_font_demand(uint8_t *data, uint8_t map[ONCE_NEED_WORDS]);

int i4s_lvgl_display_init(void);

int i4s_lvgl_display_deinit(void);


/* test */
int push_test(void);

#ifdef __cplusplus
}
#endif /* End of #ifdef __cplusplus */
#endif // end __I4S_LVGL_DISPLAY_H__