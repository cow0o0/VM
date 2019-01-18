.section .data
var1:
    .ascii "Hello123"
var2:
    .ascii "Hello456"
.section .bss
    .lcomm index,8

.section .text
.globl _start
_start:
    nop
    leal var1,%esi
    leal var2,%edi
    movl $8,%ecx

    cld
    rep cmpsb
    je equal

    movl %ecx,%ebx
    movl $1,%eax
    int $0x80

equal:
    movl $0,%ebx
    movl $1,%eax
    int $0x80
