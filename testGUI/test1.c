#include <stdio.h>
#include <string.h>

void max(int);
void exchange_value(int a, int b);
void printaddress_value1(int *a, int *b);
typedef unsigned int uint;

struct MAX{
    int a;
    int *b;
}Max;

void print_address(int *a, int *b)
{
    printf("%p %p\n", (void *)a, (void *)b);
}

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

    // printf("结构体成员的大小:%llu\n", sizeof(Max));

    // int a = 1, b = 2;
    // printf("a %p\n", (void *)&a);
    // printf("b %p\n", (void *)&b);
    // printaddress_value1(a, b);

    // int a = 1, b = 2;
    // int *a1 = &a, *b1 = &b;
    // int **a2 = &a1, **b2 = &b1;
    // int ***a3 = &a2, ***b3 = &b2;
    // printf("%p %p\n", (void *)&*a3, (void *)&*b3);
    // // printf("%d %d\n", ***a3, ***b3);
    // printf("%p %p\n", (void *)&a2, (void *)&b2);

    // printf("a:%d, b:%d\n", a, b);

    // int a = 1, b = 2;
    // int *a1 = &a, *b1 = &b;
    // printf("%p %p\n", (void *)a1, (void *)b1);
    // print_address(a1, b1);


    return 0;
}

// void max(int a)
// {
//     printf("Formal parameters of a address:%p\n", (void *)&a);
//     printf("Formal parameters of a value:%p\n", *&a);
// }

void printaddress_value1(int *a, int *b)
{
    printf("a %p\n", (void *)&a);
    printf("b %p\n", (void *)&b);
}

void exchange_value(int a, int b)
{
    a = a + b;
    b = a - b;
    a = a - b;
}