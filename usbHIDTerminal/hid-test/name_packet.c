/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <stdint.h>
#include <string.h>

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

void printarr(uint8_t* array, int arrsize)
{
    for(int i=0; i < arrsize; i++)
    {
        printf("[%i] : %c \n", i, array[i]);
    }
}

int main()
{
	uint8_t cmd_id = 0x05;

	const uint8_t btid_size = 4;
	uint8_t btid_str[btid_size];
	        btid_str[0] = 0x20; // ' ' 32
	        btid_str[1] = 0x23; // '#' 35
	        btid_str[2] = 0x30; // '0' 48
	        btid_str[3] = 0x30; // '0' 48
/******************************************************************************/
	uint8_t USBD_GetStringname[24];
	    USBD_GetStringname[0]=0x43; // 'C' 67
	    USBD_GetStringname[1]=0x6C; // 'l' 108
	    USBD_GetStringname[2]=0x6F; // 'o' 111
	    USBD_GetStringname[3]=0x75; // 'u' 117
	    USBD_GetStringname[4]=0x64; // 'd' 100
	    USBD_GetStringname[5]=0x20; // ' ' 32
	    USBD_GetStringname[6]=0x42; // 'B' 66
	    USBD_GetStringname[7]=0x54; // 'T' 84
	    USBD_GetStringname[8]=0x2D; // '-' 45
	    USBD_GetStringname[9]=0x32; // '2' 50
/******************************************************************************/
	uint8_t btid_str_len = strlen( (char*)btid_str );
	uint8_t str_name_len = strlen( (char*)USBD_GetStringname );
	uint8_t Payload_data_len = str_name_len + btid_str_len;
/******************************************************************************/
	uint8_t UART_Header_size = 4;
	uint8_t UART_header_data[UART_Header_size];
	        UART_header_data[0] = 0xAA; // Start of packet
	        UART_header_data[1] = 0x00; // Packet length MSB ->> null character
	        UART_header_data[2] = Payload_data_len; // Packet length LSB
	        UART_header_data[3] = cmd_id; // Command/Event ID (OP-Code)
/******************************************************************************/
	uint8_t uart_buffer[64];
/******************************************************************************/
	memcpy(uart_buffer,
			&UART_header_data,
			UART_Header_size * sizeof(uint8_t));

	memcpy(uart_buffer + UART_Header_size,
			&USBD_GetStringname,
			str_name_len * sizeof(uint8_t));

	memcpy(uart_buffer + (UART_Header_size + str_name_len),
			btid_str,
			btid_size * sizeof(uint8_t));

	uint8_t CRC_CAL = calculateChecksum(&uart_buffer[2], &uart_buffer[str_name_len + btid_size + 1]);

	memcpy(buffer + (UART_Header_size + str_name_len + btid_size),
			&CRC_CAL,
			1 * sizeof(uint8_t));

	MCU_UART_Transmit(uart_buffer, 64);

/******************************************************************************/
    return 0;
}

//

uint8_t uart_buffer[64];
    uart_buffer[0] = 0xAA; // Start of packet
    uart_buffer[1] = 0x00; // Packet length MSB ->> null character
    uart_buffer[2] = 0x0E;// Payload_data_len; // Packet length LSB
    uart_buffer[3] = 0x05;// cmd_id; // Command/Event ID (OP-Code)

    uart_buffer[4]=0x43; // 'C' 67
    uart_buffer[5]=0x6C; // 'l' 108
    uart_buffer[6]=0x6F; // 'o' 111
    uart_buffer[7]=0x75; // 'u' 117
    uart_buffer[8]=0x64; // 'd' 100
    uart_buffer[9]=0x20; // ' ' 32
    uart_buffer[10]=0x42; // 'B' 66
    uart_buffer[11]=0x54; // 'T' 84
    uart_buffer[12]=0x2D; // '-' 45
    uart_buffer[13]=0x32; // '2' 50
   
    uart_buffer[14] = 0x20; // ' ' 32
    uart_buffer[15] = 0x23; // '#' 35
    uart_buffer[16] = 0x30; // '0' 48
    uart_buffer[17] = 0x30; // '0' 48
    uart_buffer[18] = 0x4E; // CRC_CAL; // 










