# CSP Solver
Este trabalho visou implementar um solver simples para *Constraint Satisfaction Problems*. A solução dos CSPs é dada por um *backtracking* ingênuo (sem otimização) que percorre as variáveis, e seus domínios, do problema de forma recursiva em busca de uma solução que atenda todas as restrições.

```!
OBS: Esta implementação não busca a solução ótima, mas sim a primeira solução possível que pode ser encontrada.
```

## Ferramentas/Técnicas utilizadas
O algoritmo foi desenvolvido em python utilizando uma versão **recursiva** do algoritmo de *backtracking*.

A escolha de construir de maneira recursiva foi dada para evitar a cópia e alteração de vetores de domínio durante as iterações, buscando uma melhor performance do algoritmo e também possibilitando um uso mais efetivo de bibliotecas como numpy, a qual não lida muito bem com alteração dinâmica de tamanho de vetores.

### Executáveis
Dentro da pasta do projeto temos 2 executáveis principais:

- main.py: script principal de execução do CSP Solver;
- DIMACS_to_CSP.py: script de tradução de instancias CNF em formato DIMACS para o formato de entrada requerido pelo CSP Solver.

A execução destes 2 algoritmos será comentada posteriormente.

## Como executar
Para executar o algoritmo basta rodar o comando

```python
python3 main.py -p <caminho_do_arquivo_de_entrada>
```

Por se tratar de uma linguagem não compilada, não é necessário nenhum passo de compilação que necessitaria de um makefile por exemplo.

### Execução com arquivos CNF em formato DIMACS
Para resolver arquivos CNF primeiramente é necessário traduzi-lo para o formato de entrada do CSP Solver. Logo, 2 passos são necessários.

Primeiro rode o comando

```python
python3 DIMACS_to_CSP.py -p <caminho_para_o_arquivo_cnf>
```

Ao executar este script, um arquivo **results.txt** será gerado contendo a tradução do CNF para csp. Logo, basta executar o CSP Solver enviando este arquivo como entrada.

```python
python3 main.py -p results.txt
```

### Executando com o mundo de wumpus
Para executar este solver no mundo de wumpus é necessário apenas modificar a função ASK do arquivo bc.c

Como o mundo de wumpus constroi arquivos em formato DIMACS a cada passo, é necessário traduzi-los e enviá los para o nosso solver, logo os seguintes passos devem ser seguidos:

- Crie uma pasta chamada csp_solver (ou seu nome de preferência) na raiz do código do mundo de wumpus;
- Copie os scripts main.py, DIMACS_to_CSP.py e a pasta tools do código deste csp solver para dentro desta pasta;
- Faça a seguinte alteração na função ASK do arquivo bc.c para que fique como mostrado abaixo.

```C
// devolve 1 se clausula alfa é consequência lógica da BC
int ASK(Clausula alfa, BaseCon *BC) {
  // BC |= alfa sse BC => alfa é válida, i.e., ~BC v alfa é válida
  // Ou ainda, ~(~BC v alfa) não é sat, i.e., BC ^ ~alfa não é sat
  // (prova por redução ao absurdo)

  // cria arquivo de entrada para o SAT solver
  FILE *f = fopen(ARQ_IN, "w+");
  fprintf(f, "p cnf %u %u\n", BC->n_vars, BC->n_claus + 1);
  for (int i = 0; i < BC->n_claus; ++i) {
    for (int j = 0; j < BC->clausulas[i].n_lit; ++j) fprintf(f, "%d ", BC->clausulas[i].literais[j]);
    fprintf(f, "0\n");
  }
  // ~(alfa1 v ... v alfak) <=> (~alfa1) ^ ... ^ (~alfak)
  for (int j = 0; j < alfa.n_lit; ++j) fprintf(f, "%d 0\n", -alfa.literais[j]);
  fclose(f);

  char conversor[100];
  sprintf(conversor, "%s -p %s", "python3 csp_solver/DIMACS_to_CSP.py", "tmp.cnf");
  if (system(conversor) == -1) {
    printf("ERRO ao executar SAT Solver com comando %s\n", conversor);
    exit(-1);
  }

  char csp_solver[200];
  sprintf(csp_solver, "%s -p %s > %s", "python3 csp_solver/main.py", "results.txt", "tmp.out");
  if (system(csp_solver) == -1) {
    printf("ERRO ao executar SAT Solver com comando %s\n", csp_solver);
    exit(-1);
  }

  f = fopen("tmp.out", "r");
  char res[30];
  fscanf(f, "%s", res);
  fclose(f);

  return strcmp(res, "INVIAVEL") == 0 ? 1 : 0;
}
```

```!
OBS: Note que no caminho de chamada do tradutor e do solver é indicado a pasta csp_solver. Caso você decida por chamar a pasta de outra maneira, lembre-se de alterar o caminho indicado nesta função.
```

Com estas alterações será possível utilizar este algoritmo na solução dos problemas do mundo de wumpus!

```!
OBS: Como esta implementação é deveras mais lenta que o solver minisat, o delay do print na tela torna-se basicamente desnecessário, podendo ser removido.
```

## Exemplos de Entrada/Saída
Dentro da pasta examples é possível encontrar alguns exemplos de entrada, e na pasta DIMACS é possível encontrar exemplos de arquivos CNF para tradução.

Executando um exemplo do solver temos:

```python
python3 main.py -p examples/example1.txt

# Saída
x1 = 1
x2 = 2
x3 = 3
x4 = 1
x5 = 2
x6 = 1
x7 = 1
```
