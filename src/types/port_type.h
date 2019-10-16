#include "general_types.h"
#include "port_mapping.h"

#ifndef PORT_TYPE
#define PORT_TYPE

class PortType
{
    private:
        nameType portName;          /* required */
        int maxMessageSize;         /* required */
        PortMappingType direction;  /* required */
        int channelId;              /* required */  /* what type should this be */
};

#endif
