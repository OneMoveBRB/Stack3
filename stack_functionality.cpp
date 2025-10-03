#include "stack.h"

#include <stdio.h>


StackErr_t StackPush(Stack_t* stack, type value) {
#if STACK_MODE == STACK_DEBUG
    StackErr_t err_flag = OK;
    if ((err_flag = STACK_VERIFY(stack, errno)) != OK) return err_flag;
#endif

    if (stack->size + 1 == stack->capacity - TWO_CANARIES) StackUpdate(stack);

    *(type*)MoveArrPtr(stack->arr, stack->size) = value;
    ++stack->size;

#if STACK_MODE == STACK_DEBUG
    if ((err_flag = STACK_VERIFY(stack, errno)) != OK) return err_flag;
#endif

    return OK;
}

type StackPop(Stack_t* stack) {
#if STACK_MODE == STACK_DEBUG
    StackErr_t err_flag = OK;
    if ((err_flag = STACK_VERIFY(stack, errno)) != OK) return err_flag;

    if (stack->size == 0) return STACK_VERIFY(stack, EPERM);
#endif

    type element = *(type*)MoveArrPtr(stack->arr, stack->size-1);
    *(type*)MoveArrPtr(stack->arr, stack->size-1) = 0;
    --stack->size;

#if STACK_MODE == STACK_DEBUG
    if ((err_flag = STACK_VERIFY(stack, errno)) != OK) return err_flag;
#endif
    
    return element;
}
