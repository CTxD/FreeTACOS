/*
<task name="BlrService"/>
            <task name="DiagnosisService"/>
            <task name="OutputService"/>
            <task name="IoService"/>
            <task name="Io2BlrService"/>
            <task name="RfidReaderService"/>
            <task name="GpsService"/>
            <task name="DataProcessorService"/>
            <task name="BlrLllHostService"/>
            */

#ifndef _LYNGSOE_BLRLLLHOST_SERVICE
#define _LYNGSOE_BLRLLLHOST_SERVICE

#include <task.hpp>

#include <apex_process.hpp>
#include <apex_types.hpp>

class BlrLllHostServiceTask : public Task {
private:
    const MESSAGE_ADDR_TYPE errorMsg = MESSAGE_ADDR_TYPE(new APEX_BYTE('n'));

public:
    BlrLllHostServiceTask();
    ~BlrLllHostServiceTask(void);

    void Run(void);
    MESSAGE_ADDR_TYPE fetchMessage();
    void handleMessage();
};

#endif