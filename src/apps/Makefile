ROOT=		../../

LYNGSOEOBJS= lyngsoe/blr_lll_host_service.o \
						 lyngsoe/data_processor_service.o \
						 lyngsoe/diagnosis_service.o \
						 lyngsoe/gps_service.o \
						 lyngsoe/io_blr_service.o \
						 lyngsoe/io_service.o \
						 lyngsoe/output_service.o \
						 lyngsoe/rfid_reader.o

OBJS=	consumer_part.o \
			dummy_part.o \
			fib_part.o \
			test_app.o \
			entry.o

# Append Lyngsoe Objects
OBJS+=LYNGSOEOBJS

all: $(TARGET)

.PHONY: clean all

clean: common-clean

#include $(ROOT)/misc/common-pi4.mk
include $(ROOT)/src/misc/common-rules.mk