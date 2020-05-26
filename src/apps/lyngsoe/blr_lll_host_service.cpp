#include <apex_buffer.hpp>
#include <circle/logger.h>
#include <circle/timer.h>
#include <lyngsoe/blr_lll_host_service.hpp>

BlrLllHostServiceTask::BlrLllHostServiceTask()
    : Task(10, 10, 10, HARD, {"BlrLllHostService"}, {"BlrSystem"})
{
}

void BlrLllHostServiceTask::Run(void)
{
    CLogger::Get()->Write(*getProcessName().x, LogNotice, "Initialised");

    while (1) {
        CLogger::Get()->Write(*getProcessName().x, LogNotice, "Initialised");
        handleMessage();

        CTimer::Get()->MsDelay(1500);
    }
    return;
}

BlrLllHostServiceTask::~BlrLllHostServiceTask(void)
{
}

MESSAGE_ADDR_TYPE BlrLllHostServiceTask::fetchMessage()
{
    // Get message from queuing port - after processed by data processor
    MESSAGE_ADDR_TYPE addr = MESSAGE_ADDR_TYPE(new APEX_BYTE('testmsg'));

    return addr;
}

void BlrLllHostServiceTask::handleMessage()
{
    auto msg = fetchMessage();
    bool status = false;

    // Check message API Call
    if (msg != NULL) {
        // Emulate api delay
        CTimer::Get()->MsDelay(100);

        status = true;
    }

    RETURN_CODE_TYPE code;

    // Send message based on status
    status == true
        ? ApexBuffer::SEND_BUFFER(0, msg, sizeof(msg) / sizeof(MESSAGE_ADDR_TYPE), 100, &code)
        : ApexBuffer::SEND_BUFFER(
              0, msg, sizeof(errorMsg) / sizeof(MESSAGE_ADDR_TYPE), 100, &code);
}