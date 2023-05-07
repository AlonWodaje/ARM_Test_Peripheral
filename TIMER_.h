/*
 * TIMAER_.h
 *
 *  Created on: Nov 21, 2022
 *      Author: Alon
 */

#ifndef INC_TIMER__H_
#define INC_TIMER__H_

#include "main.h"
#include "stm32f7xx_hal.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
extern UART_HandleTypeDef huart3;	//Change to match your UART number
extern TIM_HandleTypeDef htim2;	//Change to match your UART number

#define END_OF_STRING 0
#define BACKSPACE 8
#define LINE_FEED 10
#define CARRIAGE_RETURN 13

#define UART_DEBUG &huart3			//Change to match your UART number
#define GPIO_PER_1 GPIOB
#define GPIO_LED_1 LD1_Pin
#define TIM_2 &htim2				//Change to match your Timer number

uint8_t timer_main(int Iterations);


#endif /* INC_TIMER__H_ */
