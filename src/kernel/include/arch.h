#ifndef __FREETACOS_ARCH__
#define __FREETACOS_ARCH__

#include <circle/actled.h>
#include <circle/memory.h>
#include <circle/types.h>
#include <errcode.h>
#include <timer.h>

enum TShutdownMode { ShutdownNone, ShutdownHalt, ShutdownReboot };

class CKernel {
public:
    CKernel(void);
    ~CKernel(void);

    boolean Initialize(void);

    TShutdownMode Run(void);

protected:
    // do not change this order
    CMemorySystem m_Memory;
    CActLED m_ActLED;

    CTimer m_Timer;
};

class CBootableKernel : public CKernel {
private:
public:
    CBootableKernel();
    ~CBootableKernel();
    ret_t Start();

    TShutdownMode Run(void);
};

#endif
