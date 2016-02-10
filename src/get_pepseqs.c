#include <stdio.h>
#include <stdlib.h>

#include "aa.h"
#include "get_pepseqs.h"

char ** get_pepseqs(const char *datfile)
{
	FILE *in = fopen(datfile, "rb");

	if (in == NULL)
	{
		printf("In get_pepseqs\n");
		perror("Open input file text");
		exit(1);
	}

	int peplen;
	int nonzero;
	int i;
	int j;

	int size;
	char **pepseqs;
	
	fread(&size, 1, sizeof(int), in);

	pepseqs = (char **) malloc(size * sizeof(char *));

	for (i = 0; i < size; i++)
	{
		fread(&peplen, 1, sizeof(int), in);
		pepseqs[i] = (char *) malloc((peplen + 1) * sizeof(char));
		fread(pepseqs[i], peplen + 1, sizeof(char), in);

		for (j = 0; j < peplen; j++)
			pepseqs[i][j] = (char) aa(pepseqs[i][j]);

		fread(&nonzero, 1, sizeof(int), in);
		fseek(in, nonzero * (sizeof(int) + sizeof(double)), SEEK_CUR);
	}

	fclose(in);
	return pepseqs;
}
