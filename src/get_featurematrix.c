#include <stdio.h>
#include <stdlib.h>

#include "commons.h"
#include "hamdist.h"
#include "get_featurematrix.h"


char * get_featurematrix(char **seqs1, char **seqs2, label *cl, int len, int peplen, char *feature_file)
{
	FILE *out = fopen(feature_file, "wt");

	if (out == NULL)
	{
		printf("In get_featurematrix\n");
		perror("Open input file text");
		exit(1);
	}

	int i;
	int j;
	int dist;	

	for (i = 0; i < len; i++)
	{
		if (cl[i] == POS)
			fprintf(out, "+1");
		else if (cl[i] == NEG)
			fprintf(out, "-1");
		else
			fprintf(out, "0");

		for (j = 0; j < peplen; j++)
		{
			int x, y, xx, yy, p; 
			x = seqs1[i][j];
			y = seqs2[i][j];

			xx = (x >= y ? x : y);
			yy = (x <  y ? x : y);

			p = AA_PAIR * j + yy + (xx - 1) * xx / 2 - 1;

			dist = hamdist(seqs1[i], seqs2[i], peplen);


			fprintf(out, " %d:%d", p + 1, 1);

			if (j == peplen - 1 && p != AA_PAIR * peplen - 1)
				fprintf(out, " %d:%d", AA_PAIR * peplen, 0);

		}

		fprintf(out, " %d:%.4f", AA_PAIR * peplen + 1, (double) dist / peplen);

		fprintf(out, "\n");
	}
	
	fclose(out);

	return feature_file;
}

