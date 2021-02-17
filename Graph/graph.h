#ifndef ADVANCED_CALCULATOR_GRAPH_H
#define ADVANCED_CALCULATOR_GRAPH_H


#include <malloc.h>
#include <stdio.h>
#include <string.h>
#include "assert.h"

typedef struct {
    int *cnt;
    int cSize;
    int *cycle;
} gResult;

void transpose(int **g, int n);

void printGraph(int **g, int n);

gResult *gProcess(int **g, int n);


#endif //ADVANCED_CALCULATOR_GRAPH_H
