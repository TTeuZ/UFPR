# Selection sort in Assembly AMD64 (x86-64)

.section .data
    DATA_ITEMS: .quad 3, 67, 34, 222, 45, 75, 54, 34, 44, 33, 22, 11, 66, 0
.section .text
.globl _start
_start:
    movq $0, %rdi # Iterador dos loops
main_loop:
    movq DATA_ITEMS(, %rdi , 8), %rbx # %rbx := DATA_ITEMS[i]
    cmpq $0, %rbx # Se chegamos no ultimo elemento do array, saimos do main loop (
    je end_main_loop
    movq %rdi, %rsi # Salavando valor atual do %rdi em %rsi
    movq %rdi, %rcx # Menor posição começa na posição atual do main_loop
    movq %rbx, %rdx
intern_loop:
    addq $1, %rdi
    movq DATA_ITEMS(, %rdi , 8), %rax
    cmpq $0, %rax
    je end_intern_loop
    cmpq %rdx, %rax
    jge end_intern_if
    movq %rdi, %rcx
    movq %rax, %rdx
end_intern_if:
    jmp intern_loop
end_intern_loop:
    cmpq %rsi, %rcx
    je end_if
    movq %rcx, %rdi
    movq %rbx, DATA_ITEMS(, %rdi , 8)
    movq %rsi, %rdi
    movq %rdx, DATA_ITEMS(, %rdi , 8)
end_if:
    movq %rsi, %rdi
    addq $1, %rdi
    jmp main_loop
end_main_loop:
    movq $60, %rax
    syscall
