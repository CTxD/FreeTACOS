#include "tacoskernel.h"
#include <errcode.h>
#include <stdio.h>

CTacosKernel::CTacosKernel()
{
}
CStdlibApp::TShutdownMode CTacosKernel::Run(void)
{
    GetLogger().Write(GetKernelName(), LogNotice, "C Standard Library stdin/stdout/stderr Demo");

    return ShutdownHalt;
}

CTacosKernel::~CTacosKernel()
{
}