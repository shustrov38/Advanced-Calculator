#include "tree.h"

Node *nodeInit(int elementSize) {
    Node *node = (Node *) malloc(sizeof(Node));
    assert(node != NULL && "bad mem allocate");
    node->elementSize = elementSize;
    node->value = (char *) malloc(node->elementSize);
    assert(node->value != NULL && "bad mem allocate");
    node->left = node->right = NULL;
    return node;
}

void opTreeGen(Node *node, Stack *stack) {
    assert(node != NULL && "bad root");
    assert(stack != NULL && stack->size != 0 && "bad stack");

    // recursive end condition
    if (stack->size == 0) return;

    char *tmp = (char *) malloc(stack->elementSize);
    strcpy(tmp, stTop(stack));
    stPop(stack);

    if (IS_OPER(tmp)) {
        node->state = OPERATION;
    } else if (IS_FUNC_1ARG(tmp)) {
        node->state = FUNCTION1;
    } else if (IS_FUNC_2ARG(tmp)) {
        node->state = FUNCTION2;
    } else /* var or const */ {
        node->state = BASIC;
    }

    switch (node->state) {
        case OPERATION:
        case FUNCTION2:
            strcpy(node->value, tmp);
            node->right = nodeInit(node->elementSize);
            opTreeGen(node->right, stack);
            node->left = nodeInit(node->elementSize);
            opTreeGen(node->left, stack);
            break;
        case FUNCTION1:
            strcpy(node->value, tmp);
            node->right = nodeInit(node->elementSize);
            opTreeGen(node->right, stack);
            break;
        case BASIC:
            strcpy(node->value, tmp);
            break;
    }
}

double complex opTreeCalc(Node *node) {
    double complex a, b;
    if (node->state == OPERATION) {
        a = opTreeCalc(node->right);
        b = opTreeCalc(node->left);
        switch (getOpID(node->value)) {
            case PLS:
                return __sum(a, b);
            case MNS:
                return __sub(a, b);
            case MUL:
                return __mul(a, b);
            case DIV:
                return __div(a, b);
            case MOD:
                return __mod(a, b);
            case PWR:
                return __pwr(a, b);
        }
    } else if (node->state == FUNCTION1) {

    } else if (node->state == FUNCTION2) {

    } else /* basic */ {
        return toComplex(node->value);
    }
}

void opTreePrint(Node *node) {
    if (node == NULL) return;
    switch (node->state) {
        case OPERATION:
            printf("(");
            opTreePrint(node->left);
            printf("%s", node->value);
            opTreePrint(node->right);
            printf(")");
            break;
        case FUNCTION1:
            printf("%s(", node->value);
            opTreePrint(node->right);
            printf(")");
            break;
        case FUNCTION2:
            printf("%s(", node->value);
            opTreePrint(node->left);
            printf(",");
            opTreePrint(node->right);
            printf(")");
            break;
        case BASIC:
            printf("%s", node->value);
            break;
    }
}
