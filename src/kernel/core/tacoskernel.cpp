#include "tacoskernel.h"
#include "port.hpp"
#include "scheduling/partitionscheduling.hpp"
#include <circle/time.h>
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
    partitionScheduler();
    while (1) {
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