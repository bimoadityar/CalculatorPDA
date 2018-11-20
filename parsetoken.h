#ifndef parsetoken_H
#define parsetoken_H

#include "stacktoken.h"

extern Token arrToken[MaxEl+1];
extern int last;
extern int now;

int parseToken ();
boolean readToken (Token* T);


#endif