#include <circle/sched/synchronizationevent.h>
#include <circle/sched/taskswitch.h>
#include <circle/sysconfig.h>
#include <circle/types.h>

#include <apex_process.h>

#include <process.hpp>

class Task : Process {
public:
    Task(name_t name, decOrHex_t identifier, decOrHex_t priority, decOrHex_t period, unsigned nStackSize = TASK_STACK_SIZE)
        : Process(name, identifier, priority, period);

    virtual ~Task(void);

    virtual void Run(void);

    void Terminate(void);
    void WaitForTermination(void);

    void SetUserData(void* pData);
    void* GetUserData(void);

private:
};