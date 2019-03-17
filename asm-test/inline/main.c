#include<stdio.h>
#include<stdlib.h>
#define CAL ({\
    asm("addl $10,result\n\t"\
        "subl $2,result\n\t");\
        })

int result = 10;

int main(int argc,char ** argv){

    CAL;
    printf("The result is %d\n",result);
    return 0;
}
