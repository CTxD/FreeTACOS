#include "port_type.h"

#ifndef QUEUING_PORT
#define QUEUING_PORT

class QueuingPort : PortType
{
    private:
        int max_nb_messages;      /* required */
};

#endif
