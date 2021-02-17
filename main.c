#include <stdio.h>
#include <string.h>

#include "Operations/ops.h"
#include "Stack/stack.h"

#include "Parser/Parser.h"
#include "Graph/graph.h"

int main() {
    /* Input Data Parser initialization */
    Expression *e = createExpressions();
    int n = parserReadExpressions("../input.txt", e, 1, 1);
    checkVariables(e, n);
    return EXIT_SUCCESS;
}