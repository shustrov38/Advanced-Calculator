#ifndef ADVANCED_CALCULATOR_OPS_H
#define ADVANCED_CALCULATOR_OPS_H


#include <string.h>
#include <complex.h>

// start enum index for operations
#define OPS_H_OPERATIONS 10
// start enum index for functions
#define OPS_H_FUNCTIONS 20
// start enum index for constants
#define OPS_H_CONSTANTS 50
// enum index for variable
#define OPS_H_VARIABLE 9999

// check if (X) is operation
#define IS_OPER(X) (OPS_H_OPERATIONS < getOpID(X) && getOpID(X) < OPS_H_FUNCTIONS)

// check if (X) is function
#define IS_FUNC(X) (OPS_H_FUNCTIONS < getOpID(X) && getOpID(X) < OPS_H_CONSTANTS)

// check if (X) is constant
#define IS_CONST(X) (OPS_H_CONSTANTS < getOpID(X) && getOpID(X) < OPS_H_VARIABLE)

// get priority instantly
#define PRIORITY(X) (getOpPriority(getOpID(X)))

typedef enum {
    OPERATIONS = OPS_H_OPERATIONS,
    PLS, MNS, MUL, DIV, MOD, PWR,
    FUNCTIONS = OPS_H_FUNCTIONS,
    SIN, COS, LOG, LN, SQRT, POW, ABS, EXP, REAL, IMAG, MAG, PHASE,
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
    CONST
} Priority;

OpID getOpID(char *op);

Priority getOpPriority(OpID id);


#endif //ADVANCED_CALCULATOR_OPS_H
