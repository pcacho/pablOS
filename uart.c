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

#include <stdarg.h>
#include <strings.h>
#include <string.h>
#include <ctype.h>
#include "gpio.h"
#include "synchronization.h"
#include "uart.h"

#define UART0 (*(UART_CSR*) UART0_CTRL_ADDR)
mutex_t s_mutex_uart0;

void uart_putc(char c) {
	mutex_acquire(&s_mutex_uart0);
	while (UART0.TXDATA.full);
	UART0.TXDATA.data = c;
	mutex_release(&s_mutex_uart0);
}

void uart_puts(char *s) {
	while (*s != '\0'){
		uart_putc(*s++);
	}
}

void uart_init(void) {

	// Configure UART0 GPIOs
	gpio_output_set(UART0_TX_PIN, 1);
	gpio_output_set(UART0_RX_PIN, 1);

	gpio_output_enable(UART0_TX_PIN, 1);
	gpio_output_enable(UART0_RX_PIN, 1);

	// SiFive HiFive1 Getting Started Guide 1.0.2
	// Table 7.1: HiFive1 GPIO Offset to Board Pin Number
	gpio_iof_sel(UART0_TX_PIN, 0);
	gpio_iof_sel(UART0_RX_PIN, 0);

	gpio_iof_enable(UART0_TX_PIN, 1);
	gpio_iof_enable(UART0_RX_PIN, 1);

	// Configure baud rate and enable TX/RX
	UART0.DIV.div = UART_BAUD_115200;
	UART0.TXCTRL.txen = 1;
	UART0.RXCTRL.rxen = 1;

	// Initialize mutex
	mutex_init(&s_mutex_uart0);

	// TODO: add delays in timer.c
	// UART needs settling time
	volatile int i=0;
	while (i < 10000){
		i++;
	}
}
