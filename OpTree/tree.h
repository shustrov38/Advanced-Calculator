#ifndef ADVANCED_CALCULATOR_TREE_H
#define ADVANCED_CALCULATOR_TREE_H


#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <complex.h>

#include "../Stack/stack.h"
#include "../Operations/ops.h"

typedef enum {
    OPERATION,
    FUNCTION1,
    FUNCTION2,
    BASIC
} NodeState;

typedef struct node_t {
    char *value;
    NodeState state;
    double complex result;
    size_t elementSize;
    struct node_t *left, *right;
} Node;

Node *nodeInit(int elementSize);

void opTreeGen(Node *node, Stack *stack);

double complex opTreeCalc(Node *node);

void opTreePrint(Node *node);

/*
    // example to present tree
    int size = sizeof(char[10]);
    Stack *stack = stCreate(size);
    stPush(stack, "3");
    stPush(stack, "a");
    stPush(stack, "b");
    stPush(stack, "+");
    stPush(stack, "ln");
    stPush(stack, "log");
    stPrint(stack);
    Node *root = nodeInit(size);
    opTreeGen(root, stack);
    opTreePrint(root);
*/

#endif //ADVANCED_CALCULATOR_TREE_H
