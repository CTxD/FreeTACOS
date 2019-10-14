ifneq ($(TARGET),) 
$(TARGET): $(DEPS) $(OBJS)
	$(LD) $(LDFLAGS) $(LDOPTS) -r $(LO_DEPS) $(OBJS) -o $(TARGET)
endif

common-clean:
	$(RM) $(TARGET) $(LO_TARGET) $(LO_DEPS) $(LO_OBJS) $(OBJS)

PREFIX ?= aarch64-elf-

CC	= $(PREFIX)gcc
CPP	= $(PREFIX)g++
AS	= $(CC)
LD	= $(PREFIX)ld
AR	= $(PREFIX)ar

ARCH	?= -DAARCH=64 -march=armv8-a -mtune=cortex-a72 -mlittle-endian -mcmodel=small

CFLAGS	+= $(ARCH) -Wall -fsigned-char -ffreestanding $(DEFINE) $(INCLUDE) $(OPTIMIZE) -g
CPPFLAGS+= $(CFLAGS) -std=c++14



%.o: %.cpp
	@echo "  $(CPP)   $@"
	@$(CPP) $(CPPFLAGS) -c -o $@ $<
