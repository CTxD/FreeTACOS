#include <general_types.h>
#include <error_id_level.h>
#include <error_id_action.h>

class SystemStateEntry
{
    private:
        int system_state;                       /* required */
        std::optional<NameType> description;   /* optional */
        ErrorIDLevel error_id_level[MAX_NUMBER_ERROR_ID_LEVEL];
        ErrorIDAction error_id_action[MAX_NUMBER_ERROR_ID_ACTION];
}