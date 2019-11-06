#include <errcode.h>
#include "tacoskernel.h"
#include <circle/startup.h>

ret_t boot()
{
    CTacosKernel kernel;
    if (!kernel.Initialize())
    {
        halt();
        return (ret_t)EXIT_HALT;
    }
    return (ret_t)kernel.Run();
}