.section .data
    HEAP_START: .quad 0
    HEAP_END: .quad 0

    STR: .string "\n"
    STR1: .string "topo da heap %p\n"
    HEADER_STRING: .string "################"
    FREE_CHAR: .string "+"
    OCCUPED_CHAR: .string "-"
.section .text
.globl iniciaAlocador
.globl finalizaAlocador
.globl liberaMem
.globl alocaMem
.globl imprimeMapa

iniciaAlocador:
# --------------------------------------------- registro de ativação
    pushq %rbp                                  # 
    movq %rsp, %rbp                             #
# ---------------------------------------------
    movq $STR, %rdi                             # primeiro parametro do printf
    call printf                                 # chama o printf

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

# -8(%rbp) = void *temp = %r8
# -16(%rbp) = void *iterator = %r9
# -24(%rbp) = void *freeSpace = %r10
# -32(%rbp) = diff = %rcx
# parametro num_bytes = %rdi
alocaMem:
# --------------------------------------------- registro de ativação
    pushq %rbp                                  #
    movq %rsp, %rbp                             #
    subq $32, %rsp                              # requisitando espaço para 5 variaveis locais
# ---------------------------------------------
    movq $0, -24(%rbp)                          # freeSpace <- null (0)
    movq HEAP_START, %r9                        # %r9 <- inicio da heap
    movq %r9, -16(%rbp)                         # iterator <- inicio da heap
while:
    movq HEAP_END, %rdx                         # %rdx <- fim da heap
    movq -16(%rbp), %r9                         # %r9 <- iterador
    cmpq %rdx, %r9                              # compara iterador com topo atual da heap
    jge end_while                               # se iterator >= temp vai para o fim do while

    movq $0, %rdx                               # %rdx <- 0
    movq -24(%rbp), %r10                        # %r10 <- freeSpace
    cmpq %rdx, %r10                             # compara freeSpace com null(0)
    jg end_while                                # se ja tiver achado sai do loop

    movq $0, %rdx                               # %rdx <- 0
    cmpq %rdx, (%r9)                            # compara *(int*)iterator com 0
    jg else_free_if                             # se for maior que 0 (1) vai para o fim deste if

    addq $8, %r9                                # iterator <- iteator + 8

    cmpq (%r9), %rdi                            # compara num_bytes com *(int*)iterator
    jg else_bytes_if                            # se for maior vai para o fim deste if
    
    addq $8, %r9                                # iterator <- iterator + 8
    movq %r9, -24(%rbp)                         # freeSpace <- iterator
    jmp exit_if
else_bytes_if:
    addq $8, %r9                                # iterator <- iterator + 8
    jmp exit_if                                 # sai da execução do if (para não pegar o else_free_if)
else_free_if:
    addq $16, %r9                               # iterator <- iterator + 16
exit_if:
    movq %r9, %rdx                              # %rdx <- iterador
    subq $8, %rdx                               # %rdx <- iterator - 8
    addq (%rdx), %r9                            # %r9 <- iterator + *(int*)iterator
    movq %r9, -16(%rbp)                         # iterator <- %r9
    jmp while                                   # volta para o inicio do while
end_while:
    movq -24(%rbp), %r10                        # %r10 <- freeSpace
    movq $0, %rdx                               # %rdx <- 0
    cmpq %r10, %rdx                             # compara freeSpace com null (0)
    jne else_alloc_if

    pushq %rdi                                  # salvando o valor de %rdi (num_bytes)
    
    movq $12, %rax                              # %rax <- 12 (syscall brk)
    movq $0, %rdi                               # %rdi <- 0 (parametro)
    syscall  
    movq %rax, -8(%rbp)                         # temp <- topo alocado da heap

    popq %rdi                                   # recuperando o valor de %rdi (num_bytes)

    movq HEAP_END, %rdx                         # %rdx <- final da heap
    movq -8(%rbp), %r8                          # %r8 <- temp
    subq %rdx, %r8                              # %r8 <- temp - heapEnd
    movq %r8, -32(%rbp)                         # diff <- %r8

    movq -8(%rbp), %r8                          # %r8 <- temp
    movq -32(%rbp), %rcx                        # %rcx <- diff

    movq %rdi, %rdx                             # %rdx <- numBytes
    addq $16, %rdx                              # %rdx <- %rdx + 16
    cmpq %rdx, %rcx                             # compara num_bytes (%rdx + 16) com diff (%rcx)
    jge exit_inside_alloc_if                    # sai do if interno

    movq $0, %rdx                               # %rdx <- 0
    movq %rdi, %rax                             # %rax <- num_bytes
    movq $4096, %rcx                            # %rcx <- 4096
    div %rcx                                    # %rax <- %rax / 4096
    addq $1, %rax                               # %rax <- %rax + 1
    imul $4096, %rax                            # %rax <- %rax * 4096

    pushq %rdi                                  # salvando o valor de %rdi (num_bytes)
    
    addq -8(%rbp), %rax                         # %rax <- %rax + topo atual da heap (temp)
    movq %rax, %rdi                             # %rdi <- %rax
    movq $12, %rax                              # %rax <- 12 (syscall brk)
    syscall                                     # chamada do sistema para o brk

    popq %rdi                                   # recuperando o valor de %rdi (num_bytes)
exit_inside_alloc_if:
    movq HEAP_END, %r8                          # %r8 <- fim da heap
    movq %r8, -8(%rbp)                          # temp <- fim da heap

    movq $1, (%r8)                              # *(int*)temp <- 1
    addq $8, %r8                                # temp <- temp + 8
    movq %rdi, (%r8)                            # *(int*)temp <- num_bytes
    addq $8, %r8                                # temp <- temp + 8

    movq %r8, -8(%rbp)                          # atualiza o valor da variavel local
    addq %rdi, %r8                              # %r8 <- %r8 + num_bytes
    movq %r8, HEAP_END                          # topo atual da heap é atualizado

    movq -24(%rbp), %r10                        # %r10 <- freeSpace
    movq HEAP_END, %r10                         # freeSpace <- heap_end
    movq %r10, -24(%rbp)                        # atualiza a variavel local

    movq $0, (%r10)                             # *(int*)freeSpace <- 0;
    addq $8, %r10                               # freeSpace <- freeSpace + 8

    pushq %rdi                                  # salvando o valor de %rdi (num_bytes)

    movq $12, %rax                              # %rax <- 12 (syscall brk)
    movq $0, %rdi                               # %rdi <- 0 (parametro)
    syscall                                     # chamada do sistema para o brk

    popq %rdi                                   # recuperando o valor de %rdi (num_bytes)

    movq %rax, %rdx                             # %rdx <- topo alocado da heap
    movq HEAP_END, %rcx                         # %rcx <- heap_end
    addq $16, %rcx                              # %rcx <- %rcx + 16
    subq %rcx, %rdx                             # %rcx <- sbrk(0) - %rcx    

    movq %rdx, (%r10)                           # *(int*)freeSpace <- %rcx
    jmp exit_aloc_if                            # sai do if
else_alloc_if:
    movq -24(%rbp), %r10                        # %r11 <- freeSpace
    subq $16, %r10                              # freeSpace(r11) <- freeSpace - 16
    movq $1, (%r10)                             # *(int*)freeSpace <- 1
    addq $16, %r10                              # freeSpace(r11) <- freeSpace + 16
    movq %r10, -24(%rbp)                        # atualiza a variavel local
    movq %r10, -8(%rbp)                         # temp <- freeSpace
exit_aloc_if:
    movq -8(%rbp), %rax                         # coloca temp como retorno da função
# --------------------------------------------- restauração do registro de ativação
    addq $32, %rsp                              # restauradno o espaço das 3 variaveis locais
    popq %rbp                                   #
    ret   


# -8(%rbp) = void *iterator = %r8
# -16(%rbp) = int free = %r9
# -24(%rbp) = int size = %r10
# -32(%rbp) = int count = %r11
imprimeMapa:
# --------------------------------------------- registro de ativação
    pushq %rbp                                  #
    movq %rsp, %rbp                             #
    subq $32, %rsp                              # requisitando espaço para 4 variaveis locais
# ---------------------------------------------
    movq HEAP_START, %r8                        # %r8 <- topo inicial da heap
    movq %r8, -8(%rbp)                          # iterator <- topo inicial da heap
print_while:
    movq $0, -32(%rbp)                          # count <- 0

    movq $12, %rax                              # chamada para brk
    movq $0, %rdi                               # %rdi <- 0 (parametro)
    syscall                                     # chamada do sistema para o brk

    movq %rax, %rcx                             # %rcx <- sbrk(0)
    movq -8(%rbp), %r8                          # %r8 <- iterator

    cmpq %rcx, %r8                              # compara iterador com sbrk(0)
    jge end_print_while                         # se for maior, sai do while do print

    movq $0, %rdx                               # %rdx <- 0
    cmpq %rdx, (%r8)                            # compara *(int*)iterator com 0
    jg else_print_free_if                       # se for diferente cai no falso
    movq $1, -16(%rbp)                          # free recebe 1
    jmp exit_print_free_if                      # sai do if
else_print_free_if:
    movq $0, -16(%rbp)                          # free recebe 0
exit_print_free_if:
    movq $HEADER_STRING, %rdi                   # primeiro parametro do printf
    call printf                                 # print do header

    movq -8(%rbp), %r8                          # %r8 <- iterator

    addq $8, %r8                                # iterator <- iteator + 8
    movq (%r8), %r10                            # %r10 <- *(int*)iterator
    movq %r10, -24(%rbp)                        # size <- *(int*)iterator

    addq $8, %r8                                # iterator <- iteator + 8
    movq %r8, -8(%rbp)                          # salva o valor do iterador
print_for:
    movq -32(%rbp), %r11                        # %r11 <- count
    movq -24(%rbp), %r10                        # rcx <- size
    cmpq %r10, %r11                             # compara count com size
    jge end_print_for                           # se >= sai do for

    movq -16(%rbp), %r9                         # %r9 <- free
    movq $1, %rcx                               # rcx <- $1
    cmpq %r9, %rcx                              # compara free com 1
    je else_char_select                         # se for igual pula pro else
    movq $OCCUPED_CHAR, %rdi                    # coloca o '+' como parametro do printf
    jmp exit_char_select                        # sai do if
else_char_select:
    movq $FREE_CHAR, %rdi                       # coloca o '-' como parametro do print
exit_char_select:
    call printf                                 # chama o printf

    movq -32(%rbp), %r11                        # %r11 <- count
    addq $1, %r11                               # %r11 <- %r11 + 1
    movq %r11, -32(%rbp)                        # count <- %r11
    
    jmp print_for                               # volta pro for
end_print_for:
    movq -24(%rbp), %r10                        # %r10 <- size
    movq -8(%rbp), %r8                          # %r8 <- iterator
    
    addq %r10, %r8                              # iterator <- iteator + size
    movq %r8, -8(%rbp)                          # atualiza a variavel local
    jmp print_while                             # volta pro while
end_print_while:
    movq $STR, %rdi                             # primeiro parametro do print
    call printf                                 # chama o printf
# --------------------------------------------- restauração do registro de ativação
    addq $32, %rsp                              # restauradno o espaço para 4 variaveis locais
    popq %rbp                                   #
    ret                                         #
