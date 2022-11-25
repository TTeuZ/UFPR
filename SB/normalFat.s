.section .data
.section .text
.globl _start
fat:
    pushq %rbp
    movq %rsp, %rbp
    movq 16(%rbp), %rax
    movq $0, %rbx
    cmpq %rbx, %rax
    jne else
    movq $1, %rdi
    jmp end_if
else:
    movq %rax, %rbx
    subq $1, %rbx
    pushq %rbx
    call fat
    addq $8, %rsp
    movq 16(%rbp), %rax
    imul %rax, %rdi
end_if:
    popq %rbp
    ret
_start:
    pushq %rsp
    movq %rsp, %rbp
    pushq $3
    call fat
    addq $8, %rsp
    movq $60, %rax
    syscall
