#include "parsetoken.h"

Token arrToken[MaxEl+1];
int last,now;

int parseToken () {
    last = 1;
    int status = SUCC;
    arrToken[1] = createOp('(');
    int openPrnth = 1;
    Token T;
    while (status == SUCC) {
        if (op(arrToken[last]) == 'n' || op(arrToken[last]) == ')')
            status = getOp(&T);
        else status = getNum(&T);
        if (status == SUCC) {
            ++last;
            arrToken[last] = T;
            if (op(T) == '(') ++openPrnth;
            else if (op(T) == ')') --openPrnth;
            if (openPrnth <= 0) status = UXIN;
        }
    }
    if (status == UXIN || (op(arrToken[last]) != 'n' && op(arrToken[last]) != ')' )) status = UXIN;
    ++last;
    arrToken[last] = createOp(')');
    if (status == UXIN) return UXIN;
    now = 1;
    return SUCC;
}

boolean readToken (Token* T) {
    if (now > last) return false;
    *T = arrToken[now];
    ++now;
    return true;
}