#ifndef IMAGE_F
#define IMAGE_F 
typedef struct image {
    char image_type[3];
    int row_size;
    int column_size;
    int max_value;
    unsigned char *image_data;
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