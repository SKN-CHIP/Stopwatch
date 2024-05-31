/*
 * communication.h
 *
 *  Created on: Mar 21, 2024
 *      Author: patry
 */

#ifndef INC_COMMUNICATION_H_
#define INC_COMMUNICATION_H_
#include "main.h"
#include "led_set.h"

struct bluetooth_data{
	uint8_t device_address; // 1 - timer; 2 - diodes; 3 - flags
	uint8_t value1; //minutes, diode number, flag state
	uint8_t value2; //seconds, diode color
	uint8_t check_sum;
	uint8_t flag;
};

void usart1_init(void);
void usart2_init(void);
void usart_transmit(USART_TypeDef *USARTx, uint8_t text[]);
void decompose_data(uint8_t message[], uint8_t length);
void SavePointer(struct led_data *newLedData);


#endif /* INC_COMMUNICATION_H_ */
