#ifndef TACOS_PROCESS_LOADER
#define TACOS_PROCESS_LOADER
#include <processinterface.h>
#include <stdlib.h>

class ProcessLoader {
protected:
    CLogger& mLogger;

public:
    IProcess* processList[3];

    ProcessLoader(CLogger& mLogger);
    ~ProcessLoader(){};
};
#endif