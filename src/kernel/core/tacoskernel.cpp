#include "tacoskernel.h"

#include "partitionscheduling.hpp"
#include "port.hpp"
#include "process_schedule.hpp"
#include <apex_buffer.hpp>
#include <apex_kernel.hpp>
#include <apex_mutex.hpp>
#include <circle/time.h>
#include <consumer_part.h>
#include <defines.hpp>
#include <tacoskerneltest.hpp>

#include <dummy_part.h>
#include <entry.hpp>
#include <errcode.h>
#include <queuing_port.hpp>
#include <test_app.hpp>

ProcessSchedule* pCurrentProcessScheduler = NULL;

CTacosKernel::CTacosKernel()
{
}

CStdlibApp::TShutdownMode CTacosKernel::Run(void)
{
#if APEX_TEST()
    setup();
#endif
    CyclicExecutiveSchedule::GetCurrentPartition()->partitionName = {
        "IOProcessing"};

    BUFFER_ID_TYPE id;
    RETURN_CODE_TYPE code;

    ApexBuffer::initialiseBuffers();
    ApexMutex::InitializeMutex();

    ApexBuffer::CREATE_BUFFER({"TestBuffer"}, 255, 10, FIFO, &id, &code);

    if (code == NO_ERROR) {
        mLogger.Write("Tester", LogNotice, "Buffer created with id: %i", id);
    }
    else {
        mLogger.Write("Tester", LogNotice, "Error creating buffer");
    }
    CyclicExecutiveSchedule partitionSchedule;
#if KERNEL_DEBUG()
    mLogger.Write("Tester", LogNotice, "Testing ProcessSchedules..");
    mLogger.Write("ProcessSchedule", LogNotice,
                  "Initialising schedules from XML");
#endif

    ProcessSchedule::InitialiseSchedules();

#if KERNEL_DEBUG()
    mLogger.Write("ProcessSchedule", LogNotice, "Printing Names:");
    auto* schedule = ProcessSchedule::scheduleList->at(0);
    mLogger.Write("ProcessSchedule", LogNotice, "Name: %s---",
                  *(schedule->GetProcessScheduleName()->x.x));
    schedule = ProcessSchedule::scheduleList->at(1);
    mLogger.Write("ProcessSchedule", LogNotice, "Name: %s---",
                  *(schedule->GetProcessScheduleName()->x.x));
    schedule = ProcessSchedule::scheduleList->at(2);
    mLogger.Write("ProcessSchedule", LogNotice, "Name: %s---",
                  *(schedule->GetProcessScheduleName()->x.x));
    schedule = ProcessSchedule::scheduleList->at(3);
    mLogger.Write("ProcessSchedule", LogNotice, "Name: %s---",
                  *(schedule->GetProcessScheduleName()->x.x));
    schedule = ProcessSchedule::scheduleList->at(4);
    mLogger.Write("ProcessSchedule", LogNotice, "Name: %s---",
                  *(schedule->GetProcessScheduleName()->x.x));
#endif

    // Running Entry Process
    auto entry = new Entry(&mLogger);
    entry->Run();

    partitionSchedule.InitPartitionScheduler();
    CTimer::Get()->StartKernelTimer(0, PartitionTimerHandler, this, &partitionSchedule);
    CTimer::Get()->StartKernelTimer(100, ProcessTimerHandler, NULL, NULL);
    while (1) {
        CLogger::Get()->Write("Busy Looping", LogNotice, " ... ");
        CTimer::Get()->MsDelay(1000);
    }
    return ShutdownHalt;
}
// Invokes Partition Scheduling
void CTacosKernel::PartitionTimerHandler(TKernelTimerHandle hTimer, void* pParam, void* pSavedContext)
{
    CyclicExecutiveSchedule* pPartitionScheduler = (CyclicExecutiveSchedule*)pSavedContext;
    assert(pPartitionScheduler != 0);

    pPartitionScheduler->PartitionHandler();

    unsigned int runTime = CyclicExecutiveSchedule::GetCurrentPartition()->endTime -
                           CTimer::Get()->GetClockTicks();
    unsigned int runTimeSecs = runTime / CLOCKHZ;

    name_t partitionName = {
        (*CyclicExecutiveSchedule::GetCurrentPartition()[0].partitionName.x)};

    ProcessSchedule* ps = ProcessSchedule::GetProcessScheduleByName(partitionName);
    ps->StartScheduler();
    pCurrentProcessScheduler = ps;

    CTimer::Get()->StartKernelTimer(runTimeSecs * HZ, PartitionTimerHandler,
                                    pParam, pSavedContext);
}

// Invokes Process Scheduling
void CTacosKernel::ProcessTimerHandler(TKernelTimerHandle hTimer, void* pParam, void* pSavedContext)
{
    pCurrentProcessScheduler->Iterate();
    CTimer::Get()->StartKernelTimer(50, ProcessTimerHandler, pParam, pSavedContext);
}
