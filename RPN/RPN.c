#include "RPN.h"
#include "../Operations/ops.h"
#include "../Stack/stack.h"

typedef struct {
    Stack *numStack;
    Stack *funcStack;
    Stack *finalStack;
} rpnProcessor;

rpnProcessor* init(){
    rpnProcessor *stackVault = malloc(sizeof(rpnProcessor));
    stackVault -> numStack = stCreate(sizeof(char[10]));
    stackVault -> funcStack = stCreate(sizeof(char[10]));
    stackVault -> finalStack = stCreate(sizeof(char[10]));
    return stackVault;
}

void rpnStep(rpnProcessor *stack){

}

Stack* rpnFunc(rpnProcessor *stack, char** string, int size){
    int openBracket = 0, closeBracket = 0;
    int func = 0;

    assert(size > 0 && string != NULL);
    for (int i = 0; i < size; ++i){
        if (IS_VAR(string[i]) || IS_CONST(string[i])) {
            stPush(stack->numStack, string[i]);
        }

        if (IS_OPER(string[i])){

        }

        if (IS_FUNC_1ARG(string[i])){

        }

        if (IS_FUNC_2ARG(string[i])){

        }

        if (strcmp(string[i], "(") == 0){

        }

        if (strcmp(string[i], ")") == 0){

        }






    }
}


