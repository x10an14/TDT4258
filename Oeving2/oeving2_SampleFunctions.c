#include <limits.h>
#include <stdlib.h>
#include "oeving2.h"


sample* sampleConstructor(sample *inpt, int size, int maxRate, short *tonelist, short *strokelist){
	/*Common things for all samples*/
	//Allocate space on heap for pointers (And set all member-values to zero!)
	inpt = (sample*) calloc(1, sizeof(sample));

	inpt->size = size;
	if(tonelist == NULL){ //We will fill the list at a later point
		inpt->list = (short*) calloc(size, sizeof(short));
	} else{ //We have a list already declared (and malloc'd) that we want to use
		inpt->list = tonelist;
	}

	if(strokelist != NULL){/*If the sample in question DOES use strokeList:*/
		inpt->rateMax = 0;
		inpt->usingStrokeList = 1;
		inpt->strokeList = strokelist;
	} else if(maxRate > 0){/*Special for samples w/o strokeList*/
		inpt->strokeList = NULL;
		inpt->usingStrokeList = 0;
		inpt->rateMax = (short) maxRate;
	} else{ /*We have an error. This is a situation not accounted for.*/
		inpt->rateMax = 0;
		inpt->strokeList = NULL;
		inpt->usingStrokeList = 0;
	}

	inpt->rateCntr = 0;
	inpt->playCntr = 0;
	return inpt;
}


/*Function to add the time a tone will be played to a list, given a tone, length (stroke), and list*/
sample* addFrequency(sample *inpt, short stroke, short tone, int start){
	/*We have a problem here. In the for-loops calling this method, we calculate the amount of i*j by the following math: ABDAC_SAMPLERATE/stroke.
	However, this number i BIGGER than amountOfPeriods*periodSize.
	This is a problem, but it shouldn't be the segfault we are looking for.*/
	int amountOfPeriods = (int) (tone/stroke);
	int periodSize = (int) ABDAC_SAMPLERATE/tone;
	int halfPeriod;
	if(periodSize%2 == 0){
		halfPeriod = periodSize/2;
	} else{
		halfPeriod = (periodSize/2)+1;
	}
	int i;
	for(i = 0; i < amountOfPeriods; i++){
		int j;
		for (j = 0; j < halfPeriod; j++){
			inpt->list[start+j+(i*periodSize)] = -SHRT_MAX;
		}
		for (j = halfPeriod; j < periodSize; j++){
			inpt->list[start+j+(i*periodSize)] = SHRT_MAX;
		}
	}
	return inpt;
}

/*Function to add 0 an amount of times to a list*/
void addZeroes(int amount, short *list, int start){
	int i;
	for(i = start; i < amount + start; i++){
		list[i] = 0;
	}
}
