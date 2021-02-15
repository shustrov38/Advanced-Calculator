#ifndef ADVANCED_CALCULATOR_STACK_H
#define ADVANCED_CALCULATOR_STACK_H

<<<<<<< HEAD
=======

>>>>>>> 088faea77faf5ae85b4c6380f9b781540c184a76
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <assert.h>

#define STACK_H_INIT_CAPACITY 4

typedef struct {
    size_t elementSize;
    int size, capacity;
    char **data;
} Stack;

<<<<<<< HEAD
Stack *stCreate();
=======
Stack *stCreate(int elementSize);
>>>>>>> 088faea77faf5ae85b4c6380f9b781540c184a76

void stPush(Stack *stack, char *data);

char *stTop(Stack *stack);

void stPop(Stack *stack);

void stResize(Stack *stack, int newCap);

void stPrint(Stack *stack);

#endif //ADVANCED_CALCULATOR_STACK_H
<<<<<<< HEAD

=======
>>>>>>> 088faea77faf5ae85b4c6380f9b781540c184a76
