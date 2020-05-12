#include "tacoskernel.h"
#include <circle/startup.h>
#include <errcode.h>

ret_t boot()
{
    CTacosKernel kernel;
    if (!kernel.Init()) {
        halt();
        return (ret_t)EXIT_HALT;
    }
    return (ret_t)kernel.Run();
}