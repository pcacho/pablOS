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
#include <stdlib.h>
#include "uart.h"
#include "queue.h"

#define QUEUE_DEBUG 0

int queue_init(Queue *qp, char *name) {
	*qp = (Queue) malloc(sizeof(Queue_t));
	if (*qp == NULL) {
#if QUEUE_DEBUG
		printf("%s: ERROR unable to allocate space for queue\n\r", __FUNCTION__);
#endif
		return -1;
	}
	(*qp)->head = NULL;
	(*qp)->tail = NULL;
	(*qp)->size = 0;
	strncpy((*qp)->name, name, QUEUE_MAX_NAME_LEN);
#if QUEUE_DEBUG
	printf("%s: initialized %s\n\r", __FUNCTION__, (*qp)->name);
#endif

	return 0;
}

int queue_empty(Queue Q) {
	return Q->head == NULL;
}

void queue_insert(Queue Q, tcb_t *tcb) {
#if QUEUE_DEBUG
	int position;
#endif
	if (queue_empty(Q)) {
		Q->head = tcb;
		Q->tail = tcb;
		Q->size++;
#if QUEUE_DEBUG
		position = 0;
#endif
	} else {
		Q->tail->next = tcb;
		Q->tail = tcb;
#if QUEUE_DEBUG
		position = Q->size;
#endif
		Q->size++;
	}
#if QUEUE_DEBUG
	printf("%s: inserted %s into position=%d\n\r",
			__FUNCTION__, tcb->name, position);
#endif
}

int queue_dequeue(Queue Q, tcb_t **tcb) {
	if (queue_empty(Q)) {
		return -1;
	}
	*tcb = Q->head;
	Q->head = Q->head->next;
	if (Q->head == NULL) {
		Q->tail = NULL;
	}
	Q->size--;

	return 0;
}

#if defined(TEST_BUILD)
int queue_test(void) {
	int ret = 0;
	char name[] = "QueueTest";
	Queue testQ;
	queue_init(&testQ, name);

	// Test 1: make sure empty works
	if (queue_empty(testQ) != 1) {
		printf("%s: Test 1 FAIL\n\r", __FUNCTION__);
		ret = -1;
	} else {
		printf("%s: Test 1 PASS\n\r", __FUNCTION__);
	}

	// Test 2: test insert and non-empty
	tcb_t tcb;
	bzero(&tcb, sizeof(tcb_t));
	strncpy(tcb.name, name, TASK_MAX_NAME_LEN);
	queue_insert(testQ, &tcb);
	if (queue_empty(testQ) != 0) {
		printf("%s: Test 2 FAIL\n\r", __FUNCTION__);
		ret = -1;
	} else {
		printf("%s: Test 2 PASS\n\r", __FUNCTION__);
	}

	// Test 3: dequeue and verify name
	tcb_t *tcb_out;
	queue_dequeue(testQ, &tcb_out);
	if (strncmp(tcb_out->name, name, TASK_MAX_NAME_LEN) != 0) {
		printf("%s: Test 3 FAIL\n\r", __FUNCTION__);
		ret = -1;
	} else {
		printf("%s: Test 3 PASS\n\r", __FUNCTION__);
	}

	// Test 4: make sure empty after dequeue works
	if (queue_empty(testQ) != 1) {
		printf("%s: Test 4 FAIL\n\r", __FUNCTION__);
		ret = -1;
	} else {
		printf("%s: Test 4 PASS\n\r", __FUNCTION__);
	}

	return ret;
}

#endif
