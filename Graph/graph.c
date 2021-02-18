#include "graph.h"

typedef struct {
    int *cnt, *p, *used;
    int n; // cycle length. if exists, cycle stored in *p
    int cycleStart, cycleEnd;
} Data;

typedef struct {
    int n; // count of unique variables
    char **variables;
    int **g;
    Data data;
} Graph;

void dfs(Graph *g, int v) {
    if (g->data.cycleStart != -1) return; // recursive break

    g->data.used[v] = 1;

    for (int u = 0; u < g->n; ++u) {
        if (g->g[v][u]) {
            if (g->data.used[u] == 0) {
                g->data.p[u] = v;
                dfs(g, u);
            } else if (g->data.used[u] == 1) {
                g->data.cycleEnd = v;
                g->data.cycleStart = u;
                return;
            }
            g->data.cnt[v] += g->data.cnt[u] + 1;
        }
    }

    g->data.used[v] = 2;
}

void gProcess(Graph *g) {
    g->data.used = (int *) malloc(g->n * sizeof(int));
    assert(g->data.used != NULL && "bad mem allocation");
    memset(g->data.used, 0, g->n * sizeof(int));

    g->data.cnt = (int *) malloc(g->n * sizeof(int));
    assert(g->data.cnt != NULL && "bad mem allocation");
    memset(g->data.cnt, 0, g->n * sizeof(int));

    g->data.p = (int *) malloc((g->n + 1) * sizeof(int));
    assert(g->data.p != NULL && "bad mem allocation");
    memset(g->data.p, -1, (g->n + 1) * sizeof(int));

    g->data.n = 0;
    g->data.cycleStart = -1;
    g->data.cycleEnd = -1;

    for (int v = 0; v < g->n; ++v) {
        if (!g->data.used[v]) {
            dfs(g, v);
        }
    }

    if (g->data.cycleStart != -1) {
        int cycle[g->n + 1];
        cycle[g->data.n++] = g->data.cycleStart;
        for (int v = g->data.cycleEnd; v != -1; v = g->data.p[v]) {
            cycle[g->data.n++] = v;
        }
        for (int i = g->data.n - 1; i >= 0; --i) {
            g->data.p[g->data.n - 1 - i] = cycle[i];
        }
    }
}

static int compare(const void *a, const void *b) {
    int aDep = ((Expression *) a)->trueDependenciesCnt;
    int bDep = ((Expression *) b)->trueDependenciesCnt;
    return aDep - bDep;
}

void prepareVariables(Expression *e, int n) {
#define THROW_ERROR(...) fprintf(stderr, "\n"__VA_ARGS__); exit(-1)

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

    for (int i = 0; i < n; ++i) {
        if (!strlen(e[i].varName)) continue;
        for (int j = 0; j < graph->n; ++j) {
            if (!strcmp(graph->variables[j], e[i].varName)) {
                THROW_ERROR("There is more than one possible definition for variable '%s'", e[i].varName);
            }
        }
        strcpy(graph->variables[graph->n++], e[i].varName);
    }

#ifdef __GRAPH_DEBUG__
    printf("variables: ");
    for (int i = 0;i < graph->n;++i) {
        printf("%s ", graph->variables[i]);
    }
    printf("\n");
#endif //__GRAPH_DEBUG__

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
            if (!strlen(e[i].dependencies[j])) continue;
            for (; B < graph->n; ++B) {
                if (!strcmp(graph->variables[B], e[i].dependencies[j])) {
                    break;
                }
            }

            if (B == graph->n) {
                THROW_ERROR("Have an unrecognized variable '%s' in definition of '%s'", e[i].dependencies[j],
                            e[i].varName);
            }

            graph->g[A][B] = 1;
        }
    }

#ifdef __GRAPH_DEBUG__
    printGraph(graph->g, graph->n);
#endif //__GRAPH_DEBUG__

    gProcess(graph);

#ifdef __GRAPH_DEBUG__
    printf("graph_cnt: ");
    for (int i = 0; i < graph->n; ++i) {
        printf("%d ", res->cnt[i]);
    }
    printf("\n");
#endif //__GRAPH_DEBUG__

    // has cycle
    if (graph->data.n) {
        fprintf(stderr, "Have cycle in variable definition: ");
        for (int i = 0; i < graph->data.n; ++i) {
            fprintf(stderr, "%s", graph->variables[graph->data.p[i]]);
            if (i + 1 != graph->data.n) {
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
                e[j].trueDependenciesCnt = graph->data.cnt[i];
                break;
            }
        }
    }

    qsort(e, n, sizeof(Expression), compare);

#undef THROW_ERROR
    // TODO: there must be free of all functions
}

void printGraph(int **g, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            printf("%d ", g[i][j]);
        }
        printf("\n");
    }
}