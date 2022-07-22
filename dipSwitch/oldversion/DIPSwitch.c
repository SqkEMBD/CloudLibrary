/*
 * DIPSwitch.c
 *
 *  Created on: Jul 22, 2022
 *  Latest modified on: Jul 22, 2022
 *      Author: Amornsak <amornsak-ra@starsmicro.com>
 */

#include "DIPSwitch.h"

// Basic GPIO definition
// Consists of a port and a pin using the HAL type definitions of these
// HAL abstractions
//
uint32_t getDipSwitchValue(const GPIO_DEFINITION *defs, int size)
{
    // Build up an up-to 32 bit unsigned integer value, based on 1 or more
    // switch positions in a DIP switch, read by the same number of GPIO pins.
    // Each switch position is assigned the next binary weighted bit
    // position, the first DIP switch read will correspond to the MSB of
    // the resulting integer value.
    //
    uint32_t result = 0UL;
    for (int i = 0; i < size; i++)
    {
        // shift the result before we apply the next bit position.
        //
        result <<= 1;

        // Note: We check for GPIO_PIN_RESET (a value of zero on the pin),
        // as this is the logical "on" state of a DIP switch,
        // as the switches short to 0v when closed
        //
        if (HAL_GPIO_ReadPin(defs[i].port, defs[i].pin) == GPIO_PIN_RESET)
        {
            result |= 1UL;
        }
    }
    return result;
}

uint8_t getSecuredState()
{
	uint8_t state = -1;
	if(HAL_GPIO_ReadPin(Secure_GPIO_Port, Secure_Pin) == GPIO_PIN_RESET)
	{
		return state = 1;
	}
	else
	{
		return state = 0;
	}

}

uint8_t getRFPowerIndex()
{
    static const GPIO_DEFINITION defs[3] =
    {
		{ RF_PO_2_GPIO_Port, RF_PO_2_Pin },
		{ RF_PO_1_GPIO_Port, RF_PO_1_Pin },
		{ RF_PO_0_GPIO_Port, RF_PO_0_Pin }
    };

//    return (uint8_t)( (getDipSwitchValue(defs,3) + 1UL) & 0xFF);
    return (uint8_t)( (getDipSwitchValue(defs,3) ) & 0xFF);
}

uint8_t getBTId()
{
    static const GPIO_DEFINITION defs[4] =
    {
		{ BT_ID_3_GPIO_Port, BT_ID_3_Pin },
		{ BT_ID_2_GPIO_Port, BT_ID_2_Pin },
		{ BT_ID_1_GPIO_Port, BT_ID_1_Pin },
		{ BT_ID_0_GPIO_Port, BT_ID_0_Pin }

    };

    // Note: Add 1 to the result, to get an index between 1 and 16
    //
    return (uint8_t)((getDipSwitchValue(defs, 4) + 1UL) & 0XFF);
    // return (uint8_t)((getDipSwitchValue(defs, 4) ) & 0XFF);
}
