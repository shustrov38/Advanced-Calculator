#ifndef ADVANCED_CALCULATOR_OPS_H
#define ADVANCED_CALCULATOR_OPS_H


#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define _GNU_SOURCE
#include <complex.h>

#define _USE_MATH_DEFINES
#include <math.h>

// start enum index for operations
#define OPS_H_OPERATIONS_U 10
#define OPS_H_OPERATIONS_B 20
// start enum index for functions with 1 argument
#define OPS_H_FUNCTIONS_1ARG 40
// start enum index for functions with 2 arguments
#define OPS_H_FUNCTIONS_2ARG 60
// start enum index for constants
#define OPS_H_CONSTANTS 80
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
    UMNS,                           // unary operations
    OPERATIONS_B = OPS_H_OPERATIONS_B,
    PLS, MNS, MUL, DIV, MOD, PWR,   // common operations
    AND, OR, XOR,                   // binary operations
    FUNCTIONS_1ARG = OPS_H_FUNCTIONS_1ARG,
    SIN, COS, LN, LOG, SQRT, ABS, EXP, REAL, IMAG, MAG, PHASE,
    FUNCTIONS_2ARG = OPS_H_FUNCTIONS_2ARG,
    POW, MAX, MIN,
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

double complex toComplex(char *str);

void printNum(double complex value);

#pragma region OPERATIONS

double complex _umns(double complex a);

double complex _sum(double complex a, double complex b);

double complex _sub(double complex a, double complex b);

double complex _mul(double complex a, double complex b);

double complex _div(double complex a, double complex b);

double complex _mod(double complex a, double complex b);

double complex _pwr(double complex a, double complex b);

double complex _and(double complex a, double complex b);

double complex _or(double complex a, double complex b);

double complex _xor(double complex a, double complex b);

#pragma endregion OPERATIONS

#pragma region FUNCTIONS_1ARG

double complex _sin(double complex a);

double complex _cos(double complex a);

double complex _ln(double complex a);

double complex _log(double complex a);

double complex _sqrt(double complex a);

double complex _abs(double complex a);

double complex _exp(double complex a);

double complex _real(double complex a);

double complex _imag(double complex a);

double complex _mag(double complex a);

double complex _phase(double complex a);

#pragma endregion FUNCTIONS_1ARG

#pragma region FUNCTIONS_2ARG

double complex _pow(double complex a, double complex b);

double complex _min(double complex a, double complex b);

double complex _max(double complex a, double complex b);

#pragma endregion FUNCTIONS_2ARG

#pragma region CONSTANTS

double complex _pi();

double complex _euler();

double complex _j();

#pragma endregion CONSTANTS


#endif //ADVANCED_CALCULATOR_OPS_H
