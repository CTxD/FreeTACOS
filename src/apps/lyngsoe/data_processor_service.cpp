#include <circle/logger.h>
#include <lyngsoe/data_processor_service.hpp>

DataProcessorServiceTask::DataProcessorServiceTask()
    : Task(10, 10, 10, HARD, {"DataProcessorService"}, {"DataProcessing"})
{
}

void DataProcessorServiceTask::Run(void)
{
    CLogger::Get()->Write(*getProcessName().x, LogNotice, "Initialised");

    while (1) {
        CLogger::Get()->Write(*getProcessName().x, LogNotice, "Initialised");
    }
    return;
}

DataProcessorServiceTask::~DataProcessorServiceTask(void)
{
}

void DataProcessorServiceTask::handleIncomming()
{
}
void DataProcessorServiceTask::processData()
{
}

void DataProcessorServiceTask::queueData()
{
}