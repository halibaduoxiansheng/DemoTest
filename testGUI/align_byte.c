#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// __attribute__((__packed__)) 就是指明 不要向大的对齐填充

// 32位系统，是4个字节一对齐，64位系统，是8个字节一对齐，这是使用uint32也是为了访问速度
// 位域（就抓住两个重点：1.共享 2.对齐大的）
// typedef struct {
//     uint32_t uart0_sel : 1;  // 1 bit
//     uint32_t reserved : 31;  // 31 bits
// } BitFieldExample; // 占用4个字节，共享一个uint32_t 单元

// struct lmac_init_param {
//     uint32 rxbuf, rxbuf_size; // 接收地址、接收地址大小
//     uint32 tdma_buff, tdma_buff_size;
//     uint32 uart0_sel : 1; // uart 选择标识
// }; // 这个就不同，虽然uart0_sel想共享单元，但是其它的单元都占据满了，所以它还是占用4个字节

// typedef struct byte {
//     char a : 2;
//     int b : 6;
// }__attribute__((__packed__)) byte_t; // 占用5个字节（会按照大的对齐）

// typedef struct byte {
//     char a : 2;
//     int b : 6;
// } byte_t; // 会占用8个字节，会将char的也对齐为4个字节的

// typedef struct byte {
//     char a : 2;
//     char b : 6;
//     int c : 6;
// }__attribute__((__packed__)) byte_t; // 5个字节，但是如果去除对齐关键字，会占用8个字节

// typedef struct byte {
//     char a : 2;
//     char b : 6;
//     int c : 6;
// }__attribute__((__packed__)) byte_t;


typedef struct byte {
    char a;
    int *b;
    char c;
}__attribute__((__packed__)) byte_t;
byte_t byte_1;

int main(void) {    
    // printf("%d Bytes\n", sizeof(byte_t));
    // printf("%d Bytes\n", sizeof(byte_1));
    printf("%p\n", (void *)&byte_1.a);
    printf("%p\n", (void *)&byte_1.b);
    printf("%p\n", (void *)&byte_1.c);
    return 0;
}