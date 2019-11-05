#ifndef IRMOVE_H_
#define IRMOVE_H_
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#include "Registar.h"


void binaryRep(char * inputItem, FILE * outputPtr);
void HexToBin(char * inputItem, FILE * outputPtr);
int checkItem(char * inputItem, char * compareItem);
char * IrMove(char * userInput, int lineNum, FILE * outputPtr);
bool regiValue(char * inputRegi, FILE * outputPtr);




#endif // !IRMOVE_H_

