# Makefile generated by the project manager
#


## core information

PRJ_FILE       = FM130.wpj
ifeq ($(wildcard Makefile),)
PRJ_DIR        = ..
else
PRJ_DIR        = .
endif
PRJ_TYPE       = vxApp
PRJ_OBJS       = hwSysALib.o list.o fc_api.o fc_demo.o hba.o hba_time.o hw.o
BUILD_SPEC     = PPC603gnu
TGT_DIR        = $(WIND_BASE)/target




## build-configuration info

ifeq ($(BUILD_SPEC),PPC603gnu)
CPU              = PPC603
TOOL             = gnu
TOOL_FAMILY      = gnu
DEFAULT_RULE     = FM130.out
endif

include $(TGT_DIR)/h/make/defs.project

## build-configuration info

ifeq ($(BUILD_SPEC),PPC603gnu)
AR               = arppc
AS               = ccppc
CC               = ccppc
CC_ARCH_SPEC     = -mcpu=603 -mstrict-align
CFLAGS           = -g -mcpu=603 -mstrict-align -ansi -fno-builtin -I. -I$(WIND_BASE)/target/h/ -I$(WIND_BASE)/target/h/drv/pci -DCPU=PPC603 -DTOOL_FAMILY=gnu -DTOOL=gnu -mlongcall
CFLAGS_AS        = -g -mcpu=603 -mstrict-align -ansi -fno-builtin -P -xassembler-with-cpp -I. -I$(WIND_BASE)/target/h/ -DCPU=PPC603 -DTOOL_FAMILY=gnu -DTOOL=gnu
CPP              = ccppc -E -P
LD               = ldppc
LDDEPS           = 
LDFLAGS          = -X -N
LD_PARTIAL       = ccppc -r -nostdlib -Wl,-X
LD_PARTIAL_FLAGS = -X -r
NM               = nmppc
OPTION_DEFINE_MACRO = -D
OPTION_DEPEND    = -M -w
OPTION_GENERATE_DEPENDENCY_FILE = -MD
OPTION_INCLUDE_DIR = -I
OPTION_LANG_C    = -xc
OPTION_UNDEFINE_MACRO = -U
POST_BUILD_RULE  = cp ./FM130.out Z:\vmshare\Firmware\PPC603gnu
PRJ_LIBS         = 
SIZE             = sizeppc
TOOL_FAMILY      = gnu
endif

# override make definitions only below this line


# override make definitions only above this line
include $(TGT_DIR)/h/make/rules.project



## build-configuration info

ifeq ($(BUILD_SPEC),PPC603gnu)
hwSysALib.o:
	$(AS) -g -mcpu=603 -mstrict-align -ansi -fno-builtin -P -xassembler-with-cpp -I. -I$(WIND_BASE)/target/h/ -DCPU=PPC603 -DTOOL_FAMILY=gnu -DTOOL=gnu -c $(PRJ_DIR)/hwSysALib.s -o hwSysALib.o
list.o:
	$(CC) -g -mcpu=603 -mstrict-align -ansi -fno-builtin -I. -I$(WIND_BASE)/target/h/ -I$(WIND_BASE)/target/h/drv/pci -DCPU=PPC603 -DTOOL_FAMILY=gnu -DTOOL=gnu -mlongcall -c $(PRJ_DIR)/list.c
fc_api.o:
	$(CC) -g -mcpu=603 -mstrict-align -ansi -fno-builtin -I. -I$(WIND_BASE)/target/h/ -I$(WIND_BASE)/target/h/drv/pci -DCPU=PPC603 -DTOOL_FAMILY=gnu -DTOOL=gnu -mlongcall -c $(PRJ_DIR)/fc_api.c
fc_demo.o:
	$(CC) -g -mcpu=603 -mstrict-align -ansi -fno-builtin -I. -I$(WIND_BASE)/target/h/ -I$(WIND_BASE)/target/h/drv/pci -DCPU=PPC603 -DTOOL_FAMILY=gnu -DTOOL=gnu -mlongcall -c $(PRJ_DIR)/fc_demo.c
hba.o:
	$(CC) -g -mcpu=603 -mstrict-align -ansi -fno-builtin -I. -I$(WIND_BASE)/target/h/ -I$(WIND_BASE)/target/h/drv/pci -DCPU=PPC603 -DTOOL_FAMILY=gnu -DTOOL=gnu -mlongcall -c $(PRJ_DIR)/hba.c
hba_time.o:
	$(CC) -g -mcpu=603 -mstrict-align -ansi -fno-builtin -I. -I$(WIND_BASE)/target/h/ -I$(WIND_BASE)/target/h/drv/pci -DCPU=PPC603 -DTOOL_FAMILY=gnu -DTOOL=gnu -mlongcall -c $(PRJ_DIR)/hba_time.c
hw.o:
	$(CC) -g -mcpu=603 -mstrict-align -ansi -fno-builtin -I. -I$(WIND_BASE)/target/h/ -I$(WIND_BASE)/target/h/drv/pci -DCPU=PPC603 -DTOOL_FAMILY=gnu -DTOOL=gnu -mlongcall -c $(PRJ_DIR)/hw.c
endif


## dependencies

hwSysALib.o: $(PRJ_DIR)/hwSysALib.s

list.o: $(PRJ_DIR)/list.c \
	$(WIND_BASE)/host/$(WIND_HOST_TYPE)/lib/gcc-lib/powerpc-wrs-vxworks/gcc-2.96/include/stddef.h \
	$(WIND_BASE)/host/$(WIND_HOST_TYPE)/lib/gcc-lib/powerpc-wrs-vxworks/gcc-2.96/include/stdarg.h \
	$(WIND_BASE)/host/$(WIND_HOST_TYPE)/lib/gcc-lib/powerpc-wrs-vxworks/gcc-2.96/include/va-ppc.h \
	$(PRJ_DIR)/list.h

fc_api.o: $(PRJ_DIR)/fc_api.c \
	$(WIND_BASE)/host/$(WIND_HOST_TYPE)/lib/gcc-lib/powerpc-wrs-vxworks/gcc-2.96/include/stddef.h \
	$(PRJ_DIR)/hba.h \
	$(PRJ_DIR)/list.h \
	$(PRJ_DIR)/fc_utility.h \
	$(PRJ_DIR)/fc_api.h

fc_demo.o: $(PRJ_DIR)/fc_demo.c \
	$(PRJ_DIR)/fc_demo.h \
	$(PRJ_DIR)/hba.h \
	$(WIND_BASE)/host/$(WIND_HOST_TYPE)/lib/gcc-lib/powerpc-wrs-vxworks/gcc-2.96/include/stddef.h \
	$(PRJ_DIR)/list.h \
	$(PRJ_DIR)/fc_utility.h

hba.o: $(PRJ_DIR)/hba.c \
	$(WIND_BASE)/host/$(WIND_HOST_TYPE)/lib/gcc-lib/powerpc-wrs-vxworks/gcc-2.96/include/stddef.h \
	$(WIND_BASE)/host/$(WIND_HOST_TYPE)/lib/gcc-lib/powerpc-wrs-vxworks/gcc-2.96/include/stdarg.h \
	$(WIND_BASE)/host/$(WIND_HOST_TYPE)/lib/gcc-lib/powerpc-wrs-vxworks/gcc-2.96/include/va-ppc.h \
	$(PRJ_DIR)/hba.h \
	$(PRJ_DIR)/list.h \
	$(PRJ_DIR)/fc_utility.h \
	$(PRJ_DIR)/hw.h

hba_time.o: $(PRJ_DIR)/hba_time.c \
	$(WIND_BASE)/host/$(WIND_HOST_TYPE)/lib/gcc-lib/powerpc-wrs-vxworks/gcc-2.96/include/stddef.h \
	$(PRJ_DIR)/hba_time.h \
	$(PRJ_DIR)/hba.h \
	$(PRJ_DIR)/list.h \
	$(PRJ_DIR)/fc_utility.h \
	$(PRJ_DIR)/hw.h

hw.o: $(PRJ_DIR)/hw.c \
	$(WIND_BASE)/host/$(WIND_HOST_TYPE)/lib/gcc-lib/powerpc-wrs-vxworks/gcc-2.96/include/stddef.h \
	$(PRJ_DIR)/hw.h \
	$(PRJ_DIR)/hba.h \
	$(PRJ_DIR)/list.h \
	$(PRJ_DIR)/fc_utility.h


## user defined rules

