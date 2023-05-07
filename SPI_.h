/*
 * SPI_.h
 *
 *  Created on: Nov 22, 2022
 *      Author: Alon
 */

#ifndef SRC_SPI__H_
#define SRC_SPI__H_

#include "main.h"
#include "stm32f7xx_hal.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
extern UART_HandleTypeDef huart3;
extern SPI_HandleTypeDef hspi1;
extern SPI_HandleTypeDef hspi2;

#define END_OF_STRING 0
#define BACKSPACE 8
#define LINE_FEED 10
#define CARRIAGE_RETURN 13

#define UART_DEBUG &huart3
#define SPI_1 &hspi1
#define SPI_2 &hspi2

#define GPIO_PER_1 GPIOB
#define GPIO_PER_2 GPIOB
#define GPIO_PER_3 GPIOB
#define GPIO_PER_4 GPIOC
#define GPIO_LED_1 LD1_Pin
#define GPIO_LED_2 LD2_Pin
#define GPIO_LED_3 LD3_Pin


uint8_t spi_main(int Iterations, char *Bit_pattern, int len);


#endif /* SRC_SPI__H_ */
