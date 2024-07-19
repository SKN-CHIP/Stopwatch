/*
 * led_set.h
 *
 *  Created on: Apr 4, 2024
 *      Author: patry
 */

#ifndef INC_LED_SET_H_
#define INC_LED_SET_H_

#include "led_pwm.h"
#include "math.h"

#define MAX_LED 8
#define PI 3.14159265
#define STANDARD_BRIGHTNESS 2
#define PWM_DATA_LENGTH 50+(24*MAX_LED)+50

struct led_data{
	uint8_t LED_Data[MAX_LED*4];
	uint8_t LED_Mod[MAX_LED*4];
	uint16_t pwmData[PWM_DATA_LENGTH];
	uint8_t autoMode;
};

void WS2812_Send (struct led_data *led, uint8_t brightness);
void Set_Brightness(struct led_data *led, uint8_t brightness);
void Set_LED (struct led_data *led, int LEDnum, int Red, int Green, int Blue);
void Reset_LED (struct led_data *led);
void DisableLED (void);

#endif /* INC_LED_SET_H_ */
