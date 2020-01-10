#include "tacoskernel.h"
#include <arinc_module.hpp>
#include <errcode.h>
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
