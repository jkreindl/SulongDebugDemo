#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "calc.h"

void printStack(Calculator* calc) {
    printf("Current Stack content (top-down):\n");
    for (struct StackEntry *entry = calc->top; entry ; entry = entry->next) {
        const int value = entry->num;
        printf("\t%d\n", value);
    }
}

/* calculate the result of a postfix expression */
int main(int argc, char** argv) {
    Calculator calc = { .top = 0L };

    push(&calc, 1);
    push(&calc, 2);
    push(&calc, 3);

    printStack(&calc);

    doOp(&calc, ADD);
    doOp(&calc, ADD);

    int result = getResult(&calc);
    printf("The result is: %d\n", result);
    return result;
}