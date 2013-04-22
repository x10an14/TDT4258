##include "include/sampleStructs.h"

/* Prototypes */
void movePlayer(/*Modifiable object for directions? or simply an int/char*/);
void playSound(/*Pointer to sound to play (we were told that we were given some in the handed out code, no?*/);
void generateMap(void); //Generate map and put player in the centre.
void expandMap(/*Expand map, same direction as player?*/);
void generateBlock(void); //Generate a block which is added to the map (this function is normally used by both generatemap and expandmap);
void loseHealth(int amount);//Lose health, maybe flash each time? Continously flash when health is <= 3?

 /*To write to screen, use fbfd, open /dev/fbd0(?), and then use mmap to write to it. */
