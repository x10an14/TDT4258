#include <stdio.h>
#include "include/sampleStructs.h"

/* Prototypes */
void generateMap(void); //Generate map and put player in the centre.
void startGame(Player *player);
Player* generatePlayer(Player *player);

void spawnEnemies(short amount, short type, short difficulty);//Self-explanatory
void shotHit(void); //When drawing the map (screen), check to see if a player or enemy will get hit by a shot
// void movePlayer(/*Modifiable object for directions? or simply an int/char*/); Remove?

void playSound(/*Pointer to sound to play (we were told that we were given some in the handed out code, no?*/);

void loseHealth(Objects *object, Type type, int listIndex, int amount);//Lose health, maybe flash each time? Continously flash when health is <= 3? Called by shotHit, when true. If 0, kill player/enemy.

void computeMove(Objects *object, Type type, int listIndex); //Moves parameter object according to its role, if player, then like so, if enemy, then like so, and if shot, then like so.

void refreshTick();/* Function which should be called at each "tick", and refresh all sprites on screen after having called move, by first calling move() and then calling function(s) in graphics. */


Player* generatePlayer(Player *player){
	player->form = malloc(sizeof(Form));
	player->form->x = 150;
	player->form->y = 150;
	player->form->dx = 0;
	player->form->dy = -3;
	player->form->radius = 15;
	player->form->red = 0;
	player->form->blue = 0;
	player->form->green = 0;
	player->form->formType = SQUARE;
	return player;
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

void computeMove(Objects *object, Type type, int listIndex){
	switch(type){
		case PLAYER:
		break;

		case ENEMY:
		break;

		case SHOT:
		break;
	}
}

void startGame(Player *player){
	/* Infinite loop for now */
	while(1){
		usleep(30000);
		make_new_frame(player);
	}
}
