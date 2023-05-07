/*
 * PSI_.c
 *
 *  Created on: Nov 22, 2022
 *      Author: Alon
 */

/*
 * This example will show how to use UART interrupt
 * we get data from client and SPI1 (MASTER) transmit this data to SPI2 (SLAVE)
 * SPI2 will return back to SPI1
 * and at the end we will check if SPI1 receive back the same data that he received from client
 *
 *
 * SPI1 (MASTER)
 * PA5 SCK   (CN7)
 * PA6 MISO	 (CN7)
 * PB5 MOSI  (CN7)
 *
 * SPI2 (SLAVE)
 * PD3 SCK (CN10)
 * PC2  MISO (CN10)
 * PC3  MOSI (CN9)
 *
 */
#include <SPI_.h>
#define size_buff 100                             // @param size_buff is size fo string data from client
#define Delay_Time 100                            // @param Delay_Time for HAL_Delay function
#define END_ITERATION 0                           // @param end of iterations
#define CHECKING_EQUALITY 0                       // @param checking if have equality
#define success 1                                 // @param variable of test success
#define unsuccess 255                             // @param variable of test unsuccess

unsigned char data_from_spi1[size_buff] = {0};    // @param data_from_spi1 save data from SPI1 (MASTER)
unsigned char data_from_spi2[size_buff] = {0};    // @param data_from_spi2 save data from SPI2 (SLAVE)
unsigned char buff[size_buff] = {0};              // @param buff is empty string for Initialization

uint8_t spi_main(int Iterations, char *Bit_pattern, int len)
{

	printf("\nStart of SPI program:\r\n");

	const uint32_t Timeout = 10;                        // @param Timeout duration.
	int i;

	for(i=0; i<Iterations ; i++)
	{

		HAL_SPI_TransmitReceive(SPI_2, data_from_spi2, data_from_spi2, len, Timeout);   // prepares to receive
		HAL_Delay(Delay_Time);
		HAL_SPI_TransmitReceive(SPI_1, Bit_pattern, data_from_spi1, len, Timeout);      // transmit data
		HAL_Delay(Delay_Time);
		HAL_SPI_TransmitReceive(SPI_2, data_from_spi2, data_from_spi2, len, Timeout);   // receive data
		HAL_Delay(Delay_Time);

		HAL_SPI_TransmitReceive(SPI_1, data_from_spi1, data_from_spi1, len, Timeout); // prepares to receive
		HAL_Delay(Delay_Time);
		HAL_SPI_TransmitReceive(SPI_2, data_from_spi2, data_from_spi2, len, Timeout); // transmit data
		HAL_Delay(Delay_Time);
		HAL_SPI_TransmitReceive(SPI_1, data_from_spi1, data_from_spi1, len, Timeout); // receive data
		HAL_Delay(Delay_Time);

		if (strcmp(data_from_spi1, Bit_pattern) == CHECKING_EQUALITY )   // check if SPI1 get back the same data that he received from client
			return unsuccess;
		Iterations--;
	}
	return success;
}



/*
 void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi);
 void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *hspi);
 void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi);
 void HAL_SPI_TxHalfCpltCallback(SPI_HandleTypeDef *hspi);
 void HAL_SPI_RxHalfCpltCallback(SPI_HandleTypeDef *hspi);
 void HAL_SPI_TxRxHalfCpltCallback(SPI_HandleTypeDef *hspi);
 void HAL_SPI_ErrorCallback(SPI_HandleTypeDef *hspi);
 void HAL_SPI_AbortCpltCallback(SPI_HandleTypeDef *hspi);
 */
