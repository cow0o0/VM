#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<stdint.h>
#include<string.h>
#include<unistd.h>

#define OPCODE_N 6

// enum regs{
//     EAX = 0xa1,
//     EBX = 0xa2,
//     ECX = 0xa3,
//     EDX = 0xa4,
//     ESI = 0xa5,
//     EDI = 0xa6,
//     EBP = 0xa7,
//     ESP = 0xa8,
//     EFL = 0xa9,
// };

enum opcodes{

    PushReg32 = 0xe1,
    MovImm2Reg = 0xe2,
    PushImm32 = 0xe3,
    PushMem32 = 0xe4,
    PopReg32 = 0xe5,


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
uint8_t vm_code[]={
    0xe2,0x11,0x11,0x11,0x11,0x01,//MovImm2Reg 0x11111111 ebx
    0xe1,0x02,                    //PushReg32    ecx
    0xe3,0x22,0x22,0x22,0x22,   //PushImm32 0x22222222
    0xe5,0x03,                  //PopReg32 edx
    0xe4,0x00,                  //PushMem32 0ffset[0x0]
    0x66,                       //vNop
    0xe5,0x04,                  //PopReg32 esi
    0xff                            //RET
};

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
void vJae(vm_cpu *cpu);
void vJb(vm_cpu *cpu);
void vJbe(vm_cpu *cpu);
void vJe(vm_cpu *cpu);

void vJz(vm_cpu *cpu);
void vJo(vm_cpu *cpu);

//
void vSal(vm_cpu *cpu);
void vSar(vm_cpu *cpu);


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
    *mem += imm;

    cpu->v_eip += 6;
}
void vAddReg2Mem(vm_cpu *cpu){
//vAddReg2Mem reg mem
    uint8_t * reg_offset = (uint8_t*)(cpu->v_eip+1);
    uint32_t * reg = (uint32_t*)cpu+(*reg_offset);
    uint8_t* mem_offset = (uint8_t *)(cpu->v_eip+2);
    uint32_t* mem = (uint32_t *)vm_MemBase+(*mem_offset);
    *mem += * reg;

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
    *mem *= imm;

    cpu->v_eip += 6;
}
void vMulReg2Mem(vm_cpu *cpu){
    //vMulReg2Mem reg mem
    uint8_t * reg_offset = (uint8_t*)(cpu->v_eip+1);
    uint32_t * reg = (uint32_t*)cpu+(*reg_offset);
    uint8_t* mem_offset = (uint8_t *)(cpu->v_eip+2);
    uint32_t* mem = (uint32_t *)vm_MemBase+(*mem_offset);
    *mem *= * reg;

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
    *mem ^= imm;

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
    if(result == 0){
        //set efl zf = 0
        cpu->v_efl = 0x0;
    }
    if()
    
}

//jxx
void vJmp(vm_cpu *cpu);
void vJa(vm_cpu *cpu);
void vJae(vm_cpu *cpu);
void vJb(vm_cpu *cpu);
void vJbe(vm_cpu *cpu);
void vJe(vm_cpu *cpu);

void vJz(vm_cpu *cpu);
void vJo(vm_cpu *cpu);

//
void vSal(vm_cpu *cpu);
void vSar(vm_cpu *cpu);

void vm_init(vm_cpu *cpu)	
{
    cpu->v_eax = 0;
    cpu->v_ebx = 0;
    cpu->v_ecx = 0;
    cpu->v_edx = 0;

    cpu->v_esi = 0;
    cpu->v_edi = 0;

    cpu->v_ebp = 0;
    cpu->v_esp = 0xffffffff;
    cpu->v_efl = 0;

    cpu->v_eip = (uint8_t *)vm_code;

    cpu->op_list[0].opcode = 0xe1;
    cpu->op_list[0].handle = (void (*)(void *))vPushReg32;

    cpu->op_list[1].opcode = 0xe2;
    cpu->op_list[1].handle = (void (*)(void *))vMovImm2Reg;

    cpu->op_list[2].opcode = 0xe3;
    cpu->op_list[2].handle = (void (*)(void *))vPushImm32;

    cpu->op_list[3].opcode = 0xe4;
    cpu->op_list[3].handle = (void (*)(void *))vPushMem32;

    cpu->op_list[4].opcode = 0xe5;
    cpu->op_list[4].handle = (void (*)(void *))vPopReg32;



    cpu->op_list[5].opcode = 0x66;
    cpu->op_list[5].handle = (void (*)(void *))vNop;


    vm_stack = malloc(0x1024);
    memset(vm_stack,0,0x1024);
    //init mem section
    vm_MemBase = (uint32_t*)(vm_stack+4*0x512);
}

void vm_dispatcher(vm_cpu *cpu)
{
    uint8_t i;
    for(i=0 ; i < OPCODE_N ; i++) 
    {
        if(*cpu->v_eip == cpu->op_list[i].opcode)	
        {
            cpu->op_list[i].handle(cpu);//(void (*)(void *))
            break;
        }
    }
    
}

void vm_start(vm_cpu *cpu)
{

    cpu->v_eip = (uint8_t*)vm_code;
    while((*cpu->v_eip)!= RET)
    {
        vm_dispatcher(cpu);
    }

}

int main(int argc, char ** argv){

    vm_cpu *cpu={0};
    puts("power by badrer");
    puts("---------------------");
    puts("please input the flag:");
    setbuf(stdin,0);
    setbuf(stdout,0);
    setbuf(stderr,0);

    vm_init(&cpu);

    read(0,vm_MemBase,4);

    vm_start(&cpu);

    exit(0);

    return 0;
}
