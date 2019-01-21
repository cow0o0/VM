#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<stdint.h>
#include<string.h>
#include<unistd.h>

#define OPCODE_N 2

enum regs{
    EAX = 0xa1,
    EBX = 0xa2,
    ECX = 0xa3,
    EDX = 0xa4,
    ESI = 0xa5,
    EDI = 0xa6,
    EBP = 0xa7,
    ESP = 0xa8,
    EFL = 0xa9,
};

enum opcodes{

    vXor = 0xe1,
    vAdd = 0xe2,

    vRET = 0xff,
};


typedef struct
{
	uint8_t opcode;
	void (*handle)(void *);

}vm_opcode;

typedef struct vm_cpus{
                   //         offset
    uint32_t v_eax;//           0
    uint32_t v_ebx;//           4
    uint32_t v_ecx;//           8
    uint32_t v_edx;//           12

    uint32_t v_esi;//           16
    uint32_t v_edi;//           20

    uint32_t v_ebp;//           24
    uint32_t v_esp;//           28

    uint32_t v_efl;//EFLAGs     32

    uint8_t *v_eip;//           36

    vm_opcode op_list[OPCODE_N]; //opcode list, store opcode and handle
}vm_cpu;

char * vm_stack;

uint8_t vm_code[]={
    
};
// calc instruct
void vXor(vm_cpu *cpu);      //xor edi esi 
void vAdd(vm_cpu *cpu);      //add edi esi


//
void vPushReg32(vm_cpu *cpu);
void vPushImm32(vm_cpu *cpu);


void vXor(vm_cpu *cpu){
    // //0xe1,0xa6,0xa5
    // uint8_t reg0 = (uint8_t)cpu->v_eip+1;//read reg flag
    // uint8_t reg1 = (uint8_t)cpu->v_eip+2;//read reg flag

    // switch(regs){
    //     case 
    // }

}

void vPushReg32(vm_cpu *cpu){
//op reg  vPushReg32 eax
    uint8_t reg_offset = (uint8_t)cpu->v_eip+1;//reg offset
    uint32_t reg = (uint32_t)cpu+reg_offset;
    uint32_t stack_offset = cpu->v_esp;
    *(vm_stack+stack_offset) = reg;
}
void vm_init(vm_cpu *cpu)	
{
    cpu->v_eax = 0;
    cpu->v_ebx = 0;
    cpu->v_ecx = 0;
    cpu->v_edx = 0;

    cpu->v_esi = 0;
    cpu->v_edi = 0;

    cpu->v_ebp = 0;
    cpu->v_esp = 0;
    cpu->v_efl = 0;

    cpu->v_eip = (uint8_t *)vm_code;

    cpu->op_list[0].opcode = 0xe1;
    cpu->op_list[0].handle = (void (*)(void *))vXor;

    cpu->op_list[1].opcode = 0xe2;
    cpu->op_list[1].handle = (void (*)(void *))vAdd;


    vm_stack = malloc(0x512);
    memset(vm_stack,0,0x512);
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
    while((*cpu->v_eip)!= vRET)
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

    read(0,vm_stack,4);
    vm_init(&cpu);
    vm_start(&cpu);

    printf("%d\n",(char)vm_stack[32]);
    exit(0);

    // check();
    return 0;
}
