#ifndef __H__VMOPCODE
#define __H__VMOPCODE

#include<stdint.h>
#define OPCODE_N 35

enum regs {

    EAX = 0,
    EBX = 1,
    ECX = 2,
    EDX = 3,

    ESI = 4,
    EDI = 5,

    EBP = 6,
    ESP = 7,
    EFL = 8,

    ED0 = 9,
    ED1 = 10,
    ED2 = 11,
    ED3 = 12,

};
enum opcodes{

    Push32 = 0xe1,
    Pop32  = 0xe5,

    MovReg2Mem = 0xa4,

    AddMem2Mem = 0xa0,

    MulMem2Mem = 0xeb,

    XorMem2Mem = 0xc5,

    Jmp = 0xb0,
    Sal = 0x99,
    Sar = 0x88,
    
    NOP = 0xfe,
    RET = 0xff,
};

typedef struct
{
	uint8_t opcode;
	void (*handle)(void *);

}vm_opcode;

typedef struct vm_cpus{
                   //         offset
    uint32_t v_eax;//           0   0
    uint32_t v_ebx;//           4   1
    uint32_t v_ecx;//           8   2
    uint32_t v_edx;//           12  3

    uint32_t v_esi;//           16  4
    uint32_t v_edi;//           20  5

    uint32_t v_ebp;//           24  6
    uint32_t v_esp;//           28  7

    uint32_t v_efl;//EFLAGs     32  8

    uint32_t *v_eip;//           36

    vm_opcode op_list[OPCODE_N]; //opcode list, store opcode and handle
}vm_cpu;

uint32_t * vm_stack;

uint32_t * vm_data0;
uint32_t * vm_data1;
uint32_t * vm_data2;
uint32_t * vm_data3;


#endif