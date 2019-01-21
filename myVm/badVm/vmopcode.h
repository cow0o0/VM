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
};
enum opcodes{

    //4
    PushReg32 = 0xe1,
    PushImm32 = 0xe3,
    PushMem32 = 0xe4,
    PopReg32 = 0xe5,

    //4
    MovImm2Reg = 0xa1,
    MovReg2Reg = 0xa2,
    MovMem2Reg = 0xa3,
    MovReg2Mem = 0xa4,

    //6
    AddReg2Reg = 0xa5,
    AddImm2Reg = 0xa6,
    AddMem2Reg = 0xa7,
    AddImm2Mem = 0xa8,
    AddReg2Mem = 0xa9,
    AddMem2Mem = 0xa0,

    //6
    MulReg2Reg = 0xe6,
    MulImm2Reg = 0xe7,
    MulMem2Reg = 0xe8,
    MulImm2Mem = 0xe9,
    MulReg2Mem = 0xea,
    MulMem2Mem = 0xeb,

    //6
    XorReg2Reg = 0xc0,
    XorImm2Reg = 0xc1,
    XorMem2Reg = 0xc2,
    XorImm2Mem = 0xc3,
    XorReg2Mem = 0xc4,
    XorMem2Mem = 0xc5,

    //5
    Jmp = 0xb0,
    Ja = 0xb1,
    Jb = 0xb2,
    Je = 0xb3,
    Jz = 0xb4,
    
    //2
    Sal = 0x99,
    Sar = 0x88,
    
    //1
    CmpReg2Reg = 0x77,

    //2
    Nop = 0x66,
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

    uint8_t *v_eip;//           36

    vm_opcode op_list[OPCODE_N]; //opcode list, store opcode and handle
}vm_cpu;

uint32_t * vm_stack;
uint32_t * vm_MemBase;



//AT&T

//push&pop
void vPushReg32(vm_cpu *cpu);
void vPushImm32(vm_cpu *cpu);
void vPushMem32(vm_cpu *cpu);
void vPopReg32(vm_cpu *cpu);
void vNop(vm_cpu *cpu);

//mov
void vMovImm2Reg(vm_cpu *cpu);
void vMovReg2Reg(vm_cpu *cpu);
void vMovMem2Reg(vm_cpu *cpu);
void vMovReg2Mem(vm_cpu *cpu);

//add
void vAddReg2Reg(vm_cpu *cpu);
void vAddImm2Reg(vm_cpu *cpu);
void vAddMem2Reg(vm_cpu *cpu);
void vAddImm2Mem(vm_cpu *cpu);
void vAddReg2Mem(vm_cpu *cpu);
void vAddMem2Mem(vm_cpu *cpu);

//mul
void vMulReg2Reg(vm_cpu *cpu);
void vMulImm2Reg(vm_cpu *cpu);
void vMulMem2Reg(vm_cpu *cpu);
void vMulImm2Mem(vm_cpu *cpu);
void vMulReg2Mem(vm_cpu *cpu);
void vMulMem2Mem(vm_cpu *cpu);

//xor
void vXorReg2Reg(vm_cpu *cpu);
void vXorImm2Reg(vm_cpu *cpu);
void vXorMem2Reg(vm_cpu *cpu);
void vXorImm2Mem(vm_cpu *cpu);
void vXorReg2Mem(vm_cpu *cpu);
void vXorMem2Mem(vm_cpu *cpu);

//cmp
void vCmpReg2Reg(vm_cpu *cpu);

//jxx
void vJmp(vm_cpu *cpu);
void vJa(vm_cpu *cpu);
void vJb(vm_cpu *cpu);
void vJe(vm_cpu *cpu);
void vJz(vm_cpu *cpu);
//
void vSal(vm_cpu *cpu);
void vSar(vm_cpu *cpu);

#endif