#include <stdio.h>

/* Project includes */
#include "include/prototypes.h"
#include "include/sampleStructs.h"

Objects *container;

Objects* generateObjects(int amountOfPlayers){
	container = (Objects*) malloc(sizeof(Objects));
	insertPlayers(container, amountOfPlayers);
	return container;
}

void loseHealth(Type type, int listIndex, int amount){
	switch(type){
		case PLAYER:
		//doSomething(object->playerList[listIndex]);
		break;

		case ENEMY:
		break;

		case SHOT:
		break;
	}
}

void move(Type type, int listIndex){
	switch(type){
		case PLAYER:
		break;

		case ENEMY:
		break;

		case SHOT:
		break;
	}
}

void startGame(){
	/* Infinite loop for now */
	int i;
	while(1){
		usleep(100000);
		for(i = 0; i < container->playerSize; i++){
			make_new_frame(container->playerList[i]);
		}
	}
}
