#include <stdio.h>

void print_address(int *a, int *b);

int main(void) {
    int a = 1, b = 2;
    printf("a: %p b: %p\n", (void *)&a, (void *)&b);
    print_address(&a, &b);    
    printf("a: %d b: %d\n", a, b);
}

void print_address(int *a, int *b)
{
    printf("a: %p b: %p\n", (void *)&a, (void *)&b); // 指针本身的地址
    printf("a: %p b: %p\n", (void *)a, (void *)b); // 指针指向的地址 （即为传入的地址）
    *a = *a ^ *b;
    *b = *a ^ *b;   
    *a = *a ^ *b;
    printf("a: %p b: %p\n", (void *)&a, (void *)&b); // 指针本身的地址
    printf("a: %p b: %p\n", (void *)a, (void *)b); // 指针指向的地址 （即为传入的地址）
}