//
// Created by zhvzh on 15.02.2021.
// Designed by Hideo Kojima 14.88.1488

#ifndef ADVANCED_CALCULATOR_PARSER_H
#define ADVANCED_CALCULATOR_PARSER_H


#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include "assert.h"
#include "../Operations/ops.h"

#define PARSE_ERROR(...) fprintf(stderr, "\n"__VA_ARGS__); exit(-1)

#define MAX_V_NAME_SIZE 10
#define MAX_E_SIZE 100

typedef struct Expression {
    char *varName; // name of var, null if expression is just a number
    char **formula; // expression splitted to pseudo string
    char **dependencies; //vars, on which expression depends, according to plain scanning
    int evenDependenciesCnt; // num of dependencies after scan
    int trueDependenciesCnt; // num of dependencies after reverse+BFS
    double complex value;
    int segCnt;

} Expression;

Expression *createExpressions();

int parserReadExpressions(char *filename, Expression *parsedExpr, int debug, int forceLowerCase);

void destroyExpressionsArray(Expression *E);

int splitExpression(char *str, char **dest, char divs[]);

int expressionIsValid(OpID *mask);

OpID *getSyntax(Expression E);

#endif //ADVANCED_CALCULATOR_PARSER_H
