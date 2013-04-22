#include "stdio.h"
#include "linux/soundcard.h" //For sound

/* Project include files */
#include "include/listsAndConstants.h"


int main(){
	short result = -1;
	printf("Initializing game...\n");

	/* Initialize screen through io.s function A */
	result = A();
	if(!result){
		printf("A() had following error code: %d\n", result);
		return result;
	}

	/* Initialize drivers through io.s function B(C?) */
	result = B();
	if(!result){
		printf("B() had following error code: %d\n", result);
		return result;
	}

	/* Initialize structs */

	/* Give structs to engine to play with */

	/* Infinite while to receive events from drivers? And send inputs to gameEngine? */

	return 0;
}
