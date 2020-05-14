#ifndef _LYNGSOE_RFID_READER
#define _LYNGSOE_RFID_READER

#include <task.hpp>

#include <apex_buffer.hpp>
#include <apex_process.hpp>

class RfidReaderTask : public Task {
public:
    RfidReaderTask();
    ~RfidReaderTask(void);

    void Run(void);

private:
    void generateRfidRead();
};

#endif