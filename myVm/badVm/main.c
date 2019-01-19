#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<stdint.h>
#include<string.h>
#include<unistd.h>

#define OPCODE_N 7

enum regs{
    R1 = 0xe1,
    R2 = 0xe2,
    R3 = 0xe3,
};

enum opcodes{

    MOV = 0xf1,
    XOR = 0xf2,
    RET = 0xf4,
    READ = 0xf5,
};


typedef struct
{
	uint8_t opcode;
	void (*handle)(void *);

}vm_opcode;

typedef struct vm_cpus{
    uint32_t r1;
    uint32_t r2;
    uint32_t r3;
    uint8_t *eip;
    vm_opcode op_list[OPCODE_N]; //opcode list, store opcode and handle
}vm_cpu;

char * vm_stack;

uint8_t vm_code[]={
    0xf5,
    0xf1,0xe1,0x00,0x00,0x00,0x00,
    0xf2,
    0xf1,0xe4,0x20,0x00,0x00,0x00,
    0xf1,0xe1,0x01,0x00,0x00,0x00,
    0xf2,
    0xf1,0xe4,0x21,0x00,0x00,0x00,
    0xf1,0xe1,0x02,0x00,0x00,0x00,
    0xf2,
    0xf1,0xe4,0x22,0x00,0x00,0x00,
    0xf1,0xe1,0x03,0x00,0x00,0x00,
    0xf2,
    0xf1,0xe4,0x23,0x00,0x00,0x00,
    0xf4
};
// calc instruct
void xor(vm_cpu *cpu);      //xor flag , 0x1-0x9

void mov(vm_cpu *cpu);      //change flag position

void read_(vm_cpu *cpu);    //call read ,read the flag


void xor(vm_cpu *cpu)
{  
    int temp;
    temp = cpu->r1 ^ cpu->r2;
    temp ^= 0x1;
    cpu->r1 = temp;
    cpu->eip +=1;                //xor指令占一个字节             
}

void read_(vm_cpu *cpu)
{

    char *dest = vm_stack;
    read(0,dest,4);           //用于往虚拟机的栈上读入数据
    cpu->eip += 1;            //read_指令占一个字节  
}

void mov(vm_cpu *cpu)
{
    //mov指令的参数都隐藏在字节码中，指令表示后的一个字节是寄存器标识，第二到第五是要mov的数据在vm_stack上的偏移
    //我这里只是实现了从vm_stack上取数据和存数据到vm_stack上
    uint8_t *res = cpu->eip + 1;  //寄存器标识
    uint32_t *offset = (uint32_t *) (cpu->eip + 2);    //数据在vm_stack上的偏移
    char *dest = 0;
    dest = vm_stack;

   
    switch (*res) {
        case 0xe1:
            cpu->r1 = *(dest + *offset);
            break;    

        case 0xe2:
            cpu->r2 = *(dest + *offset);
            break;    

        case 0xe3:
            cpu->r3 = *(dest + *offset);
            break;    
        case 0xe4:
        {
        	int x = cpu->r1;
            *(dest + *offset) = x;
            break;
            
        }
    }    

    cpu->eip += 6;
    //mov指令占六个字节，所以eip要向后移6位
}    

void vm_init(vm_cpu *cpu)	
{
    cpu->r1 = 0;
    cpu->r2 = 0;
    cpu->r3 = 0;
    cpu->eip = (uint8_t *)vm_code;

    cpu->op_list[0].opcode = 0xf1;
    cpu->op_list[0].handle = (void (*)(void *))mov;

    cpu->op_list[1].opcode = 0xf2;
    cpu->op_list[1].handle = (void (*)(void *))xor;

    cpu->op_list[2].opcode = 0xf5;
    cpu->op_list[2].handle = (void (*)(void *))read_;

    vm_stack = malloc(0x512);
    memset(vm_stack,0,0x512);
}

void vm_dispatcher(vm_cpu *cpu)
{
    uint8_t i;
    for(i=0 ; i < OPCODE_N ; i++) 
    {
        if(*cpu->eip == cpu->op_list[i].opcode)	
        {
            cpu->op_list[i].handle(cpu);//(void (*)(void *))
            break;
        }
    }
    
}

void vm_start(vm_cpu *cpu)
{

    cpu->eip = (uint8_t*)vm_code;
    while((*cpu->eip)!= RET)
    {
        vm_dispatcher(cpu);
    }

}

int main(int argc, char ** argv){

    vm_cpu *cpu={0};
    puts("power by badrer");
    puts("---------------------");
    puts("please input the flag:");

    vm_init(&cpu);
    vm_start(&cpu);

    printf("%d\n",(char)vm_stack[32]);
    exit(0);

    // check();
    return 0;
}
