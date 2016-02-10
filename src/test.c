#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commons.h"

#include "get_featurematrix.h"
#include "get_neighborindex.h"
#include "get_trainpairs.h"
#include "spec_average.h"
#include "test.h"

#include "printspec.h"
#include "mass.h"

void test(char **pepseqs, double **peaklists, int peplen, int size, int *query_index, char **queryseqs, int query_size, double *conf,    int K, char *modelfile, int preccharge, int veclen, char *outputfile)
{
	int i;
	int j;
	char **query = (char **) malloc(query_size * sizeof(char *));
	int **K_index = (int **) malloc(query_size * sizeof(int *));

	FILE *out = fopen(outputfile, "a");


	for (i = 0; i < query_size; i++)
	{
		query[i] = (char *) malloc((peplen + 1) * sizeof(char));
		strcpy(query[i], queryseqs[query_index[i]]);
	//	K_index[i] = (int *) malloc(K * sizeof(int));
	//	query[i] = queryseqs[query_index[i]];
		K_index[i] = (int *) malloc(K * sizeof(int));
	}

	get_neighborindex(query, pepseqs, K_index, conf, peplen, size, query_size, K, modelfile, veclen, peaklists, query_index);

	double **neighbor_peaklists = (double **) malloc(K * sizeof(double *));
	double *prediction = (double *) malloc(veclen * sizeof(double));

	for (i = 0; i < query_size; i++)
	{
		memset(prediction, 0, veclen * sizeof(double));

		for (j = 0; j < K; j++)
		{
			neighbor_peaklists[j] = peaklists[K_index[i][j]];
		}
		
		spec_average(prediction, neighbor_peaklists, K, peplen, veclen);

		printspec(prediction, query[i], peplen, preccharge, veclen, out);	


	}

	free(neighbor_peaklists);
	free(prediction);
	
	for (i = 0; i < query_size; i++) 
	{
		free(query[i]);
		free(K_index[i]);	
	}
	free(K_index);
	free(query);

	fclose(out);

	return;
}

