.section .data
values:
    .int 10,20,30,40

.section .text
.globl _start
_start:
    nop
    movl values,%eax
    movl $values,%edi
    movl $100,4(%edi)
    movl $1,%edi
    movl $1,%eax
    int $0x80
