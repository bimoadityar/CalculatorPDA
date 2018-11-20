#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "Token.h"
#include "boolean.h"

Token readToken() {
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
}

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

Token currTkn, tknHasil;
static StackToken TknStck;
int lastPrecedence;
double a, b, temp;
char opr;

Token computeGan() {
	int lastPrecedence;
	double a, b, temp;
	char opr;
	Token currTkn, tknHasil;
	do {
		currTkn = readToken();
		if (op(currTkn) == 'n') {
			if (op(top(TknStck)) == 'n') {
				b = val(PopStack(&TknStck));
				val(currTkn) *= b;
			}
			PushStack(&TknStck, currTkn); 
		} else if (op(currTkn) == '(') {
			PushStack(&TknStck, currTkn);
			computeGan();
			PopStack(&TknStck);
			tknHasil = PopStack(&TknStck);
			PopStack(&TknStck);
			if (op(top(TknStck)) == 'n') {
				b = val(PopStack(&TknStck));
				val(tknHasil) *= b;
			} 
			PushStack(&TknStck, tknHasil);
		} else {
			if ((getPrecedence(currTkn) > lastPrecedence) || (lastPrecedence == 3 && getPrecedence(currTkn) == 3)) {
				PushStack(&TknStck, currTkn);
				lastPrecedence = getPrecedence(currTkn);
			} else {
				a = val(PopStack(&TknStck));
				opr = op(PopStack(&TknStck));
				b = val(PopStack(&TknStck));
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
				if (IsEmpty(TknStck)) {
					PushStack(&TknStck, tknHasil);
					PushStack(&TknStck, currTkn);
					lastPrecedence = getPrecedence(currTkn);
				} else {
					while (op(top(TknStck)) != '(') {
						opr = op(PopStack(&TknStck));
						b = val(PopStack(&TknStck));
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
					PushStack(&TknStck, tknHasil);
					PushStack(&TknStck, currTkn);
					lastPrecedence = getPrecedence(currTkn);
				}
			}
		}
		printf("lastPrecedence : %d\n", lastPrecedence);
		printStack(TknStck);
	} while (op(currTkn) != ')');
}

int main() {
	CreateEmpty(&TknStck);
	lastPrecedence = 0;
	do {
		currTkn = readToken();
		if (op(currTkn) == 'n') {
			if (op(top(TknStck)) == 'n') {
				b = val(PopStack(&TknStck));
				val(currTkn) *= b;
			}
			PushStack(&TknStck, currTkn);
		} else if (op(currTkn) == '(') {
			PushStack(&TknStck, currTkn);
			computeGan();
			PopStack(&TknStck);
			tknHasil = PopStack(&TknStck);
			PopStack(&TknStck);
			if (op(top(TknStck)) == 'n') {
				b = val(PopStack(&TknStck));
				val(tknHasil) *= b;
			} 
			PushStack(&TknStck, tknHasil);	
		} else {
			if ((getPrecedence(currTkn) > lastPrecedence) || (lastPrecedence == 3 && getPrecedence(currTkn) == 3)) {
				PushStack(&TknStck, currTkn);
				lastPrecedence = getPrecedence(currTkn);
			} else {
				a = val(PopStack(&TknStck));
				opr = op(PopStack(&TknStck));
				b = val(PopStack(&TknStck));
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
				if (IsEmpty(TknStck)) {
					PushStack(&TknStck, tknHasil);
					PushStack(&TknStck, currTkn);
					lastPrecedence = getPrecedence(currTkn);
				} else {
					while (!IsEmpty(TknStck)) {
						opr = op(PopStack(&TknStck));
						b = val(PopStack(&TknStck));
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
					PushStack(&TknStck, tknHasil);
					PushStack(&TknStck, currTkn);
					lastPrecedence = getPrecedence(currTkn);
				}
			}
		}
		printf("lastPrecedence : %d\n", lastPrecedence);
		printStack(TknStck);
	} while (op(currTkn) != '=');
	PopStack(&TknStck);
	printf("Hasil = %lf\n", val(PopStack(&TknStck)));
	return 0;
}