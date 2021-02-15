#include "ops.h"

OpID getOpID(char *op) {

    // arithmetic operations
    if (!strcmp(op, "+"))
        return PLS;

    if (!strcmp(op, "-"))
        return MNS;

    if (!strcmp(op, "*"))
        return MUL;

    if (!strcmp(op, "/"))
        return DIV;

    if (!strcmp(op, "%"))
        return MOD;

    if (!strcmp(op, "^"))
        return PWR;

    // functions
    if (!strcmp(op, "sin"))
        return SIN;

    if (!strcmp(op, "cos"))
        return COS;

    if (!strcmp(op, "log"))
        return LOG;

    if (!strcmp(op, "ln"))
        return LN;

    if (!strcmp(op, "sqrt"))
        return SQRT;

    if (!strcmp(op, "pow"))
        return POW;

    if (!strcmp(op, "abs"))
        return ABS;

    if (!strcmp(op, "exp"))
        return EXP;

    if (!strcmp(op, "real"))
        return REAL;

    if (!strcmp(op, "imag"))
        return IMAG;

    if (!strcmp(op, "mag"))
        return MAG;

    if (!strcmp(op, "phase"))
        return PHASE;

    if (!strcmp(op, "min"))
        return MIN;

    if (!strcmp(op, "max"))
        return MAX;

    // constants
    if (!strcmp(op, "PI"))
        return PI;

    if (!strcmp(op, "e"))
        return EULER;

    if (!strcmp(op, "j"))
        return J;

    // standard variable
    return VAR;
}

Priority getOpPriority(OpID id) {
    switch (id) {
        case PLS:
        case MNS:
            return SUM;
        case MUL:
        case DIV:
        case MOD:
            return PROD;
        case SIN:
        case COS:
        case LOG:
        case LN:
        case SQRT:
        case POW:
        case ABS:
        case EXP:
        case REAL:
        case IMAG:
        case MAG:
        case PHASE:
        case MIN:
        case MAX:
            return FUNC;
        case PWR:
            return POWER;
        default:
            return NONE;
    }
}

double complex toComplex(char *str) {
    return atof(str) * (str[strlen(str) - 1] == 'j' ? I : 1);
}

void printError(const char *error) {
    fprintf(stderr, "%s", error);
    exit(-1);
};

double complex __sum(double complex a, double complex b) {
    return a + b;
}

double complex __sub(double complex a, double complex b) {
    return a - b;
}

double complex __mul(double complex a, double complex b) {
    return a * b;
}

double complex __div(double complex a, double complex b) {
    if (!EQC(b, 0)) {
        return a / b;
    } else {
        printError("division by zero");
    }
}

double complex __mod(double complex a, double complex b) {
    if (EQI(a, 0) && IS_INT(a) && EQI(b, 0) && IS_INT(b)) {
        return (int)a % (int)b;
    } else {
        printError("function '%%' is defined for integers");
    }
}

double complex __pwr(double complex a, double complex b) {
    if (EQI(a, 0) && EQI(b, 0)) {
        if (EQR(a, 0) && creal(b) < 0) {
            printError("function '^' is not defined for negative powers of zero");
        }
        return pow(a, b);
    } else {
        printError("function '^' is not defined for complex numbers");
    }
}