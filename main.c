#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <omp.h>
#include "headers/data_structures.h"
#include "headers/utilities.h"



int main(int argc, char** argv) {

    int rows; //? N. righe matrice
    int columns; //? N. colonne matrice
    int threads; //? N. thread da usare

    double** matrix; //? Matrice
    double* vector; //? Vettore
    double* result; //? Risultato del prodotto (Vettore)

    struct timeval time_start; //? Ora inizio
    struct timeval time_end; //? Ora fine
    double overall_time; //? Tempo impiegato


    
    //? Verifica parametri
    check_params(argc, argv);


    //? Imposto i valori
    rows = atoi(argv[2]);
    columns = atoi(argv[4]);
    threads = atoi(argv[6]);


    //? Generazione della matrice e del vettore
    matrix = get_random_matrix(rows, columns);
    vector = get_random_vector(columns);
    if(!matrix || !vector) {
        printf("\n <!> ERROR: Unable to allocate memory.\n");
        return ERR_MEMORY;
    }


    //? Stampa della matrice e del vettore ottenuti
    printf("\nRandom Matrix: \n\n");
    print_matrix(matrix, rows, columns);
    printf("\n\nRandom Vector: \n\n");
    print_vector(vector, columns);


    //? Set del numero di thread da usare
    omp_set_num_threads(threads);


    //? Segna l'ora di inizio
    gettimeofday(&time_start, NULL);


    //? Calcolo il prodotto VETTORE X MATRICE
    result = mat_vec_product(rows, columns, matrix, vector);
    if(!result){
        printf("\n <!> ERROR: Unable to allocate memory.\n");
        return ERR_MEMORY;
    }


    //? Segna l'ora di fine
    gettimeofday(&time_end, NULL);


    //? Ottiene il tempo effettivo
    overall_time = (time_end.tv_sec+(time_end.tv_usec/1000000.0)) -
                   (time_start.tv_sec+(time_start.tv_usec/1000000.0));


    //? Stampa dei risultati ottenuti
    printf("\n\nProduct Vector: \n\n");
    print_vector(result, rows);
    printf("\nOverall time: %lf\n", overall_time);

    return 0;

}
