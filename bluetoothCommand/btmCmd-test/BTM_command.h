#ifndef __BTM_COMMAND_H__
#define __BTM_COMMAND_H__

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "main.h"

// Global
UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;

// Global variables
uint8_t BTM_String_Name[10] = {0x43,0x6C,0x6F,0x75,0x64,0x20,0x42,0x54,0x2D,0x31}; // Cloud BT-1
uint8_t BTM_String_ID[4] = {0x20,0x23,0x30,0x30}; // #00

// GPIO PINS
void BTM_Pin_MFB_SetLow();
void BTM_Pin_MFB_SetHigh();
void BTM_Pin_RESET_SetLow();
void BTM_Pin_RESET_SetHigh();

// UART MMI Action
void BTM_MFB_On_Pressed();
void BTM_MFB_On_Released();
void BTM_MFB_Off_Pressed();
void BTM_MFB_Off_Released();

// UART Command Power State
void BTM_Power_ON();
void BTM_Power_OFF();
void BTM_Power_OFF_Soft();
void BTM_Power_RST();

// UART Command Operatation States
void BTM_State_Standby_State();
void BTM_State_Enter_Pairing();
void BTM_State_Exit_Pairing();
void BTM_State_Disconnected_All();
void BTM_State_Mode_Inactive();
void BTM_State_Mode_Resume();
void BTM_State_Connect_A2DP();

// UART Command Parameter Changes
void BTM_Change_UART_Buffersize();
void BTM_Change_Pairing_Timeout();
void BTM_Change_Device_Name();
void BTM_Change_Local_Name();

// Reset (Remove All Paired device)
void BTM_Reset_Flash_Default();

// Profile Linkback
void BTM_Linkback_A2DP();
void BTM_Linkback_Lastdevice();



#endif // __BTM_COMMAND_H__