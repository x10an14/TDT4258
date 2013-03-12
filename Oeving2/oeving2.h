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
//Commented out above so that we can compile on our own machines (see lines below)
#include <stdlib.h>
#include "sys/interrupts.h"
#include "avr32/ap7000.h"
#include "avr32/abdac_101.h"


/*Structs we've made ourselves for this assignment*/

typedef struct sample{
    //List of short-values (amplitude/tone values) for tune that this struct holds
    short *list;
    //A list of short values carrying the X in Y/X where Y always equals 1. (To get tones of different time length)
    short *strokeList;
    //Int used as bool for whether list is used with strokeList or rateCntr
    short usingStrokeList;
    //Counter and size for both abovementioned lists
    short playCntr, size;
    //Counter and maxvalue for rate of playing (If timelist is not used, these two are meant to be used instead)
    short rateCntr, rateMax;
}sample;

typedef struct sampleCollection{
    //List to pointers which point a sample struct each
    sample **list;
    //Size of abovementioned list
    short size;
}sampleCollection;

volatile avr32_pio_t *piob = &AVR32_PIOB;
volatile avr32_pio_t *pioc = &AVR32_PIOC;
volatile avr32_pm_t *pm = &AVR32_PM;
volatile avr32_abdac_t *abdac = &AVR32_ABDAC;

//All below are global
short *currentSamplePtr = NULL;
int *ratePtr = NULL;
sample *flaaklypaSample, *flaa1, *flaa2, *flaa3, *flaa4,
       *squareSample, *sawSample, *triangleSample, *scaleSample, *sineSample, *currentSample;
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
void addFrequency(short stroke, short tone, short *list, int start);
int getAmountOfPeriods(int stroke, short tone);
void addZeroes(int amount, short *list, int start);
void setAbdacOnOff(int value);

#endif
