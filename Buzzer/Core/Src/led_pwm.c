/*
 * led_pwm.c
 *
 *  Created on: Mar 14, 2024
 *      Author: patry
 */
#include "main.h"

void enable_timer3(){
	LL_TIM_EnableDMAReq_CC1(TIM3);
	LL_TIM_CC_EnableChannel(TIM3, LL_TIM_CHANNEL_CH1);
	LL_TIM_EnableCounter(TIM3);

}


void generate_signal(uint8_t* data, uint32_t data_length){
	LL_DMA_ConfigAddresses(DMA1, LL_DMA_CHANNEL_6, (uint32_t)data, (uint32_t)&TIM3->CCR1, LL_DMA_DIRECTION_MEMORY_TO_PERIPH);
	LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_6, data_length);

	LL_DMA_EnableIT_TC(DMA1, LL_DMA_CHANNEL_6);
	LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_6);
}


void dma_init(void)
{
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA1);
  NVIC_SetPriority(DMA1_Channel6_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),0, 0));
  NVIC_EnableIRQ(DMA1_Channel6_IRQn);

  LL_DMA_SetPeriphRequest(DMA1, LL_DMA_CHANNEL_6, LL_DMA_REQUEST_5);
	LL_DMA_SetDataTransferDirection(DMA1, LL_DMA_CHANNEL_6, LL_DMA_DIRECTION_MEMORY_TO_PERIPH);
	LL_DMA_SetChannelPriorityLevel(DMA1, LL_DMA_CHANNEL_6, LL_DMA_PRIORITY_LOW);
	LL_DMA_SetMode(DMA1, LL_DMA_CHANNEL_6, LL_DMA_MODE_NORMAL);
	LL_DMA_SetPeriphIncMode(DMA1, LL_DMA_CHANNEL_6, LL_DMA_PERIPH_NOINCREMENT);
	LL_DMA_SetMemoryIncMode(DMA1, LL_DMA_CHANNEL_6, LL_DMA_MEMORY_INCREMENT);
	LL_DMA_SetPeriphSize(DMA1, LL_DMA_CHANNEL_6, LL_DMA_PDATAALIGN_HALFWORD);
	LL_DMA_SetMemorySize(DMA1, LL_DMA_CHANNEL_6, LL_DMA_MDATAALIGN_BYTE);

	LL_DMA_EnableIT_TE(DMA1, LL_DMA_CHANNEL_6);

}

void DMA1_Channel6_IRQHandler(void)
{

	if(LL_DMA_IsActiveFlag_TC6(DMA1) == 1)
	{
		LL_DMA_ClearFlag_TC6(DMA1);
		LL_DMA_DisableChannel(DMA1, LL_DMA_CHANNEL_6);
		LL_DMA_DisableIT_TC(DMA1, LL_DMA_CHANNEL_6);
	}
	else if(LL_DMA_IsActiveFlag_TE6(DMA1)){
		//nananana
	}

}
