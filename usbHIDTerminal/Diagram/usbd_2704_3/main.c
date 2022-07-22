/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

void USBtoBluetooth_DataPacket(uint8_t* name_str, uint8_t name_len, uint8_t name_size);

void PrintArray(uint8_t* arr, uint8_t arrsize)
{
    for(int i = 0; i < arrsize; i++)
    {
        printf("ARR[%i] : %c \n", i, arr[i]);
    }
}

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

void GetString_USBD(uint8_t* USB_Buffer)
{
    uint8_t btid[5];
    btid[0] = ' ';
    btid[1] = '#';
    btid[2] = '0';
    btid[3] = '1';
    
    uint8_t id_len = strlen(btid);
    uint8_t btid_size = sizeof(btid)/sizeof(btid[0]);
    
    uint8_t buffer1_size = sizeof(USB_Buffer)/sizeof(USB_Buffer[0]);
    uint8_t buffer1_len = (uint8_t)strlen(USB_Buffer);
    
    uint8_t buffer2_size = (buffer1_len + 1);
    uint8_t buffer2[buffer2_size];
    strcpy(buffer2,USB_Buffer);
    
    uint8_t buffer2_sizeof = sizeof(buffer2)/sizeof(buffer2[0]);
    uint8_t buffer2_len = (uint8_t)strlen(buffer2);
    
    
    uint8_t buffer3_size = buffer2_len + btid_size;
    uint8_t buffer3[buffer3_size];
    
    strcpy(buffer3, buffer2);
    strcat(buffer3, btid);
    
    uint8_t buffer3_len = (uint8_t)strlen(buffer3);
    
    USBtoBluetooth_DataPacket(buffer3, buffer3_len, buffer3_size);

}


void USBtoBluetooth_DataPacket(uint8_t* name_str, uint8_t name_len, uint8_t name_size)
{
   uint8_t max_size = 32;
   
   uint8_t header[2];
   header[0] = 0xAA;
   header[1] = 0x00;
   
   uint8_t packet_length = name_len;
   uint8_t buffer[packet_length];
   strcpy(buffer, name_str);
 
   buffer[packet_length] = calculateChecksum(&buffer[0],&buffer[packet_length]);
   
   PrintArray(buffer, name_size);
}


int main()
{
    
    // printf("**********************************************\n");
   
    uint8_t usb_buffer[20] = "Cloud BT-2";
    GetString_USBD(usb_buffer);
    
 
    return 0;
}

