#ifndef SYSTEM_HM_TABLE
#define SYSTEM_HM_TABLE

#include "module_hm_table.h"

class SystemHMTable
{
  private:
    ModuleHMTable* moduleHMTable;

  public:
    SystemHMTable(ModuleHMTable* moduleHM): moduleHMTable(moduleHM) {}
};

#endif
