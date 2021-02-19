#include <stdio.h>
#include <string.h>

#include "Operations/ops.h"
#include "Stack/stack.h"
#include "RPN/RPN.h"
#include "Parser/Parser.h"
#include "Graph/graph.h"
#include "OpTree/tree.h"



    int main() {
    Expression *e = createExpressions();
    int n = parserReadExpressions("../input.txt", e, 0, 1);
    prepareVariables(e, n);
    for (int i = 0; i < n; ++i) {
        rpnProcessor *outStack = init();
        Node *root = nodeInit(10 * sizeof(char));
        opTreeGen(root, rpnFunc(outStack, e[i].formula, e[i].segCnt));
        e[i].value = opTreeCalc(root, e, n);
    }
    for (int i = 0; i < n; ++i) {
        if (strlen(e[i].varName)) {
            printf("%s = ", e[i].varName);
        } else {
            printf("expr = ");
        }
        printNum(e[i].value);
        printf("\n");
    }
    return EXIT_SUCCESS;



    }
