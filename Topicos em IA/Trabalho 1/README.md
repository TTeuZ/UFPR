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
P(i, j) <=> B(i-1, j) v B(i+1, J) v B(i, j-1) v B(i, j+1)
```
Que se entende para:

Existe **poço** em P(i, j) se e somente se existe uma **brisa** nas 4 posições adijacentes (horizontal e vertical) ao poço.

## Arquivos
- wumpus.pl: Arquivo principal para exexutar o agente;
- search.pl: Arquivo que contem o algoritmo para executar a busca;
- kn.pl: Arquivo que contem a definição da Base de Conhecimento e predicados para seu uso;
- fill_up_kb.pl: Arquivo que contem os predicados para construção da Base de Conhecimento;
- utils.pl: Arquivo com predicados uteis como verificação de borda, dentre outros;
- sat.pl: SAT solver.

## Como executar

Dentro da pasta do projeto execute o comando swipl wumpus.pl

Ao entrar na interface do swi-prolog execute o predicado wumpus(N, Map), passando o tamanho e o seu mapa de preferencia.

```prolog
wumpus(4, [[0, 0, 0, 0], [1, 0, 0, 0], [2, 1, 0, 0], [1, 0, 0, 3]]).
```

```!
Para mapas de tamanho 7 acima esta levando um tempo consideravel para executar.
```

## Exemplo de entrada/saida

```prolog
?- wumpus(4, [[0, 0, 0, 0], [1, 0, 0, 0], [2, 1, 0, 0], [1, 0, 0, 3]]).
You won!
Path -> [0,0] -> [0,1] -> [0,2] -> [0,3] -> [1,3] -> [1,2] -> [2,2] -> [3,2] -> [3,3]
true .
```