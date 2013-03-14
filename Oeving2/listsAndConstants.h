/* legg andre "includes" her, sammen med "defines" */
//Moved the above line to this file instead!

#ifndef OEVING_2_H_LISTS_AND_CONSTANTS
#define OEVING_2_H_LISTS_AND_CONSTANTS

/* macroes!!!! \o/ */
#define ABDAC_INT_LEVEL 0
#define BUTTONS_INT_LEVEL 0

/*Array sizes.*/
#define ARRAYSIZE 16
#define SINEARRAYSIZE 128

/*Button values in hex values*/
#define SW7 0x80
#define SW6 0x40
#define SW5 0x20
#define SW4 0x10
#define SW3 0x8
#define SW2 0x4
#define SW1 0x2
#define SW0 0x1

/*Rates of which we will play each single element before moving on to next element (manipulating pitch and time each element will be played simultaneously)*/
#define SAWRATE 9
#define TRIANGLERATE 16
#define SQUARERATE 24
#define SINERATE 3

//List of macroes, where we have the name of a tone, which will be replaced with the frequency of said tone divided by 2. This is because we're presupposing we will use a square waveform to play the listts using these tones.
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

//The rate at which the ABDAC samples each output ((12*1000^2)/256)
//Testing OSC0 instead at 20Mhz
#define ABDAC_SAMPLERATE 78125

//Lists which in theory can be used in every single C-file, so therefore they are declared with type-modifier extern. Have not tested whether it is needed, because we only really use them in oeving2_main.c
//Tone-lists which together in specific order compose the tune "Reodors Ballade" from the famous norwegian story "Flåklypa"
extern short FLAA1[];
extern short FLAA2[];
extern short FLAA3[];
extern short FLAA4[];

//Stroke-lists for each of the above tone-lists.
extern short FLAASTROKE1[];
extern short FLAASTROKE2[];
extern short FLAASTROKE3[];
extern short FLAASTROKE4[];

//A tone-list and corresponding stroke-list for the scaleSample in main.
extern short SCALE[];
extern short SCALESTROKE[];

//Declaration of the saw waveform list
extern short SAW[];

//Declaration of the triangle waveform list
extern short TRIANGLE[];

//Declaration of the square waveform list
extern short SQUARE[];

#endif
