#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../headers/utilities.h"


//? Stampa le indicazioni di utilizzo.
//? Per chiamare questa funzione passare come unico parametro il flag --help
void print_how_to_use(char* program_name) {

    printf(
            "\n > Usage: %s [%s %s] <value> [%s %s] <value> [%s %s] <value>",
            program_name,
            SD_ARG_ROWS, DD_ARG_ROWS,
            SD_ARG_COLUMNS, DD_ARG_COLUMNS,
            SD_ARG_THREADS, DD_ARG_THREADS
    );

    printf("\n\n      Mandatory arguments:");
    printf("\n        %s  %-20s Number of rows of the matrix", SD_ARG_ROWS, DD_ARG_ROWS);
    printf("\n        %s  %-20s Number of columns of the matrix", SD_ARG_COLUMNS, DD_ARG_COLUMNS);
    printf("\n        %s  %-20s Number of threads to use", SD_ARG_THREADS, DD_ARG_THREADS);

    printf("\n\n      Error codes:");
    printf("\n        %d %-20s Invalid number of arguments", ERR_ARGC, "ERR_ARGC");
    printf(
            "\n        %d %-20s Mandatory argument [%s %s] not provided",
            ERR_NO_ROWS, "ERR_NO_ROWS",
            SD_ARG_ROWS, DD_ARG_ROWS
    );
    printf(
            "\n        %d %-20s Mandatory argument [%s %s] not provided",
            ERR_NO_COLUMNS, "ERR_NO_COLUMNS",
            SD_ARG_COLUMNS, DD_ARG_COLUMNS
    );
    printf(
            "\n        %d %-20s Mandatory argument [%s %s] not provided",
            ERR_NO_THREADS, "ERR_NO_THREADS",
            SD_ARG_THREADS, DD_ARG_THREADS
    );
    printf("\n        %d %-20s Invalid number of rows provided", ERR_INVLD_ROWS, "ERR_INVLD_ROWS");
    printf("\n        %d %-20s Invalid number of columns provided", ERR_INVLD_COLUMNS, "ERR_INVLD_COLUMNS");
    printf("\n        %d %-20s Invalid number of threads provided", ERR_INVLD_THREADS, "ERR_INVLD_THREADS");
    printf("\n        %d %-20s Unable to allocate memory\n", ERR_MEMORY, "ERR_MEMORY");
    printf("\n        %d %-20s Unmanaged error\n", ERR_NOT_MANAGED, "ERR_NOT_MANAGED");

}


//? Esegue la verifica dei parametri passati da linea di comando
int get_params_code(int argc, char** argv) {

    if(argc == 2 && !strcmp(argv[1], DD_ARG_HELP))
        return SCC_HELP;

    if(argc == 7) {

        if(strcmp(argv[1], SD_ARG_ROWS) && strcmp(argv[1], DD_ARG_ROWS))
            return ERR_NO_ROWS;

        if(strcmp(argv[3], SD_ARG_COLUMNS) && strcmp(argv[3], DD_ARG_COLUMNS))
            return ERR_NO_COLUMNS;

        if(strcmp(argv[5], SD_ARG_THREADS) && strcmp(argv[5], DD_ARG_THREADS))
            return ERR_NO_THREADS;

        int rows = atoi(argv[2]);
        int columns = atoi(argv[4]);
        int threads = atoi(argv[6]);

        if(rows <= 0)
            return ERR_INVLD_ROWS;

        if(columns <= 0)
            return ERR_INVLD_COLUMNS;

        if(threads <= 0)
            return ERR_INVLD_THREADS;

        return SCC_ARGS;

    }

    return ERR_ARGC;

}


//? Stampa il messaggio di errore relativo ad un dato codice di errore
int check_params(int argc, char** argv) {
    switch(get_params_code(argc, argv)) {

        case SCC_HELP:
            print_how_to_use(argv[0]);
            return SCC_HELP;

        case ERR_ARGC:
            printf("\n <!> ERROR: Invalid number of arguments! For additional info type %s.\n", DD_ARG_HELP);
            return ERR_ARGC;

        case ERR_NO_ROWS:
            printf(
                    "\n <!> ERROR: Expected [%s %s] argument! For additional info type %s.\n",
                    SD_ARG_ROWS, DD_ARG_ROWS, DD_ARG_HELP
            );
            return ERR_NO_ROWS;

        case ERR_NO_COLUMNS:
            printf(
                    "\n <!> ERROR: Expected [%s %s] argument! For additional info type %s.\n",
                    SD_ARG_COLUMNS, DD_ARG_COLUMNS, DD_ARG_HELP
            );
            return ERR_NO_COLUMNS;

        case ERR_NO_THREADS:
            printf(
                    "\n <!> ERROR: Expected [%s %s] argument! For additional info type %s.\n",
                    SD_ARG_THREADS, DD_ARG_THREADS, DD_ARG_HELP
            );
            return ERR_NO_THREADS;

        case ERR_INVLD_ROWS:
            printf("\n <!> ERROR: Invalid value for argument [%s %s]! For additional info type %s.\n",
                   SD_ARG_ROWS, DD_ARG_ROWS, DD_ARG_HELP
            );
            return ERR_INVLD_ROWS;

        case ERR_INVLD_COLUMNS:
            printf("\n <!> ERROR: Invalid value for argument [%s %s]! For additional info type %s.\n",
                   SD_ARG_COLUMNS, DD_ARG_COLUMNS, DD_ARG_HELP
            );
            return ERR_INVLD_COLUMNS;

        case ERR_INVLD_THREADS:
            printf("\n <!> ERROR: Invalid value for argument [%s %s]! For additional info type %s.\n",
                   SD_ARG_THREADS, DD_ARG_THREADS, DD_ARG_HELP
            );
            return ERR_INVLD_THREADS;
        default:
            return SCC_ARGS;
    }
}
