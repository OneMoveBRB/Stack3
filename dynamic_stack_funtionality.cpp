#include "stack.h"

#include <stdio.h>
#include <stdlib.h>


StackErr_t StackInit(Stack_t* stack, size_t capacity) {
#if STACK_MODE == STACK_DEBUG
    if (stack == NULL) return STACK_VERIFY(stack, EFAULT);
    if (capacity < 1) return STACK_VERIFY(stack, EINVAL);
#endif

    stack->size = 0;

#if STACK_MODE == STACK_DEBUG
    stack->capacity = capacity + 2;
#else
    stack->capacity = capacity;
#endif

    stack->arr = calloc(stack->capacity, sizeof(type));
#if STACK_MODE == STACK_DEBUG
    if (stack->arr == NULL) return STACK_VERIFY(stack, ENOMEM);
#endif

    stack->debugMemory = INIT;

#if STACK_MODE == STACK_DEBUG
    stack->LeftBorder = create_const_int(stack->arr, stack->canary);
    stack->RightBorder = create_const_int(MoveArrPtr(stack->arr, capacity + 1), stack->canary);

    stack->arr = MoveArrPtr(stack->arr, 1);
#endif

    return OK;
}

StackErr_t StackUpdate(Stack_t* stack){
#if STACK_MODE == STACK_DEBUG
    if (stack == NULL) return STACK_VERIFY(stack, EFAULT);
#endif
    printf("Stack size: %zu\n", stack->size);
    
    const size_t exp_multiplier = 2;

#if STACK_MODE == STACK_DEBUG
    *(int*)stack->RightBorder = 0;
    stack->arr = (void*)((char*)stack->arr - 1 * sizeof(type));
#endif

    stack->capacity *= exp_multiplier;

    stack->arr = realloc(stack->arr, stack->capacity * sizeof(type));
#if STACK_MODE == STACK_DEBUG
    if (stack->arr == NULL) return STACK_VERIFY(stack, ENOMEM);
#endif

#if STACK_MODE == STACK_DEBUG
    stack->LeftBorder = (const unsigned int*)stack->arr;
    stack->RightBorder = create_const_int(MoveArrPtr(stack->arr, stack->capacity-1), stack->canary);
    
    stack->arr = MoveArrPtr(stack->arr, 1);
#endif

#if STACK_MODE == STACK_DEBUG
    printf("LEFT %d\n", *(const int*)stack->LeftBorder);
    printf("ARR %d\n", *(type*)stack->arr);
    printf("RIGHT %d\n", *(const int*)stack->RightBorder);
#endif

    return OK;
    
}

StackErr_t StackDestroy(Stack_t* stack) {
#if STACK_MODE == STACK_DEBUG
    if (stack == NULL) return STACK_VERIFY(stack, EFAULT);
#endif

#if STACK_MODE == STACK_DEBUG
    free((void*)stack->LeftBorder);
    stack->LeftBorder = NULL;
    stack->RightBorder = NULL;
#else
    free(stack->arr);
#endif

    stack->size = 0;
    stack->capacity = 0;
    stack->arr = NULL;
    
    return OK;
}
