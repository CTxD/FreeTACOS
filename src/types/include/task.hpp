#ifndef _FREETACOS_TASK
#define _FREETACOS_TASK

#include <apex_process.h>
#include <circle/sched/synchronizationevent.h>
#include <circle/sched/taskswitch.h>
#include <circle/sysconfig.h>
#include <circle/types.h>
#include <process.hpp>

#include <assert.h>

class Task : Process {
public:
    Task(PROCESS_ATTRIBUTE_TYPE attributes) : Process(attributes)
    {
        nStackSize = TASK_STACK_SIZE;

        if (nStackSize != 0) {
            assert(nStackSize >= 1024);
            pStack = new u8[nStackSize];
            assert(pStack != 0);

            InitializeRegs();
        }
    }

    virtual ~Task(void);

    virtual void Run(void);

    void Terminate(void);
    void WaitForTermination(void);

    void InitializeRegs(void);
    TTaskRegisters* GetRegs(void);

    static void TaskEntry(void* pParam);

    PROCESS_STATE_TYPE& getState();

private:
    DEADLINE_TYPE deadlineType;

    unsigned nStackSize;

    TTaskRegisters registers;
    u8* pStack;
};

#endif