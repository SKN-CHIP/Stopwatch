//
//#include "led_set.h"
//
//
//void WS2812_Send (struct led_data *led, uint8_t brightness){
//	uint32_t indx=0;
//	uint32_t color;
//	Set_Brightness(led, brightness);
//
//	for (int i=0; i<50; i++){
//		led->pwmData[indx] = 0;
//		indx++;
//	}
//
//	for (int i= 0; i<MAX_LED; i++){
//		color = ((led->LED_Mod[i*4 + 1]<<16) | (led->LED_Mod[i*4 + 2]<<8) | (led->LED_Mod[i*4 + 3]));
//		for (int i=23; i>=0; i--){
//			if (color&(1<<i))
//				led->pwmData[indx] = 27;  // 2/3 of 90
//			else
//				led->pwmData[indx] = 13;  // 1/3 of 90
//
//			indx++;
//		}
//	}
//
//	for (int i=0; i<50; i++){
//		led->pwmData[indx] = 0;
//		indx++;
//	}
//
//	generate_signal((uint8_t*)led->pwmData, sizeof(led->pwmData));
//}
//
//
//void Set_Brightness(struct led_data *led, uint8_t brightness){  // 0 - 45
//	if (brightness > 45)
//		brightness = 45;
//
//	for (int i=0; i<MAX_LED; i++){
//		led->LED_Mod[i*4 + 0] = led->LED_Data[i*4 + 0];
//		for (int j=1; j<4; j++){
//			float angle = 90-brightness;  // in degrees
//			angle = angle*PI / 180;  // in rad
//			led->LED_Mod[i*4 + j] = (led->LED_Data[i*4 + j])/(tan(angle));
//		}
//	}
//}
//
//
//void Set_LED (struct led_data *led, int LEDnum, int Red, int Green, int Blue){
//	led->LED_Data[LEDnum*4 + 0] = LEDnum;
//	led->LED_Data[LEDnum*4 + 1] = Green;
//	led->LED_Data[LEDnum*4 + 2] = Red;
//	led->LED_Data[LEDnum*4 + 3] = Blue;
//}
//
//
//void Reset_LED (struct led_data *led){
//	for (int i=0; i<MAX_LED; i++){
//		led->LED_Data[i*4 + 0] = i;
//		led->LED_Data[i*4 + 1] = 0;
//		led->LED_Data[i*4 + 2] = 0;
//		led->LED_Data[i*4 + 3] = 0;
//	}
//	WS2812_Send(led, 0);
//}
//
