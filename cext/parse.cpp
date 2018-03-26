#include <stdlib.h>
#include "boole.h"

Node *toOpNode(Kind kind, Node *lhs, Node *rhs) {
    Node *node = new Node(kind, lhs, rhs);
    return node;
}

Node *toVarNode(int id) {
    Node *node = new Node(id);
    return node;
}

Node *parseBasic(int (*peek)(), int (*pop)()) {
    const int next = pop();

    if (next == TOKEN_LPAR) {
        Node *res =  parse(peek, pop);
        if (pop() != TOKEN_RPAR) {
            free(res);
            return NULL;
        }
        return res;

    } else if (next >= 0) {
        return toVarNode(next);

    } else {
        return NULL;
    }
}

Node *parseNot(int (*peek)(), int (*pop)()) {
    if (peek() == TOKEN_NOT) {
        pop();
        Node *child = parseBasic(peek, pop);
        if (child) {
            return toOpNode(NOT, child, NULL);
        } else {
            return NULL;
        }

    } else {
        return parseBasic(peek, pop);
    }
}

Node *parseAnd(int (*peek)(), int (*pop)()) {
    Node *lhs = parseNot(peek, pop);
    if (!lhs) {
        return NULL;
    }

    while (peek() == TOKEN_AND) {
        pop();
        Node * rhs = parseNot(peek, pop);
        if (!rhs) {
            free(lhs);
            return NULL;
        }
        lhs = toOpNode(AND, lhs, rhs);
    }

    return lhs;
}

Node *parseOr(int (*peek)(), int (*pop)()) {
    Node *lhs = parseAnd(peek, pop);
    if (!lhs) {
        return NULL;
    }

    while (peek() == TOKEN_OR) {
        pop();
        Node * rhs = parseAnd(peek, pop);
        if (!rhs) {
            free(lhs);
            return NULL;
        }
        lhs = toOpNode(OR, lhs, rhs);
    }

    return lhs;
}

Node *parseImplies(int (*peek)(), int (*pop)()) {
    Node *lhs = parseOr(peek, pop);
    if (!lhs) {
        return NULL;
    }

    const int next = peek();
    if (next == TOKEN_IMPL || next == TOKEN_IMPL_REVERSE) {
        pop();
        Node * rhs = parseOr(peek, pop);
        if (!rhs) {
            free(lhs);
            return NULL;
        }

        if (next == TOKEN_IMPL_REVERSE) {
            Node *tmp = lhs;
            lhs = rhs;
            rhs = tmp;
        }

        lhs = toOpNode(IMPLIES, lhs, rhs);
    }

    return lhs;
}

Node *parseEquals(int (*peek)(), int (*pop)()) {
    Node *lhs = parseImplies(peek, pop);
    if (!lhs) {
        return NULL;
    }

    const int next = peek();
    if (next == TOKEN_EQUALS) {
        pop();
        Node * rhs = parseImplies(peek, pop);
        if (!rhs) {
            free(lhs);
            return NULL;
        }

        lhs = toOpNode(EQUALS, lhs, rhs);
    }

    return lhs;
}

Node *parse(int (*peek)(), int (*pop)()) {
    return parseEquals(peek, pop);
}

void freeTree(Node *root) {
    if (root) {
        freeTree(root->lhs);
        freeTree(root->rhs);
        delete root;
    }
}
