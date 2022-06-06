#define RED "\e[0;31m"
#define GREEN "\e[0;32m"
#define YELLOW "\e[1;33m"
#define NC "\e[0m"

#ifndef IMAGE_F
#define IMAGE_F 
typedef struct image {
    char type[3];
    int width;
    int height;
    int max_value;
    unsigned char *data;
} image_f;
#endif

#ifndef PARAMS_F
#define PARAMS_F
typedef struct paramns {
    int input;
    int output;
    float ex_param;
} params_f;
#endif