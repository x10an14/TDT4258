// #include <linux/soundcard.h> //For sound (Not currently in use)
#include <stdio.h>
#include <unistd.h>
// #include <sys/types.h>

/* Project include files */
#include "include/prototypes.h"
#include "include/listsAndConstants.h"
#include "include/sampleStructs.h"



int main(){
	printf("Initializing game...\n");

	/* Initialize structs */
	setUpLCDDriver();
	Objects *container = generateObjects(1);
	printf("Main is about to call startGame()\n");
	startGame();

	return 0;
}
