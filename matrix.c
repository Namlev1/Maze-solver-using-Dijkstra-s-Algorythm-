#include "maze.h"
#include "matrix.h"
#include <stdio.h>

/* Funcion prints maze with numbered nodes to stdout */
static void printNodeMatrix(maze_t *maze, matrix_t *matrix){
    int i, j;

    printf("Maze represented with numbered nodes:\n\n");
    //first wall
    printf("##");
    for(i = 0; i < maze->size; i++){
        if(i == maze->start)
            printf("      ");
        else
            printf("#####");
    }
    printf("###\n");

    //rows of the maze
    for(i = 0; i < maze->size; i++){
        printf("## ");
        for(j = 0; j < maze->size; j++){
            if(maze->cells[i][j] == WALL)
                printf("#### ");
            else
                printf("%3d  ", matrix->nodeMatrix[i][j]);
        }
        printf(" ##\n");
    }

    //bottom wall
    printf("##");
    for(i = 0; i < maze->size; i++){
        if(i == maze->finish)
            printf("      ");
        else
            printf("#####");
    }
    printf("###\n\n");

    printf("Number of nodes = %d\n", matrix->n);
    printf("Starting node = %d\n", matrix->nodeMatrix[0][maze->start]);
    printf("End node = %d\n\n", matrix->nodeMatrix[maze->size - 1][maze->finish]);
}

/* Funcion returns a fully-initialized matrix */
matrix_t *initMatrix(maze_t *maze){     
    int i, j;

    matrix_t *newMatrix = malloc(sizeof *newMatrix);
    if (newMatrix == NULL)              //error - no memory
        return NULL;
        
    newMatrix->n = 0;

    newMatrix->nodeMatrix = malloc(maze->size * sizeof newMatrix->nodeMatrix);    
    if(newMatrix->nodeMatrix == NULL){  //error - no memory
        free(newMatrix);
        return NULL;
    }

    for(i = 0; i < maze->size; i++){
        newMatrix->nodeMatrix[i] = calloc(maze->size, sizeof *newMatrix->nodeMatrix);
        if(newMatrix->nodeMatrix[i] == NULL){   //error - no memory
            for(j = 0; j < i; j++)
                free(newMatrix->nodeMatrix[j]);
            free(newMatrix->nodeMatrix);
            free(newMatrix);
            return NULL;
        }
    }

    //count nodes, fill the nodeMatrix
    for(i = 0; i < maze->size; i++)
        for(j = 0; j < maze->size; j++)
            if(maze->cells[i][j] != WALL)
                newMatrix->nodeMatrix[i][j] = newMatrix->n++;


    newMatrix->adjMatrix = malloc(newMatrix->n * sizeof *newMatrix->adjMatrix);
    if(newMatrix->adjMatrix == NULL){       //error - no memory
        for(i = 0; i < maze->size; i++)
            free(newMatrix->nodeMatrix[i]);
        free(newMatrix->nodeMatrix);
        free(newMatrix);
        return NULL;
    }

    for(i = 0; i < newMatrix->n; i++){
        newMatrix->adjMatrix[i] = calloc(newMatrix->n, sizeof *newMatrix->adjMatrix[i]);
        if(newMatrix->adjMatrix[i] == NULL){    //error - no memory
            for(j = 0; j < i; j++)
                free(newMatrix->adjMatrix[j]);
            free(newMatrix->adjMatrix);
            for(j = 0; j < maze->size; j++)
                free(newMatrix->nodeMatrix[j]);
            free(newMatrix->nodeMatrix);
            free(newMatrix);
            return NULL;
        }
    }
    
    //fill adjacency matrix
    for(i = 0; i < maze->size; i++)
        for(j = 0; j < maze->size; j++){
            if(j != 0 && maze->cells[i][j-1] != WALL && maze->cells[i][j] != WALL){ //if cell to the left is not a wall
                //add connection
                newMatrix->adjMatrix[newMatrix->nodeMatrix[i][j]][newMatrix->nodeMatrix[i][j-1]] = (maze->cells[i][j-1] + maze->cells[i][j]) / 2; 
            }
            if(j != maze->size - 1 && maze->cells[i][j+1] != WALL && maze->cells[i][j] != WALL){ //if cell to the right is not a wall
                //add connection
                newMatrix->adjMatrix[newMatrix->nodeMatrix[i][j]][newMatrix->nodeMatrix[i][j+1]] = (maze->cells[i][j+1] + maze->cells[i][j]) / 2; 
            }
            if(i != maze->size - 1 && maze->cells[i+1][j] != WALL && maze->cells[i][j] != WALL){ //if cell to the bottom is not a wall
                //add connection
                newMatrix->adjMatrix[newMatrix->nodeMatrix[i][j]][newMatrix->nodeMatrix[i+1][j]] = (maze->cells[i+1][j] + maze->cells[i][j]) / 2; 
            }
            if(i != 0 && maze->cells[i-1][j] != WALL && maze->cells[i][j] != WALL){ //if cell up is not a wall
                //add connection
                newMatrix->adjMatrix[newMatrix->nodeMatrix[i][j]][newMatrix->nodeMatrix[i-1][j]] = (maze->cells[i+-1][j] + maze->cells[i][j]) / 2; 
            }
        }
    
    printNodeMatrix(maze, newMatrix);

    #ifdef DEBUG
    //print adjacency matrix to stdout
    if(newMatrix->n > 15){  //disclaimer - too big adjacency matrix
        char c;
        printf("Warning: size of the adjacency matrix (%d) is too big and may not be displayed properly\n", newMatrix->n);
        do{
            printf("Do you want to print it? [y/n]");
            c = fgetc(stdin);
            fflush(stdin);
        } while (c != 'y' && c != 'n');
        
        if(c == 'y'){
            printf("\nAdjacency matrix:\n");
            for(i = 0; i < newMatrix->n; i++){           
                for(j = 0; j < newMatrix->n; j++)
                    printf("%2.2lf ", newMatrix->adjMatrix[i][j]);
                printf("\n\n");
            }
        }
    }
    else{
        printf("Adjacency matrix:\n");
            for(i = 0; i < newMatrix->n; i++){           
                for(j = 0; j < newMatrix->n; j++)
                    printf("%2.2lf ", newMatrix->adjMatrix[i][j]);
                printf("\n\n");
            }
    }
    #endif

    return newMatrix;
}

/*Function frees memory allocated for the matrix*/
void freeMatrix(matrix_t *matrix, int size){
    int i;

    for(i = 0; i < matrix->n; i++)
        free (matrix->adjMatrix[i]);
    free(matrix->adjMatrix);

    for(i = 0; i < size; i++)
        free(matrix->nodeMatrix[i]);
    free(matrix->nodeMatrix);

    free(matrix);
}