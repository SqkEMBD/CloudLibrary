packet()
{
  uint8_t command[64];
          command[0]=0x00;
          command[1]=0xAA;
          command[2]=0x20; // 32 Bytes


          command[3]=//0
          command[4]=//1
          command[5]=//2
          command[6]=//3
          command[7]=//4
          command[8]=//5
          command[9]=//6
          command[10]=//7
          command[11]=//8
          command[12]=//9
          command[13]=//10
          command[14]=//11
          command[15]=//12
          command[16]=//13
          command[17]=//14
          command[18]=//15
          command[19]=//16
          command[20]=//17
          command[21]=//18
          command[22]=//19
          command[23]=//20
          command[24]=//21
          command[25]=//22
          command[26]=//23
          command[27]=//24
          command[28]=//25
          command[29]=//26
          command[30]=//27
          command[31]=//28
          command[32]=//29
          command[33]=//30
          command[34]=//31
          
          command[35]=calculateChecksum(&command[2],&command[34]);//CRC
          
          

}




static int8_t CUSTOM_HID_OutEvent_FS(uint8_t* state)
{
	/* USER CODE BEGIN 6 */

	int8_t string_size;
	string_size = charatercount(state);

	uint8_t buffer[string_size];
	memcpy(buffer, state, string_size);

	HAL_UART_Transmit(&huart1, (uint8_t*)buffer, string_size, 100); // BTM Command
	USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS,(uint8_t*)buffer,64); // PC HID Terminal

	return (0);
  /* USER CODE END 6 */
}

static int8_t charatercount(uint8_t* string)
{
	uint8_t buffer[64]; // maximum size of string
	int8_t charscounter = 0;

	memcpy(buffer,string,64);

	for(int i = 0; i < sizeof(buffer); i++)
	{
		if(buffer[i] != '\0')
		{
			charscounter++;
		}
	}
	return charscounter;
}

// Simulate Change BTM Name
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

void changeBT_devicename()
{

    new_name_length = charatercount(string);

    command[size];

    //reserved space for string and header
    command[0] = 0xAA;
    command[1] = 0x00;
    command[2] = (0x01) + (new_name_length);

    strcat[ new_name_string]

    command[end] = calculateChecksum();

    UARTSend(&command,sizeof(command), 100);

}

if(new_name_string_length < 32)


