#include "include/channel.hpp"

const identifier_t& Channel::getChannelId() const
{
    return channelIdentifier;
}

const std::optional<NAME_TYPE>& Channel::getChannelName() const
{
    return channelName;
}

const PortMapping& Channel::getSource() const
{
    return source;
}

const std::vector<PortMapping, MonotonicAllocator<PortMapping>>& Channel::getDestinations() const
{
    return destinations;
}
