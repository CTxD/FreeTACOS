#ifndef MODULE_HM_TABLE
#define MODULE_HM_TABLE

#include "error_action.h"

class ModuleHMTable
{
    private:
      identifier_t stateIdentifier;     /* required */
      std::string description;          /* required */
      std::vector<ModuleErrorAction> actions; /* required */

    public:
      ModuleHMTable(identifier_t state, std::string descr, std::vector<ModuleErrorAction> actions):
        stateIdentifier(state), description(descr), actions(std::move(actions)) {}
};

#endif
