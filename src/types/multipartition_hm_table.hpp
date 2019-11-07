#ifndef MULTIPARTITION_HM_TABLE
#define MULTIPARTITION_HM_TABLE

#include "multipartition_error_action.h"


class MultiPartitionHMTable
{
  private:
    name_t tableName;                                /* required */
    vector<MultiPartitionErrorAction> errorActions;  /* required */

  public:
    MultiPartitionHMTable(name_t name, std::initializer_list<MultiPartitionErrorAction> actions):
      tableName(name), errorActions(actions) {}

    name_t getTableName();

    vector<MultiPartitionErrorAction> getActions();
};

#endif
