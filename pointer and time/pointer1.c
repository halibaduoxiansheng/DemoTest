/*
    玩转指针 1.传递给函数的参数都是值的副本 2.指针解引用既可以提取值，也可以修改值
*/
#include <stdio.h>

void pointer_0(void);
void pointer_1(void);
void pointer_2(void);
void pointer_3(void);
void pointer_4(void);

int main(void) {
    // 下面函数 逐个打开 难度逐级递增
    //pointer_0();
    //pointer_1();
    //pointer_2();
    //pointer_3();
    pointer_4();
    /* 开始二级指针 */
    // code
    return 0;
}

void pointer_0(void) { // 目的：演示一级指针赋值，解引用
    int l_temp = 6; 
    int *l_ptr_level1 = &l_temp;
    printf("l_temp = %d, *l_ptr_level1 = %d\n", l_temp, *l_ptr_level1); // l_temp = 6, *l_ptr_level1 = 6
}

void pointer_1(void) { // 目的： 演示指针解引用既可以提取值，也可以修改值
    int l_temp = 6;
    int *l_ptr_level1 = &l_temp;
    *l_ptr_level1 = 7;
    printf("l_temp = %d, *l_ptr_level1 = %d\n", l_temp, *l_ptr_level1); // l_temp = 7, *l_ptr_level1 = 7
}

void pointer_2(void) { // 演示指针赋值
    int l_temp = 6;
    int *l_ptr_level1 = &l_temp;
    int *l_ptr1_level1 = l_ptr_level1;
    printf("l_temp = %d, *l_ptr_level1 = %d, *l_ptr1_level1 = %d\n", l_temp, *l_ptr_level1, *l_ptr1_level1); // l_temp = 6, *l_ptr_level1 = 6, *l_ptr1_level1 = 6
}

void pointer_3(void) { // 演示二级指针赋值
    int l_temp = 6;
    int *l_ptr_level1 = &l_temp;
    int **l_ptr_level2 = &l_ptr_level1; // 取得一级指针的地址（注意：指针本身也是需要地址存储的，指针存储的值又是指针别人的）
    printf("l_temp = %d, *l_ptr_level1 = %d, **l_ptr_level2 = %d\n", l_temp, *l_ptr_level1, **l_ptr_level2); // l_temp = 6, *l_ptr_level1 = 6, **l_ptr_level2 = 6
}

void pointer_4(void) { // 
    int l_temp = 6, l_temp1 = 7;
    int *l_ptr_level1 = &l_temp, *l_ptr1_level1 = &l_temp1;
    int **l_ptr_level2 = &l_ptr_level1, **l_ptr2_level2 = &l_ptr1_level1;
    //exchange_address();
}