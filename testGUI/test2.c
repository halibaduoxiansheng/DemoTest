#include <stdio.h>
#include <stdlib.h>

enum {
    Num_0 = 0,
    Num_1,
};

void printf_default_address(int *a) {
    printf("%p %p\n", (void *)a, (void *)&a);
}

int main(void) 
{
    // int a = Num_0, b = Num_1;
    // printf("%p %p\n", (void *)&a, (void *)&b);
    // printf_default_address(&a);
    // printf_default_address(&b);

    // int *ptr1 = NULL;
    // ptr1 = malloc(10 * sizeof(int));
    // for (int i = 0; i < 10; i++) {
    //     ptr1[i] = i;
    // }
    // for (int i = 0; i < 200; i++) {
    //     printf("%d ", ptr1[i]);
    // }

    // int *ptr2[11] = {NULL}; // 和 int string[11] = {NULL}; 一样
    // for (int i = 0; i < 11; i++) {
    //     ptr2[i] = malloc(10 * sizeof(int));
    //     printf("%d : %p  selfbody\n",i, (void *)&ptr2[i]);
    //     printf("%d : %p  point to\n",i, (void *)ptr2[i]); // 即 ptr2[0]指向的地址就是 ptr2[0][0]的地址
    //     // 类推：  ptr2[3]指向的地址就是 ptr2[3][0]的地址
    //     for (int j = 0; j < 10; j++) {
    //         printf("%p\n", (void *)&ptr2[i][j]);
    //     }
    // }
    // for (int i = 0; i < 11; i++) {
    //     for (int j = 0; j < 10; j++) {
    //         printf("%d ", ptr2[i][j]);
    //     }
    // }

    int array2[5][5];
    // printf("%d\n", sizeof(int));
    // printf("%p\n", (void *)array2);
    // printf("%p\n", (void *)array2[0]);
    // printf("%p\n", (void *)&array2[0][0]); // 这行往上三行都是一样的地址

    // printf("%p\n", (void *)array2[3]);
    // printf("%p\n", (void *)&array2[3][0]); // 000000000061FDEC
    // printf("%p\n", (void *)&array2[2][4]); //四个字节 000000000061FDE8、000000000061FDE9、000000000061FDEA、000000000061FDEB

    array2[2][2] = 256;
    printf("%p\n", (void *)&array2[2][2]); // 分配的首地址和使用的地址是相反的啊
    uintptr_t address = 0x000000000061FD90;
    uintptr_t address1 = 0x000000000061FD91;
    uintptr_t address2 = 0x000000000061FD92;
    uintptr_t address3 = 0x000000000061FD93;

    // 将地址转换为 unsigned char* 类型
    unsigned char *ptr = (unsigned char *)address;

    // 读取并打印该地址的第一个字节的值
    unsigned char value = *ptr;
    printf("Value at address 0x%lx: 0x%02x\n", address, value);

    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    // 将地址转换为 unsigned char* 类型
    unsigned char *ptr1 = (unsigned char *)address1;
    // 读取并打印该地址的第一个字节的值
    unsigned char value1 = *ptr1;
    printf("Value at address 0x%lx: 0x%02x\n", address1, value1);

    unsigned char *ptr2 = (unsigned char *)address2;
    unsigned char value2 = *ptr2;
    printf("Value at address 0x%lx: 0x%02x\n", address2, value2);

    unsigned char *ptr3 = (unsigned char *)address3;
    unsigned char value3 = *ptr3;
    printf("Value at address 0x%lx: 0x%02x\n", address3, value3);

    return 0;
}