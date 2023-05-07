/*
 * ADC_.c
 *
 *  Created on: Nov 22, 2022
 *      Author: Alon
 */

/*
 *	This example will show how to use HAL_ADC/HAL_DAC
 *	by transmitting DAC 1,000 Volt and sampling it
 *	with ADC every one second
 *	and shows on console how much Volt ADC read
 *	and display the measurement error
 */

/*
 * Connect DAC to ADC
 * DAC PA4 -- CN7
 * ADC PA0 -- CN10
 *
 */

/*
 * stm32f7xx_hal_dac.c:
 * HAL_DAC_SetValue(DAC_1, DAC_CHANNEL_1, --> DAC_ALIGN_12B_R <--, num);
 * 	Data alignment can be set as one of the following values:
 * 		DAC_ALIGN_8B_R: 8bit right data alignment selected
 * 		DAC_ALIGN_12B_L: 12bit left data alignment selected
 * 		DAC_ALIGN_12B_R: 12bit right data alignment selected
*/

#include "ADC_.h"
#define END_ITERATION 0          // @param end of iterations
#define Delay_Time 50            // @param Delay_Time for HAL_Delay function
#define HUNDR 100                // @param HUNDRED is Auxiliary variable
#define success 1                // @param variable of test success
#define unsuccess 255            // @param variable of test unsuccess
#define MAX_ERROR 1100           // @param 10 percent error
#define MIN_ERROR 900            // @param 10 percent error

uint8_t adc_main(int Iterations)
{
	uint32_t Percent_error;                // @param Percent hold measurement error
	int TR_Volt = 1000;                    // @param TR_Volt is the Volt are DAC transmit
	int i;

	HAL_DAC_SetValue(DAC_1, DAC_CHANNEL_1, DAC_ALIGN_12B_R, TR_Volt); // Initialization : Sets the DAC output according to TR_Volt
	HAL_DAC_Start(DAC_1, DAC_CHANNEL_1);                              // (Start after Initialization) Enabled DAC conversion


	for(i=0; i<Iterations ; i++)
	{

		// in this condition we check the measurement error
		if (HAL_ADC_GetValue(ADC_1) < TR_Volt)
		{
			Percent_error = (HUNDR*TR_Volt)/HAL_ADC_GetValue(ADC_1) ;
			Percent_error -= HUNDR;
		}
		else
		{
			Percent_error = (HUNDR*HAL_ADC_GetValue(ADC_1))/TR_Volt ;
			Percent_error -= HUNDR;
		}

		printf("transmit %d Volt -> read %ld Volt, Error percentage %ld%% \n\r",
				TR_Volt, HAL_ADC_GetValue(ADC_1), Percent_error);                  //Sample the DAC value using the ADC

		HAL_ADC_Start_IT(ADC_1);   // Read how much many Volt get into DAC1
		HAL_Delay(Delay_Time);

		if( MAX_ERROR < HAL_ADC_GetValue(ADC_1) || MIN_ERROR > HAL_ADC_GetValue(ADC_1)) // if Fails return unsuccess
			return unsuccess;
		Iterations--;
	}
	return success;
}

