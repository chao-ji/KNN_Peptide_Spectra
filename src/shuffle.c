#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "shuffle.h"

int *shuffle(int *a, int n)
{
	int i;
	int j;
	int tmp;

	srand(time(NULL));

	for (i = n - 1; i >= 0; i--)
	{
		j = rand() % (i + 1);

		tmp = a[i];
		a[i] = a[j];
		a[j] = tmp;
	}

	return a;
}
