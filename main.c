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
    int sz = parserReadExpressions("../input.txt", e, 1, 1);
    int n = e[0].segCnt;

    rpnProcessor *outputStack;
    outputStack = init();

    stPrint(rpnFunc(outputStack, e[0].formula, n));

    int size = sizeof(char[10]);
    Node *root = nodeInit(size);
    opTreeGen(root, rpnFunc(outputStack, e[0].formula, n));
    opTreePrint(root, NULL);

    double complex result = opTreeCalc(root);
    printf(" = ");
    printNum(result);

    //destroyExpressionsArray(e, sz); //!todo
    return EXIT_SUCCESS;
}
