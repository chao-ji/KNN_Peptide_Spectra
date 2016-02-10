#include "commons.h"
#include "sort.h"

elem * sort(elem *array, int start, int end)
{
	int i;
	int j;
	elem key;

	for (i = start + 1; i <= end; i++)
	{
		key = array[i];

		j = i - 1;

		while (j >= start && array[j].d < key.d)
		{
			array[j + 1] = array[j];
			j--;
		}
		array[j + 1] = key;
	}

	return array;
}
