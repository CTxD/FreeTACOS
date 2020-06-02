#ifndef _LYNGSOE_DATA_PROCESSOR_SERVICE
#define _LYNGSOE_DATA_PROCESSOR_SERVICE

#include <task.hpp>

#include <circle/logger.h>

#include <apex_process.hpp>
#include <apex_queuing_port.hpp>

class DataProcessorServiceTask : public Task {
public:
    DataProcessorServiceTask();
    ~DataProcessorServiceTask(void);

    void Run(void);
    void handleIncomming();
    void processData(MESSAGE_ADDR_TYPE msg);
    void queueData(bool status);

private:
    QUEUING_PORT_ID_TYPE qIdRaw, qIdProcd;
};

#endif