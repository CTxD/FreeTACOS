#include "tacoskernel.h"
#include "port.hpp"
#include "process_schedule.hpp"
#include "scheduling/partitionscheduling.hpp"
#include <apex_kernel.hpp>
#include <circle/time.h>
#include <consumer_part.h>
#include <context.h>
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

typedef struct processControlBlock {
    volatile u64* pTopOfStack;
    u64* pStack;
} PCB;

const uint16_t stackDepth = 2048;
PCB* pA_PCB = NULL;
PCB* pB_PCB = NULL;
PCB* pKernel_PCB = NULL;
PCB* pCurrent_PCB = NULL;

CTacosKernel::CTacosKernel()
{
}

void PrintBottomOfStack(const char* stackDescription, volatile u64* pTopStack)
{
    CLogger::Get()->Write(
        stackDescription, LogNotice,
        "R0 - %lX, R1 - %lX, ELR - %lX, SPSR - %lX, R29 - %lX, R30 - %lX",
        *(pTopStack + 28), *(pTopStack + 29), *(pTopStack + 30),
        *(pTopStack + 31), *(pTopStack + 32), *(pTopStack + 33));
}

static void A()
{
    int i = 0;
    while (1) {
        CLogger::Get()->Write("A running", LogNotice, " ... Iteration - %d", i++);
        CTimer::Get()->MsDelay(1000);
    }
}
static void B()
{
    int i = 0;
    while (1) {
        CLogger::Get()->Write("B running", LogNotice, " ... Iteration - %d", i++);
        CTimer::Get()->MsDelay(1000);
    }
}

u64* init_stack(u64* pTopOfStack, run_func pCode)
{
    pTopOfStack--;
    *pTopOfStack = (u64)0x30303030ULL; /* R30 - procedure call link register. */
    pTopOfStack--;
    *pTopOfStack = (u64)0x0ULL; /* R29 */
    pTopOfStack--;

    *pTopOfStack = (u64)(0x20000304); // SPSR_EL   30
    pTopOfStack--;
    *pTopOfStack = (u64)pCode; /// ELR_EL    31
    pTopOfStack--;

    *pTopOfStack = 0x0101010101010101ULL; /* R1 */
    pTopOfStack--;
    *pTopOfStack = (u64)0x00; /* R0 */
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

PCB* AllocPCB(PCB* p, run_func code)
{
    p = (PCB*)malloc(sizeof(PCB));
    u64* pStack = (u64*)malloc((((size_t)stackDepth) * sizeof(u64)));
    u64* pTopOfStack = &(pStack[stackDepth - 1]);
    p->pStack = pStack;
    pTopOfStack = init_stack(pTopOfStack, code);
    p->pTopOfStack = pTopOfStack;
    return p;
}
TSysRegs regs;

bool firstSchedule = 1;
extern "C" void nextProcess()
{
    pCurrent_PCB->pTopOfStack = *pSavedContext;
    if (pA_PCB->pTopOfStack == pCurrentPCBStack) {
        pCurrentPCBStack = pB_PCB->pTopOfStack;
        pCurrent_PCB = pB_PCB;
    }
    else {
        pCurrentPCBStack = pA_PCB->pTopOfStack;
        pCurrent_PCB = pA_PCB;
    }

    return;
}

CStdlibApp::TShutdownMode CTacosKernel::Run(void)
{
    pA_PCB = AllocPCB(pA_PCB, &A);
    pB_PCB = AllocPCB(pB_PCB, &B);
    pKernel_PCB = AllocPCB(pKernel_PCB, NULL);

    pCurrentPCBStack = pKernel_PCB->pTopOfStack;
    pCurrent_PCB = pKernel_PCB;

    CTimer::Get()->StartKernelTimer(2 * HZ, TimerHandler, this);
    while (1) {
        CLogger::Get()->Write("Inside Run", LogNotice, " ... ");
        CTimer::Get()->MsDelay(1000);
    }
    return ShutdownHalt;
}

void CTacosKernel::TimerHandler(TKernelTimerHandle hTimer, void* pParam, void* pSavedContext)
{
    CLogger::Get()->Write("Inside Handler", LogNotice, " ... ");

    CTacosKernel* pThis = (CTacosKernel*)pParam;
    assert(pThis != 0);
    *switchRequired = 1;
    CTimer::Get()->StartKernelTimer(3 * HZ, TimerHandler, pThis);
}