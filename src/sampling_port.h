#include "port_type.h"

#ifndef SAMPLING_PORT
#define SAMPLING_PORT

class SamplingPort : Port
{
    private:
        float refreshRateSecond;

    public:
        SamplingPort(NameType name, int msgSize, PortMappingType direction, int id, float rate):
          Port(name, msgSize, direction, id), refreshRateSecond(rate) {}
};

#endif
