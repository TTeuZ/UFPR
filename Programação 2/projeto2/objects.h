#ifndef BLOCK_S
#define BLOCK_S

typedef struct block {
    int height, widht;          // dimensões do bloco
    int x, y;                   // posicionamento do bloco
    char *sprite;
} block_t;
#endif

