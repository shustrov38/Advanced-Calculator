#include <stdio.h>
#include <string.h>

#include "Operations/ops.h"
#include "Stack/stack.h"
#include "RPN/RPN.h"
#include "Parser/Parser.h"
#include "Graph/graph.h"
#include "OpTree/tree.h"

#define ARG_COUNT 2

int main(const int argc, const char *argv[]) {
    char *filename = (char *) malloc(30 * sizeof(char));
    memset(filename, 0, 30);
    if (argc == ARG_COUNT) {
        strcpy(filename, argv[1]);
    } else {
        strcpy(filename, "../input.txt");
    }

    Expression *e = createExpressions();
    int n = parserReadExpressions(filename, e, 0, 1);
    prepareVariables(e, n);
    for (int i = 0; i < n; ++i) {
        rpnProcessor *outStack = rpnProcInit(10 * sizeof(char));
        Node *root = nodeInit(10 * sizeof(char));
        opTreeGen(root, rpnFunc(outStack, e[i].formula, e[i].segCnt));
//        opTreePrint(root, NULL);
//        printf("\n");
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
