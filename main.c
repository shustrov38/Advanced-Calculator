#include <stdio.h>
#include <string.h>

#include "Operations/ops.h"
#include "Stack/stack.h"

#include "Parser/Parser.h"
#include "RPN/RPN.h"
#include "OpTree/tree.h"

int main() {
    /* Input Data Parser initialization */
    Expression *e = createExpressions();
    int sz = parserReadExpressions("../input.txt", e, 0, 1);
    int n = e[0].segCnt;

    rpnProcessor *outputStack;
    outputStack = init();

//////////////////////
    char **kekt = (char **) malloc(100 * sizeof(char *));
    for (int i = 0; i < 100; ++i) {
        kekt[i] = (char *) malloc(10 * sizeof(char));
    }

    for (int i = 0; i < n; ++i) {
        strcpy(kekt[i], e[0].formula[i]);
    }
//////////////////////

//    stPrint(rpnFunc(outputStack, kekt, n));

    int size = sizeof(char[10]);
    Node *root = nodeInit(size);
    opTreeGen(root, rpnFunc(outputStack, kekt, n));
    opTreePrint(root, NULL);
    double complex result = opTreeCalc(root);
    printf(" = ");
    printNum(result);

    destroyExpressionsArray(e);
    return EXIT_SUCCESS;
}
