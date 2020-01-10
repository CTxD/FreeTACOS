#include "tacoskernel.h"
#include <errcode.h>
#include <arinc_module.hpp>
#include <process.hpp>

CTacosKernel::CTacosKernel()
{
}
CStdlibApp::TShutdownMode CTacosKernel::Run(void)
{
    while (1) {
        mLogger.Write(GetKernelName(), LogNotice,
                      "C Standard Library stdin/stdout/stderr Demo");
    }

    return ShutdownHalt;
}
