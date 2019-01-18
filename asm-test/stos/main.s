.section .data
space:
    .ascii "1"
.section .bss
    .lcomm output,256
.section .text
.globl _start
_start:
    nop
    leal space,%esi
    leal output,%edi
    movl $256,%ecx

    cld
    lodsb #esi -> eax
    rep stosb #

    movl $0,%ebx
    movl $1,%eax
    int $0x80
    