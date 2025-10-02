#include "stack.h"

#include <stdio.h>

StackErr_t StackPush(Stack_t* stack, type value) {
    if (stack == NULL) return STACK_VERIFY(stack, EFAULT);

#if STACK_MODE == STACK_DEBUG
    STACK_VERIFY(stack, errno);
#endif

// Сделаю макрос TWO_CANARIES 2 ....
// Тогда if (stack->size + 1 == stack->capacity - TWO_CANARIES) StackUpdate(stack); без #if
#if STACK_MODE == STACK_DEBUG
    if (stack->size + 1 == stack->capacity - 2) StackUpdate(stack);
#else
    if (stack->size + 1 == stack->capacity) StackUpdate(stack);
#endif

    *(type*)MoveArrPtr(stack->arr, stack->size) = value;
    ++stack->size;

#if STACK_MODE == STACK_DEBUG
    STACK_VERIFY(stack, errno);
#endif

    return OK;
}

type StackPop(Stack_t* stack) {
    if (stack == NULL) return STACK_VERIFY(stack, EFAULT);
    if (stack->size == 0) return STACK_VERIFY(stack, EPERM);

#if STACK_MODE == STACK_DEBUG
    STACK_VERIFY(stack, errno);
#endif

    type element = *(type*)MoveArrPtr(stack->arr, stack->size-1);
    *(type*)MoveArrPtr(stack->arr, stack->size-1) = 0;
    --stack->size;

#if STACK_MODE == STACK_DEBUG
    STACK_VERIFY(stack, errno);
#endif
    
    return element;
}
