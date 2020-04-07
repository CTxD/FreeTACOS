#ifndef _FREETACOS_TEST_APP
#define _FREETACOS_TEST_APP

#include <task.hpp>

#include <circle/logger.h>

#include <apex_process.hpp>

class TestApp : public Task {
public:
    TestApp(CLogger* logger, name_t partitionRef);
    ~TestApp(void);

    void Run(void);

private:
    CLogger* logger;
};

#endif