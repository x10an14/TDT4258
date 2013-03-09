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
typedef struct smallSample{
    int **list;
    int size;
}smallSample;

typedef struct sample{
    smallSample **list;
    int size;
}sample;

/* legg andre "includes" her, sammen med "defines" og prototyper */
#define ABDAC_INT_LEVEL 0
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

sample flaaklypa;
smallSample flaa1, flaa2, flaa3, flaa3, flaa4;
flaa1.size = 8;
flaa1.list[flaa1.size] = {E4,A4,B4,C5,B4,A4,G4,E4};
flaa2.size = 12;
flaa2.list[flaa2.size] = {C4,D4,E4,F4,E4,D4,C4,D4,E4,D4,C4,B3};
flaa3.size = 8;
flaa3.list[flaa3.size] = {C4,D4,E4,D4,C4,B3,A3,A3};
flaa4.size = 15;
flaa4.list[flaa4.size] = {A3,A4,G4,F4,E4,C4,A3,B3,C4,D4,E4,F4,E4,D4,C4};
flaaklypa.size = 10;


/* prototyper */
int main (int argc, char *argv[]);
static void initIntc(void);
static void initButtons(void);
static void initLeds(void);
static void initAudio(void);
static void initHardware (void);

static void button_isr(void);
static void abdac_isr(void);

#endif
