#include "graph.h"

dfsResult *inti(int n) {
    dfsResult *dfsRes = malloc(sizeof(dfsResult));
    dfsRes->dfsCnt = (int *) malloc(n * sizeof(int));
    dfsRes->dfsCycle = (int *) malloc(n * sizeof(int));
    return dfsRes;
}

int **transpose(int **g, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = i; j < n; ++j) {
            int temp = g[i][j];
            g[i][j] = g[j][i];
            g[j][i] = temp;
        }
    }
    return g;
}

void printGraph(int **g, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            printf("%d ", g[i][j]);
        }
        printf("\n");
    }
}

dfsResult *dfsAlgorithm(dfsResult *dfsRes, int **g, int n) {

    return dfsRes;
}