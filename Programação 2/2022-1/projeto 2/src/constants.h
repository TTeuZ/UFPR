#ifndef __CONSTANTS_H__
#define __CONSTANTS_H__

// Coloração de outputs
#define RED "\e[0;31m"
#define NC "\e[0m"

// Definições
#define FPS 1.0 / 60.0

// Audio
#define AUDIO_QTD 2

// Dimensões
#define BUFFER_HEIGHT 780
#define BUFFER_WIDTH 420

#define BUFFER_SCALE 1
#define DISPLAY_HEIGHT (BUFFER_HEIGHT * BUFFER_SCALE)
#define DISPLAY_WIDTH (BUFFER_WIDTH * BUFFER_SCALE)

#define SQUARE_SIZE 60

// Erros
#define INIT_ERROR 0

#endif