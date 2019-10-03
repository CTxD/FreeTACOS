
class PortType
{
    private:
        NameType port_name;         /* required */
        int max_message_size;       /* required */
        PortMappingType direction;  /* required */
        int channel_id;             /* required */  /* what type should this be */
}