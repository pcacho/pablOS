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

#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include "uart.h"
#include "util.h"

void util_memdump(uint32_t *start_addr, uint32_t len) {
	int i;
	int j;
	int first_pass = 1;
	int index = 0;
	char buffer[32];
	int num_iter = len / 4;
	if (len % 4) {
		num_iter++;
	}

	bzero(buffer, sizeof(buffer));

	for (i = 0; i < num_iter; i++) {
		// Print memory address
		if (first_pass) {
			uart_printf("\n\r0x%08X ", (uint32_t) start_addr);
			first_pass = 0;
		}
		uint32_t val = *start_addr++;

		// Print data at memory address
		uart_printf("%08X ", val);

		// Convert data to ASCII
		for (j = 24; j >= 0; j-=8) {
			uint8_t c = (val >> j) & 0xFF;
			buffer[index++] = isalnum(c) ? c : '.';
		}
		buffer[index++] = ' ';

		// formatting
		if (((i + 1) % 4) == 0) {
			uart_printf(" %s\n\r", buffer);
			bzero(buffer, sizeof(buffer));
			index = 0;
			if ((i + 1) < num_iter) {
				uart_printf("0x%08X ", (uint32_t) start_addr);
			}
		}
	}
}
