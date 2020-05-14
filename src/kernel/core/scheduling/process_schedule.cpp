#ifndef _PROCESS_SCHEDULE_
#define _PROCESS_SCHEDULE_

#include "process_schedule.hpp"
#include <arinc_module.hpp>
#include <circle/logger.h>
#include <circle/timer.h>

#include <algorithm>

ProcessSchedule::ProcessSchedule(name_t scheduleName)
    : scheduleName(scheduleName)
{
    // Instantiate empty queues
    blockedQueue = {};
    readyQueue = {};
    runningProcess = nullptr;
}

/**
 * DESCRIPTION: Initial function for starting the scheduler
 */
void ProcessSchedule::startScheduler()
{
    // Just return if there is no processes in the partition
    if (readyQueue.size() == 0 && blockedQueue.size() == 0)
        return;

    auto timeStamp = CTimer::Get()->GetClockTicks();

    // Reset all periods
    for (auto& processInfo : readyQueue) {
        processInfo->period = processInfo->process->ATTRIBUTES.PERIOD + timeStamp;
    }

    for (auto& processInfo : blockedQueue) {
        processInfo->period = processInfo->process->ATTRIBUTES.PERIOD + timeStamp;
    }

    // Iterate
    iterate();
}

/**
 * DESCRIPTION: Keeps iterating the ready queue.
 */
void ProcessSchedule::iterate()
{
    // TODO: Remove this when preemption works. That should solve this problem.
    if (CyclicExecutiveSchedule::getCurrentPartition()->endTime <= CTimer::GetClockTicks()) {
        return;
    }

    runNextProcess();

    reReadyProcesses();

    CTimer::Get()->MsDelay(1 * HZ); // Delay for 1 hz time
    iterate();
}

/**
 * DESCRIPTION: Finds the next process and runs it, if there is another process
 * in the ready queue
 */
void ProcessSchedule::runNextProcess()
{
    // Get next process
    PROCESS_ID_TYPE procId;
    auto* nextProcess = getNextProcess(procId);

    // If there is a processes in the ready queue
    if (nextProcess != nullptr) {
        // Put next process in running state
        runningProcess = nextProcess;
        runningProcess->process->PROCESS_STATE = PROCESS_STATE_TYPE::RUNNING;

        // Run process
        runningProcess->startTime = CTimer::GetClockTicks();
        static_cast<Task*>(nextProcess->process->ATTRIBUTES.ENTRY_POINT)->Run();
        runningProcess->endTime = CTimer::GetClockTicks();

        // If process has become dormant -> terminate it
        if (runningProcess->process->PROCESS_STATE == DORMANT) {
            terminatedProcess = runningProcess;
        }
        else {
            // Update
            runningProcess->period += runningProcess->process->ATTRIBUTES.PERIOD;

            // Make process wait and put in blocked queue
            runningProcess->process->PROCESS_STATE = WAITING;
            blockedQueue.push_back(runningProcess);
        }

        // Pop process
        readyQueue.erase(readyQueue.begin() + procId);
    }
}

/**
 * DESCRIPTION: Check the blocked queue for processes, that has exceeded their
 * period, re-ready them by populating the readyQueue again
 */
void ProcessSchedule::reReadyProcesses()
{
    // Check if there is any blocked processes
    if (blockedQueue.size() < 1)
        return;

    // Get current running partition
    auto* currentPartition = CyclicExecutiveSchedule::getCurrentPartition();

    // Retrieve current clock ticks
    auto currentTime = abs((long double)CTimer::Get()->GetClockTicks());

    // Get cycle time
    auto deltaTime = currentTime;

    // Check if time has exceeded periods
    for (unsigned long int i = 0; i < blockedQueue.size(); i++) {
        auto& processInfo = blockedQueue.at(i);

        auto& period = processInfo->period;
        // CLogger::Get()->Write("DEBUGGER", LogNotice, "DT: %i >= p: %i",
        // deltaTime, period);
        if (deltaTime >= period) {
            processInfo->startTime = 0;
            processInfo->endTime = 0;

            readyQueue.push_back(processInfo);

            blockedQueue.erase(blockedQueue.begin() + i);
        }
    }
}

/**
 * DESCRIPTION: Get the next process with earliest deadline and highest priority
 * RETURN: nullptr || PROCESS_STATUS_TYPE*
 */
ProcessScheduleInfo* ProcessSchedule::getNextProcess(PROCESS_ID_TYPE& procId)
{
    // If there is no processes in the schedule
    if (readyQueue.size() < 1) {
        return nullptr;
    }

    procId = 0;
    ProcessScheduleInfo* returnProcess = readyQueue.at(procId);
    SYSTEM_TIME_TYPE deadline =
        returnProcess->period - CTimer::Get()->GetClockTicks(); // Get time left

    // Check for earlier deadlines
    for (unsigned int i = 0; i < readyQueue.size(); i++) {
        auto* readyProc = readyQueue.at(i);
        SYSTEM_TIME_TYPE rDeadline = readyProc->period - CTimer::Get()->GetClockTicks();

        // If the process has an earlier deadline
        if (deadline > rDeadline) {
            // Update deadline
            deadline = rDeadline;

            // Update return process
            returnProcess = readyProc;
            procId = i;
        }
    }

    // Return
    return returnProcess;
}

/**
 * DESCRIPTION: Add a process to the initial ready queue
 */
void ProcessSchedule::addProcess(PROCESS_STATUS_TYPE* status)
{
    // Push to ready queue
    readyQueue.push_back(new ProcessScheduleInfo{status->ATTRIBUTES.PERIOD, 0, 0, status});
}

/**
 * Get the name of the processSchedule
 * RETURN: name_t
 */
name_t* ProcessSchedule::getProcessScheduleName()
{
    return &scheduleName;
}

// Initialise scheduleList and isInitialised
std::vector<ProcessSchedule*> ProcessSchedule::scheduleList[MAX_NUMBER_OF_PARTITIONS]{};
bool ProcessSchedule::isInitialised = false;

/**
 * DESCRIPTION: Get a processSchedule by name
 * USAGE: Call with a name_t to get any process schedule by their name
 * RETURN: ProcessSchedule* || nullptr
 */
ProcessSchedule* ProcessSchedule::getProcessScheduleByName(name_t& scheduleName)
{
    ProcessSchedule* returnSchedule = nullptr;

    for (long unsigned int i = 0; i < scheduleList->size(); i++) {
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
 * DESCRIPTION: Static function to initialise process schedules from XML file
 * USAGE: ProcessSchedule::initialiseSchedules(), fom anywhere.
 */
void ProcessSchedule::initialiseSchedules()
{
    // Check that we have not initialised schedules before
    assert(isInitialised == false &&
           "Schedules have already been initialised!");

    // Retrive all partitions from XML
    const std::vector<Partition> partitions = ArincModule::generatedArincModule.partitions;

    // Create a processSchedule from each partition
    for (auto& partition : partitions) {
        // Add each processSchedule to list of processSchedules
        scheduleList->push_back(new ProcessSchedule(partition.getPartitionName()));
    }

    isInitialised = true; // All ok - everything was initialised
}

ProcessScheduleInfo* ProcessSchedule::getCurrentProcess(){
    return ProcessSchedule::runningProcess;
}

std::vector<ProcessScheduleInfo*> ProcessSchedule::getReadyQueue(){
    return readyQueue;
}

std::vector<ProcessScheduleInfo*> ProcessSchedule::getBlockedQueue(){
    return blockedQueue;
}

#endif