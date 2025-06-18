#include <stdio.h>
#include <stdlib.h>

int main() {
    int ****p1 = NULL, ***p2 = NULL, **p3 = NULL;
    int *p4 = NULL;
    int a = 1;

    /* NOTE p1 = &p2; p2 = &p3; p3 = &p4; p4 = &a; 是最好的方法 */

    // /* 空指针不能解引用 ，所以需要malloc */
    p1 = malloc(sizeof(int ***));   // 分配一层指针空间
    p2 = malloc(sizeof(int **));    // 分配一层指针空间

    *p1 = p2;        // *p1 -> p2
    *p2 = p3;        // *p2 -> p3 这里会让 p2 为NULL
    ***p2 = 2;		 // *p2 有malloc ，但是 **p2 贺 ***p2 都是不允许使用的
    // p1 = &p2;
    // p2 = &p3;

    // p3 = &p4;        // p3 -> p4
    // p4 = &a;         // p4 -> a

    // printf("p1 is %d, p2 is %d, p3 is %d\r\n", ****p1, ***p2, **p3);
    // printf("p3 is %d\r\n", **p3);
    // printf("p4 is %d\r\n", *p4);

    printf("p1 is %d,p2 is %d\r\n",****p1, ***p2);

    free(p1);
    free(p2);

    return 0;
}
