#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include "../headers/data_structures.h"


//? Genera un vettore di dimensione DIM con elementi randomici
double* get_random_vector(int dim) {

    srand(time(NULL));
    double* vector = (double*)malloc(dim * sizeof(double));
    if (vector) {
        for (int i = 0; i < dim; i++) {
            vector[i] = (double)rand() / RAND_MAX;
        }
    }
    return vector;
}


//? Genera un vettore di dimensione ROWS X COLUMNS con elementi randomici
double** get_random_matrix(int rows, int columns) {

    srand(time(NULL));
    double** matrix = (double**)malloc(rows * sizeof(double*));

    if (matrix) {
        for (int i = 0; i < rows; i++) {
            matrix[i] = (double*)malloc(columns * sizeof(double));
            if (!matrix[i]) {
                for (int k = 0; k < i; k++) {
                    free(matrix[k]);
                }
                free(matrix);
                return NULL;
            }
            for (int j = 0; j < columns; j++) {
                matrix[i][j] = (double)rand() / RAND_MAX;
            }
        }
    }
    return matrix;
}


//? Esegue il calcolo del prodotto MATRICE X VETTORE
double *mat_vec_product(int rows, int columns, double **matrix, double* vector)
{
    double *product = (double *)calloc(rows, sizeof(double));
    if (product) {
        #pragma omp parallel for default(none) shared(rows, columns, matrix, vector, product)
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < columns; j++)
                product[i] += matrix[i][j] * vector[j];
    }
    return product;
}


//? Stampa Vettore
void print_vector(double* vector, int dim) {
    for(int i = 0; i < dim; i++)
        printf(" [%lf] ", vector[i]);
    printf("\n");
}


//? Stampa Matrice
void print_matrix(double** matrix, int rows, int columns) {
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < columns; j++)
            printf(" [%lf]", matrix[i][j]);
        printf("\n");
    }
}
