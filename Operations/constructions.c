#include "constructions.h"

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

double complex toComplex(char *str) {
    int e = (int) strlen(str);
    return (e == 1 && str[0] == 'j' ? 1 : atof(str)) * (str[e - 1] == 'j' ? I : 1);
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

double complex fixNegativeZero(double complex a) {
    if (EQI(a, 0)) a = creal(a) + 0 * I;
    if (EQC(a, 0)) a = 0 + cimag(a);
    return a;
}

void printFormula(Expression *e) {
    fprintf(stderr, "%s\n", e->rawFormula);
}

double complex _umns(double complex a, Expression *e) {
    return -a;
}

double complex _flip(double complex a, Expression *e) {
    if (!EQI(a, 0)) {
        printFormula(e);
        ERROR("Operation '~' is not define for complex operands. ");
    }
    if (!IS_INT(a)) {
        printFormula(e);
        ERROR("Operation '~' is not define for floating point operands. ");
    }
    return ~(int) a;
}

double complex _fact(double complex a, Expression *e) {
    if (!EQI(a, 0)) {
        printFormula(e);
        ERROR("Operation '!' is not define for complex operands. ");
    }
    if (!IS_INT(a)) {
        printFormula(e);
        ERROR("Operation '!' is not define for floating point operands. ");
    }
    int res = 1;
    for (int i = 2; i <= (int) a; ++i) {
        res *= i;
    }
    return res;
}

double complex _sum(double complex a, double complex b, Expression *e) {
    return a + b;
}

double complex _sub(double complex a, double complex b, Expression *e) {
    return a - b;
}

double complex _mul(double complex a, double complex b, Expression *e) {
    return a * b;
}

double complex _div(double complex a, double complex b, Expression *e) {
    if (EQC(b, 0)) {
        printFormula(e);
        ERROR("Division by zero.");
    }
    return a / b;
}

double complex _mod(double complex a, double complex b, Expression *e) {
    int left = !EQI(a, 0);
    int right = !EQI(b, 0);
    if (left || right) {
        printFormula(e);
        fprintf(stderr, "Operation '%%' is not define for complex operands. ");
        if (left && right) {
            ERROR("Check both operands.");
        } else {
            ERROR("Check %s operand.", (left ? "left" : "right"));
        }
    }
    left = !IS_INT(a);
    right = !IS_INT(b);
    if (left || right) {
        printFormula(e);
        fprintf(stderr, "Operation '%%' is not define for floating point operands. ");
        if (left && right) {
            ERROR("Check both operands.");
        } else {
            ERROR("Check %s operand.", (left ? "left" : "right"));
        }
    }
    return (int) a % (int) b;
}

double complex _pwr(double complex a, double complex b, Expression *e) {
    int left = !EQI(a, 0);
    int right = !EQI(b, 0);
    if (left || right) {
        printFormula(e);
        fprintf(stderr, "Operation '^' is not define for complex operands. ");
        if (left && right) {
            ERROR("Check both operands.");
        } else {
            ERROR("Check %s operand.", (left ? "left" : "right"));
        }
    }
    if (EQR(a, 0) && creal(b) < 0) {
        printFormula(e);
        ERROR("Operation '^' is not defined for negative powers of zero");
    }
    return pow(a, b);
}

double complex _and(double complex a, double complex b, Expression *e) {
    int left = !EQI(a, 0);
    int right = !EQI(b, 0);
    if (left || right) {
        printFormula(e);
        fprintf(stderr, "Operation '&' is not define for complex operands. ");
        if (left && right) {
            ERROR("Check both operands.");
        } else {
            ERROR("Check %s operand.", (left ? "left" : "right"));
        }
    }
    left = !IS_INT(a);
    right = !IS_INT(b);
    if (left || right) {
        printFormula(e);
        fprintf(stderr, "Operation '&' is not define for floating point operands. ");
        if (left && right) {
            ERROR("Check both operands.");
        } else {
            ERROR("Check %s operand.", (left ? "left" : "right"));
        }
    }
    return (int) a & (int) b;
}

double complex _or(double complex a, double complex b, Expression *e) {
    int left = !EQI(a, 0);
    int right = !EQI(b, 0);
    if (left || right) {
        printFormula(e);
        fprintf(stderr, "Operation '|' is not define for complex operands. ");
        if (left && right) {
            ERROR("Check both operands.");
        } else {
            ERROR("Check %s operand.", (left ? "left" : "right"));
        }
    }
    left = !IS_INT(a);
    right = !IS_INT(b);
    if (left || right) {
        printFormula(e);
        fprintf(stderr, "Operation '|' is not define for floating point operands. ");
        if (left && right) {
            ERROR("Check both operands.");
        } else {
            ERROR("Check %s operand.", (left ? "left" : "right"));
        }
    }
    return (int) a | (int) b;
}

double complex _xor(double complex a, double complex b, Expression *e) {
    int left = !EQI(a, 0);
    int right = !EQI(b, 0);
    if (left || right) {
        printFormula(e);
        fprintf(stderr, "Operation '@' is not define for complex operands. ");
        if (left && right) {
            ERROR("Check both operands.");
        } else {
            ERROR("Check %s operand.", (left ? "left" : "right"));
        }
    }
    left = !IS_INT(a);
    right = !IS_INT(b);
    if (left || right) {
        printFormula(e);
        fprintf(stderr, "Operation '@' is not define for floating point operands. ");
        if (left && right) {
            ERROR("Check both operands.");
        } else {
            ERROR("Check %s operand.", (left ? "left" : "right"));
        }
    }
    return (int) a ^ (int) b;
}

double complex _sin(double complex a, Expression *e) {
    return csin(a);
}

double complex _cos(double complex a, Expression *e) {
    return ccos(a);
}

double complex _tg(double complex a, Expression *e) {
    if (EQC(_cos(a, e), 0)) {
        printFormula(e);
        ERROR("Function 'tg()' is not defined for phase pi/2 + pi*k.");
    }
    return _sin(a, e) / _cos(a, e);
}

double complex _ctg(double complex a, Expression *e) {
    if (EQC(_sin(a, e), 0)) {
        printFormula(e);
        ERROR("Function 'ctg()' is not defined for phase pi*k.");
    }
    return _cos(a, e) / _sin(a, e);
}

double complex _rad(double complex a, Expression *e) {
    if (!EQI(a, 0)) {
        printFormula(e);
        ERROR("Function 'rad()' is not define for complex argument.");
    }
    return a / 180 * _pi();
}

double complex _floor(double complex a, Expression *e) {
    if (!EQI(a, 0)) {
        printFormula(e);
        ERROR("Function 'floor()' is not define for complex argument.");
    }
    return floor(a);
}

double complex _ceil(double complex a, Expression *e) {
    if (!EQI(a, 0)) {
        printFormula(e);
        ERROR("Function 'ceil()' is not define for complex argument.");
    }
    return ceil(a);
}

double complex _ln(double complex a, Expression *e) {
    if (EQI(a, 0) && creal(a) < 0) {
        printFormula(e);
        ERROR("Function 'ln()' for non-complex numbers defined for positive arguments.");
    }
    return clog(a);
}

double complex _log(double complex a, Expression *e) {
    if (EQI(a, 0) && creal(a) < 0) {
        printFormula(e);
        ERROR("Function 'log()' for non-complex numbers defined for positive arguments.");
    }
    return clog10(a);
}

double complex _sqrt(double complex a, Expression *e) {
    if (EQI(a, 0) && EQR(a, -1)) {
        return csqrt(a);
    }
    if (EQI(a, 0) && creal(a) < 0) {
        printFormula(e);
        ERROR("Function 'sqrt()' for non-complex numbers defined only for positive arguments.");
    }
    return csqrt(a);
}

double complex _abs(double complex a, Expression *e) {
    if (!EQI(a, 0)) {
        printFormula(e);
        ERROR("Function 'abs()' is not defined for complex arguments.");
    }
    return fabs(creal(a));
}

double complex _exp(double complex a, Expression *e) {
    return cexp(a);
}

double complex _real(double complex a, Expression *e) {
    return creal(a);
}

double complex _imag(double complex a, Expression *e) {
    return cimag(a);
}

double complex _mag(double complex a, Expression *e) {
    return cabs(a);
}

double complex _phase(double complex a, Expression *e) {
    return carg(a);
}

double complex _pow(double complex a, double complex b, Expression *e) {
    if (EQR(a, 0) && EQI(a, 0) && creal(b) < 0 && EQI(b, 0)) {
        printFormula(e);
        ERROR("Function 'pow()' is not defined for negative powers of zero");
    }
    return cpow(a, b);
}

double complex _min(double complex a, double complex b, Expression *e) {
    int left = !EQI(a, 0);
    int right = !EQI(b, 0);
    if (left || right) {
        printFormula(e);
        fprintf(stderr, "Function 'min()' is not defined for complex arguments. ");
        if (left && right) {
            ERROR("Check both arguments.");
        } else {
            ERROR("Check %s argument.", (left ? "left" : "right"));
        }
    }
    return (creal(a) < creal(b) ? a : b);
}

double complex _max(double complex a, double complex b, Expression *e) {
    int left = !EQI(a, 0);
    int right = !EQI(b, 0);
    if (left || right) {
        printFormula(e);
        fprintf(stderr, "Function 'max()' is not defined for complex arguments. ");
        if (left && right) {
            ERROR("Check both arguments.");
        } else {
            ERROR("Check %s argument.", (left ? "left" : "right"));
        }
    }
    return (creal(a) > creal(b) ? a : b);
}

double complex _rand(double complex a, double complex b, Expression *e) {
    int left = !EQI(a, 0);
    int right = !EQI(b, 0);
    if (left || right) {
        printFormula(e);
        fprintf(stderr, "Function 'rand()' is not defined for complex arguments. ");
        if (left && right) {
            ERROR("Check both arguments.");
        } else {
            ERROR("Check %s argument.", (left ? "left" : "right"));
        }
    }
    left = !IS_INT(a);
    right = !IS_INT(b);
    if (left || right) {
        printFormula(e);
        fprintf(stderr, "Function 'rand()' is not defined for floating point arguments. ");
        if (left && right) {
            ERROR("Check both operands.");
        } else {
            ERROR("Check %s operand.", (left ? "left" : "right"));
        }
    }
    return (int) a + rand() % ((int) b - (int) a + 1);
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