#ifndef _LYNGSOE_OUTPUT_SERVICE
#define _LYNGSOE_OUTPUT_SERVICE

#include <task.hpp>

#include <apex_process.hpp>

class OutputServiceTask : public Task {
public:
    OutputServiceTask();
    ~OutputServiceTask(void);

    void Run(void);
};

#endif