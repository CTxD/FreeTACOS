#ifndef MULTIPARTITION_HM_TABLE
#define MULTIPARTITION_HM_TABLE

#include "multipartition_error_action.hpp"


class MultiPartitionHMTable
{
  private:
    MultiPartitionErrorAction multiPartitionErrorAction[100];
    monotonic_buffer_resource multiPartitionErrorActionSrc{std::data(multiPartitionErrorAction),
                                                           std::size(multiPartitionErrorAction)};
    name_t tableName;                                   /* required */
    vector<MultiPartitionErrorAction> errorAction;      /* required */

  public:
    MultiPartitionHMTable() {}

    MultiPartitionHMTable(name_t name, std::initializer_list<MultiPartitionErrorAction> actions):
      tableName(name), errorAction(actions, &multiPartitionErrorActionSrc) {}

    MultiPartitionHMTable(const MultiPartitionHMTable&) {}

    MultiPartitionHMTable& operator=(const MultiPartitionHMTable&) {
      return *this;
    }

    name_t getTableName();

    vector<MultiPartitionErrorAction> getActions();
};

#endif
