#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "boolean.h"
#include "parsetoken.h"

Token currTkn, tknHasil,x;
static StackToken TknStck;
int lastPrecedence;
double a, b, temp;
char opr;
boolean retVal;
Token arrToken[MaxEl+1];
int last,now;

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
Token computeGan() { //untuk dalam kurung
	int lastPrecedence;
	double a, b, temp;
	char opr;
	Token currTkn, tknHasil,x;
	lastPrecedence = 0;
	boolean retVal = false;
	do {
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
				if (op(top(TknStck)) == '(') {
					opr = '+';
					b = 0;
				} else {
					pop(&TknStck, &x);
					opr = op(x);
					pop(&TknStck, &x);
					b = val(x);
				}
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
		//printf("lastPrecedence : %d\n", lastPrecedence);
		//printStack(TknStck);
	} while (op(currTkn) != ')');
}

double compute() {
	createEmpty(&TknStck);
	printf(">> ");
	setTokenStream();
	if (parseToken() != SUCC) {
		printf("SYNTAX ERROR\n");	
	} else {
		lastPrecedence = 0;
		do {
			retVal = readToken(&currTkn);
			if (!retVal) {
				op(currTkn) = '=';
				val(currTkn) = ValUndef;
			}
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
					if (isEmpty(TknStck)) {
						opr = '+';
						b=0;
					}else{
						pop(&TknStck, &x);
						opr = op(x);
						pop(&TknStck, &x);
						b = val(x);
					}
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
			//printf("lastPrecedence : %d\n", lastPrecedence);
			//printStack(TknStck);
		} while (retVal);
		pop(&TknStck, &x);
		pop(&TknStck, &x);
		if (isnan(val(x))||val(x)==INFINITY) {
			printf("MATH ERROR\n");
		} else {
			printf("Hasil = %lf\n", val(x));
		}
	}
	
}