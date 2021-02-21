#include "Parser.h"

#define MAX_ARRAY_SIZE 100

#define ERROR(...) fprintf(stderr, "\n"__VA_ARGS__); exit(-1)

void initExpression(Expression *E) {
    assert((E) && "null ptr at expressions array while init");
    for (int i = 0; i < 10; ++i) {
        E[i].formula = (char **) malloc(100 * sizeof(char *));
        E[i].dependencies = (char **) malloc(100 * sizeof(char *));
        for (int j = 0; j < 100; ++j) {
            E[i].formula[j] = (char *) malloc(10 * sizeof(char));
            memset(E[i].formula[j], 0, 10);
            E[i].dependencies[j] = (char *) malloc(10 * sizeof(char));
            memset(E[i].dependencies[j], 0, 10);
        }
        E[i].varName = (char *) malloc(10 * sizeof(char));
        E[i].evenDependenciesCnt = 0;
        E[i].trueDependenciesCnt = 0;

        for (int j = 0; j < MAX_E_SIZE; ++j) {
            memset(E[i].formula[j], 0, MAX_V_NAME_SIZE);
            memset(E[i].dependencies[j], 0, MAX_V_NAME_SIZE);
        }

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

    int lastValCh = strlen(src)-1;
    while(src[lastValCh] == ' '  || src[lastValCh] == '\n' || src[lastValCh] == '\t') src[lastValCh--] = '\0';
    //printf("%s", src);

    char tmpStr[100][10];
    for (int i = 0; i < 100; i++) {
        memset(tmpStr[i], 0, 10);
    }
    int i = 0;
    int k = 0;
    int z = 0;
    int opF = 1; //is op flag for ch
    while (src[i] != '\n' && src[i] != '\0' && src[i] != '\r') {
        while (i < strlen(src)-1 && (src[i] == ' ' || src[i] == '\t')) i++;
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
            tmpStr[k][0] = src[i];
            // check for unary minus
            if (src[i] == '-') {
                if (i == 0 || tmpStr[k - 1][0] == '=' || tmpStr[k - 1][0] == '(' || tmpStr[k - 1][0] == ',') {
                    tmpStr[k][1] = '-';
                }
            }
            // end check
            ++k;
            ++i;
            opF = 1;
        }
    }

    for (i = 0; i < 100; ++i) {
        strcpy(dest[i], tmpStr[i]);
    }

    while ((dest[k][0] == ' ' || dest[k][0] == '\t')) k--;

    return k + (dest[k][0] != 0);
}

void *checkForErrors(char **dest, int dlenght) {
    if (dlenght == 0) {
        ERROR("EMPTY INPUT");
    }
    int brCnt = 0;
    for (int i = 0; i < dlenght; ++i) {
        if (getOpID(dest[i]) == OPB) {
            brCnt++;

        } else if (getOpID(dest[i]) == CLB) {
            brCnt--;
            if (i > 0 && getOpID(dest[i - 1]) == OPB) {
                ERROR("BAD EXPRESSION NOTATION : empty brackets");
            }
        }
        if (brCnt < 0) { ERROR("BAD EXPRESSION NOTATION : wrong bracket sequence"); }
        if (getOpID(dest[i]) == COM) {
            if (i == 0 || i == dlenght - 1 || getOpID(dest[i - 1]) == OPB || getOpID(dest[i + 1]) == CLB) {
                ERROR("wrong place for ','");
            }
        }
        if (IS_OPER(dest[i])) { // check for {binary operand} exception
            if (i == 0 || IS_OPER(dest[i - 1]) || IS_OPER(dest[i + 1]) ||
                (getOpID(dest[i - 1]) == OPB || getOpID(dest[i + 1]) == CLB)) {
                ERROR("operator '%s' must have two operands\n", dest[i]);
            }
        } else if (IS_NUM(dest[i])) { // check for {num vals} exception
            int pointCnt = 0;
            if (dest[i][0] == '0' && dest[i][1] != '\0' && dest[i][1] != '.') {
                ERROR("BAD NUMBER : wrong number input '%s'\n", dest[i]);
            }
            for (int j = 0; dest[i][j] != '\0'; j++) {
                if (dest[i][j] == '.') {
                    pointCnt++;
                    if (dest[i][j + 1] == '\0') {
                        ERROR("BAD NUMBER : wrong float value notation '%s'\n", dest[i]);
                    }
                    if (j > 0 && pointCnt > 1) {
                        ERROR("BAD NUMBER : wrong float value notation '%s'\n", dest[i]);
                    }
                } else if (!(dest[i][j] >= '0' && dest[i][j] <= '9' || dest[i][j] == '.' ||
                             dest[i][j] == 'j')) { // appropriate char check
                    ERROR("BAD NUMBER : wrong number char '%s'\n", dest[i]);
                } else if (dest[i][j] == 'j' && dest[i][j + 1] != '\0') {
                    ERROR("BAD NUMBER : wrong complex value notation '%s'\n", dest[i]);
                }
            }
        } else if (IS_VAR(dest[i])) { // check for {var names} exception
            if (!((dest[i][0] >= 'a' && dest[i][0] <= 'z') || (dest[i][0] == '_'))) {
                ERROR("BAD VAR NAME : explicit char in variable name '%s'\n", dest[i]);
            }
            for (int j = 1; dest[i][j] != '\0'; j++) {
                if (!((dest[i][j] >= 'a' && dest[i][j] <= 'z') || (dest[i][j] >= '0' && dest[i][j] <= '9') ||
                      (dest[i][j] == '_'))) {
                    ERROR("BAD VAR NAME : explicit char in variable name '%s'\n", dest[i]);
                }
            }
        } else if (IS_FUNC_1ARG(dest[i])) { // check for {1 arg func} exception
//            if (!(IS_VAR(dest[i + 2]) || IS_NUM(dest[i + 2]) || IS_FUNC_1ARG(dest[i+2]) || IS_FUNC_2ARG(dest[i+2])
//            || IS_CONST(dest[i+2]))) {
//                ERROR("wrong '%s' function error\n", dest[i]);
//            }
            int countBr = 1;
            for (int j = i + 2; countBr != 0 && j < dlenght; j++) {
                if (getOpID(dest[j]) == OPB) {
                    countBr++;
                } else if (getOpID(dest[j]) == CLB) {
                    countBr--;
                }
                if (getOpID(dest[j]) == COM && countBr == 1) {
                    ERROR("FUNCTION %s ERROR: required 1 argument but more given", dest[i]);
                }
            }
        } else if (IS_FUNC_2ARG(dest[i])) { // need to fix ','
            int countBr = 1;
            int countCom = 0;
            for (int j = i + 2; countBr != 0 && j < dlenght; j++) {
                if (getOpID(dest[j]) == OPB) {
                    countBr++;
                } else if (getOpID(dest[j]) == CLB) {
                    countBr--;
                }
                if (getOpID(dest[j]) == COM && countBr == 1) {
                    countCom++;
                }
                if (countCom == 2) {
                    ERROR("FUNCTION %s ERROR: required 2 arguments", dest[i]);
                }
            }
            if (countCom != 1) {
                ERROR("FUNCTION %s ERROR: required 2 arguments", dest[i]);
            }
        }
    }
    if (brCnt != 0) { ERROR("BAD EXPRESSION NOTATION : wrong bracket sequence"); }
}

int parserReadExpressions(char *filename, Expression *e, int debug, int forceLowerCase) {
    FILE *in = fopen(filename, "r");
    if (in == NULL) {
        fprintf(stderr, "Can't open input file.\n");
        exit(-1);
    }
    assert((e) && "null ptr of struct");
    char buffStr[MAX_E_SIZE];
    int number = 0;
    while (!feof(in)) {
        fgets(buffStr, MAX_E_SIZE, in);
        for (int i = 0; i < strlen(buffStr); ++i) {
            if (forceLowerCase && buffStr[i] >= 'A' && buffStr[i] <= 'Z') buffStr[i] += ('a' - 'A');
        }
        e[number].segCnt = splitExpression(buffStr, e[number].formula, "()=-+*^/,%&|@");
        if (e[number].formula[0] && !strcmp(e[number].formula[1], "=")) {
            strcpy(e[number].varName, e[number].formula[0]);
            for (int segI = 0; segI < e[number].segCnt - 2; segI++) {
                strcpy(e[number].formula[segI], e[number].formula[segI + 2]);
            }
            memset(e[number].formula[e[number].segCnt - 1], 0, 10);
            memset(e[number].formula[e[number].segCnt - 2], 0, 10);
            e[number].segCnt -= 2;
        }
        int i = 0;
        int j = 0;
        while (e[number].formula[i][0] != '\0') {
            assert(getOpID(e[number].formula[i]) && "null opId");
            if (getOpID(e[number].formula[i]) == VAR) {
                int uniqDep = 1;
                for(int l = 0; l < e[number].evenDependenciesCnt; l++){
                    if(!strcmp(e[number].formula[i],e[number].dependencies[l])) uniqDep = 0;
                }
                if (uniqDep){
                    strcpy(e[number].dependencies[j++], e[number].formula[i]);
                    assert(e[number].dependencies[j - 1] && "null str after strcpy at building dependencies");
                    e[number].evenDependenciesCnt++;
                }
            }
            i++;
        }
        if (debug) {
            printf("expression (%s) #%d:[ ", e[number].varName, number + 1);
            for (i = 0; i < MAX_E_SIZE && e[number].formula[i][0] != '\0'; ++i) {
                printf("%s ", e[number].formula[i]);
            }
            printf("] ");
            if (e[number].evenDependenciesCnt > 0) {
                printf("dependencies are: ");
                for (i = 0; i < e[number].evenDependenciesCnt; ++i) {
                    printf("'%s' ", e[number].dependencies[i]);
                }
            }
            printf("\n");
        }
        checkForErrors(e[number].formula, e[number].segCnt);
        ++number;
    }
    fclose(in);
    return number;
}

void destroyExpressionsArray(Expression *E) {
    assert((E) && "null ptr, lul, nothing to delete");
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 100; ++j) {
            free(E[i].formula[j]);
            free(E[i].dependencies[j]);
        }
        free(E[i].varName);
        free(E[i].formula);
        free(E[i].dependencies);
    }
    free(E);
}