#ifndef ADVANCED_CALCULATOR_OPS_H
#define ADVANCED_CALCULATOR_OPS_H


#include <string.h>
#include <complex.h>

// start enum index for operations
#define OPS_H_OPERATIONS 10
// start enum index for functions with 1 argument
#define OPS_H_FUNCTIONS_1ARG 20
// start enum index for functions with 2 arguments
#define OPS_H_FUNCTIONS_2ARG 40
// start enum index for constants
#define OPS_H_CONSTANTS 60
// enum index for variable
#define OPS_H_VARIABLE 9999

// check if (X) is variable
#define IS_VAR(X) (OPS_H_VARIABLE == getOpID(X))

// check if (X) is operation
#define IS_OPER(X) (OPS_H_OPERATIONS < getOpID(X) && getOpID(X) < OPS_H_FUNCTIONS_1ARG)

// check if (X) is function with 1 argument
#define IS_FUNC_1ARG(X) (OPS_H_FUNCTIONS_1ARG < getOpID(X) && getOpID(X) < OPS_H_FUNCTIONS_2ARG)

// check if (X) is function with 2 arguments
#define IS_FUNC_2ARG(X) (OPS_H_FUNCTIONS_2ARG < getOpID(X) && getOpID(X) < OPS_H_CONSTANTS)

// check if (X) is constant
#define IS_CONST(X) (OPS_H_CONSTANTS < getOpID(X) && getOpID(X) < OPS_H_VARIABLE)

// get priority instantly
#define PRIORITY(X) (getOpPriority(getOpID(X)))

typedef enum {
    OPERATIONS = OPS_H_OPERATIONS,
    PLS, MNS, MUL, DIV, MOD, PWR,
    FUNCTIONS_1ARG = OPS_H_FUNCTIONS_1ARG,
    SIN, COS, LN, SQRT, POW, ABS, EXP, REAL, IMAG, MAG, PHASE,
    FUNCTIONS_2ARG = OPS_H_FUNCTIONS_2ARG,
    LOG, MAX, MIN,
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
    UNARY
} Priority;

OpID getOpID(char *op);

Priority getOpPriority(OpID id);


#endif //ADVANCED_CALCULATOR_OPS_H
