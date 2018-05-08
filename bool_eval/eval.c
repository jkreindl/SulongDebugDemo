/* Satisfiability checker for assignments to a boole AST. */
#include "boole.h"

typedef int (*Op)(Node *node, long vars);
Op getOp(Kind kind);

// check the truth value of a variable
int var(Node *node, long vars) {
    int varId = node->varId;
    long mask = 0x1 << varId;
    long value = vars & mask;
    if (value) {
        return 1;
    } else {
        return 0;
    }
}

int not(Node *node, long vars) {
    Node *child = node->lhs;
    int expr = getOp(child->kind)(child, vars);
    int res = !expr;
    return res;
}

int and(Node *node, long vars) {
    Node *child = node->lhs;
    int lhs = getOp(child->kind)(child, vars);
    if (!lhs) {
        return 0;
    }

    child = node->rhs;
    int rhs = getOp(child->kind)(child, vars);
    return rhs;
}

int or(Node *node, long vars) {
    Node *child = node->lhs;
    int lhs = getOp(child->kind)(child, vars);
    if (lhs) {
        return 1;
    }

    child = node->rhs;
    int rhs = getOp(child->kind)(child, vars);
    return rhs;
}

int implies(Node *node, long vars) {
    Node *child = node->lhs;
    int lhs = getOp(child->kind)(child, vars);
    if (!lhs) {
        return 1;
    }

    child = node->rhs;
    int rhs = getOp(child->kind)(child, vars);
    return rhs;
}

int equals(Node *node, long vars) {
    Node *child = node->lhs;
    int lhs = getOp(child->kind)(child, vars);

    child = node->rhs;
    int rhs = getOp(child->kind)(child, vars);

    int res = rhs == lhs;
    return res;
}

// return the function for evaluating a node based on its kind
Op getOp(Kind kind) {
    switch (kind) {
        case VAR: return &var;
        case AND: return &and;
        case OR: return &or;
        case NOT: return &not;
        case IMPLIES: return &implies;
        case EQUALS: return &equals;
    }
}

int eval(Node *root, long vars) {
    int res = getOp(root->kind)(root, vars);
    return res;
}
