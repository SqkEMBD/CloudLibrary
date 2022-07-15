#include "BTM_command.h"

// set Multi-fuction-button pin to low
void BTM_Pin_MFB_SetLow()
{
  HAL_GPIO_WritePin(HCI_MFB_GPIO_Port, HCI_MFB_Pin, GPIO_PIN_RESET);
}

// set Multi-fuction-button pin to high
void BTM_Pin_MFB_SetHigh()
{
  HAL_GPIO_WritePin(HCI_MFB_GPIO_Port, HCI_MFB_Pin, GPIO_PIN_SET);
}
// set reset pin to low
void BTM_Pin_RESET_SetLow()
{
  HAL_GPIO_WritePin(HCI_RST_GPIO_Port, HCI_RST_Pin, GPIO_PIN_RESET);
}

// set reset pin to high
void BTM_Pin_RESET_SetHigh()
{
  HAL_GPIO_WritePin(HCI_RST_GPIO_Port, HCI_RST_Pin, GPIO_PIN_SET);
}

// MMI Command Power on pressed
void BTM_MFB_On_Pressed()
{
    uint8_t command[7];
    command[0]=0xAA; // Header 0
    command[1]=0x00; // Header 1
    command[2]=0x03; // Payload
    command[3]=0x02; // Command ID
    command[4]=0x00; // Params
    command[5]=0x51; // Chksum
    command[6]=0xAA; // End

//   uint8_t command[7] = {0xAA,0x00,0x03,0x02,0x00,0x51,0xAA};
//  HAL_UART_Transmit(&huart2, (uint8_t* )command, sizeof(command), 50);
    for(int i = 0; i < sizeof(command); i++)
    {
        HAL_UART_Transmit(&huart2, &command[i], 1, 50);
        HAL_UART_Transmit(&huart1, &command[i], 1, 50);
    }
}
// MMI Command Power on released
void BTM_MFB_On_Released()
{
    uint8_t command[7];
    command[0]=0xAA; // Header 0
    command[1]=0x00; // Header 1
    command[2]=0x03; // Payload
    command[3]=0x02; // Command ID
    command[4]=0x00; // Params
    command[5]=0x52; // Chksum
    command[6]=0xA9; // End

//   uint8_t command[7] = {0xAA,0x00,0x03,0x02,0x00,0x52,0xA9};

    for(int i = 0; i < sizeof(command); i++)
    {
        HAL_UART_Transmit(&huart2, &command[i], 1, 50);
        HAL_UART_Transmit(&huart1, &command[i], 1, 50);
    }

}

// MMI Command Power off pressed
void BTM_MFB_Off_Pressed()
{
    uint8_t command[7] = {0xAA,0x00,0x03,0x02,0x00,0x53,0xA8};

    for(int i = 0; i < sizeof(command); i++)
    {
        HAL_UART_Transmit(&huart2, &command[i], 1, 50);
        HAL_UART_Transmit(&huart1, &command[i], 1, 50);
    }
}

// MMI Command Power off released
void BTM_MFB_Off_Released()
{
    uint8_t command[7] = {0xAA,0x00,0x03,0x02,0x00,0x54,0xA7};

    for(int i = 0; i < sizeof(command); i++)
    {
      HAL_UART_Transmit(&huart2, &command[i], 1, 50);
      HAL_UART_Transmit(&huart1, &command[i], 1, 50);
    }
}

// BTM Power on
void BTM_Power_ON()
{
    BTM_MFB_On_Pressed();
    BTM_MFB_On_Released();
}

// BTM Power off
void BTM_Power_OFF()
{
    BTM_MFB_Off_Pressed();
    BTM_MFB_Off_Released();
}

// BTM Power off(soft) 
void BTM_Power_OFF_Soft()
{
    uint8_t command[7] = {0xAA,0x00,0x03,0x02,0x00,0x5E,0x90};

    for(int i = 0; i < sizeof(command); i++)
    {
        HAL_UART_Transmit(&huart2, &command[i], 1, 50);
        HAL_UART_Transmit(&huart1, &command[i], 1, 50);
    }

}
// BTM Power Reset
void BTM_Power_RST()
{

    BTM_Pin_MFB_SetLow();
    BTM_Pin_RESET_SetLow();
    HAL_Delay(100);

    BTM_Pin_MFB_SetHigh();
    HAL_Delay(20);
    BTM_Pin_RESET_SetHigh();
    HAL_Delay(500);

    BTM_Pin_MFB_SetLow();
    BTM_Pin_RESET_SetLow();

}

// BTM Standby state
void BTM_State_Standby_State()
{
    
    uint8_t command[7] = {0xAA,0x00,0x03,0x01,0x0F,0x00,0xED};

    for(int i = 0; i < sizeof(command); i++)
    {
        HAL_UART_Transmit(&huart2, &command[i], 1, 50);
        HAL_UART_Transmit(&huart1, &command[i], 1, 50);
    }
}

// BTM Discoverable 
void BTM_State_Enter_Pairing()
{
  uint8_t command[7] = {0xAA,0x00,0x03,0x02,0x00,0x5D,0x9E};

  for(int i = 0; i < sizeof(command); i++){

      HAL_UART_Transmit(&huart2, &command[i], 1, 50);
      HAL_UART_Transmit(&huart1, &command[i], 1, 50);
  }
}

// BTM Undiscoverable 
void BTM_State_Exit_Pairing()
{
    uint8_t command[7] = {0xAA,0x00,0x03,0x02,0x00,0x6B,0x90};

    for(int i = 0; i < sizeof(command); i++)
    {
        HAL_UART_Transmit(&huart2, &command[i], 1, 50);
        HAL_UART_Transmit(&huart1, &command[i], 1, 50);
    }
}

// Disconnect all Link profiles 
void BTM_State_Disconnected_All()
{
    uint8_t command[6] = {0xAA,0x00,0x02,0x18,0x0F,0xD7};

    for(int i = 0; i < sizeof(command); i++)
    {
        HAL_UART_Transmit(&huart2, &command[i], 1, 50);
        HAL_UART_Transmit(&huart1, &command[i], 1, 50);
    }   
}

// force BTM into the non-connectable mode
void BTM_State_Mode_Inactive()
{
    uint8_t command[7] = {0xAA, 0x00, 0x03, 0x13, 0x03, 0x00, 0xE7};

    for(int i = 0; i < sizeof(command); i++)
    {
        HAL_UART_Transmit(&huart2, &command[i], 1, 50);
        HAL_UART_Transmit(&huart1, &command[i], 1, 50);
    }
}

// To resume BTM to the normal mode
void BTM_State_Mode_Resume()
{
    uint8_t command[7] = {0xAA, 0x00, 0x03, 0x13, 0x03, 0x01, 0xE6};

    for(int i = 0; i < sizeof(command); i++)
    {
        HAL_UART_Transmit(&huart2, &command[i], 1, 50);
        HAL_UART_Transmit(&huart1, &command[i], 1, 50);
    }
}

// Connected to A2DP Profile
void BTM_State_Connect_A2DP()
{
    uint8_t command[7] = {0xAA, 0x00, 0x03, 0x15, 0x00, 0x01, 0xE7};

    for(int i = 0; i < sizeof(command); i++)
    {
        HAL_UART_Transmit(&huart2, &command[i], 1, 50);
        HAL_UART_Transmit(&huart1, &command[i], 1, 50);
    }
}

// Change MCU UART Buffer size
void BTM_Change_UART_Buffersize()
{
     //256
    uint8_t command[7] = {0xAA, 0x00, 0x03, 0x1F, 0x01, 0x00, 0xDD};

    for(int i = 0; i < sizeof(command); i++)
    {
        HAL_UART_Transmit(&huart2, &command[i], 1, 50);
        HAL_UART_Transmit(&huart1, &command[i], 1, 50);
    }
}

// Set BTM Link paring timeout 
void BTM_Change_Pairing_Timeout()
{

    // AA 00 02 07 01 F6 // 30 secs
    // AA 00 02 07 02 F5 // 60 secs

    uint8_t command[6] = {0xAA,0x00,0x02,0x07,0x01,0xF6};

    for(int i = 0; i < sizeof(command); i++)
    {
        HAL_UART_Transmit(&huart2, &command[i], 1, 50);
        HAL_UART_Transmit(&huart1, &command[i], 1, 50);
    }
}

// Set BTM Device name
void BTM_Change_Device_Name()
{
    
    uint8_t command[19];
    command[0]=0xAA;            
    command[1]=0x00;
    command[2]=0x0F;
    command[3]=0x05;
    command[4]=0x43;
    command[5]=0x6C;
    command[6]=0x6F;
    command[7]=0x75;
    command[8]=0x64;
    command[9]=0x20;
    command[10]=0x42;
    command[11]=0x54;
    command[12]=0x2D;
    command[13]=0x31;
    command[14]=0x20;
    command[15]=0x23;
    command[16]=0x30;
    command[17]=0x30;
    command[18]=0x3E;

    for(int i = 0; i < sizeof(command); i++)
    {
        HAL_UART_Transmit(&huart2, &command[i], 1, 50);
        HAL_UART_Transmit(&huart1, &command[i], 1, 50);
    }
}

// Set BTM Local device name
void BTM_Change_Local_Name()
{
    
    uint8_t command[21] = {0xAA,0x00,0x12,0x35,0x00,0x00,0x0E,0x6C,0x6F,0x75,0x64,0x20,0x42,0x54,0x2D,
0x31,0x20,0x23,0x30,0x30,0xFD};

    for(int i = 0; i < sizeof(command); i++)
    {
        HAL_UART_Transmit(&huart2, &command[i], 1, 50);
        HAL_UART_Transmit(&huart1, &command[i], 1, 50);
    }
}

// Reset some flash memory informations (paired device information)
void BTM_Reset_Flash_Default()
{
    uint8_t command[7] = {0xAA, 0x00, 0x03, 0x02, 0x00, 0x56, 0xA5};

    for(int i = 0; i < sizeof(command); i++)
    {
        HAL_UART_Transmit(&huart2, &command[i], 1, 50);
        HAL_UART_Transmit(&huart1, &command[i], 1, 50);
    }
}

// Linkback to A2DP Profile
void BTM_Linkback_A2DP()
{
    uint8_t command[6] = {0xAA, 0x00, 0x02, 0x17, 0x02, 0xE5}; 

    for(int i = 0; i < sizeof(command); i++)
    {
        HAL_UART_Transmit(&huart2, &command[i], 1, 50);
        HAL_UART_Transmit(&huart1, &command[i], 1, 50);
    }
}

// Linkback to Lastdevice
void BTM_Linkback_Lastdevice()
{
    uint8_t command[6] = {0xAA, 0x00, 0x02, 0x17, 0x00, 0xE7};
    
    for(int i = 0; i < sizeof(command); i++)
    {
        HAL_UART_Transmit(&huart2, &command[i], 1, 50);
        HAL_UART_Transmit(&huart1, &command[i], 1, 50);
    }
}