#include <circle/logger.h>
#include <processinterface.h>

#include <circle/sched/scheduler.h>
#include <circle/string.h>
#include <circle/util.h>
#include <partition.hpp>

class FibPart : public CTask {
protected:
    CLogger* mLogger;

public:
    FibPart(CLogger* logger);
    ~FibPart(){};
    void Run();

    int fib(int n);
};
