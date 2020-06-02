#include <apex_buffer.hpp>
#include <apex_queuing_port.hpp>
#include <circle/logger.h>
#include <circle/timer.h>
#include <lyngsoe/blr_lll_host_service.hpp>

BlrLllHostServiceTask::BlrLllHostServiceTask()
    : Task(10, 10, 10, HARD, {"BlrLllHostService"}, {"BlrSystem"})
{
}

void BlrLllHostServiceTask::Run(void)
{
    BUFFER_ID_TYPE id;
    RETURN_CODE_TYPE code;

    ApexBuffer::CREATE_BUFFER({"TestBuffer"}, 255, 10, FIFO, &id, &code);

    if (code == NO_ERROR) {
        ApexQueuingPort::CREATE_QUEUING_PORT({"rfidProcd"}, 1, 100, DESTINATION,
                                             FIFO, &id, &code);
    }
    else {
        CLogger::Get()->Write("Tester", LogNotice, "Error creating buffer");
    }

    while (1) {
        handleMessage();

        CTimer::Get()->MsDelay(500);
    }
    return;
}

BlrLllHostServiceTask::~BlrLllHostServiceTask(void)
{
}

MESSAGE_ADDR_TYPE BlrLllHostServiceTask::fetchMessage()
{
    // Get message from queuing port - after processed by data processor
    MESSAGE_ADDR_TYPE addr;
    MESSAGE_SIZE_TYPE size;
    RETURN_CODE_TYPE code;

    ApexQueuingPort::RECEIVE_QUEUING_MESSAGE(1, 100, &addr, &size, &code);

    if (code == NO_ERROR) {
        return addr;
    }
    else {
        return NULL;
    }
}

void BlrLllHostServiceTask::handleMessage()
{
    auto msg = fetchMessage();
    bool status = false;

    // Check message API Call
    if (msg == NULL) {
        return;
    }

    CLogger::Get()->Write(*getProcessName().x, LogNotice,
                          "Handling Messages...");

    RETURN_CODE_TYPE code;

    // Send message based on status
    status == true
        ? ApexBuffer::SEND_BUFFER(0, msg, sizeof(msg) / sizeof(MESSAGE_ADDR_TYPE), 100, &code)
        : ApexBuffer::SEND_BUFFER(
              0, msg, sizeof(errorMsg) / sizeof(MESSAGE_ADDR_TYPE), 100, &code);
}