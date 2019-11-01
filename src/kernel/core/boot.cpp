#include <errcode.h>
#include "tacoskernel.h"

ret_t boot(){
    CTacosKernel kernel;
    return kernel.Start();
}