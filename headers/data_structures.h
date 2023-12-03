#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

double* get_random_vector(int dim);
double** get_random_matrix(int rows, int columns);
double* vec_mat_product(int rows, int columns, double** matrix, double* vector);
void print_vector(double* vector, int dim);
void print_matrix(double** matrix, int rows, int columns);

#endif
