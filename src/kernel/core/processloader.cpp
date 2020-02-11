#include <apex_process.h>
#include <primeproc.h>
#include <processloader.h>

typedef void func(void);
ProcessLoader::ProcessLoader(CLogger& mLogger) : mLogger(mLogger)
{
    // IProcess run() function pointer
    void (IProcess::*fptr)(void) = &IProcess::run;

    /* Declare applications here
     * --->
     */

    this->processList[0] = new PrimeProc{"App 1", mLogger};
    this->processList[1] = new PrimeProc{"App 2", mLogger};
    this->processList[2] = new PrimeProc{"App 3", mLogger};
}
