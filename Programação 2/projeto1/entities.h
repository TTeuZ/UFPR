/*
* Struct que define a imagem recebida
*/
typedef struct image {
    char image_type[3];
    int row_size;
    int column_size;
    int max_value;
    unsigned char *image_data;
} image_f;

typedef struct paramns {
    int input;
    int output;
    float ex_param;
} paramns_f;