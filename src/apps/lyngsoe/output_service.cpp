#include <circle/logger.h>
#include <lyngsoe/output_service.hpp>

OutputServiceTask::OutputServiceTask()
    : Task(10, 10, 10, HARD, {"OutputService"}, {"IOProcessing"})
{
}

void OutputServiceTask::Run(void)
{
    CLogger::Get()->Write(*getProcessName().x, LogNotice, "Initialised");

    while (1) {
    }
    return;
}

OutputServiceTask::~OutputServiceTask(void)
{
}