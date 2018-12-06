TARGET = pablOS
C_SRCS += pablOS.c uart.c gpio.c util.c timer.c idle.c task.c
CFLAGS += -O2 -fno-builtin-printf -DNO_INIT

BSP_BASE = ../../bsp
include $(BSP_BASE)/env/common.mk
