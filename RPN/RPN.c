#include "RPN.h"
#include "../Operations/ops.h"
#include "../Stack/stack.h"


rpnProcessor *init() {
    rpnProcessor *stackVault = malloc(sizeof(rpnProcessor));
    stackVault->numStack = stCreate(sizeof(char[10]));
    stackVault->opStack = stCreate(sizeof(char[10]));
    stackVault->finalStack = stCreate(sizeof(char[10]));
    assert(stackVault && "NULLPTR in init");
    return stackVault;
}


Stack *rpnFunc(rpnProcessor *stack, char **string, int size) {
    int openBracket = 0, closeBracket = 0;
    int func = 0;


    assert(size > 0 && string != NULL);
    for (int i = 0; i < size; ++i) {
        if (IS_VAR(string[i]) || IS_CONST(string[i]) || getOpID(string[i]) == NUM) {
            stPush(stack->finalStack, string[i]);
        }

        if (strcmp(string[i], ",") == 0 && strcmp(stTop(stack->opStack), "(" ) != 0){
            stPush(stack->finalStack, stTop(stack->opStack));
            stPop(stack->opStack);
        }

        if (IS_OPER(string[i]) || IS_FUNC_1ARG(string[i]) || IS_FUNC_2ARG(string[i])) {
            if (stack->opStack->size != 0 && (IS_OPER(stTop(stack->opStack)) || IS_FUNC_1ARG(stTop(stack->opStack)) ||
                                              IS_FUNC_2ARG(stTop(stack->opStack)))) {
                if (PRIORITY(string[i]) > PRIORITY(stTop(stack->opStack))) {
                    stPush(stack->opStack, string[i]);
                } else {
                    if (strcmp(string[i], "^") == 0 && strcmp(stTop(stack->opStack), "^") == 0){
                        stPush(stack->opStack, string[i]);
                    } else {
                        if ((IS_FUNC_2ARG(string[i]) || IS_FUNC_1ARG(string[i])) &&
                            strcmp((stTop(stack->opStack)), "^") == 0) {
                            stPush(stack->opStack, string[i]);
                        } else {
                            stPush(stack->finalStack, stTop(stack->opStack));
                            stPop(stack->opStack);
                            stPush(stack->opStack, string[i]);
                        }
                    }
                }
            } else stPush(stack->opStack, string[i]);
        }

        if (strcmp(string[i], "(") == 0) {
            openBracket++;
            stPush(stack->opStack, string[i]);
        }

        if (strcmp(string[i], ")") == 0) {
            while (strcmp(stTop(stack->opStack), "(")) {
                stPush(stack->finalStack, stTop(stack->opStack));
                stPop(stack->opStack);
            }
            stPop(stack->opStack);
            if (stack->opStack->size  && (IS_FUNC_1ARG(stTop(stack->opStack)) || IS_FUNC_2ARG(stTop(stack->opStack)))) {
                stPush(stack->finalStack, stTop(stack->opStack));
                stPop(stack->opStack);
            }
            openBracket--;
        }
//        DEBUG
        printf("op");
        stPrint(stack->opStack);
        printf("final");
        stPrint(stack->finalStack);
//        DEBUG
    }
    while (stack->opStack->size != 0) {
        stPush(stack->finalStack, stTop(stack->opStack));
        stPop(stack->opStack);
    }

    return stack->finalStack;
}


