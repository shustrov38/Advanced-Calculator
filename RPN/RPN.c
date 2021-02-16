#include "RPN.h"
#include "../Operations/ops.h"
#include "../Stack/stack.h"



rpnProcessor* init(){
    rpnProcessor *stackVault = malloc(sizeof(rpnProcessor));
    stackVault -> numStack = stCreate(sizeof(char[10]));
    stackVault -> opStack = stCreate(sizeof(char[10]));
    stackVault -> finalStack = stCreate(sizeof(char[10]));
    assert(stackVault && "NULLPTR in init");
    return stackVault;
}

int getOpPriorityNum(char *op){
    switch (getOpPriority(getOpID(op))){
        case SUM:
            return 1;
        case PROD:
            return 2;
        case FUNC:
            return 3;
        case POWER:
            return 4;
    }
}


Stack* rpnFunc(rpnProcessor *stack, char** string, int size){
    int openBracket = 0, closeBracket = 0;
    int func = 0;


    assert(size > 0 && string != NULL);
    for (int i = 0; i < size; ++i){
        if (IS_VAR(string[i]) || IS_CONST(string[i])) {
            stPush(stack->finalStack, string[i]);
        }

        if (IS_OPER(string[i]) || IS_FUNC_1ARG(string[i]) || IS_FUNC_2ARG(string[i])){
            if(stack->opStack->size!=0 && (IS_OPER(stTop(stack->opStack)) || IS_FUNC_1ARG(stTop(stack->opStack)) ||
            IS_FUNC_2ARG(stTop(stack->opStack)))){
                if(getOpPriorityNum(string[i])>getOpPriorityNum(stTop(stack->opStack))) {
                    stPush(stack->opStack, string[i]);
                }
                else {
                    stPush(stack->finalStack, stTop(stack->opStack));
                    stPop(stack->opStack);
                }
            }
            else stPush(stack->opStack, string[i]);
        }

        if (strcmp(string[i], "(") == 0){
            openBracket++;
            stPush(stack->opStack, string[i]);
        }

        if (strcmp(string[i], ")") == 0){
            while(stTop(stack->opStack)!='(') {
                stPush(stack->finalStack, stTop(stack->opStack));
                stPop(stack->opStack);
            }
            stPop(stack->opStack);
            openBracket--;
        }
    }
    while(stack->opStack->size!=0) {
        stPush(stack->finalStack, stTop(stack->opStack));
        stPop(stack->opStack);
    }

    return stack->finalStack;
}


