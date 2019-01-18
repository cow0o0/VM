.section .data
msg:
    .ascii "This is call\n"
    len = .-msg
.section .text
.globl _start
_start:

    nop
    call call_func

    movl $0,%ebx
    movl $1,%eax
    int $0x80

.code32
call_func:
    pushl %ebp
    movl %esp,%ebp

    #func code here
    movl $len,%edx
    movl $msg,%ecx
    movl $1  ,%ebx
    movl $4  ,%eax  #sys_write
    int $0x80

    movl %ebp,%esp
    popl %ebp
    ret
