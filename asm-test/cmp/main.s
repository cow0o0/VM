.section .text
.globl _start
_start:
    nop
    movl $11,%eax
    movl $12,%ebx
    cmp %eax,%ebx
    jle jae_here
    movl $1,%eax
    int $0x80

jae_here:
    movl $20,%ebx
    movl $1 ,%eax
    int $0x80
    

