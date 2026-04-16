lude <stdlib.h>
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
    return 0;
}

void traverseOfBFS(G* g, int visited[NO_OF_POINTS], int currentNode){
    Q* queue = NULL;

    visited[currentNode] = 1;
    queue = enqueue(queue, currentNode);
    while(queue != NULL){

        int currentNode = queue->array[queue->front];
        queue = dequeue(queue);
        printf(" %d", currentNode + 1);

        for(int i = 0; i < NO_OF_POINTS; i++){
            if (g->matrix[currentNode][i] == 1 && !(visited[i])){
                visited[i] = 1;
                queue = enqueue(queue, i);
            }
        }
    }
}

int main(){
    G *graph;
    graph = calloc(sizeof(G), 1);

    createGraph(graph->matrix);

    printf("\nThe given graph is of the following :\n");
    showGraph(graph->matrix);

    int *nodesFoundByDFS;
    nodesFoundByDFS = calloc(sizeof(int), NO_OF_POINTS);

    printf("\n\nBelow is every node found from the root node in the given graph found through DFS: ");
    traverseOfDFS(graph, nodesFoundByDFS, 0);

    free(nodesFoundByDFS);

    nodesFoundByDFS = calloc(sizeof(int), NO_OF_POINTS);

    int destNode;
    printf("\nYou can also find path, please enter a destination point : ");
    scanf("%d", &destNode);
    printf("\n\nYou can reach Node number 4 from 1 on following the give path below:\n");
    findPathbyDFS(graph, nodesFoundByDFS, 0, destNode - 1);

    free(nodesFoundByDFS);

    int *nodesFoundByBFS;
    nodesFoundByBFS = calloc(sizeof(int), NO_OF_POINTS);

    printf("\n\nBelow is every node found from the root node in the given graph found through BFS: ");
    traverseOfBFS(graph, nodesFoundByBFS, 0);

    free(nodesFoundByBFS);

    free(graph);

    return 0;
