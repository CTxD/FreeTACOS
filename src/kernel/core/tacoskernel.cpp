#include "tacoskernel.h"
#include "port.hpp"
#include <consumer_part.h>
#include <context.h>
#include <dummy_part.h>
#include <errcode.h>
#include <fib_part.h>
#include <process.hpp>
#include <queuing_port.hpp>

CTacosKernel::CTacosKernel()
{
}
static void A()
{
    while (1) {
        CLogger::Get()->Write("A running", LogNotice, " ... ");
    }
}
static void B()
{
    CLogger::Get()->Write("B running", LogNotice, " ... ");
    while (1) {
        CLogger::Get()->Write("B running", LogNotice, " ... ");
    }
}

typedef void (*run_func)();

typedef struct processControlBlock {
    volatile u64* pTopOfStack;
    u64* pStack;
} PCB;

u64* init_stack(u64* pTopOfStack, run_func pCode)
{
    pTopOfStack--;
    *pTopOfStack = (u64)0x30303030ULL; /* R30 - procedure call link register. */
    pTopOfStack--;
    *pTopOfStack = (u64)pCode; /* R29 */
    pTopOfStack--;

    *pTopOfStack = (u64)pCode; /// ELR_EL    30
    pTopOfStack--;
    *pTopOfStack = (u64)(0x0c); // SPSR_EL   29
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

    return pTopOfStack;
}

const uint16_t stackDepth = 100;

PCB* AllocPCB(run_func code)
{
    PCB* p = (PCB*)malloc(sizeof(PCB));
    u64* pStack = (u64*)malloc((((size_t)stackDepth) * sizeof(u64)));
    u64* pTopOfStack = &(pStack[stackDepth - 1]);
    pTopOfStack = init_stack(pTopOfStack, code);
    p->pStack = pStack;
    p->pTopOfStack = pTopOfStack;
    return p;
}

u64 volatile* pCurrentPCB;
u64 volatile switchRequired = 0;

PCB* pA_PCB;
PCB* pB_PCB;

extern "C" void nextProcess()
{
    pCurrentPCB = pB_PCB->pTopOfStack;
    CLogger::Get()->Write(
        "FreeTACOS", LogNotice, "SP 1 - %lX, SP 2 - %lX, SPSR - %lX, ELR - %lX",
        *pCurrentPCB, *(pCurrentPCB + 1), *(pCurrentPCB + 29), *(pCurrentPCB + 30));

    return;
}
CStdlibApp::TShutdownMode CTacosKernel::Run(void)
{
    pA_PCB = AllocPCB(&A);
    pB_PCB = AllocPCB(&B);

    pCurrentPCB = pA_PCB->pTopOfStack;

    CTimer::Get()->StartKernelTimer(2 * HZ, TimerHandler, this);
    while (1) {
        CLogger::Get()->Write("FreeTACOS", LogNotice,
                              "SP 1 - %lX, SP 2 - %lX, SPSR - %lX, ELR - %lX",
                              *pCurrentPCB, *(pCurrentPCB + 1),
                              *(pCurrentPCB + 29), *(pCurrentPCB + 30));
        CTimer::Get()->MsDelay(1000);
    }
    return ShutdownHalt;
}

void CTacosKernel::TimerHandler(TKernelTimerHandle hTimer, void* pParam, void* pContext)
{
    CLogger::Get()->Write("Inside Handler", LogNotice, " ... ");
    CTacosKernel* pThis = (CTacosKernel*)pParam;
    assert(pThis != 0);
    // pCurrentPCB = (pCurrentPCB == pB_PCB->pTopOfStack) ? pB_PCB->pTopOfStack
    //                                                    : pA_PCB->pTopOfStack;
    switchRequired = 1;
    CTimer::Get()->StartKernelTimer(3 * HZ, TimerHandler, pThis);
}