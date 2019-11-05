#ifndef RM_MOVE_H_
#define RM_MOVE_H_

#include <stdio.h>
#include <string.h>
#include "IrMove.h"

#pragma warning(disable : 4996)
char * RmMove(char * userInput, FILE * outputPtr)
{
	const int CLEAN_UP_REGI_ID = 4; 
	char * initialPtr = strtok(userInput, " ");
	if (initialPtr == NULL || checkItem(initialPtr, "rmmovq"))// check for initial keyword 
	{
		return "";
	}
	fputs("00100000", outputPtr);
	initialPtr = strtok(NULL, ",");
	if (!regiValue(initialPtr, outputPtr))
	{
		return "";
	}
	initialPtr = strtok(NULL, "(");
	char regiVals[60];
	strcpy(regiVals, initialPtr);
	char * secondToken = strtok(NULL, ")");
	secondToken[CLEAN_UP_REGI_ID] = '\0';
	//printf("regiVals %s \n", initialPtr);
	if (!regiValue(secondToken, outputPtr))
	{
		return "";
	}
	removeBack(regiVals);
	if (regiVals[1] == 'x')
	{
		//printf("inputs Item %s\n", regiVals);
		removeBack(regiVals);
		removeBack(regiVals);
		//printf("inputs Item %s\n", regiVals);
		HexToBin(regiVals, outputPtr);
	}
	else
	{
		//printf("this is a thing%s\n", regId);
		binaryRep(regiVals, outputPtr);
	}
	return "OKAY";
}

char * MrMove(char * userInput, FILE * outputPtr)
{
	const int CLEAN_UP_REGI_ID = 4;
	char * initialPtr = strtok(userInput, " ");
	char firstRegi[60];
	if (initialPtr == NULL || checkItem(initialPtr, "mrmovq"))// check for initial keyword 
	{
		return "";
	}
	fputs("01010000", outputPtr);
	char regiVals[60];
	if (userInput[7] != '(')
	{
		initialPtr = strtok(NULL, "(");
		if (initialPtr == NULL) { return ""; }
		strcpy(regiVals, initialPtr);
	}
	else
	{
		initialPtr = strtok(NULL, ")");
		if (initialPtr == NULL) { return ""; }
		removeBack(initialPtr);
		strcpy(firstRegi, initialPtr);
	}
	char secondRegi[60];
	initialPtr = strtok(NULL, ", ");
	strcpy(secondRegi, initialPtr);
	if (initialPtr == NULL) { return ""; }
	//printf("regiValues %s\n", initialPtr);

	initialPtr = strtok(NULL, "\0");
	if (initialPtr != NULL)
	{
		removeBack(initialPtr);
		initialPtr[4] = '\0';
		if (!regiValue(initialPtr, outputPtr))
		{
			return "";
		}
		secondRegi[4] = '\0';
		if (!regiValue(secondRegi, outputPtr))
		{
			return "";
		}
	}
	else
	{
		firstRegi[4] = '\0';

		if (!regiValue(firstRegi, outputPtr))
		{
			return "";
		}
		secondRegi[4] = '\0';
		if (!regiValue(secondRegi, outputPtr))
		{
			return "";
		}
	}
	if (regiVals[1] == 'x')
	{
		removeBack(regiVals);
		removeBack(regiVals);
		HexToBin(regiVals, outputPtr);
	}
	else
	{
		binaryRep(regiVals, outputPtr);
	}
	return "OKAY";
}

#endif
