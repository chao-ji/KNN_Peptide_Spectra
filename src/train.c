#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "get_peaklists.h"
#include "rm_peaklists.h"
#include "get_pepseqs.h"
#include "rm_pepseqs.h"
#include "commons.h"
#include "hamdist.h"
#include "get_featurematrix.h"
#include "get_size.h"
#include "get_trainpairs.h"
#include "shuffle.h"
#include "train.h"

char * train(char **pepseqs, double **peaklists, int peplen, int *perm, int N, int pos_size, int neg_size, double rho_high, double rho_low, char *modelfile, int veclen)
{
	int i;
	char *trainfile = "m.txt";	

	char **seqs1;
	char **seqs2;


	seqs1 = (char **) malloc((pos_size + neg_size) * sizeof(char *));
	seqs2 = (char **) malloc((pos_size + neg_size) * sizeof(char *));
	label *cl = (label *) malloc((pos_size + neg_size) * sizeof(label));


	for (i = 0; i < pos_size + neg_size; i++)
	{
		seqs1[i] = (char *) calloc((peplen + 1), sizeof(char));
		seqs2[i] = (char *) calloc((peplen + 1), sizeof(char));
	}

	get_trainpairs(seqs1, seqs2, cl, pepseqs, peaklists, perm, peplen, N, pos_size, neg_size, rho_high, rho_low, veclen);
	get_featurematrix(seqs1, seqs2, cl, pos_size + neg_size, peplen, trainfile);

	char *cmdstr = calloc(CMDSTRLEN, sizeof(char));
	strcat(cmdstr, "svm_learn -z c -t 0 ");
	strcat(cmdstr, trainfile);
	strcat(cmdstr, " ");
	strcat(cmdstr, modelfile);

	system(cmdstr);

	for (i = 0; i < pos_size + neg_size; i++)
	{
		free(seqs1[i]);
		free(seqs2[i]);
	}

	free(cmdstr);
	
	free(cl);
	free(seqs2);
	free(seqs1);

	return modelfile;
}
