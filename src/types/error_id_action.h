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
<<<<<<< HEAD:src/error_id_action.h
        std::optional<NameType> description;    /* optional */
        ModuleActionType action;                /* required */

    public:
        ErrorIDAction(int id, NameType description, ModuleActionType action):
          errorIdentifier(id), description(description), action(action) {}
=======
        std::optional<nameType> description;    /* optional */
        ModuleActionType action;                /* required */
>>>>>>> 22a2fdd349393e993c07f0055e4fa948756e1e64:src/types/error_id_action.h
};

#endif
