export ROOT=$(CURDIR)/../../
export KERNEL=$(ROOT)/src/kernel
export CORE=$(ROOT)/src/kernel/core
export APPS=$(ROOT)/src/apps
export TYPES=$(ROOT)/src/types
export CIRCLELIB=$(ROOT)/aarch/circle-stdlib
export APEX=$(ROOT)/src/libuser/apex/

# Lyngsø System app objects
LOBJS = $(APPS)/lyngsoe/blr_lll_host_service.o \
				$(APPS)/lyngsoe/data_processor_service.o \
				$(APPS)/lyngsoe/io_blr_service.o \
				$(APPS)/lyngsoe/rfid_reader.o

# ---  Target dependent and should be changed w.r.t architecture

# Apex Objects
APEXOBJS = $(APEX)/src/apex_blackboard.o \
		$(APEX)/src/apex_queuing_port.o \
		$(APEX)/src/apex_mutex.o \
		$(APEX)/src/apex_event.o \
		$(APEX)/src/apex_buffer.o

# App Objects
APPOBJS = $(APPS)/test_app.o \
		$(APPS)/entry.o

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
		$(KERNEL)/arch/rasp4/arch.o \
		$(CORE)/scheduling/partitionscheduling.o \
		$(CORE)/scheduling/process_schedule.o \
		$(CORE)/apex_kernel.o \
		$(TYPES)/src/task.o \
		$(TYPES)/src/queuing_port.o

OBJS += $(GENERALOBJS) $(TYPEOBJS) $(APEXOBJS) $(APPOBJS) $(LOBJS)


include $(CIRCLELIB)/Config.mk

CIRCLEHOME = $(CIRCLELIB)/libs/circle
NEWLIBDIR = $(CIRCLELIB)/install/$(NEWLIB_ARCH)

INCLUDE += -I $(ROOT)/src/kernel/include
INCLUDE += -I $(APPS)
INCLUDE += -I $(CORE)/scheduling
INCLUDE += -I $(ROOT)/../boost_1_71_0
INCLUDE += -I $(ROOT)/src/types/include
INCLUDE += -I $(APEX)/include
INCLUDE += -I $(ROOT)/src/kernel/core/scheduling
INCLUDE += -I $(APPS)/
INCLUDE += -I $(ROOT)/src/kernel/core/
INCLUDE += -I $(KERNEL)/
INCLUDE += -I $(CORE)/scheduling
INCLUDE += -I $(ROOT)/src
INCLUDE += -I $(ROOT)/aarch/circle-stdlib/libs/circle/include/circle/sched/




CPPFLAGS+= $(CFLAGS) -std=c++17 -O0

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
	cd $(CURDIR)/core/scheduling && $(MAKE) clean
	cd $(CURDIR)/../apps && $(MAKE) clean
	cd $(CURDIR)/../types/src && $(MAKE) clean
	cd $(CURDIR)/arch/rasp4 && $(MAKE) clean
	cd $(APEX)/src && $(MAKE) clean

