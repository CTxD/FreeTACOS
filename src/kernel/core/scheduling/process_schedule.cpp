#ifndef _PROCESS_SCHEDULE_
#define _PROCESS_SCHEDULE_

#include "process_schedule.hpp"
#include "generated_arinc_module.hpp"

ProcessSchedule::ProcessSchedule(name_t scheduleName)
    : scheduleName(scheduleName)
{
    // Instantiate empty queues
    blockedQueue = {};
    readyQueue = {};
}

void ProcessSchedule::iterate()
{
    // Get next process
    auto* nextProcess = getNextProcess();

    // If there is no processes in the ready queue
    if (nextProcess == nullptr)
        return;

    // Terminate running process or put to blocked list
    if (runningProcess->PROCESS_STATE == RUNNING || runningProcess->PROCESS_STATE == WAITING) {
        blockedQueue.push_back(runningProcess);
    }
    else {
        terminatedProcess = runningProcess;
    }

    // Put next process in running state
    runningProcess = nextProcess;

    // Run process
    nextProcess->PROCESS_STATE = PROCESS_STATE_TYPE::RUNNING;

    static_cast<Task*>(nextProcess->ATTRIBUTES.ENTRY_POINT)->Run();
}

/**
 * Get the next process with earliest deadline and highest priority
 * RETURN: nullptr || PROCESS_STATUS_TYPE*
 */
PROCESS_STATUS_TYPE* ProcessSchedule::getNextProcess()
{
    // If there is no processes in the schedule
    if (readyQueue.size() < 1)
        return nullptr;

    SYSTEM_TIME_TYPE deadline = INFINITE_TIME_VALUE; // High number (infinite)

    PROCESS_STATUS_TYPE* returnProcess = nullptr;

    // Initilise the deadline to the currently running process' deadline
    if (runningProcess != nullptr)
        deadline = runningProcess->DEADLINE_TIME;

    // Check for earlier deadlines
    for (unsigned int i = 0; i < readyQueue.size(); i++) {
        auto* readyProc = readyQueue[i];

        // If the process has an earlier deadline
        if (deadline > readyProc->DEADLINE_TIME) {
            // Update deadline
            deadline = readyProc->DEADLINE_TIME;

            // Update return process
            returnProcess = readyProc;
        }
    }

    // Pop process
    readyQueue.emplace_back(returnProcess);
    readyQueue.pop_back();

    // Return
    return returnProcess;
}

/**
 * Add a process to the initial ready queue
 */
void ProcessSchedule::addProcess(PROCESS_STATUS_TYPE* status)
{
    // Push to ready queue
    readyQueue.push_back(status);
}

/**
 * Check if there is a higher process with a higher deadline
 */
bool ProcessSchedule::checkIteration()
{
    // Check if we have any ready processes
    if (readyQueue.size() == 0)
        return false;

    SYSTEM_TIME_TYPE deadline = INFINITE_TIME_VALUE; // High number (infinite)

    // Initilise the deadline to the currently running process' deadline
    if (runningProcess != nullptr)
        deadline = runningProcess->DEADLINE_TIME;

    for (unsigned int i = 0; i < readyQueue.size(); i++) {
        auto* readyProc = readyQueue[i];

        // If the process has an earlier deadline
        if (deadline > readyProc->DEADLINE_TIME) {
            return true;
        }
        else if (deadline == readyProc->DEADLINE_TIME && runningProcess != nullptr) {
            // If deadlines are the same, check process priority
            return readyProc->CURRENT_PRIORITY >= runningProcess->CURRENT_PRIORITY;
        }
    }

    // Found one
    return false;
}

/**
 * Get the name of the processSchedule
 * RETURN: name_t
 */
name_t* ProcessSchedule::getProcessScheduleName()
{
    return &scheduleName;
}

/**
 * Is called through preemption, in order to check the next process
 */
void ProcessSchedule::interruptHandler()
{
    // Check if there is a higher priority process with earlier deadline
    auto isHigher = checkIteration();

    // FALSE -> continue
    if (!isHigher)
        return;

    // else iterate
    iterate();
}

// Initialise scheduleList and isInitialised
std::vector<ProcessSchedule*> ProcessSchedule::scheduleList[MAX_NUMBER_OF_PARTITIONS]{};
bool ProcessSchedule::isInitialised = false;

/**
 * Get a processSchedule by name
 * RETURN: ProcessSchedule* || nullptr
 */
ProcessSchedule* ProcessSchedule::getProcessScheduleByName(name_t& scheduleName)
{
    ProcessSchedule* returnSchedule = nullptr;

    for (int i = 0; i < scheduleList->size(); i++) {
        // Get this schedules name
        auto& name = *(scheduleList->at(i)->getProcessScheduleName()->x.x);

        // Check if this is what we are looking for
        if (strcmp(*scheduleName.x.x, name) == 0) {
            returnSchedule = scheduleList->at(i);
            break;
        }
    }

    return returnSchedule;
}

/**
 * Static function to initialise process schedules from XML file
 * USAGE: ProcessSchedule::initialiseSchedules(), fom anywhere.
 */
void ProcessSchedule::initialiseSchedules()
{
    // Check that we have not initialised schedules before
    assert(isInitialised == false &&
           "Schedules have already been initialised!");

    // Retrive all partitions from XML
    const std::vector<Partition> partitions = arincModule.getPartitions();

    // Create a processSchedule from each partition
    for (auto& partition : partitions) {
        // Add each processSchedule to list of processSchedules
        scheduleList->push_back(new ProcessSchedule(partition.getPartitionName()));
    }

    isInitialised = true; // All ok - everything was initialised
}

#endif