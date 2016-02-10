#include <stdio.h>
#include <stdlib.h>

#include "commons.h"
#include "train.h"
#include "get_peaklists.h"
#include "get_pepseqs.h"
#include "shuffle.h"
#include "rm_peaklists.h"
#include "rm_pepseqs.h"
#include "get_size.h"
#include "test.h"
#include "get_input.h"
#include "mass.h"

int main(int argc, char *argv[])
{
        if (argc != 8)
        {       
                perror("Usage:\ntest_main [length] [library file] [charge] [K] [model file] [sequence file] [spectra file]\n");
                exit(1);
        }       

	int peplen = atoi(argv[1]);
	char datfile[100];
	strcpy(datfile, argv[2]);

	char **pepseqs;
	double **peaklists;
	char modelfile[100];
//	char *modelfile = "model";
	int size = get_size(datfile);
	int i;
	int j;
	int query_size;
	int K = atoi(argv[4]);

	int *query_index;
	char *logfile = "log.txt";
	int preccharge = atoi(argv[3]);
	int veclen;
	char **queryseqs;
	double *conf;
	FILE *out;
	char outputfile[100];

	strcpy(modelfile, argv[5]);

        if (preccharge == 2)
                veclen = VEC_LEN2(peplen);
        else if (preccharge == 3)
                veclen = VEC_LEN3(peplen);
        else
        {
                printf("preccharge = %d\n", preccharge);
                perror("No such charge state.\n");
                exit(1);
        }

	queryseqs = get_input(argv[6], peplen, &query_size);
	strcpy(outputfile, argv[7]);


	query_index = (int *) malloc(query_size * sizeof(int));
	for (i = 0; i < query_size; i++)
		query_index[i] = i;

	peaklists = get_peaklists(peplen, veclen, datfile, preccharge);
	pepseqs = get_pepseqs(datfile);
	conf = (double *) malloc(query_size * sizeof(double));

	test(pepseqs, peaklists, peplen, size, query_index, queryseqs, query_size, conf, K, modelfile, preccharge, veclen, outputfile);
	out = fopen(logfile, "w");

	for (i = 0; i < query_size; i++)
	{
		for (j = 0; j < peplen; j++)
			fprintf(out, "%c",  aasigma[queryseqs[i][j] - 1]);

		fprintf(out, "\t%f\n", conf[i]);
	}

	fclose(out);

	rm_peaklists(peaklists, size);
	rm_pepseqs(pepseqs, size);
	free(conf);

	return 0;
}

