/* legg andre "includes" her, sammen med "defines" og prototyper */
//Moved the above line to this file instead!

/* macroes!!!! \o/ */
#define ABDAC_INT_LEVEL 1
#define BUTTONS_INT_LEVEL 0

/*Array sizes.*/
#define ARRAYSIZE 17
#define TONESIZE 8

/*Button values in hex*/
#define SW7 0x80
#define SW6 0x40
#define SW5 0x20
#define SW4 0x10
#define SW3 0x8

/*Obsolete? Rates of which we will play each single element before moving on to next element (creating pitch)*/
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

// Saw Waveform 17 steps
short SAW[] = {-8,-7,-6,-5,-4,-3,-2,-1,0,1,2,3,4,5,6,7,8};
// Triangle Waveform 17 steps
short TRIANGLE[] = {0,2,4,6,8,6,4,2,0,-2,-4,-6,-8,-6,-4,-2,0};

short toneScale[TONESIZE] = {C4,D4,E4,F4,G4,A4,B4};
