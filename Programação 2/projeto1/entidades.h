/*
* Struct que define a imagem recebida
*/
typedef struct image {
    int image_type;
    int row_size;
    int column_size;
    int max_value;
    unsigned char *image_data;
} image;

typedef struct paramns {
    int input;
    int output;
    float ex_param;
} paramns;