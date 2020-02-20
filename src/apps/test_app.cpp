#include <test_app.h>

TestApp::TestApp(CLogger* logger)
    : Task({10, 10, this, 0x8000, 10, DEADLINE_TYPE::HARD, {"Test Application"}})
{
    this->logger = logger;
}

void TestApp::Run(void)
{
    logger->Write(*getIdentifier().x, LogNotice, "Running Once.");

    auto* regs = GetRegs();

    logger->Write(*getIdentifier().x, LogNotice, "Register x30: %d", regs->x30);
    logger->Write(*getIdentifier().x, LogNotice, "State: %d", 1.2);
}

TestApp::~TestApp(void)
{
}