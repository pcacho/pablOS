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

#include "task.h"
#include "idle.h"
#include "uart.h"

const char idle_task_name[] = "IdleTask";
const uint8_t idle_task_priority = 255;
const uint8_t idle_task_stack_size = 64;

void *idle_task(void) {
	// reset watchdog counter
	// if the uart gets a queue, flush logs here
	// check stack limits being approached by tasks
	// -> memset stack with known data and then calculate usage accordingly
	// change power modes?
	// calculate utilization of each task
	// toggle led on idle task entry
	// print size of malloc'ed memory
	volatile int i;
	volatile int j;
	volatile int c;
	while(1) {
		for(i = 'a'; i <= 'z'; i++) {
			uart_printf("%c", (char) i);
			for (j = 0; j < 10000; j++) {
				c++;
			}
		}
	}
}

int idle_task_init(void) {
	if (task_create(idle_task_name, &idle_task,
				idle_task_priority, idle_task_stack_size) != 0) {
		uart_printf("%s: ERROR unable to initialize task=%s\n\r",
				__FUNCTION__, idle_task_name);
		return -1;
	}
	uart_printf("%s: Successfully added %s\n\r", __FUNCTION__, idle_task_name);

	return 0;
}
