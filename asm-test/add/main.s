.section .text
.globl _start
_start:
    nop
    movl $0,%ebx
    movb $2,%bl
    movb $2,%al
    #addb %al,%bl
    inc %ebx
    dec %ebx
    sal $2,%ebx
    sar $2,%ebx

    jc  jc_here
    movl $1,%eax
    int $0x80

jc_here:
    movl $0,%ebx
    movl $1,%eax
    int $0x80
