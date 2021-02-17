#include <stdio.h>
#include "Graph/graph.h"

int main() {
    int n, m;
    scanf("%d%d", &n, &m);

    int **g = (int**) malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        g[i] = (int*) malloc(n * sizeof(int));
        memset(g[i], 0, n * sizeof(int));
    }

    for (int i = 0; i < m; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        g[u-1][v-1] = 1;
    }

//    transpose(g, n);

    gProcess(g, n);

//    printGraph(g , n);
}