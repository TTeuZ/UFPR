.section .data
    A: .quad 0
    B: .quad 0
.section .text
.globl _start
soma:
    pushq %rbp
    movq %rsp, %rbp
    subq $8, %rsp
    movq 16(%rbp), %rbx
    movq 24(%rbp), %rax
    addq %rbx, %rax
    movq %rax, -8(%rbp)
    addq $8, %rsp
    popq %rbp
debug:
    ret
_start: 
    movq $4, A
    movq $5, B
    pushq B
    pushq A
    call soma
    addq $16, %rsp
    movq %rax, B
    movq %rax, %rdi
    movq $60, %rax
    syscall


# .section .data
#     A: .quad 0
#     B: .quad 0
# .section .text
# .globl _start
# soma:
#     pushq %rbp
#     movq %rsp, %rbp
#     subq $8, %rsp
#     movq 16(%rbp), %rbx
#     movq 24(%rbp), %rax
#     addq %rbx, %rax
#     movq %rax, -8(%rbp)
#     addq $8, %rsp
#     popq %rbp
#     ret
# _start: 
#     movq $4, A
#     movq $5, B
#     movq A, %rax
#     movq B, %rbx
#     movq %rax, 16(%rbp)
#     movq %rbx, 24(%rbp)
#     call soma
#     movq %rax, B
#     movq %rax, %rdi
#     movq $60, %rax
#     syscall
# Esse é o errado, não é a maneira certa de fazer um push de parametros, tem que usar o pushq
