#include "maze.h"
#include <stdio.h>

/*  *Function checks if one cell of the maze is surrounded 
    *by walls from every side */
static void ifSurrounded (maze_t *maze){
    int i, j;

    //check if corners of the maze are closed (surrounded)
    if(maze->cells[0][0] != WALL && maze->cells[0][1] == WALL && maze->cells[1][0] == WALL){  //left-upper corner
        int direction = rand() % 2;
        switch (direction){
        case 0: //change right wall
            maze->cells[0][1] = (double)(rand() % 999 + 1)/100;
            break;
        
        case 1: //change bottom wall
            maze->cells[1][0] = (double)(rand() % 999 + 1)/100;
            break;
        }
    }

    if(maze->cells[maze->size - 1][0] != WALL && maze->cells[maze->size - 1][1] == WALL && maze->cells[maze->size - 2][0] == WALL){//left-bottom corner
        int direction = rand() % 2;
        switch (direction){
        case 0: //change upper wall
            maze->cells[maze->size - 2][0] = (double)(rand() % 999 + 1)/100;
            break;
        case 1: //change right wall
            maze->cells[maze->size - 1][1] = (double)(rand() % 999 + 1)/100;
            break;
        }
    } 

    if(maze->cells[0][maze->size - 1] != WALL && maze->cells[0][maze->size - 2] == WALL && maze->cells[1][maze->size - 1] == WALL){ //right-upper corner
        int direction = rand() % 2;
        switch (direction){
        case 0: //change left wall
            maze->cells[0][maze->size - 2] = (double)(rand() % 999 + 1)/100;
            break;
        case 1: //change bottom wall
            maze->cells[1][maze->size - 1] = (double)(rand() % 999 + 1)/100;
            break;
        }
    } 

    if(maze->cells[maze->size - 1][maze->size - 1] != WALL && maze->cells[maze->size - 1][maze->size - 2] == WALL && maze->cells[maze->size - 2][maze->size - 1] == WALL){ //right-bottom corner
        int direction = rand() % 2;
        switch (direction){
        case 0: //change left wall
            maze->cells[maze->size - 1][maze->size - 2] = (double)(rand() % 999 + 1)/100;
            break;
        case 1: //change bottom wall
            maze->cells[maze->size - 2][maze->size - 1] = (double)(rand() % 999 + 1)/100;
            break;
        }
    } 

    //check sides of the maze
    for(i = 1; i < maze->size - 1; i++){
        if(maze->cells[0][i] != WALL && maze->cells[0][i-1] == WALL && maze->cells[0][i+1] == WALL && maze->cells[1][i] == WALL){ //upper row
            int direction = rand() % 3;
            switch (direction){
            case 0: //change left 
                maze->cells[0][i-1] = (double)(rand() % 999 + 1)/100;
                break;
            case 1: //change bottom
                maze->cells[1][i] = (double)(rand() % 999 + 1)/100;
                break;
            case 2: //change right
                maze->cells[0][i+1] = (double)(rand() % 999 + 1)/100;
                break;
            }
        }
        if(maze->cells[maze->size - 1][i] != WALL && maze->cells[maze->size - 1][i-1] == WALL && maze->cells[maze->size - 1][i+1] == WALL && maze->cells[maze->size - 2][i] == WALL){ //bottom row
            int direction = rand() % 3;
            switch (direction){
            case 0: //change left
                maze->cells[maze->size - 1][i-1] = (double)(rand() % 999 + 1)/100;
                break;
            case 1: //change upper
                maze->cells[maze->size - 2][i] = (double)(rand() % 999 + 1)/100;
                break;
            case 2: //change right
                maze->cells[maze->size - 1][i+1] = (double)(rand() % 999 + 1)/100;
                break;
            }
        }
        if(maze->cells[i][0] != WALL && maze->cells[i-1][0] == WALL && maze->cells[i][1] == WALL && maze->cells[i+1][0] ){ //left column
            int direction = rand() % 3;
            switch (direction){
            case 0: //change upper
                maze->cells[i-1][0] = (double)(rand() % 999 + 1)/100;
                break;
            case 1: //change right
                maze->cells[i][1] = (double)(rand() % 999 + 1)/100;
                break;
            case 2: //change down
                maze->cells[i+1][0] = (double)(rand() % 999 + 1)/100;
                break;
            }
        }
        if(maze->cells[i][maze->size - 1] != WALL && maze->cells[i-1][maze->size - 1] == WALL && maze->cells[i][maze->size - 2] == WALL && maze->cells[i+1][maze->size - 1] ){ //right column
            int direction = rand() % 3;
            switch (direction){
            case 0: //change upper
                maze->cells[i-1][maze->size - 1] = (double)(rand() % 999 + 1)/100;
                break;
            case 1: //change left
                maze->cells[i][maze->size - 2] = (double)(rand() % 999 + 1)/100;
                break;
            case 2: //change bottom
                maze->cells[i+1][maze->size - 1] = (double)(rand() % 999 + 1)/100;
                break;
            }
        }
    }

    //check if inner cells are surrounded
    for(i = 1; i < maze->size - 2; i++)
        for(j = 1; j < maze->size - 2; j++)
            if(maze->cells[i][j] != WALL && maze->cells[i-1][j] == WALL && maze->cells[i+1][j] == WALL && maze->cells[i][j-1] == WALL && maze->cells[i][j+1] == WALL){  //if cell is surrounded
                int direction = rand() % 4;
                switch (direction){
                case 0: //change upper wall
                    maze->cells[i-1][j] = (double)(rand() % 999 + 1)/100;
                    break;
                case 1: //change bottom wall
                    maze->cells[i+1][j] = (double)(rand() % 999 + 1)/100;
                    break;
                case 2: //change left wall
                    maze->cells[i][j-1] = (double)(rand() % 999 + 1)/100;
                    break;
                case 3: //change right wall
                    maze->cells[i][j+1] = (double)(rand() % 999 + 1)/100;
                    break;
                }
            }
}

/*Function returns fully-initialized maze*/
maze_t* initMaze(int n){
    int i, j;

    maze_t *newMaze = malloc(n * sizeof *newMaze);
    if(newMaze == NULL)         //error - no memory
        return NULL;
    
    newMaze->cells = malloc(n * sizeof *newMaze->cells);
    if(newMaze->cells == NULL){ //error - no memory
        free(newMaze);
        return NULL;
    }

    //randomize start and end
    newMaze->start = rand()%n;
    newMaze->finish = rand()%n;
    newMaze->size = n;

    //generate random values of cells
    for(i = 0; i < n; i++){     
        newMaze->cells[i] = malloc(n * sizeof *newMaze->cells[0]);
        if (newMaze->cells[i] == NULL){     //error - no memory
                for(j = 0; j < i; j++)
                    free(newMaze->cells[i]);
                free(newMaze->cells);
                free(newMaze);
                return NULL;
        }
        for(j = 0; j < n; j++){
            newMaze->cells[i][j] = (double)(rand() % 999 + 1)/100;
            if(rand() % 3 == 0)     //33,33% chance to change a cell into a wall
                newMaze->cells[i][j] = WALL;
        }
    }

    //ensure that start and end cells are not walls
    newMaze->cells[0][newMaze->start] = (double)(rand() % 999 + 1)/100;
    newMaze->cells[newMaze->size-1][newMaze->finish] = (double)(rand() % 999 + 1)/100;

    ifSurrounded(newMaze);
    return newMaze;
}

/* Function prints maze to stdout*/
void printMaze(maze_t *maze, int n){
    int i, j;

    printf("\nGenerated maze:\n\n");

    //first wall
    printf("##");
    for(i = 0; i < n; i++){
        if(i == maze->start)
            printf("      ");
        else
            printf("#####");
    }
    printf("###");
    printf("\n");

    //rows of the maze
    for(i = 0; i < n; i++){
        printf("## ");
        for(j = 0; j < n; j++){
            if(maze->cells[i][j] == WALL)
                printf("#### ");
            else
                printf("%.2lf ", maze->cells[i][j]);
        }
        printf(" ##\n");
    }
    printf("##");

    //bottom wall
    for(i = 0; i < n; i++){
        if(i == maze->finish)
            printf("      ");
        else
            printf("#####");
    }
    printf("###\n\n");
}

/* Function frees memory allocated for the maze */
void freeMaze(maze_t *maze){
    int i;
    for(i = 0; i < maze->size; i++)
        free(maze->cells[i]);
    free(maze->cells);
    free(maze);
}