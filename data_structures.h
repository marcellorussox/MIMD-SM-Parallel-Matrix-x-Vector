#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

double* random_vector(int dim);
double** random_matrix(int rows, int columns);
double* product(int rows, int columns, double** matrix, double* restrict vector);
void print_vector(double* vector, int dim);
void print_matrix(double** matrix, int rows, int columns);

#endif
