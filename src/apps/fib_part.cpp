#include "fib_part.h"
#include "circle/logger.h"

FibPart::FibPart(CLogger* logger, QueuingPort* q) : mLogger(logger), sendPort(q)
{
}

void FibPart::Run()
{
    mLogger->Write(nameRef, LogNotice, "Running Fib(10) times...");

    for (int i = 0; i < 10; i++) {
        char* mes = (char*)malloc(10);
        sprintf(mes, "%d", fib(i));
        mLogger->Write(nameRef, LogNotice, "Producing - %s", mes);
        sendPort->addMessage(mes);
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
