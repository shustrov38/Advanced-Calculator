#include <stdio.h>
#include <string.h>

#include "Stack/stack.h"
#include "Operations/ops.h"
#include "OpTree/tree.h"
#include "Parser/Parser.h"
int main() {
    /* Input Data Parser initialization */
    Expression *e = createExpressions();
    parserReadExpressions("../input.txt", e,1,1);
    destroyExpressionsArray(e);
    return 0;
}
