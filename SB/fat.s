.section .data
.section .text
.globl _start
fat:
    pushq %rbp
    movq %rsp, %rbp
    subq $8, %rsp
    movq 24(%rbp), %rax
    movq $1, %rbx
    cmpq %rbx, %rax
    jg else
    movq 16(%rbp), %rbx
    movq $1, (%rbx)
    jmp end_if
else:
    movq 24(%rbp), %rax
    subq $1, %rax
    movq 16(%rbp), %rbx
    pushq %rax
    pushq %rbx
    call fat
    addq $16, %rsp
    movq 24(%rbp), %rax
    movq 16(%rbp), %rbx
    movq (%rbx), %rbx
    imul %rax, %rbx
    movq %rbx, -8(%rbp)
    movq -8(%rbp), %rax
    movq 16(%rbp), %rbx
    movq %rax, (%rbx)
end_if:
    addq $8, %rsp
    popq %rbp
    ret
_start:
    pushq %rsp
    movq %rsp, %rbp
    subq $8, %rsp
    pushq $3
    movq %rbp, %rax
    subq $8, %rax
    pushq %rax
    call fat
    movq -8(%rbp), %rdi
    addq $16, %rsp
    movq $60, %rax
    syscall
