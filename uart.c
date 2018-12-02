#include <stdarg.h>
#include <strings.h>
#include "gpio.h"
#include "uart.h"

#define UART0 (*(UART_CSR*) UART0_CTRL_ADDR)

void uart_putc(char c) {
	while (UART0.TXDATA.full);
	UART0.TXDATA.data = c;
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


}

void uart_uint_to_str(char **buf, uint8_t buf_len, uint32_t val, uint8_t base) {
	char *ptr = &(*buf)[buf_len - 1];
	char hex_digits[] = "0123456789ABCDEF";
	bzero(*buf, buf_len);


	while (val != 0) {
		*--ptr = hex_digits[val % base];
		val = val / base;
	}
	*buf = ptr;
}

void uart_printf(char *str, ...) {
	char *c = &str[0];
	char *s;
	uint32_t val;
	va_list arg;
	char buffer[16];
	char *ptr = &buffer[0];

	va_start(arg, str);
	while(*str != '\0') {

		if (*str != '%') {
			uart_putc(*str);
			str++;
			continue;
		}

		// increment to get format type
		str++;

		switch(*str) {
		case('c'):
			val = va_arg(arg, int);
			uart_putc(val);
			break;
		case('d'):
			val = va_arg(arg, int);
			if (val < 0) {
				uart_putc('-');
			}
			uart_uint_to_str(&ptr, sizeof(buffer), val, 10);
			uart_puts(ptr);
			break;
		case('x'):
		case('X'):
			val = va_arg(arg, int);
			uart_uint_to_str(&ptr, sizeof(buffer), val, 16);
			uart_puts(ptr);
			break;
		case('s'):
			s = va_arg(arg, char *);
			uart_puts(s);
			break;
		}
		str++;
	}

}
