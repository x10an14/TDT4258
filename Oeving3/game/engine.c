#include <stdio.h>
#include "include/sampleStructs.h"

Objects container;

/* Prototypes */
void generateMap(void); //Generate map and put player in the centre.
void startGame(Objects *container);
Objects* generateObjects(int amountOfPlayers);

void spawnEnemies(short amount, short type, short difficulty);//Self-explanatory
void shotHit(void); //When drawing the map (screen), check to see if a player or enemy will get hit by a shot
// void movePlayer(/*Modifiable object for directions? or simply an int/char*/); Remove?

void playSound(/*Pointer to sound to play (we were told that we were given some in the handed out code, no?*/);

void loseHealth(Objects *object, Type type, int listIndex, int amount);//Lose health, maybe flash each time? Continously flash when health is <= 3? Called by shotHit, when true. If 0, kill player/enemy.

void move(Objects *object, Type type, int listIndex); //Moves parameter object according to its role, if player, then like so, if enemy, then like so, and if shot, then like so.


Objects* generateObjects(int amountOfPlayers){
	Objects* container = (Objects*) malloc(sizeof(Objects));
	insertPlayers(container, amountOfPlayers);
	return container;
}

void loseHealth(Objects *object, Type type, int listIndex, int amount){
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

void move(Objects *object, Type type, int listIndex){
	switch(type){
		case PLAYER:
		break;

		case ENEMY:
		break;

		case SHOT:
		break;
	}
}

void startGame(Objects *container){
	/* Infinite loop for now */
	int i;
	while(1){
		usleep(100000);
		for(i = 0; i < container->playerSize; i++){
			make_new_frame(container->playerList[i]);
		}
	}
}
