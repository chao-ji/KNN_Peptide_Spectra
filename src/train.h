#ifndef TRAIN_H
#define TRAIN_H

char * train(char **pepseqs, double **peaklists, int peplen, int *perm, int N, int pos_size, int neg_size, double rho_high, double rho_low, char *modelfile, int vec_len);

#endif
