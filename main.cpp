#include "stack.h"

#include <stdio.h>

int main() {
    errno = 0;
    
    Stack_t stk;
    StackErr_t flag = OK;
    const int first_capacity = 5;

    flag = StackInit(&stk, first_capacity);
    if (flag != OK) fprintf(stderr, "ERROR: %u\n", flag);

    StackPush(&stk, 1000);
    StackPush(&stk, 2000);
    StackPush(&stk, 3000);
    StackPop(&stk);
    StackPush(&stk, 4000);
    StackPush(&stk, 5000);
    StackPush(&stk, 6000);
    StackPush(&stk, 7000);
    StackPop(&stk);


    StackPrint(&stk);

    flag = StackDestroy(&stk);
    if (flag != OK) fprintf(stderr, "ERROR: %u\n", flag);

    return 0;
}