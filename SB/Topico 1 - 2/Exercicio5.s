# Programa para imprimir o tamanho das seções .text e .data

.section .data
    D_START: .quad 0
    D_END: .quad 0
.section .text
.globl _start
_start:
t_start:
    movq $t_start, %rcx
    movq $t_end, %rdx
    movq $D_END, %rbx
    movq $D_START, %rax
debug:
    subq %rcx, %rdx
    subq %rax, %rbx
    movq $60, %rax
debug2:
    syscall
t_end:
