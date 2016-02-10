#include <stdio.h>
#include <stdlib.h>

#include "commons.h"
#include "mass.h"
#include "sort.h"
#include "printspec.h"

int printspec(double *peaklist, char *pepseq, int peplen, int preccharge, int vec_len, FILE *out)
{
	int i;

	double *pref_mass;
	double *suff_mass;
	elem *spec_inten;
	char *pepseq_ascii;

	int iontype;
	int frag;
	int num_peaks = 0;
	double precmass;
	double mz;
	int peaks_per_ion;
	
	const double *ioncharge;
	const double *fragmassshift;
	const char (*annfrag)[ANNSTRLEN];
	const int *isprefix;	
       
        if (preccharge == 2)
	{
		ioncharge = ioncharge2;
		fragmassshift = fragmassshift2;
		annfrag = &annfrag2[0];
		isprefix = isprefix2;

		peaks_per_ion = PEAKS_PER_ION2;
	}
        else if (preccharge == 3)
	{
		ioncharge = ioncharge3;
		fragmassshift = fragmassshift3;
		annfrag = &annfrag3[0];
		isprefix = isprefix3;

		peaks_per_ion = PEAKS_PER_ION3;
	}
        else
        {
                printf("preccharge = %d\n", preccharge);
                perror("No such charge state.\n");
                exit(1);
        }


	pref_mass = (double *) calloc(peplen, sizeof(double));
	suff_mass = (double *) calloc(peplen, sizeof(double));

	spec_inten = (elem *) malloc(vec_len * sizeof(elem));
	pepseq_ascii = (char *) calloc(peplen + 1, sizeof(double));


	for (i = 1; i < peplen; i++)
	{
		pref_mass[i] = pref_mass[i - 1] + aamass_mono[pepseq[i - 1] - 1];
		suff_mass[i] = suff_mass[i - 1] + aamass_mono[pepseq[peplen - i] - 1];

		pepseq_ascii[i - 1] = aasigma[pepseq[i - 1] - 1];
	}
	pepseq_ascii[peplen - 1] = aasigma[pepseq[peplen - 1] - 1];

	precmass = pref_mass[peplen - 1] + suff_mass[1] + H2Omass;
	
	for (i = 0; i < vec_len - PREC_PEAKS; i++)
	{
		spec_inten[i].i = (int) peaklist[i];

		iontype = i % peaks_per_ion;
		frag = i / peaks_per_ion;

		if (isprefix[iontype])
			mz = (pref_mass[frag + 1] + protonmass * (ioncharge)[iontype] +  (fragmassshift)[iontype]) / (double) (ioncharge)[iontype];
		else
			mz = (suff_mass[frag + 1] + H2Omass + protonmass * (ioncharge)[iontype] + (fragmassshift)[iontype]) / (double) (ioncharge)[iontype];

		spec_inten[i].d = -mz;

		sprintf(spec_inten[i].s, "\"%c%d%s\"", (annfrag)[iontype][0], frag + 1, (annfrag)[iontype] + 1);
	}
		
	for (i = vec_len - PREC_PEAKS; i < vec_len; i++)
	{
		spec_inten[i].i = (int) peaklist[i];
		mz = (precmass + protonmass * preccharge + precmassshift[i - vec_len + PREC_PEAKS]) / (double) preccharge;
		spec_inten[i].d = -mz;

		sprintf(spec_inten[i].s, "\"%s\"", annprec[i - vec_len + PREC_PEAKS]);
	}

	sort(spec_inten, 0, vec_len - 1);


	for (i = 0; i < vec_len; i++)
	{
		if (spec_inten[i].i >= 10)
		{
			num_peaks++;
		}
	}

	fprintf(out, "Name: %s/%d\nMW: %.3f\nComment:\nNum peaks: %d\n", pepseq_ascii, (int) preccharge, precmass + protonmass * preccharge, num_peaks);

	for (i = 0; i < vec_len; i++)
	{
		if (spec_inten[i].i >= 10)
		{
			fprintf(out, "%.1f\t%d\t%s\n", -spec_inten[i].d, spec_inten[i].i, spec_inten[i].s);
		}
	}


	fprintf(out, "\n");

	free(pepseq_ascii);
	free(spec_inten);
	free(suff_mass);
	free(pref_mass);

	return num_peaks;
}
