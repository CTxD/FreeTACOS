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
      vector<ModuleErrorAction> actions;   /* required */

    public:
      ModuleHMTable() {};

      ModuleHMTable(identifier_t state, std::string descr, std::initializer_list<ModuleErrorAction> actions):
        stateIdentifier(state), description(descr), actions(actions, &moduleErrorActionSrc) {}

      ModuleHMTable(const ModuleHMTable& rhs):
        stateIdentifier(rhs.stateIdentifier), description(rhs.description), actions(rhs.actions) {}

      ModuleHMTable& operator=(const ModuleHMTable&);

      const identifier_t& getStateIdentifier() const;

      const std::string& getDescription() const;

      const vector<ModuleErrorAction>& getActions() const;
};

#endif
