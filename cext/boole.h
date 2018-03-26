#ifndef BOOLE_H
#define BOOLE_H

/* nodes in the AST of a boole formula */
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

/* parse a formula into an AST */
/* defined in parse.c */
const int TOKEN_LPAR; const int TOKEN_RPAR;
const int TOKEN_NOT; const int TOKEN_EQUALS;
const int TOKEN_AND; const int TOKEN_OR;
const int TOKEN_IMPL; const int TOKEN_IMPL_REVERSE;
Node *parse(int (*peek)(), int (*pop)());

/* check if an assignment satisfies the formula AST */
/* defined in eval.c */
int eval(Node *root, long vars);

/* deallocate the formula AST */
/* defined in eval.c */
void freeTree(Node *root);

#endif //BOOLE_H
