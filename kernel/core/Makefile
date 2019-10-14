ROOT=		../../

TARGET=	core.a

OBJS=		partition.o \
			error.o \
			boot.o \
			scheduling.o \
			time.o

all: $(TARGET)

.PHONY: clean all

clean: common-clean

#include $(ROOT)/misc/common-pi4.mk
include $(ROOT)/misc/common-rules.mk
