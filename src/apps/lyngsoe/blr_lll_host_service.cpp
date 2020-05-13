#include <circle/logger.h>
#include <lyngsoe/blr_lll_host_service.hpp>

BlrLllHostServiceTask::BlrLllHostServiceTask()
    : Task(10, 10, 10, HARD, {"BlrLllHostService"}, {"IOProcessing"})
{
}

void BlrLllHostServiceTask::Run(void)
{
    CLogger::Get()->Write(*getProcessName().x, LogNotice, "Initialised");

    while (1) {
    }
    return;
}

BlrLllHostServiceTask::~BlrLllHostServiceTask(void)
{
}