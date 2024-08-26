#include <stdio.h>
#include "halibaduo_register.h"
#include "halibaduo_capacity.h"

int main(void)
{
    int flag = halibaduo_register(OP_STATE_1);
    if (flag == OP_OK) {
        fun_op->op_func(10);
    }
    halibaduo_register(OP_STATE_2);
    fun_op->op_func(10);


    hali_set_capacity(COFFEE_WATER);
    int l_capacity = hali_get_capacity();
    if (l_capacity & COFFEE_WATER) {
        printf("Already set COFFEE_WATER\n");
    }
    if(hali_haveset_capacity(HOT_WATER)) {
        printf("Already set HOT_WATER\n");
    }
    return 0;
}