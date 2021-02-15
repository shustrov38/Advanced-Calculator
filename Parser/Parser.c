#include "Parser.h"

#define MAX_ARRAY_SIZE 100

void initExpression(Expression *E) {
    assert((E) && "null ptr at expressions array while init");
    for (int i = 0; i < MAX_ARRAY_SIZE; ++i) {
        memset(E[i].varName, 0, MAX_V_NAME_SIZE);
        E[i].evenDependenciesCnt = 0;
        E[i].trueDependenciesCnt = 0;
        for (int j = 0; j < MAX_E_SIZE; ++j) {
            memset(E[i].formula[j], 0, MAX_V_NAME_SIZE);
            memset(E[i].dependencies[j], 0, MAX_V_NAME_SIZE);

        }
    }
};

Expression *createExpressions() {
    Expression *tmp = (Expression *) malloc(MAX_ARRAY_SIZE * sizeof(Expression));
    assert((tmp) && "null ptr at creating expressions array");
    initExpression(tmp);
    return tmp;
};

void parserReadExpressions(char *filename, Expression *e, int debug, int forceLowerCase) {
    FILE *in = fopen(filename, "r");
    assert((in) && "null file ptr, error while reading");
    char buffStr[MAX_E_SIZE];
    //char buffPseudoStr[MAX_E_SIZE][MAX_E_SIZE];
    int number = 0;
    while (!feof(in)) {
        fgets(buffStr, MAX_E_SIZE, in);
        int elementIndex = 0;
        int i = 0;
        int j = 0;
        int opF = 1;
        while (buffStr[i] != '\n' && buffStr[i] != '\0') {
            if (i<strlen(buffStr)-1 && buffStr[i] == ' ') i++;
            if (forceLowerCase && buffStr[i] >= 'A' && buffStr[i] <= 'Z') buffStr[i] += ('a' - 'A');
            if (!((buffStr[i] >= 'a' && buffStr[i] <= 'z')||(buffStr[i] >= '0' && buffStr[i] <= '9')||(buffStr[i] == ')'
            || buffStr[i] == '(' || buffStr[i] == ',' || buffStr[i] == '+' || buffStr[i] == '-' ||
            buffStr[i] == '/' || buffStr[i] == '*' || buffStr[i] == '^' || buffStr[i] == '=' || buffStr[i] == '%' ||
            buffStr[i] == '.'))){
                printf("unknown char");
                exit(-1);
            };
            if (buffStr[i] != ')' && buffStr[i] != '(' && buffStr[i] != ',' && buffStr[i] != '+' && buffStr[i] != '-' &&
                buffStr[i] != '/' && buffStr[i] != '*' && buffStr[i] != '^' && buffStr[i] != '=' && buffStr[i] != '%') {
                opF = 0;
                e[number].formula[elementIndex][j] = buffStr[i];
                ++j;
            } else {
                j = 0;
                if (!opF) ++elementIndex;
                opF = 1;
                e[number].formula[elementIndex][0] = buffStr[i];
                ++elementIndex;
            }
            ++i;
        };
        if(e[number].formula[0] && !strcmp(e[number].formula[1],"=")) {
            strcpy(e[number].varName,e[number].formula[0]);
        }
        if (debug) {
            printf("expression (%s) #%d:[ ", e[number].varName, number + 1);
            for (int i = 0; i < MAX_E_SIZE && e[number].formula[i][0] != '\0'; ++i) {
                printf("%s ", e[number].formula[i]);
            }
            printf("]\n");
        }
        ++number;
    };
    fclose(in);
}