#include "i4s_bk_bat.h"
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <math.h>
// #include <stdint.h>

/*
 * 此库仅为 电压计算 （徐提供结合获取当前电压的函数）
*/

enum {
	NO_ERROR = 0,
	LOCAL_ERROR = 1,
	MALLOC_ERROR = 2,
	ARGS_ERROR = 3,
};



/* NOTE 例如 2500 表示 2.5V */ /* 用前记得初始化 */
uint16_t i4s_bk_bat[BAT_ARRY_INDEX_SIZE] = {0};

static uint8_t mark_map[BAT_ARRY_INDEX_SIZE] = {0};


inline static uint16_t get_diff_value(uint16_t param0, uint16_t param1) {
	if (param0 > param1) {
		return param0 - param1;
	} else {
		return param1 - param0;
	}
}

/* NOTE 冒泡排序 小 -> 大 */
static void BubbleSort_16(uint16_t *array, uint8_t size)
{
	if (!array || size <= 0) {
		return ;
	}

	uint8_t i = 0, j = 0;
	uint16_t temp = 0;
	for (i = 0; i < size - 1; i++)
	{
		for (j = 0; j < size - 1 - i; j++)
		{
			if (array[j] > array[j + 1])
			{
				temp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = temp;
			}
		}
	}
}
/* TODO 这里相比适配形参数据类型 还不如 现在的 的写两个函数  */
static void BubbleSort_8(uint8_t *array, uint8_t size)
{
	if (!array || size <= 0) {
		return ;
	}

	uint8_t i = 0, j = 0;
	uint8_t temp = 0;
	for (i = 0; i < size - 1; i++)
	{
		for (j = 0; j < size - 1 - i; j++)
		{
			if (array[j] > array[j + 1])
			{
				temp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = temp;
			}
		}
	}
}

static uint8_t fill_index(uint8_t index_idx, uint8_t index[MAX_MAX_ABANDON])
{
	uint8_t i = 0;
	for (i = 0; i < MAX_MAX_ABANDON; i++) {
		if (index[i] == 0) {
			index[i] = index_idx;
			return 0; /* success */
		}
	} 
	return 1;
}

/* NOTE 找到了 返回 1，没找到 返回 0 */
static uint8_t is_find_in_param(uint8_t value, uint8_t param[MAX_MAX_ABANDON]) {
	uint8_t i = 0;
	for (i = 0; i < MAX_MAX_ABANDON; i++) {
		if (param[i] == value) {
			return 1;
		}
	}
	return 0;
}

/* NOTE 求得最高标记的 如果最高标记的有多个 最多去除 MAX_MAX_ABANDON 个 */
static int8_t get_max_index_from_array(uint8_t *mark_map, uint8_t size, uint8_t index[MAX_MAX_ABANDON])
{
	if (MAX_MAX_ABANDON >= size) {
		return ARGS_ERROR;
	}

	uint8_t i = 0, fill_num = 0;
	uint8_t index_idx = 0;
	uint8_t param0_index = 0, param1_index = 0, param3_index = 0;
	uint8_t param0 = 0, param1 = 1, param2 = 0;

	/* 创建临时标记表 */
	uint8_t mark_map_temp[BAT_ARRY_INDEX_SIZE] = {0};
	memcpy(mark_map_temp, mark_map, BAT_ARRY_INDEX_SIZE);

	BubbleSort_8(mark_map_temp, size); /* 排序 */

	/* 得到最大的 MAX_MAX_ABANDON 个值 */
	uint8_t param[MAX_MAX_ABANDON] = {0};
	for (i = 0; i < MAX_MAX_ABANDON; i++) {
		param[i] = mark_map_temp[size - i];
	}

	/* 开始寻找这些最大标记值的 下标 */
	for (i = 0; i < size; i++) {
		if (is_find_in_param(mark_map[i], param)) { 
			if (fill_num < MAX_MAX_ABANDON && !fill_index(i, index)) { /* success */
				fill_num++;
			} else {
				break;
			}
		}
	}

	return 0;
}

/* 单纯的求平均值 */
static uint16_t get_average_value(uint16_t *array, uint8_t size)
{
	if (!array || size <= 0) {
		return ARGS_ERROR;
	}

	uint32_t sum = 0;
	uint8_t i = 0, j = 0;
	int8_t ret = 0;
	uint16_t average_value = 0;
	uint8_t diff_sum = 0, diff_average_num = 0;

	/* 得到平均偏差值 */
	for (i = 0; i < size - 1; i++) {
		diff_sum += get_diff_value(array[i+1], array[i]);
	}
	diff_average_num = diff_sum / size; /* 大于这个偏差值的将被标记 */

	/* init */
	memset(mark_map, 0, BAT_ARRY_INDEX_SIZE);

	/* 标记 可能非法数据 统计标记数量 */
	for (i = 0; i < size - 1; i++) {
		for (j = i; j < size; j++) {
			if (get_diff_value(array[i], array[j]) > diff_average_num) {
				mark_map[i]++;
			}
		}
	}

	/* 前 MAX_MAX_ABANDON 位 被标记的非法数据 */
	uint8_t mark_max_index[MAX_MAX_ABANDON] = {0};

	ret = get_max_index_from_array(mark_map, size, mark_max_index);
	if (ret) {
		printf("size is invali, please check youself\r\n");
	} else {

	}

	for (i = 0; i < size; i++) {
		if (is_find_in_param(i, mark_max_index)) {
			/* 下标是被标记的非法下标 不使用 */
		} else {
			sum += array[i];
		}
	}

	average_value = sum / (size - MAX_MAX_ABANDON);

	return average_value;
}

/*
 * 获取平均值
 * @size the lengths of array
 * @param abandon_forward ： Number of discarded heads ,if not need ,please input 0
 * @param abandon_later ： Number of discarded tails ,if not need ,please input 0
 */
static uint16_t logical_get_average_value(uint16_t *array, uint8_t size, uint8_t abandon_forward, uint8_t abandon_later)
{
	if (abandon_forward <= 0 || abandon_later <= 0) {
		return ARGS_ERROR;
	}

	if ((abandon_forward + abandon_later) >= size) {
		return LOCAL_ERROR;
	}

	uint16_t average_value = 0;

	size = size - (abandon_forward + abandon_later);

	average_value = get_average_value(&array[abandon_forward], size);

	return average_value;
}

/* NOTE 获取中位数 给的数据随意 内部是会再 冒泡排序一次 */
static uint16_t get_median_number(uint16_t *array, uint8_t size)
{
	if (!array || size <= 0) {
		return ARGS_ERROR;
	}

	uint16_t median_num = 0;

	uint16_t *array_temp = NULL;
	array_temp = (uint16_t *)malloc(size * sizeof(uint16_t));
	if (!array_temp) {
		return MALLOC_ERROR;
	}

	memcpy(array_temp, (const void *)array, size * sizeof(uint16_t));

	BubbleSort_16(array_temp, size);

	if (size % 2) {
		median_num = (array_temp[size / 2] + array_temp[size / 2 - 1]) / 2;
	} else {
		median_num = array_temp[size / 2];
	}

	if (array_temp) {
		free(array_temp);
	}

	return median_num;
}



static uint16_t value_check_validity(uint16_t *array, uint8_t size, uint8_t is_onCharging, uint16_t median_num, uint16_t average_value)
{
	if (!array || size <= 0) {
		return ARGS_ERROR;
	}
	uint8_t i = 0, j = 0;


	if (size == 1) {
		return array[0];
	}

	/* 偏差值 */ 
	uint16_t med_avr_deviation_value = get_diff_value(median_num, average_value);
	printf("med_avr_deviation_value is %d\r\n", med_avr_deviation_value);

	/* SIZE > 2 */

	/**
	 * 		充电中  	：	存在浮充， (中位数 + 平均值)/2 - 偏差值
	 * 		非充电中	：	(中位数 + 平均值)/2
	 *      
	 */
	uint16_t temp = (median_num + average_value) / 2;
	if (is_onCharging) {
		return temp - med_avr_deviation_value;
	} else {
		return temp;
	}
}



/* 排除 可能的无效值 */
/* 此函数帮助一键式 获取平均值，中位数 */

/**
 * 外放接口 直接放回 电压值 map表 对应值
 * @param  array           数组
 * @param  size            数组大小
 * @param  is_onCharging   是否充电中
 * @param  abandon_forward 数组 前面排除的 个数值 （前几次是 adc 刚启动 防止不稳定） 0表示不需要
 * @param  abandon_later   数组 后面派出的 个数值 （后几次是 如果后面停止了 采样延迟等） 0表示不需要
 * @return                 测得的电压 map 表对应的值
 */
uint16_t i4s_bk_battery_one_click(uint16_t *array, uint8_t size, uint8_t is_onCharging, uint8_t abandon_forward, uint8_t abandon_later)
{
	uint16_t median_num = get_median_number(array, size);
	// printf("median_num is %d\r\n", median_num); /* 得到 总体 中位数 */

	uint16_t average_value = logical_get_average_value(array, size, abandon_forward, abandon_later);
	// printf("average_value is %d\r\n", average_value); /* 得到 总体 平均数 */
	
	/* begin */
	uint16_t last_return_value = value_check_validity(array, size, is_onCharging, median_num, average_value);

	printf("last_return_value is %d\r\n", last_return_value);

	return last_return_value;
}

// int main(void) {
// 	uint16_t array[BAT_ARRY_INDEX_SIZE] = {3700, 3701, 3704, 3750, 3703, 3740, 3720, 3710, 3711, 3703
// 										, 3704, 3709, 3706, 3709, 3800, 3722, 3729, 3744, 3707, 3702};
// 	i4s_bk_battery_one_click(array, BAT_ARRY_INDEX_SIZE, 1, 1, 1);
// }

/* 测量电压函数部分 */


/*  */
