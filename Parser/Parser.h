//
// Created by zhvzh on 15.02.2021.
//

#ifndef ADVANCED_CALCULATOR_PARSER_H
#define ADVANCED_CALCULATOR_PARSER_H

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include "assert.h"
#include "../Operations/ops.h"

#define MAX_V_NAME_SIZE 10
#define MAX_E_SIZE 100

typedef struct Expression {

    char varName[MAX_V_NAME_SIZE]; // name of var, null if expression is just a number
    char formula[MAX_E_SIZE][MAX_V_NAME_SIZE]; // expression splitted to pseudo string
    char dependencies[MAX_E_SIZE][MAX_V_NAME_SIZE]; //vars, on which expression depends, according to plain scanning
    int evenDependenciesCnt; // num of dependencies after scan
    int trueDependenciesCnt; // num of dependencies after reverse+BFS
    double complex value;

} Expression;

Expression *createExpressions();
void parserReadExpressions(char *filename, Expression *parsedExpr, int debug, int forceLowerCase);
void destroyExpressionsArray(Expression *E);
void splitExpression(char *str, char dest[100][10], char divs[]);
int expressionIsValid(OpID *mask);
OpID *getSyntax(Expression E);

#endif //ADVANCED_CALCULATOR_PARSER_H
