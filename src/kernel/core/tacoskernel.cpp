#include "tacoskernel.h"
#include "port.hpp"
#include <errcode.h>
#include <queuing_port.hpp>
#include <test_app.h>

CTacosKernel::CTacosKernel()
{
}
CStdlibApp::TShutdownMode CTacosKernel::Run(void)
{
    auto app = TestApp(&mLogger);
    app.Run();

    while (1) {
    }

    /*
    QueuingPort* q1 = new QueuingPort({"Q1"}, 8, PORT_DIRECTION_TYPE::SOURCE,
    10); mTimer.StartKernelTimer(7 * HZ, TimerHandler, this); while (1) {
        mEvent.Clear();
        // Cyclic schedule
        new FibPart(&mLogger, q1);
        new ConsumerPart(&mLogger, q1);
        //
        mEvent.Wait();
    }
    while (1) {
        CLogger::Get()->Write("FreeTACOS", LogNotice, "In busy loop");
    }
    */
    return ShutdownHalt;
}

void CTacosKernel::TimerHandler(TKernelTimerHandle hTimer, void* pParam, void* pContext)
{
    CTacosKernel* pThis = (CTacosKernel*)pParam;
    assert(pThis != 0);
    CTimer::Get()->StartKernelTimer(7 * HZ, TimerHandler, pThis);
    pThis->mEvent.Set();
}