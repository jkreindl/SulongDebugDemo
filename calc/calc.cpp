#ifndef CALCULATOR
#define CALCULATOR

#include <cstdlib>
#include <cstdio>

/* Entry in the value stack */
struct StackEntry {
    int num;
    struct StackEntry *next;
};

/* Supported operations */
typedef enum Op { ADD = 0, SUB = 1, MUL = 2, DIV = 3, PRINT = 4 } Op;

class Calculator {
private:
    int stackSize;
    struct StackEntry *top;

    /* Pop a value from the stack */
    int pop() {
        if (this->stackSize < 1) {
            printf("Error: Popping from empty stack!\n");
            abort();
        }
        struct StackEntry *topEntry = this->top;
        int val = topEntry->num;
        this->top = topEntry->next;
        free(topEntry);
        this->stackSize -= 1;
        return val;
    }

public:
    Calculator() : stackSize(0), top(0) {
    };

    /* Push a number onto the stack */
    void push(int num) {
        struct StackEntry *newEntry;
        newEntry = (struct StackEntry *) calloc(1, sizeof(struct StackEntry));
        newEntry->num = num;
        newEntry->next = this->top;
        this->top = newEntry;
        this->stackSize += 1;
    };

    /* Apply a binary operation to the top two stack elements and push the result,
     * or print the current content of the stack top-down */
    void doOp(Op &op, void (*printStackEntry)(int)) {
        if (op == PRINT) {
            for (struct StackEntry *entry = this->top; entry ; entry = entry->next) {
                const int val = entry->num;
                printStackEntry(val); /* | Inspection Point | */
            }
            return;
        }
        const int rhs = pop();
        const int lhs = pop();
        int result = 0;
        switch (op) {
            case ADD: result = lhs + rhs; break;
            case SUB: result = lhs - rhs; break;
            case MUL: result = lhs * rhs; break;
            case DIV: result = lhs / rhs; break;
            default: printf("Unknown Op: %d\n", op); abort(); break;
        }
        push(result);
    };

    /* Return the only value on the stack as result */
    int getResult() {
        if (this->stackSize != 1) {
            printf("Error: Stack contains %d elements!\n", this->stackSize);
            abort();
        }
        return pop();
    };
};

#endif
