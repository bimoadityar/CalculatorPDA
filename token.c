#include "token.h"
#include <stdlib.h>

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
    char s[100];
    scanf("%[^\n]s", &s);
    fprintf(ts, "%s", s);
    char c;
    scanf("%c", &c);
    fflush(stdin);
    fclose(ts);
    ts = fopen("stream.txt", "r");
}

void ignoreBlank () {
    char c;
    int x;
    do {
        x = fscanf(ts, "%c", &c);
    } while (x == 1 && c == ' ');
    if (x == 1) ungetc(c,ts);
}

int getOp (Token* T) {
    ignoreBlank();
    char opt;
    int x = fscanf(ts, "%c", &opt);
    if (x != 1) return NOIN;
    if (opt != '+' && opt != '-' && opt != '*' && opt != '/' && opt != '^' && opt != ')' && (opt-'0' < 0 || opt-'9' > 0) && opt != '(')
        return UXIN;
    if (opt-'0' >= 0 && opt-'9' <= 0) {
        ungetc(opt,ts);
        double d;
        fscanf(ts,"%lf",&d);
        *T = createNum(d);
    } else *T = createOp(opt);
    return SUCC;
}

int getNum (Token* T) {
    ignoreBlank();
    char c;
    int x = fscanf(ts, "%c", &c);
    if (x != 1) return NOIN;
    if ((c-'0' < 0 || c-'9' > 0) && c != '+' && c != '-' && c != '(')
        return UXIN;
    if (c == '(') *T = createOp(c);
    else {
        if (c == '+' || c == '-') {
            char d;
            fscanf(ts, "%c", &d);
            if (d-'0' < 0 || d-'9' > 0) return UXIN;
            ungetc(d,ts);
        }
        ungetc(c,ts);
        double d;
        fscanf(ts, "%lf", &d);
        *T = createNum(d);
    }
    return SUCC;
}