# InversaoDeMatriz

## Autores

Nome: Paulo Mateus Luza Alves GRR: GRR20203945
Nome: Vinícius Mioto GRR: GRR20203931

## Estruturas

```c
matrix_t;
```

- `coef`: Ponteiro duplo de doubles que armazenam os **coeficientes da matriz**;
- `n`: Inteiro que representa o **tamanho da matriz** (_n_ x _n_).

```c
parser_t;
```

- `input`: String para o nome do **arquivo de input** enviado pelo usuário (Opcional);
- `output`: String para o nome do **arquivo de output** enviado pelo usuário (Opcional);
- `n`: Inteiro que representa o **tamanho da matriz** (_n_ x _n_) para geração de matriz aleatória;
- `iterations`: Inteiro que representa o **número de iterações** do processo de refinamento.

```c
 steps_t;
```

- `line`: Inteiro que representa a **linha que vai ser trocada**;
- `pivot`: Inteiro que representa o **pivô da troca**.

```c
 pivot_steps_t;
```

- `list`: Ponteiro duplo de steps_t, **lista de trocas** de linhas efetuadas;
- `qtd`: Inteiro que representa a **quantidade de trocas** de linhas que foram realizadas.

## Códigos de erro

**MISSING_REQUIRED_ARG_ERROR**:

- Valor: -1;
- Descrição: Erro de falta de paramêtro obrigatório.

**ALLOC_ERROR**:

- Valor: -2;
- Descrição: Erro de de alocação de memória.

**FILE_ERROR**:

- Valor: -3;
- Descrição: Erro de abertura de arquivo.

**NAN_INF_ERROR**:

- Valor: -4;
- Descrição: Erro de geração de NaN ou Inf no cálculo da inversa.

**INVERTABLE_ERROR**:

- Valor: -5;
- Descrição: Erro de impossibilidade de inversão da matriz enviada.

## Processo de cálculo da inversa

- _Entre as linhas 18 - 26_:
  Realização da leitura da linha de comando, armazenando as informações enviadas pelo usuário nas estruturas indicadas.

- _Entre as linhas 29 - 39_:
  Verificação das paramêtros enviados pelo usuário, indicando qual é a fonte da matriz que vai ser invertida, sendo possivel as seguintes opções: - `Randômica`: Gerada **aleatoriamente** a partir do paramentro N enviado; - `Input por terminal`: Lida por input do usuário diretamente do **terminal**; - `Input por arquivo`: Lida a partir de um **arquivo enviado** pelo usuário.

- _Entre as linhas 42 - 51_:
  Alocação de memória para as matrizes que vão ser utilizadas na resolução do inversa: - `Matriz U`; - `Matriz L`; - `Matriz Inversa`.

Alocação de memória para o vetor das normas calculadas, e execução de uma copia da matriz de input na matriz U.

- _Entre as linhas 53 - 57_:
  Alocação de memoria para a estrutura de armazenamento dos passos de pivotamento executados na fatoração LU.

- _Entre as linhas 60 - 64_:
  Execução da fatoração LU, resultando na criação da matriz U e L.

- _Entre as linhas 66 - 70_:
  Execução do refinamento, resultando na matriz inversa calculada.

## Funções

#### error.h

```c
void emit_error (int error_code, parser_t *parser, double *norma_vet, matrix_t *input_matrix, matrix_t *l_matrix, matrix_t *u_matrix, matrix_t *inv_matrix, pivot_steps_t *pivot_steps);
```

**Funcionalidade**: Função que executa a limpeza das estruturas alocadas e print de erro na stderr em caso de erro. Os erros abrangidos são:

- **ALLOC_ERROR;**
- **NAN_INF_ERROR;**
- **INVERTABLE_ERROR.**

**Parâmetros:**

- _error_code_: Código de erro;
- _parser_: Ponteiro para o parser;
- _norma_vet_: Ponteiro para o vetor das normas;
- _input_matrix_: Ponteiro para a matriz de entrada;
- _inv_matrix_: Ponteiro para a matriz inversa;
- _l_matrix_: Ponteiro para a matriz L;
- _u_matrix_: Ponteiro para a matriz U;
- _pivot_steps_: Ponteiro para o vetor de passos do pivotamento.

#### matrix.h

```c
matrix_t *alloc_matrix (unsigned int n);
```

**Funcionalidade:** Função de alocação de memória para uma matriz.

**Parâmetros:**

- _n_: Tamanho da Matriz.

**Retorno:**

- Sucesso: Ponteiro de acesso para a Matriz;
- Erro: Null.

```c

void free_matrix (matrix_t *matrix);
```

**Funcionalidade:** Função de limpeza de memória para uma matriz.

**Parâmetros:**

- _matrix_: Ponteiro para uma Matriz.

```c
void copy_matrix (matrix_t *font, matrix_t *target);
```

**Funcionalidade:** Função que copia os valores de uma matriz (fonte) para outra (destino).

**Parâmetros:**

- _Font_: Ponteiro para a matriz que vai ser copiada;
- _Target_: Ponteiro para a matriz que vai receber a copia.

```c
void random_matrix (matrix_t *matrix, double coef_max);
```

**Funcionalidade:** Gera uma matriz com valores aleatórios para os coeficientes.

**Parâmetros:**

- _matrix_: Ponteiro para a matriz que vai ser gerada;
- _coef_max_: Valor maximo para cada coeficiente que vai ser gerado.

```c
void generate_identity_matrix (matrix_t *matrix);
```

**Funcionalidade:** Gera uma matriz identidade.

**Parâmetros:**

- _matrix_: Ponteiro para a matriz que vai ser preenchida com a identidade.

```c
matrix_t* read_from_file (parser_t *parser);
```

**Funcionalidade:** Realiza a leitura de uma matriz a partir de um arquivo.

**Parâmetros:**

- _parser_: Ponteiro para a estrutura de dados do parser, que contém as informações enviadas pela linha de comando.

**Retorno:**

- Sucesso: Ponteiro de acesso para a Matriz;
- Erro: Null.

```c
matrix_t* read_from_terminal ();
```

**Funcionalidade:** Realiza a leitura de uma matriz a partir da entrada pelo terminal (usuário).

**Retorno:**

- Sucesso: Ponteiro de acesso para a Matriz;
- Erro: Null.

```c
int print_result (matrix_t *inv_matrix, double *norma_vet, double lu_time, double iter_time, double residue_time, parser_t *parser);
```

**Funcionalidade:** Imprime o resultado da matriz inversa.

**Parâmetros:**

- _inv_matrix_: Ponteiro para a matriz inversa (Retorno);
- _norma_vet_: Ponteiro para o vetor com as normas calculadas;
- _lu_time_: Tempo para a fatoração LU;
- _iter_time_: Tempo médio para calculas as retrosubstituições;
- _residue_time_: Tempo médio para cálculo do resíduo;
- _parser_: Ponteiro para o parser;

**Retorno:**

- Sucesso: 0;
- Erro: **FILE_ERROR**.

#### methods.h

```c
int lu_factorization (matrix_t *u_matrix, matrix_t *l_matrix, pivot_steps_t *pivot_steps, double *lu_time);
```

**Funcionalidade:** Função que realiza a fatorização LU da matriz. A matriz um inicia-se contendo os valores de input do usuário. Ao final da execução temos em u_matrix a matriz U e em l_matrix a matriz L.

**Parâmetros:**

- _u_matrix_: Matriz enviada pelo usuário (Retorno);
- _l_matrix_: Ponteiro para a matriz L (Retorno);
- _lu_time_ : Tempo levado para executar a Fatoração LU (Retorno).

**Retorno:**

- Sucesso: 0;
- Erro: **NAN_INF_ERROR** ou **INVERTIBLE_ERROR**.

```c
int matrix_refinement (matrix_t *inv_matrix, matrix_t *matrix, matrix_t *l_matrix, matrix_t *u_matrix, pivot_steps_t *steps, double *norma_vet, int iterations, double *iter_time, double *residue_time);
```

**Funcionalidade:** Função que realiza o refinamento da solução obtida pela fatorização LU. O retorno é enviado no parãmetro inv_mat.

**Parâmetros:**

- _input_matrix_: Matriz enviada pelo usuário;
- _l_matrix_: Ponteiro para a matriz L;
- _u_matrix_: Ponteiro para a matriz U;
- _inv_matrix_: Ponteiro para a matriz inversa (Retorno);
- _iterations_ Número: de iterações fornecido pelo usuário;
- _iter_time_: Tempo médio levado para executar a os passos do refinamento (Retorno);
- _residue_time_: Tempo médio levado para calcular o residuo;
- _norma_vet_: Vetor de armazenamento das normas calculadas.

**Retorno:**

- Sucesso: 0;
- Erro: **NAN_INF_ERROR** ou **ALLOC_ERROR**.

```c
int find_max (matrix_t *matrix, int line);
```

**Funcionalidade:** Função que encontra o valor maximo da coluna.

**Parâmetros:**

- _matrix_: Matriz para a iteração;
- _line_: linha atual da Eliminação de Gauss.

**Retorno:**
Linha onde esta o pivo de maior valor.

```c
void swap_line (matrix_t *matrix, int line, int pivot);
```

**Funcionalidade:** Função que realiza a troca de linhas entre a linha _line_ e a linha _pivot_

**Parâmetros:**

- _matrix_: Matriz para a iteração;
- _line_: linha que será trocada;
- _pivot_: Linha pivo (possui o pivo de maior valor).

```c
int add_pivot_step (pivot_steps_t *pivot_steps, int line, int pivot);
```

**Funcionalidade:** Função que adiciona o passo de pivotamento executado na Eliminação de Gauss na estrutura de armazenamento dos passos.

**Parâmetros:**

- _pivot_steps_: Ponteiro para ;
- _line_: linha que será trocada;
- _pivot_: Linha pivo (possui o pivo de maior valor).

**Retorno:**

- Sucesso: 0;
- Erro: **ALLOC_ERROR**.

```c

void apply_pivot_steps (matrix_t *matrix, pivot_steps_t *steps);
```

**Funcionalidade:** Função que aplica as etapas de pivotamento na Matriz indicada.

**Parâmetros:**

- _matrix_ Ponteiro para Matriz que será pivoteada;
- _steps_ Ponteiro para Passos que serão aplicados.

```c
double calc_determinant (matrix_t *matrix);
```

**Funcionalidade:** Função que calcula o valor do determinante da matriz.

**Parâmetros:**

- _matrix_ Ponteiro para Matriz de entrada.

**Retorno:**
Valor do determinante da matriz.

```c
int inv_retro_subs (matrix_t *l_matrix, matrix_t *i_matrix, double *solution, int ls_b);
```

**Funcionalidade:** Função que calcula os valores das incognitas do sistema linear formado por uma matriz Triangulo inferior. O valor de _ls_b_ nos indica a posição/coluna da matriz de termos independentes que vai ser utilizada na solução do sistema.

**Parâmetros:**

- _l_matrix_: Ponteiro para a matriz L resultande ta fatorização LU;
- _b_matrix_: Ponteiro para a matriz de termos independentes;
- _solution_: Ponteiro para o vetor com as soluções obtidas das incognitas;
- _ls_b_: Inteiro que indica qual coluna da matriz de termos independentes que vai ser utilizada para a solução do sistema linear.

**Retorno:**

- Sucesso: 0;
- Erro: **NAN_INF_ERROR**.

```c
int retro_subs (matrix_t *u_matrix, matrix_t *inv_matrix, matrix_t *solution, int ls_b);
```

**Funcionalidade:** Função que calcula os valores das incognitas do sistema linear formado por uma matriz Triangulo superior. O valor de _ls_b_ nos indica a posição/coluna da matriz de termos independentes que vai ser utilizada na solução do sistema.

**Parâmetros:**

- _u_matrix_: Ponteiro para a matriz U resultande ta fatorização LU;
- _inv_matrix_: Ponteiro para Matriz Inversa (Retorno);
- _solution_: matrix com a solução da retrosubstituição anterior;
- _ls_b_: Inteiro que indica qual coluna da matriz de termos independentes que vai ser utilizada para a solução do sistema linear.

**Retorno:**

- Sucesso: 0;
- Erro: **NAN_INF_ERROR**.

```c
void calc_residue (matrix_t *residue_matrix, matrix_t *matrix, matrix_t \*inv_matrix);
```

**Funcionalidade:** Função que calcula a matrix de residuos do resultado obtido na iteração da fatoração LU.

**Parâmetros:**

- _residue_matrix_: Ponteiro para a matriz de Residuos (Retorno);
- _matrix_: Ponteiro para Matriz enviada pelo usuário;
- _inv_matrix_: Ponteiro para a matriz inversa calculada.

```c
double calc_norma (matrix_t *residue_matrix, double *residue_time);
```

**Funcionalidade:** Função que calcula a norma L2 do residuo.

**Parâmetros:**

- _residue_matrix_: Ponteiro para a matriz de Residuos;
- _residue_time_: Tempo para calcular a norma do residuot.

**Retorno:**
Valor da norma.

#### parser.h

```c
parser_t *init_parser ();
```

**Funcionalidade:** Função de alocação/inicialização dos valores do parser.

**Retorno:**

- Sucesso: Ponteiro de acesso para a estrutura de dados parser;
- Erro: Null.

```c
/*!
    \brief Função parser da linha de comando
    varre os Parâmetros de entrada e armazena na estrutura de dados
    \param parser Estrutura de dados previamente alocadas
    \param arqc numero de argumentos da entrada
    \param arqv array com os argumentos da entrada
*/
int parse_input (parser_t *parser, int argc, char *argv[]);
```

**Funcionalidade:** Função parser da linha de comando. Recebe os parâmetros do usuário e os armazena na estrutura de dados indicada.

**Parâmetros:**

- _parser_: Estrutura de dados de armazenamento das informações do parser;
- _arqc_: Número de argumentos da entrada;
- _arqv_: Array com os argumentos da entrada;

**Retorno:**

- Sucesso: 0;
- Erro: **MISSING_REQUIRED_ARG_ERROR**.

#### steps.h

```c
pivot_steps_t *alloc_steps ();
```

**Funcionalidade:** Aloca espaço para a struct de passos de pivotamento.

**Retorno:**

- Sucesso: Ponteiro de acesso para a estrutura steps;
- Erro: Null.

```c
void free_steps (pivot_steps_t *steps);
```

**Funcionalidade:** Libera o espaço alocado para o pivot_steps.

**Parâmetros:**

- _steps_ Ponteiro de acesso para lista de passos;

#### utils.h

```c
#define ABS(num) ((num) < 0.0 ? -(num) : (num))

**Funcionalidade:** Define para um ABS funcional para floats.

double timestamp (void);
```

**Funcionalidade:** Função de geração de valor timestamp.

**Retorno:**
Valor Double do timestamp atual.
