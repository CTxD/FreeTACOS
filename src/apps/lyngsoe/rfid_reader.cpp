#include <circle/logger.h>
#include <circle/time.h>
#include <lyngsoe/rfid_reader.hpp>

RfidReaderTask::RfidReaderTask()
    : Task(10, 10, 10, HARD, {"RfidReader"}, {"IOProcessing"})
{
}

void RfidReaderTask::Run(void)
{
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

    // Put read in Buffer
}