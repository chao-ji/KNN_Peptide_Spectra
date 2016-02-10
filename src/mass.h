#ifndef MASS_H
#define MASS_H

#include "commons.h"

extern const char aasigma[21];
extern const double aamass_mono[20];

extern const double protonmass;
extern const double H2Omass;
extern const double OHmass;
extern const double NH3mass;

extern const double Hmass;
extern const double Cmass;
extern const double Nmass;
extern const double Omass;

extern const char annfrag2[PEAKS_PER_ION2][ANNSTRLEN]; 

extern const double fragmassshift2[PEAKS_PER_ION2]; 
extern const double ioncharge2[PEAKS_PER_ION2]; 
extern const int isprefix2[PEAKS_PER_ION2];

extern const char annfrag3[PEAKS_PER_ION3][ANNSTRLEN];

extern const double fragmassshift3[PEAKS_PER_ION3];
extern const double ioncharge3[PEAKS_PER_ION3];
extern const int isprefix3[PEAKS_PER_ION3];

extern const char annprec[PREC_PEAKS][ANNSTRLEN];
extern const double precmassshift[PREC_PEAKS];

#endif 
