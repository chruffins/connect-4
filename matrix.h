#ifndef MATRIX_H
#define MATRIX_H

#include<stdlib.h>

struct Matrix {
    int x;
    int y;
    unsigned char* contents;
} typedef Matrix;

Matrix* new_matrix(int x, int y);
void dlt_matrix(Matrix* m);
int mod_matrix(Matrix* m, int x, int y, unsigned char new_value);
int get_in_matrix(Matrix* m, int x, int y);
Matrix* id_matrix(int size);
void print_matrix(Matrix* m);

#endif