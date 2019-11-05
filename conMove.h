#ifndef CON_MOVE_H_
#define CON_MOVE_H_

#include <string.h>
#include <stdio.h>
#include "IrMove.h"

bool FunctVal(char * inputCmd, FILE * outputPtr);
bool ConMove(char * inputCmd, FILE * outputPtr);
bool MathCmd(char * inputCmd, FILE * outputPtr);

bool ConMove(char * inputCmd, FILE * outputPtr)
{
	
	char * currentValue = strtok(inputCmd, " ");
	fputs("0010", outputPtr);
	if (!FunctVal(currentValue, outputPtr))
	{
		return false; 
	}
	currentValue = strtok(NULL, ",");
	if (!regiValue(currentValue, outputPtr))
	{
		return false;
	}
	currentValue = strtok(NULL, "\0");
	printf("current Value %s\n", currentValue);
	removeBack(currentValue);
	int regiBack = strlen(currentValue);
	if (strstr(currentValue,"\n"))
	{
		currentValue[regiBack - 1] = '\0';
	}
	if (!regiValue(currentValue, outputPtr))
	{
		return false;
	}
	fputs("\n", outputPtr);
	return true; 
}
bool FunctVal(char * inputCmd, FILE * outputPtr)
{
	//printf("this works right %s\n", inputCmd);
	if (strcmp(inputCmd,"rrmovq") == 0 || strcmp(inputCmd,"addq") == 0)
	{
		fputs("0000",outputPtr);
	}
	else if (strcmp(inputCmd, "cmovle") == 0 || strcmp(inputCmd, "subq") == 0)
	{
		fputs("0001", outputPtr);
	}
	else if (strcmp(inputCmd, "cmovl") == 0 || strcmp(inputCmd, "andq") == 0)
	{
		fputs("0010", outputPtr);
	}
	else if (strcmp(inputCmd, "cmove") == 0 || strcmp(inputCmd, "xorq") == 0)
	{
		fputs("0011", outputPtr);
	}
	else if (strcmp(inputCmd, "cmovne") == 0)
	{
		fputs("0100", outputPtr);
	}
	else if (strcmp(inputCmd, "cmovge") == 0)
	{
		fputs("0101", outputPtr);
	}
	else if (strcmp(inputCmd, "cmovg") == 0)
	{
		fputs("0110", outputPtr);
	}
	else
	{
		return false;
	}
	return true;

}
bool MathCmd(char * inputCmd, FILE* outputPtr)
{
	char * currentValue = strtok(inputCmd, " ");
	fputs("0110", outputPtr);
	if (!FunctVal(currentValue, outputPtr))
	{
		return false;
	}
	currentValue = strtok(NULL, ",");
	printf("current Value %s\n", currentValue);
	if (!regiValue(currentValue, outputPtr))
	{
		return false;
	}
	currentValue = strtok(NULL, "\0");
	removeBack(currentValue);
	int regiBack = strlen(currentValue);
	if (strstr(currentValue, "\n"))
	{
		currentValue[regiBack - 1] = '\0';
	}
	if (!regiValue(currentValue, outputPtr))
	{
		return false;
	}
	fputs("\n", outputPtr);
	return true;

}




#endif