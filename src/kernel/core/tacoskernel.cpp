#include "tacoskernel.h"
#include "apex_kernel.hpp"
#include "port.hpp"
#include <errcode.h>
#include <queuing_port.hpp>
#include <test_app.h>

CTacosKernel::CTacosKernel()
{
}
CStdlibApp::TShutdownMode CTacosKernel::Run(void)
{
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
        mLogger.Write("APP RUNNER", LogNotice, "------RUNNING SLAVE-------");
        Task* pSlave = static_cast<Task*>(ApexKernel::processPool[1]);

        pSlave->Run();
        mLogger.Write("APP RUNNER", LogNotice, "------SLAVE FINISHED------");
    }
    else {
        mLogger.Write("WARNING", LogWarning,
                      "Pool Size: %i - process wasn't added", ApexKernel::numProcesses);
    }

    mLogger.Write("RECAP", LogNotice,
                  "First: %i\nAfter app: %i\nAfter spawn: %i", a, b, c);

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