/*
 * led_pwm.h
 *
 *  Created on: Mar 14, 2024
 *      Author: patry
 */

#ifndef INC_LED_PWM_H_
#define INC_LED_PWM_H_

#include "main.h"

void enable_timer3(void);

void generate_signal(uint16_t* data, uint32_t data_length);

void dma_init(void);


#endif /* INC_LED_PWM_H_ */
