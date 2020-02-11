#include "queuing_port.hpp"

const APEX_INTEGER& QueuingPort::getQueueSize() const
{
    return messageQueue.size();
}

const APEX_INTEGER& QueuingPort::getMaxNumMessages() const
{
    return maxNumMessages;
}

const identifier_t QueuingPort::GET_QUEUING_PORT_ID() const
{
    return id;
}

void QueuingPort::addMessage(char* msg)
{
    messageQueue.push_back(msg);
}

char* QueuingPort::getMessage()
{
    char* message = messageQueue.front();
    messageQueue.erase(messageQueue.begin());
    return message;
}

void QueuingPort::removeMessage()
{
    messageQueue.erase(messageQueue.begin());
}