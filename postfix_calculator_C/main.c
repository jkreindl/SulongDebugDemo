#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "calc.h"

void printStackEntry(int entry) {
    printf("\t%d\n", entry);
}

/* calculate the result of a postfix expression */
int main(int argc, char** argv) {
    Calculator calc = { .top = 0L };

    for (int arg_i = 1; arg_i < argc; ++arg_i) {
        char* arg = argv[arg_i];
        if (strncmp("+", arg, 2) == 0) {
            doOp(&calc, ADD, &printStackEntry);
        } else if (strncmp("-", arg, 2) == 0) {
            doOp(&calc, SUB, &printStackEntry);
        } else if (strncmp("*", arg, 2) == 0) {
            doOp(&calc, MUL, &printStackEntry);
        } else if (strncmp("/", arg, 2) == 0) {
            doOp(&calc, DIV, &printStackEntry);
        } else if (strncmp("=", arg, 2) == 0) {
            printf("Current Stack content (top-down):\n");
            doOp(&calc, PRINT, &printStackEntry);
        } else {
            int num = atoi(arg);
            push(&calc, num);
        }
    }
    int result = getResult(&calc);
    printf("The result is: %d\n", result);
    return result;
}