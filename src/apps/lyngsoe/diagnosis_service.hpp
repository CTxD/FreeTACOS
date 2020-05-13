#ifndef _LYNGSOE_DIAGNOSIS_SERVICE
#define _LYNGSOE_DIAGNOSIS_SERVICE

#include <task.hpp>

#include <circle/logger.h>

#include <apex_process.hpp>

class DiagnosisServiceTask : public Task {
public:
    DiagnosisServiceTask();
    ~DiagnosisServiceTask(void);

    void Run(void);
};

#endif