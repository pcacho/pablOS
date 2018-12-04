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

#include "gpio.h"

#define GPIO (*(GPIO_CSR*) GPIO_CTRL_ADDR)

void gpio_output_enable(uint8_t pin, uint8_t set) {
	if (set) {
		GPIO.output_en |= (1 << pin);
	} else {
		GPIO.output_en &= ~(1 << pin);
	}
}

void gpio_output_set(uint8_t pin, uint8_t set) {
	if (set) {
		GPIO.output_value |= (1 << pin);
	} else {
		GPIO.output_value &= ~(1 << pin);
	}
}

void gpio_iof_sel(uint8_t pin, uint8_t set) {
	if (set) {
		GPIO.iof_sel |= (1 << pin);
	} else {
		GPIO.iof_sel &= ~(1 << pin);
	}
}

void gpio_iof_enable(uint8_t pin, uint8_t set) {
	if (set) {
		GPIO.iof_enable |= (1 << pin);
	} else {
		GPIO.iof_enable &= ~(1 << pin);
	}
}
