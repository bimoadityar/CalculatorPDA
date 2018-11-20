#ifndef stacktoken_H
#define stacktoken_H

#include "boolean.h"
#include "token.h"

#define Nil 0
#define MaxEl 100

typedef struct {
    Token T[MaxEl+1];
    int topAd;
} StackToken;

#define topAd(S) (S).topAd
#define top(S) (S).T[(S).topAd]

void createEmpty (StackToken* S);
boolean isEmpty (StackToken S);
boolean isFull (StackToken S);
boolean push (StackToken* S, Token T);
boolean pop (StackToken* S, Token T);

#endif