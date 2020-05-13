#include <circle/logger.h>
#include <lyngsoe/gps_service.hpp>

GpsServiceTask::GpsServiceTask()
    : Task(10, 10, 10, HARD, {"GpsService"}, {"IOProcessing"})
{
}

void GpsServiceTask::Run(void)
{
    CLogger::Get()->Write(*getProcessName().x, LogNotice, "Initialised");

    while (1) {
    }
    return;
}

GpsServiceTask::~GpsServiceTask(void)
{
}