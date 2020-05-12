#ifndef __INITIAL_H__
#define __INITIAL_H__

#include <circle/memory.h>
#include <circle/multicore.h>

class CInitialWorker
#ifdef ARM_ALLOW_MULTI_CORE
    : public CMultiCoreSupport
#endif
{

private:
    /* data */
public:
    CInitialWorker(CMemorySystem* pMemorySystem);

    static unsigned ThisCore(void) // returns number of current core (0..CORES-1)
    {
#if AARCH == 32
        u32 nMPIDR;
        asm volatile("mrc p15, 0, %0, c0, c0, 5" : "=r"(nMPIDR));
#else
        u64 nMPIDR;
        asm volatile("mrs %0, mpidr_el1" : "=r"(nMPIDR));
#endif

        return nMPIDR & (CORES - 1);
    }

#ifndef ARM_ALLOW_MULTI_CORE
    boolean Initialize(void)
    {
        return TRUE;
    }

#endif
    ~CInitialWorker();
    void IPIHandler(unsigned nCore, unsigned nIPI);
    void Run(unsigned nCore);
};

#endif