#include "arch.h"
#include <circle/gpiopin.h>
#include <circle/timer.h>
#include <errcode.h>
#include <circle/startup.h>

ret_t init_arch()
{
	CKernel Kernel;
	if (!Kernel.Initialize())
	{
		halt();
		return (ret_t)EXIT_HALT;
	}

	TShutdownMode ShutdownMode = Kernel.Run();

	switch (ShutdownMode)
	{
	case ShutdownReboot:
		reboot();
		return (ret_t)EXIT_REBOOT;

	case ShutdownHalt:
	default:
		halt();
		return (ret_t)EXIT_HALT;
	}
};

CKernel::CKernel(void)
{
}

CKernel::~CKernel(void)
{
}

boolean CKernel::Initialize(void)
{
	return TRUE;
}

TShutdownMode CKernel::Run(void)
{
	CGPIOPin AudioLeft(GPIOPinAudioLeft, GPIOModeOutput);
	CGPIOPin AudioRight(GPIOPinAudioRight, GPIOModeOutput);

	// flash the Act LED 10 times and click on audio (3.5mm headphone jack)
	for (unsigned i = 1; i <= 10; i++)
	{
		m_ActLED.On();
		AudioLeft.Invert();
		AudioRight.Invert();
		CTimer::SimpleMsDelay(500);

		m_ActLED.Off();
		CTimer::SimpleMsDelay(1000);
	}

	return ShutdownReboot;
}
