#include "general_types.h"

#ifndef ERROR_ID_ACTION
#define ERROR_ID_ACTION

typedef
    enum ModuleActionType
    {
        IGNORE      = 0;
        SHUTDOWN    = 1;
        RESET       = 2;
    };

class ErrorIDAction
{
    private:
        int errorIdentifier;                    /* required */
        std::optional<NameType> description;    /* optional */
        ModuleActionType action;                /* required */

    public:
        ErrorIDAction(int id, NameType description, ModuleActionType action):
          errorIdentifier(id), description(description), action(action) {}
};

#endif
