#include "port_type.h"

#ifndef QUEUING_PORT
#define QUEUING_PORT

class QueuingPort : Port
{
    private:
        int maxNumMessages;      /* required */

    public:
      QueuingPort(NameType name, int msgSize, PortMappingType direction, int id, int msgNum):
        Port(name, msgSize, direction, id), maxNumMessages(msgNum) {}
};

#endif
