#ifndef _LYNGSOE_IO_SERVICE
#define _LYNGSOE_IO_SERVICE

#include <task.hpp>

#include <circle/logger.h>

#include <apex_process.hpp>

class IoServiceTask : public Task {
public:
    IoServiceTask();
    ~IoServiceTask(void);

    void Run(void);
};

#endif