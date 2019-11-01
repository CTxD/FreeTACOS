#ifndef __FREETACOS_ARCH__
#define __FREETACOS_ARCH__

#include <errcode.h>
#include <circle/memory.h>
#include <circle/actled.h>
#include <circle/types.h>

enum TShutdownMode
{
	ShutdownNone,
	ShutdownHalt,
	ShutdownReboot
};

class CKernel
{
public:
	CKernel (void);
	~CKernel (void);

	boolean Initialize (void);

	TShutdownMode Run (void);

private:
	// do not change this order
	CMemorySystem	m_Memory;
	CActLED		m_ActLED;
};


class CBootableKernel : public CKernel
{
private:
public:
    CBootableKernel();
    ~CBootableKernel();
    ret_t Start();
};

#endif