.section .data
    str1: .string "Meu nome eh % s\n"
.section .text
.globl main
main:
    pushq %rbp
    movq %rsp, %rbp
    subq $32, %rsp # Locais para salvar % rsi e % rdi

    movq %rdi, -24(%rbp) # salva % rdi ( argc )
    movq %rsi, -32(%rbp) # salva % rsi ( argv [0])

    movq -32(%rbp), %rbx
    movq (%rbx), %rsi # segundo parametro : * argv [0]
    movq $str1, %rdi # primeiro parametro : $str1
    call printf

    movq -24(%rbp), %rdi # restaura % rdi
    movq -32(%rbp), %rsi # restaura % rsi

    movq $0, %rdi
    movq $60, %rax
    syscall
