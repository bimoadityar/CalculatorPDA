#include "parsetoken.h"

int main () {
	setTokenStream();
	if (parseToken() == SUCC) {
		Token T;
		while (readToken(&T))
			printToken(T);
	}
	stopTokenStream();
	setTokenStream();
	if (parseToken() == SUCC) {
		Token T;
		while (readToken(&T))
			printToken(T);
	}
	stopTokenStream();
}