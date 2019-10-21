#ifndef MULTIPARTITION_HM_TABLE
#define MULTIPARTITION_HM_TABLE

#include "error_action.h"

class MultiPartitionHMTable
{
  private:
    name_t tableName;                                     /* required */
    std::vector<MultiPartitionErrorAction> errorActions;  /* required */

  public:
    MultiPartitionHMTable(name_t name, std::vector<MultiPartitionErrorAction> actions):
      tableName(name), errorActions(actions) {}
};

#endif
