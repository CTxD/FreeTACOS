#include <circle/logger.h>
#include <lyngsoe/rfid_reader.hpp>

RfidReaderTask::RfidReaderTask()
    : Task(10, 10, 10, HARD, {"RfidReader"}, {"IOProcessing"})
{
}

void RfidReaderTask::Run(void)
{
    CLogger::Get()->Write(*getProcessName().x, LogNotice, "Initialised");

    while (1) {
    }
    return;
}

RfidReaderTask::~RfidReaderTask(void)
{
}