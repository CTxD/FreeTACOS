#ifndef QUEUING_PORT
#define QUEUING_PORT

#include "port.hpp"
#include <string>
#include <vector>

class QueuingPort : public Port {
private:
    APEX_INTEGER maxNumMessages; /* required */
    APEX_INTEGER numMessages;
    std::vector<char*> messageQueue;

public:
    QueuingPort()
    {
    }

    QueuingPort(NAME_TYPE name, APEX_INTEGER msgSize, PORT_DIRECTION_TYPE direction, APEX_INTEGER maxMessages)
        : Port(name, msgSize, direction), maxNumMessages(maxMessages)
    {
        messageQueue.reserve(maxNumMessages);
    }

    const APEX_INTEGER& getQueueSize() const;

    const APEX_INTEGER& getMaxNumMessages() const;

    const identifier_t GET_QUEUING_PORT_ID() const;

    void addMessage(char* msg);

    char* getMessage();

    void removeMessage();
};

#endif