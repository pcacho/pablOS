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
