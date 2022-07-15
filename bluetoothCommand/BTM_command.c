#include "BTM_command.h"

/***************************************************************************
 *
 * BM83-MCU I/O functions
 * -MFB Pin
 * -Reset Pin
 *
****************************************************************************/

// set MFB pin to low
void BTM_Pin_MFB_SetLow()
{
  HAL_GPIO_WritePin(HCI_MFB_GPIO_Port, HCI_MFB_Pin, GPIO_PIN_RESET);
}

// set MFB pin to high
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

/***************************************************************************
 * BM83 UART data packet protocol
 *
 * | Byte 0 | Byte 1-2 | Byte 3 | Byte 4 - XX | Byte (Length + 3) |
 * | Start  | Length   | CMD ID |CMD Parameter|      Checksum     |
 *
 * EX: uint8_t enter_pairing_cmd[7] = {0xAA,0x00,0x03,0x02,0x00,0x5D,0x9E};
 *
 * | Byte 0 | Byte 1-2 | Byte 3 | Byte 4 - XX | Byte (Length + 3) |
 * |  0xAA  |0x00  0x03|  0x02  |  0x00 0x5D  |       0x9E        |
 * | Start  | Length=3 | CMD=2  | Params=0,5D |    CHKSUM=0x9E    |
 *
 * -> Command ID 0x02 -> MMI_Action
 * -> Parameter  0x00 -> Database_index
 * -> Parameter  0x5D -> Fast enter pairing mode
 * -> Checksum   0x9E ->  1+ ~(length + Cmd + params)
 * --------------------> ( 03 + 02 + 5D ) = ( 62 )
 * --------------------> ~(0x62) = 9D
 * --------------------> 9D + 1 = 0x9E
 *
****************************************************************************/

// Calculate checksum by sending UART command packet with start Byte is (Payload Byte) to the end byte of the data packet
uint8_t calculateChecksum(uint8_t* startByte, uint8_t* endByte)
{
    uint8_t checksum = 0;
    while(startByte <= endByte)
    {
        checksum += *startByte;
        startByte++;
    }
    checksum = ~checksum + 1;
    return checksum;
}

// sending UART command packet via HAL UART API
// sendData(Pointer to Byte 0 of UART Packet, sizeofPacket)
void MCU_UART_sendData(uint8_t *Data, uint16_t dataSize)
{
    for(uint16_t i = 0; i < dataSize; i++)
    {
	      HAL_UART_Transmit(&huart1, &Data[i], 1, 50);
    }
}

// MMI Command Power on pressed
void BTM_MFB_On_Pressed()
{
    uint8_t command[7];
    command[0]=0xAA; // Header 0
    command[1]=0x00; // Header 1
    command[2]=0x03; // Payload length
    command[3]=0x02; // Command ID
    command[4]=0x00; // Database index
    command[5]=0x51; // Parameter (Action)
    command[6]=calculateChecksum(&command[2], &command[5]);
    MCU_UART_sendData(&command[0], 7);

}

// MMI Command Power on released
void BTM_MFB_On_Released()
{
    uint8_t command[7];
    command[0]=0xAA; // Header 0
    command[1]=0x00; // Header 1
    command[2]=0x03; // Payload length
    command[3]=0x02; // Command ID
    command[4]=0x00; // Database index
    command[5]=0x52; // Parameter (Action)
    command[6]=calculateChecksum(&command[2], &command[5]);
    MCU_UART_sendData(&command[0], 7);

}

// MMI Command Power off pressed
void BTM_MFB_Off_Pressed()
{
    uint8_t command[7];
    command[0]=0xAA; // Header 0
    command[1]=0x00; // Header 1
    command[2]=0x03; // Payload length
    command[3]=0x02; // Command ID
    command[4]=0x00; // Database index
    command[5]=0x53; // Parameter (Action)
    command[6]=calculateChecksum(&command[2], &command[5]);
    MCU_UART_sendData(&command[0], 7);

}

// MMI Command Power off released
void BTM_MFB_Off_Released()
{
    uint8_t command[7];
    command[0]=0xAA; // Header 0
    command[1]=0x00; // Header 1
    command[2]=0x03; // Payload length
    command[3]=0x02; // Command ID
    command[4]=0x00; // Database index
    command[5]=0x54; // Parameter (Action)
    command[6]=calculateChecksum(&command[2], &command[5]);
    MCU_UART_sendData(&command[0], 7);

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

  uint8_t command[7];
  command[0]=0xAA; // Header 0
  command[1]=0x00; // Header 1
  command[2]=0x03; // Payload length
  command[3]=0x02; // Command ID
  command[4]=0x00; // Database index
  command[5]=0x5E; // Parameter (Action)
  command[6]=calculateChecksum(&command[2], &command[5]);
  MCU_UART_sendData(&command[0], 7);

}

// BTM Power Reset
void BTM_Power_RST()
{

    BTM_Pin_MFB_SetLow();
    BTM_Pin_RESET_SetHigh();
    HAL_Delay(100);

    BTM_Pin_MFB_SetHigh();
    HAL_Delay(20);
    BTM_Pin_RESET_SetLow();
    HAL_Delay(500);

    BTM_Pin_MFB_SetLow();
    BTM_Pin_RESET_SetHigh();

}

// BTM Standby state
void BTM_State_Standby_State()
{

  uint8_t command[7];
  command[0]=0xAA; // Header 0
  command[1]=0x00; // Header 1
  command[2]=0x03; // Payload length
  command[3]=0x01; // Command ID
  command[4]=0x0F; // Parameter (Action)
  command[5]=0x00; // Parameter (Action)
  command[6]=calculateChecksum(&command[2], &command[5]);
  MCU_UART_sendData(&command[0], 7);
    
}

// BTM Discoverable 
void BTM_State_Enter_Pairing()
{

  uint8_t command[7];
  command[0]=0xAA; // Header 0
  command[1]=0x00; // Header 1
  command[2]=0x03; // Payload length
  command[3]=0x02; // Command ID
  command[4]=0x00; // Database index
  command[5]=0x5D; // Parameter (Action)
  command[6]=calculateChecksum(&command[2], &command[5]);
  MCU_UART_sendData(&command[0], 7);

}

// BTM Undiscoverable 
void BTM_State_Exit_Pairing()
{

  uint8_t command[7];
  command[0]=0xAA; // Header 0
  command[1]=0x00; // Header 1
  command[2]=0x03; // Payload length
  command[3]=0x02; // Command ID
  command[4]=0x00; // Database index
  command[5]=0x6B; // Parameter (Action)
  command[6]=calculateChecksum(&command[2], &command[5]);
  MCU_UART_sendData(&command[0], 7);

}

// Disconnect all Link profiles 
void BTM_State_Disconnected_All_Profile()
{

  uint8_t command[6];
  command[0]=0xAA; // Header 0
  command[1]=0x00; // Header 1
  command[2]=0x02; // Payload length
  command[3]=0x18; // Command ID
  command[4]=0x0F; // Parameter (Action)
  command[5]=calculateChecksum(&command[2], &command[4]);
  MCU_UART_sendData(&command[0], 6);

}

// force BTM into the non-connectable mode
void BTM_State_Mode_Inactive()
{

  uint8_t command[7];
  command[0]=0xAA; // Header 0
  command[1]=0x00; // Header 1
  command[2]=0x03; // Payload length
  command[3]=0x13; // Command ID
  command[4]=0x03; // Parameter (Action)
  command[5]=0x00; // Parameter (Action)
  command[6]=calculateChecksum(&command[2], &command[5]);
  MCU_UART_sendData(&command[0], 7);

}

// To resume BTM to the normal mode
void BTM_State_Mode_Resume()
{

  uint8_t command[7];
  command[0]=0xAA; // Header 0
  command[1]=0x00; // Header 1
  command[2]=0x03; // Payload length
  command[3]=0x13; // Command ID
  command[4]=0x03; // Parameter (Action)
  command[5]=0x01; // Parameter (Action)
  command[6]=calculateChecksum(&command[2], &command[5]);
  MCU_UART_sendData(&command[0], 7);

}

// Connected to A2DP Profile
void BTM_State_Connect_A2DP()
{

  uint8_t command[7];
  command[0]=0xAA; // Header 0
  command[1]=0x00; // Header 1
  command[2]=0x03; // Payload length
  command[3]=0x15; // Command ID
  command[4]=0x00; // Database index
  command[5]=0x01; // Parameter (Action)
  command[6]=calculateChecksum(&command[2], &command[5]);
  MCU_UART_sendData(&command[0], 7);

}

// Change MCU UART Buffer size
void BTM_Set_UART_Buffersize()
{

  uint8_t command[7];
  command[0]=0xAA; // Header 0
  command[1]=0x00; // Header 1
  command[2]=0x03; // Payload length
  command[3]=0x1F; // Command ID
  command[4]=0x01; // Parameter (Action)
  command[5]=0x00; // Parameter (Action)
  command[6]=calculateChecksum(&command[2], &command[5]);
  MCU_UART_sendData(&command[0], 7);

}

// Set BTM Link paring timeout 
void BTM_Set_Pairing_Timeout()
{

  uint8_t command[6];
  command[0]=0xAA; // Header 0
  command[1]=0x00; // Header 1
  command[2]=0x02; // Payload length
  command[3]=0x07; // Command ID
  command[4]=0x01; // Parameter (Action)
  command[5]=calculateChecksum(&command[2], &command[5]);
  MCU_UART_sendData(&command[0], 6);

}

// Set BTM Device name
void BTM_Set_Device_Name()
{

    uint8_t command[19];
    command[0]=0xAA; // Header 0
    command[1]=0x00; // Header 1
    command[2]=0x0E; // Payload length
    command[3]=0x05; // Command ID
    command[4]=0x43; // 'C'
    command[5]=0x6C; // 'l;
    command[6]=0x6F; // 'o'
    command[7]=0x75; // 'u'
    command[8]=0x64; // 'd'
    command[9]=0x20; // ' '
    command[10]=0x42; // 'B'
    command[11]=0x54; // 'T'
    command[12]=0x2D; // '-'
    command[13]=0x31; // '1'
    command[14]=0x20; // ' '
    command[15]=0x23; // '#'
    command[16]=0x31; // '1'
    command[17]=0x20; // ' ' // reserved space for 2 digits ID character
    command[18]=calculateChecksum(&command[2], &command[17]);
    MCU_UART_sendData(&command[0], 18);

}

// Set BTM Local device name
void BTM_Set_Local_Name()
{
    
  uint8_t command[22];
  command[0]=0xAA; // Header 0
  command[1]=0x00; // Header 1
  command[2]=0x11; // Payload length
  command[3]=0x35; // Command ID
  command[4]=0x00; // Parameter (Change Device Name)
  command[5]=0x00; // Option (Reserved set it 0x00)
  command[6]=0x0D; // String Length
  command[7]=0x43; // 'C'
  command[8]=0x6C; // 'l'
  command[9]=0x6F; // 'o'
  command[10]=0x75; // 'u'
  command[11]=0x64; // 'd'
  command[12]=0x20; // ' '
  command[13]=0x42; // 'B'
  command[14]=0x54; // 'T'
  command[15]=0x2D; // '-'
  command[16]=0x31; // '1'
  command[17]=0x20; // ' '
  command[18]=0x23; // '#'
  command[19]=0x31; // '1'
  command[20]=0x20; // ' ' // reserved space for 2 digits ID character
  command[21]=calculateChecksum(&command[2], &command[20]);
  MCU_UART_sendData(&command[0], 21);

}

// Reset some EEPROM memory to Default value (Erase paired device information)
void BTM_Reset_Flash_Default()
{

  uint8_t command[7];
  command[0]=0xAA; // Header 0
  command[1]=0x00; // Header 1
  command[2]=0x03; // Payload length
  command[3]=0x02; // Command ID
  command[4]=0x00; // Database index
  command[5]=0x56; // Parameter (Action)
  command[6]=calculateChecksum(&command[2], &command[5]);
  MCU_UART_sendData(&command[0], 7);

}

// BTM Link-back to A2DP Profile
void BTM_Linkback_A2DP()
{


  uint8_t command[6];
  command[0]=0xAA; // Header 0
  command[1]=0x00; // Header 1
  command[2]=0x02; // Payload length
  command[3]=0x17; // Command ID
  command[4]=0x02; // Parameter (Action)
  command[5]=calculateChecksum(&command[2], &command[4]);
  MCU_UART_sendData(&command[0], 6);

}

// BTM Link-back to Last-device
void BTM_Linkback_Lastdevice()
{

  uint8_t command[6];
  command[0]=0xAA; // Header 0
  command[1]=0x00; // Header 1
  command[2]=0x02; // Payload length
  command[3]=0x17; // Command ID
  command[4]=0x00; // Parameter (Action)
  command[5]=calculateChecksum(&command[2], &command[4]);
  MCU_UART_sendData(&command[0], 6);

}
