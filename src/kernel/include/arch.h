#ifndef __FREETACOS_ARCH__
#define __FREETACOS_ARCH__

#include <circle/memory.h>
#include <circle/sched/scheduler.h>
#include <circle/sched/synchronizationevent.h>

#include <circle_stdlib_app.h>
#include <errcode.h>
#include <init_worker.hpp>

class CKernel : public CStdlibAppStdio {
public:
    CKernel(void);

    TShutdownMode Run(void);
    bool Init()
    {
        boolean bOK = TRUE;
        if (bOK)
            bOK = this->Initialize();
        if (bOK)
            bOK = mWorker.Initialize();
        return bOK;
    }

protected:
    CMemorySystem mMemory;
    CInitialWorker mWorker;
    CScheduler mScheduler;
    CSynchronizationEvent mEvent;
};

#endif