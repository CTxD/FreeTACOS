#include <arch.h>
#include <circle/gpiopin.h>
#include <circle/memory.h>
#include <circle/startup.h>
#include <circle/timer.h>
#include <errcode.h>

ret_t init_arch()
{
    CBootableKernel kernel;
    return kernel.Start();
}

CBootableKernel::CBootableKernel()
{
}
CBootableKernel::~CBootableKernel()
{
}

ret_t CBootableKernel::Start()
{
    CKernel kernel;
    if (!Initialize()) {
        halt();
        return (ret_t)EXIT_HALT;
    }

    TShutdownMode ShutdownMode = Run();

    switch (ShutdownMode) {
    case ShutdownReboot:
        reboot();
        return (ret_t)EXIT_REBOOT;

    case ShutdownHalt:
    default:
        halt();
        return (ret_t)EXIT_HALT;
    }
};

CKernel::CKernel(void)
{
}

CKernel::~CKernel(void)
{
}

boolean CKernel::Initialize(void)
{
    return TRUE;
}

TShutdownMode CKernel::Run(void)
{
    return ShutdownReboot;
}
