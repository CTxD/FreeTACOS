#include <apex_kernel.hpp>
#include <test_app.h>

TestApp::TestApp(CLogger* logger)
    : Task({10, 10, this, 0x8000, 10, DEADLINE_TYPE::HARD, {"Test Application {MASTER}"}})
{
    this->logger = logger;
}

void TestApp::Run(void)
{
    auto* regs = GetRegs();

    logger->Write(*getIdentifier().x, LogNotice, "Register x30: %d", regs->x30);

    logger->Write(*getIdentifier().x, LogNotice, "Spawning new Process...");
    RETURN_CODE_TYPE* returnCode;
    PROCESS_ID_TYPE* id;

    PROCESS_ATTRIBUTE_TYPE* newProcess = new PROCESS_ATTRIBUTE_TYPE{
        10, 10, new TestApp(logger), 0x8000, 10, DEADLINE_TYPE::HARD, {"Test Application {SLAVE}"}};

    CREATE_PROCESS(newProcess, id, returnCode);
    addToProcessList(static_cast<Task*>(newProcess->ENTRY_POINT));

    if (*returnCode == RETURN_CODE_TYPE::NO_ERROR) {
        logger->Write(*getIdentifier().x, LogNotice,
                      "Process Spawned with RC: %i and id: %i", returnCode, id);
    }
    else {
        logger->Write(*getIdentifier().x, LogNotice, "Error creating process");
    }

    logger->Write(*getIdentifier().x, LogNotice, "ID TEST: %i", id);
}

TestApp::~TestApp(void)
{
}