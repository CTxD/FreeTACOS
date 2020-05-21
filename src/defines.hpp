#ifndef __DEFINES__
#define __DEFINES__

// Kernel defines
#define KERNEL_PROCESSER(X) KERNEL_##X()
#define KERNEL_IS_MULTICORE() 0
#define KERNEL_IS_SINGLECORE() 1
#define KERNEL_DEBUG() 1

// Types defines
#define TYPES_IS_MULTICORE() 0

// APEX defines
#define APEX_DEBUG() 0

// Tests
#define APEX_TEST() 1

#endif