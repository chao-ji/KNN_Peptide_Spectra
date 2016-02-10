#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "commons.h"
#include "get_predictions.h"

elem * get_predictions(elem *a, int *neighbor_count, int len, char *infile)
{
	FILE *in = fopen(infile,"rt");

        if (in == NULL)
        {  
		printf("In get_predictions\n");     
                perror("Open input file text");
                exit(1);
        }

	int c;  
        char *line = NULL;      
        long long curr = 0;
        long long prev = curr; 

	int i = 0;

        while ((c = fgetc(in)) != EOF) 
        {       
                if(c == '\n')
                {       
                        curr = ftell(in);
                        fseek(in, prev, SEEK_SET);
                        line = (char *) malloc((curr - prev) * sizeof(char));
                        fgets(line, (curr - prev), in);     /* line is now null-terminated and does not include the newline character */

			a[i++].d = SIGMOID(atof(line));

			free(line);
			fseek(in,curr,SEEK_SET);
			prev = curr; 
		}
	}

	fclose(in);

	return a;
}
