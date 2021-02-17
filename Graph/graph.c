#include "graph.h"

void checkVariables(Expression *e, int n) {
    Graph *graph = (Graph *) malloc(sizeof(Graph));
    assert(graph != NULL && "bad mem allocate");

    graph->n = 0;
    graph->variables = (char **) malloc(n * sizeof(char *));
    assert(graph->variables != NULL && "bad mem allocate");
    for (int i = 0; i < n; ++i) {
        graph->variables[i] = (char *) malloc(10 * sizeof(char));
        assert(graph->variables[i] != NULL && "bad mem allocate");
        memset(graph->variables[i], 0, 10);
    }

    // TODO: check for identical name
    for (int i = 0; i < n; ++i) {
        if (!strlen(e[i].varName)) continue;
        strcpy(graph->variables[graph->n++], e[i].varName);
    }

    graph->g = (int **) malloc(n * sizeof(int *));
    assert(graph->g != NULL && "bad mem allocate");
    for (int i = 0; i < n; ++i) {
        graph->g[i] = (int *) malloc(n * sizeof(int));
        assert(graph->g[i] != NULL && "bad mem allocate");
        memset(graph->g[i], 0, n * sizeof(int));
    }

    for (int i = 0; i < n; ++i) {
        if (!strlen(e[i].varName)) continue;
        int A = 0, B = 0;
        for (; A < graph->n; ++A) {
            if (!strcmp(graph->variables[A], e[i].varName)) {
                break;
            }
        }
        for (int j = 0; j < e[i].segCnt; ++j) {
            for (; B < graph->n; ++B) {
                if (!strcmp(graph->variables[B], e[i].dependencies[j])) {
                    break;
                }
            }
            if (A != B) {
                // add edge
                graph->g[A][B] = 1;
            }
        }
    }

    printGraph(graph->g, graph->n);
    gResult *res = gProcess(graph->g, graph->n);

    // has cycle
    if (res->size) {
        fprintf(stderr, "Have cycle in variable definition: ");
        for (int i = 0; i < res->size; ++i) {
            fprintf(stderr,"%s", graph->variables[res->p[i]]);
            if (i + 1 != res->size) {
                fprintf(stderr, " -> ");
            }
        }
        exit(-1);
    }

    for (int i = 0; i < graph->n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (!strlen(e[j].varName)) {
                e[j].trueDependenciesCnt = n + 1;
            } else if (!strcmp(graph->variables[i], e[j].varName)) {
                e[j].trueDependenciesCnt = res->cnt[i];
                break;
            }
        }
    }
}

int dfs(int **g, int *used, int n, int v, gResult *res) {
    used[v] = 1;

    for (int u = 0; u < n; ++u) {
        if (g[v][u]) {
            if (used[u] == 0) {
                res->p[u] = v;
                return dfs(g, used, n, u, res);
            } else if (used[u] == 1) {
                res->cycleEnd = v;
                res->cycleStart = u;
                return 1;
            }
            res->cnt[v] += res->cnt[u] + 1;
        }
    }

    used[v] = 2;
    return 0;
}

gResult *gProcess(int **g, int n) {
    gResult *res = (gResult *) malloc(sizeof(gResult));
    assert(res != NULL && "bad mem allocation");

    res->cnt = (int *) malloc(n * sizeof(int));
    assert(res->cnt != NULL && "bad mem allocation");
    memset(res->cnt, 0, n * sizeof(int));

    res->p = (int *) malloc((n + 1) * sizeof(int));
    assert(res->p != NULL && "bad mem allocation");
    memset(res->p, -1, (n + 1) * sizeof(int));

    res->size = 0;
    res->cycleStart = -1;
    res->cycleEnd = -1;

    int *used = (int *) malloc(n * sizeof(int));
    assert(used != NULL && "bad mem allocation");
    memset(used, 0, n * sizeof(int));

    for (int i = 0; i < n; ++i) {
        if (!used[i] && dfs(g, used, n, i, res)) {
            break;
        }
    }

    if (res->cycleStart != -1) {
        int cycle[n + 1];
        cycle[res->size++] = res->cycleStart;
        for (int v = res->cycleEnd; v != -1; v = res->p[v]) {
            cycle[res->size++] = v;
        }
        for (int i = res->size - 1; i >= 0; --i) {
            res->p[res->size - 1 - i] = cycle[i];
        }
    }

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