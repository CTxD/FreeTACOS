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
        identifier_t portIdentifier;    /* required */

    public:
        Port(name_t name, int msgSize, PORT_DIRECTION_TYPE dir):
          portName(name), maxMessageSize(msgSize), direction(dir) {}
};

class SamplingPort : Port
{
    private:
        std::optional<float> refreshRate;  /* optional */

    public:
        SamplingPort(name_t name, int msgSize, PORT_DIRECTION_TYPE direction, float refreshRate):
          Port(name, msgSize, direction), refreshRate(refreshRate) {}
};

class QueuingPort : Port
{
    private:
        int maxNumMessages; /* required */


    public:
        QueuingPort(name_t name, int msgSize, PORT_DIRECTION_TYPE direction, int maxMessages):
          Port(name, msgSize, direction), maxNumMessages(maxMessages) {}
};

#endif
