#include <stdlib.h>

#include "rm_pepseqs.h"

int rm_pepseqs(char **ptr, int len)
{

	int i;

	for (i = 0; i < len; i++)
	{
		free(ptr[i]);
	}
	free(ptr);
	
	return 0;
}
