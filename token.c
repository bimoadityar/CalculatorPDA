#include "token.h"

Token createOp (char opt) {
    Token T;
    op(T) = opt;
    val(T) = ValUndef;
    return T;
}

Token createNum (double value) {
    Token T;
    op(T) = 'n';
    val(T) = value;
    return T;
}

void printToken (Token T) {
    printf("%c %lf\n", op(T), val(T));
}

FILE* ts;


void stopTokenStream () {
    if (ts != NULL) fclose(ts);
}

void setTokenStream () {
    stopTokenStream();
    ts = fopen("stream.txt", "w");
    char* s;
    scanf("%m[^\n]s", &s);
    fprintf(ts, "%s", s);
    fclose(ts);
    ts = fopen("stream.txt", "r");
}


int getOp (Token* T) {
    char opt;
    int x = fscanf(ts, "%c", &opt);
    if (x != 1) return NOIN;
    if (opt != '+' && opt != '-' && opt != '*' && opt != '/' && opt != '^')
        return UXIN;
    *T = createOp(opt);
    return SUCC;
}

int getNum (Token* T) {
    char c;
    int x = fscanf(ts, "%c", &c);
    if (x != 1) return NOIN;
    if ((c-'0' < 0 || c-'9' > 0) && c != '(' && c != ')') return UXIN;
    if (c == '(' || c == ')') *T = createOp(c);
    else {
        ungetc(c,ts);
        double d;
        fscanf(ts, "%lf", &d);
        *T = createNum(d);
    }
    return SUCC;
}
