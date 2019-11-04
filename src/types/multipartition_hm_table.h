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
    // 
    // MultiPartitionHMTable(const MultiPartitionHMTable& p):
    //   tableName(p.tableName), errorActions(p.errorActions) {}
    //
    // MultiPartitionHMTable(MultiPartitionHMTable&& p) noexcept:
    //   tableName(std::move(p.tableName)), errorActions(std::move(p.errorActions)) {}
    //
    // ~MultiPartitionHMTable() = default;
};

#endif
