Click [this](https://github.com/chao-ji/KNN_Peptide_Spectra/blob/master/From%20peptide%20and%20spectrum%20to%20user%20and%20item.ipynb) for an intuitive and graphical explanation for this algorithm.

# KNN_Peptide_Spectra
An K nearest neighbor algorithm for predicting peptide fragmentation patterns

This program predicts CID fragmentation spectra of unmodified (without PTMs) peptide ions of a given length based on a set of peptides (of the same length and charge) with known spectra under a K-nearest neighbor framework. Currently this program accepts peptide ions of charge 2+ (length 7 to 20) and charge 3+ (length 12 to 25).

1. Installation

1.a. Install SVMlight 

This program uses SVMlight (a fast implementation of Support Vector Machine) as a subroutine. The installation package can be downloaded from http://svmlight.joachims.org/. SVMlight can be installed (follow the instructions on this website) under any directory. 

To make the SVMlight executable (svm_learn and svm_classify) visible to this program, the PATH environmental variable in Linux needs to be correctly set as follows: 

Assume SVMlight is installed under directory "\~/svmlight/"

* Open file "~/.bashrc" and add a line "export PATH=$PATH:~/svmlight/"
* Type "source .bashrc"

1.b. Install this program
This program was written in C, and the package itself includes two pre-compiled executables ("train_main" and "test_main") in the subdirectory "bin", but it's recommended that the users re-compile the source code on their local machines.

To re-compile the source code, go to subdirectory "src" and type "make". The two executable files will be generated.

This program relies on peptides along with their spectra to predict the fragmentation spectrum of a given peptide.  The library file that contains the peptide-spectrum pairs (potential neighbors) for peptide ions of charge [charge] and length [length] can be found under the following directory:

/library/[charge]/[length]/[length].dat

2. Training the scoring model 
This program uses the trained SVM model to score the spectral similarity between a target and neighbor peptide. Note that a different model is trained for peptide ions of different length. The package itself includes pre-trained SVM models for each length (/library/[charge]/[length]/model) using the parameters (default) as follows:

Charge 2+
rho_high		rho_low		
0.9413			0.0966
0.8901			0.0873
0.8345			0.0971
0.7799			0.1014
0.7456			0.1041
0.7266			0.1061
0.7157			0.1067
0.7070			0.1041
0.6987			0.1012
0.6926			0.1042
0.6828			0.1037
0.6767			0.1016
0.6717			0.1012
0.6625			0.1038

Charge 3+
rho_high		rho_low
0.8503			0.0288
0.8423			0.0314
0.8109			0.0347
0.7742			0.0371
0.7445			0.0386
0.7105			0.0407
0.6763			0.0419
0.6495			0.0449
0.6348			0.0443
0.6192			0.0446
0.6054			0.0436
0.5914			0.0426
0.5869			0.0430
0.5675			0.0423

The performance of the prediction accuracy will be robust if thresholds that define the positive and negative classes are reasonably set (e.g. rho_high is close to 1 and rho_low is close to 0), and it's recommended that users use pre-trained models, but it's also optional for the users to re-train the SVM models.

To train an SVM model for peptides of a particular length using different thresholds, use the executable file "train_main", the usage is as follows:

> train_main [length] [library file] [charge] [rho_high] [rho_low] [model file]

[length]: the peptide length (7 to 20 for charge 2+ and 12 to 25 for charge 3+)

[library file]: the input file that contains the peptide-spectrum matches for this particular length and charge group.

[charge]: the charge state (2 or 3)

[rho_high] [rho_low]: the threshold for defining positive and negative classes

[model file]: the output file containing the trained SVM model

 
3. Spectra prediction

To generate the predicted spectra of peptide ions of a given length, use the executable file "test_main": 

> test_main [length] [library file] [charge] [K] [model file] [sequence file] [spectra file]

[length]: the peptide length (7 to 20 for charge 2+ and 12 to 25 for charge 3+)

[library file]: the input file that contains the peptide-spectrum matches for this particular length and charge group.

[charge]: the charge state (2 or 3)

[K]: the number neighbors to be used (e.g. K = 11)

[model file]: the input file containing the trained SVM model 

[sequence file]: the input file that contains the peptide sequences of length [length]

[spectra file]: the output file that contains the predicted spectra along with the peptide sequences

Sample Input:

test_main 25   library/3/25/25.dat   3   11  library/3/25/model  25_3  spectra.msp

This command line generates predicted spectra in output file "spectra.msp" for peptide ions of length 25 and charge 3+. (see the subdirectory "sample")

This program also generated two intermediate files: mindist.dist and nghbrs.txt for analysis purposes. They can be ignored if one only wants the predicted spectra and the confidence scores.

4. Confidence scores

Each predicted spectrum is assigned confidence score (between 0 and 1) in the output file "log.txt"

log.txt:

AAAASAISEGQLSSDESGDLTFSLK       0.881302
AAAHCAHVFTTVSQITAIEAQHLLK       0.906962
AAAIVIGFLMNSEQTSFTSAFSLVK       0.874060
AAALQPLPATHAALYHGMALALLSR       0.849274
AAALSGPWGSPPPPPEQIHSAPGPR       0.902062
AAAPLAAGALQLLAGSTVLLEAYAR       0.677142

In our paper we used the 80-percentiles of all confidence scores for each length as the threshold:

Charge 2+		Charge 3+
7	0.8556		12	0.8294
8	0.7316		13	0.7704
9	0.8647		14	0.7648
10	0.7498		15	0.8607
11	0.8206		16	0.8623
12	0.8072		17	0.8010
13	0.8177		18	0.8861
14	0.8234		19	0.8475
15	0.8253		20	0.7981
16	0.8391		21	0.9016
17	0.8439		22	0.8769
18	0.8521		23	0.9119
19	0.8628		24	0.8968
20	0.8641		25	0.9045

Generally, the higher the confidence score, the more similar the predicted spectra are to their real counterparts. And the user can use other thresholds to achieve an acceptable trade-off between accuracy and coverage.

Contact: Chao Ji
jic@indiana.edu


