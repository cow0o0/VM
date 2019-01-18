.section .data
var:
    .ascii "Hello."
    len = .-var
.section .bss
    .lcomm output,7
.section .text
.globl _start
_start:
    leal var,%esi
    leal output,%edi
    movl $7,%ecx

    cld
    rep movsb

    movl $0,%ebx
    movl $1,%eax
    int $0x80
