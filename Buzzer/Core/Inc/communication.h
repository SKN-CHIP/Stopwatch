/*
 * communication.h
 *
 *  Created on: Mar 21, 2024
 *      Author: patry
 */

#ifndef INC_COMMUNICATION_H_
#define INC_COMMUNICATION_H_
#include "main.h"

void usart1_init(void);
void usart2_init(void);
void usart_transmit(USART_TypeDef *USARTx, uint8_t text[]);
void decompose_data(uint8_t message[], uint8_t length);

#endif /* INC_COMMUNICATION_H_ */
