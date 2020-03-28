#include "tacoskernel.h"
#include "port.hpp"
#include "process_schedule.hpp"
#include "scheduling/partitionscheduling.hpp"
#include <apex_kernel.hpp>
#include <circle/time.h>
#include <consumer_part.h>
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
    mLogger.Write("Tester", LogNotice, "Testing ProcessSchedules..");
    mLogger.Write("ProcessSchedule", LogNotice,
                  "Initialising schedules from XML");

    ProcessSchedule::initialiseSchedules();

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

    // Running Entry Process
    auto entry = new Entry(&mLogger);
    entry->Run();
    partitionSchedule.partitionScheduler();

    while (1) {
    }

    /*partitionScheduler();
    ApexKernel apex = ApexKernel{};

    Task* app = new TestApp(&mLogger);

    auto a = ApexKernel::numProcesses;
    apex.addToProcessList(app);
    auto b = ApexKernel::numProcesses;

    mLogger.Write("APP RUNNER", LogNotice, "------RUNNING MASTER-------");
    Task* pMaster = static_cast<Task*>(ApexKernel::processPool[0]);
    pMaster->Run();
    mLogger.Write("APP RUNNER", LogNotice, "------MASTER FINISHED------");

    auto c = ApexKernel::numProcesses;

    if (c >= 2) {
        mLogger.Write("ProcessSchedule", LogNotice, "Adding Slave");

        Task* pSlave = static_cast<Task*>(ApexKernel::processPool[1]);
        mLogger.Write("APP RUNNER", LogNotice, "Slave Name: %s",
                      *(pSlave->getProcessName().x));
    }
    else {
        mLogger.Write("WARNING", LogWarning,
                      "Pool Size: %i - process wasn't added", ApexKernel::numProcesses);
    }

    mLogger.Write("RECAP", LogNotice,
                  "First: %i\nAfter app: %i\nAfter spawn: %i", a, b, c);

    mLogger.Write("RECAP", LogWarning, "Process Test");
    auto* p0 = static_cast<Task*>(ApexKernel::processPool[0]);
    auto* p1 = static_cast<Task*>(ApexKernel::processPool[1]);
    auto* p2 = static_cast<Task*>(ApexKernel::processPool[2]);

    mLogger.Write("RECAP", LogWarning, "P0: %s", *(p0->getProcessName().x));
    mLogger.Write("RECAP", LogWarning, "P1: %s", *(p1->getProcessName().x));
    mLogger.Write("RECAP", LogWarning, "P2: %s", *(p2->getProcessName().x));

    while (1) {
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