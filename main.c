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
    Graph *graph = grCreate(e, n);
    printGraph(graph->g, graph->n);
    gResult *res = gProcess(graph->g, graph->n);
    printf("dependency:\n");
    for (int i = 0; i < graph->n; ++i) {
        printf("%d ", res->cnt[i]);
    }
    return EXIT_SUCCESS;
}