export ROOT=$(CURDIR)/../../
export KERNEL=$(ROOT)/src/kernel
export CORE=$(ROOT)/src/kernel/core
export APPS=$(ROOT)/src/apps
export TYPES=$(ROOT)/src/types
export CIRCLELIB=$(ROOT)/aarch/circle-stdlib
export APEX=$(ROOT)/src/libuser/apex/

# ---  Target dependent and should be changed w.r.t architecture

# Apex Objects
APEXOBJS = $(APEX)/src/apex_blackboard.o \
		$(APEX)/src/apex_mutex.o \
		$(APEX)/src/apex_event.o \
		$(APEX)/src/apex_buffer.o

# App Objects
APPOBJS = $(APPS)/test_app.o

# Type Objects
TYPEOBJS = $(TYPES)/src/process.o \
		$(TYPES)/src/partition.o \
		$(TYPES)/src/arinc_module.o \
		$(TYPES)/src/multipartition_hm_table.o \
		$(TYPES)/src/module_hm_table.o \
		$(TYPES)/src/partition_hm_table.o \
		$(TYPES)/src/core_schedule.o \
		$(TYPES)/src/partition_schedule.o

# General Objects
GENERALOBJS = main.o \
		$(CORE)/boot.o \
		$(CORE)/tacoskernel.o \
		$(KERNEL)/generated_arinc_module.o \
		$(ROOT)/src/kernel/arch/rasp4/arch.o \
		$(ROOT)/src/kernel/core/scheduling/partitionscheduling.o \
		$(ROOT)/src/kernel/core/scheduling/process_schedule.o \
		$(CORE)/apex_kernel.o \
		$(TYPES)/src/task.o \
		$(TYPES)/src/queuing_port.o

OBJS += $(GENERALOBJS) $(TYPEOBJS) $(APEXOBJS) $(APPOBJS)

include $(CIRCLELIB)/Config.mk

CIRCLEHOME = $(CIRCLELIB)/libs/circle
NEWLIBDIR = $(CIRCLELIB)/install/$(NEWLIB_ARCH)

INCLUDE += -I $(ROOT)/src/kernel/include
INCLUDE += -I $(ROOT)/src/types/include
INCLUDE += -I $(APEX)/include
INCLUDE += -I $(ROOT)/src/kernel/core/scheduling
INCLUDE += -I $(APPS)/
INCLUDE += -I $(ROOT)/src/kernel/core/
INCLUDE += -I $(KERNEL)/
INCLUDE += -I $(CORE)/scheduling
INCLUDE += -I $(ROOT)/src
INCLUDE += -I $(ROOT)/aarch/circle-stdlib/libs/circle/include/circle/sched/


CPPFLAGS+= $(CFLAGS) -std=c++17

include $(CIRCLEHOME)/Rules.mk

CFLAGS += -I "$(NEWLIBDIR)/include" -I $(STDDEF_INCPATH) -I $(CIRCLELIB)/include
LIBS := "$(NEWLIBDIR)/lib/libm.a" "$(NEWLIBDIR)/lib/libc.a" "$(NEWLIBDIR)/lib/libcirclenewlib.a" \
 	$(CIRCLEHOME)/addon/SDCard/libsdcard.a \
  $(CIRCLEHOME)/lib/usb/libusb.a \
 	$(CIRCLEHOME)/lib/input/libinput.a \
 	$(CIRCLEHOME)/lib/fs/fat/libfatfs.a \
 	$(CIRCLEHOME)/lib/fs/libfs.a \
  $(CIRCLEHOME)/lib/net/libnet.a \
  $(CIRCLEHOME)/lib/sched/libsched.a \
  $(CIRCLEHOME)/lib/libcircle.a

# ---

.PHONY: all clean

clean all:
	rm -f *.o *.a *.elf *.lst *.img *.hex *.cir *.map *~ $(EXTRACLEAN)
	cd $(CURDIR)/core && $(MAKE) clean
	cd $(CURDIR)/../apps && $(MAKE) clean
	cd $(CURDIR)/../types/src && $(MAKE) clean
	cd $(CURDIR)/arch/rasp4 && $(MAKE) clean
	cd $(APEX)/ clean
