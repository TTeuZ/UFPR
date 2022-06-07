// lembrar de separar depois
#ifndef BICYCLE_F
#define BICYCLE_F
typedef struct bicycle_logs {
    char *date;
    float distance;
    float average_speed;
    float max_speed;
    int avarage_ht;
    int max_hr;
    int avarage_cadence;
    int accumulated_ascent;
} bicycle_log_f;
typedef struct bicycle {
    char *name;
    int activities_qtd;
    float total_km;
    float longest_ride;
    float shorter_ride;
    float avarage_distance;
    bicycle_log_f *logs;
} bicycle_f;

// função para iniciar uma bibicleta
// função para modificar/adicionar valores a uma bicicleta
// função para pegar um histograma da bicicleta
// função para limpar as bicicletas
#endif