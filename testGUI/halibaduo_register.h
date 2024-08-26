#ifndef _HALIBADUO_REGISTER_H_
#define _HALIBADUO_REGISTER_H_

#include <stdio.h>
#include <stdlib.h>

typedef unsigned int uint;

typedef enum OP_State{
    OP_STATE_1 = 0,
    OP_STATE_2,

    OP_OK = 0,
    OP_ERROR = 1
}OP_S;

typedef void (*func)(uint);
typedef struct Function
{
    func op_func; // 所有使用函数 都是它
    /* 需要增加函数指针 在这里增加 */
}Function;
extern Function *fun_op;


int halibaduo_register(OP_S em);


#endif

