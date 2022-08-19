#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ABS(num) ((num) < 0.0 ? -(num) : (num))

/*!
    \brief Função de geração de valor timestamp
    \return valor Double do timestamp atual
*/
double timestamp (void);
#endif
