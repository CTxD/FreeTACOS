#ifndef _FREETACOS_TEST_APP
#define _FREETACOS_TEST_APP

#include <task.hpp>

#include <circle/logger.h>

#include "apex_process.h"

class TestApp : Task {
public:
    TestApp(CLogger* logger);
    ~TestApp(void);

    void Run(void);

private:
    CLogger* logger;
};

#endif