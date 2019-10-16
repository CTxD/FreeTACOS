#ifndef CHANNEL
#define CHANNEL

#include "port_mapping.h"

class Channel
{
	private:
		IdentifierValueType channelIdentifier;					/* required */
		std::optional<NameType> channelName;						/* optional */
		PortMappingType* source;												/* required */
		PortMappingType* destination;										/* required */

	public:
		Channel(IdentifierValueType id, NameType name, PortMappingType* source, PortMappingType* destinations):
			channelIdentifier(id), channelName(name), source(source), destination(destinations) {}
};

#endif
