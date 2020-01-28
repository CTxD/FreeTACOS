#include "tacoskernel.h"
#include "port.hpp"
#include <consumer_part.h>
#include <dummy_part.h>
#include <errcode.h>
#include <fib_part.h>
#include <process.hpp>
#include <queuing_port.hpp>

CTacosKernel::CTacosKernel()
{
}
CStdlibApp::TShutdownMode CTacosKernel::Run(void)
{
    QueuingPort* q1 = new QueuingPort({"Q1"}, 8, PORT_DIRECTION_TYPE::SOURCE, 10);
    mTimer.StartKernelTimer(7 * HZ, TimerHandler, this);
    while (1) {
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
    return ShutdownHalt;
}

void CTacosKernel::TimerHandler(TKernelTimerHandle hTimer, void* pParam, void* pContext)
{
    CTacosKernel* pThis = (CTacosKernel*)pParam;
    assert(pThis != 0);
    CTimer::Get()->StartKernelTimer(7 * HZ, TimerHandler, pThis);
    pThis->mEvent.Set();
}