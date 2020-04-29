#include "tacoskernel.h"
#include <apex_buffer.hpp>
#include <apex_kernel.hpp>
#include <circle/time.h>
#include <partitionscheduling.hpp>

CTacosKernel::CTacosKernel()
{
}

CStdlibApp::TShutdownMode CTacosKernel::Run(void)
{
    CyclicExecutiveSchedule::getCurrentPartition()->partitionName = {
        "IOProcessing"};

    BUFFER_ID_TYPE id;
    RETURN_CODE_TYPE code;

    ApexBuffer::initialiseBuffers();

    ApexBuffer::CREATE_BUFFER({"TestBuffer"}, 255, 10, FIFO, &id, &code);

    if (code == NO_ERROR) {
        mLogger.Write("Tester", LogNotice, "Buffer created with id: %i", id);
    }
    else {
        mLogger.Write("Tester", LogNotice, "Error creating buffer");
    }

    while (1) {
    }

    return ShutdownHalt;
}

void CTacosKernel::TimerHandler(TKernelTimerHandle hTimer, void* pParam, void* pContext)
{
    CTacosKernel* pThis = (CTacosKernel*)pParam;
    assert(pThis != 0);
    CTimer::Get()->StartKernelTimer(7 * HZ, TimerHandler, pThis);
    pThis->mEvent.Set();
}