#ifndef PORT_TYPE
#define PORT_TYPE

#include "port_mapping.h"

class Port
{
    private:
        NameType portName;          /* required */
        int maxMessageSize;         /* required */
        PortMappingType direction;  /* required */
        int channelId;              /* required */  /* what type should this be */

    public:
        Port(NameType name, int msgSize, PortMappingType dir, int id):
          portName(name), maxMessageSize(msgSize), direction(dir), channelId(id) {}
};

class SamplingPort : Port
{
    private:
        float refreshRateSecond;

    public:
        SamplingPort(NameType name, int msgSize, PortMappingType direction, int id, float rate):
          Port(name, msgSize, direction, id), refreshRateSecond(rate) {}
};

class QueuingPort : Port
{
    private:
        int maxNumMessages;      /* required */

    public:
        QueuingPort(NameType name, int msgSize, PortMappingType direction, int id, int msgNum):
          Port(name, msgSize, direction, id), maxNumMessages(msgNum) {}
};

#endif
