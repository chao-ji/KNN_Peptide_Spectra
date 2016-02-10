#include <stdlib.h> 
#include <stdio.h>
#include <string.h>

#include "dotproduct.h"

#include "shuffle.h"
#include "commons.h"
#include "hamdist.h"
#include "get_trainpairs.h"

int cmp(const void *p1, const void *p2);

void get_trainpairs(char **seqs1, char **seqs2, label *cl, char **pepseqs, double **peaklists, int *perm, int peplen, int size, int pos_size, int neg_size, double rho_high, double rho_low, int veclen)
{
	int i;
	int j;
	int c;
	float r;
	int d;

	int *I = (int *) malloc(NCHOOSE2(size) * sizeof(int));
	int *J = (int *) malloc(NCHOOSE2(size) * sizeof(int));
	pair *pos = (pair *) malloc(NCHOOSE2(size) * sizeof(pair));
	pair *neg = (pair *) malloc(NCHOOSE2(size) * sizeof(pair));
	int pos_num = 0;
	int neg_num = 0;

	int *dist_pos_count = (int *) calloc(peplen, sizeof(int));
	int *dist_neg_count = (int *) calloc(peplen, sizeof(int));

	c = 0;
// debugging
	FILE *out = fopen("index.txt", "w");
	for (i = 0; i < size; i++)
		fprintf(out, "%d\t%d\n", perm[i], i);
	fclose(out);	

	for (i = 0; i < size - 1; i++)
	{
		for (j = i + 1; j < size; j++)
		{
			I[c] = perm[i];
			J[c] = perm[j];
			r = (float) dotproduct(peaklists[perm[i]], peaklists[perm[j]], veclen, 0);
			d = hamdist(pepseqs[perm[i]], pepseqs[perm[j]], peplen);
	
			if (r >= rho_high)
			{
				pos[pos_num].dist = d;
				pos[pos_num].index = c;
				pos_num++;

				dist_pos_count[d - 1]++;
			}
			else if (r <= rho_low)
			{
				neg[neg_num].dist = d;
				neg[neg_num].index = c;
				neg_num++;

				dist_neg_count[d - 1]++;
			}


			c++;
		}
	}




	printf("%d\t%d\n", pos_num, neg_num);
	fflush(stdout);

	if (pos_num < pos_size)
	{
		printf("pos_num = %d\t pos_size = %d\n", pos_num, pos_size);
		perror("Not enough positive examples.\n");
		exit(1);
	}
	else if (neg_num < neg_size)
	{
		printf("neg_num = %d\t neg_size = %d\n", neg_num, neg_size);
		perror("Not enough negative examples.\n");
		exit(1);
	}

//	pos = shuffle(pos, pos_num);
//	neg = shuffle(neg, neg_num);

	qsort(pos, pos_num, sizeof(pair), cmp);
	qsort(neg, neg_num, sizeof(pair), cmp);


	int total_pos = 0;
	int total_neg = 0;

	for (i = 0; i < peplen; i++)
	{
		total_pos += dist_pos_count[i];
		if (total_pos > pos_size)
		{
			total_pos -= dist_pos_count[i];
			break;
		}
	}

	for (i = 0; i < peplen; i++)
	{
		total_neg += dist_neg_count[i];
		if (total_neg > neg_size)
		{
			total_neg -= dist_neg_count[i];
			break;
		}
	}

	pair tmp;
	
	srand(time(NULL));
	for (i = pos_num - 1 - total_pos; i >= 0; i--)
	{
		j = rand() % (i + 1);

		tmp = pos[i + total_pos];
		pos[i + total_pos] = pos[j + total_pos];
		pos[j + total_pos] = tmp;
	}

	for (i = neg_num - 1 - total_neg; i >= 0; i--)
	{
		j = rand() % (i + 1);

		tmp = neg[i + total_neg];
		neg[i + total_neg] = neg[j + total_neg];
		neg[j + total_neg] = tmp;
	}


	for (i = 0; i < pos_size; i++)
	{
		strcpy(seqs1[i], pepseqs[I[pos[i].index]]);
		strcpy(seqs2[i], pepseqs[J[pos[i].index]]);
		cl[i] = POS;
	}

	for (i = 0; i < neg_size; i++)
	{
		strcpy(seqs1[i + pos_size], pepseqs[I[neg[i].index]]);
		strcpy(seqs2[i + pos_size], pepseqs[J[neg[i].index]]);
		cl[i + pos_size] = NEG;
	}

	free(I);
	free(J);
	free(neg);
	free(pos);
	
	return;
}

int cmp(const void *p1, const void *p2)
{
	const pair *myp1, *myp2;

	myp1 = (const pair *) p1;
	myp2 = (const pair *) p2;

	return (int) (myp1->dist - myp2->dist);
}
