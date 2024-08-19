#include <stdio.h>
#include <time.h>

int main() {
    clock_t start, end;
    double cpu_time_used;

    start = clock();
    printf("Hello, World!\n");
    end = clock();

    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("123Time taken: %f seconds\n", cpu_time_used);

    return 0;
}
