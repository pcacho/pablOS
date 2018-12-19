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

#ifndef _TASK_H
#define _TASK_H

#include <stdint.h>
#include "platform.h"

#define TASK_MAX_NAME_LEN 16
#define TASK_STACK_KEY 0xDEADBEAF

typedef enum {
	E_TASK_RUNNING,
	E_TASK_READY,
	E_TASK_SUSPENDED,
} taskState_t;

// Registers that need to be saved/restored from stack
typedef struct {
	uint32_t ra;
	uint32_t sp;
	uint32_t gp;
	uint32_t tp;
	uint32_t t0;
	uint32_t t1;
	uint32_t t2;
	uint32_t s0;
	uint32_t s1;
	uint32_t a0;
	uint32_t a1;
	uint32_t a2;
	uint32_t a3;
	uint32_t a4;
	uint32_t a5;
	uint32_t a6;
	uint32_t a7;
	uint32_t s2;
	uint32_t s3;
	uint32_t s4;
	uint32_t s5;
	uint32_t s6;
	uint32_t s7;
	uint32_t s8;
	uint32_t s9;
	uint32_t s10;
	uint32_t s11;
	uint32_t t3;
	uint32_t t4;
	uint32_t t5;
	uint32_t t6;
	uint32_t pc;
} contextRegs_t;


// Task Control Block
typedef struct tcb {
	uint32_t regs[32];
	char name[TASK_MAX_NAME_LEN];
	void *function;
	uint32_t id;
	uint32_t *sp;
	uint32_t *base_sp;
	uint32_t stack_size;
	uint32_t priority;
	uint32_t wait_time;
	taskState_t state;
	uint64_t last_run_tick;
	uint64_t creation_tick;
	uint64_t total_run_ticks;
	struct tcb *next;
} tcb_t, *tcbPtr;

int task_init(void);
int task_create(const char *task_name, void (*function), uint8_t priority, uint32_t stack_size);

#endif
