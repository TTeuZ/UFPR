#include <stdio.h>
#include <stdlib.h>
#include "eventos.h"

#define TAM_MUNDO 20000
#define RUMORES_MUNDO 30
#define PESSOAS_MUNDO 100
#define LOCAIS_MUNDO 8  
#define FIM_MUNDO 34944

/* Funções internas */
/* ------------------------------------------------------------------------------- */
/* funcao que gera um numero aleatorio entre dois limites */
int gerar_numeros_aleatorios (int min, int max) {
    return min + (rand() % max); 
}

/* cria o array de rumores e o retorna em rumores */
void cria_rumores_mundo (conjunto_t rumores[]) {
    int count;
    /* Cria uma seguencia ordenada de rumores com id = count (1 a 30) */
    for (count = 1; count <= RUMORES_MUNDO; count++) 
        insere_conjunto (rumores, count);
}

/* Cria todos os locais que vão ser usados na simulacao do mundo */
void cria_locais_mundo (local_m locais[]) {
    local_m local;
    int count;
    /* Gera os locaois do mundo */
    for (count = 1; count <= LOCAIS_MUNDO; count++) {
        local.id = count;
        local.lot_max = gerar_numeros_aleatorios (5, 30); /* gera uma lotação max */
        local.localizacao.x = gerar_numeros_aleatorios (0, TAM_MUNDO-1); /* gera a posicao no eixo x */
        local.localizacao.y = gerar_numeros_aleatorios (0, TAM_MUNDO-1); /* gera a posicao no eixo xy*/
        local.pessoas = cria_conjunto (local.lot_max); /* gera o conjunto de pessoas do local */
        local.fila = cria_fila (); /* gera a lista de espera */
        /* adiciona esse local no array */
        locais[count-1] = local;
    }
}

/* cria todas as pessoas que participaram da simulacao do mundo */
void cria_pessoas_mundo (pessoa_m pessoas[], conjunto_t rumores[], lef_t *eventos) {
    pessoa_m pessoa;
    int count;
    /* gera todas as pessoas do mundo */
    for (count = 1; count <= PESSOAS_MUNDO; count++) {
        pessoa.id = count;
        pessoa.extroversao = gerar_numeros_aleatorios (0, 100); /* gera o nivel de extroversao dela */
        pessoa.paciencia = gerar_numeros_aleatorios (0, 100); /* gera o nivel de passiencia dela */
        pessoa.idade = gerar_numeros_aleatorios (18, 101); /* gera a idade dela */
        pessoa.rumores = cria_subconjunto (rumores, gerar_numeros_aleatorios (1, 5)); /* gera o conjunto de rumores dela */
        /* insere a pessoa no array */
        pessoas[count-1] = pessoa;

        cria_evento_de_chegada (pessoa, eventos, gerar_numeros_aleatorios (0, 96*7));
    }
}
/* ------------------------------------------------------------------------------- */
/* Funções internas */

/* Funções de criacao */
/* ------------------------------------------------------------------------------- */
mundo_m cria_mundo (lef_t *eventos) {
    mundo_m mundo;
    mundo.tempo_atual = 0; /* seta o tempo inicial do mundo */
    mundo.n_pessoas = PESSOAS_MUNDO; /* seta o numero de pessoas do mundo */
    mundo.n_locais = LOCAIS_MUNDO; /* seta o numero de locais do mundo */
    mundo.tam_mundo.x = TAM_MUNDO; /* seta o tamanho max do eixo x do mundo */
    mundo.tam_mundo.y = TAM_MUNDO; /* seta o tamanho max do eixo y do mundo */

    mundo.rumores = cria_conjunto (RUMORES_MUNDO); /* cria o conjunto de rumores */
    cria_rumores_mundo (mundo.rumores); /* cria todos os rumores para a simulacao */
    cria_locais_mundo (mundo.locais); /* cria todos os locais para a simulacao */
    cria_pessoas_mundo (mundo.pessoas, mundo.rumores, eventos); /* cria todas as pessoas para a simulacao */

    cria_evento_de_fim (eventos);
    /* retorna o mundo criado para a main */
    return mundo;
}

/* função para criar eventos de chegada */
void cria_evento_de_chegada (pessoa_m pessoa, lef_t *eventos, int tempo) {
    evento_t evento; /* evento que vai ser inserido */
    dados_chegada_m chegada_pessoa; /* dados do evento */

    chegada_pessoa.id_pessoa = pessoa.id; /* id da pessoa que vai chegar */
    chegada_pessoa.id_local = gerar_numeros_aleatorios (1, LOCAIS_MUNDO); /* gera um local aleatorio */
    /* setando as informações do evento */
    evento.tempo = tempo;
    evento.tipo = 1;
    evento.tamanho = sizeof(dados_chegada_m);
    evento.dados = &chegada_pessoa;
    /* adicionando na LEF */
    adiciona_ordem_lef (eventos, &evento);
}

/* função para criar eventos de saida */
void cria_evento_de_saida (pessoa_m pessoa, local_m local, lef_t *eventos, int tempo) {
    evento_t evento; /* evento que vai ser inserido */
    dados_saida_m saida_pessoa; /* dados do evento */

    saida_pessoa.id_pessoa = pessoa.id; /* pessoa que ta saindo */
    saida_pessoa.id_local = local.id; /* local que ela esta saindo */
    /* setando as informações do evento */
    evento.tempo = tempo;
    evento.tipo = 2;
    evento.tamanho = sizeof(dados_saida_m);
    evento.dados = &saida_pessoa;
    /* adicionando na LEF */
    adiciona_ordem_lef (eventos, &evento);
}

/* função para criar eventos de disceminacao */
void cria_evento_de_disceminacao (pessoa_m pessoa, local_m local, lef_t *eventos, int tempo) {
    evento_t evento; /* evento que vai ser inserido */
    dados_disceminacao_m disceminacao_pessoa; /* dados do evento */
    conjunto_t *dis_rumores; /* conjunto de rumores que vamos tentar propagar */
    int nrd = pessoa.extroversao/10; /* quantidade de rumores */
    /* cria o subconjunto de rumores */
    dis_rumores = cria_subconjunto (pessoa.rumores, nrd);

    disceminacao_pessoa.id_pessoa_origem = pessoa.id; /* pessoa que ta disceminando */
    disceminacao_pessoa.id_local = local.id; /* local que ocorre */
    disceminacao_pessoa.cj_rumores = dis_rumores; /* conjunto de rumores que vao ser discemindados */
    /* setando as informações do evento */
    evento.tempo = tempo;
    evento.tipo = 3;
    evento.tamanho = sizeof(dados_disceminacao_m);
    evento.dados = &disceminacao_pessoa;
    /* adicionando na LEF */
    adiciona_ordem_lef (eventos, &evento);
} 

/* função para criar eventos de fim */
void cria_evento_de_fim (lef_t *eventos) {
    evento_t evento; /* evento que vai ser inserido */

    evento.tempo = 34944;
    evento.tipo = 4;
    evento.tamanho = 0;
    evento.dados = NULL;
    adiciona_ordem_lef (eventos, &evento);
}
/* ------------------------------------------------------------------------------- */
/* Funções de criacao */

/* Funções de execucao */
/* ------------------------------------------------------------------------------- */
void evento_chegada (mundo_m mundo, lef_t *eventos, int id_pessoa, int id_local) {
    local_m local = mundo.locais[id_local-1]; /* variavel para o local */
    pessoa_m pessoa = mundo.pessoas[id_pessoa-1]; /* variavel para a pessoa */
    int tpl; /* variavel para o tempo de permanencia */
    /* se o local estiver lotado, decide se vai para a fila ou se vai para outro lugar */
    if (cardinalidade (local.pessoas) == local.lot_max) {
        /* se a paciencia for suficiente, entra na fila */
        if ((pessoa.paciencia / 4 - tamanho_fila (local.fila)) > 0)
            insere_fila (local.fila, id_pessoa);
        /* caso não, cria um evento de saida da pessoa */
        else cria_evento_de_saida (pessoa, local, eventos, mundo.tempo_atual);
    } else { /* se o local não estiver lotado */
        insere_conjunto (local.pessoas, id_pessoa); /* adiciona a pessoa no conjunto de pessaos do lugar */
        tpl = 1 + (pessoa.paciencia/10+gerar_numeros_aleatorios (-2, 6)); /* calcula o tempo de permanencia */
        
        cria_evento_de_disceminacao (pessoa, local, eventos, mundo.tempo_atual+gerar_numeros_aleatorios (0, tpl));
        cria_evento_de_saida (pessoa, local, eventos, mundo.tempo_atual+tpl); /* cria o evento de saida da pessoa */
    }
}

void evento_fim (mundo_m mundo) {
    int count; /* contador para os for */
    /* libera todos os rumores das pessoas */
    for (count = 0; count < mundo.n_pessoas; count++) 
        destroi_conjunto (mundo.pessoas[count].rumores);
    /* libera as pessoas dos locais e as filas */
    for (count = 0; count < mundo.n_locais; count++) {
        destroi_conjunto (mundo.locais[count].pessoas);
        destroi_fila (mundo.locais[count].fila);
    }
    /* libera os rumores do mundo */
    destroi_conjunto (mundo.rumores);
}
/* ------------------------------------------------------------------------------- */
/* Funções de execucao */