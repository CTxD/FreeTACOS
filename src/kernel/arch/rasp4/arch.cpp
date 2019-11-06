#include <arch.h>
#include <circle/debug.h>
#include <circle/gpiopin.h>
#include <circle/startup.h>
#include <circle/timer.h>
#include <errcode.h>

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

CKernel::CKernel(void) : CStdlibAppStdio("CKERNEL")
{
    mActLED.Blink(5); // show we are alive
}

CStdlibApp::TShutdownMode CKernel::Run(void)
{
    mLogger.Write(GetKernelName(), LogNotice,
                  "C Standard Library stdin/stdout/stderr Demo");
    return CStdlibApp::ShutdownHalt;
}