#include "fibpart.h"
#include "circle/logger.h"

auto nameRef = "Fib Partition";

FibPart::FibPart(CLogger* logger) : mLogger(logger)
{
}

void FibPart::Run()
{
    mLogger->Write(nameRef, LogNotice, "Running Fib(10) times...");
    for (int i = 0; i < 10; i++) {
        mLogger->Write(nameRef, LogNotice, "fib(%i): %i", i, fib(i));
    }
}

int FibPart::fib(int n)
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
