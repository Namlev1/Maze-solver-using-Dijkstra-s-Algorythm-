#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "maze.h"
#include "matrix.h"
#include "dijkstra.h"

int main(int argc, char** argv){
    srand(time(0));

    if(argc == 1){      //error - no arguments
        fprintf(stderr, "Error: too few arguments\n");
        fprintf(stderr, "Usage:\n");
        fprintf(stderr, "<filename> <size_of_maze>\n");
        return 1;
    }

    int size = atoi(argv[1]);
    if(size < 3){       //error - too small size
        fprintf(stderr, "Error: wrong maze size\n");
        fprintf(stderr, "Minimum size of the maze is 3\n");
        return 2;
    }

    if(size > 25){      //disclaimer - too big size
        char c;
        printf("\nWarning: size of the maze (%d) is too big and the maze may not be displayed properly\n", size);
        do{
            printf("Do you want to continue? [y/n]");
            c = fgetc(stdin);
            fflush(stdin);
        } while (c != 'y' && c != 'n');

        if(c == 'n')
            return 0;
    }

    maze_t *maze = initMaze(size);
    if(maze == NULL){       //error - no allocated memory for maze
        fprintf(stderr, "Error: not enough memory for creating a maze\n");
        return 3;
    }
    printMaze(maze, size);

    matrix_t *matrix = initMatrix(maze);
    if(matrix == NULL){     //error - no allocated memory for matrix
        fprintf(stderr, "ERROR: not enough memory for creating an adjacency matrix\n");
        freeMaze(maze);
        return 4;
    }

    dijkstra(matrix, maze);

    freeMaze(maze);
    freeMatrix(matrix, size);
    return 0;

}