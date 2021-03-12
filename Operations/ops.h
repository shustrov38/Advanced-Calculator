#ifndef ADVANCED_CALCULATOR_OPS_H
#define ADVANCED_CALCULATOR_OPS_H


#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// start enum index for operations
#define OPS_H_OPERATIONS_U 100
#define OPS_H_OPERATIONS_B 200
// start enum index for functions with 1 argument
#define OPS_H_FUNCTIONS_1ARG 300
// start enum index for functions with 2 arguments
#define OPS_H_FUNCTIONS_2ARG 400
// start enum index for constants
#define OPS_H_CONSTANTS 500
// enum index for variable
#define OPS_H_VARIABLE 9999

// get priority instantly
#define PRIORITY(X) (getOpPriority(getOpID(X)))

// check if (X) is variable
#define IS_VAR(X) (OPS_H_VARIABLE == getOpID(X))

//check if (X) is number
#define IS_NUM(X) (NUM == getOpID(X))

// check if (X) is operation
#define IS_UOPER(X) (OPS_H_OPERATIONS_U < getOpID(X) && getOpID(X) < OPS_H_OPERATIONS_B)

// check if (X) is operation
#define IS_OPER(X) (OPS_H_OPERATIONS_B < getOpID(X) && getOpID(X) < OPS_H_FUNCTIONS_1ARG)

// check if (X) is power operation ('^')
#define IS_PWR(X) (PRIORITY(X) == POWER)

// check if (X) is function with 1 argument
#define IS_FUNC_1ARG(X) (OPS_H_FUNCTIONS_1ARG < getOpID(X) && getOpID(X) < OPS_H_FUNCTIONS_2ARG)

// check if (X) is function with 2 arguments
#define IS_FUNC_2ARG(X) (OPS_H_FUNCTIONS_2ARG < getOpID(X) && getOpID(X) < OPS_H_CONSTANTS)

// check if (X) is function (arguments doesn't matter)
#define IS_FUNC(X) (PRIORITY(X) == FUNC)

// check if (X) is constant
#define IS_CONST(X) (OPS_H_CONSTANTS < getOpID(X) && getOpID(X) < OPS_H_VARIABLE)

typedef enum {
    EQL, OPB, CLB, COM, NUM,
    OPERATIONS_U = OPS_H_OPERATIONS_U,
    UMNS, FLIP, FACT,                   // unary operations
    OPERATIONS_B = OPS_H_OPERATIONS_B,
    PLS, MNS, MUL, DIV, MOD, PWR,       // common operations
    AND, OR, XOR,                       // binary operations
    FUNCTIONS_1ARG = OPS_H_FUNCTIONS_1ARG,
    SIN, COS, TG, CTG, RAD, FLR, CEIL, LN, LOG, SQRT, ABS, EXP, REAL, IMAG, MAG, PHASE,
    FUNCTIONS_2ARG = OPS_H_FUNCTIONS_2ARG,
    POW, MAX, MIN, RND,
    CONSTANTS = OPS_H_CONSTANTS,
    PI, EULER, J,
    VAR = OPS_H_VARIABLE
} OpID;

typedef enum {
    NONE,
    SUM,
    PROD,
    FUNC,
    POWER,
    UNARY,
    FACTORIAL
} Priority;

OpID getOpID(char *op);

Priority getOpPriority(OpID id);


#endif //ADVANCED_CALCULATOR_OPS_H
