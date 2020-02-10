ROOT=		../../../

OBJS=		arinc_module.o \
			channel.o \
			module_hm_table.o \
			multipartition_hm_table.o \
			partition_hm_table.o \
			partition_schedule.o \
			partition.o \
			queuing_port.o \
			system_error 

all: $(TARGET)

.PHONY: clean all

clean: common-clean

#include $(ROOT)/misc/common-pi4.mk
include $(ROOT)/src/misc/common-rules.mk