#include <stdio.h>

struct event {
	int a;
	char b;
	float c;
};
// 编译器回内存对齐
// |   a (4字节)   | b (1字节) | padding (3字节) | c (4字节) |


#define list_entry_1(ptr, type, member) \
    ((type *)((char *)(ptr) - (unsigned long)(&((type *)0)->member)))

int main(void)
{
	struct event e;

	printf("struct e size %d Bytes\r\n", sizeof(e)); // 12 
	printf("int a size %d Bytes\r\n",sizeof(e.a)); // 4
	printf("char b size %d Bytes\r\n",sizeof(e.b)); // 1
	printf("float c size %d Bytes\r\n",sizeof(e.c)); // 4

	printf("print e address : %p\r\n",&e);
	printf("print e.a address : %p\r\n",&e.a);
	printf("print e.b address : %p\r\n",&e.b);
	printf("print e.c address : %p\r\n",&e.c);
	/**
	 * 范例
	 *  print e address : 	000000000061FE0C
		print e.a address : 000000000061FE0C
		print e.b address : 000000000061FE10 （+4）
		print e.c address : 000000000061FE14 （+4） 因为对齐了
		print d address : 	000000000061FE0C
	 */

	char* d = list_entry_1(&e.b, struct event, b);
	printf("print d address : %p\r\n",d);
	return 0;
}

/**
 * #pragma pack(2)
	struct event {
	    int a;
	    char b;
	    float c;
	};
	#pragma pack()
	强制所有字段两字节对齐
 */
/**
	 * struct event {
	    int a;
	    char b;
	    float c;
	} __attribute__((packed));
	禁用对齐
 */