#include <stdio.h>
#include <time.h>
// 计算延迟
#define ITERATIONS 2147483647

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

    return 0;
}
