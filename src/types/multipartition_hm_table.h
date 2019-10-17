#ifndef MULTIPARTITION_HM_TABLE
#define MULTIPARTITION_HM_TABLE

#include "error_action.h"

class MultiPartitionHMTable
{
  private:
    name_t tableName;                       /* required */
    std::vector<ErrorAction> errorActions;  /* required */

    // Deprecated
    std::optional<identifier_t> tableIdentifier;  /* optional */

  public:
    MultiPartitionHMTable(identifier_t id, name_t name, std::vector<ErrorAction> actions):
      tableIdentifier(id), tableName(name), errorActions(actions) {}
};

#endif
