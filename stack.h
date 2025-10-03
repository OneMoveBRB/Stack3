#ifndef STACK_H
#define STACK_H

#include <stddef.h>
#include "stack_settings.h"

#if STACK_MODE == STACK_DEBUG
#include <errno.h>
#define errno_t error_t
#endif

#ifndef TWO_CANARIES
#define TWO_CANARIES 0
#endif

#define INIT VarInfo{__FILE__, __func__, __LINE__}
#define STACK_VERIFY(stack_ptr, _errno) \
    StackVerify(stack_ptr, INIT, _errno)


typedef int type;


StackErr_t StackInit(Stack_t* stack, size_t capacity);
StackErr_t StackUpdate(Stack_t* stack);
StackErr_t StackDestroy(Stack_t* stack);


StackErr_t StackPush(Stack_t* stack, type value);
type StackPop(Stack_t* stack);


/* CALCULATOR */
// StackErr_t StackAdd(Stack_t* stack);
// StackErr_t StackSub(Stack_t* stack);
// StackErr_t StackMul(Stack_t* stack);


#if STACK_MODE == STACK_DEBUG
StackErr_t StackVerify(Stack_t* stack, VarInfo curInfo, errno_t error = 0);
StackErr_t StackDump(Stack_t* stack, VarInfo curInfo, errno_t error);
#endif

void* MoveArrPtr(void* ptr, size_t offset);
unsigned const int* create_const_int(void* ptr, unsigned int value);
StackErr_t StackPrint(Stack_t* stack);


#endif // STACK_H
