#ifndef MODULE_HM_TABLE
#define MODULE_HM_TABLE

#include "error_action.h"


class ModuleHMTable
{
    private:
      ModuleErrorAction moduleErrorAction[100];
      monotonic_buffer_resource moduleErrorActionSrc{std::data(moduleErrorAction),
                                                    std::size(moduleErrorAction)};
      identifier_t stateIdentifier;       /* required */
      std::string description;            /* required */
      vector<ModuleErrorAction> action;   /* required */

    public:
    ModuleHMTable() {};
      ModuleHMTable(identifier_t state, std::string descr, std::initializer_list<ModuleErrorAction> actions):
        stateIdentifier(state), description(descr), action(actions, &moduleErrorActionSrc) {}
      
};

#endif
