#ifndef CALCULATOR_C
#define CALCULATOR_C

#include <stdlib.h>
#include <stdio.h>

#include "calc.h"

/* Pop the number from the top of the stack */
int pop(Calculator * calculator) {
    if (calculator->top == 0L) {
        printf("Error: Popping from empty stack!\n");
        abort();
    }
    struct StackEntry *topEntry = calculator->top;
    int val = topEntry->num;
    calculator->top = topEntry->next;
    free(topEntry);
    return val;
}

/* Push a number onto the stack */
void push(Calculator * calculator, int num) {
    struct StackEntry *newEntry;
    newEntry = (struct StackEntry *) calloc(1, sizeof(struct StackEntry));
    newEntry->num = num;
    newEntry->next = calculator->top;
    calculator->top = newEntry;
};

/* Apply a binary operation to the top two stack elements and push the result */
void doOp(Calculator * calculator, Op op) {
    const int rhs = pop(calculator);
    const int lhs = pop(calculator);
    int result = 0;
    switch (op) {
        case ADD: result = lhs + rhs; break;
        case SUB: result = lhs - rhs; break;
        case MUL: result = lhs * rhs; break;
        case DIV: result = lhs / rhs; break;
        default: printf("Unknown Op: %d\n", op); abort(); break;
    }
    push(calculator, result);
};

/* Return the only value on the stack as result */
int getResult(Calculator* calculator) {
    if (calculator->top == 0L || calculator->top->next != 0L) {
        printf("Error: Invalid Expression!\n");
        abort();
    }
    return pop(calculator);
};

#endif