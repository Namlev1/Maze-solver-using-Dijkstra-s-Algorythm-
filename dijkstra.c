#include "dijkstra.h"
#include <stdio.h>

/* Function prints results of using Dijkstra's Algorithm - shortest path */
void printSolution(int endNode,int startNode, double *dist, int *predecessor, int n){

    if(dist[endNode] == INF){   //no route
        printf("There is no route between starting node and end node.\n");
        return;
    }

    orderList_t *order = malloc(sizeof *order);
    if(order == NULL){      //error - no enough memory
        fprintf(stderr, "Error: not enough memory for Dijkstra's Algorithm\n");
        return;
    }

    //initialization of linked list
    order->nodeNumber = endNode;
    order->next = NULL;
    int next = predecessor[endNode];

    do{
        if(pushOrder(&order, next)){    //add element to the beginning of linked list
            //if pushOrder return 1 - error, not enough memory
            fprintf(stderr, "Error: not enough memory for Dijkstra's Algorithm\n");
            while(order != NULL){       //free memory allocated for linked list
                orderList_t *temp = order;
                order = order->next;
                free(temp);
            }
            return;
        }
        next = predecessor[next];       //proceed to the next node
    } while ((predecessor[next] != -1));

    //print results
    printf("The shortest distance from start to end is: %g\n",dist[endNode]);
    printf("%d", startNode);
    while(order != NULL){       //print elements & free linked list
        orderList_t *temp = order;
        printf(" -> %d", order->nodeNumber);
        order = order->next;
        free(temp);
    }
    printf("\n");
}

/* Function updates minimal distance and returns 
    unvisited node index with smallest distance */
static double minDist(double *dist, int *visited, int n){
    double minDist = INF;
    int minNode;
    int i;
    for(i = 0; i < n; i++)
        if(visited[i] == 0 && dist[i] <= minDist){  //look for unvisited node with smallest distance
            minDist = dist[i];
            minNode = i;
        }
    
    return minNode;
}

/* Function adds new linked list element to
    the beginning of linked list */
int pushOrder(orderList_t **head, int newVertex){
    orderList_t *newNode = malloc(sizeof *newNode);
    if(newNode == NULL)     //error - no enough memory
        return 1;
    newNode->nodeNumber = newVertex;
    newNode->next = (*head);
    (*head) = newNode;
    return 0;
}

/* Function that performs Dijkstra's Algorithm */
void dijkstra(matrix_t *matrix, maze_t *maze){
    int i, j;

    double *dist = malloc(matrix->n * sizeof *dist);    
    if(dist == NULL){               //error - not enough memory
        fprintf(stderr, "Error: not enough memory for Dijkstra's Algorithm\n");
        return;
    }

    int *visited = calloc(matrix->n, sizeof visited);   // visited == 1, unvisited == 0
    if(visited == NULL){            //error - not enough memory
        free(dist);
        fprintf(stderr, "Error: not enough memory for Dijkstra's Algorithm\n");
        return;
    }

    int *predecessor = malloc(matrix->n * sizeof *predecessor);
    if(predecessor == NULL){        //error - not enough memory
        free(visited);
        free(dist);
        fprintf(stderr, "Error: not enough memory for Dijkstra's Algorithm\n");
        return;
    }

    int startNode = matrix->nodeMatrix[0][maze->start];
    int endNode = matrix->nodeMatrix[maze->size - 1][maze->finish];

    for(i = 0; i < matrix->n; i++)
        dist[i] = INF;
    
    dist[startNode] = 0;   
    predecessor[startNode] = -1;

    for(i = 0; i < matrix->n; i++){
        int currNode = minDist(dist, visited, matrix->n);
        visited[currNode] = 1;
        
        for(j = 0; j < matrix->n; j++)
            if(visited[j] != 1 && matrix->adjMatrix[currNode][j] && dist[currNode] != INF &&dist[currNode] + matrix->adjMatrix[currNode][j] < dist[j]){
                dist[j] = dist[currNode] + matrix->adjMatrix[currNode][j];
                predecessor[j] = currNode;
                if(j == endNode)    //if reached end node
                    goto END;       //stop processing algorithm
            }
        
    }
    END: 
    printSolution(endNode, startNode, dist, predecessor, matrix->n);
    free(visited);
    free(dist);   
    free(predecessor);
}