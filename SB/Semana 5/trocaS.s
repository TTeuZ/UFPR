.section .data
    A: .quad 0
    B: .quad 0
.section .text
.globl _start
troca:
    # ------------------------------------------------------------------------------------------------
    pushq %rbp              # Atualização do sp para a nova página
    movq %rsp, %rbp
    # ------------------------------------------------------------------------------------------------
    subq $8, %rsp           # armazenando espaço na pilha para variaveis internas
    # ------------------------------------------------------------------------------------------------
    movq 16(%rbp), %rax
    movq (%rax), %rbx       # pegando o valor que esta armazenado no primeiro parametro (A)
    # ------------------------------------------------------------------------------------------------
    movq %rbx, -8(%rbp)      # z <- *x
    # ------------------------------------------------------------------------------------------------
    movq 24(%rbp), %rax
    movq (%rax), %rbx       # pegando o valor armazenado no segunda parametro (B)
    movq 16(%rbp), %rax
    movq %rbx, (%rax)       # *x <- *y 
    # ------------------------------------------------------------------------------------------------
    movq 24(%rbp), %rax 
    movq -8(%rbp), %rbx     # pegando o valor da variavel interna e jogando em %rbx
    movq %rbx, (%rax)       # *y <- z
    # ------------------------------------------------------------------------------------------------
    addq $8, %rsp           # voltando a pilha para o lugar certo
    popq %rbp               # restaurando o valor antigo de %rbp
    ret                     # saindo da função
_start:
    movq $1, A
    movq $2, B
    movq A, %rax
    movq B, %rbx
debug1:
    pushq $B
    pushq $A
    call troca
    addq $16, %rsp
    # ------------------------------------------------------------------------------------------------
    movq A, %rax
    movq B, %rbx
debug2:
    movq $60, %rax
    syscall

# Sobre a linha 21:
# Como temos o %rbx com o valor de B, nos buscamos o conteudo que esta dentro de A, que seria o %rax, e inserimos o valor
# aonde o A esta apontando, ou seja, acessamos o espaço de memoria apontato por A e atualizamos o valor que está la
