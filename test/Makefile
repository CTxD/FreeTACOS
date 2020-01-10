.PHONY: conformance-testing unit-testing clean
LIB_DIR=../src/libuser/apex/
TYPES_DIR=../src/types/
CACTH_DIR=catch2/
TEST_DIR=.
SRCS=
INCLUDES=-I$(LIB_DIR) -I$(TYPES_DIR) -I$(CACTH_DIR) 
CPP_FLAGS=-std=c++17 -Wall
OBJS=$(SRCS:.cpp=.o)

conformance-testing: 
	$(eval TEST_DIR:=conformance-tests/)
	$(eval SRCS:=$(TEST_DIR)test_process_management.cpp $(shell find $(TYPES_DIR)src/ -name '*.cpp'))
	g++ -DHOST_TESTING $(INCLUDES) $(CPP_FLAGS) $(SRCS) -o conformance-tests.o
