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
