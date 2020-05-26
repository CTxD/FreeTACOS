#include <circle/logger.h>
#include <lyngsoe/io_blr_service.hpp>

Io2BlrServiceTask::Io2BlrServiceTask()
    : Task(10, 10, 10, HARD, {"Io2BlrService"}, {"BlrSystem"})
{
}

void Io2BlrServiceTask::Run(void)
{
    CLogger::Get()->Write(*getProcessName().x, LogNotice, "Initialised");

    // Continously check for processed data
    while (1) {
        CLogger::Get()->Write(*getProcessName().x, LogNotice, "Initialised");
        // Check buffer for messages
        auto msg = checkBuffer();

        if (msg != NULL) {
            auto status = handleMessage(msg);

            ioResponse(status);
        }

        // Delay by 1.5 seconds.
        CTimer::Get()->MsDelay(1500);
    }

    return;
}

Io2BlrServiceTask::~Io2BlrServiceTask(void)
{
}

MESSAGE_ADDR_TYPE Io2BlrServiceTask::checkBuffer()
{
    MESSAGE_ADDR_TYPE msg;
    RETURN_CODE_TYPE code;
    MESSAGE_SIZE_TYPE size;
    ApexBuffer::RECEIVE_BUFFER(0, 100, &msg, &size, &code);

    // Check if there is a message in the buffer
    if (code == NO_ERROR) {
        handleMessage(msg);
    }

    // Else do nothing
}

bool Io2BlrServiceTask::handleMessage(MESSAGE_ADDR_TYPE msg)
{
    // Success Message
    if (msg == MESSAGE_ADDR_TYPE(new APEX_BYTE('testmsg'))) {
        ioResponse(true);
    }
    else {
        // Error Message
        ioResponse(false);
    }
}

void Io2BlrServiceTask::ioResponse(bool status)
{
    status ? CLogger::Get()->Write("BLR IO", LogNotice, "Success")
           : CLogger::Get()->Write("BLR IO", LogWarning, "Error");
}
