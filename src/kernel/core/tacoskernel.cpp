#include "tacoskernel.h"
#include "partitionscheduling.hpp"
#include "port.hpp"
#include "process_schedule.hpp"
#include <apex_kernel.hpp>
#include <circle/time.h>
#include <consumer_part.h>
#include <context.hpp>
#include <defines.hpp>

#include <dummy_part.h>
#include <entry.hpp>
#include <errcode.h>
#include <queuing_port.hpp>
#include <test_app.hpp>

// Preemption
volatile u64 switchR = 0;
volatile u64* switchRequired = &switchR;

volatile u64* context = 0;
volatile u64** pSavedContext = &context;

volatile u64* pCurrentPCBStack = NULL;

// Debug
TSysRegs sysRegs;

// Allocation of PCBS
typedef void (*run_func)();

const uint16_t stackDepth = 2048;

Task* pA = NULL;
Task* pB = NULL;
Task* pKernel = NULL;
Task* pCurrent = NULL;

CTacosKernel::CTacosKernel()
{
}

void PrintBottomOfStack(const char* stackDescription, volatile u64* pTopOfStack)
{
    CLogger::Get()->Write(
        stackDescription, LogNotice,
        "R0 - %lX, R1 - %lX, ELR - %lX, SPSR - %lX, R29 - %lX, R30 - %lX",
        *(pTopOfStack + 28), *(pTopOfStack + 29), *(pTopOfStack + 30),
        *(pTopOfStack + 31), *(pTopOfStack + 32), *(pTopOfStack + 33));
}

u64* InitProcStack(u64* pTopOfStack, Task* proc)
{
    pTopOfStack--;
    *pTopOfStack = (u64)0x30303030ULL; /* R30 - procedure call link register. */
    pTopOfStack--;
    *pTopOfStack = (u64)0x2929292929292929ULL; /* R29 */
    pTopOfStack--;

    *pTopOfStack = (u64)(0x20000304); // SPSR_EL   30
    pTopOfStack--;
    *pTopOfStack = (u64)(&Task::TaskEntry); /// ELR_EL    31
    pTopOfStack--;

    *pTopOfStack = 0x0101010101010101ULL; /* R1 */
    pTopOfStack--;
    *pTopOfStack = (u64)(proc); /* R0 */
    pTopOfStack--;
    *pTopOfStack = 0x0303030303030303ULL; /* R3 */
    pTopOfStack--;
    *pTopOfStack = 0x0202020202020202ULL; /* R2 */
    pTopOfStack--;
    *pTopOfStack = 0x0505050505050505ULL; /* R5 */
    pTopOfStack--;
    *pTopOfStack = 0x0404040404040404ULL; /* R4 */
    pTopOfStack--;
    *pTopOfStack = 0x0707070707070707ULL; /* R7 */
    pTopOfStack--;
    *pTopOfStack = 0x0606060606060606ULL; /* R6 */
    pTopOfStack--;
    *pTopOfStack = 0x0909090909090909ULL; /* R9 */
    pTopOfStack--;
    *pTopOfStack = 0x0808080808080808ULL; /* R8 */
    pTopOfStack--;
    *pTopOfStack = 0x1111111111111111ULL; /* R11 */
    pTopOfStack--;
    *pTopOfStack = 0x1010101010101010ULL; /* R10 */
    pTopOfStack--;
    *pTopOfStack = 0x1313131313131313ULL; /* R13 */
    pTopOfStack--;
    *pTopOfStack = 0x1212121212121212ULL; /* R12 */
    pTopOfStack--;
    *pTopOfStack = 0x1515151515151515ULL; /* R15 */
    pTopOfStack--;
    *pTopOfStack = 0x1414141414141414ULL; /* R14 */
    pTopOfStack--;
    *pTopOfStack = 0x1717171717171717ULL; /* R17 */
    pTopOfStack--;
    *pTopOfStack = 0x1616161616161616ULL; /* R16 */
    pTopOfStack--;
    *pTopOfStack = 0x1919191919191919ULL; /* R19 */
    pTopOfStack--;
    *pTopOfStack = 0x1818181818181818ULL; /* R18 */
    pTopOfStack--;
    *pTopOfStack = 0x2121212121212121ULL; /* R21 */
    pTopOfStack--;
    *pTopOfStack = 0x2020202020202020ULL; /* R20 */
    pTopOfStack--;
    *pTopOfStack = 0x2323232323232323ULL; /* R23 */
    pTopOfStack--;
    *pTopOfStack = 0x2222222222222222ULL; /* R22 */
    pTopOfStack--;
    *pTopOfStack = 0x2525252525252525ULL; /* R25 */
    pTopOfStack--;
    *pTopOfStack = 0x2424242424242424ULL; /* R24 */
    pTopOfStack--;
    *pTopOfStack = 0x2727272727272727ULL; /* R27 */
    pTopOfStack--;
    *pTopOfStack = 0x2626262626262626ULL; /* R26 */
    pTopOfStack--;
    *pTopOfStack = 0x2828282828282828ULL; /* R28 */
    pTopOfStack--;
    *pTopOfStack = 0x0; /* XZR */

    return pTopOfStack;
}

extern "C" void nextProcess()
{
    pCurrent->pTopOfStack = *pSavedContext;
    if (pA->pTopOfStack == pCurrentPCBStack) {
        pCurrentPCBStack = pB->pTopOfStack;
        pCurrent = pB;
    }
    else {
        pCurrentPCBStack = pA->pTopOfStack;
        pCurrent = pA;
    }
    return;
}

Task* initProcess(Task* p)
{
    u64* pStack = (u64*)malloc((((size_t)stackDepth) * sizeof(u64)));
    u64* pTopOfStack = &(pStack[stackDepth - 1]);
    p->pStack = pStack;
    pTopOfStack = InitProcStack(pTopOfStack, p);
    p->pTopOfStack = pTopOfStack;
    return p;
}

CStdlibApp::TShutdownMode CTacosKernel::Run(void)
{
    pA = new TestApp(&mLogger, {"flightManagement"});
    pB = new TestApp(&mLogger, {"io"});
    pKernel = new TestApp(&mLogger, {"io"});

    pA = initProcess(pA);
    pB = initProcess(pB);
    pKernel = initProcess(pKernel);

    pCurrentPCBStack = pKernel->pTopOfStack;
    pCurrent = pKernel;

    CTimer::Get()->StartKernelTimer(2 * HZ, TimerHandler, this);
    while (1) {
        CLogger::Get()->Write("Inside Run", LogNotice, " ... ");
        CTimer::Get()->MsDelay(1000);
    }
    return ShutdownHalt;

    //     CyclicExecutiveSchedule partitionSchedule;
    // #if KERNEL_DEBUG()
    //     mLogger.Write("Tester", LogNotice, "Testing ProcessSchedules..");
    //     mLogger.Write("ProcessSchedule", LogNotice,
    //                   "Initialising schedules from XML");
    // #endif

    //     ProcessSchedule::initialiseSchedules();

    // #if KERNEL_DEBUG()
    //     mLogger.Write("ProcessSchedule", LogNotice, "Printing Names:");
    //     auto* schedule = ProcessSchedule::scheduleList->at(0);
    //     mLogger.Write("ProcessSchedule", LogNotice, "Name: %s---",
    //                   *(schedule->getProcessScheduleName()->x.x));
    //     schedule = ProcessSchedule::scheduleList->at(1);
    //     mLogger.Write("ProcessSchedule", LogNotice, "Name: %s---",
    //                   *(schedule->getProcessScheduleName()->x.x));
    //     schedule = ProcessSchedule::scheduleList->at(2);
    //     mLogger.Write("ProcessSchedule", LogNotice, "Name: %s---",
    //                   *(schedule->getProcessScheduleName()->x.x));
    //     schedule = ProcessSchedule::scheduleList->at(3);
    //     mLogger.Write("ProcessSchedule", LogNotice, "Name: %s---",
    //                   *(schedule->getProcessScheduleName()->x.x));
    //     schedule = ProcessSchedule::scheduleList->at(4);
    //     mLogger.Write("ProcessSchedule", LogNotice, "Name: %s---",
    //                   *(schedule->getProcessScheduleName()->x.x));
    // #endif

    //     // Running Entry Process
    //     auto entry = new Entry(&mLogger);
    //     entry->Run();

    //     partitionSchedule.startPartitionScheduler();

    //     while (1) {
    //     }

    // return ShutdownHalt;
}

void CTacosKernel::TimerHandler(TKernelTimerHandle hTimer, void* pParam, void* pSavedContext)
{
    CLogger::Get()->Write("Inside Handler", LogNotice, " ... ");

    CTacosKernel* pThis = (CTacosKernel*)pParam;
    assert(pThis != 0);
    *switchRequired = 1;
    CTimer::Get()->StartKernelTimer(3 * HZ, TimerHandler, pThis);
}