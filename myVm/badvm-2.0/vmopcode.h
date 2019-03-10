#ifndef __H__VMOPCODE
#define __H__VMOPCODE

#include<stdint.h>
#define OPCODE_N 82
#define CHUNK_SIZE 0x1000

enum regs {
    RAX  =  0,
    RBX  =  1,
    RCX  =  2,
    RDX  =  3,

    REX  =  4,
    RFX  =  5,
    RGX  =  6,
    RHX  =  7,
    
    EFL  =  8,
    RFP  =  9,
    RFPO =  10,
    ZERO =  11,
    RBP  =  12,

};
enum opcodes{

    MovImm2Reg = 0x01,
    MovMem2Reg = 0x02,
    MovReg2Reg = 0x03,
    MovReg2Mem = 0x04,
    MovImm2Mem = 0x05,
    MovMem2Mem = 0x06,//delete

    AddReg4Imm2Reg = 0x10,
    AddReg4Reg2Reg = 0x11,
    AddReg4Mem2Reg = 0x12,
    AddReg4Imm2Mem = 0x13,
    AddReg4Reg2Mem = 0x14,
    AddReg4Mem2Mem = 0x15,//delete

    SubReg4Imm2Reg = 0x26,
    SubReg4Reg2Reg = 0x27,
    SubReg4Mem2Reg = 0x28,
    SubReg4Imm2Mem = 0x29,
    SubReg4Reg2Mem = 0x2a,
    SubReg4Mem2Mem = 0x2b,//delete

    MulReg4Imm2Reg = 0x30,
    MulReg4Reg2Reg = 0x31,
    MulReg4Mem2Reg = 0x32,
    MulReg4Imm2Mem = 0x33,
    MulReg4Reg2Mem = 0x34,
    MulReg4Mem2Mem = 0x35,//delete

    SraReg4Imm2Reg = 0x46,
    SraReg4Reg2Reg = 0x47,
    SraReg4Mem2Reg = 0x48,
    SraReg4Imm2Mem = 0x49,
    SraReg4Reg2Mem = 0x4a,
    SraReg4Mem2Mem = 0x4b,//delete

    SllReg4Imm2Reg = 0x50,
    SllReg4Reg2Reg = 0x51,
    SllReg4Mem2Reg = 0x52,
    SllReg4Imm2Mem = 0x53,
    SllReg4Reg2Mem = 0x54,
    SllReg4Mem2Mem = 0x55,//delete

    XorReg4Imm2Reg = 0x66,
    XorReg4Reg2Reg = 0x67,
    XorReg4Mem2Reg = 0x68,
    XorReg4Imm2Mem = 0x69,
    XorReg4Reg2Mem = 0x6a,
    XorReg4Mem2Mem = 0x6b,//delete

    AndReg4Imm2Reg = 0x70,
    AndReg4Reg2Reg = 0x71,
    AndReg4Mem2Reg = 0x72,
    AndReg4Imm2Mem = 0x73,
    AndReg4Reg2Mem = 0x74,
    AndReg4Mem2Mem = 0x75,//delete

    OrReg4Imm2Reg  = 0x80,
    OrReg4Reg2Reg  = 0x81,
    OrReg4Mem2Reg  = 0x82,
    OrReg4Imm2Mem  = 0x83,
    OrReg4Reg2Mem  = 0x84,
    OrReg4Mem2Mem  = 0x85,//delete

    NorReg4Imm2Reg = 0xa0,
    NorReg4Reg2Reg = 0xa1,
    NorReg4Mem2Reg = 0xa2,
    NorReg4Imm2Mem = 0xa3,
    NorReg4Reg2Mem = 0xa4,

    SetLessThanImm      = 0x86,
    SetLessThanReg      = 0x87,
    BranchNotEquelZero  = 0x88,
    BranchNotEquelReg   = 0x89,
    BranchIfEquelZero   = 0x8a,
    BranchIfEquelReg    = 0x8b,

    Jmp = 0x90,
    Nop = 0x91,

    PushImm = 0xb0,
    PushMem = 0xb1,
    PushReg = 0xb2,
    PopImm  = 0xb3,
    PopMem  = 0xb4,
    PopReg  = 0xb5,

    AtomAdd = 0xc0,
    AtomSub = 0xc1,
    AtomAnd = 0xc2,
    AtomXor = 0xc3,
    AtomOr  = 0xc4,
    AtomNor = 0xc5,
    AtomMul = 0xc6,
    AtomSll = 0xc7,
    AtomSra = 0xc8,

    Ret = 0xFF,

};

typedef struct
{
	uint32_t opcode;
	void (*handle)(void *);

}vm_opcode;

typedef struct vm_cpus{
                   //         offset
    uint32_t v_rax;//           0   0
    uint32_t v_rbx;//           4   1
    uint32_t v_rcx;//           8   2
    uint32_t v_rdx;//           12  3

    uint32_t v_rex;//           16  4
    uint32_t v_rfx;//           20  5
    uint32_t v_rgx;//           24  6
    uint32_t v_rhx;//           28  7

    uint32_t v_efl;//EFLAGs     32  8

    uint32_t v_rfp;
    uint32_t v_rfpo;
    uint32_t v_zero;

    uint32_t v_rbp;               
    uint32_t *v_eip;//           36

    vm_opcode op_list[OPCODE_N]; //opcode list, store opcode and handle
}vm_cpu;

uint32_t * vm_stack;

uint32_t * vm_FrameBase;
uint32_t * vm_data0;
uint32_t * vm_data1;
uint32_t * vm_data2;
uint32_t * vm_data3;

//append To move data offset to reg  div + or -

//old
void vMovImm2Reg(vm_cpu * cpu);
void vMovMem2Reg(vm_cpu * cpu);
void vMovReg2Reg(vm_cpu * cpu);
void vMovReg2Mem(vm_cpu * cpu);
void vMovImm2Mem(vm_cpu * cpu);
void vMovMem2Mem(vm_cpu * cpu);

void vAddReg4Imm2Reg(vm_cpu * cpu);
void vAddReg4Reg2Reg(vm_cpu * cpu);
void vAddReg4Mem2Reg(vm_cpu * cpu);
void vAddReg4Imm2Mem(vm_cpu * cpu);
void vAddReg4Reg2Mem(vm_cpu * cpu);
void vAddReg4Mem2Mem(vm_cpu * cpu);

void vSubReg4Imm2Reg(vm_cpu * cpu);
void vSubReg4Reg2Reg(vm_cpu * cpu);
void vSubReg4Mem2Reg(vm_cpu * cpu);
void vSubReg4Imm2Mem(vm_cpu * cpu);
void vSubReg4Reg2Mem(vm_cpu * cpu);
void vSubReg4Mem2Mem(vm_cpu * cpu);

void vMulReg4Imm2Reg(vm_cpu * cpu);
void vMulReg4Reg2Reg(vm_cpu * cpu);
void vMulReg4Mem2Reg(vm_cpu * cpu);
void vMulReg4Imm2Mem(vm_cpu * cpu);
void vMulReg4Reg2Mem(vm_cpu * cpu);
void vMulReg4Mem2Mem(vm_cpu * cpu);

void vSraReg4Imm2Reg(vm_cpu * cpu);
void vSraReg4Reg2Reg(vm_cpu * cpu);
void vSraReg4Mem2Reg(vm_cpu * cpu);
void vSraReg4Imm2Mem(vm_cpu * cpu);
void vSraReg4Reg2Mem(vm_cpu * cpu);
void vSraReg4Mem2Mem(vm_cpu * cpu);

void vSllReg4Imm2Reg(vm_cpu * cpu);
void vSllReg4Reg2Reg(vm_cpu * cpu);
void vSllReg4Mem2Reg(vm_cpu * cpu);
void vSllReg4Imm2Mem(vm_cpu * cpu);
void vSllReg4Reg2Mem(vm_cpu * cpu);
void vSllReg4Mem2Mem(vm_cpu * cpu);

void vXorReg4Imm2Reg(vm_cpu * cpu);
void vXorReg4Reg2Reg(vm_cpu * cpu);
void vXorReg4Mem2Reg(vm_cpu * cpu);
void vXorReg4Imm2Mem(vm_cpu * cpu);
void vXorReg4Reg2Mem(vm_cpu * cpu);
void vXorReg4Mem2Mem(vm_cpu * cpu);

void vAndReg4Imm2Reg(vm_cpu * cpu);
void vAndReg4Reg2Reg(vm_cpu * cpu);
void vAndReg4Mem2Reg(vm_cpu * cpu);
void vAndReg4Imm2Mem(vm_cpu * cpu);
void vAndReg4Reg2Mem(vm_cpu * cpu);
void vAndReg4Mem2Mem(vm_cpu * cpu);

void vOrReg4Imm2Reg(vm_cpu * cpu);
void vOrReg4Reg2Reg(vm_cpu * cpu);
void vOrReg4Mem2Reg(vm_cpu * cpu);
void vOrReg4Imm2Mem(vm_cpu * cpu);
void vOrReg4Reg2Mem(vm_cpu * cpu);
void vOrReg4Mem2Mem(vm_cpu * cpu);

void vNorReg4Imm2Reg(vm_cpu * cpu);
void vNorReg4Reg2Reg(vm_cpu * cpu);
void vNorReg4Mem2Reg(vm_cpu * cpu);
void vNorReg4Imm2Mem(vm_cpu * cpu);
void vNorReg4Reg2Mem(vm_cpu * cpu);

void vPushImm(vm_cpu * cpu);
void vPushMem(vm_cpu * cpu);
void vPushReg(vm_cpu * cpu);
void vPopImm(vm_cpu * cpu);
void vPopMem(vm_cpu * cpu);
void vPopReg(vm_cpu * cpu);

//atom operator
void vAtomAdd(vm_cpu * cpu);
void vAtomSub(vm_cpu * cpu);
void vAtomAnd(vm_cpu * cpu);
void vAtomXor(vm_cpu * cpu);
void vAtomOr(vm_cpu * cpu);
void vAtomNor(vm_cpu * cpu);
void vAtomMul(vm_cpu * cpu);
void vAtomSll(vm_cpu * cpu);
void vAtomSra(vm_cpu * cpu);

//set if else
void vSetLessThanImm(vm_cpu * cpu);
void vSetLessThanReg(vm_cpu * cpu);
void vBranchNotEquelZero(vm_cpu * cpu);
void vBranchNotEquelReg(vm_cpu * cpu);
void vBranchIfEquelZero(vm_cpu * cpu);
void vBranchIfEquelReg(vm_cpu * cpu);
void vJmp(vm_cpu * cpu);
void vNop(vm_cpu * cpu);

#endif