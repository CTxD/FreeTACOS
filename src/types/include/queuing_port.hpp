#ifndef QUEUING_PORT
#define QUEUING_PORT

#include "port.hpp"

class QueuingPort : Port {
private:
    APEX_INTEGER maxNumMessages; /* required */

public:
    QueuingPort()
    {
    }

    QueuingPort(NAME_TYPE name, APEX_INTEGER msgSize, PORT_DIRECTION_TYPE direction, APEX_INTEGER maxMessages)
        : Port(name, msgSize, direction), maxNumMessages(maxMessages)
    {
    }

    const APEX_INTEGER& getMaxNumMessages() const;
};

#endif
