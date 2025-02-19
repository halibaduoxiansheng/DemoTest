#include <stdio.h>


void print_binary(unsigned char val) {
    int i;
    for (i = 7; i >= 0; i--) {
        putchar((val >> i) & 1 ? '1' : '0');
    }
}
// 
int main()
{
    /*int array[5][6] = {0};
    int *ptr = array[0];
    int (*ptr1)[6] = array; // ptr1 是一个指向 array 第一行的指针
    

    printf("%d\n", *ptr); // 0

    // 下面四行是一样的 都是指向首地址
    printf("%p\n", (void*)ptr1);
    printf("%p\n", (void*)array);
    printf("%p\n", (void*)&array[0][0]);
    printf("%p\n", (void*)array[0]);

    // 下面两行一致(和上面的四行一样，打印的地址)
    printf("%p\n", *ptr1); // *ptr1 相当于 array[0]
    printf("%p\n", *array); // *array 也相当于 array[0]

    // 下面两行一致
    printf("%d\n", *&array[0][0]); // 0
    printf("%d\n", *array[0]); // 0
    */

    /*int num = 10;
    char *ptr = (char *)&num;

    printf("num的二进制表示为:");
    for (int i = 0; i < sizeof(int); i++) {
        print_binary(ptr[i]);
	printf(".");
    }
    printf("\n");*/

    unsigned int binary = 0b1010;// 二进制

    unsigned int octal = 0123;//八进制

    unsigned int decimal = 123;//十进制

    unsigned int hexadecimal = 0x1A3;//十六进制

    // 下面是10进制输出
    printf("Binary (0b1010): %u\n", binary);//10
    printf("Octal (0123): %u\n", octal);//83
    printf("Decimal (123): %u\n", decimal);//123
    printf("Hexadecimal (0x1A3): %u\n", hexadecimal);//419
    

    return 0;
}
