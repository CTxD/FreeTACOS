
#ifndef _LYNGSOE_IO2BLR_SERVICE
#define _LYNGSOE_IO2BLR_SERVICE

#include <task.hpp>

#include <circle/logger.h>

#include <apex_buffer.hpp>
#include <apex_process.hpp>
#include <apex_types.hpp>

class Io2BlrServiceTask : public Task {
public:
    Io2BlrServiceTask();
    ~Io2BlrServiceTask(void);

    void Run(void);
    MESSAGE_ADDR_TYPE checkBuffer();
    bool handleMessage(MESSAGE_ADDR_TYPE msg);
    void ioResponse(bool status);
};

#endif