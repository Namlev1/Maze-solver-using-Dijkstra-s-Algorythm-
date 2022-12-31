#ifndef MATRIX_H
#define MATRIX_H

#define INF 2147483647  //representation of infinity - maximum value stored by int

typedef struct matrix{
    int n;                      //number of nodes
    double **adjMatrix;         //representation of adjacency matrix
    int **nodeMatrix;           //representatnion of maze with numbered nodes
} matrix_t;

matrix_t *initMatrix(maze_t *maze);
void freeMatrix(matrix_t *matrix, int size);

#endif