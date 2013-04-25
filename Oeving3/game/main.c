// #include <linux/soundcard.h> //For sound (Not currently in use)
#include <stdio.h>
#include <unistd.h>
// #include <sys/types.h>

/* Project include files */
#include "include/listsAndConstants.h"
#include "include/sampleStructs.h"



int main(){
	printf("Initializing game...\n");

	/* Initialize structs */
	Player playerOne;
	setImageStruct();
	startGame(&playerOne);

	return 0;
}
