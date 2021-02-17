#include "graph.h"

void transpose(int **g, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = i; j < n; ++j) {
            int temp = g[i][j];
            g[i][j] = g[j][i];
            g[j][i] = temp;
        }
    }
}

int size(int **g, int n, int v) {
    int k = 0;
    for (int u = 0; u < n; ++u) {
        if (g[v][u]) {
            k++;
        }
    }
    return k;
}

void dfs(int **g, int *used, int n, int v, gResult *res) {
    used[v] = 1;

    if (size(g, n, v) == 0) {
        res->cnt[v] = 0;
    }

    for (int u = 0; u < n; ++u) {
        if (g[v][u] && !used[u]) {
            dfs(g, used, n, u, res);
        }
    }

    for (int u = 0; u < n; ++u) {
        if (g[v][u]) {
            res->cnt[v] += res->cnt[u] + 1;
        }
    }
}

gResult *gProcess(int **g, int n) {
    gResult *res = (gResult *) malloc(sizeof(gResult));
    assert(res != NULL && "bad mem allocation");

    res->cnt = (int *) malloc(n * sizeof(int));
    assert(res->cnt != NULL && "bad mem allocation");
    memset(res->cnt, 0, n * sizeof(int));

    res->cSize = 0;
    res->cycle = (int *) malloc(n * sizeof(int));
    assert(res->cycle != NULL && "bad mem allocation");
    memset(res->cycle, 0, n * sizeof(int));

    int *used = (int *) malloc(n * sizeof(int));
    assert(used != NULL && "bad mem allocation");
    memset(used, 0, n * sizeof(int));

    for (int i = 0; i < n; ++i) {
        if (!used[i]) {
            dfs(g, used, n, i, res);
        }
    }

    for (int i = 0; i < n; ++i) {
        printf("%d ", res->cnt[i]);
    }
    printf("\n");

    return res;
}

void printGraph(int **g, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            printf("%d ", g[i][j]);
        }
        printf("\n");
    }
}