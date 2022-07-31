#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include <allegro5/allegro5.h>
#include "../../constants.h"

/*!
    \brief Função de inicialização do display da Alegro
    \param display Ponteiro de acesso para a estrutura de display da Allegro
    \return 0 em caso de sucesso 1 em caso de falha
*/
int create_display (ALLEGRO_DISPLAY **display);

#endif