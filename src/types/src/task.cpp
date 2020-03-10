#include <assert.h>
#include <cstring>
#include <process.hpp>
#include <task.hpp>

/**
 * Init task with only attributes
 */
Task::Task(PROCESS_ATTRIBUTE_TYPE& attributes) : Process(attributes)
{
    nStackSize = TASK_STACK_SIZE;

    if (nStackSize != 0) {
        assert(nStackSize >= 1024);
        pStack = new u8[nStackSize];
        assert(pStack != 0);

        InitializeRegs();
    }
}

/**
 * More simple constructer
 * Automatically set atts and status from few values
 */
Task::Task(SYSTEM_TIME_TYPE period,
           SYSTEM_TIME_TYPE timeCapacity,
           PRIORITY_TYPE priority,
           DEADLINE_TYPE deadline,
           PROCESS_NAME_TYPE name)
{
    PROCESS_ATTRIBUTE_TYPE atts = PROCESS_ATTRIBUTE_TYPE{
        period, timeCapacity, this, TASK_STACK_SIZE, priority, deadline, name};

    PROCESS_STATUS_TYPE status = PROCESS_STATUS_TYPE{deadline, priority, DORMANT, atts};

    setStatus(status);

    initRegs();
}

/**
 * Init a Task with whole custom status
 */
Task::Task(PROCESS_STATUS_TYPE& status) : Process(status)
{
    initRegs();
}

Task::~Task(void)
{
    // Deconstructing Task
}

void Task::initRegs()
{
    nStackSize = TASK_STACK_SIZE;

    if (nStackSize != 0) {
        assert(nStackSize >= 1024);
        pStack = new u8[nStackSize];
        assert(pStack != 0);

        InitializeRegs();
    }
}

void Task::Run(void)
{
    // Base case Task::Run function
}

TTaskRegisters* Task::GetRegs(void)
{
    return &registers;
}

// Same approach as CTasks
void Task::InitializeRegs(void)
{
    memset(&registers, 0, sizeof registers);

    registers.x0 = (u64)this; // pParam for TaskEntry()

    assert(pStack != 0);
    registers.sp = (u64)pStack + nStackSize;

    registers.x30 = (u64)&TaskEntry;

    u32 nFPCR;
    asm volatile("mrs %0, fpcr" : "=r"(nFPCR));
    registers.fpcr = nFPCR;
}

// Same approach as CTask
void Task::TaskEntry(void* pParam)
{
    Task* pThis = (Task*)pParam;
    assert(pThis != 0);

    pThis->Run();
}
