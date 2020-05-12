#ifndef _LYNGSOE_RFID_READER
#define _LYNGSOE_RFID_READER

#include <task.hpp>

#include <circle/logger.h>

#include <apex_process.hpp>

class RfidReaderTask : public Task {
public:
    RfidReaderTask(CLogger* logger);
    ~RfidReaderTask(void);

    void Run(void);

private:
    CLogger* logger;
};

#endif