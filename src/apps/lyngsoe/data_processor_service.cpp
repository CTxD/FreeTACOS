#include <circle/logger.h>
#include <lyngsoe/data_processor_service.hpp>

DataProcessorServiceTask::DataProcessorServiceTask()
    : Task(10, 10, 10, HARD, {"DataProcessorService"}, {"DataProcessing"})
{
}

void DataProcessorServiceTask::Run(void)
{
    RETURN_CODE_TYPE code, code1;
    ApexQueuingPort::CREATE_QUEUING_PORT({"rfidRaw"}, 1, 100, DESTINATION, FIFO,
                                         &qIdRaw, &code);

    ApexQueuingPort::CREATE_QUEUING_PORT({"rfidProcd"}, 1, 100, SOURCE, FIFO,
                                         &qIdRaw, &code);

    if (code == NO_ERROR) {
    }
    else {
        CLogger::Get()->Write(*getProcessName().x, LogNotice, "Error");
    }

    while (1) {
        handleIncomming();

        CTimer::Get()->MsDelay(200);
    }
    return;
}

DataProcessorServiceTask::~DataProcessorServiceTask(void)
{
}

void DataProcessorServiceTask::handleIncomming()

{
    MESSAGE_ADDR_TYPE msg;
    MESSAGE_SIZE_TYPE length;
    RETURN_CODE_TYPE code;

    ApexQueuingPort::RECEIVE_QUEUING_MESSAGE(0, 100, &msg, &length, &code);

    if (code == NO_ERROR) {
        CLogger::Get()->Write(*getProcessName().x, LogNotice,
                              "-----------------MSG: %c------------", *msg);
        processData(msg);
    }
    else {
        CLogger::Get()->Write(*getProcessName().x, LogNotice,
                              "-----------------EMPTY!");
    }
}
void DataProcessorServiceTask::processData(MESSAGE_ADDR_TYPE msg)
{
    if (*msg == 'a' || *msg == 'c' || *msg == 'd') {
        queueData(true);
    }
    else {
        queueData(false);
    }
}

void DataProcessorServiceTask::queueData(bool status)
{
    RETURN_CODE_TYPE code;
    if (status) {
        ApexQueuingPort::SEND_QUEUING_MESSAGE(
            1, MESSAGE_ADDR_TYPE(new APEX_BYTE('1')), 1, 100, &code);
    }
    else {
        ApexQueuingPort::SEND_QUEUING_MESSAGE(
            1, MESSAGE_ADDR_TYPE(new APEX_BYTE('0')), 1, 100, &code);
    }
}