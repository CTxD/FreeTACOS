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

#include <circle/logger.h>

#include <apex_process.hpp>

class BlrLllHostServiceTask : public Task {
public:
    BlrLllHostServiceTask(CLogger* logger);
    ~BlrLllHostServiceTask(void);

    void Run(void);

private:
    CLogger* logger;
};

#endif