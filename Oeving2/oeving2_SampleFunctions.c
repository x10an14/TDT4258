#include <limits.h>
#include <stdlib.h>
#include "oeving2.h"


void sampleConstructor(sample *inpt, int size, int maxRate, short *tonelist, short *strokelist){
	/*Common things for all samples*/
	//Allocate space on heap for pointers (And set all member-values to zero!)
	inpt = (sample*) calloc(1, sizeof(sample));

	inpt->size = (short) size;
	inpt->list = (short*) calloc(size, sizeof(short));
	inpt->list = tonelist;
	inpt->rateCntr = 0;
	inpt->playCntr = 0;

	/*Special for samples w/o strokeList*/
	if(maxRate > 0 && strokelist != NULL){
		inpt->usingStrokeList = 0;
		inpt->rateMax = (short) maxRate;
		return;
	}

	/*If the sample in question DOES use strokeList:*/
	inpt->strokeList = strokelist;
	inpt->usingStrokeList = 1;
	inpt->rateMax = 0;
}


/*Function to add the time a tone will be played to a list, given a tone, length (stroke), and list*/
void addFrequency(short stroke, short tone, short *list, int start){
	int periods = (int) (tone/stroke);
	int periodSize = (int) ABDAC_SAMPLERATE/tone;
	int halfPeriod = periodSize/2;
	int i;
	for(i = start; i < periods + start; i++){
		int j;
		for (j = 0; j < halfPeriod; j++){
			list[j] = -SHRT_MAX;
		}
		for (j = halfPeriod; j < periodSize; j++){
			list[j] = SHRT_MAX;
		}
	}
}

/*Function to add 0 an amount of times to a list*/
void addZeroes(int amount, short *list, int start){
	int i;
	for(i = start; i < amount + start; i++){
		list[i] = 0;
	}
}
