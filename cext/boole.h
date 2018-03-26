#ifndef BOOLE_H
#define BOOLE_H
/* nodes in the AST of a boole formula */
typedef enum Kind { VAR = 0, AND = 1, OR = 2, NOT = 3, IMPLIES = 4, EQUALS = 5 } Kind;
class Node {
public:
    Kind kind; int varId; Node *lhs; Node *rhs;
    Node(int _varId) : kind(VAR), varId(_varId), lhs(0), rhs(0) {};
    Node(Kind _kind, Node *_lhs, Node *_rhs) : kind(_kind), varId(-1), lhs(_lhs), rhs(_rhs) {};
    int eval(long vars);
};

/* parse a formula into an AST ; defined in parse.cpp */
int TOKEN_LPAR = -1; int TOKEN_RPAR = -2; int TOKEN_NOT = -3; int TOKEN_EQUALS = -4;
int TOKEN_AND = -5; int TOKEN_OR = -6; int TOKEN_IMPL = -7; int TOKEN_IMPL_REVERSE = -8;
Node *parse(int (*peek)(), int (*pop)());

/* check if an assignment satisfies the formula AST ; defined in eval.cpp */
int eval(Node *root, long vars);

/* deallocate the formula AST ; defined in eval.cpp */
void freeTree(Node *root);
#endif //BOOLE_H
