/* legg andre "includes" her, sammen med "defines" */
//Moved the above line to this file instead!

#ifndef OEVING_2_LISTS_AND_CONSTANTS
#define OEVING_2_LISTS_AND_CONSTANTS

#include "limits.h"

/* macroes!!!! \o/ */
#define ABDAC_INT_LEVEL 0
#define BUTTONS_INT_LEVEL 0

/*Array sizes.*/
#define ARRAYSIZE 16
#define SINEARRAYSIZE 128

/*Button values in hex*/
#define SW7 0x80
#define SW6 0x40
#define SW5 0x20
#define SW4 0x10
#define SW3 0x8
#define SW2 0x4
#define SW1 0x2
#define SW0 0x1

/*Obsolete? Rates of which we will play each single element before moving on to next element (creating pitch)*/
#define SAWRATE 16
#define SQUARERATE 16
#define TRIANGLERATE 4
#define SINERATE 2

//#define TONE#OCTAVE AmountOfRepetitionsPerSquareWaveElementPerSecondToGenerateSaidTone
#define G_3 104
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

#define ABDAC_SAMPLERATE 46875

/* megalists! \o/ */
extern short FLAA1[];
extern short FLAA2[];
extern short FLAA3[];
extern short FLAA4[];

extern short FLAASTROKE1[];
extern short FLAASTROKE2[];
extern short FLAASTROKE3[];
extern short FLAASTROKE4[];

// Scale roll 8 steps
extern short SCALE[];
extern short SCALESTROKE[];

// Saw Waveform 17 steps
extern short SAW[];

// Triangle Waveform 17 steps
extern short TRIANGLE[];

// Square Waveform 17 steps
extern short SQUARE[];

#endif
