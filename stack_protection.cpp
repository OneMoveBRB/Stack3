#include "stack.h"

#include <stdio.h>
#include <string.h>

#define MSG_LEN 1024

StackErr_t StackVerify(Stack_t* stack, VarInfo curInfo, errno_t error) {
    if (error != 0) {
        StackDump(stack, curInfo, error);
        switch (error) {
            case EFAULT:
                return NULL_PTR;
            case EINVAL:
                return WRONG_CAPACITY;
            case ENOMEM:
                return STACK_OVERFLOW;
            case EPERM:
                return ZERO_SIZE;
        }
        error = 0;
    }

    if (stack == NULL || stack->arr == NULL) {
        StackDump(stack, curInfo, EFAULT);
        return NULL_PTR;
    }

    if ((*stack->LeftBorder != stack->canary) || (*stack->RightBorder != stack->canary)) {
        StackDump(stack, curInfo, ENOLCK);
        return CANARY_FAILED;
    }

    return OK;
}

// Записывает состояние программы в отладочный файл в данный момент
StackErr_t StackDump(Stack_t* stack, VarInfo curInfo, errno_t error) {
    char error_buf[MSG_LEN] = "";
    char* error_message = NULL;

    error_message = strerror_r(error, error_buf, MSG_LEN);

    fprintf(stderr, "File : %s\nLine : %d\nCurrent function : %s()\nError message : %s\n", 
                    curInfo.file, curInfo.line, curInfo.func, error_message);

    return OK;
}
