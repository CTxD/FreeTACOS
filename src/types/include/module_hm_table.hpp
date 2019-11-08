#ifndef MODULE_HM_TABLE
#define MODULE_HM_TABLE

#include "module_error_action.hpp"


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

      ModuleHMTable(const ModuleHMTable&) {}

      ModuleHMTable& operator=(const ModuleHMTable&)
      {
        return *this;
      }

      identifier_t getStateIdentifier();

      std::string getDescription();

      vector<ModuleErrorAction> getActions();
};

#endif
