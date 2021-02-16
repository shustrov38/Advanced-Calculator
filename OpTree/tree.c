#include "tree.h"

Node *nodeInit(int elementSize) {
    Node *node = (Node *) malloc(sizeof(Node));
    assert(node != NULL && "bad mem allocate");
    node->elementSize = elementSize;
    node->value = (char *) malloc(node->elementSize);
    assert(node->value != NULL && "bad mem allocate");
    node->left = node->right = NULL;
    return node;
}

void opTreeGen(Node *node, Stack *stack) {
    assert(node != NULL && "bad root");
    assert(stack != NULL && stack->size != 0 && "bad stack");

    // recursive end condition
    if (stack->size == 0) return;

    char *tmp = (char *) malloc(stack->elementSize);
    strcpy(tmp, stTop(stack));
    stPop(stack);

    if (IS_OPER(tmp)) {
        node->state = OPERATION;
    } else if (IS_FUNC_1ARG(tmp)) {
        node->state = FUNCTION1;
    } else if (IS_FUNC_2ARG(tmp)) {
        node->state = FUNCTION2;
    } else /* var or const */ {
        node->state = BASIC;
    }

    switch (node->state) {
        case OPERATION:
        case FUNCTION2:
            strcpy(node->value, tmp);
            node->right = nodeInit(node->elementSize);
            opTreeGen(node->right, stack);
            node->left = nodeInit(node->elementSize);
            opTreeGen(node->left, stack);
            break;
        case FUNCTION1:
            strcpy(node->value, tmp);
            node->right = nodeInit(node->elementSize);
            opTreeGen(node->right, stack);
            break;
        case BASIC:
            strcpy(node->value, tmp);
            break;
    }
}

double complex opTreeCalc(Node *node) {
    if (node == NULL) return 0;
    double complex a = opTreeCalc(node->right), b = opTreeCalc(node->left);
    switch (getOpID(node->value)) {
        case PLS:
            return _sum(a, b);
        case MNS:
            return _sub(a, b);
        case MUL:
            return _mul(a, b);
        case DIV:
            return _div(a, b);
        case MOD:
            return _mod(a, b);
        case PWR:
            return _pwr(a, b);
        case SIN:
            return _sin(a);
        case COS:
            return _cos(a);
        case LN:
            return _ln(a);
        case LOG:
            return _log(a);
        case SQRT:
            return _sqrt(a);
        case ABS:
            return _abs(a);
        case EXP:
            return _exp(a);
        case REAL:
            return _real(a);
        case IMAG:
            return _imag(a);
        case MAG:
            return _mag(a);
        case PHASE:
            return _phase(a);
        case POW:
            return _pow(a, b);
        case MAX:
            return _max(a, b);
        case MIN:
            return _min(a, b);
        case PI:
            return _pi();
        case EULER:
            return _euler();
        case J:
            return _j();
        case VAR:
            return toComplex(node->value);
        default:
            return 0;
    }
}

void opTreePrint(Node *node) {
    if (node == NULL) return;
    switch (node->state) {
        case OPERATION:
            printf("(");
            opTreePrint(node->right);
            printf("%s", node->value);
            opTreePrint(node->left);
            printf(")");
            break;
        case FUNCTION1:
            printf("%s(", node->value);
            opTreePrint(node->right);
            printf(")");
            break;
        case FUNCTION2:
            printf("%s(", node->value);
            opTreePrint(node->right);
            printf(",");
            opTreePrint(node->left);
            printf(")");
            break;
        case BASIC:
            printf("%s", node->value);
            break;
    }
}
