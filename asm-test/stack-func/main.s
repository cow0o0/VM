.section .data
var:
    .int 100
plus_no:
    .int 8
.section .bss
    .lcomm result ,4

.section .text
.globl _start
.code32
_start:
    nop
    pushl var
    pushl plus_no
    call cal_func

    movl $1,%eax
    int $0x80

cal_func:
    pushl %ebp
    movl %esp,%ebp

    movl $0,%eax
    addl 8(%ebp),%eax
    addl 12(%ebp),%eax
    movl %eax,%ebx

    movl %ebp,%esp
    popl %ebp
    ret
    