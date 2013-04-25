#include <linux/soundcard.h> //For sound
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

	/* Give structs to engine to play with */

	FILE* lcdDriver = fopen("/dev/fb0", "r+");
	//FILE* testFile = fopen("/usr/src/testRead", "r");
	draw_background(lcdDriver);

	printf("hello world, file: %d errno %s\n", lcdDriver, strerror(errno));

	playerOne.playerX = 150;
	playerOne.playerY = 220;
	playerOne.dx = 6;
	playerOne.dy = 0;
	playerOne.radius = 15;
	playerOne.col_red = 0;
	playerOne.col_blue = 0;
	playerOne.col_green = 0;

	/* Infinite while to receive events from drivers? And send inputs to gameEngine? */

	while(1){
		usleep(100000);

		make_new_frame(lcdDriver, &playerOne);
	}

	return 0;
}
