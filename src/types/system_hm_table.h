#include "general_types.h"
#include "module_hm_table.h"

#ifndef MODULE_HM_TABLE
#define MODULE_HM_TABLE

class SystemHMTable
{
  private:
    ModuleHMTable* moduleHMTable;

  public:
    SystemHMTable(ModuleHMTable* moduleHM): moduleHMTable(moduleHM) {}
};

#endif
