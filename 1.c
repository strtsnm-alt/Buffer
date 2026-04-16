GNU nano 8.6                                                graph_methods.c
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#define NO_OF_POINTS 5

struct graph{
    int matrix[NO_OF_POINTS][NO_OF_POINTS];
};
typedef struct graph G;

void createGraph(int m[NO_OF_POINTS][NO_OF_POINTS]){
    int edgeTrue = 0;
    for(int i = 0; i < NO_OF_POINTS; i++){
        for(int j = 0; j < NO_OF_POINTS; j++){
            if (i < j && *(*(m + i) + j) == 0){
                printf("\nFrom point %d to %d ? (1/0) ", i + 1, j + 1);
                scanf("%d", &edgeTrue);
                if (edgeTrue){ m[i][j] = 1; m[j][i] = 1; }
            }
        }
    }
}

void showGraph(int m[NO_OF_POINTS][NO_OF_POINTS]){
    for(int i = 0; i < NO_OF_POINTS; i++){
        for(int j = 0; j < NO_OF_POINTS; j++){
            if (i < j && *(*(m + i) + j) == 1) printf("\n%d -> %d", i + 1, j + 1);
        }
    }
}

void traverseOfDFS(G* g, int visited[NO_OF_POINTS], int startNode){
    printf(" %d", startNode + 1);
    visited[startNode] = 1;

    for(int j = 0; j < NO_OF_POINTS; j++){
        if (g->matrix[startNode][j] == 1 && !(visited[j]))
            traverseOfDFS(g, visited, j);
    }
}

int findPathbyDFS(G* g, int visited[NO_OF_POINTS], int currentNode, int targetNode){
    visited[currentNode] = 1;
    if (currentNode == targetNode){
        printf("\nTarget found, the path : %d", currentNode + 1);
        return 1;
    }

    for(int i = 0; i < NO_OF_POINTS; i++){
        if (g->matrix[currentNode][i] == 1 && !visited[i]){
            if (findPathbyDFS(g, visited, i, targetNode)){
                printf(" <- %d", currentNode + 1);
                return 1;
            }
        }
    }
