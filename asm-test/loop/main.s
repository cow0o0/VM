.section .text
.globl _start
_start:
    movl $10,%ecx
    movl $0 ,%eax
loop_here:
    addl %ecx,%eax
    loop loop_here

    movl %eax,%ebx
    movl $1  ,%eax
    int $0x80
