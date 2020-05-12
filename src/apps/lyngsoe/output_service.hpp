#ifndef _LYNGSOE_OUTPUT_SERVICE
#define _LYNGSOE_OUTPUT_SERVICE

#include <task.hpp>

#include <circle/logger.h>

#include <apex_process.hpp>

class OutputServiceTask : public Task {
public:
    OutputServiceTask(CLogger* logger);
    ~OutputServiceTask(void);

    void Run(void);

private:
    CLogger* logger;
};

#endif