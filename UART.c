/*
 * UART.c
 *
 *  Created on: Nov 21, 2022
 *      Author: Alon
 */

/*
 * This example will show how to use UART interrupt
 * we get data from client and UART_4 transmit this data to USART_2
 * USART_2 will return back to UART_4
 * and at the end we will check if UART_4 receive back the same data that he received from client
 *
 * UART_4 :
 * 	RX : PC11
 * 	TX : PC10
 *
 * USART_2 :
 * 	RX : PD6
 * 	TX : PD5
 */

#include "UART.h"
#define size_buff 100            // @param size_buff is size fo string data from client
#define END_ITERATION 0          // @param end of iterations
#define CHECKING_EQUALITY 0      // @param checking if have equality
#define Delay_Time 50            // @param Delay_Time for HAL_Delay function
#define Delay_Time_1s 1000       // @param Delay_Time for HAL_Delay function
#define success 1                // @param variable of test success
#define unsuccess 255            // @param variable of test unsuccess

uint8_t uart_main(int Iterations, char *Bit_pattern, int len)
{
	printf("Start of UART program\r\n");
	uint8_t rbuff2[size_buff] = {0};                    // @param rbuff2 save data from client
	uint8_t rbuff4[size_buff] = {0};                    // @param rbuff4 save data from client
	uint8_t rbuff0[size_buff] = {0};
	const uint32_t Timeout = 10;                        // @param Timeout duration.
	int i;

	HAL_UART_Receive_IT(UART_2, rbuff2, len);          // prepares to receive data from UART_4
	HAL_UART_Receive_IT(UART_4, rbuff4, len);          // prepares to receive data from USART_2

	for(i=0; i<Iterations ; i++)
	{
		HAL_UART_Transmit(UART_4, Bit_pattern, len, Timeout);    // UART_4 Transmit data from client to UsART_2
		HAL_Delay(Delay_Time);
		HAL_UART_Receive_IT(UART_2, rbuff2, len);                // prepares to receive data from USART_2, for next round
		HAL_Delay(Delay_Time_1s);

		HAL_UART_Transmit(UART_2, rbuff2, len, Timeout);         // UsART_2 Transmit back the data from client to UART_4
		HAL_Delay(Delay_Time);
		HAL_UART_Receive_IT(UART_4, rbuff4, len);                // prepares to receive data from UART_4, for next round
		HAL_Delay(Delay_Time_1s);

		if (strcmp(rbuff4, Bit_pattern) != CHECKING_EQUALITY)    // check if UART_4 get back the same data that he received from client
			return unsuccess;

		Iterations--;
		memcpy(rbuff4, rbuff0, 17);
		memcpy(rbuff2, rbuff0, 17);
	}
	return success;
}


//Available types of callback for UARTs only

/*
(+) TxHalfCpltCallback        : Tx Half Complete Callback.
(+) TxCpltCallback            : Tx Complete Callback.
(+) RxHalfCpltCallback        : Rx Half Complete Callback.
(+) RxCpltCallback            : Rx Complete Callback.
(+) ErrorCallback             : Error Callback.
(+) AbortCpltCallback         : Abort Complete Callback.
(+) AbortTransmitCpltCallback : Abort Transmit Complete Callback.
(+) AbortReceiveCpltCallback  : Abort Receive Complete Callback.
(+) WakeupCallback            : Wakeup Callback.
(+) RxFifoFullCallback        : Rx Fifo Full Callback.
(+) TxFifoEmptyCallback       : Tx Fifo Empty Callback.
(+) MspInitCallback           : UART MspInit.
(+) MspDeInitCallback         : UART MspDeInit.
*/
