#include "general_types.h"
#include "port_mapping.h"

#ifndef PORT_TYPE
#define PORT_TYPE

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

#endif
