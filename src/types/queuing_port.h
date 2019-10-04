#include "port_type.h"

#ifndef QUEUING_PORT
#define QUEUING_PORT

class QueuingPort : PortType
{
    private:
        int maxNbMessages;      /* required */
};

#endif
