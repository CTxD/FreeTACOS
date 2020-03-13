export ROOT=$(CURDIR)/../../
export KERNEL=$(ROOT)/src/kernel
export CORE=$(ROOT)/src/kernel/core
export APPS=$(ROOT)/src/apps
export TYPES=$(ROOT)/src/types
export CIRCLELIB=$(ROOT)/aarch/circle-stdlib
export APEX=$(ROOT)/src/libuser

# ---  Target dependent and should be changed w.r.t architecture
OBJS = main.o \
		$(CORE)/boot.o \
		$(CORE)/tacoskernel.o \
		$(ROOT)/src/kernel/arch/rasp4/arch.o \
        $(TYPES)/src/process.o \
        $(TYPES)/src/partition.o \
        $(TYPES)/src/arinc_module.o \
        $(TYPES)/src/multipartition_hm_table.o \
        $(TYPES)/src/module_hm_table.o \
        $(TYPES)/src/partition_hm_table.o \
		$(TYPES)/src/core_schedule.o \
		$(TYPES)/src/partition_schedule.o \
		$(ROOT)/src/kernel/core/scheduling/partitionscheduling.o \
		$(CORE)/apex_kernel.o \
		$(TYPES)/src/task.o \
		$(TYPES)/src/queuing_port.o \
		$(APPS)/test_app.o

include $(CIRCLELIB)/Config.mk

CIRCLEHOME = $(CIRCLELIB)/libs/circle
NEWLIBDIR = $(CIRCLELIB)/install/$(NEWLIB_ARCH)

INCLUDE += -I $(ROOT)/src/kernel/include
INCLUDE += -I $(ROOT)/src/types
INCLUDE += -I $(ROOT)/../boost_1_72_0
INCLUDE += -I $(ROOT)/src/types/include
INCLUDE += -I $(ROOT)/src/libuser/apex
INCLUDE += -I $(ROOT)/src/kernel/core/process
INCLUDE += -I $(ROOT)/src/kernel/core/schedulig
INCLUDE += -I $(APPS)/
INCLUDE += -I $(ROOT)/src/kernel/core/
INCLUDE += -I $(ROOT)/src/kernel
INCLUDE += -I $(ROOT)/src
INCLUDE += -I $(APPS)


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