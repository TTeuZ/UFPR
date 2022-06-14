#ifndef BICYCLE
#define BICYCLE
typedef struct bicycle_log {
    char *bicycle_name;
    char *date;
    float distance;
    float average_speed;
    float max_speed;
    int average_hr;
    int max_hr;
    int average_cadence;
    float altimetry_gain;
} bicycle_log_f;
typedef struct bicycle {
    char *name;
    int activities_qtd;
    float total_km;
    float longest_ride;
    float shorter_ride;
    float average_distance;
    bicycle_log_f **logs;
} bicycle_f;

/*
* Função que aloca espaço para uma bicicleta e retorna seu ponteiro ed acesso
*/
bicycle_f *create_bicycle (char *name);

/*
* Função que recebe como parametros os valores do log e cria uma instancia de log
* retorna esta instancia
*/
bicycle_log_f *create_log (char *bicycle_name, char *date, float distance, float average_speed, float max_speed, int average_hr, int max_hr, int average_cadence, float altimetry_gain);

/*
* Função que adiciona um novo log para uma bicicleta
* Adição ocorre de forma ordenada pela data
*/
void add_bicycle_log (bicycle_f *bicycle, bicycle_log_f *log);

/*
* Função que recebea bicicleta e o ultimo log adicionado
* Trata as informação de resumo da biciclita, atualizando os valores necessários
*/
void treat_bicycle_resume (bicycle_f *bicycle, bicycle_log_f *log);

/*
* Limpa a estrutura de dados que armazena as informaçãos da bicicleta
* Passa por cada log de atividade da bicicleta limpando seu espaço ocupador
* Ao final, limpa toda a estrutura de armazenamento da bicicleta
*/
void clean_bicycle (bicycle_f *bicycle);

// função para pegar um histograma da bicicleta
#endif