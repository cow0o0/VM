.section .data
var:
    .ascii "This is test\n"
    len = .-var

.section .text
.globl _start
_start:
    nop

    leal var,%edi
    movl $0xffff,%ecx
    movb $0,%al

    cld
    repne scasb
    jne not_found

    subw $0xffff,%cx
    neg  %cx
    dec  %cx

    movl %ecx,%ebx
    movl $1,%eax
    int $0x80

not_found:
    movl $0,%ebx
    movl $1,%eax
    int $0x80
