#ifndef COMMONS_H
#define COMMONS_H

#define PEAKS_PER_ION2 33
#define PEAKS_PER_ION3 42

#define PREC_PEAKS 6

#define VEC_LEN2(x) ((x - 1) * PEAKS_PER_ION2 + PREC_PEAKS)
#define VEC_LEN3(x) ((x - 1) * PEAKS_PER_ION3 + PREC_PEAKS)

#define NCHOOSE2(x) ((x - 1) * x / 2)
#define AA_PAIR 210
#define SIGMOID(x) (1 / (1 + exp(-x)))
#define CMDSTRLEN 100
#define ANNSTRLEN 20

typedef enum LABEL 
{
	POS,
	NEG,
	NA	
} label;

typedef struct ELEM
{
        double d;
        int i;  
        char s[ANNSTRLEN];
	int dist;        
} elem;

typedef struct PAIR 
{
	short dist;
	int index;
} pair;

#endif
