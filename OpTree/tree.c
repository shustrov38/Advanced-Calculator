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

    strcpy(node->value, stTop(stack));
    stPop(stack);

    if (IS_OPER(node->value) || IS_UOPER(node->value)) {
        node->state = OPERATION;
    } else if (IS_FUNC_1ARG(node->value)) {
        node->state = FUNCTION1;
    } else if (IS_FUNC_2ARG(node->value)) {
        node->state = FUNCTION2;
    } else /* var or const */ {
        node->state = BASIC;
    }

    if (node->state != BASIC) {
        node->right = nodeInit(node->elementSize);
        opTreeGen(node->right, stack);
        // unary and func1 require one argument
        if (node->state != FUNCTION1 && !IS_UOPER(node->value)) {
            node->left = nodeInit(node->elementSize);
            opTreeGen(node->left, stack);
        }
    }
}

double complex opTreeCalc(Node *node, Expression *e, int n) {
    if (node == NULL) return 0;

    double complex a = opTreeCalc(node->left, e, n);
    double complex b = opTreeCalc(node->right, e, n);

    switch (getOpID(node->value)) {
        case UMNS:
            return _umns(b, e);
        case PLS:
            return _sum(a, b, e);
        case MNS:
            return _sub(a, b, e);
        case MUL:
            return _mul(a, b, e);
        case DIV:
            return _div(a, b, e);
        case MOD:
            return _mod(a, b, e);
        case PWR:
            return _pwr(a, b, e);
        case AND:
            return _and(a, b, e);
        case OR:
            return _or(a, b, e);
        case XOR:
            return _xor(a, b, e);
        case SIN:
            return _sin(b, e);
        case COS:
            return _cos(b, e);
        case LN:
            return _ln(b, e);
        case LOG:
            return _log(b, e);
        case SQRT:
            return _sqrt(b, e);
        case ABS:
            return _abs(b, e);
        case EXP:
            return _exp(b, e);
        case REAL:
            return _real(b, e);
        case IMAG:
            return _imag(b, e);
        case MAG:
            return _mag(b, e);
        case PHASE:
            return _phase(b, e);
        case POW:
            return _pow(a, b, e);
        case MAX:
            return _max(a, b, e);
        case MIN:
            return _min(a, b, e);
        case PI:
            return _pi();
        case EULER:
            return _euler();
        case J:
            return _j();
        case VAR:
            for (int i = 0; i < n; ++i) {
                if (!strlen(e[i].varName)) continue;
                if (!strcmp(node->value, e[i].varName)) {
                    return e[i].value;
                }
            }
        default:
            return toComplex(node->value);
    }
}

void opTreePrint(Node *node, Node *parent) {
    if (node == NULL) return;
    int need;
    switch (node->state) {
        case OPERATION:
            need = (parent != NULL) && ((PRIORITY(node->value) == SUM && PRIORITY(parent->value) == PROD) ||
                                        (getOpID(node->value) != VAR && getOpID(node->value) != NUM &&
                                         PRIORITY(parent->value) == POWER));
            if (need) printf("(");
            opTreePrint(node->left, node);
            printf("%s", node->value);
            opTreePrint(node->right, node);
            if (need) printf(")");
            break;
        case FUNCTION1:
            printf("%s(", node->value);
            opTreePrint(node->right, node);
            printf(")");
            break;
        case FUNCTION2:
            printf("%s(", node->value);
            opTreePrint(node->left, node);
            printf(",");
            opTreePrint(node->right, node);
            printf(")");
            break;
        case BASIC:
            printf("%s", node->value);
            break;
    }
}
