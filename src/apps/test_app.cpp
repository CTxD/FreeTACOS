#include <apex_kernel.hpp>
#include <test_app.h>

TestApp::TestApp(CLogger* logger) : Task(10, 10, 10, HARD, {"MASTER"})
{
    this->logger = logger;
}

void TestApp::Run(void)
{
    auto processName = getProcessName().x;

    logger->Write(*processName, LogNotice, "TESTING APEX");
    PROCESS_ID_TYPE myId;
    RETURN_CODE_TYPE idReturn;

    GET_MY_ID(&myId, &idReturn);

    PROCESS_STATUS_TYPE myStatus;
    RETURN_CODE_TYPE statusReturn;

    GET_PROCESS_STATUS(myId, &myStatus, &statusReturn);

    if (statusReturn != NO_ERROR) {
        logger->Write("APEX", LogPanic,
                      "PROCESS_STATUS: Something went wrong! ReturnCode is %i", statusReturn);
    }
    else {
        logger->Write("APEX", LogNotice, "Process Name: %s",
                      *myStatus.ATTRIBUTES.NAME.x);
    }

    if (idReturn != NO_ERROR) {
        logger->Write("APEX", LogPanic,
                      "Process ID: Something went wrong! ReturnCode is %i", idReturn);
    }
    else {
        logger->Write("APEX", LogNotice, "Process ID: %i -- TaskID is %i", myId,
                      static_cast<Task*>(myStatus.ATTRIBUTES.ENTRY_POINT)->getId());
    }

    logger->Write("APEX", LogNotice, "Spawning new Process...");
    RETURN_CODE_TYPE returnCode;
    PROCESS_ID_TYPE id;

    PROCESS_ATTRIBUTE_TYPE newProcess = PROCESS_ATTRIBUTE_TYPE{
        10, 10, new TestApp(logger), 0x8000, 10, HARD, {"SLAVE"}};

    CREATE_PROCESS(&newProcess, &id, &returnCode);

    if (returnCode == RETURN_CODE_TYPE::NO_ERROR) {
        logger->Write(*processName, LogNotice,
                      "Process %s Spawned with RC: %i and id: %i",
                      *newProcess.NAME.x, returnCode, id);
    }
    else {
        logger->Write(*processName, LogPanic, "Error creating process");
    }
}

TestApp::~TestApp(void)
{
}