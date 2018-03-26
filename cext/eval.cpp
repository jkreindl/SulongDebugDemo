/* Evaluate whether an assignment satisfies the formula AST. */
#include "boole.h"

int Node::eval(long vars) {
    int result = 0;
    switch (kind) {
        case VAR: {
            const int varId = this->varId;
            const long mask = 0x1 << varId;
            const long value = vars & mask;
            result = value ? 1 : 0;
            break;
        }
        case NOT: {
            result = this->lhs->eval(vars);
            result = !result;
            break;
        }
        case AND: {
            result = this->lhs->eval(vars);
            if (result) {
                result = this->rhs->eval(vars);
            }
            break;
        }
        case OR: {
            result = this->lhs->eval(vars);
            if (!result) {
                result = this->rhs->eval(vars);
            }
            break;
        }
        case IMPLIES: {
            result = this->lhs->eval(vars);
            if (!result) {
                result = 1;
            } else {
                result = this->rhs->eval(vars);
            }
            break;
        }
        case EQUALS: {
            const int _lhs = this->lhs->eval(vars);
            const int _rhs = this->rhs->eval(vars);
            result = _lhs == _rhs;
            break;
        }
    }
    return result;
}

int eval(Node *root, long vars) {
    int res = root->eval(vars);
    return res;
}
