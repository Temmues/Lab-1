#include "IrMove.h"
#include "hexCon.h"
#pragma warning(disable : 4996)

void removeBack(char * inputItem)
{
	for (unsigned int i = 0; i < strlen(inputItem); i++)
	{
		if (i != strlen(inputItem))
		{
			inputItem[i] = inputItem[i + 1];
		}
	}
}
bool regiValue(char * inputRegi, FILE * outputPtr)
{
	if (strcmp(inputRegi, "F") == 0)
	{
		fputs("1111", outputPtr);
	}
	else if (strcmp(inputRegi, "%r14") == 0)
	{
		fputs("1110", outputPtr);
	}
	else if (strcmp(inputRegi, "%r13") == 0)
	{
		fputs("1101", outputPtr);
	}
	else if (strcmp(inputRegi, "%r12") == 0)
	{
		fputs("1100", outputPtr);
	}
	else if (strcmp(inputRegi, "%r11") == 0)
	{
		fputs("1011", outputPtr);
	}
	else if (strcmp(inputRegi, "%r10") == 0)
	{
		fputs("1010", outputPtr);
	}
	else if (strcmp(inputRegi, "%r9") == 0)
	{
		fputs("1001", outputPtr);
	}
	else if (strcmp(inputRegi, "%r8") == 0)
	{
		fputs("1000", outputPtr);
	}
	else if (strcmp(inputRegi, "%rdi") == 0)
	{
		fputs("0111", outputPtr);
	}
	else if (strcmp(inputRegi, "%rsi") == 0)
	{
		fputs("0110", outputPtr);
	}
	else if (strcmp(inputRegi, "%rbp") == 0)
	{
		fputs("0101", outputPtr);
	}
	else if (strcmp(inputRegi, "%rsp") == 0)
	{
		fputs("0100", outputPtr);
	}
	else if (strcmp(inputRegi, "%rbx") == 0)
	{
		fputs("0011", outputPtr);
	}
	else if (strcmp(inputRegi, "%rdx") == 0)
	{
		fputs("0010", outputPtr);
	}
	else if (strcmp(inputRegi, "%rcx") == 0)
	{
		fputs("0001", outputPtr);
	}
	else if (strcmp(inputRegi, "%rax") == 0)
	{
		fputs("0000", outputPtr);
	}
	else
	{
		return false;
	}
	return true;
}

char * IrMove(char * userInput, int lineNum, FILE * outputPtr) // checks intructions and returns a string of binary if valid or an empty string if false
{
	const int TOKEN_COUNT = 3;
	const int CLEAN_UP_REGI_ID = 4;
	int cmdSize = strlen(userInput);
	char * initialPtr = strtok(userInput, " ");
	if (initialPtr == NULL || strcmp(initialPtr, "irmovq") != 0)// check for initial keyword 
	{
		return "";
	}
	fputs("00110000", outputPtr);

	if (!regiValue("F", outputPtr))
	{
		return "";
	}
	//printf("inputs Item %s\n", initialPtr);
	initialPtr = strtok(NULL, ","); // update initial Ptr
	if (initialPtr == NULL || initialPtr[0] != '$')
	{	
		return "";
	}
	removeBack(initialPtr);
	char regId[60]; 
	strcpy(regId, initialPtr);
	initialPtr = strtok(NULL, " ");
	if (strstr(initialPtr,"\n"))
	{
		initialPtr[CLEAN_UP_REGI_ID] = '\0';
	}
	
	
	if (!regiValue(initialPtr, outputPtr))
	{
		return "";
	}
	if (regId[1] == 'x')
	{
		//printf("inputs Item %s\n", regId);
		removeBack(regId);
		removeBack(regId);
		//printf("inputs Item %s\n", regId);
		HexToBin(regId, outputPtr);
	}
	else
	{
		//printf("this is a thing%s\n", regId);
		binaryRep(regId, outputPtr);
	}
	
	return "OKAY";
}
int checkItem(char * inputItem, char * compareItem)
{
	bool errorFlag = false;
	if (strncmp(inputItem, compareItem, strlen(compareItem) != 0))
	{
		errorFlag = true;
	}
	return errorFlag;
}
void binaryRep(char * inputItem, FILE * outputPtr)
{
	const int BIT_NUM = 8; 
	const int LAST_ITERATION = 15;
	const int ITERATION_NUM = 4; 
	int bufferVal = 0;
	bufferVal = atoi(inputItem);
	char littleEnd[33];
	char binaryRep[33];
	int k = 0;
	for (int i = 31; i >= 0; i--)
	{
		int input = bufferVal >> i;

		if (input & 1)
		{
			binaryRep[k] = '1';
		}
		else
		{
			binaryRep[k] = '0';
		}
		k++;
	}
	printf("binaryRep %s\n", binaryRep);
	int outerBound = 31;
	// or have a nested loop
	k = 0; 
	int byteDelim = 32;
	for (unsigned int j = 0; j < ITERATION_NUM; j++)
	{
		
		for (unsigned int i = byteDelim - 8; i < byteDelim; i++)
		{
			littleEnd[k] = binaryRep[i];
			k++;
		}
		if (byteDelim == LAST_ITERATION)
		{
			byteDelim -= BIT_NUM - 1;
		}
		else
		{
			byteDelim -= BIT_NUM;
		}
	}
	littleEnd[32] = '\0';
	printf("our little endian binary: %s\n", littleEnd);
	fputs(littleEnd, outputPtr);
	fputs("\n", outputPtr);
}

void HexToBin(char * inputItem, FILE * outputPtr)
{
	char newList[17];
	char littleEnRep[17];
	int topIndex = 16;
	int inputItemSize = 0;
	int j = 0;
	while (inputItem[inputItemSize] != '\0')
	{
		inputItemSize++;
	}
	for (int i = 0; i < topIndex; i++)
	{
		if (i >= topIndex - inputItemSize)
		{
			newList[i] = inputItem[i - (topIndex - inputItemSize)];
		}
		else
		{
			newList[i] = '0';
		}
	}
	newList[topIndex] = '\0';
	int outerBound = topIndex - 1;
	for (int i = 0; i < 16; i += 2) {
		littleEnRep[i] = newList[outerBound - i - 1];
		littleEnRep[i + 1] = newList[outerBound - i];
	}
	littleEnRep[topIndex] = '\0';
	char binValue[65];
	for (int i = 0; i < 16; i++)
	{
		switch (littleEnRep[i])
		{
		case('0'):
			if (i == 0) { strcpy(binValue, "0000"); }
			else
			{
				strcat(binValue, "0000");
			}
			break;
		case('1'):
			if (i == 0) { strcpy(binValue, "0001"); }
			else
			{
				strcat(binValue, "0001");
			}
			break;
		case('2'):
			if (i == 0) { strcpy(binValue, "0010"); }
			else
			{
				strcat(binValue, "0010");
			}
			break;
		case('3'):
			if (i == 0) { strcpy(binValue, "0011"); }
			else
			{
				strcat(binValue, "0011");
			}
			break;
		case('4'):
			if (i == 0) { strcpy(binValue, "0100"); }
			else
			{
				strcat(binValue, "0100");
			}
			break;
		case('5'):
			if (i == 0) { strcpy(binValue, "0101"); }
			else
			{
				strcat(binValue, "0101");
			}
			break;
		case('6'):
			if (i == 0) { strcpy(binValue, "0110"); }
			else
			{
				strcat(binValue, "0110");
			}
			break;
		case('7'):
			if (i == 0) { strcpy(binValue, "0111"); }
			else
			{
				strcat(binValue, "0111");
			}
			break;
		case('8'):
			if (i == 0) { strcpy(binValue, "1000"); }
			else
			{
				strcat(binValue, "1000");
			}
			break;
		case('9'):
			if (i == 0) { strcpy(binValue, "1001"); }
			else
			{
				strcat(binValue, "1001");
			}
			break;
		case('a'):
			if (i == 0) { strcpy(binValue, "1010"); }
			else
			{
				strcat(binValue, "1010");
			}
			break;
		case('b'):
			if (i == 0) { strcpy(binValue, "1011"); }
			else
			{
				strcat(binValue, "1011");
			}
			break;
		case('c'):
			if (i == 0) { strcpy(binValue, "1100"); }
			else
			{
				strcat(binValue, "1100");
			}
			break;
		case('d'):
			if (i == 0) { strcpy(binValue, "1101"); }
			else
			{
				strcat(binValue, "1101");
			}
			break;
		case('e'):
			if (i == 0) { strcpy(binValue, "1110"); }
			else
			{
				strcat(binValue, "1110");
			}
			break;
		case('f'):
			if (i == 0) { strcpy(binValue, "1111"); }
			else
			{
				strcat(binValue, "1111");
			}
			break;
		default:
			printf("Not a hex value %c", littleEnRep[i]);
		}
	}
	binValue[32] = '\0';
	fputs(binValue, outputPtr);
	fputs("\n", outputPtr);
	//puts(binValue);
}
