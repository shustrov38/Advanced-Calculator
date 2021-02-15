#include <stdio.h>
#include <string.h>

#include "Stack/stack.h"
#include "OpTree/tree.h"

int main() {
    int size = sizeof(char[10]);
    Stack *stack = stCreate(size);
    stPush(stack, "12.34");
    stPush(stack, "0.34j");
    stPush(stack, "+");
    stPush(stack, "3");
    stPush(stack, "*");
    stPrint(stack);
    Node *root = nodeInit(size);
    opTreeGen(root, stack);
    opTreePrint(root);
    double complex result = opTreeCalc(root);
    printf("\n%f + %fj", creal(result), cimag(result));
}
