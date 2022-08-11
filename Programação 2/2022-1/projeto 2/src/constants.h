#ifndef __CONSTANTS_H__
#define __CONSTANTS_H__

// Macro para ABS
#define ABS(num) ((num) < 0.0 ? -(num) : (num))

// Coloração de outputs
#define RED "\e[0;31m"
#define NC "\e[0m"

// RGB
#define WHITE 255, 255, 255
#define BLACK 0, 0, 0
#define DARK_GRAY 20, 20, 20
#define NORMAL_GRAY 32, 32, 32
#define LIGTH_GRAY 160, 160, 160
#define GRAY 32, 32, 32
#define GOLDEN 255, 178, 102
#define PINK 204, 0, 102
#define BLUE 0, 102, 204
#define GREEN 0, 153, 76
#define LIGHT_GREEN 153, 255, 51

// Definições
#define FPS 1.0 / 60.0
#define AIM_SIZE 16

// Audio
#define AUDIO_QTD 2

#define CLICK_GAIN 3
#define CLICK_SPEED 12

// Fontes
#define TITLE_H1 90
#define TITLE_H2 45
#define TEXT_HELP 20
#define TEXT_RECORD 15
#define BUTTON 25
#define POINTS 30
#define COINS 20
#define BALLS 16
#define SPEEDER 13

// Dimensões
#define SQUARE_SIZE 60
#define BALL_RADIUS 8
#define AIM_RADIUS 20

#define BUFFER_HEIGHT (SQUARE_SIZE * 12)
#define BUFFER_WIDTH (SQUARE_SIZE * 7)

#define BUFFER_SCALE 1
#define DISPLAY_HEIGHT (BUFFER_HEIGHT * BUFFER_SCALE)
#define DISPLAY_WIDTH (BUFFER_WIDTH * BUFFER_SCALE)

#define START_Y_AREA SQUARE_SIZE
#define END_Y_AREA (SQUARE_SIZE * 9)
#define START_X_AREA 0
#define END_X_AREA (SQUARE_SIZE * 7)

// Bolinha
#define INITIAL_X_POSITION BUFFER_WIDTH / 2
#define INITIAL_Y_POSITION (SQUARE_SIZE * 9) - BALL_RADIUS
#define BALL_SPEED 14

// Timers
#define WITHDRAW_TIME 5
#define SPEEDER_TIME 300

// Bust
#define NONE_BUST 1
#define SPEEDER_BUST 2

// Animações
#define SPEEDER_ANIMATION 300

// Erros
#define INIT_ERROR 0
#define READ_GAME_ERROR -1
#define SAVE_POINTS_ERROR -2
#define SAVE_GAME_ERROR -3
#define ADD_BALL_ERROR -4

#endif