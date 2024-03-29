#ifndef __CONSTANTS_H__
#define __CONSTANTS_H__

// Macro para ABS
#define ABS(num) ((num) < 0.0 ? -(num) : (num))

// Coloração de outputs
#define RED "\e[0;31m"
#define NC "\e[0m"

// Definições
#define FPS 1.0 / 60.0
#define STOP_EPSILON 0.5f

// RGB
#define WHITE 255, 255, 255
#define BLACK 0, 0, 0
#define DARK_GRAY 20, 20, 20
#define NORMAL_GRAY 32, 32, 32
#define LIGHT_GRAY 160, 160, 160
#define GRAY 32, 32, 32
#define GOLDEN 255, 178, 102
#define PINK 204, 0, 102
#define YELLOW 255, 185, 0
#define CIANO 32, 178, 170
#define BLUE 0, 102, 204
#define GREEN 0, 153, 76
#define LIGHT_GREEN 153, 255, 51

// Audio
#define AUDIO_QTD 2

#define CLICK_GAIN 3
#define CLICK_SPEED 12
#define HIT_GAIN 1
#define HIT_SPEED 1
#define BUY_GAIN 1
#define BUY_SPEED 1
#define COIN_GAIN 0.5
#define COIN_SPEED 1
#define BUBBLE_GAIN 2.5
#define BUBBLE_SPEED 1
#define LEVEL_GAIN 1.5
#define LEVEL_SPEED 1

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
#define SQUARE 23

// Randow
#define MAX_SQUARES 3

// Área de jogo (mapa)
#define MAP_COLS 7
#define MAP_LINES 9

#define SQUARE_SIZE 60
#define SQUARE_MARGIN 3

#define START_Y_AREA SQUARE_SIZE
#define END_Y_AREA (SQUARE_SIZE * 10)
#define START_X_AREA 0
#define END_X_AREA (SQUARE_SIZE * 7)

// Dimensões
#define BUFFER_HEIGHT (SQUARE_SIZE * 13)
#define BUFFER_WIDTH (SQUARE_SIZE * 7)
#define BUFFER_SCALE 1

#define DISPLAY_HEIGHT (BUFFER_HEIGHT * BUFFER_SCALE)
#define DISPLAY_WIDTH (BUFFER_WIDTH * BUFFER_SCALE)

// transcricao do mapa
#define ADD_BALL -1
#define COIN -2

// Bolinha
#define BALL_RADIUS 8
#define INITIAL_X_POSITION BUFFER_WIDTH / 2
#define INITIAL_Y_POSITION (SQUARE_SIZE * 10) - BALL_RADIUS
#define BALL_SPEED 14

// Add_ball
#define ADD_BALL_RADIUS 8
#define INITIAL_ARC_RADIUS 14
#define ARC_LIMIT 16

// Moeda
#define COIN_IN_GAME_RADIUS 12

// Mira
#define INITIAL_AIM_Y_POSITION INITIAL_Y_POSITION - 20
#define AIM_RADIUS 20
#define AIM_SIZE_LIMIT 125
#define AIM_QTD 16
#define AIM_LIMIT 8

// Timers
#define WITHDRAW_TIME 7
#define SPEEDER_TIME 240

// Bust
#define NONE_BUST 1
#define SPEEDER_BUST 2.5

// Animações
#define SPEEDER_ANIMATION 300
#define ADD_BALL_ARC_ANIMATION 5

// CheatCodes
#define YUDI_CHEAT_SIZE 8
#define RAIN_CHEAT_CLIKS_TO_ACTIVE 7

// Shop
#define ITEMS_SIZE 9
#define MAX_ITEM_LINE 3
#define MAX_ITEM_COL 3

// Erros
#define INIT_ERROR 0
#define READ_GAME_ERROR -1
#define READ_POINTS_ERROR -2
#define READ_SHOP_ERROR -3
#define SAVE_POINTS_ERROR -4
#define SAVE_GAME_ERROR -5
#define SAVE_SHOP_ERROR -6
#define GAME_OBJECTS_ERROR -7
#define ADD_BALL_ERROR -8
#define CHEAT_CODE_ERROR -9

#endif