#ifndef CHANNEL
#define CHANNEL

#include "port_mapping.h"


class Channel
{
	private:
		identifier_t channelIdentifier;						/* required */
		std::optional<name_t> channelName;				/* optional */
		PortMappingType source;										/* required */
		std::vector<PortMappingType> destination; /* required */

	public:
		Channel(identifier_t id, name_t name, PortMappingType source, std::vector<PortMappingType> destinations):
			channelIdentifier(id), channelName(name), source(source), destination(destinations) {}
};

#endif
