#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<string.h>
#include<stdbool.h>
#include"vmopcode.h"
#include"vmhandler.h"

int main(int argc, char ** argv){

    vm_cpu *cpu=(vm_cpu *)malloc(sizeof(vm_cpu));
    setbuf(stdin,0);
    setbuf(stdout,0);
    setbuf(stderr,0);
    puts("Powered by badrer!");
    printfBadVm();
    printf("---------[LOGIN]---------\n");
    printf("Username:");
    vm_init(cpu);
    char username[7];
    scanf("%7s",username);
    HIDE_CURSOR();
    printf("Password:");
    setBufferedInput(false);
    // scanf("%s",passwd);
    for(uint8_t i = 0;i<6;i++){
        // memcpy(vm_FrameBase+0x24+i,&passwd[i],1);
        read(0,vm_FrameBase+0x24+i,1);
    }
    // memcpy(vm_FrameBase+0x24,passwd,6);
    vm_start(cpu);
    uint8_t v0 = strncmp(username,"badrer",6);
    uint32_t v1 = *(vm_FrameBase+0x19);
    setBufferedInput(true);
    SHOW_CURSOR();
    vm_over(cpu);
    if(v0 == 0 && v1 == 0){
        printf("\n---------[WELCOME]---------\n");
        system("/bin/sh");
    }else{
        printf("\n----------[EXIT]----------\n");
        system("exit");
    }
    return 0;
}
