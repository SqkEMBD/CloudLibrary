/*
 * P2PButton.c
 *
 *  Created on: Jul 22, 2022
 *  Latest modified on: Jul 22, 2022
 *      Author: Amornsak <amornsak-ra@starsmicro.com>
 */

#include "P2PButton.h"

//*** Global Variables
//static uint16_t buttonTimCnt = -1;
static uint32_t TIM2_CNT;

void HAL_GPIO_EXTI_Falling_Callback(uint16_t GPIO_Pin)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(GPIO_Pin);

  /* NOTE: This function should not be modified, when the callback is needed,
           the HAL_GPIO_EXTI_Falling_Callback could be implemented in the user file
   */

  // get secured state from the DIPSwitch pins.
  bool securedState = getSecuredState();

  // External interrupt with falling edge trigger detection **button active low**
  // Check interrupt pin
  // Check secure mode status
  HAL_Delay(10);
  if( (GPIO_Pin == BUTTON_Pin) && (secureState == ON) )
  {
	  // Clear EXTI flags
	  if(__HAL_GPIO_EXTI_GET_FALLING_IT(BUTTON_Pin) != RESET) __HAL_GPIO_EXTI_CLEAR_FALLING_IT(BUTTON_Pin);

	  if(HAL_GPIO_ReadPin(BUTTON_GPIO_Port, BUTTON_Pin) == GPIO_PIN_RESET) // button down
	  {
		  // Start Timer/Counter
		  HAL_TIM_Base_Start(&htim3);
		  // Toggle LED
		  HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
	  }

  }

}

void HAL_GPIO_EXTI_Rising_Callback(uint16_t GPIO_Pin)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(GPIO_Pin);
  /* NOTE: This function should not be modified, when the callback is needed,
           the HAL_GPIO_EXTI_Rising_Callback could be implemented in the user file
   */

  HAL_Delay(10);

  // get secured state from the DIPSwitch pins.
  bool securedState = getSecuredState();

  // External interrupt with Rising edge trigger detection **button active low**
  // Check interrupt pin
  // Check secure mode status
  if( ( GPIO_Pin == BUTTON_Pin ) && ( securedState == ON ) )
  {
  	  // Clear EXTI flags
    if(__HAL_GPIO_EXTI_GET_RISING_IT(BUTTON_Pin) != RESET) __HAL_GPIO_EXTI_CLEAR_RISING_IT(BUTTON_Pin);

    if(HAL_GPIO_ReadPin(BUTTON_GPIO_Port, BUTTON_Pin) == GPIO_PIN_SET) // Button Up
    {
      HAL_TIM_Base_Stop(&htim3);
      HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);

      if(TIM3->CNT >= 0 && TIM3->CNT <= 2000)
      {
        printf("Quick Press\n");
      }
      else if(TIM3->CNT >= 2000 && TIM3->CNT <= 5000)
      {
        printf("Short Press\n");
      }
      else if(TIM3->CNT >= 5000 && TIM3->CNT <= 10000)
      {
        printf("Long Press\n");
      }
      else
      {
        Error_Handler();
      }
		  TIM3->CNT = 0; // Reset Counter Register
		}
  }