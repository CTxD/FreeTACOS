#ifndef QUEUING_PORT
#define QUEUING_PORT

#include "port.h"

class QueuingPort : Port
{
    private:
       APEX_INTEGER maxNumMessages; /* required */

    public:
        QueuingPort(name_t name,APEX_INTEGER msgSize, PORT_DIRECTION_TYPE direction,APEX_INTEGER maxMessages):
          Port(name, msgSize, direction), maxNumMessages(maxMessages) {}

       APEX_INTEGER getMaxNumMessages();
};

#endif
