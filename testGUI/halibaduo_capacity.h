#ifndef _HALIBADUO_CAPACITY_H_
#define _HALIBADUO_CAPACITY_H_

#define BIN(N) (1 << (N))

typedef enum THING{
    HOT_WATER = BIN(0),
    COLD_WATER = BIN(1),
    COLA_WATER = BIN(2),
    TEA_WATER = BIN(3),
    COFFEE_WATER = BIN(4),
    SODA_WATER = BIN(5)
}Thing;

typedef struct {
    int capacity;
    int size;
    int *data;
}Capacity_t; // _t 表示别名

void hali_set_capacity(Thing thing);
int hali_get_capacity(void);
int hali_haveset_capacity(Thing thing);

#endif