.section .data
    HEAP_START: .quad 0
    HEAP_END: .quad 0

    INT_MAX: .quad 0x7fffffff

    STR0: .string " "
    STR1: .string "topo da heap %p\n"
.section .text
.globl main
                                     #
main:
# --------------------------------------------- registro de ativação
    pushq %rbp                                  #
    movq %rsp, %rbp                             #
# ---------------------------------------------
    movq $0, %rdx
    movq $10, %rax
    movq $5, %rcx
    div %rcx
break:
    movq $60, %rax
    syscall
