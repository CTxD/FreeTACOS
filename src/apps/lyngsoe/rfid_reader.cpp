#include <circle/logger.h>
#include <circle/time.h>
#include <lyngsoe/rfid_reader.hpp>

RfidReaderTask::RfidReaderTask()
    : Task(10, 10, 10, HARD, {"RfidReader"}, {"BlrSystem"})
{
}

void RfidReaderTask::Run(void)
{
    CLogger::Get()->Write(*getProcessName().x, LogNotice, "Initialised");
    while (1) {
        // Keep generating reads
        generateRfidRead();

        // Delay the time by 1,5 sec
        CTimer::Get()->MsDelay(1500);
    }

    return;
}

RfidReaderTask::~RfidReaderTask(void)
{
}

void RfidReaderTask::generateRfidRead()
{
    // Generate a read
    CLogger::Get()->Write(*getProcessName().x, LogNotice, "Reading...");

    // Put read in Queuing Port
}