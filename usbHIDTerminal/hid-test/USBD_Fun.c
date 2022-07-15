
/*
*
* -> fixed size
*
*
*
*
*/

Cloud BT-2 #01

USBD_GetString(uint8_t* ReceiveUSBString)
{
    uint8_t buffer_size = 25;
    uint8_t buffer[buffer_size];

    memcpy(buffer, ReceiveUSBString, buffer_size * sizeof(uint8_t) );


}


void USBD_Custom_Set_BluetoothName(uint8_t* string)
{
    uint8_t buff_size = 64;
    uint8_t buffer[buff_size];

    buffer[0] = 0xAA; // Header
    buffer[1] = 0x00; // Packet length LSB
    buffer[2] = 25; // (1_cmd + param[20_string name + 4_bluetooth_ID]) // 25 Bytes // Packet lenth MSB
    memcpy(buffer + 2, string, 25 * sizeof(uint8_t));
    buffer[26] = calculateChecksum(&buffer[2],&buffer[25]);

    for(uint8_t i = 0; i < 26; i++ )
    {
        HAL_UART_transmit(&huart1, &buffer, 26, 100);
        printf("HAL_[%i] : %c \n", i, buffer[i]);
    }

}

































