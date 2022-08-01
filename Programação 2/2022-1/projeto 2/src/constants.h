#ifndef __CONSTANTS_H__
#define __CONSTANTS_H__

// Coloração de outputs
#define RED "\e[0;31m"
#define NC "\e[0m"

// Dimensões
#define BUFFER_HEIGHT 720
#define BUFFER_WIDTH 480

#define BUFFER_SCALE 1
#define DISPLAY_HEIGHT (BUFFER_HEIGHT * BUFFER_SCALE)
#define DISPLAY_WIDTH (BUFFER_WIDTH * BUFFER_SCALE)

// Erros
#define INIT_ERROR 0

#endif