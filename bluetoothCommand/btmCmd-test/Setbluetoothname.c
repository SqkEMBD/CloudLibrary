void USBD_HID_SetBluetoothname(uint8_t* usbbuffer)
{
	uint8_t Packet[64];
	uint8_t Command_len 		= 	usbbuffer[0] + 1U;  // ptr to uint8_t 1-> cmdID
	uint8_t chksum_pos 			= 	Command_len + 3U;
	uint8_t packet_end 			= 	chksum_pos + 1U;

	Packet[0] = 0xAA;			// BT_Module Packet Header
	Packet[1] = 0x00;			// Packet Lenth *LSB*
	Packet[2] = Command_len; 	// Packet Lenth *MSB* -> Command_ID (1 Byte) + Parameters (Shouldn't over 32 Bytes)
	Packet[3] = 0x05; 			// UART Command 0x05 *Change Bluetooth device name on discovery mode*

	memcpy(&Packet[4] , &usbbuffer[1], chksum_pos); 					   // copy buffer that receives from USB to new buffer to send via UART Protocol.

	//	memcpy(&Packet[4] , &usbbuffer[1], Command_len + 4 ); 					   // copy buffer that receives from USB to new buffer to send via UART Protocol.
	Packet[chksum_pos] = calculateChecksum(&Packet[2], &Packet[packet_end]); // Add checksum at the tail of the UART Packet.

	// Transmit Command Packet via MCU UART
	// from head(packet[0]) to the tail(checksum)
	for(uint8_t i = 0; i < packet_end; i++)
	{
		HAL_UART_Transmit(&huart1, &Packet[i], 1, 100);
	}

}
