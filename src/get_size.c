#include "get_size.h"
#include <stdio.h>
#include <stdlib.h>

int get_size(char *file)
{
	int size;
	FILE *in = fopen(file, "rb");
	fread(&size, sizeof(int), 1, in);
	fclose(in);
	return size;
}
