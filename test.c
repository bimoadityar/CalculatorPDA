#include "token.h"

int main () {
    setTokenStream();
    Token T;
    while (getNum(&T) != NOIN)
        printToken(T);
    stopTokenStream();

    return 0;
}