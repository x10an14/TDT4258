#include <stdio.h>
#include "include/sampleStructs.h"

/* Prototypes */
void generateMap(void); //Generate map and put player in the centre.

void startGame(player *player);

void spawnEnemies(short amount, short type, short difficulty);//Self-explanatory
void shotHit(void); //When drawing the map (screen), check to see if a player or enemy will get hit by a shot
// void movePlayer(/*Modifiable object for directions? or simply an int/char*/); Remove?

void playSound(/*Pointer to sound to play (we were told that we were given some in the handed out code, no?*/);

void loseHealth(int amount);//Lose health, maybe flash each time? Continously flash when health is <= 3? Called by shotHit, when true. If 0, kill player/enemy.

void move(void *obj); //Moves parameter object according to its role, if player, then like so, if enemy, then like so, and if shot, then like so.

void refreshTick();/* Function which should be called at each "tick", and refresh all sprites on screen after having called move, by first calling move() and then calling function(s) in graphics. */

 /*To write to screen, use fbfd, open /dev/fbd0(?), and then use mmap to write to it. */

void startGame(player *player){
	/* Infinite loop for now */
	while(1){
		usleep(100000);

		make_new_frame(player);
	}
}
