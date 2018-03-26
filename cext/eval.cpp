#include "boole.h"

int eval_VAR(Node *node, long vars);
int eval_NOT(Node *node, long vars);
int eval_AND(Node *node, long vars);
int eval_OR(Node *node, long vars);
int eval_IMPLIES(Node *node, long vars);
int eval_EQUALS(Node *node, long vars);

int eval_VAR(Node *node, long vars) {
    int varId = node->varId;
    long mask = 0x1 << varId;
    long value = vars & mask;
    if (value) {
        return 1;
    } else {
        return 0;
    }
}

int eval_NOT(Node *node, long vars) {
    Node *child = node->lhs;
    int expr = child->getOp()(child, vars);
    int res = !expr;
    return res;
}

int eval_AND(Node *node, long vars) {
    Node *child = node->lhs;
    int lhs = child->getOp()(child, vars);
    if (!lhs) {
        return 0;
    }

    child = node->rhs;
    int rhs = child->getOp()(child, vars);
    return rhs;
}

int eval_OR(Node *node, long vars) {
    Node *child = node->lhs;
    int lhs = child->getOp()(child, vars);
    if (lhs) {
        return 1;
    }

    child = node->rhs;
    int rhs = child->getOp()(child, vars);
    return rhs;
}

int eval_IMPLIES(Node *node, long vars) {
    Node *child = node->lhs;
    int lhs = child->getOp()(child, vars);
    if (!lhs) {
        return 1;
    }

    child = node->rhs;
    int rhs = child->getOp()(child, vars);
    return rhs;
}

int eval_EQUALS(Node *node, long vars) {
    Node *child = node->lhs;
    int lhs = child->getOp()(child, vars);

    child = node->rhs;
    int rhs = child->getOp()(child, vars);

    int res = rhs == lhs;
    return res;
}

Op Node::getOp() {
    switch (kind) {
        case VAR: return &eval_VAR;
        case AND: return &eval_AND;
        case OR: return &eval_OR;
        case NOT: return &eval_NOT;
        case IMPLIES: return &eval_IMPLIES;
        case EQUALS: return &eval_EQUALS;
    }
}

int eval(Node *root, long vars) {
    int res = root->getOp()(root, vars);
    return res;
}
