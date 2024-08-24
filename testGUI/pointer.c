/*
    首先一句话，万物皆指针
    本篇章主要介绍指针，指针是C语言中一个非常重要的概念，也是C语言中一个比较难理解的概念。
    玩转 -> 指针

    重点：1.传递给函数的参数 都是 值的副本 2.指针解引用既可以提取值，也可以修改值

    从交换值中学习指针
    无论是几级指针 只要*写全了 都是既是地址改变值，又是提取值

    无论是指针，还是什么其它的变量，都会有一个名字，而这个名字都是给编译器看的，编译后，全是地址，没有变量名，编译器的作用就是将变量名和地址“绑定”
    传入的是基本变量：那就是新创一个变量，然后值传递
    传入的是指针：那就是新创一个指针，指向同样的地址

    （数*号，少了几个就少几级） 
    简单说 定义的 int ****ptr; ptr是4级指针 那么 *ptr 就是3级指针，
    **ptr 就是2级指针，***ptr 就是1级指针，****ptr 就是0级指针，也就是变量。

    指针最常用的还是结构体指针，本章未涉及，静待后续update~
*/
#include <stdio.h>
#include <stdlib.h>

typedef unsigned int uint;
// 参数：一级指针 作用：交换一级指针指向地址所存储的值
// 即使 函数形参 指针 本身地址 和 传入的 实参指针 本身地址 不一致，但是 它们指向的地址 是 一致的
void exchange(uint *a, uint *b)
{
    uint temp = *a; // *a表示解引用，即获取指针a指向的地址存储的值
    *a = *b;
    *b = temp;
}

void exchange2(uint **a, uint **b) // 一直找到最底层的变量（0级指针，与变量a、b一致）
{
    uint temp = **a;
    **a = **b;
    **b = temp;
}
// 这里 将 a1 指向的地址 和 b1 指向的地址 交换了（原本a1指向变量a的地址，现在指向b的地址）
void exchange2_1(uint **a, uint **b) //
{
    uint *temp = *a;
    *a = *b;
    *b = temp;
}
// 同级别不解引用 就是局部变量（传递给函数的参数都是值的副本）
void exchange2_2(uint **a, uint **b) // 这里调换二级指针的地址
{
    printf("%p %p\n", (void *)a, (void *)b); // 0x7ffeedd7c8d4 0x7ffeedd7c8d8
    uint **temp = a; // 需要提别敏感 这里是改变的 副本的地址
    a = b;
    b = temp;
    printf("%p %p\n", (void *)a, (void *)b); // 0x7ffeedd7c8d4 0x7ffeedd7c8d8
    //printf("%u %u\n", **a, **b); // 1  2  交换了 成 2 1 
}
// ***a 就是取了 变量a 的值 然后与变量b交换 所以地址都没变，只是交换了值
void exchange2_3(uint ***a, uint ***b) 
{
    uint temp = ***a; // 指向指针的指针 看*是反的看 原本三级，加一个*，就是二级指针的地址
    ***a = ***b;
    ***b = temp;
}
// 交换的只是 局部变量 三级指针 的
void exchange2_4(uint ***a, uint ***b) // 
{
    printf("%p %p\n", (void *)a, (void *)b); // 
    // printf("%p %p\n", (void *)&a, (void *)&b);
    uint ***temp = a; // 
    a = b;
    b = temp;
    printf("%p %p\n", (void *)a, (void *)b); // 调换了（也就是本来新创建的指针a是和指针a3指向的地址一致的，现在和b3指向的地址交换，指向b3指向的地址了）
    // printf("%p %p\n", (void *)&a, (void *)&b); // 本身地址不会调换
}

// 看清函数参数 需要几级指针
int main(void) 
{
    uint a = 1, b = 2;
    uint *a1 = &a, *b1 = &b; // 指针a1指向变量a储存的地址，指针b1指向变量b储存的地址
    
    // printf("%p %p\n", (void *)a1, (void *)b1); // 指针a1、b1指向的地址
    // printf("%p %p\n", (void *)&a, (void *)&b); // 参数a、b储存的地址（Consistent with the code above）
    // printf("%p %p\n", (void *)&a1, (void *)&b1); // 指针a1、b1本身的地址
    // exchange(a1, b1); // 交换的是指针a1、b1指向的值
    // printf("%p %p\n", (void *)a1, (void *)b1); // not change
    // printf("%p %p\n", (void *)&a, (void *)&b); // not change
    // printf("%p %p\n", (void *)&a1, (void *)&b1); // not change
    
    // printf("%p %p\n", (void *)&*a1, (void *)&*b1); // 就是变量a 变量b 的地址
    // printf("%u %u\n", a, b); // 2  1  交换了 变得是地址内存储的值



    uint **a2 = &a1, **b2 = &b1;
    // printf("%p %p\n", (void *)a2, (void *)b2); 
    // printf("%p %p\n", (void *)&a1, (void *)&b1);
    // exchange(*a2, *b2); // 这和使用exchange(a1, b1); 是一样的
    // exchange2(a2, b2); // 交换了0级指针存储的值（即变量a、b的存储的值交换）
    // printf("%p %p\n", (void *)a2, (void *)b2); 
    // printf("%p %p\n", (void *)&a1, (void *)&b1);
    // printf("%u %u\n", a, b); // 2  1  交换了 变得是地址内存储的值(这里和上面都是改变的值 不是地址)
    // printf("%u %u\n", **a2, **b2); // 2  1  交换了 变得是地址内存储的值
    // printf("%u %u\n", *a1, *b1); // 2  1  交换了 变得是地址内存储的值
    
    /*
        *a2 = a1（&a2 = &a1） 是定义的二级指针 *a2 是一级指针，a1 是一级指针，所以 *a2 = a1 是将一级指针a1赋值给一级指针 *a2
    */
    // printf("%p %p\n", (void *)a1, (void *)b1); // 
    // printf("%p %p\n", (void *)&a1, (void *)&b1); // 本身地址不变
    // printf("%p %p\n", (void *)&a, (void *)&b);
    // exchange2_1(a2, b2);// 这里 将 a1 指向的地址 和 b1 指向的地址 交换了（原本a1指向变量a的地址，现在指向b的地址）
    // 上面的代码相当于 int *a1 = &b, &b1 = &a;
    // printf("%p %p\n", (void *)&a, (void *)&b);
    // printf("%p %p\n", (void *)a1, (void *)b1); // a1、b1指向的地址交换了
    // printf("%p %p\n", (void *)&a1, (void *)&b1); 
    // printf("%u %u\n", *a1, *b1); // 2  1 
    // printf("%u %u\n", a, b); // 1  2  

    // printf("%p %p\n", (void *)a2, (void *)b2); // 
    // exchange2_2(a2, b2);
    // printf("%u %u\n", **a2, **b2); // 依旧是 1 2 这里改变的只是 二级指针本身的地址值(且还是改变的副本地址值)
    // printf("%p %p\n", (void *)a2, (void *)b2); // 不变的原因是 改变的是形参的地址
    // printf("%u %u\n", a, b);

    // uint ***a3 = &a2, ***b3 = &b2;
    // printf("%p %p\n", (void *)&a, (void *)&b);
    // exchange2_3(a3, b3);
    // printf("%p %p\n", (void *)&a, (void *)&b);
    // printf("%u %u\n", ***a3, ***b3); // 2 1 交换了 只是改变了 二级指针的地址值 
    // printf("%u %u\n", **a2, **b2);
    // 这里能看出来  再多级指针 一直追 也只是改变地址  真实的最原始的变量值并没有改变

    // printf("%u %u\n", a, b);

    
    uint ***a3 = &a2, ***b3 = &b2;
    // printf("%p %p\n", (void *)a3, (void *)b3);
    // printf("%p %p\n", (void *)&a3, (void *)&b3);
    // exchange2_4(a3, b3);
    // printf("%p %p\n", (void *)a3, (void *)b3);
    // printf("%p %p\n", (void *)&a3, (void *)&b3);

    //int i = 3;
    //int *p = &i; // &取地址符 （取得对方存储在内存的地址）  内存 不等于 寄存器  寄存器
    /*
        寄存器没有内存地址。寄存器是处理器内部的一种高速存储单元，用于存放临时的数据和指令执行过程中的中间结果。
        寄存器：位于 CPU 内部，是处理器的一部分。非常快 个位数纳秒级别 很小，通常只有几十个字节 用于临时存储数据和地址（想查看地址可以通过调试工具，编码人员无法直接获取寄存器地址）
        内存：位于 CPU 外部，通常指 RAM，是计算机的一部分。 相对较慢，需要几十纳秒到几百纳秒 很大，通常有几十 GB 到几百 GB 用于存储程序代码、全局变量、堆和栈等较大数据
    */
    // register int a = 2; // 寄存器变量 可以提高访问速度（只是对编译器的建议，即使没有写register，编译器认为该放也会放）
    // int *goupibuxing = &a; // 所以这行代码 是 不合法的
    // printf("%p\n", (void *)goupibuxing);

    // const int constant_1 = 2; // 告诉编译器和编码人员，这是一个只读变量(没错，“只读”和“变量”并不矛盾，下面会举一个例子)
    // 这个仍旧会被分配一个内存地址
    // constant_1 = 3; // 编译器会报错，因为 constant_1 是一个只读变量，不能被(这样)修改
    // printf("%p\n", (void *)&constant_1);
    // int *ptr_1 = (int *)&constant_1;
    // *ptr_1 = 3; // 使用 灰色手段 修改其值
    // printf("%d\n", constant_1); // 3


    // 下面继续介绍一些非法使用指针的例子
    // 1.解引用未初始化的空指针
    // int *fool_1 = NULL;
    // int fool_1_value = *fool_1; // 编译器会报错，因为 fool_1 是一个空指针，不能被解引用
    // printf("%d\n", fool_1_value);

    // 2.越界访问
    // 不考虑填充字节，数组，结构体都必须是连续存储的
    // int fool_2[6] = {0, 1, 2, 3, 4, 5}; // 数组名就是一个指针，指向数组的第一个元素
    // int *fool_2_ptr = fool_2;
    // *(fool_2_ptr + 6) == fool_2[6] == fool_2_ptr[6]
    // printf("%d\n", *(fool_2_ptr + 6)); // 编译器不会报错，但是会引发未定义行为，因为 fool_2_ptr + 6 越过了 fool_2 数组的边界

    // 3.不兼容指针类型转换
    // float fool_3_1 = 1.12f;
    // float *fool_3_2 = &fool_3_1;
    // int *fool_3_3 = (int *)fool_3_2; // 编译器不会报错，但是会引发未定义行为，因为 float 和 int 的内存表示不同，这种转换是不安全的
    // printf("%d\n", *fool_3_3);
    
    // 4.使用悬空指针
    // int *fool_4 = (int *)malloc(sizeof(int)); // (int *)在c++中必须要写，c中可以不写
    // free(fool_4); // 为了防止使用，可以在free函数后，将指针设置为NULL 即fool_4 = NULL;
    // *fool_4 = 1; // 编译器不会报错，但是会引发未定义行为，因为 fool_4 已经被释放，指向的内存可能已经被其他程序使用
    // int *fool_4_value = fool_4;
    // printf("%d\n", *fool_4_value); // 无法打印的

    // 5.未初始化的指针解引用
    // int *fool_5 = NULL; // 或 int *fool_5;
    // int fool_5_1 = *fool_5; // 崩溃

    // 6.安全考虑
    // double *fool6 = (double *)malloc(sizeof(double));
    // free(fool6);
    // fool6 = NULL; // 加了这行代码 程序不容易崩溃
    // free(fool6); // add 上面的一行代码不会奔溃
    // double fool6_1 = *fool6; // 依旧崩溃

    // 7.验证
    // int *fool7 = NULL;
    // printf("%p\n", (void *)&fool7); // 是有地址的 -> 不指向任何有效的内存地址(指向的保留地址,也为随机)
    // int *fool7_1;
    // printf("%p\n", (void *)&fool7_1); // 随机地址(虽然说是随机地址，但是读者可以自己试一试，换一个)

    // int abc = 1;
    // int *ptr_111 = &abc;
    // printf("%p\n", (void *)ptr_111); // 
    /*
        至于安全性可以分为两点：（int *pointer = NULL 和 int *pointer;）
            1. 定义指针的时候，赋为NULL（因为在使用指针的地方都会默认先判断指针是否为NULL）
            2. free指针后，将指针赋为NULL
    */

    return 0;
}

/*int main(void)
{
    int a = 1;
    int *p = &a;
    printf("%p\n", (void *)p); // 变量a的地址
    printf("%p\n", (void *)&a); // 变量a的地址
    printf("%p\n", (void *)&p); // 变量p的本身地址 (指针变量的地址)
    return 0;
}*/
