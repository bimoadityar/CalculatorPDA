#ifndef token_H
#define token_H

#include "boolean.h"
#include <stdio.h>


#define ValUndef -9999

typedef struct {
    char op;
    double val;
} Token;
// If operator, the val is ValUndef, if number, the op is n

#define op(T) (T).op
#define val(T) (T).val




Token createOp (char opt);
Token createNum (double value);
void printToken (Token T);

extern FILE* ts;

void stopTokenStream ();
void setTokenStream ();
void ignoreBlank ();

#define SUCC 0
#define NOIN 1
#define UXIN 2

int getOp (Token* T);
int getNum (Token* T);

#endif