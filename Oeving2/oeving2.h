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
typedef struct smpl{
    short *list;
    short *timeList;
    short playCntr;
    //Implement counter variable for when playing a sample?
    short size;
}sample;

typedef struct smplCollectn{
    sample **list;
    short size;
}sampleCollection;

/* legg andre "includes" her, sammen med "defines" og prototyper */
#define ABDAC_INT_LEVEL 1
#define BUTTONS_INT_LEVEL 0

#define ARRAYSIZE 17
#define SQUARESIZE 2
#define TONESIZE 8
#define SW7 0x80
#define SW6 0x40
#define SW5 0x20
#define SW4 0x10
#define SW3 0x8

#define SAWRATE 20
#define SQUARERATE 11
#define TRIANGLERATE 18

//#define TONE#OCTAVE AmountOfRepetitionsPerSquareWaveElementPerSecondToGenerateSaidTone
#define A3 110
#define B3 123
#define C4 131
#define D4 147
#define E4 167
#define F4 175
#define G4 196
#define A4 220
#define B4 247
#define C5 262

/* megalists! \o/ */
short FLAA1[] = {E4,A4,B4,C5,B4,A4,G4,E4};
short FLAA2[] = {C4,D4,E4,F4,E4,D4,C4,D4,E4,D4,C4,B3};
short FLAA3[] = {C4,D4,E4,D4,C4,B3,A3,A3};
short FLAA4[] = {A3,A4,G4,F4,E4,C4,A3,B3,C4,D4,E4,F4,E4,D4,C4};
short TIME1[] = {4,4,4,5,4,4,3,4};
short TIME2[] = {4,4,4,4,4,4,4,4,4,4,4,2};
short TIME3[] = {4,4,2,4,4,2,2,2};
short TIME4[] = {2,2,4,4,4,4,2,4,4,2,4,4,4,4,4};


/* prototyper */
int main (int argc, char *argv[]);
static void initIntc(void);
static void initButtons(void);
static void initLeds(void);
static void initAudio(void);
static void initHardware (void);

static void button_isr(void);
static void abdac_isr(void);
void addFrequency(int timeDiv, short tone, short *list, int start);
int getFrequencySize(int timeDiv, short tone, int waveFormSize);
void addZeroes(int amount, short *list, int start);

#endif
