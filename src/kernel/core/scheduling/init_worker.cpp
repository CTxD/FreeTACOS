#include "init_worker.hpp"
#include <circle/logger.h>
#include <circle/startup.h>
#include <circle/time.h>

CInitialWorker::CInitialWorker(CMemorySystem* pMemorySystem)
#ifdef ARM_ALLOW_MULTI_CORE
    : CMultiCoreSupport(pMemorySystem)
#endif
{
}

CInitialWorker::~CInitialWorker()
{
}

void CInitialWorker::IPIHandler(unsigned nCore, unsigned nIPI)
{
    assert(nCore < CORES);
    assert(nIPI <= IPI_MAX);

    if (nIPI == IPI_HALT_CORE) {
        CLogger::Get()->Write("CIW", LogDebug, "CPU coore %u will halt now", ThisCore());

        halt();
    }
}

void CInitialWorker::Run(unsigned nCore)
{
#ifdef ARM_ALLOW_MULTI_CORE
    CLogger::Get()->Write("CInitialWorker", LogNotice, "Running MCore %u ...", nCore);
    if (nCore != 0)
        while (1) {
            CLogger::Get()->Write("CInitialWorker", LogNotice,
                                  "Running MCore %u ...", nCore);
            CTimer::Get()->MsDelay(1000);
        }
#else
    CLogger::Get()->Write("CInitialWorker", LogNotice, "Running SCore %u ...", nCore);
#endif

    return;
}