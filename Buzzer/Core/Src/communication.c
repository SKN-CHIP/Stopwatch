/*
 * communication.c
 *
 *  Created on: Mar 16, 2024
 *      Author: patry
 */
#include "main.h"
#include "stdio.h"
#include "string.h"
#include "communication.h"

#define LINE_MAX_LENGTH 50
#define ASCII_OFFSET 48

int _write(int file, uint8_t *buf, int nbytes){
  uint8_t num_of_byte = 0;
  while (num_of_byte <= nbytes - 1){
    while (!LL_USART_IsActiveFlag_TXE(USART2));
    LL_USART_TransmitData8(USART2, buf[num_of_byte++]);
  }
  while (!LL_USART_IsActiveFlag_TC(USART2));
  return nbytes;
}

void decompose_data(uint8_t message[], uint8_t length){
	extern struct bluetooth_data data;
	data.check_sum = (message[length - 1] - ASCII_OFFSET) * 10; //48 = ASCII offset
	data.check_sum += message[length] - ASCII_OFFSET;
	uint8_t sum = 0;
	for(int i = 0; i < length - 1; ++i){
		sum += message[i] - ASCII_OFFSET;
	}
	if(data.check_sum != sum){
		return;
	}
	data.device_address = message[0] - ASCII_OFFSET;

	if(data.device_address == 1){
		data.value1 = (message[1] - ASCII_OFFSET) * 10 + message[2] - ASCII_OFFSET;
		data.value2 = (message[3] - ASCII_OFFSET) * 10 + message[4] - ASCII_OFFSET;
	}
	else if(data.device_address == 2){
		data.value1 = message[1] - ASCII_OFFSET;
		data.value2 = message[2] - ASCII_OFFSET;
	}
	else if(data.device_address == 3){
		data.value1 = message[1] - ASCII_OFFSET;
		data.value2 = message[2] - ASCII_OFFSET;
	}
	else {
		return;
	}
	data.flag = 1;
}


static void usart_append(uint8_t value){

	static char line_buffer_usart[LINE_MAX_LENGTH + 1];
	static uint8_t line_length_usart = 0;

	if(value == '\r')
		return;

	if(value == '\n'){
		line_buffer_usart[line_length_usart] = '\0';
		printf("Received: %s\r\n", line_buffer_usart);
		decompose_data((uint8_t*)line_buffer_usart, line_length_usart-1);
		memset(line_buffer_usart, '\0', LINE_MAX_LENGTH);
		line_length_usart = 0;
	}
	else
	{
		if (line_length_usart >= LINE_MAX_LENGTH) {
			line_length_usart = 0;
		}
		line_buffer_usart[line_length_usart++] = value;
	}
}

void usart_transmit(USART_TypeDef *USARTx, uint8_t text[]){

	uint8_t num_of_byte = 0;
	while (num_of_byte < (strlen((const char*)text))){
		//waiting until the Transmit Empty flag is set
		while (!LL_USART_IsActiveFlag_TXE(USARTx)){
			uint16_t counter = 0;
			if(counter++ > 65000) return;
		}
		LL_USART_TransmitData8(USARTx, text[num_of_byte++]);
	}
	while (!LL_USART_IsActiveFlag_TC(USARTx)){
		uint16_t counter = 0;
		if(counter++ > 65000) return;
	}
	num_of_byte = 0;
}


void USART1_IRQHandler(void)
{
	uint8_t received_byte;
	if(LL_USART_IsActiveFlag_RXNE(USART1))
	{
	  received_byte = LL_USART_ReceiveData8(USART1);
	  usart_append(received_byte);
	}
}

void usart1_init(void){

  LL_USART_InitTypeDef USART_InitStruct = {0};
  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

  LL_RCC_SetUSARTClockSource(LL_RCC_USART1_CLKSOURCE_PCLK2);
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_USART1);
  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOA);
  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOB);

  GPIO_InitStruct.Pin = LL_GPIO_PIN_10;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  GPIO_InitStruct.Alternate = LL_GPIO_AF_7;
  LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = LL_GPIO_PIN_6;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  GPIO_InitStruct.Alternate = LL_GPIO_AF_7;
  LL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  NVIC_SetPriority(USART1_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),0, 0));
  NVIC_EnableIRQ(USART1_IRQn);

  USART_InitStruct.BaudRate = 9600;
  USART_InitStruct.DataWidth = LL_USART_DATAWIDTH_8B;
  USART_InitStruct.StopBits = LL_USART_STOPBITS_1;
  USART_InitStruct.Parity = LL_USART_PARITY_NONE;
  USART_InitStruct.TransferDirection = LL_USART_DIRECTION_TX_RX;
  USART_InitStruct.HardwareFlowControl = LL_USART_HWCONTROL_NONE;
  USART_InitStruct.OverSampling = LL_USART_OVERSAMPLING_16;
  LL_USART_Init(USART1, &USART_InitStruct);
  LL_USART_ConfigAsyncMode(USART1);
  LL_USART_Enable(USART1);
  LL_USART_EnableIT_RXNE(USART1);

}

void usart2_init(void){

  LL_USART_InitTypeDef USART_InitStruct = {0};
  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

  LL_RCC_SetUSARTClockSource(LL_RCC_USART2_CLKSOURCE_PCLK1);
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART2);
  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOA);

  GPIO_InitStruct.Pin = LL_GPIO_PIN_2|LL_GPIO_PIN_3;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  GPIO_InitStruct.Alternate = LL_GPIO_AF_7;
  LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  USART_InitStruct.BaudRate = 9600;
  USART_InitStruct.DataWidth = LL_USART_DATAWIDTH_8B;
  USART_InitStruct.StopBits = LL_USART_STOPBITS_1;
  USART_InitStruct.Parity = LL_USART_PARITY_NONE;
  USART_InitStruct.TransferDirection = LL_USART_DIRECTION_TX_RX;
  USART_InitStruct.HardwareFlowControl = LL_USART_HWCONTROL_NONE;
  USART_InitStruct.OverSampling = LL_USART_OVERSAMPLING_16;
  LL_USART_Init(USART2, &USART_InitStruct);
  LL_USART_ConfigAsyncMode(USART2);
  LL_USART_Enable(USART2);

}
