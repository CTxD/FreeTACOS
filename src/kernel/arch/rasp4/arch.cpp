#include <arch.h>
#include <circle/debug.h>
#include <circle/gpiopin.h>
#include <circle/startup.h>
#include <circle/timer.h>
#include <errcode.h>

CKernel::CKernel(void) : CStdlibAppStdio("FreeTACOS Kernel")
{
    mActLED.Blink(5); // show we are alive
}

CStdlibApp::TShutdownMode CKernel::Run(void)
{
    mLogger.Write(GetKernelName(), LogNotice,
                  "C Standard Library stdin/stdout/stderr Demo");
    return CStdlibApp::ShutdownHalt;
}