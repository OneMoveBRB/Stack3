#include "stack.h"

#include <stdio.h>

unsigned const int* create_const_int(void* ptr, unsigned int value) {
    unsigned int* temp = (unsigned int*)ptr;
    *temp = value;

    return (const unsigned int*)temp;
}

void* MoveArrPtr(void* ptr, size_t offset) {
    return (void*)((char*)ptr + offset*sizeof(type));
}

StackErr_t StackPrint(Stack_t* stack) {
#if STACK_MODE == STACK_DEBUG
    printf("%u\n", *(const unsigned int*)stack->arr);
#endif
    for (size_t i = 0; i < stack->size; i++) {
        printf("%d\n", *(type*)MoveArrPtr(stack->arr, i));
    }
    return OK;
}
