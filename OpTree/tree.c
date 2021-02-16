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

    if (IS_OPER(node->value)) {
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
        if (node->state != FUNCTION1) {
            node->left = nodeInit(node->elementSize);
            opTreeGen(node->left, stack);
        }
    }
}

double complex opTreeCalc(Node *node) {
    if (node == NULL) return 0;
    double complex a = opTreeCalc(node->left), b = opTreeCalc(node->right);
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
            return _sin(b);
        case COS:
            return _cos(b);
        case LN:
            return _ln(b);
        case LOG:
            return _log(b);
        case SQRT:
            return _sqrt(b);
        case ABS:
            return _abs(b);
        case EXP:
            return _exp(b);
        case REAL:
            return _real(b);
        case IMAG:
            return _imag(b);
        case MAG:
            return _mag(b);
        case PHASE:
            return _phase(b);
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
            // here must be search of the variable
            return toComplex(node->value);
        default:
            return toComplex(node->value);
    }
}

void opTreePrint(Node *node) {
    if (node == NULL) return;
    switch (node->state) {
        case OPERATION:
            printf("(");
            opTreePrint(node->left);
            printf("%s", node->value);
            opTreePrint(node->right);
            printf(")");
            break;
        case FUNCTION1:
            printf("%s(", node->value);
            opTreePrint(node->right);
            printf(")");
            break;
        case FUNCTION2:
            printf("%s(", node->value);
            opTreePrint(node->left);
            printf(",");
            opTreePrint(node->right);
            printf(")");
            break;
        case BASIC:
            printf("%s", node->value);
            break;
    }
}

void exampleRun() {
    int size = sizeof(char[10]);
    Stack *stack = stCreate(size);
    stPush(stack, "e");
    stPush(stack, "1.23");
    stPush(stack, "+");
    stPush(stack, "ln");
    stPush(stack, "sin");
    stPrint(stack);
    Node *root = nodeInit(size);
    opTreeGen(root, stack);
    opTreePrint(root);
    double complex result = opTreeCalc(root);
    printf(" = ");
    printNum(result);
}
