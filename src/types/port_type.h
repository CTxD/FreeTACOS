#ifndef PORT_TYPE
#define PORT_TYPE

#include "apex_types.h"
#include "port_mapping.h"


class Port
{
    private:
        name_t portName;                /* required */
        int maxMessageSize;             /* required */
        PORT_DIRECTION_TYPE direction;  /* required */
        // identifier_t portIdentifier;    /* required */

    public:
        Port(name_t name, int msgSize, PORT_DIRECTION_TYPE dir):
          portName(name), maxMessageSize(msgSize), direction(dir) {}

        // Port& operator=(Port&& rhs)
        // {
        //   portName = rhs.portName;
        //   maxMessageSize = rhs.maxMessageSize;
        //   direction = rhs.direction;
        //   return *this;
        // }
};

class SamplingPort : Port
{
    private:
        std::optional<float> refreshRate;  /* optional */

    public:
        SamplingPort(name_t name, int msgSize, PORT_DIRECTION_TYPE direction, float refreshRate):
          Port(name, msgSize, direction), refreshRate(refreshRate) {}
        //
        // SamplingPort& operator=(SamplingPort&& rhs)
        // {
        //     Port::operator=(std::move(rhs));
        //     refreshRate = std::move(rhs.refreshRate);
        //     return *this;
        // }
};

class QueuingPort : Port
{
    private:
        int maxNumMessages; /* required */

    public:
        QueuingPort(name_t name, int msgSize, PORT_DIRECTION_TYPE direction, int maxMessages):
          Port(name, msgSize, direction), maxNumMessages(maxMessages) {}

        // QueuingPort& operator=(QueuingPort&& rhs)
        // {
        //     Port::operator=(std::move(rhs));
        //     maxNumMessages = std::move(rhs.maxNumMessages);
        //     return *this;
        // }
};

#endif
