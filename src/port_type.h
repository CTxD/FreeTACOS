#include "general_types.h"
#include "port_mapping.h"

#ifndef PORT_TYPE
#define PORT_TYPE

class PortType
{
    private:
        NameType port_name;         /* required */
        int max_message_size;       /* required */
        PortMappingType direction;  /* required */
        int channel_id;             /* required */  /* what type should this be */
};

#endif
