#ifndef ADVANCED_CALCULATOR_GRAPH_H
#define ADVANCED_CALCULATOR_GRAPH_H


#include <malloc.h>
#include <stdio.h>
#include <string.h>
#include "assert.h"

#include "../Parser/Parser.h"

typedef struct {
    int *cnt, *p;
    int size;
    int cycleStart, cycleEnd;
} gResult;

typedef struct {
    int n;
    char **variables;
    int **g;
} Graph;

Graph *grCreate(Expression *e, int n);

void transpose(int **g, int n);

void printGraph(int **g, int n);

gResult *gProcess(int **g, int n);


#endif //ADVANCED_CALCULATOR_GRAPH_H
