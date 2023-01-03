.section .data
    HEAP_START: .quad 0

    STR0: .string " "
    STR1: .string "topo da heap %p\n"
.section .text
.globl main

startAllocator:
# --------------------------------------------- registro de ativação
    pushq %rbp                                  # 
    movq %rsp, %rbp                             #
# ---------------------------------------------
    movq $12, %rax                              # %rax <- 12 (syscall brk)
    movq $0, %rdi                               # %rdi <- 0 (parametro)
    syscall                                     # chamada do sistema para o brk
    movq %rax, HEAP_START                       # armazena o topo atual da pilha em HEAP_START
# --------------------------------------------- restauração do registro de ativação
    popq %rbp                                   #
    ret                                         #

endAllocator:
# --------------------------------------------- registro de ativação
    pushq %rbp                                  #
    movq %rsp, %rbp                             #
# ---------------------------------------------
    movq $12, %rax                              # %rax <- 12 (syscall brk)
    movq HEAP_START, %rdi                       # %rdi <- HEAP_START (parametro)
    syscall                                     # chamada do sistema para o brk
# --------------------------------------------- restauração do registro de ativação
    popq %rbp                                   #
    ret                                         #

freeMemory:
# --------------------------------------------- registro de ativação
    pushq %rbp                                  #
    movq %rsp, %rbp                             #
# ---------------------------------------------

# --------------------------------------------- restauração do registro de ativação
    popq %rbp                                   #
    ret                                         #

# -8(%rbp) = void *temp = %r9
# -16(%rbp) = void *iterator = %r10
# -24(%rbp) = void *freeSpace = %r11
# parametro num_bytes = %rdi
allocateMemory:
# --------------------------------------------- registro de ativação
    pushq %rbp                                  #
    movq %rsp, %rbp                             #
    subq $24, %rsp                              # requisitando espaço para 3 variaveis locais
# ---------------------------------------------
    pushq %rdi                                  # salvando o valor de %rdi (num_bytes)

    movq $12, %rax                              # %rax <- 12 (syscall brk)
    movq $0, %rdi                               # %rdi <- 0 (parametro)
    syscall                                     # chamada do sistema para o brk
    movq %rax, -8(%rbp)                         # temp <- topo atual da heap

    movq $0, -24(%rbp)                          # freeSpace <- null (0)

    movq HEAP_START, %r8                        # %r8 <- topo inicial da heap
    movq %r8, -16(%rbp)                         # freeSpace <- topo inicial da heap

    popq %rdi                                   # recuperando o valor de %rdi (num_bytes)

while:
    movq -8(%rbp), %r9                          # %r9 <- temp
    movq -16(%rbp), %r10                        # %r10 <- iterator
    cmpq %r9, %r10                              # compara %r10 com %r9
    jge end_while                               # se iterator >= temp vai para o fim do while

    movq $0, %r8                                # %r8 <- 0
    cmpq (%r10), %r8                            # compara *(int*)iterator com 0
    jg else_free_if                             # se for maior que 0 (1) vai para o fim deste if

    addq $8, %r10                               # iterator <- iteator + 8

    cmpq (%r10), %rdi                           # compara *(int*)iterator com num_bytes
    jl else_bytes_if                            # se for menor vai para o fim deste if

    addq $8, %r10                               # iterator <- iterator + 8
    movq %r10, -24(%rbp)                        # freeSpace <- iterator
    jmp end_while                               # encontrou o espaço, sai do while
else_bytes_if:
    addq $8, %r10                               # iterator <- iterator + 8
    jmp exit_free_if                            # sai da execução do if (para não pegar o else_free_if)
else_free_if:
    addq $16, %r10                              # iterator <- iterator + 16
exit_free_if:
    movq %r10, %r8                              # %r8 <- iterator
    subq $8, r8                                 # %r8 <- iterator - 8
    addq (%r8), %r10                            # %r10 <- iterator + *(int*)iterator
    movq %r10, -16(%rbp)                        # iterator <- %r10
    jmp while                                   # volta para o inicio do while
end_while:
    movq -24(%rbp), %r11                        # %r11 <- freeSpace
    cmpq %r11, $0                               # compara freeSpace com null (0)
    jne else_alloc_if

    movq $12, %rax                              # %rax <- 12 (syscall brk)
    movq %rdi, %r8                              # %r8 <- num_bytes
    addq $16, %rdi                              # num_bytes <- num_bytes + 16 (variaveis de controle)
    syscall                                     # chamada do sistema para o brk (num_bytes ja esta em %rdi)

    movq %rax, %r9                              # temp(%r9) <- retorno do brk

    movq $1, (%r9)                              # *(int*)temp <- 1
    addq $8, %r9                                # temp <- temp + 8
    movq %r8, (%r9)                             # *(int*)temp <- num_bytes
    addq $8, %r9                                # temp <- temp + 8

    movq %r9, -8(%rbp)                         # atualiza a variavel local
    jmp exit_alloc_if                           
else_alloc_if:
    subq $16, %r11                              # freeSpace(r11) <- freeSpace - 16
    movq $1, (%r11)                             # *(int*)freeSpace <- 1
    addq $16, %r11                              # freeSpace(r11) <- freeSpace + 16
    movq %r11, -24(%rbp)                        # atualiza a variavel local
    movq %r11, -8(%rbp)                         # temp <- freeSpace
exit_free_if:
    movq -8(%rbp), %rdi                         # coloca temp como retorno da função
    
# --------------------------------------------- restauração do registro de ativação
    addq $24, %rsp                              # restauradno o espaço das 3 variaveis locais
    popq %rbp                                   #
    ret                                         #

main:
# --------------------------------------------- registro de ativação
    pushq %rbp                                  #
    movq %rsp, %rbp                             #
# ---------------------------------------------
    movq $STR0, %rdi                            # 1° parametro do printf
    call printf                                 # primeiro printf para instaurar o buffer do printf

    call startAllocator                         # chamando o startAllocator

    movq HEAP_START, %rsi                       # 2° parametro do printf
    movq $STR1, %rdi                            # 1° parametro do printf
    call printf                                 # printf 

    movq $100, %rdi                             # num_bytes = 100
    call allocateMemory                         # allocateMemory(100)

    call endAllocator                           # chamando o endAllocator

    movq $60, %rax                              #
    syscall                                     #
