#include "stacktoken.h"

void createEmpty (StackToken* S) {
    topAd(*S) = Nil;
}

boolean isEmpty (StackToken S) {
    return topAd(S) == Nil;
}

boolean isFull (StackToken S) {
    return topAd(S) == MaxEl;
}

boolean push (StackToken* S, Token T) {
    if (isFull(*S)) return false;
    ++topAd(*S);
    top(*S) = T;
    return true;
}

boolean pop (StackToken* S, Token* T) {
    if (isEmpty(*S)) return false;
    *T = top(*S);
    --topAd(*S);
    return true;
}

void printStack (StackToken S) {
    Token currTkn;
    printf("[");
    while (!isEmpty(S)) {

       	pop(&S, &currTkn);
        printf("(%c, %lf)", op(currTkn), val(currTkn));
    }
    printf("]\n");
}