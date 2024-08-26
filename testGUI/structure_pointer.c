#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef unsigned char uint8_t;

#define DEBUG_HALI 1
#ifdef DEBUG_HALI
#define DEBUG_PRINT(fmt, ...) printf(fmt, ##__VA_ARGS__)
#else
#define DEBUG_PRINT(fmt, ...)
#endif

void me_free(void* pointer);
void print_binary(uint8_t num);



#define BIN(x) (1 << (x))

enum {
    LUNCH = BIN(1),
    DINNER = BIN(2),
    BREAKFAST = BIN(3)
};

typedef struct {
    uint8_t capacity;
}capacity_t;

typedef struct {
    char name[20];
    int age;
    capacity_t capacity;
}Student_t;

Student_t* student1;
Student_t student3 = {
    .name = "halibaduo",
    .age = 20,
    .capacity = {0}
};

int main(void) {
    // student1 = (Student_t*)malloc(sizeof(Student_t));
    // strcpy(student1->name, "John");
    // student1->age = 20;
    // DEBUG_PRINT("Name: %s\n", student1->name);
    // DEBUG_PRINT("Age: %d\n", student1->age);
    // free(student1);
    // student1 = NULL;

    student1 = (Student_t*)malloc(sizeof(Student_t));
    Student_t* student2  = &student3;
    DEBUG_PRINT("Name: %s\n", student2->name);
    DEBUG_PRINT("Age: %d\n", student2->age);
    student2->capacity.capacity |= LUNCH;

    if (student2->capacity.capacity & LUNCH) {
        DEBUG_PRINT("Lunch is available\n");
    }
    // 二进制方式输出
    print_binary(student2->capacity.capacity); 

    me_free(student1);
    student1 = NULL;

    return 0;
}

void me_free(void* pointer) {
    free(pointer);
    pointer = NULL;
}

void print_binary(uint8_t num) {
    // 假设是 32 位整数，根据需要可以调整这个数字
    for (int i = 7; i >= 0; i--) {
        // 检查第 i 位是否为 1
        uint8_t mask = (uint8_t)(1 << i);
        if (num & mask) {
            DEBUG_PRINT("1");
        } else {
            DEBUG_PRINT("0");
        }

        // 每4位加一个空格，便于阅读
        if (i % 4 == 0) {
            DEBUG_PRINT(" ");
        }
    }
    DEBUG_PRINT("\n");
}