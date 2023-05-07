/*
 * I2C_.h
 *
 *  Created on: Nov 21, 2022
 *      Author: Alon
 */

#ifndef INC_I2C__H_
#define INC_I2C__H_

#include "main.h"
#include "stm32f7xx_hal.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
extern UART_HandleTypeDef huart3;
extern I2C_HandleTypeDef hi2c1;
extern I2C_HandleTypeDef hi2c2;

#define END_OF_STRING 0
#define BACKSPACE 8
#define LINE_FEED 10
#define CARRIAGE_RETURN 13

#define UART_DEBUG &huart3
#define I2C_1 &hi2c1
#define I2C_2 &hi2c2

#define GPIO_PER_1 GPIOB
#define GPIO_PER_2 GPIOB
#define GPIO_PER_3 GPIOB
#define GPIO_PER_4 GPIOC
#define GPIO_LED_1 LD1_Pin
#define GPIO_LED_2 LD2_Pin
#define GPIO_LED_3 LD3_Pin

uint8_t i2c_main(int Iterations, char *Bit_pattern, int len);
#endif /* INC_I2C__H_ */
