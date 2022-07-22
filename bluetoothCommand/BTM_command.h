/*
 * BTM_command.h
 *
 *  Created on: Jul 22, 2022
 *  Latest modified on: Jul 22, 2022
 *      Author: Amornsak <amornsak-ra@starsmicro.com>
 */

#ifndef __BTM_COMMAND_H__
#define __BTM_COMMAND_H__

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "main.h"

// External variables
UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;

// Global variables
//uint8_t BTM_String_Name[10] = {0x43,0x6C,0x6F,0x75,0x64,0x20,0x42,0x54,0x2D,0x31}; // Cloud BT-1
//uint8_t BTM_String_ID[4] = {0x20,0x23,0x30,0x30}; // #00

// BM83-MCU I/O
void BTM_Pin_MFB_SetLow();
void BTM_Pin_MFB_SetHigh();
void BTM_Pin_RESET_SetLow();
void BTM_Pin_RESET_SetHigh();

// UART Command Power State Control
void BTM_MFB_On_Pressed();
void BTM_MFB_On_Released();
void BTM_MFB_Off_Pressed();
void BTM_MFB_Off_Released();
void BTM_Power_ON();
void BTM_Power_OFF();
void BTM_Power_OFF_Soft();
void BTM_Power_RST();

// UART Command Operation State
void BTM_State_Standby_State();
void BTM_State_Enter_Pairing();
void BTM_State_Exit_Pairing();
void BTM_State_Disconnected_All_Profile();
void BTM_State_Mode_Inactive();
void BTM_State_Mode_Resume();
void BTM_State_Connect_A2DP();

// UART Command BTM Parameter Settings
void BTM_Set_UART_Buffersize();
void BTM_Set_Pairing_Timeout();
void BTM_Set_Device_Name();
void BTM_Set_Local_Name();

// Reset some EEPROM memory to Default value (Erase paired device information)
void BTM_Reset_Flash_Default();

// Profile Link-back
void BTM_Linkback_A2DP();
void BTM_Linkback_Lastdevice();

// Send UART Command function
uint8_t calculateChecksum(uint8_t *startByte, uint8_t *endByte);
void MCU_UART_sendData(uint8_t *Data, uint16_t dataSize);


#endif // __BTM_COMMAND_H__
