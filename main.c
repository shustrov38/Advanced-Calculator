#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "Parser/parser.h"
#include "Stack/stack.h"
#include "RPN/RPN.h"
#include "Graph/graph.h"
#include "OpTree/tree.h"

#define FILENAME_LENGTH 100
#define ARG_COUNT 2

int main(const int argc, const char *argv[]) {
    char *filename = (char *) malloc(FILENAME_LENGTH * sizeof(char));
    memset(filename, 0, FILENAME_LENGTH);
    if (argc == ARG_COUNT) {
        strcpy(filename, argv[1]);
    } else {
        strcpy(filename, "../input.txt");
    }

    rand();
    unsigned seed = time(0);
    srand(seed);

    Expression *e = createExpressions();
    int n = parserReadExpressions(filename, e);

    prepareVariables(e, n);

    for (int i = 0; i < n; ++i) {
        rpnProcessor *outStack = rpnProcInit(MAX_V_NAME_SIZE * sizeof(char));
        Node *root = nodeInit(MAX_V_NAME_SIZE * sizeof(char));
        Stack *stack = rpnFunc(outStack, e[i].formula, e[i].segCnt);
#ifdef __EXP_DEBUG__
        stPrint(stack);
#endif //__EXP_DEBUG__
        opTreeGen(root, stack);
#ifdef __EXP_DEBUG__
        opTreePrint(root, NULL);
        printf("\n");
#endif //__EXP_DEBUG__
        e[i].value = opTreeCalc(root, e, i, n);
    }

    if (argc == ARG_COUNT) {
        for (int i = 0; i < n; ++i) {
            if (!strcmp(e[i].varName, "res")) {
                printf("res = ");
                printNum(e[i].value);
                printf("\n");
                break;
            }
        }
    } else {
        for (int i = 0; i < n; ++i) {
            if (strlen(e[i].varName)) {
                printf("%s = ", e[i].varName);
            } else {
                printf("%s = ", e[i].rawFormula);
            }
            printNum(e[i].value);
            printf("\n");
        }
    }

    destroyExpressionsArray(e);
    free(filename);
    return EXIT_SUCCESS;
}
