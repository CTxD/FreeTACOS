#include <apex_kernel.hpp>
#include <test_app.hpp>

TestApp::TestApp(CLogger* logger, name_t partitionRef)
    : Task(10, 10, 10, HARD, {"TestApp"}, partitionRef), logger(logger)
{
}

void TestApp::Run(void)
{
    logger->Write(*getProcessName().x, LogNotice,
                  "Test program, just logging stuff..");
}

TestApp::~TestApp(void)
{
}