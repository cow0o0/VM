.section .data

msg:
    .ascii "hello world"
    len = .-msg

.section .text

#.global _start
#_start:

.global _start

_start:
movl $len,%edx
movl $msg,%ecx
movl $1  ,%ebx
movl $4  ,%eax

int $0x80

# exit

movl $0,%ebx
movl $1,%eax

int $0x80
