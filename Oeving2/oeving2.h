/*****************************************************************************
 *
 * Øving 2 UCSysDes
 *
 * Headerfil
 *
 *****************************************************************************/

#ifndef OEVING_2_H /* vanlig måte å unngå headerrekursjon på */
#define OEVING_2_H

// #include <avr32/ap7000.h> /* inkludere Atmel-headerfil */
// #include <sys/interrupts.h>
//Commented out the above two includes so that we can compile on our own machines (Added needed includes below)

#include "sys/interrupts.h"
#include "avr32/ap7000.h"
#include "avr32/abdac_101.h"
//The below include is for a header file we've written ourselves.
#include "listsAndConstants.h"


//Below are two structs we've made ourselves for this assignment

/*A "sample" struct holding both a list of amplitue or tone values, and potentially a list of strokes.
It also contains the size of the two lists, and an int member used as a bool (usingStrokeList), as well
as two counters and another maxvalue-member (similar to size)*/
typedef struct sample{
		//List of short-values (amplitude or tone values) for the tune that this struct holds
		short *list;
		//A list of short values carrying the X in 1/X-fraction that will always be how much of a second the corresponding tone in list should be played.
		short *strokeList;
		//Int used as bool for whether list is played with the help of strokeList or rateCntr
		short usingStrokeList;
		//Counter and size for both abovementioned lists (int's because they're so fricking huge numbers)
		int playCntr, size;
		//Counter and maxvalue for rate of playing each element in list. Used when strokeList is not used. These two members will also affect pitch however, which the two previous will not if used as intended.
		short rateCntr, rateMax;
}sample;

/*A "sampleCollection" struct which is meant to have an iterable collection of samples. (Used in main (outcommented code - for now))*/
typedef struct sampleCollection{
		//List to pointers which point a sample struct each
		sample **list;
		//Size of abovementioned list
		short size;
}sampleCollection;

/*Pointers which are should be possible to use "globally" between the C-files.
The pointers are used for interacting with the STK1000.*/

//Buttons ParallellInputOutput pointer
extern volatile avr32_pio_t *piob;
//LEDs ParallellInputOutput pointer
extern volatile avr32_pio_t *pioc;
//Pointer to PowerManager
extern volatile avr32_pm_t *pm;
//Pointer to ABDAC controller
extern volatile avr32_abdac_t *abdac;

//All below lists are used solely in main, and therefore do not need to have the type modifier extern.
sample *flaaklypaSample, *flaa1, *flaa2, *flaa3, *flaa4, *squareSample,
		*sawSample, *triangleSample, *scaleSample, *sineSample, *currentSample;
sampleCollection *flaaklyp;

/* prototyper */
int main (int argc, char *argv[]);
void initIntc(void);
void initButtons(void);
void initLeds(void);
void initAudio(void);
void initHardware (void);

void button_isr(void);
void abdac_isr(void);

//Our own added prototypes
sample* addFrequency(sample *inpt, short stroke, short tone, int start);
int getAmountOfPeriods(int stroke, short tone);
void addZeroes(int amount, short *list, int start);
void setAbdacOnOff(int value);
sample* sampleConstructor(sample *inpt, int size, int maxRate, short *tonelist, short *strokelist);

#endif
