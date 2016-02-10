#include <math.h>
#include "dotproduct.h"

double dotproduct(const double *x, const double *y, int len, int dosqrt)
{
	double dp;
	double sumx2 = 0;
	double sumy2 = 0;
	double sumxy = 0;
	int i;

	if (dosqrt == 0)
	{
		for (i = 0; i < len; i++)
		{
			sumx2 += x[i] * x[i];
			sumy2 += y[i] * y[i];
			sumxy += x[i] * y[i];
		}
	}
	else
	{
		for (i = 0; i < len; i++)
		{
			sumx2 += x[i];
			sumy2 += y[i];
			sumxy += sqrt(x[i] * y[i]);
		}
	}

	dp = sumxy / sqrt((sumx2) * (sumy2));

	return dp;
}
