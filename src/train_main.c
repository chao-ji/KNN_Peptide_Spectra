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

int main(int argc, char *argv[])
{
        if (argc != 7)
        {
                perror("Usage: \ntrain_main [length] [library file] [charge] [rho_high] [rho_low] [model file]\n");
                exit(1);
        }
        int peplen = atoi(argv[1]);
        char datfile[100];
        strcpy(datfile, argv[2]);
	int preccharge = atoi(argv[3]);
 	int veclen;

	char **pepseqs;
	double **peaklists;
	int *perm;

	double rho_high;
	double rho_low;
	int pos_size;
	int neg_size;

	char modelfile[100];
	int size;
	int i;

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

	pos_size = 50000;
	neg_size = 50000;

        rho_high = atof(argv[4]);
       	rho_low = atof(argv[5]);

	strcpy(modelfile, argv[6]);

	size = get_size(datfile);

	peaklists = get_peaklists(peplen, veclen, datfile, preccharge);
	pepseqs = get_pepseqs(datfile);

	perm = (int *) malloc(size * sizeof(int));

	for (i = 0; i < size; i++)
		perm[i] = i;
	perm = shuffle(perm, size);

	train(pepseqs, peaklists, peplen, perm, size, pos_size, neg_size, rho_high, rho_low, modelfile, veclen);
	rm_peaklists(peaklists, size);
	rm_pepseqs(pepseqs, size);

	return 0;
}
