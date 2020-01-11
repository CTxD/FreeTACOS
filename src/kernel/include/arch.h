#ifndef __FREETACOS_ARCH__
#define __FREETACOS_ARCH__

#include <circle/memory.h>
#include <circle/sched/scheduler.h>
#include <circle/sched/synchronizationevent.h>

#include <circle_stdlib_app.h>
#include <errcode.h>

class CKernel : public CStdlibAppStdio {
public:
    CKernel(void);

    TShutdownMode Run(void);

protected:
    CMemorySystem mMemory;
    CScheduler mScheduler;
    CSynchronizationEvent mEvent;
};

#endif