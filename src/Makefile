all: train_main test_main

train_main: train_main.o aa.o dotproduct.o get_featurematrix.o get_peaklists.o get_pepseqs.o get_size.o get_trainpairs.o rm_peaklists.o rm_pepseqs.o shuffle.o train.o hamdist.o
	gcc -o train_main train_main.o aa.o dotproduct.o get_featurematrix.o get_peaklists.o get_pepseqs.o get_size.o get_trainpairs.o rm_peaklists.o rm_pepseqs.o shuffle.o train.o hamdist.o -lm

test_main: test_main.o aa.o get_featurematrix.o get_input.o get_neighborindex.o get_peaklists.o get_pepseqs.o get_predictions.o get_size.o hamdist.o mass.o printspec.o rm_peaklists.o rm_pepseqs.o sort.o spec_average.o test.o 
	gcc -o test_main test_main.o aa.o get_featurematrix.o get_input.o get_neighborindex.o get_peaklists.o get_pepseqs.o get_predictions.o get_size.o hamdist.o mass.o printspec.o rm_peaklists.o rm_pepseqs.o sort.o spec_average.o test.o -lm

# train_main #

train_main.o: train_main.c commons.h train.h get_peaklists.h get_pepseqs.h shuffle.h rm_peaklists.h rm_pepseqs.h get_size.h
	gcc -c train_main.c

aa.o: aa.c aa.h
	gcc -c aa.c

dotproduct.o: dotproduct.c dotproduct.h
	gcc -c dotproduct.c

get_featurematrix.o: get_featurematrix.c commons.h hamdist.h get_featurematrix.h
	gcc -c get_featurematrix.c

get_peaklists.o: get_peaklists.c get_peaklists.h commons.h
	gcc -c get_peaklists.c

get_pepseqs.o: get_pepseqs.c aa.h get_pepseqs.h
	gcc -c get_pepseqs.c

get_size.o: get_size.c get_size.h 
	gcc -c get_size.c

get_trainpairs.o: get_trainpairs.c get_trainpairs.h dotproduct.h shuffle.h commons.h hamdist.h
	gcc -c get_trainpairs.c

rm_peaklists.o: rm_peaklists.c rm_peaklists.h
	gcc -c rm_peaklists.c

rm_pepseqs.o: rm_pepseqs.c rm_pepseqs.h
	gcc -c rm_pepseqs.c

shuffle.o: shuffle.c shuffle.h
	gcc -c shuffle.c

train.o: train.c train.h get_peaklists.h rm_peaklists.h get_pepseqs.h rm_pepseqs.h commons.h hamdist.h get_featurematrix.h get_size.h get_trainpairs.h shuffle.h
	gcc -c train.c

hamdist.o: hamdist.c hamdist.h
	gcc -c hamdist.c

# test_main #

test_main.o: test_main.c commons.h train.h get_peaklists.h get_pepseqs.h shuffle.h rm_peaklists.h rm_pepseqs.h get_size.h test.h get_input.h mass.h
	gcc -c test_main.c

get_input.o: get_input.c get_input.h aa.h
	gcc -c get_input.c

get_neighborindex.o: get_neighborindex.c get_neighborindex.h commons.h hamdist.h get_featurematrix.h get_predictions.h sort.h
	gcc -c get_neighborindex.c

get_predictions.o: get_predictions.c get_predictions.h commons.h
	gcc -c get_predictions.c

mass.o: mass.c mass.h commons.h
	gcc -c mass.c

printspec.o: printspec.c printspec.h commons.h mass.h sort.h
	gcc -c printspec.c

sort.o: sort.c sort.h commons.h
	gcc -c sort.c

spec_average.o: spec_average.c spec_average.h commons.h
	gcc -c spec_average.c
test.o: test.c test.h commons.h get_featurematrix.h get_neighborindex.h get_trainpairs.h spec_average.h printspec.h mass.h
	gcc -c test.c

clean:
	-rm *.o

