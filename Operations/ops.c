#include "ops.h"

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
    // TODO: rework function
    int len = strlen(str);
    return (str[len - 1] == 'j' ? I : 1) * (len == 1 && str[0] == 'j' ? 1 : atof(str));
}

void printNum(double complex value) {
    if (EQI(value, 0)) {
        if (IS_INT(value)) {
            printf("%d", (int) value);
        } else {
            printf("%f", creal(value));
        }
    } else {
        printf("%f + %fi", creal(value), cimag(value));
    }
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
        ERROR("division by zero");
    }
    return a / b;
}

double complex _mod(double complex a, double complex b) {
    if (!(EQI(a, 0) && IS_INT(a) && EQI(b, 0) && IS_INT(b))) {
        ERROR("operation '%%' is defined for integers");
    }
    return (int) a % (int) b;
}

double complex _pwr(double complex a, double complex b) {
    if (!(EQI(a, 0) && EQI(b, 0))) {
        ERROR("operation '^' is not defined for complex numbers");
    }
    if (EQR(a, 0) && creal(b) < 0) {
        ERROR("operation '^' is not defined for negative powers of zero");
    }
    return pow(a, b);
}

double complex _sin(double complex a) {
    return csin(a);
}

double complex _cos(double complex a) {
    return ccos(a);
}

double complex _ln(double complex a) {
    if (EQI(a, 0) && creal(a) < 0) {
        ERROR("function 'ln' for non-complex numbers defined for positive values");
    }
    return clog(a);
}

double complex _log(double complex a) {
    if (EQI(a, 0) && creal(a) < 0) {
        ERROR("function 'log' for non-complex numbers defined for positive values");
    }
    return clog10(a);
}

double complex _sqrt(double complex a) {
    if (EQI(a, 0) && creal(a) < 0) {
        ERROR("function 'sqrt' for non-complex numbers defined for positive values");
    }
    return csqrt(a);
}

double complex _abs(double complex a) {
    if (!EQI(a, 0)) {
        ERROR("function 'abs' is not defined for complex numbers");
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
        ERROR("function 'pow' is not defined for negative powers of zero");
    }
    return cpow(a, b);
}

double complex _min(double complex a, double complex b) {
    if (!(EQI(a, 0) && EQI(b, 0))) {
        ERROR("function 'min' is not defined for complex numbers");
    }
    return (creal(a) < creal(b) ? a : b);
}

double complex _max(double complex a, double complex b) {
    if (!(EQI(a, 0) && EQI(b, 0))) {
        ERROR("function 'max' is not defined for complex numbers");
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