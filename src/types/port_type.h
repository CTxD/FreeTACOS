#ifndef PORT_TYPE
#define PORT_TYPE

#include "port_mapping.h"

enum direction_t
{
  SOURCE,
  DESTINATION,
};

class Port
{
    private:
        name_t portName;            /* required */
        int maxMessageSize;         /* required */
        direction_t direction;      /* required */

        // Deprecated
        identifier_t channelIdentifier; /* required */

    public:
        Port(name_t name, int msgSize, direction_t dir):
          portName(name), maxMessageSize(msgSize), direction(dir) {}
};

class SamplingPort : Port
{
    private:
        float refreshRateSecond;  /* required */

    public:
        SamplingPort(name_t name, int msgSize, direction_t direction, float refreshRate):
          Port(name, msgSize, direction), refreshRateSecond(refreshRate) {}
};

class QueuingPort : Port
{
    private:
        int maxNumMessages;      /* required */

    public:
        QueuingPort(name_t name, int msgSize, direction_t direction, int maxMessages):
          Port(name, msgSize, direction), maxNumMessages(maxMessages) {}
};

#endif
