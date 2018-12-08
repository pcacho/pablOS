TARGET = pablOS
ASM_SRCS += context.S
C_SRCS += pablOS.c uart.c gpio.c util.c timer.c idle.c task.c queue.c scheduler.c
CFLAGS += -O2 -fno-builtin-printf -DNO_INIT

BSP_BASE = ../../bsp
include $(BSP_BASE)/env/common.mk
