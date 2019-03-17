.section .text
.globl _start
_start:
    nop
    movl $1,%eax
    jmp jmp_here
    movl $11,%ebx
    int $0x80

jmp_here:
    movl $20,%ebx
    int $0x80
    