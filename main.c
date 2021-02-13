#include <stdio.h>
#include <string.h>

#include "Stack/stack.h"

typedef enum {
    PLUS,
    MINUS,
    VAR
} Operation;

typedef enum {
    NONE,
    SUM,
    PROD,
    FUNC,
    POWER,
    UNARY
} Priority;

Operation getOpId(char *op) {
    Operation res;
    if (!strcmp(op, "+")) {
        return PLUS;
    }
    if (!strcmp(op, "-")) {
        return MINUS;
    }
    return VAR;

}

Priority getOpPri(Operation op) {
    switch (op) {
        case PLUS:
        case MINUS:
            return SUM;
        default:
            return NONE;
    }
}

int main() {

}
