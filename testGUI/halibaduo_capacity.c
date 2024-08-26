#include "halibaduo_capacity.h"

Capacity_t capacity;

void hali_set_capacity(Thing thing) {
    capacity.capacity |= thing;
}

int hali_get_capacity(void) {
    return capacity.capacity;
}

int hali_haveset_capacity(Thing thing) {
    return (capacity.capacity & thing) == thing;
}