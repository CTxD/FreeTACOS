#include <circle/logger.h>
#include <processinterface.h>

#include <circle/sched/scheduler.h>
#include <circle/string.h>
#include <circle/util.h>
#include <partition.hpp>
#include <queuing_port.hpp>

class FibPart : public CTask {
protected:
    CLogger* mLogger;
    QueuingPort* sendPort;
    const char* nameRef = "Fib Partition";

public:
    FibPart(CLogger* logger, QueuingPort* q);
    ~FibPart(){};
    void Run();

    int fib(int n);
};
