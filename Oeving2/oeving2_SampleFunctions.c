#include <limits.h>
#include <stdlib.h>
#include "oeving2.h"


/*This function was written to save space, and follow good coding paradigm, due to the lines in the code needing to be repeated on multiple occasions.*/
sample* sampleConstructor(sample *inpt, int size, int maxRate, short *tonelist, short *strokelist){
	//Things all samples will HAVE to do:
	//Allocate space on heap for pointers (And set all member-values to zero!)
	inpt = (sample*) calloc(1, sizeof(sample));
	//Set values to parameter values and default values
	inpt->size = size;
	inpt->rateCntr = 0;
	inpt->playCntr = 0;

	//Here we have two different cases occuring. Either the tonelist sent in is an actual list, or it is just NULL. If it is NULL, then we will need to allocate space for the list which will be filled at a later point.
	if(tonelist == NULL){
		inpt->list = (short*) calloc(size, sizeof(short));
	} else{
	//Otherwise, we have an already malloc'ed (Not always, in fact, none of the lists being sent here in the current working version of the code are not malloc'ed, but they are declared outside of main, so since main should never finish, they are safe, even though they are ON the program stack.
		inpt->list = tonelist;
	}

	//These checks find out whether we have a list of strokes (a stroke is how much of a second the tone belonging to said stroke will play), and if so, sets rateMax and usingStrokeList members to zero while adding the strokelist to the strokeList member.
	if(strokelist != NULL){
		/*If the sample in question DOES use strokeList:*/
		inpt->rateMax = 0;
		inpt->usingStrokeList = 1;
		inpt->strokeList = strokelist;
	} else if(maxRate > 0){//Elsewise, we do not have a strokelist, but we should have a rateMax input, which decides (in essence, but not exactly) the same as a stroke would. E.g. how long a specific element in list should be played, which will affect the duration of each tone, but also pitch (and strokelist is not meant to affect pitch, only duration)
		/*Special for samples w/o strokeList*/
		inpt->strokeList = NULL;
		inpt->usingStrokeList = 0;
		inpt->rateMax = (short) maxRate;
	} else{ /*Else, we have an error. This is a situation not accounted for, and it is not intended for this situation to happen.*/
		inpt->size = 0;
		inpt->rateMax = 0;
		inpt->list = NULL;
		inpt->strokeList = NULL;
		inpt->usingStrokeList = 0;
	}
	return inpt;
}


/*Function which given a tone, stroke, and starting point in a list, will fill the list from the starting point with elements which when played will result in the tone being played with resulting stroke duration.*/
sample* addFrequency(sample *inpt, short stroke, short tone, int start){
	/*There are several problems here in this function.

	In the main-loop (where this function is called), we have already allocated space for the list by the use of sampleConstructor-function.
	The size of the list is calculated by multiplying amountOfPeriods (= tone/stroke) with periodSize (= ABDAC_SAMPLERATE/tone).

	Simple math will show that the product of these two variables will end up being ABDAC_SAMPLERATE/stroke, which is how the main loops calculates space needed for the list given to this function.

	However, due to integer floor division functioning as it does, this results in the nested for-loops below to traverse a shorter "distance" in the list than there has been space allocated for.
	Therefore, it is suspicious why the assumed segfault (explained below) should occur here.

	Even so, there is a segfault (we are guessing it is a segfault, because the code stops responding) at this point, due to the program never returning from this function (except for perhaps the very first time it is called). We are assuming it is a segfault because that is what we have been told is most likely what happens when the main-loop never manages to finish.

	(If the any program run on the AP7000 at any point segfaults, we are told it will restart the code, thus running indefinetively until turned off/loaded with functioning code).*/

	int amountOfPeriods = (int) (tone/stroke);
	int periodSize = (int) ABDAC_SAMPLERATE/tone;
	int halfPeriod = periodSize/2;

	//Counter for the first for-loop
	int i;
	for(i = 0; i < amountOfPeriods; i++){
		//Counter for the inner for-loops
		int j;

		//First for-loop should traverse for HALF a period (in ABDAC_Samples)
		for (j = 0; j < halfPeriod; j++){
			inpt->list[start+j+(i*periodSize)] = -SHRT_MAX;
		}
		//Second for-loops should traverse for the rest of the period, resulting in a square-waveform.
		for (j = halfPeriod; j < periodSize; j++){
			inpt->list[start+j+(i*periodSize)] = SHRT_MAX;
		}
	}
	return inpt;
}
