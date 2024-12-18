# Mundo de Wumpus simplificado

Este trabalho visou implementar um agente inteligente em Prolog para caminhar no mundo de wumpus em busca do ouro.

```!
Esta é uma versão simplificada que possui apenas poços
```

## Ferramentas/Técnicas utilizadas
- Busca Backtracking exaustiva por todos os caminhos possiveis no mapa;
- Uma base de conhecimento em formato **CNF** contendo informaçoes do mundo (brisas encontradas conforme exploração);
- Algoritmo SAT para garantir que o agente fara apenas movimentos seguros, ou seja, que são garantidos que não encontraram poços.

Abaixo temos a preposição logica utilizada para a construção da Base de Conhecimento:
```prolog
B(i, j) <=> P(i-1, j) v P(i+1, J) v P(i, j-1) v P(i, j+1)
```
Que se entende para:

Existe uma **brisa** em B(i, j) se e somente se existe um **poço** em alguma das 4 posições adjacentes (horizontal e vertical) a brisa.

## Arquivos
- wumpus.pl: Arquivo principal para exexutar o agente;
- search.pl: Arquivo que contem o algoritmo para executar a busca;
- kn.pl: Arquivo que contem a definição da Base de Conhecimento e predicados para seu uso;
- fill_up_kb.pl: Arquivo que contem os predicados para o preenchimento da Base de Conhecimento;
- utils.pl: Arquivo com predicados uteis como verificação de borda, dentre outros;
- sat.pl: SAT solver.

## Como executar

Dentro da pasta do projeto execute o comando swipl wumpus.pl, ou, execute o swipl e internamente, no terminal dele, consulte o arquivo wumpus.pl (consult(wumpus)).

Ao entrar na interface do swi-prolog execute o predicado wumpus(N, Map), passando o tamanho e o seu mapa de preferencia.

Exemplo:
```prolog
wumpus(4, [[0, 0, 0, 0], [1, 0, 0, 0], [2, 1, 0, 0], [1, 0, 0, 3]]).
```

```!
Para mapas de tamanho 7 acima o programa leva um tempo consideravel para executar.
```

### Sobre a formatação do mapa

A maneira escolhida para enviar o mapa para o algoritmo seguiu o padrão ja conhecido

```prolog
[0 0 0]
[1 0 0] -> [[0, 0, 0], [1, 0, 0], [2, 1, 3]]
[2 1 3]
```

## Exemplo de entrada/saida

```prolog
?- wumpus(4, [[0, 0, 0, 0], [1, 0, 0, 0], [2, 1, 0, 0], [1, 0, 0, 3]]).
You won!
Path -> [0,0] -> [0,1] -> [0,2] -> [0,3] -> [1,3] -> [1,2] -> [2,2] -> [3,2] -> [3,3]
true .
```

### Comandos de exemplo

```prolog
wumpus(3, [[0, 0, 0], [1, 0, 0], [2, 1, 3]]).
wumpus(4, [[0, 0, 0, 0], [1, 0, 0, 0], [2, 1, 0, 0], [1, 0, 0, 3]]).
wumpus(7, [[0, 0, 0, 1, 0, 0, 0], [0, 0, 1, 2, 1, 0, 0], [1, 0, 0, 1, 0, 0, 1], [2, 1, 0, 0, 0, 1, 2], [1, 0, 0, 1, 0, 0, 1], [0, 1, 1, 2, 1, 0, 0], [1, 2, 1, 3, 0, 0, 0]]).
```