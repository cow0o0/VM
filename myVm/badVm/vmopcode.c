#include<stdint.h>
#include "vmopcode.h"

void vPushReg32(vm_cpu *cpu){
//vPushReg32 reg
    uint8_t* reg_offset = (uint8_t *)(cpu->v_eip+1);//reg offset
    uint32_t* reg = (uint32_t *)cpu+(*reg_offset);
    uint32_t stack_offset = cpu->v_esp+1;
    *(vm_stack+stack_offset) = *reg;

    cpu->v_esp += 1;
    cpu->v_eip += 2;
}
void vPushImm32(vm_cpu *cpu){
    //vPushImm32 0x11111111
    uint32_t* imm = (uint32_t*)(cpu->v_eip+1);
    uint32_t stack_offset = cpu->v_esp+1;
    *(vm_stack+stack_offset) = *imm;
    
    cpu->v_esp += 1;
    cpu->v_eip += 5;
}
void vPushMem32(vm_cpu *cpu){
    //vPushMem32 mem+offset
    uint8_t* mem_offset = (uint8_t *)(cpu->v_eip+1);//reg offset
    uint32_t* mem = (uint32_t *)vm_MemBase+(*mem_offset);
    uint32_t stack_offset = cpu->v_esp+1;
    *(vm_stack+stack_offset) = *mem;

    cpu->v_esp += 1;
    cpu->v_eip += 2;
}
void vPopReg32(vm_cpu *cpu){
    //vPopReg32 reg
    uint8_t* reg_offset = (uint8_t *)(cpu->v_eip+1);//reg offset
    uint32_t* reg = (uint32_t *)cpu+(*reg_offset);
    uint32_t stack_offset = cpu->v_esp;
    uint32_t* top_stack = (vm_stack+stack_offset);
    *reg = *top_stack;
    
    cpu->v_esp -= 1;
    cpu->v_eip += 2;
}
void vNop(vm_cpu *cpu){
    //vNop
    cpu->v_eip += 1;
}

void vMovImm2Reg(vm_cpu *cpu){
    //vMovImm2Reg  Imm reg
    uint32_t* imm = (uint32_t*)(cpu->v_eip+1);

    uint8_t* reg_offset = (uint8_t*)(cpu->v_eip+5);
    uint32_t * reg = (uint32_t*)cpu+(*reg_offset);
    *reg = *imm;
    
    cpu->v_eip +=6;
}

void vMovReg2Reg(vm_cpu *cpu){
//vMovReg2Reg reg1 reg2
    uint8_t * reg1_offset = (uint8_t*)(cpu->v_eip+1);
    uint8_t * reg2_offset = (uint8_t*)(cpu->v_eip+2);
    uint32_t * reg1 = (uint32_t*)cpu+(*reg1_offset);
    uint32_t * reg2 = (uint32_t*)cpu+(*reg2_offset);
    *reg2 = *reg1;

    cpu->v_eip += 3;
}

void vMovMem2Reg(vm_cpu *cpu){
    //vMovMem2Reg mem reg
    uint8_t* mem_offset = (uint8_t *)(cpu->v_eip+1);
    uint32_t* mem = (uint32_t *)vm_MemBase+(*mem_offset);
    uint8_t * reg_offset = (uint8_t*)(cpu->v_eip+2);
    uint32_t * reg = (uint32_t*)cpu+(*reg_offset);
    *reg = *mem;

    cpu->v_eip += 3;
}
void vMovReg2Mem(vm_cpu *cpu){
//vMovReg2Mem reg mem
    uint8_t * reg_offset = (uint8_t*)(cpu->v_eip+1);
    uint32_t * reg = (uint32_t*)cpu+(*reg_offset);
    uint8_t* mem_offset = (uint8_t *)(cpu->v_eip+2);
    uint32_t* mem = (uint32_t *)vm_MemBase+(*mem_offset);
    *mem = *reg;

    cpu->v_eip += 3;
}

void vAddReg2Reg(vm_cpu *cpu){
    //vAddReg2Reg reg1 reg2
    uint8_t * reg1_offset = (uint8_t*)(cpu->v_eip+1);
    uint8_t * reg2_offset = (uint8_t*)(cpu->v_eip+2);
    uint32_t * reg1 = (uint32_t*)cpu+(*reg1_offset);
    uint32_t * reg2 = (uint32_t*)cpu+(*reg2_offset);
    *reg2 += *reg1;

    cpu->v_eip += 3;
}
void vAddImm2Reg(vm_cpu *cpu){
    //vAddImm2Reg imm reg
    uint32_t* imm = (uint32_t*)(cpu->v_eip+1);
    uint8_t* reg_offset = (uint8_t*)(cpu->v_eip+5);
    uint32_t * reg = (uint32_t*)cpu+(*reg_offset);
    *reg += *imm;
    
    cpu->v_eip += 6;
}
void vAddMem2Reg(vm_cpu *cpu){
    //vAddMem2Reg mem reg
    uint8_t* mem_offset = (uint8_t *)(cpu->v_eip+1);
    uint32_t* mem = (uint32_t *)vm_MemBase+(*mem_offset);
    uint8_t * reg_offset = (uint8_t*)(cpu->v_eip+2);
    uint32_t * reg = (uint32_t*)cpu+(*reg_offset);
    *reg += *mem;

    cpu->v_eip += 3;
}
void vAddImm2Mem(vm_cpu *cpu){
    //vAddImm2Mem imm mem
    uint32_t* imm = (uint32_t*)(cpu->v_eip+1);
    uint8_t* mem_offset = (uint8_t *)(cpu->v_eip+5);
    uint32_t* mem = (uint32_t *)vm_MemBase+(*mem_offset);
    *mem += *imm;

    cpu->v_eip += 6;
}
void vAddReg2Mem(vm_cpu *cpu){
//vAddReg2Mem reg mem
    uint8_t * reg_offset = (uint8_t*)(cpu->v_eip+1);
    uint32_t * reg = (uint32_t*)cpu+(*reg_offset);
    uint8_t* mem_offset = (uint8_t *)(cpu->v_eip+2);
    uint32_t* mem = (uint32_t *)vm_MemBase+(*mem_offset);
    *mem += *reg;

    cpu->v_eip += 3;
}
void vAddMem2Mem(vm_cpu *cpu){
    //vAddMem2Mem mem1 mem2
    uint8_t* mem1_offset = (uint8_t *)(cpu->v_eip+1);
    uint32_t* mem1 = (uint32_t *)vm_MemBase+(*mem1_offset);
    uint8_t* mem2_offset = (uint8_t *)(cpu->v_eip+2);
    uint32_t* mem2 = (uint32_t *)vm_MemBase+(*mem2_offset);
    *mem2 += *mem1;

    cpu->v_eip += 3;
}
//mul
void vMulReg2Reg(vm_cpu *cpu){
//vMulReg2Reg reg reg
    uint8_t * reg1_offset = (uint8_t*)(cpu->v_eip+1);
    uint8_t * reg2_offset = (uint8_t*)(cpu->v_eip+2);
    uint32_t * reg1 = (uint32_t*)cpu+(*reg1_offset);
    uint32_t * reg2 = (uint32_t*)cpu+(*reg2_offset);
    *reg2 *= *reg1;

    cpu->v_eip += 3;
}
void vMulImm2Reg(vm_cpu *cpu){
    //vMulImm2Reg imm reg
    uint32_t* imm = (uint32_t*)(cpu->v_eip+1);
    uint8_t* reg_offset = (uint8_t*)(cpu->v_eip+5);
    uint32_t * reg = (uint32_t*)cpu+(*reg_offset);
    *reg *= *imm;
    
    cpu->v_eip += 6;
}
void vMulMem2Reg(vm_cpu *cpu){
    //vMulMem2Reg mem reg
    uint8_t* mem_offset = (uint8_t *)(cpu->v_eip+1);
    uint32_t* mem = (uint32_t *)vm_MemBase+(*mem_offset);
    uint8_t * reg_offset = (uint8_t*)(cpu->v_eip+2);
    uint32_t * reg = (uint32_t*)cpu+(*reg_offset);
    *reg *= *mem;

    cpu->v_eip += 3;
}
void vMulImm2Mem(vm_cpu *cpu){
    //vMulImm2Mem imm mem
    uint32_t* imm = (uint32_t*)(cpu->v_eip+1);
    uint8_t* mem_offset = (uint8_t *)(cpu->v_eip+5);
    uint32_t* mem = (uint32_t *)vm_MemBase+(*mem_offset);
    *mem *= *imm;

    cpu->v_eip += 6;
}
void vMulReg2Mem(vm_cpu *cpu){
    //vMulReg2Mem reg mem
    uint8_t * reg_offset = (uint8_t*)(cpu->v_eip+1);
    uint32_t * reg = (uint32_t*)cpu+(*reg_offset);
    uint8_t* mem_offset = (uint8_t *)(cpu->v_eip+2);
    uint32_t* mem = (uint32_t *)vm_MemBase+(*mem_offset);
    *mem *= *reg;

    cpu->v_eip += 3;
}
void vMulMem2Mem(vm_cpu *cpu){
    //vMulMem2Mem mem mem
    uint8_t* mem1_offset = (uint8_t *)(cpu->v_eip+1);
    uint32_t* mem1 = (uint32_t *)vm_MemBase+(*mem1_offset);
    uint8_t* mem2_offset = (uint8_t *)(cpu->v_eip+2);
    uint32_t* mem2 = (uint32_t *)vm_MemBase+(*mem2_offset);
    *mem2 *= *mem1;

    cpu->v_eip += 3;
}

//xor
void vXorReg2Reg(vm_cpu *cpu){
    //vXorReg2Reg reg reg
    uint8_t * reg1_offset = (uint8_t*)(cpu->v_eip+1);
    uint8_t * reg2_offset = (uint8_t*)(cpu->v_eip+2);
    uint32_t * reg1 = (uint32_t*)cpu+(*reg1_offset);
    uint32_t * reg2 = (uint32_t*)cpu+(*reg2_offset);
    *reg2 ^= *reg1;

    cpu->v_eip += 3;
}
void vXorImm2Reg(vm_cpu *cpu){
    //vXorImm2Reg imm reg
    uint32_t* imm = (uint32_t*)(cpu->v_eip+1);
    uint8_t* reg_offset = (uint8_t*)(cpu->v_eip+5);
    uint32_t * reg = (uint32_t*)cpu+(*reg_offset);
    *reg ^= *imm;
    
    cpu->v_eip += 6;
}
void vXorMem2Reg(vm_cpu *cpu){
    //vXorMem2Reg mem reg
    uint8_t* mem_offset = (uint8_t *)(cpu->v_eip+1);
    uint32_t* mem = (uint32_t *)vm_MemBase+(*mem_offset);
    uint8_t * reg_offset = (uint8_t*)(cpu->v_eip+2);
    uint32_t * reg = (uint32_t*)cpu+(*reg_offset);
    *reg ^= *mem;

    cpu->v_eip += 3;
}
void vXorImm2Mem(vm_cpu *cpu){
    //vXorImm2Mem imm mem
    uint32_t* imm = (uint32_t*)(cpu->v_eip+1);
    uint8_t* mem_offset = (uint8_t *)(cpu->v_eip+5);
    uint32_t* mem = (uint32_t *)vm_MemBase+(*mem_offset);
    *mem ^= *imm;

    cpu->v_eip += 6;
}
void vXorReg2Mem(vm_cpu *cpu){
    //vXorReg2Mem reg mem
    uint8_t * reg_offset = (uint8_t*)(cpu->v_eip+1);
    uint32_t * reg = (uint32_t*)cpu+(*reg_offset);
    uint8_t* mem_offset = (uint8_t *)(cpu->v_eip+2);
    uint32_t* mem = (uint32_t *)vm_MemBase+(*mem_offset);
    *mem ^= * reg;

    cpu->v_eip += 3;
}
void vXorMem2Mem(vm_cpu *cpu){
    //vXorMem2Mem mem mem
    uint8_t* mem1_offset = (uint8_t *)(cpu->v_eip+1);
    uint32_t* mem1 = (uint32_t *)vm_MemBase+(*mem1_offset);
    uint8_t* mem2_offset = (uint8_t *)(cpu->v_eip+2);
    uint32_t* mem2 = (uint32_t *)vm_MemBase+(*mem2_offset);
    *mem2 ^= *mem1;

    cpu->v_eip += 3;
}
//cmp
void vCmpReg2Reg(vm_cpu *cpu){
    //vCmpReg2Reg reg1 reg2
    uint8_t * reg1_offset = (uint8_t*)(cpu->v_eip+1);
    uint8_t * reg2_offset = (uint8_t*)(cpu->v_eip+2);
    uint32_t * reg1 = (uint32_t*)cpu+(*reg1_offset);
    uint32_t * reg2 = (uint32_t*)cpu+(*reg2_offset);
    uint32_t result = *reg1 - *reg2;  // 2-3 = -1 = 0xffffffff
    //set efl
    if(result == 0){
        //set efl zf = 1
        cpu->v_efl = 0x40;//64
    }
    if(*reg1 > *reg2){
        //set cf = 1 & zf =1
        cpu->v_efl = 0x41;

    }
    if(*reg1 < *reg2){
        //set cf = 1 & zf = 0
        cpu->v_efl = 0x1;
    }

    cpu->v_eip += 3;
    
}

//jxx
void vJmp(vm_cpu *cpu){
    //vJmp from start offset
    uint8_t *offset = (uint8_t*)(cpu->v_eip+1);
    cpu->v_eip = (uint8_t*)(cpu->v_ebp + *offset);
}
void vJa(vm_cpu *cpu){
//vJa offset
    if(((uint8_t)(cpu->v_efl & 0x40) + ((uint8_t)(cpu->v_efl & 0x1))) == 0x41){
        vJmp(cpu);
    }else cpu->v_eip += 2;
    
}
void vJb(vm_cpu *cpu){
//vJb offset
    if(((uint8_t)(cpu->v_efl & 0x1) == 0x01) && ((uint8_t)(cpu->v_efl & 0x40) == 0x0)){
        vJmp(cpu);
    }else cpu->v_eip += 2;
}
void vJe(vm_cpu *cpu){
    //vJe offset
    if(((uint8_t)(cpu->v_efl & 0x1) == 0x0) && ((uint8_t)(cpu->v_efl & 0x40) == 0x0)){
        vJmp(cpu);
    }else cpu->v_eip += 2;
}

void vJz(vm_cpu *cpu){
    //vJz offset
    if(((uint8_t)(cpu->v_efl & 0x1) == 0x0) && ((uint8_t)(cpu->v_efl & 0x40) == 0x0)){
        vJmp(cpu);
    }else cpu->v_eip += 2;
}

//
void vSal(vm_cpu *cpu){
    //vSal bit  always eax
    uint8_t * bit = (uint8_t*)(cpu->v_eip+1);//  <= 32  256 ...error handler
    cpu->v_eax <<= *bit;

    cpu->v_eip += 2;
}
void vSar(vm_cpu *cpu){
    //vSar bit  always eax
    uint8_t * bit = (uint8_t*)(cpu->v_eip+1);//  <= 32  256 ...error handler
    cpu->v_eax >>= *bit;

    cpu->v_eip += 2;
}