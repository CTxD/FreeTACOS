#include "port_type.h"

#ifndef SAMPLING_PORT
#define SAMPLING_PORT

class SamplingPort : PortType
{
    private:
        float refresh_rate_second;
};

#endif
