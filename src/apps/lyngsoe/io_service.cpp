#include <circle/logger.h>
#include <lyngsoe/io_service.hpp>

IoServiceTask::IoServiceTask()
    : Task(10, 10, 10, HARD, {"IoService"}, {"IOProcessing"})
{
}

void IoServiceTask::Run(void)
{
    CLogger::Get()->Write(*getProcessName().x, LogNotice, "Initialised");

    while (1) {
    }
    return;
}

IoServiceTask::~IoServiceTask(void)
{
}