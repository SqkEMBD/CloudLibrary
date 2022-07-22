/*
 * P2PButton.h
 *
 *  Created on: Jul 22, 2022
 *  Latest modified on: Jul 22, 2022
 *      Author: Amornsak <amornsak-ra@starsmicro.com>
 */

#ifndef __P2PBUTTON_H__
#define __P2PBUTTON_H__

// *User marcro
#define BUTTON_PIN_DOWN 0
#define BUTTON_PIN_UP 1

#define SECURE_MODE_ON 1
#define SECURE_MODE_OFF 0

//*** Global Variables

//** Fucntion Prototypes

void HAL_GPIO_EXTI_Falling_Callback(uint16_t GPIO_Pin);
void HAL_GPIO_EXTI_Rising_Callback(uint16_t GPIO_Pin);

#endif // __P2PBUTTON_H__