#ifndef _GPIO_H
#define _GPIO_H

#include <stdint.h>
#include "platform.h"

typedef volatile struct {
	uint32_t input_value;
	uint32_t input_en;
	uint32_t output_en;
	uint32_t output_value;
	uint32_t pue;
	uint32_t ds;
	uint32_t rise_ie;
	uint32_t rise_ip;
	uint32_t fall_ie;
	uint32_t fall_ip;
	uint32_t high_ie;
	uint32_t high_ip;
	uint32_t low_ie;
	uint32_t low_ip;
	uint32_t iof_enable;
	uint32_t iof_sel;
	uint32_t out_xor;
} GPIO_CSR;

void gpio_output_enable(uint8_t pin, uint8_t set);
void gpio_output_set(uint8_t pin, uint8_t set);
void gpio_iof_sel(uint8_t pin, uint8_t set);
void gpio_iof_enable(uint8_t pin, uint8_t set);

#endif
