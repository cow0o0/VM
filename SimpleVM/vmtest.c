
#include <stdio.h>
#include <time.h>
#include "vm.h"

int hello[] = {
    ICONST, 1234,
    PRINT,
    HALT
};

int loop[] = {
// .GLOBALS 2; N, I
// N = 10                      ADDRESS
        ICONST, 10,            // 0
        GSTORE, 0,             // 2
// I = 0
        ICONST, 0,             // 4
        GSTORE, 1,             // 6
// WHILE I<N:
// START (8):
        GLOAD, 1,              // 8
        GLOAD, 0,              // 10
        ILT,                   // 12
        BRF, 24,               // 13
//     I = I + 1
        GLOAD, 1,              // 15
        ICONST, 1,             // 17
        IADD,                  // 19
        GSTORE, 1,             // 20
        BR, 8,                 // 22
// DONE (24):
// PRINT "LOOPED "+N+" TIMES."
        HALT                   // 24
};

int calc[] = {
//.GLOBALS ;
// N = 10
        ICONST,10,            //0
        GSTORE,0,               //2
// sum = 0
        ICONST,0x0,            //4
        GSTORE,1,               //6
// i = 0
        ICONST,0x0,             //8
        GSTORE,2,               //10
//while i < n
        GLOAD,2,                //14
        GLOAD,0,                //16
        ILT,                    //18
        BRF,37,                   //19

        GLOAD,1,                //21
        GLOAD,2,                //23
        IADD,                   //25
        GSTORE,1,               //26

        GLOAD,2,                //28
        ICONST,1,                //30
        IADD,                   //32
        GSTORE,2,               //33
        BR,14,                   //35

        GLOAD,1,                //37
        PRINT,                  //39

        HALT                    //40

};
int main(int argc, char *argv[])
{
//     vm_exec(hello, sizeof(hello), 0, 0, 1);

    vm_exec(calc, sizeof(calc), 0, 0, 0);

//     t1 = (clock() / (CLOCKS_PER_SEC / 1000));
//     vm_exec(loop, sizeof(loop), 0, 2, 1);
//     t2 = (clock() / (CLOCKS_PER_SEC / 1000));
//     printf("duration = %d ms\n", (t2 - t1));

    return 0;
}

