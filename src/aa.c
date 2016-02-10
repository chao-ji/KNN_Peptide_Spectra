#include "aa.h"

int aa(char c)
{
	int v;
	
	switch (c)
	{
		case 'A':
			v = 1;
			break;
		case 'R':
			v = 2;
			break;
		case 'N':
			v = 3;
			break;
		case 'D':
			v = 4;
			break;
		case 'C':
			v = 5;
			break;
		case 'E':
			v = 6;
			break;
		case 'Q':
			v = 7;
			break;
		case 'G':
			v = 8;
			break;
		case 'H':
			v = 9;
			break;
		case 'I':
			v = 10;
			break;
		case 'L':
			v = 11;
			break;
		case 'K':
			v = 12;
			break;
		case 'M':
			v = 13;
			break;
		case 'F':
			v = 14;
			break;
		case 'P':
			v = 15;
			break;
		case 'S':
			v = 16;
			break;
		case 'T':
			v = 17;
			break;
		case 'W':
			v = 18;
			break;
		case 'Y':
			v = 19;
			break;
		case 'V':
			v = 20;
			break;
		default:
			v = -1;
			break;
	}		

	return v;
}
