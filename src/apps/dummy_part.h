#include <circle/logger.h>
#include <circle/sched/scheduler.h>
#include <circle/string.h>
#include <circle/util.h>
#include <partition.hpp>

class DummyPart : public CTask {
protected:
    const char* nameRef = "Dummy Partition";

public:
    DummyPart(){};
    ~DummyPart(){};
    void Run();
};
