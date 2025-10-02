#define STACK_DEBUG     1
#define STACK_REALIZE   0

#ifndef STACK_MODE
#define STACK_MODE STACK_DEBUG
#endif

#if STACK_MODE == STACK_DEBUG
struct VarInfo{
    const char* file;
    const char* func;
    int line;
};
#endif

struct Stack_t {
    void* arr;
    size_t size;
    size_t capacity;

#if STACK_MODE == STACK_DEBUG
    VarInfo debugMemory;
    const unsigned int* LeftBorder;
    const unsigned int* RightBorder;
    static const unsigned int canary = 0xBAADF00D;
#endif
};

enum StackErr_t {
    OK                  = 0,
    NULL_PTR            = 0x50FFC001,
    STACK_OVERFLOW      = 0xBEEFBABE,
    WRONG_CAPACITY      = 0xD0D0CACA,
    ZERO_SIZE           = 111111,
    CANARY_FAILED       = 111113
};
