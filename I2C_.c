/*
 * I2C_.c
 *
 *  Created on: Nov 21, 2022
 *      Author: Alon
 */

/*
 * This example will show how to use I2C interrupt
 * we get data from client and I2C_2 transmit this data to I2C_1.
 * I2C_1 will return back to I2C_2
 * and at the end we will check if I2C_2 receive back the same data that he received from client
 *
 * I2C1 (Master):
 * 	I2C1_SCL PB6 (CN10)
 * 	I2C1_SDA PB9 (CN7)
 *
 * I2C2 (Slave):
 *  I2C2_SCL PB10  (CN10)
 *  I2C2_SDA PB11 (CN10)
 *  Slave address: 30
 */

#include "I2C_.h"
#define size_buff 100            // @param size_buff is size fo string data from client
#define Delay_Time 50            // @param Delay_Time for HAL_Delay function
#define END_ITERATION 0          // @param end of iterations
#define CHECKING_EQUALITY 0      // @param checking if have equality
#define success 1                // @param variable of test success
#define unsuccess 255            // @param variable of test unsuccess

//unsigned char data_from_i2c1[20];                                // @param data_from_i2c1 save the data for i2c_1
//unsigned char data_from_i2c2[20];                                // @param data_from_i2c2 save the data for i2c_2

uint8_t i2c_main(int Iterations, char *Bit_pattern, int len)
{
	uint8_t data_from_i2c1[size_buff] = {0};                    // @param rbuff2 save data from client
	uint8_t data_from_i2c2[size_buff] = {0};                    // @param rbuff4 save data from client
	uint8_t rbuff0[size_buff] = {0};
	const uint32_t Timeout = 10;                        // @param Timeout duration.
	printf("Start of I2C program:\r\n");                                 // @param counter_iterations number of iterations that the client asked for
	uint8_t data_from_client[size_buff] = {"data_from_client"};  // @param data_from_client data from client
	int i;

	for(i=0; i<Iterations ; i++)
	{


		HAL_I2C_Master_Receive_IT(I2C_1, 30, data_from_i2c1, len);        //Master prepares to receive data from slave
		HAL_Delay(Delay_Time);
		HAL_I2C_Slave_Transmit(I2C_2, Bit_pattern, len, Timeout);        // Slave transmit data to master
		HAL_Delay(Delay_Time);

		HAL_I2C_Slave_Receive_IT(I2C_2, data_from_i2c2, len);             //Slave prepares to receive data from master
		HAL_Delay(Delay_Time);
		HAL_I2C_Master_Transmit(I2C_1, 30, data_from_i2c1, len, Timeout);     // Master transmit data to slave
		HAL_Delay(Delay_Time);

		if (strcmp(data_from_i2c1, Bit_pattern) != CHECKING_EQUALITY)       //check if I2C_2 get back the same data that he received from client
			return unsuccess;

		Iterations--;
		memcpy(data_from_i2c1, rbuff0, 17);
		memcpy(data_from_i2c2, rbuff0, 17);
	}
	return success;
}

/*
 stm32fxx_hal_i2c.c:
 Function HAL_I2C_RegisterCallback() allows to register following callbacks:
 (+) MasterTxCpltCallback : callback for Master transmission end of transfer.
 (+) MasterRxCpltCallback : callback for Master reception end of transfer.
 (+) SlaveTxCpltCallback  : callback for Slave transmission end of transfer.
 (+) SlaveRxCpltCallback  : callback for Slave reception end of transfer.
 (+) ListenCpltCallback   : callback for end of listen mode.
 (+) MemTxCpltCallback    : callback for Memory transmission end of transfer.
 (+) MemRxCpltCallback    : callback for Memory reception end of transfer.
 (+) ErrorCallback        : callback for error detection.
 (+) AbortCpltCallback    : callback for abort completion process.
 (+) MspInitCallback      : callback for Msp Init.
 (+) MspDeInitCallback    : callback for Msp DeInit.
 */
