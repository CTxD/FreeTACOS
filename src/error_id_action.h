#include <general_types.h>

typedef
    enum ModuleActionType
    {
        IGNORE      = 0;
        SHUTDOWN    = 1;
        RESET       = 2;
    }

class ErrorIDAction
{
    private:
        int ErrorIdentifier;                    /* required */
        std::optional<NameType> Description;   /* optional */
        ModuleActionType Action;                /* required */
}