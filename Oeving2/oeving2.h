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



/* prototyper */
int main (int argc, char *argv[]);
static void initIntc(void);
static void initButtons(void);
static void initLeds(void);
static void initAudio(void);
static void initHardware (void);

static void button_isr(void);
static void abdac_isr(void);
void addFrequency(short stroke, short tone, short *list, int start);
int getAmountOfPeriods(int stroke, short tone);
void addZeroes(int amount, short *list, int start);

#endif
