// #include <linux/soundcard.h> //For sound (Not currently in use)
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>

/* Project include files */
#include "include/listsAndConstants.h"
#include "include/sampleStructs.h"



int main(){
	printf("Initializing game...\n");

	/* Initialize structs */
	player playerOne;

	playerOne.playerX = 150;
	playerOne.playerY = 220;
	playerOne.dx = 6;
	playerOne.dy = 0;
	playerOne.radius = 15;
	playerOne.col_red = 0;
	playerOne.col_blue = 0;
	playerOne.col_green = 0;
	return 0;
}
