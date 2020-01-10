#include "primeproc.h"
#include "circle/logger.h"

PrimeProc::PrimeProc(const char* nameRef, CLogger& logger)
    : IProcess(nameRef), mLogger(logger)
{
}

bool PrimeProc::initialise()
{
    // Test application level things.
    return 2 + 2 == 4;
};

void PrimeProc::run()
{
    if (!initialise()) {
        return;
    }

    mLogger.Write(this->nameRef, LogNotice, "Running Fib(10) times...");
    for (int i = 0; i < 10; i++) {
        mLogger.Write(this->nameRef, LogNotice, "fib(%i): %i", i, fib(i));
    }
}

int PrimeProc::fib(int n)
{
    /* Declare an array to store Fibonacci numbers. */
    int f[n + 1];
    int i;

    /* 0th and 1st number of the series are 0 and 1*/
    f[0] = 0;
    f[1] = 1;

    for (i = 2; i <= n; i++) {
        /* Add the previous 2 numbers in the series
           and store it */
        f[i] = f[i - 1] + f[i - 2];
    }

    return f[n];
}
