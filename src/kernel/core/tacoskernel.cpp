#include "tacoskernel.h"
#include "../arinc_module.cpp"
#include <arinc_module.hpp>
#include <errcode.h>
#include <fibpart.h>
#include <process.hpp>

CTacosKernel::CTacosKernel()
{
}
CStdlibApp::TShutdownMode CTacosKernel::Run(void)
{
    // Cyclic schedule

    new FibPart(&mLogger);
    new FibPart(&mLogger);
    new FibPart(&mLogger);
    new FibPart(&mLogger);

    mEvent.Clear();
    mTimer.StartKernelTimer(60 * HZ, TimerHandler, this);
    while (1) {
        CLogger::Get()->Write("FreeTACOS", LogNotice, "In busy loop");
        mEvent.Wait();
    }
    return ShutdownHalt;
}

void CTacosKernel::TimerHandler(TKernelTimerHandle hTimer, void* pParam, void* pContext)
{
    CTacosKernel* pThis = (CTacosKernel*)pParam;
    assert(pThis != 0);

    pThis->mEvent.Set();
}