.section .data
output:
    .ascii "The processor Vendor ID is 'XXXXXXXXXXXX'\n"

.section .text
.global _start
_start:
    movl $0,%eax
    cpuid 
    movl $output,%edi
    movl %ebx,28(%edi)
    movl %edx,32(%edi)
    movl %ecx,36(%edi)

    movl $42,%edx
    movl $output,%ecx
    movl $1,%ebx
    movl $4,%eax
    int $0x80

    movl $0,%ebx
    movl $1,%eax
    int $0x80
    