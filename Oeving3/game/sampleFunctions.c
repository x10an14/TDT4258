#include "stdio.h"

/* Project includes */
#include "includ/sampleStructs.h"

/* Prototypes */
Objects *insertPlayers(Objects *container, int amountOfPlayers, Player **newPlayerList){
	container->playerList = malloc(sizeof(Player*));
	for(int i = 0; i < container->amountOfPlayers; i++){
		container->playerList[i] = newPlayerList[i];
	}
	container->playerSize = amountOfPlayers;
	return container;
}

