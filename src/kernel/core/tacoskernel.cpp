#include "tacoskernel.h"
#include "partitionscheduling.hpp"
#include "port.hpp"
#include "process_schedule.hpp"
#include <apex_kernel.hpp>
#include <circle/time.h>
#include <consumer_part.h>
#include <context.hpp>
#include <defines.hpp>

#include <dummy_part.h>
#include <entry.hpp>
#include <errcode.h>
#include <queuing_port.hpp>
#include <test_app.hpp>

ProcessSchedule* pScheduler = NULL;

// Debug
TSysRegs sysRegs;

// Allocation of PCBS
typedef void (*run_func)();

Task* pA = NULL;
Task* pB = NULL;
Task* pKernel = NULL;

CTacosKernel::CTacosKernel()
{
}

CStdlibApp::TShutdownMode CTacosKernel::Run(void)
{
    // pA = new TestApp(&mLogger, {"flightManagement"});
    // pB = new TestApp(&mLogger, {"io"});
    // pKernel = new TestApp(&mLogger, {"io"});

    // pA = initProcess(pA);
    // pB = initProcess(pB);
    // pKernel = initProcess(pKernel);

    // pCurrentPCBStack = pKernel->pTopOfStack;
    // pCurrent = pKernel;

    // CTimer::Get()->StartKernelTimer(2 * HZ, TimerHandler, this);
    // while (1) {
    //     CLogger::Get()->Write("Inside Run", LogNotice, " ... ");
    //     CTimer::Get()->MsDelay(1000);
    // }
    // return ShutdownHalt;

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

    partitionSchedule.initPartitionScheduler();
    CTimer::Get()->StartKernelTimer(0, PartitionTimerHandler, this, &partitionSchedule);
    CTimer::Get()->StartKernelTimer(100, ProcessTimerHandler, this, &partitionSchedule);
    while (1) {
        CLogger::Get()->Write("CPU time to processes", LogNotice, " ... ");
        CTimer::Get()->MsDelay(1000);
    }
    return ShutdownHalt;
}

void CTacosKernel::PartitionTimerHandler(TKernelTimerHandle hTimer, void* pParam, void* pSavedContext)
{
    CTacosKernel* pThis = (CTacosKernel*)pParam;
    CyclicExecutiveSchedule* pPartitionScheduler = (CyclicExecutiveSchedule*)pSavedContext;
    assert(pThis != 0);

    pPartitionScheduler->partitionHandler();

    auto runTime = CyclicExecutiveSchedule::getCurrentPartition()->endTime -
                   CyclicExecutiveSchedule::getCurrentPartition()->startTime;

    name_t partitionName = {
        (*CyclicExecutiveSchedule::getCurrentPartition()[0].partitionName.x)};

    auto* processSchedule = ProcessSchedule::getProcessScheduleByName(partitionName);
    processSchedule->startScheduler();
    pScheduler = processSchedule;

    // CLogger::Get()->Write("PTH", LogNotice, "Run time %u, %u", runTime, runTime / HZ);

    CTimer::Get()->StartKernelTimer(200, PartitionTimerHandler, pParam, pSavedContext);
}

void CTacosKernel::ProcessTimerHandler(TKernelTimerHandle hTimer, void* pParam, void* pSavedContext)
{
    CTacosKernel* pThis = (CTacosKernel*)pParam;
    CyclicExecutiveSchedule* pPartitionScheduler = (CyclicExecutiveSchedule*)pSavedContext;
    assert(pThis != 0);
    pScheduler->iterate();
    CTimer::Get()->StartKernelTimer(50, ProcessTimerHandler, pParam, pSavedContext);
}
