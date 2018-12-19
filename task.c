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

#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include "timer.h"
#include "uart.h"
#include "scheduler.h"
#include "util.h"
#include "task.h"

#define TASK_STACK_DEBUG 1

// Task Manager State
typedef struct {
	uint8_t number_of_tasks;
	uint8_t next_available_id;
} tms_t;

// Task Manager State
tms_t s_tms;

int task_init(void) {
	s_tms.number_of_tasks = 0;
	s_tms.next_available_id = 0;
}

void task_added(void) {
	s_tms.number_of_tasks++;
	s_tms.next_available_id++;
}

int task_next_available_get() {
	return s_tms.next_available_id;
}

void task_stack_init(uint32_t *ptr, uint32_t sp, uint32_t function) {
	contextRegs_t *cr = (contextRegs_t*) ptr;
	cr->ra = function;
	cr->sp = sp;
	cr->t6 = 0xaaaabbbb;
	cr->pc = function;
}

int task_create(const char *task_name, void (*function), uint8_t priority, uint32_t stack_size) {

	// Allocate TCB
	tcb_t *tcb = (tcb_t*) malloc(sizeof(tcb_t));
	if (tcb == NULL) {
		printf("%s: ERROR unable to allocate space for task=%s\n\r",
				__FUNCTION__, task_name);
		return -1;
	}
	bzero(tcb, sizeof(tcb_t));

	// Allocate space for stack
	tcb->sp = (uint32_t*) malloc(stack_size*4);
	if (tcb->sp == NULL) {
		printf("%s: ERROR unable to allocate stack space for task=%s\n\r",
				__FUNCTION__, task_name);
		return -1;
	}

	// Save base address of thread stack
	tcb->base_sp = tcb->sp;

	// set stack to special key
	int i;
	for (i = 0; i < stack_size; i++) {
		*tcb->sp++ = TASK_STACK_KEY;
	}
	tcb->sp--;
	printf("function_addr=%08X &regs[0]=%08X base_sp=0x%08X sp=0x%08X\n\r",
			(uint32_t) function, (uint32_t)&tcb->regs[0],
			(uint32_t) tcb->base_sp, (uint32_t) tcb->sp);

	// Initialize context registers
	task_stack_init(&tcb->regs[0], (uint32_t) tcb->sp, (uint32_t) function);

	// Initalize TCB
	tcb->function = function;
	tcb->id = task_next_available_get();
	tcb->stack_size = stack_size;
	tcb->priority = priority;
	strncpy(tcb->name, task_name, TASK_MAX_NAME_LEN);
	tcb->state = E_TASK_SUSPENDED;
	tcb->creation_tick = tick_get();

	// Increment task list and task ids
	task_added();

	// Let scheduler know we have a new task so it
	// can be inserted into Queue
	scheduler_new_task(tcb);

	return 0;
}
