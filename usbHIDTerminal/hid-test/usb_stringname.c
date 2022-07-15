/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <memory.h>

void printarr(int* array, int arrsize)
{
    
    for(int i = 0; i < arrsize; i++)
    {
        printf("Array[%i]: %d \n", i ,array[i]);
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

int main()
{
    int buffer[64];
    int buffersize = sizeof(buffer)/sizeof(buffer[0]);
    
    // printf("buffersize : %d \n", buffersize);
    
    int header[2];
    header[0]=0x00; // 0
    header[1]=0xAA; // 170
    
    int* payloadsize = 0x20; // 32 bytes 
    
    int* commandID = 0x05; 
    
    int stringname_maxsize[32];
    
    int stringname[20];
    stringname[0]=0x43; // 'C' 67
    stringname[1]=0x6C; // 'l' 108
    stringname[2]=0x6F; // 'o' 111
    stringname[3]=0x75; // 'u' 117
    stringname[4]=0x64; // 'd' 100
    stringname[5]=0x20; // ' ' 32
    stringname[6]=0x42; // 'B' 66
    stringname[7]=0x54; // 'T' 84
    stringname[8]=0x2D; // '-' 45
    stringname[9]=0x32; // '2' 50
    
    
    int btfieldplatename[4];
    btfieldplatename[0]=0x20; // ' ' 32
    btfieldplatename[1]=0x23; // '#' 35
    btfieldplatename[2]=0x30; // '0' 48
    btfieldplatename[3]=0x30; // '0' 48
    
    memset(buffer, 0, 64 * sizeof(int));
    printarr(buffer, buffersize);
    
    // for(int i = 0; i < buffersize; i++)
    // {
    //   buffer[i] = 0;
    // }
    
    // memcpy(buffer, header, 2 * sizeof(int)); // 0-1
    
    // printarr(buffer, buffersize);
    
    // memcpy(buffer + 2, &payloadsize, 1 * sizeof(int)); // 2
    
    // // printarr(buffer, buffersize);
    
    // memcpy(buffer +3, &commandID, 1 * sizeof(int)); // 3
    
    // memcpy(buffer + 4, stringname, 20 * sizeof(int)); // 4-14
    
    // // printarr(buffer, buffersize);
    
    // memcpy(buffer + 14, btfieldplatename, 4 * sizeof(int));
    
    // // printarr(buffer, buffersize);
    
    // int current_buff_size = 19;
    
    // int buffer_new[current_buff_size];
    
    // memcpy(buffer_new, buffer, current_buff_size * sizeof(int));
    
    
    // buffer_new[18] = calculateChecksum((uint8_t*)&buffer_new[2],(uint8_t*)&buffer_new[17]);
    
    // printarr(buffer_new, current_buff_size);
    
    
    

//   for(int i = 0; i < buffersize; i++)
//     {
//         printf("Array[%i]: %d \n", i ,buffer[i]);
//     }
    
    


    return 0;
}
