/*
 * DIPSwitch.h
 *
 *  Created on: Jul 22, 2022
 *  Latest modified on: Jul 22, 2022
 *      Author: Amornsak <amornsak-ra@starsmicro.com>
 */

#ifndef __DIPSWITCH_H__
#define __DIPSWITCH_H__

// standard library includes
#include <stdint.h>

// user library includes

// Basic GPIO definition
// Consists of a port and a pin using the HAL type definitions of these
// HAL abstractions
typedef struct
{
    GPIO_TypeDef *port;
    uint16_t pin;
} GPIO_DEFINITION;

uint32_t getDipSwitchValue(const GPIO_DEFINITION *defs, int size);
uint8_t getSecuredState();
uint8_t getRFPowerIndex();
uint8_t getBTId();


#endif // __DIPSWITCH_H__