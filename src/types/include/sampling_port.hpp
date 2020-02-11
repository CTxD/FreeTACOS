#ifndef SAMPLING_PORT
#define SAMPLING_PORT

#include "port.hpp"

class SamplingPort : public Port {
private:
    std::optional<float> refreshRate; /* optional */

public:
    SamplingPort()
    {
    }

    SamplingPort(NAME_TYPE name, APEX_INTEGER msgSize, PORT_DIRECTION_TYPE direction, float refreshRate)
        : Port(name, msgSize, direction), refreshRate(refreshRate)
    {
    }

    const std::optional<float>& getRefreshRate() const;
};

#endif