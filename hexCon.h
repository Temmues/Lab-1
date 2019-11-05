#ifndef HEX_CON_H_
#define HEX_CON_H_
#pragma warning(disable : 4996)
#include <stdio.h>
#include <string.h>
void HexCon(char * inputValue) // FIX ME 
{
	char binValue[36];
	//int hexLength = strlen(inputValue);
	printf("Size of input %d\n", strlen(inputValue));
	for (int i = 0; i < 17; i++)
	{
		printf("inputValue %c\n", inputValue[i]);
		char testVal = inputValue[i];
		switch (testVal)
		{
		case('0'):
			strcat(binValue, "0000");
			break;
		case('1'):
			strcat(binValue, "0001");
			break;
		case('2'):
			strcat(binValue, "0010");
			break;
		case('3'):
			strcat(binValue, "0011");
			break;
		case('4'):
			strcat(binValue, "0010");
			break;
		case('5'):
			strcat(binValue, "0101");
			break;
		case('6'):
			strcat(binValue, "0110");
			break;
		case('7'):
			strcat(binValue, "0111");
			break;
		case('8'):
			strcat(binValue, "1000");
			break;
		case('9'):
			strcat(binValue, "1001");
			break;
		case('a'):
			//strcat(binValue, "1010");
			break;
		case('b'):
			//strcat(binValue, "1011");
			break;
		case('c'):
			//strcat(binValue, "1100");
			break;
		case('d'):
			//strcat(binValue, "1101");
			break;
		case('e'):
			strcat(binValue, "1110");
			break;
		case('f'):
			strcat(binValue, "1111");
			break;
		default:
			printf("Not a hex value");
		}
	}
	//return binValue;
}
#endif // !

