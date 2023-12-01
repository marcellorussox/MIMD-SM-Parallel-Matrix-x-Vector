#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <omp.h>
#include "data_structures.h"
#include "utilities.h"



int main(int argc, char** argv) {

    /*
        rows: Numero di righe della matrice;
        columns: Numero di colonne della matrice;
        threads: Numero di thread impiegati;

        matrix: Matrice da impiegare nel prodotto;
        vector: Vettore da impiegare nel prodotto;
        result: Vettore risultate dal prodotto tra matrix e vector

        time_start: Timestamp all'inizio del calcolo del prodotto;
        time_end: Timestamp al termine del calcolo del prodotto;
        overall_time: Tempo complessivo impiegato per effettuare il prodotto;
    */

    int rows;
    int columns;
    int threads;

    double** matrix;
    double* vector;
    double* result;

    struct timeval time_start;
    struct timeval time_end;
    double overall_time;


    /* Controllo degli argomenti passati in ingresso */

    check_args(argc, argv)


    /* Lettura degli argomenti passati in ingresso */

    rows = atoi(argv[2]);
    columns = atoi(argv[4]);
    threads = atoi(argv[6]);


    /* Generazione della matrice e del vettore */

    srand(time(NULL));
    matrix = generate_random_matrix(rows, columns, 0.0, 5.0);
    vector = generate_random_vector(columns, 0.0, 5.0);
    if(!matrix || !vector) {
        printf("\n <!> ERROR: Unable to allocate memory.\n");
        return ERR_MEMORY;
    }


    /* Stampa della matrice e del vettore generati */

    printf("\n > Generated Matrix \n\n");
    print_matrix(matrix, rows, columns);
    printf("\n\n > Generated Vector \n\n");
    print_vector(vector, columns);


    /* Imposta il numero di thread da impiegare */

    omp_set_num_threads(threads);


    /* Cattura il timestamp all'inizio del calcolo del prodotto */

    gettimeofday(&time_start, NULL);


    /* Effettua il prodotto tra la matrice e il vettore */

    result = product(rows, columns, matrix, vector);
    if(!result){
        printf("\n <!> ERROR: Unable to allocate memory.\n");
        return ERR_MEMORY;
    }


    /* Cattura il timestamp al termine del calcolo del prodotto */

    gettimeofday(&time_end, NULL);


    /* Calcolo il tempo impiegato */

    overall_time = (time_end.tv_sec+(time_end.tv_usec/1000000.0)) -
                   (time_start.tv_sec+(time_start.tv_usec/1000000.0));


    /* Stampa del prodotto e del tempo impiegato */

    printf("\n\n > Product Vector \n\n");
    print_vector(result, rows);
    printf("\n\n > Overall time: %lf\n", overall_time);

    return 0;

}
