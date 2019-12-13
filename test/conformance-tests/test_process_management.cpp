#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include "include/general_types.hpp"
#include "include/partition.hpp"
#include "include/process.hpp"

void CheckCreate_Process(Partition& partition,
                         PROCESS_ATTRIBUTE_TYPE attr,
                         RETURN_CODE_TYPE& returnCode,
                         identifier_t& id)
{
    partition.createProcess(attr, id, returnCode);
}

TEST_CASE("CREATE_PROCESS", "[API-PROC-0230]"){
    SECTION("Master_Test")
    {
        Partition partition(
            1, 1, "Master", 100, 1000, {{"mainMemory", memory_region_t::RAM, 1048576, memory_access_t::READ_ONLY, {}}}, {}, {}
          
        );

        SECTION("T-PI-PROC-0230:0011")
        {
            identifier_t processId;
            PROCESS_ATTRIBUTE_TYPE attributes{"Process_1",
                                              (void*)(SYSTEM_ADDRESS_TYPE)0x80000100,
                                              100,
                                              1,
                                              10,
                                              5,
                                              DEADLINE_TYPE::SOFT};

            SECTION("API-PROC-0230:0010, API-PROC-0230:0030")
            {
                RETURN_CODE_TYPE returnValue = RETURN_CODE_TYPE::NO_ERROR;
                CheckCreate_Process(partition, attributes, returnValue, processId);
                REQUIRE(returnValue == RETURN_CODE_TYPE::NO_ERROR);
                REQUIRE(processId);

                Process proc;
                partition.getProcess(processId, proc, returnValue);
                REQUIRE(proc.getStatus().PROCESS_STATE == PROCESS_STATE_TYPE::DORMANT);
          
                returnValue = RETURN_CODE_TYPE::NO_ACTION;
                CheckCreate_Process(partition, attributes, returnValue, processId);
                  REQUIRE(returnValue == RETURN_CODE_TYPE::NO_ACTION);
            }
        }

        SECTION("T-API-PROC-0230:0015")
        {
            RETURN_CODE_TYPE returnValue = RETURN_CODE_TYPE::NO_ERROR;
            identifier_t proc1Id;
            identifier_t proc2Id;
            identifier_t proc3Id;

            PROCESS_ATTRIBUTE_TYPE attrProc1{
                "Process_1", (SYSTEM_ADDRESS_TYPE)0x80000100, 100, 1, INFINITE_TIME_VALUE, 5, DEADLINE_TYPE::SOFT};

            PROCESS_ATTRIBUTE_TYPE attrProc2{
                "Process_2", (SYSTEM_ADDRESS_TYPE)0x80000200, 100, 1, 10, INFINITE_TIME_VALUE, DEADLINE_TYPE::SOFT};

            PROCESS_ATTRIBUTE_TYPE attrProc3{"Process_3",
                                             (SYSTEM_ADDRESS_TYPE)0x80000300,
                                             100,
                                             1,
                                             INFINITE_TIME_VALUE,
                                             INFINITE_TIME_VALUE,
                                             DEADLINE_TYPE::SOFT};
            SECTION("API-PROC-0230:0016, API-PROC-0230:0013, API-PROC-0230:0018")
            {
                CheckCreate_Process(partition, attrProc1, returnValue, proc1Id);
                REQUIRE(returnValue == RETURN_CODE_TYPE::NO_ERROR);
                REQUIRE(proc1Id);

                CheckCreate_Process(partition, attrProc2, returnValue, proc2Id);
                REQUIRE(returnValue == RETURN_CODE_TYPE::NO_ERROR);
                REQUIRE(proc2Id);

                CheckCreate_Process(partition, attrProc3, returnValue, proc3Id);
                REQUIRE(returnValue == RETURN_CODE_TYPE::NO_ERROR);
                REQUIRE(proc3Id);

                Process proc1;
                partition.getProcess(proc1Id, proc1, returnValue);
                REQUIRE(proc1.getStatus().PROCESS_STATE == PROCESS_STATE_TYPE::DORMANT);

                Process proc2;
                partition.getProcess(proc2Id, proc2, returnValue);
                REQUIRE(proc2.getStatus().PROCESS_STATE == PROCESS_STATE_TYPE::DORMANT);

                Process proc3;
                partition.getProcess(proc3Id, proc3, returnValue);
                REQUIRE(proc3.getStatus().PROCESS_STATE == PROCESS_STATE_TYPE::DORMANT);

                bool uniqueIds = proc1Id != proc2Id || proc1Id != proc3Id ||
                                 proc2Id != proc3Id;
                REQUIRE(uniqueIds);
            }
        }

        SECTION("T-API-PROC-0230:0012")
        {
            identifier_t processId;

            SECTION("API-PROC-0230:0040")
            {
                RETURN_CODE_TYPE returnValue = RETURN_CODE_TYPE::INVALID_PARAM;
                PROCESS_ATTRIBUTE_TYPE attributes{"Process_ERROR_HANDLING",
                                                  (SYSTEM_ADDRESS_TYPE)0x80000100,
                                                  10000,
                                                  1,
                                                  10,
                                                  5,
                                                  DEADLINE_TYPE::SOFT};
            }

            SECTION("API-PROC-0230:0050")
            {
                RETURN_CODE_TYPE returnValue = RETURN_CODE_TYPE::INVALID_PARAM;
                PROCESS_ATTRIBUTE_TYPE attributes{"Process_ERROR_HANDLING",
                                                  (SYSTEM_ADDRESS_TYPE)0x80000100,
                                                  100,
                                                  -1,
                                                  10,
                                                  5,
                                                  DEADLINE_TYPE::SOFT};

                CheckCreate_Process(partition, attributes, returnValue, processId);
                REQUIRE(returnValue == RETURN_CODE_TYPE::INVALID_PARAM);

                attributes = PROCESS_ATTRIBUTE_TYPE{"Process_ERROR_HANDLING",
                                                    (SYSTEM_ADDRESS_TYPE)0x80000100,
                                                    100,
                                                    100,
                                                    10,
                                                    5,
                                                    DEADLINE_TYPE::SOFT};

                CheckCreate_Process(partition, attributes, returnValue, processId);
                REQUIRE(returnValue == RETURN_CODE_TYPE::INVALID_PARAM);
            }

            SECTION("API-PROC-0230:0060")
            {
                RETURN_CODE_TYPE returnValue = RETURN_CODE_TYPE::INVALID_CONFIG;
                PROCESS_ATTRIBUTE_TYPE attributes{"Process_ERROR_HANDLING",
                                                  (SYSTEM_ADDRESS_TYPE)0x80000100,
                                                  100,
                                                  1,
                                                  33,
                                                  5,
                                                  DEADLINE_TYPE::SOFT};

                CheckCreate_Process(partition, attributes, returnValue, processId);
                REQUIRE(returnValue == RETURN_CODE_TYPE::INVALID_CONFIG);

                attributes = PROCESS_ATTRIBUTE_TYPE{"Process_ERROR_HANDLING",
                                                    (SYSTEM_ADDRESS_TYPE)0x80000100,
                                                    100,
                                                    1,
                                                    -10,
                                                    5,
                                                    DEADLINE_TYPE::SOFT};

                CheckCreate_Process(partition, attributes, returnValue, processId);
                REQUIRE(returnValue == RETURN_CODE_TYPE::INVALID_CONFIG);
            }

            SECTION("API-PROC-0230:0070")
            {
            }
        }
    }
}
  