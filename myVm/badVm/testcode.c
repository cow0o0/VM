#include<stdio.h>
#include<stdint.h>

int main(void){

    uint32_t a = 0x31323334;
    uint32_t b = a<<0xa;

    printf("%x\n",b);
    return 0;
}