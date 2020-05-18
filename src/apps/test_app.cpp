#include <apex_kernel.hpp>
#include <test_app.hpp>

TestApp::TestApp(CLogger* logger, name_t partitionRef)
    : Task(10, 10, 10, HARD, {"TestApp"}, partitionRef), logger(logger)
{
}

void TestApp::Run(void)
{
    int i = 1;
    while (1) {
        logger->Write(*getProcessName().x, LogNotice,
                      "Test program ... "
                      "Iteration - %d (Seconds run)",
                      i++);
        CTimer::Get()->MsDelay(1000);
    }
    return;
}

TestApp::~TestApp(void)
{
}