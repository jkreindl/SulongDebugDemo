#ifndef CALCULATOR_H
#define CALCULATOR_H

/* Entry in the value stack */
struct StackEntry {
    int num;
    struct StackEntry *next;
};

/* Supported operations */
typedef enum Op { UNKNOWN = 0, ADD = 1, SUB = 2, MUL = 3, DIV = 4 } Op;

/* the calculator */
typedef struct Calculator {
    struct StackEntry *top;
} Calculator;

/* Supported operations */
int pop(Calculator * calculator);
void push(Calculator * calculator, int num);
void doOp(Calculator * calculator, Op op);
int getResult(Calculator * calculator);

#endif