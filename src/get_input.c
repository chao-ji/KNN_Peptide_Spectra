#include <stdio.h>
#include <stdlib.h>

#include "get_input.h"
#include "aa.h"

char ** get_input(char *infile, int peplen, int *inputsize)
{
	char **inputseqs;
	int i;
	int j;
	int myinputsize = 0;
		
	FILE *in = fopen(infile,"rt");
	if (in == NULL)
	{
		perror("Open input file text");
		printf("get input\n");
		exit(1);
	}

	int c;
	char *line = NULL;
	long long curr = 0;
	long long prev = curr;

	while ((c=fgetc(in)) != EOF)
		if (c == '\n')
			myinputsize++;
		
	rewind(in);
	(*inputsize) = myinputsize;

	inputseqs = (char **) malloc(myinputsize * sizeof(char *));
	for (i = 0; i < myinputsize; i++)
		inputseqs[i] = (char *) malloc((peplen + 1) * sizeof(char));
	
	i = 0;
	while ((c = fgetc(in)) != EOF)
	{
		if (c == '\n')
		{
			curr = ftell(in);
			fseek(in, prev, SEEK_SET);
			line = (char *)malloc((curr-prev) * sizeof(char));
			fgets(line,(curr-prev),in);

			if (strlen(line) != peplen)
			{
				perror("Peptide length?");
				exit(1);
			}

			strcpy(inputseqs[i], line);
//			free(line);

			for (j = 0; j < peplen; j++)
			{
				inputseqs[i][j] = (char) aa(inputseqs[i][j]);
			}

			i++;

			fseek(in,curr,SEEK_SET);
			prev = curr;
		}
	}

	fclose(in);


	return inputseqs;
}
