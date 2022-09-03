# Reprodução do jogo BALLZ com Allegro 5 em C

Feito por: Paulo Mateus Luza Alves

### Estrutura de pastas e Organização do Código

```shell
├── README.md
├── ballz.c
├── makefile
├── resources
│   ├── audios
│   ├── data
│   ├── fonts
│   └── images
└── src
    ├── constants.h
    ├── functions
    │   ├── cheatCodes
    │   ├── conditions
    │   ├── display
    │   ├── error
    │   ├── keyboard
    │   └── mouse
    ├── game
    │   ├── aim
    │   ├── collision
    │   ├── logic
    │   ├── pages
    │   ├── player
    │   ├── shop
    │   ├── speeder
    │   └── withdraw
    ├── loadables
    │   ├── audio
    │   ├── fonts
    │   └── images
    └── objects
        ├── addBall
        ├── ball
        ├── coin
        ├── index
        └── square
```

##### `src`

Aqui temos o código fonte do jogo, separado em `functions`, `game`, `loadables`, `objects` onde dentro de cada subpasta temos os .c e o .h equivalentes.

##### `resources`

Aqui temos os audios, imagens e fontes, separados em suas respectivas pastas `audios`, `fontes`, `images`.
Além disso, temos a pasta data, onde as informações do jogo são salvas. Nela temos 3 arquivos sendo eles:

- shop.txt -> Armazena o estado da loja do jogo;
- playerPoints.txt -> Armazena a pontuação atual, a quantidade de moedas e o record do jogador;
- game.txt -> Armazena a quantidade de bolinhas no jogo, posição inicial na bolinha e o mapa do jogo.

##### Executável

O executável do jogo se chama ballz.c e se encontra na raiz do projeto (fora da pasta src), juntamente com o makefile. Para compilar o jogo basta rodar o comando `make` e para jogar o comando `./ballz`.

OBS: É necessário ter o Allegro instalado em sua maquina e o jogo roda apenas em Linux (WSL não possui renderização gráfica, logo, não consegue executar o jogo).

### Funcionalidades 'Extras'

#### Estados do jogo salvos em memória:

Os seguintes estados de jogo são salvos em memória, e podem ser carregados ao entrar no jogo novamente:

- Pontuação e Record;
- Moedas e bolinhas compradas;
- Jogo atual em andamento (disposição do mapa, quantidade de bolinhas e posição inicial dela).

Desta maneira, ao entrar e sair do jogo, os estados importantes de execução ficam mantidos.

### Easter Eggs

#### Easter Egg do Yudi:

Dentro do jogo, enquanto as bolinhas não estiverem em lançamento, ao digitar "40028922" sem as aspas a sua quantidade de bolinhas irá dobrar.

#### Easter Egg da chuva:

Dentro do jogo, enquanto as bolinhas não estiverem em lançamento, ao clicar 7 vezes na bolinhas, ao inicial o proximo turno 7 bolinhas verdes 'irão' chover e serão adicionadas as suas bolinhas ao final do turno.
