/*
 * Copyright 2018 Pablo Cacho Redistribution and use in source and binary forms,
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
