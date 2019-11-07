#ifndef CHANNEL
#define CHANNEL

#include "port_mapping.h"
#include "general_types.h"

class Channel
{
	private:
		identifier_t channelIdentifier;				/* required */
		std::optional<name_t> channelName;		/* optional */
		PortMappingType source;								/* required */
		vector<PortMappingType> destination;	/* required */

	public:
		Channel(identifier_t id, name_t name, PortMappingType source, std::initializer_list<PortMappingType> destinations):
			channelIdentifier(id), channelName(name), source(source), destination(destinations) {}
};

#endif
