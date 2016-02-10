#include <stdlib.h>

#include "rm_peaklists.h"

int rm_peaklists(double **ptr, int len)
{

	int i;

	for (i = 0; i < len; i++)
	{
		free(ptr[i]);
	}
	free(ptr);
	
	return 0;
}
