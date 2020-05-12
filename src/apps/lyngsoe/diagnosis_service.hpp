#ifndef _LYNGSOE_DIAGNOSIS_SERVICE
#define _LYNGSOE_DIAGNOSIS_SERVICE

#include <task.hpp>

#include <circle/logger.h>

#include <apex_process.hpp>

class DiagnosisServiceTask : public Task {
public:
    DiagnosisServiceTask(CLogger* logger);
    ~DiagnosisServiceTask(void);

    void Run(void);

private:
    CLogger* logger;
};

#endif