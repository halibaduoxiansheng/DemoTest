#include <stdio.h>
#include <time.h>
// 计算延迟
#define ITERATIONS 2147483649
#define CYCLE_COUNT 20
int main(void) {
    clock_t start, end;
    double time_taken;

    start = clock();

    for (int i = 0; i < ITERATIONS; i++) {
        // do something
    }

    end = clock();

    time_taken = ((double)(end - start)) / CLOCKS_PER_SEC * 1000; // 时间以毫秒为单位

    printf("Time taken for comparison: %f ms\n", time_taken);

    // int a = 10;
    // int b = 20;
    // a = a ^ b;
    // b = a ^ b;
    // a = a ^ b;
    // printf("a = %d, b = %d\n", a, b);

    return 0;
}
