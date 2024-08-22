#include <stdio.h>
#include <string.h>

void max(int);
typedef unsigned int uint;

struct MAX{
    int a;
    int *b;
}Max;

int main(void) 
{
    // uint a = 3;
    // uint *ptr = &a;
    // uint **pptr = &ptr;
    // uint ***ppptr = &pptr;
    // // printf("%u\n", **pptr); // 3
    // // printf("%p\n",(void *)pptr); // 000000000061FE14  (即指针ptr的地址)
    // printf("%p\n",(void *)ptr); // 000000000061FE14  (即指针pptr的地址)
    // printf("%p\n",(void *)**ppptr); // 

    // uint str[6];
    // memset(str, 0, sizeof(str));
    // if (str[0]) {
    //     printf("123");
    // }

    // 无法理解形参？看懂下面，我帮你
    // int a = 1;
    // printf("Actual parameters of a address:%p\n", (void *)&a);
    // printf("Actual parameters of a value:%d\n", *&a);
    // max(a);

    printf("结构体成员的大小:%llu\n", sizeof(Max));

    return 0;
}

void max(int a)
{
    printf("Formal parameters of a address:%p\n", (void *)&a);
    printf("Formal parameters of a value:%d\n", *&a);
}

void exchange_value(int a, int b)
{
    a = a + b;
    b = a - b;
    a = a - b;
}