#include <stdio.h>
#include <string.h>
#include "Stack/stack.h"
#include "OpTree/tree.h"

#include "Operations/ops.h"
#include "RPN/RPN.h"

int main() {
    char **eq;
    eq = (char **) malloc(sizeof(char *) * 100);
    for (int i = 0; i < 100; i++) {
        eq[i] = (char *) malloc(sizeof(char) * 100);
    }
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%s", eq[i]);
    }

    rpnProcessor *outputStack;
    outputStack = init();

    stPrint(rpnFunc(outputStack, eq, n));

    int size = sizeof(char[10]);
    Node *root = nodeInit(size);
    opTreeGen(root, rpnFunc(outputStack, eq, n));
    opTreePrint(root);
    double complex result = opTreeCalc(root);
    printf(" = ");
    printNum(result);
}