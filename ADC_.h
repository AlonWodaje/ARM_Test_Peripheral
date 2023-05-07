/*
 * ADC_.h
 *
 *  Created on: Nov 22, 2022
 *      Author: Alon
 */

#ifndef INC_ADC__H_
#define INC_ADC__H_

#include "main.h"
#include "stm32f7xx_hal.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
extern UART_HandleTypeDef huart3;
extern DAC_HandleTypeDef hdac;
extern ADC_HandleTypeDef hadc1;
extern TIM_HandleTypeDef htim2;

#define END_OF_STRING 0
#define BACKSPACE 8
#define LINE_FEED 10
#define CARRIAGE_RETURN 13
#define GPIO_PER_2 GPIOB				//Change to match your peripheral section (for led 2)

#define UART_DEBUG &huart3
#define DAC_1 &hdac
#define ADC_1 &hadc1
#define TIM_2 &htim2

uint8_t adc_main(int Iterations);

#endif /* INC_ADC__H_ */
