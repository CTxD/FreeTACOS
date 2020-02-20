#ifndef _FREETACOS_TASK
#define _FREETACOS_TASK

#include <process.hpp>

#include <apex_process.h>

#include <circle/sched/synchronizationevent.h>
#include <circle/sched/taskswitch.h>
#include <circle/sysconfig.h>
#include <circle/types.h>

#include <assert.h>

class Task : public Process {
public:
    Task(PROCESS_ATTRIBUTE_TYPE attributes);

    virtual ~Task(void);

    virtual void Run(void);

    virtual NAME_TYPE getIdentifier();

    void Terminate(void);
    void WaitForTermination(void);

    void InitializeRegs(void);
    TTaskRegisters* GetRegs(void);

    static void TaskEntry(void* pParam);

private:
    unsigned nStackSize;

    TTaskRegisters registers;
    u8* pStack;
};

#endif