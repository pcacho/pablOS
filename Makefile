TARGET = pablOS
ASM_SRCS += context.S mutex.S
C_SRCS += pablOS.c uart.c gpio.c util.c timer.c idle.c task.c queue.c scheduler.c
C_SRCS += interrupt.c synchronization.c
C_SRCS += $(BSP_BASE)/drivers/plic/plic_driver.c
CFLAGS += -O2 -fno-builtin-printf -DNO_INIT
#CFLAGS += -O2 -fno-builtin-printf -DNO_INIT -DTEST_BUILD

BSP_BASE = ../../bsp
include $(BSP_BASE)/env/common.mk
