#ifndef TOKEN_GEN_H
#define TOKEN_GEN_H

#include <stdbool.h>

#include "globals.h"

void tokenGenerator(char* srcPtr, Token** tknArrPtr);
bool varDecVerify(char** tknArrPtr, int tknIdx);

#endif

