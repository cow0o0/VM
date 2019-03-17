#include<stdint.h>
#include "vmopcode.h"


void vMovImm2Reg(vm_cpu * cpu){
    //reg1 = imm
    uint32_t * imm = (uint32_t *)(cpu->v_eip+1);
    uint32_t * reg_offset = (uint32_t *)(cpu->v_eip+2);
    uint32_t * reg = (uint32_t *)cpu+(*reg_offset);
    *reg = *imm;
    
    cpu->v_eip +=3;
    ;
}
void vMovMem2Reg(vm_cpu * cpu){
    //reg1 = mem
    uint32_t * mem_reg_base = (uint32_t *)(cpu->v_eip+1);
    uint32_t mem_offset = (cpu->v_rfpo);
    uint32_t * mem_base = (uint32_t*)cpu+(*mem_reg_base);
    uint32_t * mem ;
    uint32_t * reg_offset = (uint32_t *)(cpu->v_eip+2);
    uint32_t * reg = (uint32_t *)cpu+(*reg_offset);
    if(mem_offset > CHUNK_SIZE){
        //-
        uint32_t t = 0-mem_offset;
        mem = (uint32_t *)(*mem_base - 4*t);
    }else{
        //+
        mem = (uint32_t *)(*mem_base + 4*mem_offset);
    }
    *reg = *mem;
    
    cpu->v_eip +=3;
    ;
}
void vMovReg2Reg(vm_cpu * cpu){
    //reg2 = reg1
    uint32_t * reg1_offset = (uint32_t *)(cpu->v_eip+1);
    uint32_t * reg2_offset = (uint32_t *)(cpu->v_eip+2);
    uint32_t * reg1 = (uint32_t *)cpu+(*reg1_offset);
    uint32_t * reg2 = (uint32_t *)cpu+(*reg2_offset);
    *reg2 = *reg1;
    
    cpu->v_eip +=3;
    ;
}
void vMovReg2Mem(vm_cpu * cpu){
    //mem = reg1
    uint32_t * reg_offset = (uint32_t*)(cpu->v_eip+1);
    uint32_t * reg = (uint32_t*)cpu+(*reg_offset);
    uint32_t mem_offset = (cpu->v_rfpo);
    uint32_t * mem_reg_base = (uint32_t*)(cpu->v_eip+2);
    uint32_t * mem_base = (uint32_t*)cpu+(*mem_reg_base);
    uint32_t * mem ;
    if(mem_offset > CHUNK_SIZE){
        //-
        uint32_t t = 0-mem_offset;
        mem = (uint32_t *)(*mem_base - 4*t);
    }else{
        //+
        mem = (uint32_t *)(*mem_base + 4*mem_offset);
    }
    *mem = *reg;

    cpu->v_eip += 3;
    ;
}
void vMovImm2Mem(vm_cpu * cpu){
    //mem = imm
    uint32_t * imm = (uint32_t*)(cpu->v_eip+1);
    uint32_t mem_offset = (cpu->v_rfpo);
    uint32_t * mem_reg_base = (uint32_t*)(cpu->v_eip+2);
    uint32_t * mem_base = (uint32_t*)cpu+(*mem_reg_base);
    uint32_t * mem ;
    if(mem_offset > CHUNK_SIZE){
        //-
        uint32_t t = 0-mem_offset;
        mem = (uint32_t *)(*mem_base - 4*t);
    }else{
        //+
        mem = (uint32_t *)(*mem_base + 4*mem_offset);
    }
    *mem = *imm;

    cpu->v_eip += 3;
    ;
}
void vMovMem2Mem(vm_cpu * cpu){
    //delete
    //pass this ins can't finished
    ;
}

void vAddReg4Imm2Reg(vm_cpu * cpu){
    //reg2 = reg1 + imm
    uint32_t * reg1_offset = (uint32_t*)(cpu->v_eip+1);
    uint32_t * reg1 = (uint32_t*)cpu+(*reg1_offset);
    uint32_t * imm = (uint32_t*)(cpu->v_eip+2);
    uint32_t * reg2_offset = (uint32_t*)(cpu->v_eip+3);
    uint32_t * reg2 = (uint32_t*)cpu+(*reg2_offset);
    *reg2 = *imm + *reg1;
    
    cpu->v_eip += 4;
    ;
}
void vAddReg4Reg2Reg(vm_cpu * cpu){
    //reg3 = reg1 + reg2
    uint32_t * reg1_offset = (uint32_t*)(cpu->v_eip+1);
    uint32_t * reg1 = (uint32_t*)cpu+(*reg1_offset);
    uint32_t * reg2_offset = (uint32_t*)(cpu->v_eip+2);
    uint32_t * reg2 = (uint32_t*)cpu+(*reg2_offset);
    uint32_t * reg3_offset = (uint32_t*)(cpu->v_eip+3);
    uint32_t * reg3 = (uint32_t*)cpu+(*reg3_offset);
    *reg3 = *reg2 + *reg1;

    cpu->v_eip += 4;
    ;
}
void vAddReg4Mem2Reg(vm_cpu * cpu){
    //reg2 = reg1 + mem
    uint32_t * reg1_offset = (uint32_t*)(cpu->v_eip+1);
    uint32_t * reg1 = (uint32_t*)cpu+(*reg1_offset);
    uint32_t mem_offset = (cpu->v_rfpo);
    uint32_t * mem_reg_base = (uint32_t*)(cpu->v_eip+2);
    uint32_t * mem_base = (uint32_t*)cpu+(*mem_reg_base);
    uint32_t * mem ;
    if(mem_offset > CHUNK_SIZE){
        //-
        uint32_t t = 0-mem_offset;
        mem = (uint32_t *)(*mem_base - 4*t);
    }else{
        //+
        mem = (uint32_t *)(*mem_base + 4*mem_offset);
    }
    uint32_t * reg2_offset = (uint32_t*)(cpu->v_eip+3);
    uint32_t * reg2 = (uint32_t*)cpu+(*reg2_offset);
    *reg2 = *reg1 + *mem;

    cpu->v_eip += 4;
    ;
}
void vAddReg4Imm2Mem(vm_cpu * cpu){
    //mem = reg1 + imm
    uint32_t * reg1_offset = (uint32_t*)(cpu->v_eip+1);
    uint32_t * reg1 = (uint32_t*)cpu+(*reg1_offset);
    uint32_t * imm = (uint32_t*)(cpu->v_eip+2);
    uint32_t mem_offset = (cpu->v_rfpo);
    uint32_t * mem_reg_base = (uint32_t*)(cpu->v_eip+3);
    uint32_t * mem_base = (uint32_t*)cpu+(*mem_reg_base);
    uint32_t * mem ;
    if(mem_offset > CHUNK_SIZE){
        //-
        uint32_t t = 0-mem_offset;
        mem = (uint32_t *)(*mem_base - 4*t);
    }else{
        //+
        mem = (uint32_t *)(*mem_base + 4*mem_offset);
    }
    *mem = *imm + *reg1;
    
    cpu->v_eip += 4;
    ;
}
void vAddReg4Reg2Mem(vm_cpu * cpu){
    //mem = reg1 + reg2
    uint32_t * reg1_offset = (uint32_t*)(cpu->v_eip+1);
    uint32_t * reg1 = (uint32_t*)cpu+(*reg1_offset);
    uint32_t * reg2_offset = (uint32_t*)(cpu->v_eip+2);
    uint32_t * reg2 = (uint32_t*)cpu+(*reg2_offset);
    uint32_t mem_offset = (cpu->v_rfpo);
    uint32_t * mem_reg_base = (uint32_t*)(cpu->v_eip+3);
    uint32_t * mem_base = (uint32_t*)cpu+(*mem_reg_base);
    uint32_t * mem ;
    if(mem_offset > CHUNK_SIZE){
        //-
        uint32_t t = 0-mem_offset;
        mem = (uint32_t *)(*mem_base - 4*t);
    }else{
        //+
        mem = (uint32_t *)(*mem_base + 4*mem_offset);
    }
    *mem = *reg1 + *reg2;

    cpu->v_eip += 4;
    ;
}
void vAddReg4Mem2Mem(vm_cpu * cpu){
    //pass 
    ;
}

void vSubReg4Imm2Reg(vm_cpu * cpu){
    //reg2 = reg1 - imm
    uint32_t * reg1_offset = (uint32_t*)(cpu->v_eip+1);
    uint32_t * reg1 = (uint32_t*)cpu+(*reg1_offset);
    uint32_t * imm = (uint32_t*)(cpu->v_eip+2);
    uint32_t * reg2_offset = (uint32_t*)(cpu->v_eip+3);
    uint32_t * reg2 = (uint32_t*)cpu+(*reg2_offset);
    *reg2 = *reg1 - *imm;
    
    cpu->v_eip += 4;
    ;
}
void vSubReg4Reg2Reg(vm_cpu * cpu){
    //reg3 = reg1 - reg2
    uint32_t * reg1_offset = (uint32_t*)(cpu->v_eip+1);
    uint32_t * reg1 = (uint32_t*)cpu+(*reg1_offset);
    uint32_t * reg2_offset = (uint32_t*)(cpu->v_eip+2);
    uint32_t * reg2 = (uint32_t*)cpu+(*reg2_offset);
    uint32_t * reg3_offset = (uint32_t*)(cpu->v_eip+3);
    uint32_t * reg3 = (uint32_t*)cpu+(*reg3_offset);
    *reg3 = *reg1 - *reg2;

    cpu->v_eip += 4;
    ;
}
void vSubReg4Mem2Reg(vm_cpu * cpu){
    //reg2 = reg1 - mem
    uint32_t * reg1_offset = (uint32_t*)(cpu->v_eip+1);
    uint32_t * reg1 = (uint32_t*)cpu+(*reg1_offset);
    uint32_t mem_offset = (cpu->v_rfpo);
    uint32_t * mem_reg_base = (uint32_t*)(cpu->v_eip+2);
    uint32_t * mem_base = (uint32_t*)cpu+(*mem_reg_base);
    uint32_t * mem ;
    if(mem_offset > CHUNK_SIZE){
        //-
        uint32_t t = 0-mem_offset;
        mem = (uint32_t *)(*mem_base - 4*t);
    }else{
        //+
        mem = (uint32_t *)(*mem_base + 4*mem_offset);
    }
    uint32_t * reg2_offset = (uint32_t*)(cpu->v_eip+3);
    uint32_t * reg2 = (uint32_t*)cpu+(*reg2_offset);
    *reg2 = *reg1 - *mem;

    cpu->v_eip += 4;
    ;
}
void vSubReg4Imm2Mem(vm_cpu * cpu){
    //mem = reg1 - imm
    uint32_t * reg1_offset = (uint32_t*)(cpu->v_eip+1);
    uint32_t * reg1 = (uint32_t*)cpu+(*reg1_offset);
    uint32_t * imm = (uint32_t*)(cpu->v_eip+2);
    uint32_t mem_offset = (cpu->v_rfpo);
    uint32_t * mem_reg_base = (uint32_t*)(cpu->v_eip+3);
    uint32_t * mem_base = (uint32_t*)cpu+(*mem_reg_base);
    uint32_t * mem ;
    if(mem_offset > CHUNK_SIZE){
        //-
        uint32_t t = 0-mem_offset;
        mem = (uint32_t *)(*mem_base - 4*t);
    }else{
        //+
        mem = (uint32_t *)(*mem_base + 4*mem_offset);
    }
    *mem = *reg1 - *imm;
    
    cpu->v_eip += 4;
    ;
}
void vSubReg4Reg2Mem(vm_cpu * cpu){
    //mem = reg1 - reg2
    uint32_t * reg1_offset = (uint32_t*)(cpu->v_eip+1);
    uint32_t * reg1 = (uint32_t*)cpu+(*reg1_offset);
    uint32_t * reg2_offset = (uint32_t*)(cpu->v_eip+2);
    uint32_t * reg2 = (uint32_t*)cpu+(*reg2_offset);
    uint32_t mem_offset = (cpu->v_rfpo);
    uint32_t * mem_reg_base = (uint32_t*)(cpu->v_eip+3);
    uint32_t * mem_base = (uint32_t*)cpu+(*mem_reg_base);
    uint32_t * mem ;
    if(mem_offset > CHUNK_SIZE){
        //-
        uint32_t t = 0-mem_offset;
        mem = (uint32_t *)(*mem_base - 4*t);
    }else{
        //+
        mem = (uint32_t *)(*mem_base + 4*mem_offset);
    }
    *mem = *reg1 - *reg2;

    cpu->v_eip += 4;
    ;
}
void vSubReg4Mem2Mem(vm_cpu * cpu){
    //delete
    ;
}

void vMulReg4Imm2Reg(vm_cpu * cpu){
    //reg2 = reg1 * imm
    uint32_t * reg1_offset = (uint32_t*)(cpu->v_eip+1);
    uint32_t * reg1 = (uint32_t*)cpu+(*reg1_offset);
    uint32_t * imm = (uint32_t*)(cpu->v_eip+2);
    uint32_t * reg2_offset = (uint32_t*)(cpu->v_eip+3);
    uint32_t * reg2 = (uint32_t*)cpu+(*reg2_offset);
    *reg2 = *reg1 * *imm;
    
    cpu->v_eip += 4;
    ;
}
void vMulReg4Reg2Reg(vm_cpu * cpu){
    //reg3 = reg1 * reg2
    uint32_t * reg1_offset = (uint32_t*)(cpu->v_eip+1);
    uint32_t * reg1 = (uint32_t*)cpu+(*reg1_offset);
    uint32_t * reg2_offset = (uint32_t*)(cpu->v_eip+2);
    uint32_t * reg2 = (uint32_t*)cpu+(*reg2_offset);
    uint32_t * reg3_offset = (uint32_t*)(cpu->v_eip+3);
    uint32_t * reg3 = (uint32_t*)cpu+(*reg3_offset);
    *reg3 = *reg1 * *reg2;

    cpu->v_eip += 4;
    ;
}
void vMulReg4Mem2Reg(vm_cpu * cpu){
    //reg2 = reg1 * mem
    uint32_t * reg1_offset = (uint32_t*)(cpu->v_eip+1);
    uint32_t * reg1 = (uint32_t*)cpu+(*reg1_offset);
    uint32_t mem_offset = (cpu->v_rfpo);
    uint32_t * mem_reg_base = (uint32_t*)(cpu->v_eip+2);
    uint32_t * mem_base = (uint32_t*)cpu+(*mem_reg_base);
    uint32_t * mem ;
    if(mem_offset > CHUNK_SIZE){
        //-
        uint32_t t = 0-mem_offset;
        mem = (uint32_t *)(*mem_base - 4*t);
    }else{
        //+
        mem = (uint32_t *)(*mem_base + 4*mem_offset);
    }
    uint32_t * reg2_offset = (uint32_t*)(cpu->v_eip+3);
    uint32_t * reg2 = (uint32_t*)cpu+(*reg2_offset);
    *reg2 = *reg1 * *mem;

    cpu->v_eip += 4;
    ;
}
void vMulReg4Imm2Mem(vm_cpu * cpu){
    //mem = reg1 * imm
    uint32_t * reg1_offset = (uint32_t*)(cpu->v_eip+1);
    uint32_t * reg1 = (uint32_t*)cpu+(*reg1_offset);
    uint32_t * imm = (uint32_t*)(cpu->v_eip+2);
    uint32_t mem_offset = (cpu->v_rfpo);
    uint32_t * mem_reg_base = (uint32_t*)(cpu->v_eip+3);
    uint32_t * mem_base = (uint32_t*)cpu+(*mem_reg_base);
    uint32_t * mem ;
    if(mem_offset > CHUNK_SIZE){
        //-
        uint32_t t = 0-mem_offset;
        mem = (uint32_t *)(*mem_base - 4*t);
    }else{
        //+
        mem = (uint32_t *)(*mem_base + 4*mem_offset);
    }
    *mem = *reg1 * *imm;
    
    cpu->v_eip += 4;
    ;
}
void vMulReg4Reg2Mem(vm_cpu * cpu){
    //mem = reg1 * reg2
    uint32_t * reg1_offset = (uint32_t*)(cpu->v_eip+1);
    uint32_t * reg1 = (uint32_t*)cpu+(*reg1_offset);
    uint32_t * reg2_offset = (uint32_t*)(cpu->v_eip+2);
    uint32_t * reg2 = (uint32_t*)cpu+(*reg2_offset);
    uint32_t mem_offset = (cpu->v_rfpo);
    uint32_t * mem_reg_base = (uint32_t*)(cpu->v_eip+3);
    uint32_t * mem_base = (uint32_t*)cpu+(*mem_reg_base);
    uint32_t * mem ;
    if(mem_offset > CHUNK_SIZE){
        //-
        uint32_t t = 0-mem_offset;
        mem = (uint32_t *)(*mem_base - 4*t);
    }else{
        //+
        mem = (uint32_t *)(*mem_base + 4*mem_offset);
    }
    *mem = *reg1 * *reg2;

    cpu->v_eip += 4;
    ;
}
void vMulReg4Mem2Mem(vm_cpu * cpu){
    //delete
    ;
}

void vSraReg4Imm2Reg(vm_cpu * cpu){
    //reg2 = reg1 >> imm
    uint32_t * reg1_offset = (uint32_t*)(cpu->v_eip+1);
    uint32_t * reg1 = (uint32_t*)cpu+(*reg1_offset);
    uint32_t * imm = (uint32_t*)(cpu->v_eip+2);
    uint32_t * reg2_offset = (uint32_t*)(cpu->v_eip+3);
    uint32_t * reg2 = (uint32_t*)cpu+(*reg2_offset);
    *reg2 = *reg1 >> *imm;
    
    cpu->v_eip += 4;
    ;
}
void vSraReg4Reg2Reg(vm_cpu * cpu){
    //reg3 = reg2 >> reg1
    uint32_t * reg1_offset = (uint32_t*)(cpu->v_eip+1);
    uint32_t * reg1 = (uint32_t*)cpu+(*reg1_offset);
    uint32_t * reg2_offset = (uint32_t*)(cpu->v_eip+2);
    uint32_t * reg2 = (uint32_t*)cpu+(*reg2_offset);
    uint32_t * reg3_offset = (uint32_t*)(cpu->v_eip+3);
    uint32_t * reg3 = (uint32_t*)cpu+(*reg3_offset);
    *reg3 = *reg1 >> *reg2;

    cpu->v_eip += 4;
    ;
}
void vSraReg4Mem2Reg(vm_cpu * cpu){
    //reg2 = reg1 >> mem
    uint32_t * reg1_offset = (uint32_t*)(cpu->v_eip+1);
    uint32_t * reg1 = (uint32_t*)cpu+(*reg1_offset);
    uint32_t mem_offset = (cpu->v_rfpo);
    uint32_t * mem_reg_base = (uint32_t*)(cpu->v_eip+2);
    uint32_t * mem_base = (uint32_t*)cpu+(*mem_reg_base);
    uint32_t * mem ;
    if(mem_offset > CHUNK_SIZE){
        //-
        uint32_t t = 0-mem_offset;
        mem = (uint32_t *)(*mem_base - 4*t);
    }else{
        //+
        mem = (uint32_t *)(*mem_base + 4*mem_offset);
    }
    uint32_t * reg2_offset = (uint32_t*)(cpu->v_eip+3);
    uint32_t * reg2 = (uint32_t*)cpu+(*reg2_offset);
    *reg2 = *reg1 >> *mem;

    cpu->v_eip += 4;
    ;
}
void vSraReg4Imm2Mem(vm_cpu * cpu){
    //mem = reg1 >> imm
    uint32_t * reg1_offset = (uint32_t*)(cpu->v_eip+1);
    uint32_t * reg1 = (uint32_t*)cpu+(*reg1_offset);
    uint32_t * imm = (uint32_t*)(cpu->v_eip+2);
    uint32_t mem_offset = (cpu->v_rfpo);
    uint32_t * mem_reg_base = (uint32_t*)(cpu->v_eip+3);
    uint32_t * mem_base = (uint32_t*)cpu+(*mem_reg_base);
    uint32_t * mem ;
    if(mem_offset > CHUNK_SIZE){
        //-
        uint32_t t = 0-mem_offset;
        mem = (uint32_t *)(*mem_base - 4*t);
    }else{
        //+
        mem = (uint32_t *)(*mem_base + 4*mem_offset);
    }
    *mem = *reg1 >> *imm;
    
    cpu->v_eip += 4;
    ;
}
void vSraReg4Reg2Mem(vm_cpu * cpu){
    //mem = reg1 >> reg2
    uint32_t * reg1_offset = (uint32_t*)(cpu->v_eip+1);
    uint32_t * reg1 = (uint32_t*)cpu+(*reg1_offset);
    uint32_t * reg2_offset = (uint32_t*)(cpu->v_eip+2);
    uint32_t * reg2 = (uint32_t*)cpu+(*reg2_offset);
    uint32_t mem_offset = (cpu->v_rfpo);
    uint32_t * mem_reg_base = (uint32_t*)(cpu->v_eip+3);
    uint32_t * mem_base = (uint32_t*)cpu+(*mem_reg_base);
    uint32_t * mem ;
    if(mem_offset > CHUNK_SIZE){
        //-
        uint32_t t = 0-mem_offset;
        mem = (uint32_t *)(*mem_base - 4*t);
    }else{
        //+
        mem = (uint32_t *)(*mem_base + 4*mem_offset);
    }
    *mem = *reg1 >> *reg2;

    cpu->v_eip += 4;
    ;
}
void vSraReg4Mem2Mem(vm_cpu * cpu){
    //delete
    ;
}

void vSllReg4Imm2Reg(vm_cpu * cpu){
    //reg2 = reg1 << imm
        uint32_t * reg1_offset = (uint32_t*)(cpu->v_eip+1);
    uint32_t * reg1 = (uint32_t*)cpu+(*reg1_offset);
    uint32_t * imm = (uint32_t*)(cpu->v_eip+2);
    uint32_t * reg2_offset = (uint32_t*)(cpu->v_eip+3);
    uint32_t * reg2 = (uint32_t*)cpu+(*reg2_offset);
    *reg2 = *reg1 << *imm;
    
    cpu->v_eip += 4;
    ;
}
void vSllReg4Reg2Reg(vm_cpu * cpu){
    //reg3 = reg1 << reg2
    uint32_t * reg1_offset = (uint32_t*)(cpu->v_eip+1);
    uint32_t * reg1 = (uint32_t*)cpu+(*reg1_offset);
    uint32_t * reg2_offset = (uint32_t*)(cpu->v_eip+2);
    uint32_t * reg2 = (uint32_t*)cpu+(*reg2_offset);
    uint32_t * reg3_offset = (uint32_t*)(cpu->v_eip+3);
    uint32_t * reg3 = (uint32_t*)cpu+(*reg3_offset);
    *reg3 = *reg1 << *reg2;

    cpu->v_eip += 4;
    ;
}
void vSllReg4Mem2Reg(vm_cpu * cpu){
    //reg2 = reg1 << mem
    uint32_t * reg1_offset = (uint32_t*)(cpu->v_eip+1);
    uint32_t * reg1 = (uint32_t*)cpu+(*reg1_offset);
    uint32_t mem_offset = (cpu->v_rfpo);
    uint32_t * mem_reg_base = (uint32_t*)(cpu->v_eip+2);
    uint32_t * mem_base = (uint32_t*)cpu+(*mem_reg_base);
    uint32_t * mem ;
    if(mem_offset > CHUNK_SIZE){
        //-
        uint32_t t = 0-mem_offset;
        mem = (uint32_t *)(*mem_base - 4*t);
    }else{
        //+
        mem = (uint32_t *)(*mem_base + 4*mem_offset);
    }
    uint32_t * reg2_offset = (uint32_t*)(cpu->v_eip+3);
    uint32_t * reg2 = (uint32_t*)cpu+(*reg2_offset);
    *reg2 = *reg1 << *mem;

    cpu->v_eip += 4;
    ;
}
void vSllReg4Imm2Mem(vm_cpu * cpu){
    //mem = reg1 << imm
    uint32_t * reg1_offset = (uint32_t*)(cpu->v_eip+1);
    uint32_t * reg1 = (uint32_t*)cpu+(*reg1_offset);
    uint32_t * imm = (uint32_t*)(cpu->v_eip+2);
    uint32_t mem_offset = (cpu->v_rfpo);
    uint32_t * mem_reg_base = (uint32_t*)(cpu->v_eip+3);
    uint32_t * mem_base = (uint32_t*)cpu+(*mem_reg_base);
    uint32_t * mem ;
    if(mem_offset > CHUNK_SIZE){
        //-
        uint32_t t = 0-mem_offset;
        mem = (uint32_t *)(*mem_base - 4*t);
    }else{
        //+
        mem = (uint32_t *)(*mem_base + 4*mem_offset);
    }
    *mem = *reg1 << *imm;
    
    cpu->v_eip += 4;
    ;
}
void vSllReg4Reg2Mem(vm_cpu * cpu){
    //mem = reg1 << reg2
    uint32_t * reg1_offset = (uint32_t*)(cpu->v_eip+1);
    uint32_t * reg1 = (uint32_t*)cpu+(*reg1_offset);
    uint32_t * reg2_offset = (uint32_t*)(cpu->v_eip+2);
    uint32_t * reg2 = (uint32_t*)cpu+(*reg2_offset);
    uint32_t mem_offset = (cpu->v_rfpo);
    uint32_t * mem_reg_base = (uint32_t*)(cpu->v_eip+3);
    uint32_t * mem_base = (uint32_t*)cpu+(*mem_reg_base);
    uint32_t * mem ;
    if(mem_offset > CHUNK_SIZE){
        //-
        uint32_t t = 0-mem_offset;
        mem = (uint32_t *)(*mem_base - 4*t);
    }else{
        //+
        mem = (uint32_t *)(*mem_base + 4*mem_offset);
    }
    *mem = *reg1 << *reg2;

    cpu->v_eip += 4;
    ;
}
void vSllReg4Mem2Mem(vm_cpu * cpu){
    //delete
    ;
}

void vXorReg4Imm2Reg(vm_cpu * cpu){
    //reg2 = reg2 ^ imm
    uint32_t * reg1_offset = (uint32_t*)(cpu->v_eip+1);
    uint32_t * reg1 = (uint32_t*)cpu+(*reg1_offset);
    uint32_t * imm = (uint32_t*)(cpu->v_eip+2);
    uint32_t * reg2_offset = (uint32_t*)(cpu->v_eip+3);
    uint32_t * reg2 = (uint32_t*)cpu+(*reg2_offset);
    *reg2 = *reg1 ^ *imm;
    
    cpu->v_eip += 4;
    ;
}
void vXorReg4Reg2Reg(vm_cpu * cpu){
    //reg3 = reg1 ^ reg2
    uint32_t * reg1_offset = (uint32_t*)(cpu->v_eip+1);
    uint32_t * reg1 = (uint32_t*)cpu+(*reg1_offset);
    uint32_t * reg2_offset = (uint32_t*)(cpu->v_eip+2);
    uint32_t * reg2 = (uint32_t*)cpu+(*reg2_offset);
    uint32_t * reg3_offset = (uint32_t*)(cpu->v_eip+3);
    uint32_t * reg3 = (uint32_t*)cpu+(*reg3_offset);
    *reg3 = *reg1 ^ *reg2;

    cpu->v_eip += 4;
    ;
}
void vXorReg4Mem2Reg(vm_cpu * cpu){
    //reg2 = reg1 ^ mem
    uint32_t * reg1_offset = (uint32_t*)(cpu->v_eip+1);
    uint32_t * reg1 = (uint32_t*)cpu+(*reg1_offset);
    uint32_t mem_offset = (cpu->v_rfpo);
    uint32_t * mem_reg_base = (uint32_t*)(cpu->v_eip+2);
    uint32_t * mem_base = (uint32_t*)cpu+(*mem_reg_base);
    uint32_t * mem ;
    if(mem_offset > CHUNK_SIZE){
        //-
        uint32_t t = 0-mem_offset;
        mem = (uint32_t *)(*mem_base - 4*t);
    }else{
        //+
        mem = (uint32_t *)(*mem_base + 4*mem_offset);
    }
    uint32_t * reg2_offset = (uint32_t*)(cpu->v_eip+3);
    uint32_t * reg2 = (uint32_t*)cpu+(*reg2_offset);
    *reg2 = *reg1 ^ *mem;

    cpu->v_eip += 4;
    ;
}
void vXorReg4Imm2Mem(vm_cpu * cpu){
    //mem = reg1 ^ imm
    uint32_t * reg1_offset = (uint32_t*)(cpu->v_eip+1);
    uint32_t * reg1 = (uint32_t*)cpu+(*reg1_offset);
    uint32_t * imm = (uint32_t*)(cpu->v_eip+2);
    uint32_t mem_offset = (cpu->v_rfpo);
    uint32_t * mem_reg_base = (uint32_t*)(cpu->v_eip+3);
    uint32_t * mem_base = (uint32_t*)cpu+(*mem_reg_base);
    uint32_t * mem ;
    if(mem_offset > CHUNK_SIZE){
        //-
        uint32_t t = 0-mem_offset;
        mem = (uint32_t *)(*mem_base - 4*t);
    }else{
        //+
        mem = (uint32_t *)(*mem_base + 4*mem_offset);
    }
    *mem = *reg1 ^ *imm;
    
    cpu->v_eip += 4;
    ;
}
void vXorReg4Reg2Mem(vm_cpu * cpu){
    //mem = reg1 ^ reg2
    uint32_t * reg1_offset = (uint32_t*)(cpu->v_eip+1);
    uint32_t * reg1 = (uint32_t*)cpu+(*reg1_offset);
    uint32_t * reg2_offset = (uint32_t*)(cpu->v_eip+2);
    uint32_t * reg2 = (uint32_t*)cpu+(*reg2_offset);
    uint32_t mem_offset = (cpu->v_rfpo);
    uint32_t * mem_reg_base = (uint32_t*)(cpu->v_eip+3);
    uint32_t * mem_base = (uint32_t*)cpu+(*mem_reg_base);
    uint32_t * mem ;
    if(mem_offset > CHUNK_SIZE){
        //-
        uint32_t t = 0-mem_offset;
        mem = (uint32_t *)(*mem_base - 4*t);
    }else{
        //+
        mem = (uint32_t *)(*mem_base + 4*mem_offset);
    }
    *mem = *reg1 ^ *reg2;

    cpu->v_eip += 4;
    ;
}
void vXorReg4Mem2Mem(vm_cpu * cpu){
    //delete
    ;
}

void vAndReg4Imm2Reg(vm_cpu * cpu){
    //reg2 = reg1 & imm
    uint32_t * reg1_offset = (uint32_t*)(cpu->v_eip+1);
    uint32_t * reg1 = (uint32_t*)cpu+(*reg1_offset);
    uint32_t * imm = (uint32_t*)(cpu->v_eip+2);
    uint32_t * reg2_offset = (uint32_t*)(cpu->v_eip+3);
    uint32_t * reg2 = (uint32_t*)cpu+(*reg2_offset);
    *reg2 = *reg1 & *imm;
    
    cpu->v_eip += 4;
    ;
}
void vAndReg4Reg2Reg(vm_cpu * cpu){
    //reg3 = reg1 & reg2
    uint32_t * reg1_offset = (uint32_t*)(cpu->v_eip+1);
    uint32_t * reg1 = (uint32_t*)cpu+(*reg1_offset);
    uint32_t * reg2_offset = (uint32_t*)(cpu->v_eip+2);
    uint32_t * reg2 = (uint32_t*)cpu+(*reg2_offset);
    uint32_t * reg3_offset = (uint32_t*)(cpu->v_eip+3);
    uint32_t * reg3 = (uint32_t*)cpu+(*reg3_offset);
    *reg3 = *reg1 & *reg2;

    cpu->v_eip += 4;
    ;
}
void vAndReg4Mem2Reg(vm_cpu * cpu){
    //reg2 = reg1 & mem
    uint32_t * reg1_offset = (uint32_t*)(cpu->v_eip+1);
    uint32_t * reg1 = (uint32_t*)cpu+(*reg1_offset);
    uint32_t mem_offset = (cpu->v_rfpo);
    uint32_t * mem_reg_base = (uint32_t*)(cpu->v_eip+2);
    uint32_t * mem_base = (uint32_t*)cpu+(*mem_reg_base);
    uint32_t * mem ;
    if(mem_offset > CHUNK_SIZE){
        //-
        uint32_t t = 0-mem_offset;
        mem = (uint32_t *)(*mem_base - 4*t);
    }else{
        //+
        mem = (uint32_t *)(*mem_base + 4*mem_offset);
    }
    uint32_t * reg2_offset = (uint32_t*)(cpu->v_eip+3);
    uint32_t * reg2 = (uint32_t*)cpu+(*reg2_offset);
    *reg2 = *reg1 & *mem;

    cpu->v_eip += 4;
    ;
}
void vAndReg4Imm2Mem(vm_cpu * cpu){
    //mem = reg1 & imm
    uint32_t * reg1_offset = (uint32_t*)(cpu->v_eip+1);
    uint32_t * reg1 = (uint32_t*)cpu+(*reg1_offset);
    uint32_t * imm = (uint32_t*)(cpu->v_eip+2);
    uint32_t mem_offset = (cpu->v_rfpo);
    uint32_t * mem_reg_base = (uint32_t*)(cpu->v_eip+3);
    uint32_t * mem_base = (uint32_t*)cpu+(*mem_reg_base);
    uint32_t * mem ;
    if(mem_offset > CHUNK_SIZE){
        //-
        uint32_t t = 0-mem_offset;
        mem = (uint32_t *)(*mem_base - 4*t);
    }else{
        //+
        mem = (uint32_t *)(*mem_base + 4*mem_offset);
    }
    *mem = *reg1 & *imm;
    
    cpu->v_eip += 4;
    ;
}
void vAndReg4Reg2Mem(vm_cpu * cpu){
    //mem = reg1 & reg2
    uint32_t * reg1_offset = (uint32_t*)(cpu->v_eip+1);
    uint32_t * reg1 = (uint32_t*)cpu+(*reg1_offset);
    uint32_t * reg2_offset = (uint32_t*)(cpu->v_eip+2);
    uint32_t * reg2 = (uint32_t*)cpu+(*reg2_offset);
    uint32_t mem_offset = (cpu->v_rfpo);
    uint32_t * mem_reg_base = (uint32_t*)(cpu->v_eip+3);
    uint32_t * mem_base = (uint32_t*)cpu+(*mem_reg_base);
    uint32_t * mem ;
    if(mem_offset > CHUNK_SIZE){
        //-
        uint32_t t = 0-mem_offset;
        mem = (uint32_t *)(*mem_base - 4*t);
    }else{
        //+
        mem = (uint32_t *)(*mem_base + 4*mem_offset);
    }
    *mem = *reg1 & *reg2;

    cpu->v_eip += 4;
    ;
}
void vAndReg4Mem2Mem(vm_cpu * cpu){
    //delete
    ;
}

void vOrReg4Imm2Reg(vm_cpu * cpu){
    //reg2 = reg1 | imm
    uint32_t * reg1_offset = (uint32_t*)(cpu->v_eip+1);
    uint32_t * reg1 = (uint32_t*)cpu+(*reg1_offset);
    uint32_t * imm = (uint32_t*)(cpu->v_eip+2);
    uint32_t * reg2_offset = (uint32_t*)(cpu->v_eip+3);
    uint32_t * reg2 = (uint32_t*)cpu+(*reg2_offset);
    *reg2 = *reg1 | *imm;
    
    cpu->v_eip += 4;
    ;
}
void vOrReg4Reg2Reg(vm_cpu * cpu){
    //reg3 = reg1 | reg2
    uint32_t * reg1_offset = (uint32_t*)(cpu->v_eip+1);
    uint32_t * reg1 = (uint32_t*)cpu+(*reg1_offset);
    uint32_t * reg2_offset = (uint32_t*)(cpu->v_eip+2);
    uint32_t * reg2 = (uint32_t*)cpu+(*reg2_offset);
    uint32_t * reg3_offset = (uint32_t*)(cpu->v_eip+3);
    uint32_t * reg3 = (uint32_t*)cpu+(*reg3_offset);
    *reg3 = *reg1 | *reg2;

    cpu->v_eip += 4;
    ;
}
void vOrReg4Mem2Reg(vm_cpu * cpu){
    //reg2 = reg1 | mem
    uint32_t * reg1_offset = (uint32_t*)(cpu->v_eip+1);
    uint32_t * reg1 = (uint32_t*)cpu+(*reg1_offset);
    uint32_t mem_offset = (cpu->v_rfpo);
    uint32_t * mem_reg_base = (uint32_t*)(cpu->v_eip+2);
    uint32_t * mem_base = (uint32_t*)cpu+(*mem_reg_base);
    uint32_t * mem;
    if(mem_offset > CHUNK_SIZE){
        //-
        uint32_t t = 0-mem_offset;
        mem = (uint32_t *)(*mem_base - 4*t);
    }else{
        //+
        mem = (uint32_t *)(*mem_base + 4*mem_offset);
    }
    uint32_t * reg2_offset = (uint32_t*)(cpu->v_eip+3);
    uint32_t * reg2 = (uint32_t*)cpu+(*reg2_offset);
    *reg2 = *reg1 | *mem;

    cpu->v_eip += 4;
    ;
}
void vOrReg4Imm2Mem(vm_cpu * cpu){
    //mem = reg1 | imm
    uint32_t * reg1_offset = (uint32_t*)(cpu->v_eip+1);
    uint32_t * reg1 = (uint32_t*)cpu+(*reg1_offset);
    uint32_t * imm = (uint32_t*)(cpu->v_eip+2);
    uint32_t mem_offset = (cpu->v_rfpo);
    uint32_t * mem_reg_base = (uint32_t*)(cpu->v_eip+3);
    uint32_t * mem_base = (uint32_t*)cpu+(*mem_reg_base);
    uint32_t * mem ;
    if(mem_offset > CHUNK_SIZE){
        //-
        uint32_t t = 0-mem_offset;
        mem = (uint32_t *)(*mem_base - 4*t);
    }else{
        //+
        mem = (uint32_t *)(*mem_base + 4*mem_offset);
    }
    *mem = *reg1 | *imm;
    
    cpu->v_eip += 4;
    ;
}
void vOrReg4Reg2Mem(vm_cpu * cpu){
    //mem = reg1 | reg2
    uint32_t * reg1_offset = (uint32_t*)(cpu->v_eip+1);
    uint32_t * reg1 = (uint32_t*)cpu+(*reg1_offset);
    uint32_t * reg2_offset = (uint32_t*)(cpu->v_eip+2);
    uint32_t * reg2 = (uint32_t*)cpu+(*reg2_offset);
    uint32_t mem_offset = (cpu->v_rfpo);
    uint32_t * mem_reg_base = (uint32_t*)(cpu->v_eip+3);
    uint32_t * mem_base = (uint32_t*)cpu+(*mem_reg_base);
    uint32_t * mem ;
    if(mem_offset > CHUNK_SIZE){
        //-
        uint32_t t = 0-mem_offset;
        mem = (uint32_t *)(*mem_base - 4*t);
    }else{
        //+
        mem = (uint32_t *)(*mem_base + 4*mem_offset);
    }
    *mem = *reg1 | *reg2;

    cpu->v_eip += 4;
    ;
}
void vOrReg4Mem2Mem(vm_cpu * cpu){
    //delete
    ;
}

void vNorReg4Imm2Reg(vm_cpu * cpu){
    //reg2 = ~(reg1 | imm)
    uint32_t * reg1_offset = (uint32_t*)(cpu->v_eip+1);
    uint32_t * reg1 = (uint32_t*)cpu+(*reg1_offset);
    uint32_t * imm = (uint32_t*)(cpu->v_eip+2);
    uint32_t * reg2_offset = (uint32_t*)(cpu->v_eip+3);
    uint32_t * reg2 = (uint32_t*)cpu+(*reg2_offset);
    *reg2 = ~(*reg1 | *imm);
    
    cpu->v_eip += 4;
    ;
}
void vNorReg4Reg2Reg(vm_cpu * cpu){
    //reg3 = ~(reg1 | reg2)
    uint32_t * reg1_offset = (uint32_t*)(cpu->v_eip+1);
    uint32_t * reg1 = (uint32_t*)cpu+(*reg1_offset);
    uint32_t * reg2_offset = (uint32_t*)(cpu->v_eip+2);
    uint32_t * reg2 = (uint32_t*)cpu+(*reg2_offset);
    uint32_t * reg3_offset = (uint32_t*)(cpu->v_eip+3);
    uint32_t * reg3 = (uint32_t*)cpu+(*reg3_offset);
    *reg3 = ~(*reg1 | *reg2);

    cpu->v_eip += 4;
    ;
}
void vNorReg4Mem2Reg(vm_cpu * cpu){
    //reg2 = ~(reg1 | mem)
    uint32_t * reg1_offset = (uint32_t*)(cpu->v_eip+1);
    uint32_t * reg1 = (uint32_t*)cpu+(*reg1_offset);
    uint32_t mem_offset = (cpu->v_rfpo);
    uint32_t * mem_reg_base = (uint32_t*)(cpu->v_eip+2);
    uint32_t * mem_base = (uint32_t*)cpu+(*mem_reg_base);
    uint32_t * mem ;
    if(mem_offset > CHUNK_SIZE){
        //-
        uint32_t t = 0-mem_offset;
        mem = (uint32_t *)(*mem_base - 4*t);
    }else{
        //+
        mem = (uint32_t *)(*mem_base + 4*mem_offset);
    }
    uint32_t * reg2_offset = (uint32_t*)(cpu->v_eip+3);
    uint32_t * reg2 = (uint32_t*)cpu+(*reg2_offset);
    *reg2 = ~(*reg1 | *mem);

    cpu->v_eip += 4;
    ;
}
void vNorReg4Imm2Mem(vm_cpu * cpu){
    //mem = ~(reg1 | imm)
    uint32_t * reg1_offset = (uint32_t*)(cpu->v_eip+1);
    uint32_t * reg1 = (uint32_t*)cpu+(*reg1_offset);
    uint32_t * imm = (uint32_t*)(cpu->v_eip+2);
    uint32_t mem_offset = (cpu->v_rfpo);
    uint32_t * mem_reg_base = (uint32_t*)(cpu->v_eip+3);
    uint32_t * mem_base = (uint32_t*)cpu+(*mem_reg_base);
    uint32_t * mem ;
    if(mem_offset > CHUNK_SIZE){
        //-
        uint32_t t = 0-mem_offset;
        mem = (uint32_t *)(*mem_base - 4*t);
    }else{
        //+
        mem = (uint32_t *)(*mem_base + 4*mem_offset);
    }
    *mem = ~(*reg1 | *imm);
    
    cpu->v_eip += 4;
    ;
}
void vNorReg4Reg2Mem(vm_cpu * cpu){
    //mem = ~(reg1 | reg2)
    uint32_t * reg1_offset = (uint32_t*)(cpu->v_eip+1);
    uint32_t * reg1 = (uint32_t*)cpu+(*reg1_offset);
    uint32_t * reg2_offset = (uint32_t*)(cpu->v_eip+2);
    uint32_t * reg2 = (uint32_t*)cpu+(*reg2_offset);
    uint32_t mem_offset = (cpu->v_rfpo);
    uint32_t * mem_reg_base = (uint32_t*)(cpu->v_eip+3);
    uint32_t * mem_base = (uint32_t*)cpu+(*mem_reg_base);
    uint32_t * mem ;
    if(mem_offset > CHUNK_SIZE){
        //-
        uint32_t t = 0-mem_offset;
        mem = (uint32_t *)(*mem_base - 4*t);
    }else{
        //+
        mem = (uint32_t *)(*mem_base + 4*mem_offset);
    }
    *mem = ~(*reg1 | *reg2);

    cpu->v_eip += 4;
    ;
}

void vSetLessThanImm(vm_cpu * cpu){
    //SetLessThanImm,reg1,imm,reg2,
    uint32_t * reg1_offset = (uint32_t*)(cpu->v_eip+1);
    uint32_t * reg1 = (uint32_t*)cpu+(*reg1_offset);
    uint32_t * imm = (uint32_t*)(cpu->v_eip+2);
    uint32_t * reg2_offset = (uint32_t*)(cpu->v_eip+3);
    uint32_t * reg2 = (uint32_t*)cpu+(*reg2_offset);
    if(*reg1 < *imm){
        *reg2 = 1;
    }else{
        *reg2 = 0;
    }
    cpu->v_eip += 4;
    ;
}
void vSetLessThanReg(vm_cpu * cpu){
    //SetLessThanReg,reg1,reg2,reg3,
    uint32_t * reg1_offset = (uint32_t*)(cpu->v_eip+1);
    uint32_t * reg1 = (uint32_t*)cpu+(*reg1_offset);
    uint32_t * reg2_offset = (uint32_t*)(cpu->v_eip+2);
    uint32_t * reg2 = (uint32_t*)cpu+(*reg2_offset);
    uint32_t * reg3_offset = (uint32_t*)(cpu->v_eip+3);
    uint32_t * reg3 = (uint32_t*)cpu+(*reg3_offset);
    if(*reg1 < *reg2){
         *reg3 = 1;
    }else{
         *reg3 = 0;
    }
    cpu->v_eip += 4;
    ;
}

void vBranchNotEquelZero(vm_cpu * cpu){
    //BranchNotEquelZero,RAX,Gloable Offset,
    uint32_t * reg1_offset = (uint32_t*)(cpu->v_eip+1);
    uint32_t * reg1 = (uint32_t*)cpu+(*reg1_offset);
    if(*reg1 != 0){
        uint32_t * eip_offset = (uint32_t*)(cpu->v_eip+2);
        cpu->v_eip = (uint32_t*)(cpu->v_rbp + 4**eip_offset);
    }else{
        cpu->v_eip += 3;
    }
    ;
}
void vBranchNotEquelReg(vm_cpu * cpu){
    //vBranchNotEquel,reg1,reg2,Gloable Offset,
    uint32_t * reg1_offset = (uint32_t*)(cpu->v_eip+1);
    uint32_t * reg1 = (uint32_t*)cpu+(*reg1_offset);
    uint32_t * reg2_offset = (uint32_t*)(cpu->v_eip+2);
    uint32_t * reg2 = (uint32_t*)cpu+(*reg2_offset); 
    if(*reg1 != *reg2){
        uint32_t * eip_offset = (uint32_t*)(cpu->v_eip+3);
        cpu->v_eip = (uint32_t*)(cpu->v_rbp + 4**eip_offset);
    }else{
        cpu->v_eip += 4;
    }
    ;
}
void vBranchIfEquelZero(vm_cpu * cpu){
    //BranchIfEquelZero,RAX,Gloable Offset,
    uint32_t * reg1_offset = (uint32_t*)(cpu->v_eip+1);
    uint32_t * reg1 = (uint32_t*)cpu+(*reg1_offset);
    if(*reg1 == 0){
        uint32_t * eip_offset = (uint32_t*)(cpu->v_eip+2);
        cpu->v_eip = (uint32_t*)(cpu->v_rbp + 4**eip_offset);
    }else{
        cpu->v_eip += 3;
    }
    ;
}
void vBranchIfEquelReg(vm_cpu * cpu){
    //vBranchNotEquel,reg1,reg2,Gloable Offset,
    uint32_t * reg1_offset = (uint32_t*)(cpu->v_eip+1);
    uint32_t * reg1 = (uint32_t*)cpu+(*reg1_offset);
    uint32_t * reg2_offset = (uint32_t*)(cpu->v_eip+2);
    uint32_t * reg2 = (uint32_t*)cpu+(*reg2_offset); 
    if(*reg1 == *reg2){
        uint32_t * eip_offset = (uint32_t*)(cpu->v_eip+3);
        cpu->v_eip = (uint32_t*)(cpu->v_rbp + 4**eip_offset);
    }else{
    cpu->v_eip += 4;
    }
    ;
}

void vJmp(vm_cpu * cpu){
    uint32_t * eip_offset = (uint32_t*)(cpu->v_eip+1);
    cpu->v_eip = (uint32_t*)(cpu->v_rbp + 4**eip_offset);
    ;
}
void vNop(vm_cpu * cpu){
    cpu->v_eip += 1;
    ;
}
//append

void vPushImm(vm_cpu * cpu){
    uint32_t * imm = (uint32_t*)(cpu->v_eip+1);
    *vm_stack = *imm;
    vm_stack += 1;

    cpu->v_eip += 2;
    ;
}
void vPushMem(vm_cpu * cpu){
    uint32_t mem_offset = (cpu->v_rfpo);
    uint32_t * mem_reg_base = (uint32_t*)(cpu->v_eip+1);
    uint32_t * mem_base = (uint32_t*)cpu+(*mem_reg_base);
    uint32_t * mem ;
    if(mem_offset > CHUNK_SIZE){
        //-
        uint32_t t = 0-mem_offset;
        mem = (uint32_t *)(*mem_base - 4*t);
    }else{
        //+
        mem = (uint32_t *)(*mem_base + 4*mem_offset);
    }
    *vm_stack = *mem;
    vm_stack += 1;

    cpu->v_eip += 2;
    ;
}
void vPushReg(vm_cpu * cpu){
    uint32_t * reg1_offset = (uint32_t*)(cpu->v_eip+1);
    uint32_t * reg1 = (uint32_t*)cpu+(*reg1_offset);
    *vm_stack = *reg1;
    vm_stack += 1;

    cpu->v_eip += 2;
    ;
}
void vPopImm(vm_cpu * cpu){
    uint32_t * imm = (uint32_t*)(cpu->v_eip+1);
    vm_stack -= 1;
    *imm = *vm_stack;

    cpu->v_eip += 2;
    ;
}
void vPopMem(vm_cpu * cpu){
    uint32_t mem_offset = (cpu->v_rfpo);
    uint32_t * mem_reg_base = (uint32_t*)(cpu->v_eip+1);
    uint32_t * mem_base = (uint32_t*)cpu+(*mem_reg_base);
    uint32_t * mem ;
    if(mem_offset > CHUNK_SIZE){
        //-
        uint32_t t = 0-mem_offset;
        mem = (uint32_t *)(*mem_base - 4*t);
    }else{
        //+
        mem = (uint32_t *)(*mem_base + 4*mem_offset);
    }
    vm_stack -= 1;
    *mem = *vm_stack;

    cpu->v_eip += 2;
    ;
}
void vPopReg(vm_cpu * cpu){
    uint32_t * reg1_offset = (uint32_t*)(cpu->v_eip+1);
    uint32_t * reg1 = (uint32_t*)cpu+(*reg1_offset);
    vm_stack -= 1;
    *reg1 = *vm_stack;

    cpu->v_eip += 2;
    ;
}

void vAtomAdd(vm_cpu * cpu){
    uint32_t data1 = *(vm_stack - 2);//src
    uint32_t data2 = *(vm_stack - 1);//des
    *(vm_stack-1) = data1 + data2;

    cpu->v_eip += 1;
    ;
}
void vAtomSub(vm_cpu * cpu){
    uint32_t data1 = *(vm_stack - 2);//src
    uint32_t data2 = *(vm_stack - 1);//des
    *(vm_stack-1) = data1 - data2;

    cpu->v_eip += 1;
    ;
}
void vAtomAnd(vm_cpu * cpu){
    uint32_t data1 = *(vm_stack - 2);//src
    uint32_t data2 = *(vm_stack - 1);//des
    *(vm_stack-1) = data1 & data2;

    cpu->v_eip += 1;
    ;
}
void vAtomXor(vm_cpu * cpu){
    uint32_t data1 = *(vm_stack - 2);//src
    uint32_t data2 = *(vm_stack - 1);//des
    *(vm_stack-1) = data1 ^ data2;

    cpu->v_eip += 1;
    ;
}
void vAtomOr(vm_cpu * cpu){
    uint32_t data1 = *(vm_stack - 2);//src
    uint32_t data2 = *(vm_stack - 1);//des
    *(vm_stack-1) = data1 | data2;

    cpu->v_eip += 1;
    ;
}
void vAtomNor(vm_cpu * cpu){
    uint32_t data1 = *(vm_stack - 2);//src
    uint32_t data2 = *(vm_stack - 1);//des
    *(vm_stack-1) = ~(data1 | data2);

    cpu->v_eip += 1;
    ;
}
void vAtomMul(vm_cpu * cpu){
    uint32_t data1 = *(vm_stack - 2);//src
    uint32_t data2 = *(vm_stack - 1);//des
    *(vm_stack-1) = data1 * data2;

    cpu->v_eip += 1;
    ;
}
void vAtomSll(vm_cpu * cpu){
    uint32_t data1 = *(vm_stack - 2);//src
    uint32_t data2 = *(vm_stack - 1);//des
    *(vm_stack-1) = data1 << data2;

    cpu->v_eip += 1;
    ;
}
void vAtomSra(vm_cpu * cpu){
    uint32_t data1 = *(vm_stack - 2);//src
    uint32_t data2 = *(vm_stack - 1);//des
    *(vm_stack-1) = data1 >> data2;

    cpu->v_eip += 1;
    ;
}
