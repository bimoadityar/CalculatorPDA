#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "boolean.h"
#include "parsetoken.h"
#include "calcF.c"

Token currTkn, tknHasil,x;
static StackToken TknStck;
int lastPrecedence;
double a, b, temp;
char opr;
boolean retVal;
Token arrToken[MaxEl+1];
int last,now;

int main() {
	printf("***********************SELAMAT DATANG DI TUBES TBFO***********************\n\n");
	printf("Kelas K1\n");
	printf("Bimo Adityarahman Wiraputra/13517004\n");
	printf("Hafidh Rendyanto/13517061\n");
	printf("Naufal Aditya Dirgandhavi/13517064\n\n");
	int lanjut=1;
	while (lanjut==1) {
		compute();		
		printf("Lanjut? [1 untuk Ya] ");
		scanf("%d", &lanjut);
		char c;
		scanf("%c", &c);
	}	
	printf("Terima kasih!\n");
	return 0;
}