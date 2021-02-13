#ifndef ADVANCED_CALCULATOR_OPS_H
#define ADVANCED_CALCULATOR_OPS_H


#include <string.h>

typedef enum {
    PLS, MNS,
    MUL, DIV, MOD,
    PWR, SIN, COS, LOG, LN, SQRT, POW, ABS, EXP, REAL, IMAG, MAG, PHASE,
    PI, EULER, J,
    VAR
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
