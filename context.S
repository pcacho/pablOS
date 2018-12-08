#ifndef _CONTEXT_S
#define _CONTEXT_S

#include "encoding.h"
#include "sifive/bits.h"

	.section .text
	.globl context_restore
context_restore: 
	addi sp, x10, 0
	lw x1, 4(sp)
	addi sp, sp, 8
	ret

#endif
