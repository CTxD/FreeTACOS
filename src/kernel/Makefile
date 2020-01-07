export ROOT=$(CURDIR)/../../
export CORE=$(ROOT)/src/kernel/core
export CIRCLELIB=$(ROOT)/aarch/circle-stdlib

# ---  Target dependent and should be changed w.r.t architecture
OBJS = main.o \
		$(CORE)/boot.o \
		$(CORE)/tacoskernel.o \
		$(ROOT)/src/kernel/arch/rasp4/arch.o

include $(CIRCLELIB)/Config.mk

CIRCLEHOME = $(CIRCLELIB)/libs/circle
NEWLIBDIR = $(CIRCLELIB)/install/$(NEWLIB_ARCH)

INCLUDE += -I $(ROOT)/src/kernel/include
INCLUDE += -I $(ROOT)/src/types
INCLUDE += -I $(ROOT)/../boost_1_71_0
INCLUDE += -I $(ROOT)/src/types/include
INCLUDE += -I $(ROOT)/src/libuser/apex
INCLUDE += -I $(ROOT)/src/kernel/core/process

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
	cd $(CURDIR)/arch/rasp4 && $(MAKE) clean