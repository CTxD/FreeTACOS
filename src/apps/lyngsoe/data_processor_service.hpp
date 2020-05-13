#ifndef _LYNGSOE_DATA_PROCESSOR_SERVICE
#define _LYNGSOE_DATA_PROCESSOR_SERVICE

#include <task.hpp>

#include <circle/logger.h>

#include <apex_process.hpp>

class DataProcessorServiceTask : public Task {
public:
    DataProcessorServiceTask();
    ~DataProcessorServiceTask(void);

    void Run(void);
};

#endif