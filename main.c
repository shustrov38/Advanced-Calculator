#include <stdio.h>
#include <string.h>

#include "Stack/stack.h"
#include "OpTree/tree.h"

int main() {
    int size = sizeof(char[10]);
    Stack *stack = stCreate(size);
    stPush(stack, "e");
    stPush(stack, "1.23j");
    stPush(stack, "+");
    stPush(stack, "ln");
    stPush(stack, "sin");
    stPrint(stack);
    Node *root = nodeInit(size);
    opTreeGen(root, stack);
    opTreePrint(root);
    double complex result = opTreeCalc(root);
    printf(" = ");
    printNum(result);
}
