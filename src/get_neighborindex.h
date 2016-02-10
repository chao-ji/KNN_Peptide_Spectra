#ifndef GET_NEIGHBORINDEX_H
#define GET_NEIGHBORINDEX_H

void get_neighborindex(char **query, char **pepseqs, int **index, double *conf, int peplen, int size, int query_size, int K, char *modelfile, int veclen, double **peaklists, int *query_index);

#endif
