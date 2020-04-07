#include "tacoskernel.h"
#include "port.hpp"
#include "process_schedule.hpp"
#include "scheduling/partitionscheduling.hpp"
#include <apex_kernel.hpp>
#include <circle/time.h>
#include <consumer_part.h>
#include <defines.hpp>
#include <dummy_part.h>
#include <entry.hpp>
#include <errcode.h>
#include <queuing_port.hpp>
#include <test_app.hpp>

CTacosKernel::CTacosKernel()
{
}

CStdlibApp::TShutdownMode CTacosKernel::Run(void)
{
    CyclicExecutiveSchedule partitionSchedule;
#if KERNEL_DEBUG()
    mLogger.Write("Tester", LogNotice, "Testing ProcessSchedules..");
    mLogger.Write("ProcessSchedule", LogNotice,
                  "Initialising schedules from XML");
#endif

    ProcessSchedule::initialiseSchedules();

#if KERNEL_DEBUG()
    mLogger.Write("ProcessSchedule", LogNotice, "Printing Names:");
    auto* schedule = ProcessSchedule::scheduleList->at(0);
    mLogger.Write("ProcessSchedule", LogNotice, "Name: %s---",
                  *(schedule->getProcessScheduleName()->x.x));
    schedule = ProcessSchedule::scheduleList->at(1);
    mLogger.Write("ProcessSchedule", LogNotice, "Name: %s---",
                  *(schedule->getProcessScheduleName()->x.x));
    schedule = ProcessSchedule::scheduleList->at(2);
    mLogger.Write("ProcessSchedule", LogNotice, "Name: %s---",
                  *(schedule->getProcessScheduleName()->x.x));
    schedule = ProcessSchedule::scheduleList->at(3);
    mLogger.Write("ProcessSchedule", LogNotice, "Name: %s---",
                  *(schedule->getProcessScheduleName()->x.x));
    schedule = ProcessSchedule::scheduleList->at(4);
    mLogger.Write("ProcessSchedule", LogNotice, "Name: %s---",
                  *(schedule->getProcessScheduleName()->x.x));
#endif

    // Running Entry Process
    auto entry = new Entry(&mLogger);
    entry->Run();

    partitionSchedule.partitionScheduler();

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