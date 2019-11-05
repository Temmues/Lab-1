#include <stdio.h>
#include <string.h>
#include "IrMove.h"
#include "RmMove.h"
#include "conMove.h"

#pragma warning(disable : 4996)

bool checkCon(char * inputCmd);

int main(int argc, char** argv)
{
	if (argc < 1)
	{
		fprintf(stderr,"You need some files!");
	}
	FILE  * inputPtr = NULL;			//open and check input File

	fopen_s(&inputPtr, argv[1], "r");
	if (inputPtr == NULL)
	{
		fprintf(stderr,"Input files missing\n");
		return -1;
	}
	if (!strstr(argv[1], ".c\0"))			// exit if .c extension not found
	{
		fprintf(stderr, "Inputput file format incorrect.\n Please use a file with the .o extension\n");
		return -1;
	} 

	char * outFileName = argv[1];	//createNew string and replace .c with .o
	outFileName[strlen(outFileName) - 1] = 'o';
	FILE * outputPtr = fopen(outFileName, "w");		//create output file
	char inputStr[60];
	int lineCounter = 0; 
	while (fgets(inputStr,60,inputPtr)) { // to output file 
		if (strstr(inputStr, "halt"))
		{
			fputs("00000000", outputPtr);
		}
		else if (strstr(inputStr,"nop"))
		{
			fputs("00010000", outputPtr);
		}
		else if (strstr(inputStr, "irmovq"))
		{
			if (IrMove(inputStr, lineCounter, outputPtr) == "")
			{
				fprintf(stderr, "Invalid instruction found on line %d\n", lineCounter);
				return -1;
			}
		}
		else if (strstr(inputStr, "rmmovq"))
		{
			if (RmMove(inputStr,outputPtr) == "")
			{
				fprintf(stderr, "Invalid instruction found on line %d\n", lineCounter);
				return -1;
			}
		}
		else if (strstr(inputStr, "mrmovq"))
		{
			if (MrMove(inputStr, outputPtr) == "")
			{
				fprintf(stderr, "Invalid instruction found on line %d\n", lineCounter);
				return -1;
			}
		}
		else if(checkCon(inputStr))
		{
			if (!ConMove(inputStr, outputPtr))
			{
				fprintf(stderr, "Invalid instruction found on line %d\n", lineCounter);
				return -1;
			}
		}
		else if (strstr(inputStr, "addq") || strstr(inputStr, "subq") || strstr(inputStr, "andq") || strstr(inputStr, "xorq"))
		{
			if (!MathCmd(inputStr, outputPtr))
			{
				fprintf(stderr, "Invalid instruction found on line %d\n", lineCounter);
				return -1;
			}
		}
		else
		{
			fprintf(stderr, "Invalid instruction found on line %d\n", lineCounter);
			return -1;
		}
		
		lineCounter++;
	} 
	fclose(inputPtr); // close file
	return 0;
}

bool checkCon(char * inputCmd)
{
	if (strstr(inputCmd, "rrmovq"))
	{
		return true;
	}
	else if (strstr(inputCmd, "cmovle"))
	{
		return true;
	}
	else if (strstr(inputCmd, "cmovl"))
	{
		return true;
	}
	else if (strstr(inputCmd, "cmove"))
	{
		return true;
	}
	else if (strstr(inputCmd, "cmovne"))
	{
		return true;
	}
	else if (strstr(inputCmd, "cmovge"))
	{
		return true; 
	}
	else if (strstr(inputCmd, "cmovg"))
	{
		return true;
	}
	else
	{
		return false;
	}
}
