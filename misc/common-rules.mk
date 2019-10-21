ifneq ($(TARGET),) 
$(TARGET): $(ADEPS) $(OBJS)
	$(LD) $(LDFLAGS) $(LDOPTS) -r $(LIBS) $(OBJS) -o $(TARGET)
endif

common-clean:
	$(RM) $(TARGET) $(LO_TARGET) $(LO_DEPS) $(LO_OBJS) $(OBJS)

# --- Target dependent
PREFIX ?= aarch64-elf-

CC	= $(PREFIX)gcc
CPP	= $(PREFIX)g++
AS	= $(CC)
LD	= $(PREFIX)ld
AR	= $(PREFIX)ar

ARCH	?= -DAARCH=64 -march=armv8-a -mtune=cortex-a72 -mlittle-endian -mcmodel=small

INCLUDE	+= -I $(ROOT)/kernel/include

CFLAGS	+= $(ARCH) -Wall -fsigned-char -ffreestanding $(DEFINE) $(INCLUDE) $(OPTIMIZE) -g
CPPFLAGS+= $(CFLAGS) -std=c++17

# --- Target dependent

%.o: %.cpp
	@echo "  $(CPP)  $@ "
	@$(CPP) $(CPPFLAGS) -c -o $@ $<
