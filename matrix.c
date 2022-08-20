#include<stdio.h>
#include"matrix.h"

Matrix* new_matrix(int x, int y) {
    Matrix *n_mat = malloc(sizeof(Matrix));
    n_mat->x = x;
    n_mat->y = y;
    
    unsigned char* array = calloc(x*y, sizeof(unsigned char));
    n_mat->contents = array;

    return n_mat;
}

void dlt_matrix(Matrix* m) {
    free(m->contents);
    free(m);
}

int mod_matrix(Matrix* m, int x, int y, unsigned char new_value) {
    if (m->x >= x && m->y >= y) {
        *((m->contents)+(y*m->x+x)) = new_value;
        return 1;
    } else {
        return 0;
    }
}

// returns value given valid dim
int get_in_matrix(Matrix* m, int x, int y) {
    if (m->x >= x && m->y >= y) {
        return (unsigned char)*((m->contents)+(y*m->x+x));
    }
    return -1;
}

Matrix* id_matrix(int size) {
    Matrix* m = new_matrix(size,size);

    for (int i = 0; i < size; i++) {
        mod_matrix(m, i, i, 1);
    }

    return m;
}

void print_matrix(Matrix* m) {
    int x = m->x;
    int y = m->y;
    for (int i = 0; i<x*y; i++) {
        printf("%d ", (int)*(m->contents+i));
        if ((i+1) % x == 0) {
            printf("\n");
        }
    }
}