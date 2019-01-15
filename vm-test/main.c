#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>


#define vPushData    0x10
#define vCall        0x12
#define vEnd        0xff
char *str = "Hello World";

uint8_t bVmData[] = {    vPushData,    0x00, 0x00, 0x00,0x00, 
                    vPushData,    0x00, 0x00, 0x00,0x00,
                    vPushData,    0x00, 0x00, 0x00, 0x00,
                    vPushData,    0x00, 0x00, 0x00,0x00,
                    vCall,    0x00, 0x00, 0x00, 0x00,
                    vEnd};
    