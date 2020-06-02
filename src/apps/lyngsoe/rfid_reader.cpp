#include <circle/logger.h>
#include <circle/time.h>
#include <lyngsoe/rfid_reader.hpp>

std::vector<MESSAGE_ADDR_TYPE> RfidReaderTask::belt = {
    MESSAGE_ADDR_TYPE(new APEX_BYTE('a')), MESSAGE_ADDR_TYPE(new APEX_BYTE('b')),
    MESSAGE_ADDR_TYPE(new APEX_BYTE('c')), MESSAGE_ADDR_TYPE(new APEX_BYTE('d')),
    MESSAGE_ADDR_TYPE(new APEX_BYTE('e'))};

RfidReaderTask::RfidReaderTask()
    : Task(10, 10, 10, HARD, {"RfidReader"}, {"BlrSystem"})
{
}

void RfidReaderTask::Run(void)
{
    QUEUING_PORT_ID_TYPE id;
    RETURN_CODE_TYPE code;
    ApexQueuingPort::CREATE_QUEUING_PORT({"rfidRaw"}, 1, 100, SOURCE, FIFO, &id, &code);

    if (code == NO_ERROR) {
        qId = id;
    }
    else if (code == NOT_AVAILABLE) {
        CLogger::Get()->Write(*getProcessName().x, LogNotice, "Not Available");
    }
    else if (code == INVALID_PARAM) {
        CLogger::Get()->Write(*getProcessName().x, LogNotice, "Invalid Param");
    }

    while (1) {
        // Keep generating reads
        generateRfidRead();
    }

    return;
}

RfidReaderTask::~RfidReaderTask(void)
{
}

void RfidReaderTask::generateRfidRead()
{
    // Generate a read
    RETURN_CODE_TYPE code;
    for (auto& msg : belt) {
        CLogger::Get()->Write(*getProcessName().x, LogNotice, "Reading...");
        // Put read in Queuing Port
        ApexQueuingPort::SEND_QUEUING_MESSAGE(0, msg, 1, 100, &code);

        CTimer::Get()->MsDelay(500);
    }
}