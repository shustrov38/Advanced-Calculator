#include "ops.h"

#define eps 1e-6

// check real complex part of X to integer
#define IS_INT(X) (fabs(creal(X) - (int)(X)) <= eps)
// check real complex part of X to Y
#define EQR(X, Y) (fabs(creal(X) - (Y)) <= eps)
// check imag complex part of X to Y
#define EQI(X, Y) (fabs(cimag(X) - (Y)) <= eps)
// check for equal two complex numbers
#define EQC(X, Y) (EQR(X, Y) && EQI(X, Y))
// print error
#define ERROR(...) fprintf(stderr, __VA_ARGS__); exit(-1)

OpID getOpID(char *op) {
    // extra options
    if (!strcmp(op, "="))
        return PLS;

    if (!strcmp(op, "("))
        return OPB;

    if (!strcmp(op, ")"))
        return CLB;

    if (!strcmp(op, ","))
        return COM;

    if ('0' <= op[0] && op[0] <= '9')
        return NUM;

    // arithmetic operations
    if (!strcmp(op, "--"))
        return UMNS;

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

    if (!strcmp(op, "&"))
        return AND;

    if (!strcmp(op, "|"))
        return OR;

    if (!strcmp(op, "@"))
        return XOR;

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
    if (!strcmp(op, "pi"))
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
        case OR:
        case XOR:
            return SUM;
        case MUL:
        case DIV:
        case MOD:
        case AND:
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
        case UMNS:
            return UNARY;
        default:
            return NONE;
    }
}

double complex toComplex(char *str) {
    int e = (int) strlen(str);
    return (e == 1 && str[0] == 'j' ? 1 : atof(str)) *  (str[e - 1] == 'j' ? I : 1);
}

void printNum(double complex value) {
    if (EQI(value, 0)) {
        if (IS_INT(value)) {
            printf("%d", (int) value);
        } else {
            printf("%f", creal(value));
        }
    } else {
        printf("%f %c %fi", creal(value), (cimag(value) < 0 ? '-' : '+'), fabs(cimag(value)));
    }
}

double complex _umns(double complex a) {
    return -a;
}

double complex _sum(double complex a, double complex b) {
    return a + b;
}

double complex _sub(double complex a, double complex b) {
    return a - b;
}

double complex _mul(double complex a, double complex b) {
    return a * b;
}

double complex _div(double complex a, double complex b) {
    if (EQC(b, 0)) {
        ERROR("Division by zero.");
    }
    return a / b;
}

double complex _mod(double complex a, double complex b) {
    int left = !EQI(a, 0);
    int right = !EQI(b, 0);
    if (left || right) {
        fprintf(stderr, "Operation '%%' is not define for complex operands. ");
        if (left && right) {
            ERROR("Check both operands.");
        } else {
            ERROR("Check %s operand.", (left ? "left" : "right"));
        }
    }
    return (int) a % (int) b;
}

double complex _pwr(double complex a, double complex b) {
    int left = !EQI(a, 0);
    int right = !EQI(b, 0);
    if (left || right) {
        fprintf(stderr, "Operation '^' is not define for complex operands. ");
        if (left && right) {
            ERROR("Check both operands.");
        } else {
            ERROR("Check %s operand.", (left ? "left" : "right"));
        }
    }
    if (EQR(a, 0) && creal(b) < 0) {
        ERROR("Operation '^' is not defined for negative powers of zero");
    }
    return pow(a, b);
}

double complex _and(double complex a, double complex b) {
    int left = !(EQI(a, 0) && IS_INT(a));
    int right = !(EQI(b, 0) && IS_INT(b));
    if (left || right) {
        fprintf(stderr, "Operation '&' is not define for complex operands. ");
        if (left && right) {
            ERROR("Check both operands.");
        } else {
            ERROR("Check %s operand.", (left ? "left" : "right"));
        }
    }
    return (int)a & (int)b;
}

double complex _or(double complex a, double complex b) {
    int left = !(EQI(a, 0) && IS_INT(a));
    int right = !(EQI(b, 0) && IS_INT(b));
    if (left || right) {
        fprintf(stderr, "Operation '|' is not define for complex operands. ");
        if (left && right) {
            ERROR("Check both operands.");
        } else {
            ERROR("Check %s operand.", (left ? "left" : "right"));
        }
    }
    return (int)a | (int)b;
}

double complex _xor(double complex a, double complex b) {
    int left = !(EQI(a, 0) && IS_INT(a));
    int right = !(EQI(b, 0) && IS_INT(b));
    if (left || right) {
        fprintf(stderr, "Operation '@' is not define for complex operands. ");
        if (left && right) {
            ERROR("Check both operands.");
        } else {
            ERROR("Check %s operand.", (left ? "left" : "right"));
        }
    }
    return (int)a ^ (int)b;
}

double complex _sin(double complex a) {
    return csin(a);
}

double complex _cos(double complex a) {
    return ccos(a);
}

double complex _ln(double complex a) {
    if (EQI(a, 0) && creal(a) < 0) {
        ERROR("Function 'ln()' for non-complex numbers defined for positive arguments.");
    }
    return clog(a);
}

double complex _log(double complex a) {
    if (EQI(a, 0) && creal(a) < 0) {
        ERROR("Function 'log()' for non-complex numbers defined for positive arguments.");
    }
    return clog10(a);
}

double complex _sqrt(double complex a) {
    if (EQI(a, 0) && creal(a) < 0) {
        ERROR("Function 'sqrt()' for non-complex numbers defined only for positive arguments.");
    }
    return csqrt(a);
}

double complex _abs(double complex a) {
    if (!EQI(a, 0)) {
        ERROR("Function 'abs()' is not defined for complex arguments.");
    }
    return fabs(creal(a));
}

double complex _exp(double complex a) {
    return cexp(a);
}

double complex _real(double complex a) {
    return creal(a);
}

double complex _imag(double complex a) {
    return cimag(a);
}

double complex _mag(double complex a) {
    return cabs(a);
}

double complex _phase(double complex a) {
    return carg(a);
}

double complex _pow(double complex a, double complex b) {
    if (EQR(a, 0) && EQI(a, 0) && creal(b) < 0 && EQI(b, 0)) {
        ERROR("Function 'pow()' is not defined for negative powers of zero");
    }
    return cpow(a, b);
}

double complex _min(double complex a, double complex b) {
    int left = !EQI(a, 0);
    int right = !EQI(b, 0);
    if (left || right) {
        fprintf(stderr, "Function 'min()' is not define for complex arguments. ");
        if (left && right) {
            ERROR("Check both arguments.");
        } else {
            ERROR("Check %s argument.", (left ? "left" : "right"));
        }
    }
    return (creal(a) < creal(b) ? a : b);
}

double complex _max(double complex a, double complex b) {
    int left = !EQI(a, 0);
    int right = !EQI(b, 0);
    if (left || right) {
        fprintf(stderr, "Function 'max()' is not define for complex arguments. ");
        if (left && right) {
            ERROR("Check both arguments.");
        } else {
            ERROR("Check %s argument.", (left ? "left" : "right"));
        }
    }
    return (creal(a) > creal(b) ? a : b);
}

double complex _pi() {
    return M_PI;
}

double complex _euler() {
    return M_E;
}

double complex _j() {
    return I;
}