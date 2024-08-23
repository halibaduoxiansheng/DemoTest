/*
    本篇章主要介绍指针，指针是C语言中一个非常重要的概念，也是C语言中一个比较难理解的概念。
    玩转 -> 指针
    重点：1.传递给函数的参数都是值的副本 2.指针解引用既可以提取值，也可以修改值
    从交换值中学习指针
    无论是几级指针 只要*写全了 都是既是地址改变值，又是提取值

    （数*号，少了几个就少几级） 
    简单说 定义的 int ****ptr; 是4级指针 那么 *ptr 就是3级指针，**ptr 就是2级指针，***ptr 就是1级指针，****ptr 就是0级指针，也就是变量。
*/
#include <stdio.h>

typedef unsigned int uint;
// 虽然传入的是形参 但是都是指针 同一个地址  (函数没有改地址，只是改的地址上存储的 值)
void exchange(uint *a, uint *b)
{
    uint temp = *a; // *a表示解引用，即获取指针a指向的变量的值（同时是从地址上获取的）
    *a = *b;
    *b = temp;
}

void exchange2(uint **a, uint **b) // 一直找到最底层的变量
{
    uint temp = **a;
    **a = **b;
    **b = temp;
}
// 这里 a1 和 b1 里面储存的 地址值 交换了
void exchange2_1(uint **a, uint **b) // 这里是调换指针的地址
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
// 将二级指针 本身的地址 给调换了
void exchange2_3(uint ***a, uint ***b) // 这里调换三级指针指向地址
{
    uint temp = ***a; // 指向指针的指针 看*是反的看 原本三级，加一个*，就是二级指针的地址
    ***a = ***b;
    ***b = temp;
}

void exchange2_4(uint ***a, uint ***b) // 这里调换四级指针指向地址
{
    printf("%p %p\n", (void *)a, (void *)b); // 000000000061FDF0 000000000061FDE8
    // printf("%p %p\n", (void *)&a, (void *)&b);
    uint ***temp = a; // 需要提别敏感 这里是改变的 副本的地址
    a = b;
    b = temp;
    printf("%p %p\n", (void *)a, (void *)b);
    // printf("%p %p\n", (void *)&a, (void *)&b); // 000000000061FDE8 000000000061FDF0
}

// 看清函数参数 需要几级指针
int main(void) 
{
    uint a = 1, b = 2;
    uint *a1 = &a, *b1 = &b;
    
    // printf("%p %p\n", (void *)a1, (void *)b1); //
    // printf("%p %p\n", (void *)&a, (void *)&b); // 
    // printf("%p %p\n", (void *)&a1, (void *)&b1); 
    // exchange(a1, b1); // 交换的是指针a1、b1指向的值
    // printf("%p %p\n", (void *)a1, (void *)b1); // 存储指针的地址没有变
    // printf("%p %p\n", (void *)&a, (void *)&b); // 
    // printf("%p %p\n", (void *)&a1, (void *)&b1); 
    
    // printf("%p %p\n", (void *)&*a1, (void *)&*b1); // 就是变量a 变量b 的地址
    // printf("%u %u\n", a, b); // 2  1  交换了 变得是地址内存储的值


    uint **a2 = &a1, **b2 = &b1;
    // printf("%p %p\n", (void *)a2, (void *)b2); 
    // printf("%p %p\n", (void *)&a1, (void *)&b1);
    // exchange(*a2, *b2); // 这和使用exchange(a1, b1); 是一样的
    // exchange2(a2, b2);
    // printf("%p %p\n", (void *)a2, (void *)b2); 
    // printf("%p %p\n", (void *)&a1, (void *)&b1);
    // printf("%u %u\n", a, b); // 2  1  交换了 变得是地址内存储的值(这里和上面都是改变的值 不是地址)
    // printf("%u %u\n", **a2, **b2); // 2  1  交换了 变得是地址内存储的值
    // printf("%u %u\n", *a1, *b1); // 2  1  交换了 变得是地址内存储的值
    
    // exchange2(a2, b2); // 这样即可 别写什么解引用 看清函数需要的参数
    /*
        **a2 = a1 是定义的二级指针 *a2 是一级指针，a1 是一级指针，所以 *a2 = a1 是将一级指针a1赋值给一级指针 *a2
    */
    // printf("%p %p\n", (void *)a1, (void *)b1); // 0x7ffeedd7c8cc 0x7ffeedd7c8d0
    // exchange2_1(a2, b2);
    // printf("%u %u\n", *a1, *b1); // 2  1  交换了 这里是调换了一级指针a1、b1的存储地址 （不是存储的值，是指针本身的地址）
    // printf("%p %p\n", (void *)a1, (void *)b1); // 0x7ffeedd7c8d0 0x7ffeedd7c8cc
    // printf("%u %u\n", a, b); // 1  2  交换了 这里是调换了一级指针a1、b1的存储地址 （不是存储的值，是指针本身的地址）

    // printf("%p %p\n", (void *)a2, (void *)b2); // 0x7ffeedd7c8d4 0x7ffeedd7c8d8
    // exchange2_2(a2, b2);
    // printf("%u %u\n", **a2, **b2); // 依旧是 1 2 这里改变的只是 二级指针本身的地址值(且还是改变的副本地址值)
    // printf("%p %p\n", (void *)a2, (void *)b2); // 0x7ffeedd7c8d4 0x7ffeedd7c8d8 不变的原因是 改变的是形参的地址
    // printf("%u %u\n", a, b);

    // uint ***a3 = &a2, ***b3 = &b2;
    // printf("%p %p\n", (void *)&a, (void *)&b);
    // exchange2_3(a3, b3);
    // printf("%p %p\n", (void *)&a, (void *)&b);
    // printf("%u %u\n", ***a3, ***b3); // 2 1 交换了 只是改变了 二级指针的地址值 
    // printf("%u %u\n", **a2, **b2);
    // 这里能看出来  再多级指针 一直追 也只是改变地址  真实的最原始的变量值并没有改变

    // printf("%u %u\n", a, b);

    
    // uint ***a3 = &a2, ***b3 = &b2;
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
    //register int a = 2; // 寄存器变量 可以提高访问速度（只是对编译器的建议，即使没有写register，编译器认为该放也会放）
    //*p = 4; // 解引用的使用
    //printf("%d\n", i); // 输出 4
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
