#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "commons.h"
#include "hamdist.h"
#include "get_featurematrix.h"
#include "get_predictions.h"
#include "sort.h"

#include "get_neighborindex.h"

void get_neighborindex(char **query, char **pepseqs, int **index, double *conf, int peplen, int size, int query_size, int K, char *modelfile, int veclen, double **peaklists, int *query_index)
{
	int i;
	int j;
	int d;
	int c = 0;
	int neighbor_count_sum = 0;
	double r;
	int *start;
	int *end;

	int **dist;
	int *mindist;
	int **neighbor_index;
	int *neighbor_count;
	label *cl;

	char **seqs1;
	char **seqs2;
	elem *a;

	dist = (int **) malloc(query_size * sizeof(int *));
	mindist = (int *) malloc(query_size * sizeof(int));
	neighbor_index = (int **) malloc(query_size * sizeof(int *));

	for (i = 0; i < query_size; i++)
	{	
		dist[i] = (int *) malloc(size * sizeof(int));
		neighbor_index[i] = (int *) malloc(size * sizeof(int));
	}

	for (i = 0; i < query_size; i++)
	{
		mindist[i] = peplen;
		for (j = 0; j < size; j++)
		{
			dist[i][j] = hamdist(query[i], pepseqs[j], peplen);

			if (dist[i][j] < mindist[i] && dist[i][j] > 0)
				mindist[i] = dist[i][j];
		}
	}

	neighbor_count = (int *) calloc(query_size, sizeof(int));
	start = (int *) malloc(query_size * sizeof(int));
	end = (int *) malloc(query_size * sizeof(int));

	for (i = 0; i < query_size; i++)
	{
		d = mindist[i];
		while (neighbor_count[i] < K && d <= peplen)
		{
			for (j = 0; j < size; j++)
				if (dist[i][j] == d)
					neighbor_index[i][(neighbor_count[i])++] = j;
			d++;
		}

		neighbor_count_sum += neighbor_count[i];

		start[i] = neighbor_count_sum - neighbor_count[i];
		end[i] = neighbor_count_sum - 1;
	}

	seqs1 = (char **) malloc(neighbor_count_sum * sizeof(char *));
	seqs2 = (char **) malloc(neighbor_count_sum * sizeof(char *));

	for (i = 0; i < neighbor_count_sum; i++)
	{
		seqs1[i] = (char *) malloc((peplen + 1) * sizeof(char));
		seqs2[i] = (char *) malloc((peplen + 1) * sizeof(char));
	}

	cl = (label *) malloc(neighbor_count_sum * sizeof(label));
	a = (elem *) malloc(neighbor_count_sum * sizeof(elem));

	for (i = 0; i < query_size; i++)
	{
		for (j = 0; j < neighbor_count[i]; j++)
		{
			strcpy(seqs1[c], query[i]);

			strcpy(seqs2[c], pepseqs[neighbor_index[i][j]]);

			cl[c] = NA;
			a[c].i = neighbor_index[i][j];
			a[c].dist = dist[i][neighbor_index[i][j]];
			c++;
		}
	}



	char *featurefile = "input.txt";
	char *predfile = "svmprediction";
	char *cmdstr = (char *) calloc(CMDSTRLEN, sizeof(char));

	get_featurematrix(seqs1, seqs2, cl, neighbor_count_sum, peplen, featurefile);

	strcat(cmdstr, "svm_classify ");
	strcat(cmdstr, featurefile);
	strcat(cmdstr, " ");
	strcat(cmdstr, modelfile);
	strcat(cmdstr, " ");
	strcat(cmdstr, predfile);

	system(cmdstr);

	get_predictions(a, neighbor_count, neighbor_count_sum, predfile);
	FILE *auxfile1 = fopen("mindist.txt", "a");
	FILE *auxfile2 = fopen("nghbrs.txt", "a");

	for (i = 0; i < query_size; i++)
	{
		sort(a, start[i], end[i]);
		
		double mean = 0;


		for (j = 0; j < K; j++)
		{
			index[i][j] = a[start[i] + j].i;
			mean += a[start[i] + j].d;		
		}


		conf[i] = mean / K;
		fprintf(auxfile1, "%d\t%d\n", mindist[i], neighbor_count[i]);
		for (j = 0; j < K; j++)
		{
			fprintf(auxfile2, "%d  %.4f  \t", a[start[i] + j].dist, a[start[i] + j].d);
		}
		fprintf(auxfile2, "\n");

		fflush(auxfile2);
		fflush(auxfile1);

	}

	fclose(auxfile2);
	fclose(auxfile1);
	free(a);
	free(cl);

	for (i = 0; i < neighbor_count_sum; i++)
	{
		free(seqs1[i]);
		free(seqs2[i]);
	}

	free(seqs2);
	free(seqs1);

	free(start);
	free(end);
	free(neighbor_count);


        for (i = 0; i < query_size; i++)
        {       
                free(dist[i]);
                free(neighbor_index[i]);
        }       

	free(mindist);	
        free(dist);
        free(neighbor_index); 


	return;
}
