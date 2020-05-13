#include <assert.h>
#include <cstring>
#include <process.hpp>
#include <task.hpp>

/**
 * Init task with only attributes
 */
Task::Task(PROCESS_ATTRIBUTE_TYPE& attributes, name_t partitionNameRef)
    : Process(attributes), partitionNameRef(partitionNameRef)
{
}

/**
 * More simple constructer
 * Automatically set atts and status from few values
 */
Task::Task(SYSTEM_TIME_TYPE period,
           SYSTEM_TIME_TYPE timeCapacity,
           PRIORITY_TYPE priority,
           DEADLINE_TYPE deadline,
           PROCESS_NAME_TYPE name,
           name_t partitionNameRef)
    : partitionNameRef(partitionNameRef)
{
    PROCESS_ATTRIBUTE_TYPE atts = PROCESS_ATTRIBUTE_TYPE{
        period, timeCapacity, this, TASK_STACK_SIZE, priority, deadline, name};

    PROCESS_STATUS_TYPE status = PROCESS_STATUS_TYPE{deadline, priority, DORMANT, atts};

    u64* pStack = (u64*)malloc((((size_t)stackDepth) * sizeof(u64)));
    u64* pTopOfStack = &(pStack[stackDepth - 1]);
    this->pStack = pStack;
    this->pTopOfStack = pTopOfStack;
    InitStack();
    setStatus(status);
}

void Task::InitStack()
{
    this->pTopOfStack--;
    *(this->pTopOfStack) = (u64)0x30303030ULL; /* R30 - procedure call link register. */
    this->pTopOfStack--;
    *(this->pTopOfStack) = (u64)0x2929292929292929ULL; /* R29 */
    this->pTopOfStack--;

    *(this->pTopOfStack) = (u64)(0x20000304); // SPSR_EL   30
    this->pTopOfStack--;
    *(this->pTopOfStack) = (u64)(&TaskEntry); /// ELR_EL    31
    this->pTopOfStack--;

    *(this->pTopOfStack) = 0x0101010101010101ULL; /* R1 */
    this->pTopOfStack--;
    *(this->pTopOfStack) = (u64)(this); /* R0 */
    this->pTopOfStack--;
    *(this->pTopOfStack) = 0x0303030303030303ULL; /* R3 */
    this->pTopOfStack--;
    *(this->pTopOfStack) = 0x0202020202020202ULL; /* R2 */
    this->pTopOfStack--;
    *(this->pTopOfStack) = 0x0505050505050505ULL; /* R5 */
    this->pTopOfStack--;
    *(this->pTopOfStack) = 0x0404040404040404ULL; /* R4 */
    this->pTopOfStack--;
    *(this->pTopOfStack) = 0x0707070707070707ULL; /* R7 */
    this->pTopOfStack--;
    *(this->pTopOfStack) = 0x0606060606060606ULL; /* R6 */
    this->pTopOfStack--;
    *(this->pTopOfStack) = 0x0909090909090909ULL; /* R9 */
    this->pTopOfStack--;
    *(this->pTopOfStack) = 0x0808080808080808ULL; /* R8 */
    this->pTopOfStack--;
    *(this->pTopOfStack) = 0x1111111111111111ULL; /* R11 */
    this->pTopOfStack--;
    *(this->pTopOfStack) = 0x1010101010101010ULL; /* R10 */
    this->pTopOfStack--;
    *(this->pTopOfStack) = 0x1313131313131313ULL; /* R13 */
    this->pTopOfStack--;
    *(this->pTopOfStack) = 0x1212121212121212ULL; /* R12 */
    this->pTopOfStack--;
    *(this->pTopOfStack) = 0x1515151515151515ULL; /* R15 */
    this->pTopOfStack--;
    *(this->pTopOfStack) = 0x1414141414141414ULL; /* R14 */
    this->pTopOfStack--;
    *(this->pTopOfStack) = 0x1717171717171717ULL; /* R17 */
    this->pTopOfStack--;
    *(this->pTopOfStack) = 0x1616161616161616ULL; /* R16 */
    this->pTopOfStack--;
    *(this->pTopOfStack) = 0x1919191919191919ULL; /* R19 */
    this->pTopOfStack--;
    *(this->pTopOfStack) = 0x1818181818181818ULL; /* R18 */
    this->pTopOfStack--;
    *(this->pTopOfStack) = 0x2121212121212121ULL; /* R21 */
    this->pTopOfStack--;
    *(this->pTopOfStack) = 0x2020202020202020ULL; /* R20 */
    this->pTopOfStack--;
    *(this->pTopOfStack) = 0x2323232323232323ULL; /* R23 */
    this->pTopOfStack--;
    *(this->pTopOfStack) = 0x2222222222222222ULL; /* R22 */
    this->pTopOfStack--;
    *(this->pTopOfStack) = 0x2525252525252525ULL; /* R25 */
    this->pTopOfStack--;
    *(this->pTopOfStack) = 0x2424242424242424ULL; /* R24 */
    this->pTopOfStack--;
    *(this->pTopOfStack) = 0x2727272727272727ULL; /* R27 */
    this->pTopOfStack--;
    *(this->pTopOfStack) = 0x2626262626262626ULL; /* R26 */
    this->pTopOfStack--;
    *(this->pTopOfStack) = 0x2828282828282828ULL; /* R28 */
    this->pTopOfStack--;
    *(this->pTopOfStack) = 0x0; /* XZR */
}

/**
 * Init a Task with whole custom status
 */
Task::Task(PROCESS_STATUS_TYPE& status) : Process(status)
{
}

Task::~Task(void)
{
    // Deconstructing Task
}

name_t& Task::getPartitionNameRef()
{
    return partitionNameRef;
}

void Task::Run(void)
{
    // Base case Task::Run function
}

// Same approach as CTask
void Task::TaskEntry(void* pParam)
{
    Task* pThis = (Task*)pParam;
    assert(pThis != 0);

    pThis->Run();
}
