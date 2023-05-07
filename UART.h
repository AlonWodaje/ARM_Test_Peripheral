/*
 * UART.h
 *
 *  Created on: Nov 21, 2022
 *      Author: Alon
 */

#ifndef INC_UART_H_
#define INC_UART_H_
#include "main.h"
#include "stm32f7xx_hal.h"
#include <stdio.h>
#include <stdlib.h>

extern UART_HandleTypeDef huart3;		//Change to match your UART number
extern UART_HandleTypeDef huart4;		//Change to match your UART number
extern UART_HandleTypeDef huart2;		//Change to match your UART number

#define UART_DEBUG &huart3				//Change to match your UART number
#define UART_2 &huart2					//Change to match your UART number
#define UART_4 &huart4					//Change to match your UART number

uint8_t uart_main(int Iterations, char *Bit_pattern, int len);

extern uint8_t uart3_flag_calback;
extern uint8_t uart3_flag_h;
#endif /* INC_UART_H_ */
