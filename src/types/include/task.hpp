#ifndef _FREETACOS_TASK
#define _FREETACOS_TASK

#include <process.hpp>

#include <circle/sched/synchronizationevent.h>
#include <circle/sched/taskswitch.h>
#include <circle/sysconfig.h>
#include <circle/types.h>

#include <assert.h>

class Task : public Process {
public:
    volatile u64* pTopOfStack;
    u64* pStack;

    Task(PROCESS_ATTRIBUTE_TYPE& attributes, name_t partitionNameRef);
    Task(SYSTEM_TIME_TYPE period,
         SYSTEM_TIME_TYPE timeCapacity,
         PRIORITY_TYPE priority,
         DEADLINE_TYPE deadline,
         PROCESS_NAME_TYPE name,
         name_t partitionNameRef);
    Task(PROCESS_STATUS_TYPE& status);
    virtual ~Task(void);

    virtual void Run(void);

    name_t& getPartitionNameRef();

    void Terminate(void);
    void WaitForTermination(void);

    static void TaskEntry(void* pParam);

private:
    unsigned nStackSize;

    void initRegs();

    name_t partitionNameRef;
};

#endif