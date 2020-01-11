#include "tacoskernel.h"
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

    while (1) {
        mLogger.Write(GetKernelName(), LogNotice,
                      "C Standard Library stdin/stdout/stderr Demo");
        return ShutdownHalt;
    }
}

void CTacosKernel::TimerHandler(TKernelTimerHandle hTimer, void* pParam, void* pContext)
{
    CTacosKernel* pThis = (CTacosKernel*)pParam;
    assert(pThis != 0);

    pThis->mEvent.Set();
}