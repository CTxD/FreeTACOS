export ROOT=$(CURDIR)/../
export CIRCLEHOME=$(ROOT)/aarch/rasp4

include $(CIRCLEHOME)/Rules.mk

all: .deps $(TARGET).img 

$(TARGET).img: $(OBJS) $(LIBS) $(CIRCLEHOME)/circle.ld
	@echo "  LD    bin/$(TARGET).elf"
	@mkdir -p bin
	@$(LD) -o bin/$(TARGET).elf -Map bin/$(TARGET).map --section-start=.init=$(LOADADDR) \
		-T $(CIRCLEHOME)/circle.ld $(CRTBEGIN) $(OBJS) \
		--start-group $(LIBS) $(EXTRALIBS) --end-group $(CRTEND)
	@echo "  DUMP  bin/$(TARGET).lst"
	@$(PREFIX)objdump -d bin/$(TARGET).elf | $(PREFIX)c++filt > bin/$(TARGET).lst
	@echo "  COPY  bin/$(TARGET).img"
	@$(PREFIX)objcopy bin/$(TARGET).elf -O binary bin/$(TARGET).img
	@echo -n "  WC    bin/$(TARGET).img => "
	@wc -c < bin/$(TARGET).img
	
kernel-clean:
	rm -rf bin/ *.o *.a *.elf *.lst *.img *.hex *.cir *.map *~ $(EXTRACLEAN)