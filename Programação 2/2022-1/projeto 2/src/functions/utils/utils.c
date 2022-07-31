#include "utils.h"

void emit_error (int error_code) {
    switch (error_code) {
        case INIT_ERROR:
            fprintf (stderr, RED "[ERROR] " NC "Falha na inicialização da Allegro!\n\n");
        break;
    }
}