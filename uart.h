/*
 * Copyright 2018 Pablo Cacho
 * Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _UART_H
#define _UART_H

#include <stdint.h>
#include "platform.h"

#define UART0_RX_PIN 16
#define UART0_TX_PIN 17
#define UART_BAUD_115200 138

typedef union {
	uint32_t TXDATA;
	struct {
		uint32_t data : 8;
		uint32_t reserved : 23;
		uint32_t full : 1;
	};
} UART_TXDATA;

typedef union {
	uint32_t RXDATA;
	struct {
		uint32_t data : 8;
		uint32_t rsv0 : 23;
		uint32_t empty : 1;
	};
} UART_RXDATA;

typedef union {
	uint32_t TXCTRL;
	struct {
		uint32_t txen : 1;
		uint32_t nstop : 1;
		uint32_t rsv0 : 14;
		uint32_t txcnt : 3;
		uint32_t rsv1 : 13;
	};
} UART_TXCTRL;

typedef union {
	uint32_t RXCTRL;
	struct {
		uint32_t rxen : 1;
		uint32_t rsv0 : 15;
		uint32_t rxcnt : 3;
		uint32_t rsv1 : 13;
	};
} UART_RXCTRL;

typedef union {
	uint32_t IE;
	struct {
		uint32_t txwm : 1;
		uint32_t rxwm : 1;
		uint32_t rsv0 : 30;
	};
} UART_IE;

typedef union {
	uint32_t DIV;
	struct {
		uint32_t div : 16;
		uint32_t rsv0 : 16;
	};
} UART_DIV;

typedef volatile struct {
	UART_TXDATA TXDATA;
	UART_RXDATA RXDATA;
	UART_TXCTRL TXCTRL;
	UART_RXCTRL RXCTRL;
	UART_IE IE;
	UART_DIV DIV;
} UART_CSR;


void uart_putc(char c);
void uart_puts(char *s);
void uart_init(void);
void uart_printf(char *str, ...);
#endif
