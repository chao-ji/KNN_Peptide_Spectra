#include <stdio.h>
#include <stdlib.h>

#include "commons.h"
#include "get_peaklists.h"

double ** get_peaklists(int peplen, int veclen, const char *datfile, int preccharge)
{
	FILE *in = fopen(datfile, "rb");

	if (in == NULL)
	{
		printf("In get_peaklists\n");
		perror("Open input file text");
		exit(1);
	}

	int i;
	int j;

	int size;
	int nonzero;

	int index;
	double height;	

	double **peaklists;

	fread(&size, 1, sizeof(int), in);
	peaklists = (double **) malloc(size * sizeof(double *));

	for (i = 0; i < size; i++)
	{
		fseek(in, sizeof(int) + (peplen + 1) * sizeof(char), SEEK_CUR);

		fread(&nonzero, 1, sizeof(int), in);

		peaklists[i] = (double *) calloc(veclen, sizeof(double));

		for (j = 0; j < nonzero; j++)
		{
			fread(&index, 1, sizeof(int), in);
			fread(&height, 1, sizeof(double), in);

			peaklists[i][index] = height; 
		}
	}

	fclose(in);
	return peaklists;
}

