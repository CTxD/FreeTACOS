#include "sampling_port.hpp"

const std::optional<float>& SamplingPort::getRefreshRate() const
{
    return refreshRate;
}