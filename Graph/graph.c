#include "graph.h"

typedef struct {
    int n; // count of unique variables
    char **variables;
    int **matrix; // adjacency matrix
    int *cnt, *p, *used;
    int cycleLength; // after dfs cycle will be stored in *p
    int cycleStart, cycleEnd;
} Graph;

void dfs(Graph *g, int v) {
    if (g->cycleStart != -1) return; // recursive break

    g->used[v] = 1;

    for (int u = 0; u < g->n; ++u) {
        if (g->matrix[v][u]) {
            if (g->used[u] == 0) {
                g->p[u] = v;
                dfs(g, u);
            } else if (g->used[u] == 1) {
                g->cycleEnd = v;
                g->cycleStart = u;
                return;
            }
            g->cnt[v] += g->cnt[u] + 1;
        }
    }

    g->used[v] = 2;
}

void gProcess(Graph *g) {
    g->used = (int *) malloc(g->n * sizeof(int));
    assert(g->used != NULL && "bad mem allocation");
    memset(g->used, 0, g->n * sizeof(int));

    g->cnt = (int *) malloc(g->n * sizeof(int));
    assert(g->cnt != NULL && "bad mem allocation");
    memset(g->cnt, 0, g->n * sizeof(int));

    g->p = (int *) malloc((g->n + 1) * sizeof(int));
    assert(g->p != NULL && "bad mem allocation");
    memset(g->p, -1, (g->n + 1) * sizeof(int));

    g->cycleLength = 0;
    g->cycleStart = -1;
    g->cycleEnd = -1;

    for (int v = 0; v < g->n; ++v) {
        if (!g->used[v]) {
            dfs(g, v);
        }
    }

    if (g->cycleStart != -1) {
        int cycle[g->n + 1];
        cycle[g->cycleLength++] = g->cycleStart;
        for (int v = g->cycleEnd; v != -1; v = g->p[v]) {
            cycle[g->cycleLength++] = v;
        }
        for (int i = g->cycleLength - 1; i >= 0; --i) {
            g->p[g->cycleLength - 1 - i] = cycle[i];
        }
    }
}

static int compareByDependency(const void *a, const void *b) {
    int aDep = ((Expression *) a)->trueDependenciesCnt;
    int bDep = ((Expression *) b)->trueDependenciesCnt;
    return aDep - bDep;
}

void prepareVariables(Expression *e, int n) {
#define THROW_ERROR(...) fprintf(stderr, "\n"__VA_ARGS__); exit(-1)

    Graph *g = (Graph *) malloc(sizeof(Graph));
    assert(g != NULL && "bad mem allocate");

    g->n = 0;
    g->variables = (char **) malloc(n * sizeof(char *));
    assert(g->variables != NULL && "bad mem allocate");
    for (int i = 0; i < n; ++i) {
        g->variables[i] = (char *) malloc(10 * sizeof(char));
        assert(g->variables[i] != NULL && "bad mem allocate");
        memset(g->variables[i], 0, 10);
    }

    for (int i = 0; i < n; ++i) {
        if (!strlen(e[i].varName)) {
            // expression must be calculated at the end
            e[i].trueDependenciesCnt = n + 1;
            continue;
        }
        for (int j = 0; j < g->n; ++j) {
            if (!strcmp(g->variables[j], e[i].varName)) {
                THROW_ERROR("There is more than one possible definition for variable '%s'", e[i].varName);
            }
        }
        strcpy(g->variables[g->n++], e[i].varName);
    }

#ifdef __GRAPH_DEBUG__
    printf("variables: ");
    for (int i = 0;i < g->cycleLength;++i) {
        printf("%s ", g->variables[i]);
    }
    printf("\n");
#endif //__GRAPH_DEBUG__

    g->matrix = (int **) malloc(n * sizeof(int *));
    assert(g->matrix != NULL && "bad mem allocate");
    for (int i = 0; i < n; ++i) {
        g->matrix[i] = (int *) malloc(n * sizeof(int));
        assert(g->matrix[i] != NULL && "bad mem allocate");
        memset(g->matrix[i], 0, n * sizeof(int));
    }

    for (int i = 0; i < n; ++i) {
        if (!strlen(e[i].varName)) continue;
        int A = 0, B = 0;
        for (; A < g->n; ++A) {
            if (!strcmp(g->variables[A], e[i].varName)) {
                break;
            }
        }
        for (int j = 0; j < e[i].segCnt; ++j) {
            if (!strlen(e[i].dependencies[j])) continue;
            for (; B < g->n; ++B) {
                if (!strcmp(g->variables[B], e[i].dependencies[j])) {
                    break;
                }
            }

            if (B == g->n) {
                THROW_ERROR("Have an unrecognized variable '%s' in definition of '%s'", e[i].dependencies[j],
                            e[i].varName);
            }

            g->matrix[A][B] = 1;
        }
    }

#ifdef __GRAPH_DEBUG__
    printGraph(g->matrix, g->cycleLength);
#endif //__GRAPH_DEBUG__

    gProcess(g);

#ifdef __GRAPH_DEBUG__
    printf("graph_cnt: ");
    for (int i = 0; i < g->cycleLength; ++i) {
        printf("%d ", res->cnt[i]);
    }
    printf("\n");
#endif //__GRAPH_DEBUG__

    // has cycle
    if (g->cycleLength) {
        fprintf(stderr, "Have cycle in variable definition: ");
        for (int i = 0; i < g->cycleLength; ++i) {
            fprintf(stderr, "%s", g->variables[g->p[i]]);
            if (i + 1 != g->cycleLength) {
                fprintf(stderr, " -> ");
            }
        }
        exit(-1);
    }

    for (int i = 0; i < g->n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (!strlen(e[j].varName)) continue;
            if (!strcmp(g->variables[i], e[j].varName)) {
                e[j].trueDependenciesCnt = g->cnt[i];
                break;
            }
        }
    }

    qsort(e, n, sizeof(Expression), compareByDependency);

#undef THROW_ERROR

    free(g->cnt);
    free(g->p);
    free(g->used);
    for (int i = 0; i < g->n; ++i) {
        free(g->matrix[i]);
        free(g->variables[i]);
    }
    free(g->matrix);
    free(g->cnt);
    free(g);
}

void printGraph(Graph *g) {
    for (int i = 0; i < g->n; ++i) {
        for (int j = 0; j < g->n; ++j) {
            printf("%d ", g->matrix[i][j]);
        }
        printf("\n");
    }
}