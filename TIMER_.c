/*
 * TIMAER_.c
 *
 *  Created on: Nov 21, 2022
 *      Author: Alon
 */

/*
 * This example will show how to use HAL_TIM
 * by displaying a timer on the console and count of pulses
 * using interrupt handler.
 */

#include "TIMER_.h"

#define END_ITERATION 0        // @param end of iterations
#define Delay_Time 50          // @param Delay_Time for HAL_Delay function
#define success 1              // @param variable of test success
#define unsuccess 255          // @param variable of test unsuccess
uint8_t f_time=0;              // @param  interrupt flag timer
uint8_t second=0;              // @param  seconds
uint8_t minute=0;              // @param  minutes
int long long ticks=0;         // @param  count pulses


uint8_t timer_main(int Iterations)
{
	printf("Start of program:\r\n");
	HAL_TIM_Base_Start_IT(TIM_2);        //Start work whit clock, needs to be done by the developer
	while (Iterations != END_ITERATION)
	{
		if(f_time)                       // get in when have interrupt
		{

			HAL_GPIO_TogglePin(GPIO_PER_1, GPIO_LED_1);     // toggle for Green LED
			printf("%d : %d \n\r",minute, second);          // print the clock every second
			f_time=0;
			Iterations--;
		}
	}
	return success;
}

// ============= Timer Callback =============
// this function updating the clock in every interrupt
// have interrupt every one second
// calculation interrupt for one second :
// TIM2 / (Prescaler*period)
// 72,000,000 / (7,200*10,000)

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	f_time=1;
	second ++;
	if(second == 60)
	{
		second=0;
		minute++;
	}
}

/*
stm32fxx_hal_tim.c:

These functions allow to register/unregister following callbacks:
  (+) Base_MspInitCallback              : TIM Base Msp Init Callback.
  (+) Base_MspDeInitCallback            : TIM Base Msp DeInit Callback.
  (+) IC_MspInitCallback                : TIM IC Msp Init Callback.
  (+) IC_MspDeInitCallback              : TIM IC Msp DeInit Callback.
  (+) OC_MspInitCallback                : TIM OC Msp Init Callback.
  (+) OC_MspDeInitCallback              : TIM OC Msp DeInit Callback.
  (+) PWM_MspInitCallback               : TIM PWM Msp Init Callback.
  (+) PWM_MspDeInitCallback             : TIM PWM Msp DeInit Callback.
  (+) OnePulse_MspInitCallback          : TIM One Pulse Msp Init Callback.
  (+) OnePulse_MspDeInitCallback        : TIM One Pulse Msp DeInit Callback.
  (+) Encoder_MspInitCallback           : TIM Encoder Msp Init Callback.
  (+) Encoder_MspDeInitCallback         : TIM Encoder Msp DeInit Callback.
  (+) HallSensor_MspInitCallback        : TIM Hall Sensor Msp Init Callback.
  (+) HallSensor_MspDeInitCallback      : TIM Hall Sensor Msp DeInit Callback.
  (+) PeriodElapsedCallback             : TIM Period Elapsed Callback.
  (+) PeriodElapsedHalfCpltCallback     : TIM Period Elapsed half complete Callback.
  (+) TriggerCallback                   : TIM Trigger Callback.
  (+) TriggerHalfCpltCallback           : TIM Trigger half complete Callback.
  (+) IC_CaptureCallback                : TIM Input Capture Callback.
  (+) IC_CaptureHalfCpltCallback        : TIM Input Capture half complete Callback.
  (+) OC_DelayElapsedCallback           : TIM Output Compare Delay Elapsed Callback.
  (+) PWM_PulseFinishedCallback         : TIM PWM Pulse Finished Callback.
  (+) PWM_PulseFinishedHalfCpltCallback : TIM PWM Pulse Finished half complete Callback.
  (+) ErrorCallback                     : TIM Error Callback.
  (+) CommutationCallback               : TIM Commutation Callback.
  (+) CommutationHalfCpltCallback       : TIM Commutation half complete Callback.
  (+) BreakCallback                     : TIM Break Callback.
  (+) Break2Callback                    : TIM Break2 Callback.
*/

