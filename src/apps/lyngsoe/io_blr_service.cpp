#include <circle/logger.h>
#include <lyngsoe/io_blr_service.hpp>

Io2BlrServiceTask::Io2BlrServiceTask()
    : Task(10, 10, 10, HARD, {"Io2BlrService"}, {"IOProcessing"})
{
}

void Io2BlrServiceTask::Run(void)
{
    CLogger::Get()->Write(*getProcessName().x, LogNotice, "Initialised");

    while (1) {
    }
    return;
}

Io2BlrServiceTask::~Io2BlrServiceTask(void)
{
}