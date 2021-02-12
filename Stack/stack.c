#include "stack.h"

Stack *stCreate(int elementSize) {
    Stack *stack = (Stack *) malloc(sizeof(Stack));
    assert(stack != NULL);
    stack->capacity = STACK_H_INIT_CAPACITY;
    stack->elementSize = elementSize;
    stack->size = 0;
    stack->data = (char **) malloc(STACK_H_INIT_CAPACITY * sizeof(stack->elementSize));
    assert(stack->data != NULL);
    return stack;
}

void stPush(Stack *stack, char *data) {
    if (stack->size >= stack->capacity) {
        stResize(stack, stack->capacity * 2);
    }
    stack->data[stack->size] = (char *) malloc(stack->elementSize);
    assert(stack->data[stack->size] != NULL);
    memcpy(stack->data[stack->size], data, stack->elementSize);
    stack->size++;
}

char *stTop(Stack *stack) {
    assert(stack->size > 0);
    return stack->data[stack->size - 1];
}

void stPop(Stack *stack) {
    assert(stack->size > 0);
    free(stTop(stack));
    stack->size--;
}

void stResize(Stack *stack, int newCap) {
    stack->capacity = newCap;
    stack->data = realloc(stack->data, newCap * stack->elementSize);
}

void stPrint(Stack *stack) {
    printf("stack: [");
    if (stack->size) {
        for (int i = 0; i < stack->size; ++i) {
            printf("%s", (char *) stack->data[i]);
            if (i + 1 != stack->size) {
                printf(", ");
            }
        }
    } else {
        printf("EMPTY");
    }
    printf("]\n");
}
