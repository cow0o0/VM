#include<unistd.h>
#include<signal.h>
#include<termios.h>
#include<stdbool.h>

#include"vmhandler.h"
#include"vmopcode.h"

uint32_t vm_codeTest[]={
    //MovImm2Reg,0x19,RFPO,
    PushImm,0x19,
    PopReg,RFPO,
    //MovReg2Mem,ZERO,RFP,
    PushReg,ZERO,
    PopMem,RFP,
    //MovImm2Reg,0x1a,RFPO,
    PushImm,0x1a,
    PopReg,RFPO,
    //MovReg2Mem,ZERO,RFP,
    PushReg,ZERO,
    PopMem,RFP,
    //MovImm2Reg,0x1a,RFPO,
    PushImm,0x1a,
    PopReg,RFPO,
    //MovReg2Mem,ZERO,RFP,
    PushReg,ZERO,
    PopMem,RFP,
    Jmp,176,
    Nop,
    //branch here 21
    //MovImm2Reg,0x1a,RFPO,
    PushImm,0x1a,
    PopReg,RFPO,

    //MovMem2Reg,RFP,RAX,
    PushMem,RFP,// have problem
    PopReg,RAX,

    //AddReg4Imm2Reg,RFP,0xc0,RBX,//0x30*4
    PushReg,RFP,
    PushImm,0xc0,
    AtomAdd,
    PopReg,RBX,

    //MulReg4Imm2Reg,RAX,0x04,RAX,
    PushReg,RAX,
    PushImm,0x04,
    AtomMul,
    PopReg,RAX,

    //AddReg4Reg2Reg,RBX,RAX,RAX,
    PushReg,RBX,
    PushReg,RAX,
    AtomAdd,
    PopReg,RAX,

    //MovImm2Reg,-0xc,RFPO,//-0xc
    PushImm,-0xc,
    PopReg,RFPO,
    //MovMem2Reg,RAX,RBX,
    PushMem,RAX,
    PopReg,RBX,
    //MovImm2Reg,0x1a,RFPO,
    PushImm,0x1a,
    PopReg,RFPO,
    //MovMem2Reg,RFP,RAX,
    PushMem,RFP,
    PopReg,RAX,
    //AddReg4Imm2Reg,RAX,0x31,RAX,
    PushReg,RAX,
    PushImm,0x31,
    AtomAdd,
    PopReg,RAX,

    //AndReg4Imm2Reg,RAX,0xff,RAX,
    PushReg,RAX,
    PushImm,0xff,
    AtomAnd,
    PopReg,RAX,

    //SllReg4Imm2Reg,RAX,0x18,RAX,
    PushReg,RAX,
    PushImm,0x18,
    AtomSll,
    PopReg,RAX,

    //SraReg4Imm2Reg,RAX,0x18,RAX,
    PushReg,RAX,
    PushImm,0x18,
    AtomSra,
    PopReg,RAX,

    //XorReg4Reg2Reg,RBX,RAX,RAX,
    PushReg,RBX,
    PushReg,RAX,
    AtomXor,
    PopReg,RAX,

////
    //SllReg4Imm2Reg,RAX,0x18,RAX,
    PushReg,RAX,
    PushImm,0x18,
    AtomSll,
    PopReg,RAX,

    //SraReg4Imm2Reg,RAX,0x18,RAX,
    PushReg,RAX,
    PushImm,0x18,
    AtomSra,
    PopReg,RAX,

    //AndReg4Imm2Reg,RAX,0xff,RBX,
    PushReg,RAX,
    PushImm,0xff,
    AtomAnd,
    PopReg,RBX,

    //MovImm2Reg,0x19,RFPO,
    PushImm,0x19,
    PopReg,RFPO,
    //MovMem2Reg,RFP,RAX,
    PushMem,RFP,
    PopReg,RAX,
    //AddReg4Reg2Reg,RBX,RAX,RAX,
    PushReg,RBX,
    PushReg,RAX,
    AtomAdd,
    PopReg,RAX,

    //MovImm2Reg,0x19,RFPO,
    PushImm,0x19,
    PopReg,RFPO,
    //MovReg2Mem,RAX,RFP,
    PushReg,RAX,
    PopMem,RFP,
    //MovImm2Reg,0x1a,RFPO,
    PushImm,0x1a,
    PopReg,RFPO,
    //MovMem2Reg,RFP,RAX,
    PushMem,RFP,
    PopReg,RAX,
    //AddReg4Imm2Reg,RAX,0x01,RAX,
    PushReg,RAX,
    PushImm,0x01,
    AtomAdd,
    PopReg,RAX,

    //MovImm2Reg,0x1a,RFPO,
    PushImm,0x1a,
    PopReg,RFPO,
    //MovReg2Mem,RAX,RFP,
    PushReg,RAX,
    PopMem,RFP,
    //jmp here
    //MovImm2Reg,0x1a,RFPO,
    PushImm,0x1a,
    PopReg,RFPO,
    //MovMem2Reg,RFP,RAX,
    PushMem,RFP,
    PopReg,RAX,
    SetLessThanImm,RAX,0x06,RAX,
    BranchNotEquelZero,RAX,27,
    Nop,                           
    Ret,//RET
    
};

uint32_t vm_code[]={
    MovImm2Reg,0x19,RFPO,
    MovReg2Mem,ZERO,RFP,
    MovImm2Reg,0x1a,RFPO,
    MovReg2Mem,ZERO,RFP,
    MovImm2Reg,0x1a,RFPO,
    MovReg2Mem,ZERO,RFP,
    Jmp,115,
    Nop,
    //branch here 21
    MovImm2Reg,0x1a,RFPO,
    MovMem2Reg,RFP,RAX,

    AddReg4Imm2Reg,RFP,0xc0,RBX,//0x30*4


    MulReg4Imm2Reg,RAX,0x04,RAX,
    AddReg4Reg2Reg,RBX,RAX,RAX,

    MovImm2Reg,-0xc,RFPO,//-0xc
    MovMem2Reg,RAX,RBX,
    MovImm2Reg,0x1a,RFPO,
    MovMem2Reg,RFP,RAX,
    AddReg4Imm2Reg,RAX,0x31,RAX,
    AndReg4Imm2Reg,RAX,0xff,RAX,
    SllReg4Imm2Reg,RAX,0x18,RAX,
    SraReg4Imm2Reg,RAX,0x18,RAX,
    XorReg4Reg2Reg,RBX,RAX,RAX,
    SllReg4Imm2Reg,RAX,0x18,RAX,
    SraReg4Imm2Reg,RAX,0x18,RAX,
    
    AndReg4Imm2Reg,RAX,0xff,RBX,
    MovImm2Reg,0x19,RFPO,
    MovMem2Reg,RFP,RAX,
    AddReg4Reg2Reg,RBX,RAX,RAX,

    MovImm2Reg,0x19,RFPO,
    MovReg2Mem,RAX,RFP,
    MovImm2Reg,0x1a,RFPO,
    MovMem2Reg,RFP,RAX,
    AddReg4Imm2Reg,RAX,0x01,RAX,
    MovImm2Reg,0x1a,RFPO,
    MovReg2Mem,RAX,RFP,
    //jmp here
    MovImm2Reg,0x1a,RFPO,
    MovMem2Reg,RFP,RAX,
    SetLessThanImm,RAX,0x06,RAX,
    BranchNotEquelZero,RAX,21,
    Nop,                           
    Ret,//RET
};

void setBufferedInput(bool enable){
    static bool enabled = true;
    static struct termios old;
    struct termios new;

    if(enable && !enabled){
        //restore the terminal
        tcsetattr(STDIN_FILENO,TCSANOW,&old);
        enabled = true;
    }else if(!enable && enabled){
        //get terminal attr
        if(tcgetattr(STDIN_FILENO,&new)==-1){
            printf("tcgetattr Error!\n");
            exit(-1);
        }
        //resotre now terminal attr
        old = new;
        //set c_cflag don't show cursor(光标)  attaction to order
        new.c_lflag &=(~ICANON & ~ECHO);
        tcsetattr(STDIN_FILENO,TCSANOW,&new);
        enabled = false;
    }
}

void vm_over(vm_cpu *cpu){
    // free(vm_stack);
    free(vm_FrameBase);
    free(vm_data0);
    free(vm_data1);
    free(vm_data2);
    free(vm_data3);
}

void vm_init(vm_cpu *cpu)	
{
    cpu->v_rax = 0;
    cpu->v_rbx = 0;
    cpu->v_rcx = 0;
    cpu->v_rdx = 0;
    cpu->v_rex = 0;
    cpu->v_rfx = 0;
    cpu->v_rgx = 0;
    cpu->v_rhx = 0;
    cpu->v_efl = 0;
    cpu->v_rfp = 0;
    cpu->v_rfpo = 0;
    cpu->v_zero = 0;
    cpu->v_rbp = (uint32_t *)vm_codeTest;
    cpu->v_eip = (uint32_t *)vm_codeTest;

    vm_stack = (uint32_t *)malloc(CHUNK_SIZE);
    vm_FrameBase = (uint32_t *)malloc(CHUNK_SIZE);
    vm_data0 = (uint32_t *)malloc(CHUNK_SIZE);
    vm_data1 = (uint32_t *)malloc(CHUNK_SIZE);
    vm_data2 = (uint32_t *)malloc(CHUNK_SIZE);
    vm_data3 = (uint32_t *)malloc(CHUNK_SIZE);

    memset(vm_stack,0,CHUNK_SIZE);
    memset(vm_FrameBase,0,CHUNK_SIZE);
    memset(vm_data0,0,CHUNK_SIZE);
    memset(vm_data1,0,CHUNK_SIZE);
    memset(vm_data2,0,CHUNK_SIZE);
    memset(vm_data3,0,CHUNK_SIZE);

    //init mem section
    cpu->v_rex = (uint32_t *)vm_data0;
    cpu->v_rfx = (uint32_t *)vm_data1;
    cpu->v_rgx = (uint32_t *)vm_data2;
    cpu->v_rhx = (uint32_t *)vm_data3;
    cpu->v_rfp = (uint32_t *)vm_FrameBase;

    cpu->op_list[0].opcode = 0x01;
    cpu->op_list[0].handle = (void (*)(void *))vMovImm2Reg;
    cpu->op_list[1].opcode = 0x02;
    cpu->op_list[1].handle = (void (*)(void *))vMovMem2Reg;
    cpu->op_list[2].opcode = 0x03;
    cpu->op_list[2].handle = (void (*)(void *))vMovReg2Reg;
    cpu->op_list[3].opcode = 0x04;
    cpu->op_list[3].handle = (void (*)(void *))vMovReg2Mem;
    cpu->op_list[4].opcode = 0x05;
    cpu->op_list[4].handle = (void (*)(void *))vMovImm2Mem;
    cpu->op_list[5].opcode = 0x06;
    cpu->op_list[5].handle = (void (*)(void *))vMovMem2Mem;

    cpu->op_list[6].opcode = 0x10;
    cpu->op_list[6].handle = (void (*)(void *))vAddReg4Imm2Reg;
    cpu->op_list[7].opcode = 0x11;
    cpu->op_list[7].handle = (void (*)(void *))vAddReg4Reg2Reg;
    cpu->op_list[8].opcode = 0x12;
    cpu->op_list[8].handle = (void (*)(void *))vAddReg4Mem2Reg;
    cpu->op_list[9].opcode = 0x13;
    cpu->op_list[9].handle = (void (*)(void *))vAddReg4Imm2Mem;
    cpu->op_list[10].opcode = 0x14;
    cpu->op_list[10].handle = (void (*)(void *))vAddReg4Reg2Mem;
    cpu->op_list[11].opcode = 0x15;
    cpu->op_list[11].handle = (void (*)(void *))vAddReg4Mem2Mem;

    cpu->op_list[12].opcode = 0x26;
    cpu->op_list[12].handle = (void (*)(void *))vSubReg4Imm2Reg;
    cpu->op_list[13].opcode = 0x27;
    cpu->op_list[13].handle = (void (*)(void *))vSubReg4Reg2Reg;
    cpu->op_list[14].opcode = 0x28;
    cpu->op_list[14].handle = (void (*)(void *))vSubReg4Mem2Reg;
    cpu->op_list[15].opcode = 0x29;
    cpu->op_list[15].handle = (void (*)(void *))vSubReg4Imm2Mem;
    cpu->op_list[16].opcode = 0x2a;
    cpu->op_list[16].handle = (void (*)(void *))vSubReg4Reg2Mem;
    cpu->op_list[17].opcode = 0x2b;
    cpu->op_list[17].handle = (void (*)(void *))vSubReg4Mem2Mem;

    cpu->op_list[18].opcode = 0x30;
    cpu->op_list[18].handle = (void (*)(void *))vMulReg4Imm2Reg;
    cpu->op_list[19].opcode = 0x31;
    cpu->op_list[19].handle = (void (*)(void *))vMulReg4Reg2Reg;
    cpu->op_list[20].opcode = 0x32;
    cpu->op_list[20].handle = (void (*)(void *))vMulReg4Mem2Reg;
    cpu->op_list[21].opcode = 0x33;
    cpu->op_list[21].handle = (void (*)(void *))vMulReg4Imm2Mem;
    cpu->op_list[22].opcode = 0x34;
    cpu->op_list[22].handle = (void (*)(void *))vMulReg4Reg2Mem;
    cpu->op_list[23].opcode = 0x35;
    cpu->op_list[23].handle = (void (*)(void *))vMulReg4Mem2Mem;

    cpu->op_list[24].opcode = 0x46;
    cpu->op_list[24].handle = (void (*)(void *))vSraReg4Imm2Reg;
    cpu->op_list[25].opcode = 0x47;
    cpu->op_list[25].handle = (void (*)(void *))vSraReg4Reg2Reg;
    cpu->op_list[26].opcode = 0x48;
    cpu->op_list[26].handle = (void (*)(void *))vSraReg4Mem2Reg;
    cpu->op_list[27].opcode = 0x49;
    cpu->op_list[27].handle = (void (*)(void *))vSraReg4Imm2Mem;
    cpu->op_list[28].opcode = 0x4a;
    cpu->op_list[28].handle = (void (*)(void *))vSraReg4Reg2Mem;
    cpu->op_list[29].opcode = 0x4b;
    cpu->op_list[29].handle = (void (*)(void *))vSraReg4Mem2Mem;

    cpu->op_list[30].opcode = 0x50;
    cpu->op_list[30].handle = (void (*)(void *))vSllReg4Imm2Reg;
    cpu->op_list[31].opcode = 0x51;
    cpu->op_list[31].handle = (void (*)(void *))vSllReg4Reg2Reg;
    cpu->op_list[32].opcode = 0x52;
    cpu->op_list[32].handle = (void (*)(void *))vSllReg4Mem2Reg;
    cpu->op_list[33].opcode = 0x53;
    cpu->op_list[33].handle = (void (*)(void *))vSllReg4Imm2Mem;
    cpu->op_list[34].opcode = 0x54;
    cpu->op_list[34].handle = (void (*)(void *))vSllReg4Reg2Mem;
    cpu->op_list[35].opcode = 0x55;
    cpu->op_list[35].handle = (void (*)(void *))vSllReg4Mem2Mem;

    cpu->op_list[36].opcode = 0x66;
    cpu->op_list[36].handle = (void (*)(void *))vXorReg4Imm2Reg;
    cpu->op_list[37].opcode = 0x67;
    cpu->op_list[37].handle = (void (*)(void *))vXorReg4Reg2Reg;
    cpu->op_list[38].opcode = 0x68;
    cpu->op_list[38].handle = (void (*)(void *))vXorReg4Mem2Reg;
    cpu->op_list[39].opcode = 0x69;
    cpu->op_list[39].handle = (void (*)(void *))vXorReg4Imm2Mem;
    cpu->op_list[40].opcode = 0x6a;
    cpu->op_list[40].handle = (void (*)(void *))vXorReg4Reg2Mem;
    cpu->op_list[41].opcode = 0x6b;
    cpu->op_list[41].handle = (void (*)(void *))vXorReg4Mem2Mem;

    cpu->op_list[42].opcode = 0x70;
    cpu->op_list[42].handle = (void (*)(void *))vAndReg4Imm2Reg;
    cpu->op_list[43].opcode = 0x71;
    cpu->op_list[43].handle = (void (*)(void *))vAndReg4Reg2Reg;
    cpu->op_list[44].opcode = 0x72;
    cpu->op_list[44].handle = (void (*)(void *))vAndReg4Mem2Reg;
    cpu->op_list[45].opcode = 0x73;
    cpu->op_list[45].handle = (void (*)(void *))vAndReg4Imm2Mem;
    cpu->op_list[46].opcode = 0x74;
    cpu->op_list[46].handle = (void (*)(void *))vAndReg4Reg2Mem;
    cpu->op_list[47].opcode = 0x75;
    cpu->op_list[47].handle = (void (*)(void *))vAndReg4Mem2Mem;

    cpu->op_list[48].opcode = 0x80;
    cpu->op_list[48].handle = (void (*)(void *))vOrReg4Imm2Reg;
    cpu->op_list[49].opcode = 0x81;
    cpu->op_list[49].handle = (void (*)(void *))vOrReg4Reg2Reg;
    cpu->op_list[50].opcode = 0x82;
    cpu->op_list[50].handle = (void (*)(void *))vOrReg4Mem2Reg;
    cpu->op_list[51].opcode = 0x83;
    cpu->op_list[51].handle = (void (*)(void *))vOrReg4Imm2Mem;
    cpu->op_list[52].opcode = 0x84;
    cpu->op_list[52].handle = (void (*)(void *))vOrReg4Reg2Mem;
    cpu->op_list[53].opcode = 0x85;
    cpu->op_list[53].handle = (void (*)(void *))vOrReg4Mem2Mem;

    cpu->op_list[54].opcode = 0x86;
    cpu->op_list[54].handle = (void (*)(void *))vSetLessThanImm;
    cpu->op_list[55].opcode = 0x87;
    cpu->op_list[55].handle = (void (*)(void *))vSetLessThanReg;
    cpu->op_list[56].opcode = 0x88;
    cpu->op_list[56].handle = (void (*)(void *))vBranchNotEquelZero;
    cpu->op_list[57].opcode = 0x89;
    cpu->op_list[57].handle = (void (*)(void *))vBranchNotEquelReg;
    cpu->op_list[58].opcode = 0x8a;
    cpu->op_list[58].handle = (void (*)(void *))vBranchIfEquelZero;
    cpu->op_list[59].opcode = 0x8b;
    cpu->op_list[59].handle = (void (*)(void *))vBranchIfEquelReg;

    cpu->op_list[60].opcode = 0x90;
    cpu->op_list[60].handle = (void (*)(void *))vJmp;
    cpu->op_list[61].opcode = 0x91;
    cpu->op_list[61].handle = (void (*)(void *))vNop;

    //append
    cpu->op_list[62].opcode = 0xa0;
    cpu->op_list[62].handle = (void (*)(void *))vNorReg4Imm2Reg;
    cpu->op_list[63].opcode = 0xa1;
    cpu->op_list[63].handle = (void (*)(void *))vNorReg4Reg2Reg;
    cpu->op_list[64].opcode = 0xa2;
    cpu->op_list[64].handle = (void (*)(void *))vNorReg4Mem2Reg;
    cpu->op_list[65].opcode = 0xa3;
    cpu->op_list[65].handle = (void (*)(void *))vNorReg4Imm2Mem;
    cpu->op_list[66].opcode = 0xa4;
    cpu->op_list[66].handle = (void (*)(void *))vNorReg4Reg2Mem;

    cpu->op_list[67].opcode = 0xb0;
    cpu->op_list[67].handle = (void (*)(void *))vPushImm;
    cpu->op_list[68].opcode = 0xb1;
    cpu->op_list[68].handle = (void (*)(void *))vPushMem;
    cpu->op_list[69].opcode = 0xb2;
    cpu->op_list[69].handle = (void (*)(void *))vPushReg;
    cpu->op_list[70].opcode = 0xb3;
    cpu->op_list[70].handle = (void (*)(void *))vPopImm;
    cpu->op_list[71].opcode = 0xb4;
    cpu->op_list[71].handle = (void (*)(void *))vPopMem;
    cpu->op_list[72].opcode = 0xb5;
    cpu->op_list[72].handle = (void (*)(void *))vPopReg;

    cpu->op_list[73].opcode = 0xc0;
    cpu->op_list[73].handle = (void (*)(void *))vAtomAdd;
    cpu->op_list[74].opcode = 0xc1;
    cpu->op_list[74].handle = (void (*)(void *))vAtomSub;
    cpu->op_list[75].opcode = 0xc2;
    cpu->op_list[75].handle = (void (*)(void *))vAtomAnd;
    cpu->op_list[76].opcode = 0xc3;
    cpu->op_list[76].handle = (void (*)(void *))vAtomXor;
    cpu->op_list[77].opcode = 0xc4;
    cpu->op_list[77].handle = (void (*)(void *))vAtomOr;
    cpu->op_list[78].opcode = 0xc5;
    cpu->op_list[78].handle = (void (*)(void *))vAtomNor;
    cpu->op_list[79].opcode = 0xc6;
    cpu->op_list[79].handle = (void (*)(void *))vAtomMul;
    cpu->op_list[80].opcode = 0xc7;
    cpu->op_list[80].handle = (void (*)(void *))vAtomSll;
    cpu->op_list[81].opcode = 0xc8;
    cpu->op_list[81].handle = (void (*)(void *))vAtomSra;
    
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
    while((*cpu->v_eip)!= Ret)
    {
        vm_dispatcher(cpu);
    }
}

void printfBadVm(void){
    printf("___.               ._______   ____      \n");
    printf("\\_ |__ _____     __| _\/\\   \\ \/   \/____  \n");
    printf(" | __ \\\\__  \\   \/ __ |  \\   Y   \/     \\ \n");
    printf(" | \\_\\ \\\/ __ \\_\/ \/_\/ |   \\     \/  Y Y  \\\n");
    printf(" |___  (____  \/\\____ |    \\___\/|__|_|  \/\n");
    printf("     \\\/     \\\/      \\\/               \\\/ 2.0 \n");
}