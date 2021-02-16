#ifndef ADVANCED_CALCULATOR_RPN_H
#define ADVANCED_CALCULATOR_RPN_H
#include "../Stack/stack.h"
#include "../Operations/ops.h"
#endif //ADVANCED_CALCULATOR_RPN_H



typedef struct {
    Stack *numStack;
    Stack *opStack;
    Stack *finalStack;
} rpnProcessor;

rpnProcessor* init();

Stack* rpnFunc(rpnProcessor *stack, char** string, int size);