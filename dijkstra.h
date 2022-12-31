#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "maze.h"
#include "matrix.h"

typedef struct order{
    int nodeNumber;
    struct order *next;
} orderList_t;  //structure of linked list

int pushOrder(orderList_t **head, int newVertex);
void printSolution(int endNode,int startNode, double *dist, int *predecessor, int n);
void dijkstra(matrix_t *matrix, maze_t *maze);

#endif