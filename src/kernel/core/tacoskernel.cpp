#include "tacoskernel.h"
#include <errcode.h>
#include "processchedule.hpp"

CTacosKernel::CTacosKernel()
{
}
CStdlibApp::TShutdownMode CTacosKernel::Run(void)
{
    ProcessSchedule();
        mLogger.Write(GetKernelName(), LogNotice,
                      "C Standard Library stdin/stdout/stderr Demo");
    while (1) {
    }

    return ShutdownHalt;
}
