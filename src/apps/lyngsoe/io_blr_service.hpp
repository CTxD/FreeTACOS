#ifndef _LYNGSOE_IO2BLR_SERVICE
#define _LYNGSOE_IO2BLR_SERVICE

#include <task.hpp>

#include <circle/logger.h>

#include <apex_process.hpp>

class Io2BlrServiceTask : public Task {
public:
    Io2BlrServiceTask(CLogger* logger);
    ~Io2BlrServiceTask(void);

    void Run(void);

private:
    CLogger* logger;
};

#endif