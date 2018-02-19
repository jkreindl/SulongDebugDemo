#ifndef BOOLE_H
#define BOOLE_H

typedef enum Kind Kind;
enum Kind {
    VAR = 0,
    AND = 1,
    OR = 2,
    NOT = 3,
    IMPLIES = 4,
    EQUALS = 5
};

typedef struct Node Node;
struct Node {
    Kind kind;
    Node *lhs;
    Node *rhs;
    int varId;
};

Node *parse(int (*peek)(), int (*pop)());

int eval(Node *root, long vars);

void freeTree(Node *root);

#endif //BOOLE_H
