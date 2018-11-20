#include "calculator.h"

int main () {
    while (true) {
        printf(">> ");
        setTokenStream();
        printf("%d\n", calc());
        stopTokenStream();
    }
}