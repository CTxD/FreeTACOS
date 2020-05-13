#include <arch.h>

class CTacosKernel : public CKernel {
private:
    static void TimerHandler(TKernelTimerHandle hTimer, void* pParam, void* pContext);
    static void PartitionTimerHandler(TKernelTimerHandle hTimer, void* pParam, void* pContext);
    static void ProcessTimerHandler(TKernelTimerHandle hTimer, void* pParam, void* pContext);

public:
    CTacosKernel();
    CStdlibApp::TShutdownMode Run();
};