.section .data
    HEAP_START: .quad 0
    HEAP_END: .quad 0

    INT_MAX: .quad 0x7fffffff

    STR: .string "\n"
    STR1: .string "topo da heap %p\n"
.section .text
.globl main

iniciaAlocador:
# --------------------------------------------- registro de ativação
    pushq %rbp                                  # 
    movq %rsp, %rbp                             #
# ---------------------------------------------
    movq $12, %rax                              # %rax <- 12 (syscall brk)
    movq $0, %rdi                               # %rdi <- 0 (parametro)
    syscall                                     # chamada do sistema para o brk
    movq %rax, HEAP_START                       # armazena o topo atual da heap em HEAP_START
    movq %rax, HEAP_END                         # armazena o topo atual da heap em HEAP_END
# --------------------------------------------- restauração do registro de ativação
    popq %rbp                                   #
    ret                                         #

finalizaAlocador:
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

# parametro num_bytes = %rdi
liberaMem:
# --------------------------------------------- registro de ativação
    pushq %rbp                                  #
    movq %rsp, %rbp                             #
# ---------------------------------------------
    movq %rdi, %r10                             # $r10 <- %rdi
    subq $16, %r10                              # %r1- <- %r10 - 16
    movq $0, (%r10)                             # (%r10) <- 0
    movq $0, %rdi                               # retorno da função = 0    
# --------------------------------------------- restauração do registro de ativação
    popq %rbp                                   #
    ret                                         #

# -8(%rbp) = void *temp = %r9
# -16(%rbp) = void *iterator = %r10
# -24(%rbp) = void *freeSpace = %r11
# -32(%rbp) = bytesQtd = %r8
# -40(%rbp) = diff = %r13
# parametro num_bytes = %rdi
alocaMem:
# --------------------------------------------- registro de ativação
    pushq %rbp                                  #
    movq %rsp, %rbp                             #
    subq $40, %rsp                              # requisitando espaço para 5 variaveis locais
    pushq %r13                                  # salvando %r13
    pushq %r14                                  # salvando %r14
# ---------------------------------------------
    movq $0, -24(%rbp)                          # freeSpace <- null (0)
    movq INT_MAX, %r8                           # %r8 <- INT_MAX
    movq %r8, -32(%rbp)                         # bytesQtd <- INT_MAX 

    movq HEAP_START, %r8                        # %r8 <- topo inicial da heap
    movq %r8, -16(%rbp)                         # iterator <- topo inicial da heap

while:
    movq HEAP_END, %r8                          # %r8 <- topo atual da heap
    movq -16(%rbp), %r10                        # %r10 <- iterator
    cmpq %r8, %r10                              # compara iterador com topo atual da heap
    jge end_while                               # se iterator >= temp vai para o fim do while
    
    movq $0, %r8                                # %r8 <- 0
    cmpq %r8, (%r10)                          # compara *(int*)iterator com 0
    jg else_free_if                             # se for maior que 0 (1) vai para o fim deste if

    addq $8, %r10                               # iterator <- iteator + 8

    cmpq (%r10), %rdi                           # compara *(int*)iterator com num_bytes
    jg else_bytes_if                            # se for menor vai para o fim deste if

    movq -32(%rbp), %r8                         # %r8 <- bytesQtd
    cmpq %r8, (%r10)                            # compara *(int*)iterator com bytesQtd
    jg else_bytes_if                            # se for maior vai para o fim deste if

    movq (%r10), %r8                            # bytesQtd <- *(int*)iterator
    movq %r8, -32(%rbp)                         # atualiza a variavel local
    addq $8, %r10                               # iterator <- iterator + 8
    movq %r10, -24(%rbp)                        # freeSpace <- iterator
    jmp exit_if                                 # sai do if
else_bytes_if:
    addq $8, %r10                               # iterator <- iterator + 8
    jmp exit_if                                 # sai da execução do if (para não pegar o else_free_if)
else_free_if:
    addq $16, %r10                              # iterator <- iterator + 16
exit_if:
    movq %r10, %r8                              # %r8 <- iterator
    subq $8, %r8                                # %r8 <- iterator - 8
    addq (%r8), %r10                            # %r10 <- iterator + *(int*)iterator
    movq %r10, -16(%rbp)                        # iterator <- %r10
    jmp while                                   # volta para o inicio do while
end_while:
    movq -24(%rbp), %r11                        # %r11 <- freeSpace
    movq $0, %r8                                # %r8 <- 0
    cmpq %r11, %r8                              # compara freeSpace com null (0)
    jne else_alloc_if

    pushq %rdi                                  # salvando o valor de %rdi (num_bytes)

    movq $12, %rax                              # %rax <- 12 (syscall brk)
    movq $0, %rdi                               # %rdi <- 0 (parametro)
    syscall                                     # chamada do sistema para o brk
    movq %rax, -8(%rbp)                         # temp <- topo alocado da heap

    popq %rdi                                   # recuperando o valor de %rdi (num_bytes)

    movq HEAP_END, %r13                         # %r13 <- topo atual da heap
    movq -8(%rbp), %r14                         # %r14 <- temp
    subq %r13, %r14                             # %r14 <- %r14 - %r13
    movq %r14, -40(%rbp)                        # atualiza o valor da variavel local
    cmpq %rdi, %r14                             # compara num_bytes (%rdi) com diff (%r13)
    jge exit_inside_alloc_if                    # sai do if internto

    movq $0, %rdx
    movq %rdi, %rax                             # %rax <- num_bytes
    movq $4096, %rcx                            # %rcx <- 4096
    div %rcx                                    # %rax <- %rax / 4096
    addq $1, %rax                               # %rax <- %rax + 1
    imul $4096, %rax                            # %rax <- %rax * 4096

    pushq %rdi                                  # salvando o valor de %rdi (num_bytes)

    addq -8(%rbp), %rax                         # %rax <- %rax + topo atual da pilha
    movq %rax, %rdi                             # %rdi <- %rax
    movq $12, %rax                              # %rax <- 12 (syscall brk)
    syscall                                     # chamada do sistema para o brk

    popq %rdi                                   # recuperando o valor de %rdi (num_bytes)
exit_inside_alloc_if:
    movq HEAP_END, %r9                          # temp(%r9) <- topo atual da heap

    movq $1, (%r9)                              # *(int*)temp <- 1
    addq $8, %r9                                # temp <- temp + 8
    movq %rdi, (%r9)                             # *(int*)temp <- num_bytes
    addq $8, %r9                                # temp <- temp + 8

    movq %r9, -8(%rbp)                          # atualiza o valor da variavel local
    addq %rdi, %r9                              # %r9 <- %r9 + num_bytes
    movq %r9, HEAP_END                          # topo atual da heap é atualizado
    jmp exit_aloc_if                            # sai do if
else_alloc_if:
    movq -24(%rbp), %r11                        # %r11 <- freeSpace
    subq $16, %r11                              # freeSpace(r11) <- freeSpace - 16
    movq $1, (%r11)                             # *(int*)freeSpace <- 1
    addq $16, %r11                              # freeSpace(r11) <- freeSpace + 16
    movq %r11, -24(%rbp)                        # atualiza a variavel local
    movq %r11, -8(%rbp)                         # temp <- freeSpace
exit_aloc_if:
    movq -8(%rbp), %rdi                         # coloca temp como retorno da função
# --------------------------------------------- restauração do registro de ativação
    popq %r13                                   # retornando o valor %r13
    popq %r14                                   # retornando o valor %r14
    addq $40, %rsp                              # restauradno o espaço das 3 variaveis locais
    popq %rbp                                   #
    ret                                         #

# -8(%rbp) = void *iterador = %r8
# -16(%rbp) = int free = %r9
# -24(%rbp) = int size = %r10
# -32(%rbp) = int count = %r22
imprimeMapa:
# --------------------------------------------- registro de ativação
    pushq %rbp                                  #
    movq %rsp, %rbp                             #
    subq $32, %rsp                              # requisitando espaço para 4 variaveis locais
# ---------------------------------------------
    movq HEAP_START, %r8                        # %r8 <- topo inicial da heap
    movq %r8, -8(%rbp)                          # iterator <- topo inicial da heap

printWhile:


# --------------------------------------------- restauração do registro de ativação
    subq $32, %rsp                              # restauradno o espaço para 4 variaveis locais
    popq %rbp                                   #
    ret                                         #

main:
# --------------------------------------------- registro de ativação
    pushq %rbp                                  #
    movq %rsp, %rbp                             #
    subq $80, %rsp                              # espaço para 8 variaveis locais 
# ---------------------------------------------
    movq $STR, %rdi                             # 1° parametro do printf
    call printf                                 # primeiro printf para instaurar o buffer do printf

    call iniciaAlocador                         # chamando o iniciaAlocador

    movq HEAP_START, %rsi                       # 2° parametro do printf
    movq $STR1, %rdi                            # 1° parametro do printf
    call printf                                 # primeiro printf para instaurar o buffer do printf

    movq $8, %rdi                               # primeira alocação
    call alocaMem
    movq %rdi, -8(%rbp)

    movq $16, %rdi                              # segunda alocação
    call alocaMem
    movq %rdi, -16(%rbp)

    movq $32, %rdi                              # terceira alocação
    call alocaMem
    movq %rdi, -32(%rbp)

    movq $12, %rdi                              # quarta alocação
    call alocaMem
    movq %rdi, -40(%rbp)

    movq -16(%rbp), %rdi                        # primeira desalocação
    call liberaMem

    movq -40(%rbp), %rdi                        # segunda desalocação
    call liberaMem

    movq $10, %rdi                              # quinta alocação
    call alocaMem
    movq %rdi, 48(%rbp)

    movq $15, %rdi                              # sexta alocação
    call alocaMem
    movq %rdi, 56(%rbp)

    movq $3948, %rdi                            # setima alocação
    call alocaMem
    movq %rdi, 64(%rbp)

    movq $8, %rdi                               # oitava alocação
    call alocaMem
    movq %rdi, 72(%rbp)

    call finalizaAlocador                           # chamando o finalizaAlocador

    addq $72, %rsp                              # restaura o valor da pilha
    movq $60, %rax                              #
    syscall                                     #
