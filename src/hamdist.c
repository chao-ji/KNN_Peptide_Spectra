#include "hamdist.h"

int hamdist(const char *s1, const char *s2, int len)
{
	int d = 0;
	int i;

	for (i = 0; i < len; i++)
		if (s1[i] != s2[i])
			d++;

	return d;
}
