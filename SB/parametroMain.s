.section .data
    str1: .string "argc batata\n"
    str2: .string "argv[%d]: %s\n"
    str3: .string "arge[%d]: %s\n"
.section .text
.globl main
main:
    pushq %rbp
    movq %rsp, %rbp
    subq $40, %rsp          # Locais para salvar % rsi e % rdi
    movq %rdi, -8(%rbp)      # salva % rdi ( argc )
    movq %rsi, -16(%rbp)     # salva % rsi ( argv [0])
    movq %rdx, -24(%rbp)
# ------------------------------- print do arqc
#    movq -8(%rbp), %rsi      # segundo parametro do printf
#    movq  str1, %rdi        # primeiro parametro do printf
#    call printf
# ------------------------------- print do arqc
# ------------------------------- print do arqv
    movq -16(%rbp), %rbx    # recuperando o valor de argv
    movq $0, %rsi           # %rsi <- 0
while:
    movq (%rbx), %rdx       # segundo parametro para o printf (alem de usar para comparar no while)
    movq $0, %rax
    cmpq %rax, %rdx         # Verifica se chegamos no null do argv               
    je end_while
    movq $str2, %rdi        # primeiro parametro : $str2    
    pushq %rsi              # salva o rsi 
    call printf
    popq %rsi               # restaura do %rsi
    addq $1, %rsi           # %rsi++
    addq $8, %rbx           # pega proximo do argv
    jmp while
end_while:
# ------------------------------- print do arqv
# ------------------------------- print do arqe
    movq -24(%rbp), %rbx    # recuperando o valor de arge
    movq $0, %rsi           # %rsi <- 0
while2:
    movq (%rbx), %rdx       # segundo parametro para o printf (alem de usar para comparar no while)
    movq $0, %rax
    cmpq %rax, %rdx         # Verifica se chegamos no null do argv 
    je end_while2
    movq $str3, %rdi        # primeiro parametro : $str2
    pushq %rsi              # salva o rsi 
    call printf
    popq %rsi               # restaura do %rsi
    addq $1, %rsi           # %rsi++
    addq $8, %rbx           # pega proximo do argv
    jmp while2
end_while2:
# ------------------------------- print do arqe
    movq -8(%rbp), %rdi      # restaura % rdi
    movq -16(%rbp), %rsi     # restaura % rsi
    movq $0, %rdi
    movq $60, %rax
    syscall
