#include "halibaduo_register.h"

static void print_1(uint);
static void print_2(uint);

Function *fun_op = NULL;


int halibaduo_register(OP_S em)
{
    if (fun_op == NULL) { // Description has not been initialized yet
        fun_op = (Function *)malloc(sizeof(Function));
        if (fun_op == NULL) {
            return OP_ERROR;
        }
    }
    switch(em)
    {
        case OP_STATE_1:
            fun_op->op_func = print_1;
            goto END;
            break;
        case OP_STATE_2:
            fun_op->op_func = print_2;
            goto END;
            break;
        default:
            free(fun_op); 
            fun_op = NULL; 
            return OP_ERROR;
            break;
    }
END:
    return OP_OK;
}

static void print_1(uint param)
{
    printf("1:hello world %u\n", param);
}

static void print_2(uint param)
{
    printf("2:hello world %u\n", param);
}