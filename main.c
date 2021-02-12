#include <stdio.h>
#include <string.h>

#include "Stack/stack.h"

//typedef enum {
//    PLUS,
//    MINUS,
//    NONE
//} Operation;
//
//typedef enum {
//    BIN_PLUS,
//    BIN_MINUS
//} Priority;
//
//Operation getOpId(char *oper) {
//    Operation res;
//    if (!strcmp(oper, "+")) {
//        return PLUS;
//    }
//    if (!strcmp(oper, "-")) {
//        return MINUS;
//    }
//    return NONE;
//
//}
//
//Priority getOpPri(Operation oper) {
//    switch (oper) {
//        case PLUS:
//            return BIN_PLUS;
//        case MINUS:
//            return BIN_MINUS;
//        default:
//            return 0;
//    }
//}

int main() {
    Stack *stack = stCreate(sizeof(char[10]));
    stPrint(stack);
    stPush(stack, "kek");
    stPush(stack, "abc");
    stPush(stack, "lol");
    stPrint(stack);
    stPop(stack);
    stPrint(stack);
}
