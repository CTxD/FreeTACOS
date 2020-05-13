#include <circle/logger.h>
#include <lyngsoe/data_processor_service.hpp>

DataProcessorServiceTask::DataProcessorServiceTask()
    : Task(10, 10, 10, HARD, {"DataProcessorService"}, {"IOProcessing"})
{
}

void DataProcessorServiceTask::Run(void)
{
    CLogger::Get()->Write(*getProcessName().x, LogNotice, "Initialised");

    while (1) {
    }
    return;
}

DataProcessorServiceTask::~DataProcessorServiceTask(void)
{
}