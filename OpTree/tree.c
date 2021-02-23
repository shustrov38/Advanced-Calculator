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

double complex opTreeCalc(Node *node, Expression *e, int ind, int n) {
    if (node == NULL) return 0;

    double complex a = fixNegativeZero(opTreeCalc(node->left, e, ind, n));
    double complex b = fixNegativeZero(opTreeCalc(node->right, e, ind, n));

    switch (getOpID(node->value)) {
        case UMNS:
            return _umns(b, &e[ind]);
        case FLIP:
            return _flip(b, &e[ind]);
        case FACT:
            return _fact(b, &e[ind]);
        case PLS:
            return _sum(a, b, &e[ind]);
        case MNS:
            return _sub(a, b, &e[ind]);
        case MUL:
            return _mul(a, b, &e[ind]);
        case DIV:
            return _div(a, b, &e[ind]);
        case MOD:
            return _mod(a, b, &e[ind]);
        case PWR:
            return _pwr(a, b, &e[ind]);
        case AND:
            return _and(a, b, &e[ind]);
        case OR:
            return _or(a, b, &e[ind]);
        case XOR:
            return _xor(a, b, &e[ind]);
        case SIN:
            return _sin(b, &e[ind]);
        case COS:
            return _cos(b, &e[ind]);
        case TG:
            return _tg(b, &e[ind]);
        case CTG:
            return _ctg(b, &e[ind]);
        case RAD:
            return _rad(b, &e[ind]);
        case FLR:
            return _floor(b, &e[ind]);
        case CEIL:
            return _ceil(b, &e[ind]);
        case LN:
            return _ln(b, &e[ind]);
        case LOG:
            return _log(b, &e[ind]);
        case SQRT:
            return _sqrt(b, &e[ind]);
        case ABS:
            return _abs(b, &e[ind]);
        case EXP:
            return _exp(b, &e[ind]);
        case REAL:
            return _real(b, &e[ind]);
        case IMAG:
            return _imag(b, &e[ind]);
        case MAG:
            return _mag(b, &e[ind]);
        case PHASE:
            return _phase(b, &e[ind]);
        case POW:
            return _pow(a, b, &e[ind]);
        case MAX:
            return _max(a, b, &e[ind]);
        case MIN:
            return _min(a, b, &e[ind]);
        case RND:
            return _rand(a, b, &e[ind]);
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
