#ifndef __ERROR_H__
#define __ERROR_H__

#include <stdio.h>
#include <stdlib.h>

#include "../../constants.h"

/*!
    \brief Função de lançamento de erro.
    notifica algum erro na stderr
    \param error_code Código de erro, utilizado para a exibição da mensagem
*/
void emit_error (int error_code);

#endif