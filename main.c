#include <stdio.h>
#include <string.h>

#include "Operations/ops.h"
#include "Stack/stack.h"

#include "Parser/Parser.h"
#include "Graph/graph.h"

int main() {
    /* Input Data Parser initialization */
    Expression *e = createExpressions();
    int n = parserReadExpressions("../input.txt", e, 0, 1);
    prepareVariables(e, n);
    for (int i = 0; i < n; ++i) {
        if (strlen(e[i].varName)) {
            printf("%s %d\n", e[i].varName, e[i].trueDependenciesCnt);
        } else {
            printf("expression");
        }
    }
    return EXIT_SUCCESS;
}