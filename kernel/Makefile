export ROOT=$(CURDIR)/../


OBJS = main.o kernel.o

LIBS	= $(CIRCLEHOME)/lib/libcircle.a $(ROOT)/kernel/core/core.a

include $(ROOT)/misc/common-pi4.mk
include $(ROOT)/misc/common-rules.mk

.deps: 
	@echo "deps"
	$(MAKE) -C $(CURDIR)/core

.PHONY: all clean depsss

clean: kernel-clean
	cd $(CURDIR)/core && $(MAKE) clean




