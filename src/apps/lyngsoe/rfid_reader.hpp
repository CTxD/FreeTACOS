#ifndef _LYNGSOE_RFID_READER
#define _LYNGSOE_RFID_READER

#include <task.hpp>

#include <vector>

#include <apex_buffer.hpp>
#include <apex_process.hpp>
#include <apex_queuing_port.hpp>

class RfidReaderTask : public Task {
public:
    RfidReaderTask();
    ~RfidReaderTask(void);

    void Run(void);

private:
    void generateRfidRead();

    static std::vector<MESSAGE_ADDR_TYPE> belt;

    QUEUING_PORT_ID_TYPE qId;
};

#endif