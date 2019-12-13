.PHONY: conformance-testing unit-testing clean
 
LIB_DIR=../src/types/include/
CACTH_DIR=catch2/
TEST_DIR=.
CPP_FLAGS=-std=c++17 -Wall
 
OBJS=$(SRCS:.cpp=.o)

conformance-testing:
TEST_DIR=conformance-tests/

INCLUDES=\
    -I$(LIB_DIR)\
    -I$(CACTH_DIR)
 
SRCS=\
    $(TEST_DIR)test_process_management.cpp\
    $(LIB_DIR)src/*.cpp

@g++ $(INCLUDES) $(CPP_FLAGS) -o conformance-tests $(OBJS) $(TEST_SRC)
@./conformance-tests
 
#  unit-testing: $(OBJS)
# # 	TEST_DIR=unit-tests/

# # 	INCLUDES=\
# # 	    -I$(LIB_DIR)\
# # 	    -I$(CACTH_DIR)
	 
# # 	SRCS=\
# # 	    $(TEST_DIR)test_process_management.cpp\
# # 	    $(LIB_DIR)src/*.cpp


# #     @g++ $(CPP_FLAGS) $(INCLUDES) -o run_test $(OBJS) $(TEST_SRC)
# #     @./run_test
 
# %.o : %.cpp
#     g++ $(CPP_FLAGS) $(INCLUDES) -c $< -o $@
 
# clean:
#     rm $(OBJS)