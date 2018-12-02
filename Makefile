TARGET = pablOS
C_SRCS += pablOS.c uart.c gpio.c util.c
CFLAGS += -O2 -fno-builtin-printf -DNO_INIT

BSP_BASE = ../../bsp
include $(BSP_BASE)/env/common.mk
