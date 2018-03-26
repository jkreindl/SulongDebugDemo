#ifndef BOOLE_H
#define BOOLE_H

/* nodes in the AST of a boole formula */
enum Kind {
    VAR = 0, AND = 1, OR = 2,
    NOT = 3, IMPLIES = 4, EQUALS = 5
};
typedef enum Kind Kind;
class Node;
typedef int (*Op)(Node *node, long vars);
class Node {
public:
    Kind kind;
    Node *lhs;
    Node *rhs;
    int varId;
    Node(int _varId) : kind(VAR), lhs(0), rhs(0), varId(_varId) {};
    Node(Kind _kind, Node *_lhs, Node *_rhs) : kind(_kind), lhs(_lhs), rhs(_rhs), varId(-1) {};
    Op getOp();
};

/* parse a formula into an AST */
/* defined in parse.c */
int TOKEN_LPAR = -1; int TOKEN_RPAR = -2;
int TOKEN_NOT = -3; int TOKEN_EQUALS = -4;
int TOKEN_AND = -5; int TOKEN_OR = -6;
int TOKEN_IMPL = -7; int TOKEN_IMPL_REVERSE = -8;
Node *parse(int (*peek)(), int (*pop)());

/* check if an assignment satisfies the formula AST */
/* defined in eval.c */
int eval(Node *root, long vars);

/* deallocate the formula AST */
/* defined in eval.c */
void freeTree(Node *root);

#endif //BOOLE_H
