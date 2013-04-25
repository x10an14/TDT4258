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

void computeMove(Type type, int listIndex){
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
	draw(container->playerList[0]->form);
	while(1){
		usleep(30000);
		make_new_frame(container);
	}
}
