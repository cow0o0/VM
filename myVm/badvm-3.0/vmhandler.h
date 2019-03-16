#ifndef _H_VMHANDLER
#define _H_VMHANDLER

#include"vmopcode.h"

// 隐藏光标
#define HIDE_CURSOR() printf("\033[?25l")
// 显示光标
#define SHOW_CURSOR() printf("\033[?25h")

void vm_init(vm_cpu *cpu);
void vm_dispatcher(vm_cpu *cpu);
void vm_start(vm_cpu *cpu);
void vm_over(vm_cpu *cpu);
void setBufferedInput(bool enable);
void printfBadVm(void);
#endif