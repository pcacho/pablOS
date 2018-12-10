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
#include "queue.h"
#include "uart.h"
#include "task.h"
#include "scheduler.h"

extern void context_restore(uint32_t sp);
// Ready Queue fed by:
// Fast Service Queue
// Event Queue
// Time tabled Queue
// Base Level Queue

// Ready Queue
Queue s_readyQ;
Queue s_runningQ;

#define QUEUE_NAME_READY "ReadyQueue"
#define QUEUE_NAME_RUNNING "RunningQueue"

int scheduler_init(void) {
	int ret;
	ret = queue_init(&s_readyQ, QUEUE_NAME_READY);
	if (ret != 0) {
		printf("%s: Scheduler failed to initialize\n\r", __FUNCTION__);
	} else {
		printf("%s: Scheduler initialized\n\r", __FUNCTION__);
	}

	ret = queue_init(&s_runningQ, QUEUE_NAME_RUNNING);
	if (ret != 0) {
		printf("%s: Scheduler failed to initialize\n\r", __FUNCTION__);
	} else {
		printf("%s: Scheduler initialized\n\r", __FUNCTION__);
	}

	return 0;
}

void scheduler_new_task(tcb_t *tcb) {
	queue_insert(s_readyQ, tcb);
}

int scheduler(void) {
	tcb_t *tcb;

	queue_dequeue(s_readyQ, &tcb);
	context_restore((uint32_t) tcb->sp);

}
