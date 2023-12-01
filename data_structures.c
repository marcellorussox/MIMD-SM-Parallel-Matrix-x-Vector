#include <stdio.h>
#include <string.h>
#include "data_structures.h"


/*

	Genera un vettore di dimensione "dim" elementi reali pseudo-randomici

	@params:
		int dim: Dimensione del vettore

	@return:
		double**: Vettore generato

*/

double* random_vector(int dim) {

    double* vector = (double*) calloc(dim, sizeof(double));
    if(vector) {
        for(int i = 0; i < dim; i++)
            vector[i] = (double)rand() / RAND_MAX;
    }

    return vector;

}



/*

	Genera una matrice di "rows x columns" elementi reali pseudo-randomici

	@params:
		int rows: Numero di righe della matrice
		int columns: Numero di colonne della matrice

	@return:
		double**: Matrice generata

*/

double** random_matrix(int rows, int columns) {

    double** matrix = (double**) malloc(rows*sizeof(double*));
    if(matrix) {
        for(int i = 0; i < rows; i++) {
            matrix[i] = (double*) calloc(columns, sizeof(double));
            if(!matrix[i])
                return NULL;
            for(int j = 0; j < columns; j++)
                matrix[i][j] = (double)rand() / RAND_MAX;
        }
    }

    return matrix;

}



/*

	Effettua Il prodotto tra la matrice e il vettore passati in ingresso

	@params:
		int rows: Numero di righe della matrice
		int columns: Numero di colonne della matrice
		double** matrix: Matrice da impiegare nel calcolo del prodotto
		double* vector: Vettore da impiegare nel calcolo del prodotto

	@return:
		Vettore di dime rows risultate dal prodotto

*/

double* product(int rows, int columns, double** matrix, double* restrict vector) {

    double* product = (double*) calloc(rows, sizeof(double));
    if(product) {
#pragma omp parallel for default(none) shared(rows, columns, matrix, vector, product)
        for(int i = 0; i < rows; i++)
            for(int j = 0; j < columns; j++)
                product[i] += matrix[i][j]*vector[j];
    }

    return product;

}



/*

	Effettua la stampa del vettore passato in ingresso

	@params:
		double* vector: Vettore da stampare
		int dim: Dimensione del vettore

	@return:
		void

*/

void print_vector(double* vector, int dim) {

    for(int i = 0; i < dim; i++)
        printf(" [%lf] ", vector[i]);
    printf("\n");

}



/*

	Effettua la stampa della matrice passata in ingresso

	@params:
		double** matrix: Matrice da stampare
		int rows: Numero di righe della matrice
		int columns: Numero di colonne della matrice

	@return:
		void

*/

void print_matrix(double** matrix, int rows, int columns) {

    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < columns; j++)
            printf(" [%lf]", matrix[i][j]);
        printf("\n");
    }

}
