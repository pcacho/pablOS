/*
 * Copyright 2018 Pablo Cacho
 *
 * Redistribution and use in source and binary forms,
 * with or without modification, are permitted provided that the following
 * conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors
 * may be used to endorse or promote products derived from this software without
 * specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _CONTEXT_S
#define _CONTEXT_S

#include "encoding.h"
#include "sifive/bits.h"

// Allocate space for main thread
	.global s_rTask
	.data
	.align 2
temp_space: .space 132

	.section      .text
	.align 2
	.global context_init

context_init:
	la t0, temp_space
	sw a0, 0x0(t0) 
	sw x2, 1*REGBYTES(t0)
	sw x3, 2*REGBYTES(t0)
	sw x4, 3*REGBYTES(t0)
	sw x5, 4*REGBYTES(t0)
	sw x6, 5*REGBYTES(t0)
	sw x7, 6*REGBYTES(t0)
	sw x8, 7*REGBYTES(t0)
	sw x9, 8*REGBYTES(t0)
	sw x10, 9*REGBYTES(t0)
	sw x11, 10*REGBYTES(t0)
	sw x12, 11*REGBYTES(t0)
	sw x13, 12*REGBYTES(t0)
	sw x14, 13*REGBYTES(t0)
	sw x15, 14*REGBYTES(t0)
	sw x16, 15*REGBYTES(t0)
	sw x17, 16*REGBYTES(t0)
	sw x18, 17*REGBYTES(t0)
	sw x19, 18*REGBYTES(t0)
	sw x20, 19*REGBYTES(t0)
	sw x21, 20*REGBYTES(t0)
	sw x22, 21*REGBYTES(t0)
	sw x23, 22*REGBYTES(t0)
	sw x24, 23*REGBYTES(t0)
	sw x25, 24*REGBYTES(t0)
	sw x26, 25*REGBYTES(t0)
	sw x27, 26*REGBYTES(t0)
	sw x28, 27*REGBYTES(t0)
	sw x29, 28*REGBYTES(t0)
	sw x30, 29*REGBYTES(t0)
	sw x31, 30*REGBYTES(t0)
	ret

	.section .text
	.global context_restore
context_restore: 
	addi sp, a0, 0
	// ra
	lw x1, 0x0*REGBYTES(sp)

	// gp
	//lw x3, 2*REGBYTES(sp)

	// tp
	//lw x4, 3*REGBYTES(sp)
	// t0
	lw x5, 4*REGBYTES(sp)
	// t1
	lw x6, 5*REGBYTES(sp)
	// t2
	lw x7, 6*REGBYTES(sp)
	// s0
	lw x8, 7*REGBYTES(sp)
	// s1
	lw x9, 8*REGBYTES(sp)
	// sp
	lw x10, 9*REGBYTES(sp)
	// a1
	lw x11, 10*REGBYTES(sp)
	// a2
	lw x12, 11*REGBYTES(sp)
	// a3
	lw x13, 12*REGBYTES(sp)
	// a4
	lw x14, 13*REGBYTES(sp)
	// a5
	lw x15, 14*REGBYTES(sp)
	// a6
	lw x16, 15*REGBYTES(sp)
	// a7
	lw x17, 16*REGBYTES(sp)
	// s2
	lw x18, 17*REGBYTES(sp)
	// s3
	lw x19, 18*REGBYTES(sp)
	// s4
	lw x20, 19*REGBYTES(sp)
	// s5
	lw x21, 20*REGBYTES(sp)
	// s6
	lw x22, 21*REGBYTES(sp)
	// s7
	lw x23, 22*REGBYTES(sp)
	// s8
	lw x24, 23*REGBYTES(sp)
	// s9
	lw x25, 24*REGBYTES(sp)
	// s10
	lw x26, 25*REGBYTES(sp)
	// s11
	lw x27, 26*REGBYTES(sp)
	// t3
	lw x28, 27*REGBYTES(sp)
	// t4
	lw x29, 28*REGBYTES(sp)
	// t5
	lw x30, 29*REGBYTES(sp)
	// t6
	lw x31, 30*REGBYTES(sp)

	// program counter is in offset 31
	lw t0, 31*REGBYTES(sp)
	csrw mepc, t0
	// sp
	lw x2, 1*REGBYTES(sp)
	li      t0, 0x1880
	csrs    mstatus, t0
	mret

	.section      .text
	.align 2
	.global context_isr
context_isr:
	// Check to see if interrupt is timer based
	li t1, 0x80000007
	csrr t0, mcause
	bne t0, t1, _no_timer_int
	// if it's a timer interrupt save context immediately
	// then load "main thread" registers (which don't get saved)
	lw t0, s_rTask
	addi t1, sp, 0
	sw x1, 0x0(t0)
	sw t1, 1*REGBYTES(t0)
	sw x3, 2*REGBYTES(t0)
	sw x4, 3*REGBYTES(t0)
	sw x5, 4*REGBYTES(t0)
	sw x6, 5*REGBYTES(t0)
	sw x7, 6*REGBYTES(t0)
	sw x8, 7*REGBYTES(t0)
	sw x9, 8*REGBYTES(t0)
	sw x10, 9*REGBYTES(t0)
	sw x11, 10*REGBYTES(t0)
	sw x12, 11*REGBYTES(t0)
	sw x13, 12*REGBYTES(t0)
	sw x14, 13*REGBYTES(t0)
	sw x15, 14*REGBYTES(t0)
	sw x16, 15*REGBYTES(t0)
	sw x17, 16*REGBYTES(t0)
	sw x18, 17*REGBYTES(t0)
	sw x19, 18*REGBYTES(t0)
	sw x20, 19*REGBYTES(t0)
	sw x21, 20*REGBYTES(t0)
	sw x22, 21*REGBYTES(t0)
	sw x23, 22*REGBYTES(t0)
	sw x24, 23*REGBYTES(t0)
	sw x25, 24*REGBYTES(t0)
	sw x26, 25*REGBYTES(t0)
	sw x27, 26*REGBYTES(t0)
	sw x28, 27*REGBYTES(t0)
	sw x29, 28*REGBYTES(t0)
	sw x30, 29*REGBYTES(t0)
	sw x31, 30*REGBYTES(t0)
	csrr t1, mepc
	sw t1, 31*REGBYTES(t0)

_no_timer_int:
	csrr a0, mcause
	csrr a1, mepc
	mv a2, sp
	la t0, temp_space

	// restore main thread registers and call isr
	LOAD x1, 0x0(t0)
	LOAD x2, 1*REGBYTES(t0)
	LOAD x3, 2*REGBYTES(t0)
	LOAD x4, 3*REGBYTES(t0)

	call handle_m_time_interrupt
	// this should never return
big_error:
1:
	j 1b

#endif
