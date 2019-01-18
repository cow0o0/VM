.section .data
output:
    .ascii "The result is %d.\n"

.section .bss
    .lcomm result,4
.section .text
.globl _start
.code32
_start:
    nop
    movl $0,result
    movl %esp,%ebp

    pushl 8(%ebp)
    call atoi
    movl %eax,result

    pushl 12(%ebp)
    call atoi
    addl %eax,result

    pushl result
    pushl $output
    call printf

    movl $1,%eax
    int $0x80
