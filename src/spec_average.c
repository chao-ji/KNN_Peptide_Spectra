#include <math.h>

#include "commons.h"
#include "spec_average.h"

double * spec_average(double *peaklist, double **peaklists, int K, int peplen, int veclen)
{
	int i;
	int j;

	double max = 0;
	double ratio;

	for (i = 0; i < veclen; i++)
	{
		for (j = 0; j < K; j++)
		{
			peaklist[i] += (peaklists[j][i] * exp(1 - sqrt(j + 1)));

			if (peaklist[i] > max)
				max = peaklist[i];
		}
	}

	ratio = 10000.0 / max;

	for (i = 0; i < veclen; i++)
	{
		peaklist[i] = peaklist[i] * ratio;
	}

	return peaklist;
}
