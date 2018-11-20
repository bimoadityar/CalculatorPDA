#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "boolean.h"
#include "parsetoken.h"

void printStack (StackToken S) {
    Token currTkn;
    printf("[");
    while (!isEmpty(S)) {

       	pop(&S, &currTkn);
        printf("(%c, %lf)", op(currTkn), val(currTkn));
    }
    printf("]\n");
}

/*Token readToken() {
	char S[100];
	Token Temp;
	scanf("%s", S);
	if ((strcmp(S, "+") != 0) && (strcmp(S, "-") != 0) && (strcmp(S, "*") != 0)	&& (strcmp(S, "/") != 0) && (strcmp(S, "^") != 0) && (strcmp(S, "=") != 0) && (strcmp(S, "(") != 0) && (strcmp(S, ")") != 0)) {
		op(Temp) = 'n';
		val(Temp) = atof(S);
	} else {
		op(Temp) = S[0];
		val(Temp) = ValUndef;
	}
	return Temp;
}*/

int getPrecedence(Token Tkn) {
	if ((op(Tkn) == '+') || (op(Tkn) == '-')) {
		return 1;
	} else if ((op(Tkn) == '*') || (op(Tkn) == '/')) {
		return 2;
	} else if (op(Tkn) == '^') {
		return 3;
	} else {
		return 0;
	}
}

Token currTkn, tknHasil,x;
static StackToken TknStck;
int lastPrecedence;
double a, b, temp;
char opr;

Token computeGan() {
	int lastPrecedence;
	double a, b, temp;
	char opr;
	Token currTkn, tknHasil,x;
	int i = 0;
	do {
		i++;
		if (i>7){
			break;
		}
		readToken(&currTkn);
		if (op(currTkn) == 'n') {
			if (op(top(TknStck)) == 'n') {
				pop(&TknStck, &x);
				b = val(x);
				val(currTkn) *= b;
			}
			push(&TknStck, currTkn); 
		} else if (op(currTkn) == '(') {
			push(&TknStck, currTkn);
			computeGan();
			pop(&TknStck, &x);
			pop(&TknStck, &tknHasil);
			pop(&TknStck, &x);
			if (op(top(TknStck)) == 'n') {
				pop(&TknStck, &x);
				b = val(x);
				val(tknHasil) *= b;
			} 
			push(&TknStck, tknHasil);
		} else {
			if ((getPrecedence(currTkn) > lastPrecedence) || (lastPrecedence == 3 && getPrecedence(currTkn) == 3)) {
				push(&TknStck, currTkn);
				lastPrecedence = getPrecedence(currTkn);
			} else {
				pop(&TknStck, &x);
				a = val(x);
				pop(&TknStck, &x);
				opr = op(x);
				pop(&TknStck, &x);
				b = val(x);
				if (opr == '+') {
					op(tknHasil) = 'n';
					val(tknHasil) = b + a;
				} else if (opr == '-') {
					op(tknHasil) = 'n';
					val(tknHasil) = b - a;
				} else if (opr == '*') {
					op(tknHasil) = 'n';
					val(tknHasil) = b * a;
				} else if (opr == '/') {
					op(tknHasil) = 'n';
					val(tknHasil) = b / a;
				} else if (opr == '^') {
					op(tknHasil) = 'n';
					val(tknHasil) = pow(b, a);
				} else {
					printf("Token Salah!\n");
				}
				if (isEmpty(TknStck)) {
					push(&TknStck, tknHasil);
					push(&TknStck, currTkn);
					lastPrecedence = getPrecedence(currTkn);
				} else {
					while (op(top(TknStck)) != '(') {
						pop(&TknStck, &x);
						opr = op(x);
						pop(&TknStck, &x);
						b = val(x);
						if (opr == '+') {
							op(tknHasil) = 'n';
							temp = b + val(tknHasil);
							val(tknHasil) = temp;
						} else if (opr == '-') {
							op(tknHasil) = 'n';
							temp = b - val(tknHasil);
							val(tknHasil) = temp;
						} else if (opr == '*') {
							op(tknHasil) = 'n';
							temp = b * val(tknHasil);
							val(tknHasil) = temp;
						} else if (opr == '/') {
							op(tknHasil) = 'n';
							temp = b / val(tknHasil);
							val(tknHasil) = temp;
						} else if (opr == '^') {
							op(tknHasil) = 'n';
							val(tknHasil) = pow(b, val(tknHasil));
						} else {
							printf("Token Salah!\n");
						}
					}
					push(&TknStck, tknHasil);
					push(&TknStck, currTkn);
					lastPrecedence = getPrecedence(currTkn);
				}
			}
		}
		printf("lastPrecedence : %d\n", lastPrecedence);
		printStack(TknStck);
	} while (op(currTkn) != ')');
}

boolean retVal;
Token arrToken[MaxEl+1];
int last,now;

int main() {
	createEmpty(&TknStck);
	setTokenStream();
	if (parseToken() != SUCC) printf("eror gan\n");
	else {
		int i = 0;
		lastPrecedence = 0;
		do {
			i++;
			retVal = readToken(&currTkn);
			if (op(currTkn) == 'n') {
				if (op(top(TknStck)) == 'n') {
					pop(&TknStck, &x);
					b = val(x);
					val(currTkn) *= b;
				}
				push(&TknStck, currTkn);
			} else if (op(currTkn) == '(') {
				push(&TknStck, currTkn);
				computeGan();
				pop(&TknStck, &x);
				pop(&TknStck, &tknHasil);
				pop(&TknStck, &x);
				if (op(top(TknStck)) == 'n') {
					pop(&TknStck, &x);
					b = val(x);
					val(tknHasil) *= b;
				} 
				push(&TknStck, tknHasil);	
			} else {
				if ((getPrecedence(currTkn) > lastPrecedence) || (lastPrecedence == 3 && getPrecedence(currTkn) == 3)) {
					push(&TknStck, currTkn);
					lastPrecedence = getPrecedence(currTkn);
				} else {
					pop(&TknStck, &x);
					a = val(x);
					pop(&TknStck, &x);
					opr = op(x);
					pop(&TknStck, &x);
					b = val(x);
					if (opr == '+') {
						op(tknHasil) = 'n';
						val(tknHasil) = b + a;
					} else if (opr == '-') {
						op(tknHasil) = 'n';
						val(tknHasil) = b - a;
					} else if (opr == '*') {
						op(tknHasil) = 'n';
						val(tknHasil) = b * a;
					} else if (opr == '/') {
						op(tknHasil) = 'n';
						val(tknHasil) = b / a;
					} else if (opr == '^') {
						op(tknHasil) = 'n';
						val(tknHasil) = pow(b, a);
					} else {
						printf("Token Salah!\n");
					}
					if (isEmpty(TknStck)) {
						push(&TknStck, tknHasil);
						push(&TknStck, currTkn);
						lastPrecedence = getPrecedence(currTkn);
					} else {
						while (!isEmpty(TknStck)) {
							pop(&TknStck, &x);
							opr = op(x);
							pop(&TknStck, &x);
							b = val(x);
							if (opr == '+') {
								op(tknHasil) = 'n';
								temp = b + val(tknHasil);
								val(tknHasil) = temp;
							} else if (opr == '-') {
								op(tknHasil) = 'n';
								temp = b - val(tknHasil);
								val(tknHasil) = temp;
							} else if (opr == '*') {
								op(tknHasil) = 'n';
								temp = b * val(tknHasil);
								val(tknHasil) = temp;
							} else if (opr == '/') {
								op(tknHasil) = 'n';
								temp = b / val(tknHasil);
								val(tknHasil) = temp;
							} else if (opr == '^') {
								op(tknHasil) = 'n';
								val(tknHasil) = pow(b, val(tknHasil));
							} else {
								printf("Token Salah!\n");
							}
						}
						push(&TknStck, tknHasil);
						push(&TknStck, currTkn);
						lastPrecedence = getPrecedence(currTkn);
					}
				}
			}
			printf("lastPrecedence : %d\n", lastPrecedence);
			printStack(TknStck);
		} while (retVal);
		pop(&TknStck, &x);
		pop(&TknStck, &x);
		printf("Hasil = %lf\n", val(x));
	}
	stopTokenStream();
	return 0;
}