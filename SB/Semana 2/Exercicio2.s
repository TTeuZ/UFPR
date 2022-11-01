.section .data
    A: .quad 0
    B: .quad 0
.section .text
.globl _start
_start:
    movq $5, A
    movq $4, B
    movq A, %rax
    movq B, %rbx
    cmpq %rbx, %rax
    jg if
    jle else
if:
    add %rbx, %rax
    jmp fim_if
else:
    movq %rbx, %rdi
    sub %rax, %rdi
    movq %rdi, %rax
    jmp fim_if
fim_if:
    movq %rax, %rdi
    movq $60, %rax
    syscall
