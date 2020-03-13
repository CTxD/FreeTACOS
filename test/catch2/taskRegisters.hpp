#ifndef TASK_REGISTERS
#define TASK_REGISTERS

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

#define TASK_STACK_SIZE 8000

struct TTaskRegisters {
    u64 x0; // parameter for CTask::TaskEntry()

    u64 x16; // unknown role (on this platform)
    u64 x17;
    u64 x18;

    u64 x19; // callee-saved registers
    u64 x20;
    u64 x21;
    u64 x22;
    u64 x23;
    u64 x24;
    u64 x25;
    u64 x26;
    u64 x27;
    u64 x28;

    u64 x29; // frame pointer
    u64 x30; // link register
    u64 sp;  // stack pointer

    u64 d8; // SIMD and floating-point registers
    u64 d9;
    u64 d10;
    u64 d11;
    u64 d12;
    u64 d13;
    u64 d14;
    u64 d15;

    u64 fpcr; // floating-point control register
    u64 fpsr; // floating-point status register
};

#endif
