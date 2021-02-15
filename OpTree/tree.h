#ifndef ADVANCED_CALCULATOR_TREE_H
#define ADVANCED_CALCULATOR_TREE_H


#include <stdlib.h>
#include <assert.h>
#include <string.h>

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
    size_t elementSize;
    struct node_t *left, *right;
} Node;

Node *nodeInit(int elementSize);

void opTreeGen(Node *node, Stack *stack);

void opTreePrint(Node *node, Node *parent);


#endif //ADVANCED_CALCULATOR_TREE_H
