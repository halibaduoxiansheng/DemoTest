#ifndef __I4S_BK_BAT_H__
#define __I4S_BK_BAT_H__

#include "stdio.h"

#define BAT_ARRY_INDEX_SIZE	(20) /* 电压存储数组大小 */
#define MAX_MAX_ABANDON		(3) /* 最高非法数据 遗弃个数 */


/* NOTE 例如 2500 表示 2.5V */ /* 用前记得初始化 */
/* 使用者提供 电压测量表数据*/
extern uint16_t i4s_bk_bat[BAT_ARRY_INDEX_SIZE];


/**
 * array 传入 i4s_bk_bat ， size 传入 BAT_ARRY_INDEX_SIZE
 * 外放接口 直接放回 电压值 map表 对应值
 * @param  array           数组
 * @param  size            数组大小
 * @param  is_onCharging   是否充电中
 * @param  abandon_forward 数组 前面排除的 个数值 （前几次是 adc 刚启动 防止不稳定） 0表示不需要
 * @param  abandon_later   数组 后面派出的 个数值 （后几次是 如果后面停止了 采样延迟等） 0表示不需要
 * @return                 测得的电压 map 表对应的值
 */
uint16_t i4s_bk_battery_one_click(uint16_t *array, uint8_t size, uint8_t is_onCharging, uint8_t abandon_forward, uint8_t abandon_later);

#endif // end __I4S_BK_BAT_H__