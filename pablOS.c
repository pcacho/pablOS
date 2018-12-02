#include <stdint.h>
#include "platform.h"
#include "uart.h"
#include "util.h"

static char pablOS_version[] = "\a\n\r\n\rpablOS Version 0.1\n\r";

int main(void) {
	// Make sure the HFROSC is on before the next line:
	PRCI_REG(PRCI_HFROSCCFG) |= ROSC_EN(1);
	// Run off 16 MHz Crystal for accuracy. Note that the
	// first line is
	PRCI_REG(PRCI_PLLCFG) = (PLL_REFSEL(1) | PLL_BYPASS(1));
	PRCI_REG(PRCI_PLLCFG) |= (PLL_SEL(1));
	// Turn off HFROSC to save power
	PRCI_REG(PRCI_HFROSCCFG) &= ~(ROSC_EN(1));

	uart_init();

	// UART needs settling time
	volatile int i=0;
	while(i < 10000){i++;}

	uart_puts(pablOS_version);
	uart_puts("\n\r");
	util_memdump((uint32_t*) &pablOS_version[0], 64);

}
