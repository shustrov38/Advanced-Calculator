#include "Parser.h"

#define MAX_ARRAY_SIZE 100

void initExpression(Expression *E) {
    assert((E) && "null ptr at expressions array while init");
    for (int i = 0; i < 10; ++i) {
        E[i].formula = (char **) malloc(100 * sizeof(char *));
        E[i].dependencies = (char **) malloc(100 * sizeof(char *));
        for (int j = 0; j < 100; ++j) {
            E[i].formula[j] = (char *) malloc(10 * sizeof(char));
            E[i].dependencies[j] = (char *) malloc(10 * sizeof(char));
        }
        E[i].varName = (char *) malloc(10 * sizeof(char));
        E[i].evenDependenciesCnt = 0;
        E[i].trueDependenciesCnt = 0;
    }
}

Expression *createExpressions() {
    Expression *tmp = (Expression *) malloc(MAX_ARRAY_SIZE * sizeof(Expression));
    assert((tmp) && "null ptr at creating expressions array");
    initExpression(tmp);
    return tmp;
}

int splitExpression(char *src, char **dest, char divs[]) {
    assert((src) && "given null str ptr");
    char tmpStr[100][10];
    for (int i = 0; i < 100; i++){
        memset(tmpStr[i],0,10);
    }
    int i = 0;
    int k = 0;
    int z = 0;
    int opF = 1;
    while (src[i] != '\n' && src[i] != '\0') {
        while (i < strlen(src) - 1 && (src[i] == ' ' || src[i] == '\t')) i++;
        int dvF = 0;
        for (int j = 0; j < strlen(divs); j++) {
            if (src[i] == divs[j]) dvF = 1;
        }
        if (!dvF) {
            tmpStr[k][z++] = src[i++];
            opF = 0;
        } else {
            z = 0;
            if (!opF) k++;
            tmpStr[k++][0] = src[i++];
            opF = 1;
        }
    }

    for (int i = 0; i < 100; ++i) {
        strcpy(dest[i], tmpStr[i]);
    }

    while ((dest[k][0] == ' ' || dest[k][0] == '\t')) k--;

    return k + (dest[k][0] != 0);
}

int parserReadExpressions(char *filename, Expression *e, int debug, int forceLowerCase) {
    FILE *in = fopen(filename, "r");
    assert((in) && "null file ptr, error while reading");
    assert((e) && "null ptr of struct");
    char buffStr[MAX_E_SIZE];
    int number = 0;
    while (!feof(in)) {
        fgets(buffStr, MAX_E_SIZE, in);
        for (int i = 0; i < strlen(buffStr); ++i) {
            if (forceLowerCase && buffStr[i] >= 'A' && buffStr[i] <= 'Z') buffStr[i] += ('a' - 'A');
        }
        e[number].segCnt = splitExpression(buffStr, e[number].formula, "()=-+/*^,%@");
        if (e[number].formula[0] && !strcmp(e[number].formula[1], "=")) {
            strcpy(e[number].varName, e[number].formula[0]);
            for (int segI = 0; segI < e[number].segCnt-2; segI++){
                strcpy(e[number].formula[segI],e[number].formula[segI+2]);
            }
            memset(e[number].formula[e[number].segCnt-1],0,100);
            memset(e[number].formula[e[number].segCnt-2],0,100);
            e[number].segCnt-=2;
        }
        int i = 0;
        int j = 0;
        while (e[number].formula[i][0] != '\0') {
            assert(getOpID(e[number].formula[i]) && "null opId");
            if (getOpID(e[number].formula[i]) == VAR && strcmp(e[number].formula[i], e[number].varName)) {
                strcpy(e[number].dependencies[j++], e[number].formula[i]);
                assert(e[number].dependencies[j - 1] && "null str after strcpy at building dependencies");
                e[number].evenDependenciesCnt++;
            }
            i++;
        }
        if (debug) {
            printf("expression (%s) #%d:[ ", e[number].varName, number + 1);
            for (int i = 0; i < MAX_E_SIZE && e[number].formula[i][0] != '\0'; ++i) {
                printf("%s ", e[number].formula[i]);
            }
            printf("] ");
            if (e[number].evenDependenciesCnt > 0) {
                printf("dependencies are: ", e[number].varName, number + 1);
                for (int i = 0; i < e[number].evenDependenciesCnt; ++i) {
                    printf("%s ", e[number].dependencies[i]);
                }
                printf("; %d even dependencies \n", e[number].evenDependenciesCnt);
            } else printf("without dependencies\n");
        }
        ++number;
    }
    fclose(in);
    return number;
}

void destroyExpressionsArray(Expression *E, int n) {
    assert((E) && "null ptr, lul, nothing to delete");
    for(int i = 0; i < n; i++)
    {for (int j = 0; j < 100; ++j) {
        free(E[i].formula[j]);
        free(E[i].dependencies[j]);
    }
    free(E[i].formula);
    free(E[i].dependencies);}
    free(E);
}