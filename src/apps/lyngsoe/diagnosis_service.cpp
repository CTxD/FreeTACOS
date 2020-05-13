#include <circle/logger.h>
#include <lyngsoe/diagnosis_service.hpp>

DiagnosisServiceTask::DiagnosisServiceTask()
    : Task(10, 10, 10, HARD, {"DiagnosisService"}, {"IOProcessing"})
{
}

void DiagnosisServiceTask::Run(void)
{
    CLogger::Get()->Write(*getProcessName().x, LogNotice, "Initialised");

    while (1) {
    }
    return;
}

DiagnosisServiceTask::~DiagnosisServiceTask(void)
{
}