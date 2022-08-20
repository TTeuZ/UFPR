#include "parser.h"

parser_t *init_parser () {
    parser_t *parser;

    if ((parser = malloc (sizeof (parser_t)))) {
        parser->input = NULL;
        parser->output = NULL;
        parser->n = -1;
        parser->iterations = -1;
        return parser;
    } else return NULL;
}

int parse_input (parser_t *parser, int argc, char *argv[]) {
    int parameter;
    opterr = 0;

    while ((parameter = getopt (argc, argv, "e:s:i:r:")) != -1) {
        switch (parameter) {
            case 'e': {
                parser->input = optarg;
                break;
            }
            case 's': {
                parser->output = optarg;
                break;
            }
            case 'r': {
                parser->n = atoi (optarg);
                break;
            }
            case 'i': {
                parser->iterations = atoi (optarg);
                break;
            }
            case '?': {
                if (optopt == 'r' && optarg == NULL) 
                    return MISSING_REQUIRED_ARG_ERROR;
                break;
            }
        }
    }
    if (parser->iterations == -1) 
        return MISSING_REQUIRED_ARG_ERROR;
    return EXIT_SUCCESS;
}
