/*****************************************************************************
 *
 * Øving 2 UCSysDes
 *
 *****************************************************************************/

#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include "sys/interrupts.h"
#include "oeving2.h"

short FLAA1[] = {E4,A4,B4,C5,B4,A4,G4,E4};
short FLAA2[] = {C4,D4,E4,F4,E4,D4,C4,D4,E4,D4,C4,B3};
short FLAA3[] = {C4,D4,E4,D4,C4,B3,A3,G_3,A3};
short FLAA4[] = {A3,A4,G4,F4,E4,C4,A3,B3,C4,D4,E4,F4,E4,D4,E4};

short FLAASTROKE1[] = {4,4,4,8,8,4,4,4};
short FLAASTROKE2[] = {8,8,4,8,8,4,8,8,4,8,8,2};
short FLAASTROKE3[] = {8,8,4,8,8,4,8,8,1};
short FLAASTROKE4[] = {4,2,8,8,4,4,4,8,8,4,8,8,4,4,1};

// Scale roll 8 steps
short SCALE[] = {C4,D4,E4,F4,G4,A4,B4,C5};
short SCALESTROKE[] = {2,2,2,2,2,2,2,2};

// Saw Waveform 17 steps
short SAW[] = {-SHRT_MAX, -(7/8)*SHRT_MAX, -(6/8)*SHRT_MAX, -(5/8)*SHRT_MAX,
						-(4/8)*SHRT_MAX, (-3/8)*SHRT_MAX, -(2/8)*SHRT_MAX, -(1/8)*SHRT_MAX,
						0, (1/8)*SHRT_MAX, (2/8)*SHRT_MAX, (3/8)*SHRT_MAX, (4/8)*SHRT_MAX,
						(5/8)*SHRT_MAX, (6/8)*SHRT_MAX, (7/8)*SHRT_MAX};

// Triangle Waveform 17 steps
short TRIANGLE[] = {0,(1/4)*SHRT_MAX, (2/4)*SHRT_MAX, (3/4)*SHRT_MAX,
						(4/4)*SHRT_MAX, (3/4)*SHRT_MAX, (2/4)*SHRT_MAX, (1/4)*SHRT_MAX, 0,
						-(1/4)*SHRT_MAX, -(2/4)*SHRT_MAX, -(3/4)*SHRT_MAX, -(4/4)*SHRT_MAX,
						-(3/4)*SHRT_MAX, -(2/4)*SHRT_MAX, -(1/4)*SHRT_MAX};

// Square Waveform 16 steps
short SQUARE[]={SHRT_MAX, SHRT_MAX, SHRT_MAX, SHRT_MAX, SHRT_MAX, SHRT_MAX,
						SHRT_MAX, SHRT_MAX, -SHRT_MAX, -SHRT_MAX, -SHRT_MAX, -SHRT_MAX,
						-SHRT_MAX, -SHRT_MAX, -SHRT_MAX, -SHRT_MAX};


int main (int argc, char *argv[]){
	// Creating of sinus wave list 128 steps
	short *sineSampleList = (short*) malloc(SINEARRAYSIZE*sizeof(short));;
	//for-loop cntr
	int i;
	for (i=0; i < SINEARRAYSIZE; i++){
		sineSampleList[i] = SHRT_MAX*sin((M_PI*i)/SINEARRAYSIZE);
	}


/*
	flaa1 = sampleConstructor(flaa1, 8, 0, FLAA1, FLAASTROKE1);
	flaa2 = sampleConstructor(flaa2, 12, 0, FLAA2, FLAASTROKE2);
	flaa3 = sampleConstructor(flaa3, 9, 0, FLAA3, FLAASTROKE3);
	flaa4 = sampleConstructor(flaa4, 15, 0, FLAA4, FLAASTROKE4);*/
	sawSample = sampleConstructor(sawSample, ARRAYSIZE, SAWRATE, SAW, NULL);
	squareSample = sampleConstructor(squareSample, ARRAYSIZE, SQUARERATE, SQUARE, NULL);
	sineSample = sampleConstructor(sineSample, SINEARRAYSIZE, SINERATE, sineSampleList, NULL);
	triangleSample = sampleConstructor(triangleSample, ARRAYSIZE, TRIANGLERATE, TRIANGLE, NULL);

  /*
	//Repeat of all above, except that pointer is a sampleCollection* pointer
	flaaklyp = (sampleCollection*) malloc(sizeof(sampleCollection));
	flaaklyp->size = 10;
	flaaklyp->list = (sample**) malloc(10*sizeof(sample*));*/

	/*The below for-loop declares the list member of the sampleCollection pointer to be the addresses of the above sample pointers
	(Flaaklypa variants only!)
	for (i = 0; i < 10; i++){
		if(i == 0 || i == 2 || i == 8 || i == 6){
			flaaklyp->list[i] = flaa1;
		} else if(i == 1 || i == 7){
			flaaklyp->list[i] = flaa2;
		} else if(i == 3 || i == 9){
			flaaklyp->list[i] = flaa3;
		} else{
			flaaklyp->list[i] = flaa4;
		}
	}*/

	//Count to see how much space is needed for flaaklypaSample->list / size
	//cntr for how much space needed
	int memCntr = 0;/*
	for(i = 0; i < flaaklyp->size; i++){
		//Temporary variable for readability
		sample *small = flaaklyp->list[i];
		//Inner for-loop cntr
		int j, size;
		for(j = 0; j < small->size; j++){
			//size == temp variable with how much space is needed for each period of each tone in the final list
			size = (int) (ABDAC_SAMPLERATE/small->strokeList[j]);
			//Self-explanatory (if you've read the above comments)
			memCntr += size;
		}
	}

	flaaklypaSample = sampleConstructor(flaaklypaSample, memCntr, 0, NULL, NULL);

	//Assigning(/Combining) values to final list (flaaklypaSample->list)*/
	int cntr = 0;/*
	for(i = 0; i < flaaklyp->size; i++){
		sample *small = flaaklyp->list[i];
		int j, size;
		for(j = 0; j < small->size; j++){
			size = (int)(ABDAC_SAMPLERATE/small->strokeList[j]);
			//Her er det en feil! Se i addFrequency for forklaring!
			flaaklypaSample = addFrequency(flaaklypaSample, small->strokeList[j], small->list[j], cntr);
			cntr += size;
		}
	}*/


	/*Do the same for our scaleSample playlist*/
	memCntr = 0;
	int size;
	for(i = 0; i < 8; i++){
		//temp variable with how many times each tone is played
		size = (int) (ABDAC_SAMPLERATE/SCALESTROKE[i]);
		//Self-explanatory
		memCntr += size;
	}

	scaleSample = sampleConstructor(scaleSample, memCntr, 0, SCALE, SCALESTROKE);

	//Assigning(/Combining) values to final list (flaaklypaSample->list)
	cntr = 0;
	for(i = 0; i < scaleSample->size; i++){
		size = (int) (ABDAC_SAMPLERATE/SCALESTROKE[i]);
		//Her er det en feil! Se i addFrequency for forklaring!
		addFrequency(SCALESTROKE[i], SCALE[i], scaleSample->list, cntr);
		cntr += size;
	}

	initHardware();

	while(1);
	return 0;
}
