#
#  RTEMS_MAKEFILE_PATH is typically set in an environment variable
#

PGM=${ARCH}/led.exe

# optional managers required
MANAGERS=all

# C source names
CSRCS = led.c
COBJS = $(CSRCS:%.c=${ARCH}/%.o)

include $(RTEMS_MAKEFILE_PATH)/Makefile.inc
include $(RTEMS_CUSTOM)
include $(PROJECT_ROOT)/make/leaf.cfg

OBJS= $(COBJS) $(CXXOBJS) $(ASOBJS) -lm

all:    ${ARCH} $(PGM)

$(PGM): $(OBJS)
	$(make-exe)
