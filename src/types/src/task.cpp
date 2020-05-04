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

    setStatus(status);
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
