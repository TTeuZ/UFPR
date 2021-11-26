#include "entidades.h"
#include "liblef.h"

/* 
* Funcao responsavel por inicializar tudo o que for necessario para
* a simulacao do mundo
*/
void cria_mundo (pessoa_m pessoas[], local_m locais[], conjunto_t rumores[], lef_t *eventos);

/*
* função relacionada ao evento de chegada de pessoa em um local
*/
void chegada (pessoa_m *pessoas, local_m *local);

/*
* função relacionada ao evento de saida de pessoa em um local
*/
void saida (pessoa_m *pessoas, local_m *local);

/*
* função relacionada a disseminacao de rumores por uma pessoa no local
*/
void disseminacao (pessoa_m *pessoas, local_m *local);

/*
* função relacionada ao evento de fim de mundo
*/
void fim ();