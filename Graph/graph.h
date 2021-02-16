#ifndef ADVANCED_CALCULATOR_GRAPH_H
#define ADVANCED_CALCULATOR_GRAPH_H

#include <malloc.h>
#include <stdio.h>
#include <string.h>


typedef struct {
    int *dfsCnt;
    int *dfsCycle;
} dfsResult;

dfsResult *inti(int n);

int **transpose(int **g, int n);

void printGraph(int **g, int n);

dfsResult *dfsAlgorithm(dfsResult *dfsRes, int **g, int n);

#endif //ADVANCED_CALCULATOR_GRAPH_H
