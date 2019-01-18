.type print_badrer, @function
.section .data
output:
    .ascii "BadRer"
    len = .-output

.section .text
.globl print_badrer
print_badrer:
    movl $len,%edx
    movl $output,%ecx
    movl $1,%ebx
    movl $4,%eax

    int $0x80

    movl $0,%ebx
    movl $1,%eax
    int $0x80
