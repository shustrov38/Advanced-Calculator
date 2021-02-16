#include <stdio.h>
#include "Graph/graph.h"

int main() {
    int n;
    scanf("%d", &n);

    int **g = (int**) malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        g[i] = (int*) malloc(n * sizeof(int));
    }

    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n; ++j){
            scanf("%d", &g[i][j]);
        }
    }

    g = transpose(g, n);

    //dfsAlgorithm(inti(n), g, n);

    printGraph(g , n);

    /* Input Data Parser initialization
    Expression *e = createExpressions();
    int sz = parserReadExpressions("../input.txt", e, 0, 1);
    int n = e[0].segCnt;

    rpnProcessor *outputStack;
    outputStack = init();

    char **kekt = (char **) malloc(100 * sizeof(char *));
    for (int i = 0; i < 100; ++i) {
        kekt[i] = (char *) malloc(10 * sizeof(char));
    }

    for (int i = 0; i < n; ++i) {
        strcpy(kekt[i], e[0].formula[i]);
        printf("'%s' ", kekt[i]);
    }
    printf("\n");

    stPrint(rpnFunc(outputStack, kekt, n));

    int size = sizeof(char[10]);
    Node *root = nodeInit(size);
    opTreeGen(root, rpnFunc(outputStack, kekt, n));
    opTreePrint(root);
    double complex result = opTreeCalc(root);
    printf(" = ");
    printNum(result);

    destroyExpressionsArray(e);
    return EXIT_SUCCESS;*/
}
