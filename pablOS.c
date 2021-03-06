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
#include <stdint.h>
#include "encoding.h"
#include "platform.h"
#include "uart.h"
#include "util.h"
#include "task.h"
#include "idle.h"
#include "scheduler.h"
#include "interrupt.h"
#include "queue.h"

static char pablOS_version[] = "\a\n\r\n\rpablOS Version 0.2\n\r";

int main(void) {
	volatile int i;
	printf("%s\n\r", pablOS_version);
	util_memdump((uint32_t*) &pablOS_version[0], 64);

	// Initialize interrupts
	interrupt_init();

#if defined(TEST_BUILD)
	queue_test();
#endif
	// Initialize scheduler
	scheduler_init();

	// Initialize the Task Manager State
	task_init();

	// Initialize Idle Task
	idle_task_init();

	// Start the scheduler
	scheduler_start();

	// Should never reach this spot
	while (1) {
		i++;
	}

	return -1;
}
