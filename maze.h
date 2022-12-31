#ifndef MAZE_H
#define MAZE_H
#include <stdlib.h>

#define WALL -1

typedef struct{
    double **cells;  //cells of the maze
    int start;       //starting cell
    int finish;      //end cell
    size_t size;     //size of one side of the maze
} maze_t;

maze_t* initMaze(int n);
void printMaze(maze_t *maze, int n);
void freeMaze(maze_t *maze);

#endif