void USBD_HID_SendRawDataCommand(uint8_t* usbbuffer)
{
	uint8_t Packet[64];
	uint8_t* ptr_packet_len = &usbbuffer[0]; 	  // ptr to Add:usbbuffer[0] -> len
	uint8_t packet_len = *(ptr_packet_len);
	uint8_t chksum_pos = packet_len+2;
	uint8_t packet_end = chksum_pos+1;

	Packet[0] = 0xAA;
	Packet[1] = 0x00;
	memcpy(Packet + 2, &usbbuffer[1], packet_len);
//	Packet[chksum_pos] = calculateChecksum(&Packet[3], &Packet[packet_len]);
	Packet[chksum_pos] = 'X';

	for(uint8_t i = 0; i < packet_end; i++)
	{
		HAL_UART_Transmit(&huart1, &Packet[i], 1, 100);
	}

}