#include "process_schedule.hpp"

ProcessSchedule::ProcessSchedule(NAME_TYPE partitionName)
    : partitionName(partitionName)
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
    unsigned int id = 0;

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