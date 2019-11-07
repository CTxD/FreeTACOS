#ifndef MODULE_HM_TABLE
#define MODULE_HM_TABLE

#include "module_error_action.h"


class ModuleHMTable
{
    private:
      identifier_t stateIdentifier;       /* required */
      std::string description;            /* required */
      vector<ModuleErrorAction> actions;  /* required */

    public:
      ModuleHMTable() {}

      ModuleHMTable(identifier_t state, std::string descr, std::initializer_list<ModuleErrorAction> actions):
        stateIdentifier(state), description(descr), actions(std::move(actions)) {}

      identifier_t getStateIdentifier();

      std::string getDescription();

      vector<ModuleErrorAction> getActions();
};

#endif
