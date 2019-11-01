export ROOT=$(CURDIR)/../../
export CORE=$(ROOT)/src/kernel/core

# ---  Target dependent and should be changed w.r.t architecture
OBJS = main.o \
		$(CORE)/boot.o \
		$(CORE)/tacoskernel.o \
		$(ROOT)/src/kernel/arch/rasp4/arch.o

LIBS	= $(CIRCLEHOME)/lib/libcircle.a

include $(ROOT)/src/misc/common-pi4.mk
include $(ROOT)/src/misc/common-rules.mk

# ---
.deps: 
	@echo "deps"
	cd $(ROOT)/aarch/rasp4 && ./makeall

.PHONY: all clean deps

clean: kernel-clean
	cd $(CURDIR)/core && $(MAKE) clean
	cd $(CURDIR)/arch/rasp4 && $(MAKE) clean