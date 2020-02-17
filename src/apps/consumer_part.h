#include <circle/logger.h>

#include <circle/sched/scheduler.h>
#include <circle/string.h>
#include <circle/util.h>
#include <partition.hpp>
#include <queuing_port.hpp>

class ConsumerPart : public CTask {
protected:
    CLogger* mLogger;
    QueuingPort* receivePort;
    const char* nameRef = "Consumer Partition";

public:
    ConsumerPart(CLogger* logger, QueuingPort* q);
    ~ConsumerPart(){};
    void Run();
};
