#ifndef _LYNGSOE_GPS_SERVICE
#define _LYNGSOE_GPS_SERVICE

#include <task.hpp>

#include <circle/logger.h>

#include <apex_process.hpp>

class GpsServiceTask : public Task {
public:
    GpsServiceTask(CLogger* logger);
    ~GpsServiceTask(void);

    void Run(void);

private:
    CLogger* logger;
};

#endif