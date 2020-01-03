#include <circle/logger.h>
#include <processinterface.h>

class PrimeProc : public IProcess {
protected:
    CLogger& mLogger;

public:
    PrimeProc(const char* nameRef, CLogger& logger);
    ~PrimeProc(){};
    void run();
    bool initialise();

    int fib(int n);
};
