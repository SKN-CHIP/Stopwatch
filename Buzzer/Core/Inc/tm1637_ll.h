/*
 * TM1637.h
 *
 *  Created on: 20-Oct-2018
 *      Author: Venki
 */

#ifndef TM1637_LL_H_
#define TM1637_LL_H_

void TM1637_Init(void);
void TM1637_Demo(void);
void TM1637_DisplayDecimal(int v, int displaySeparator);
void TM1637_SetBrightness(char brightness);
void TM1637_Start(void);
void TM1637_Stop(void);
void TM1637_ReadResult(void);
void TM1637_WriteByte(unsigned char b);
void TM1637_DelayUsec(unsigned int i);
void TM1637_ClkHigh(void);
void TM1637_ClkLow(void);
void TM1637_DataHigh(void);
void TM1637_DATALow(void);
void dziala(void);
void TM1637_IdleMode(int displaySeparator);
void TM1637_gpio_init();
void TM1637_DisplayNothing( int displaySeparator);
#endif /* TM1637_H_ */
