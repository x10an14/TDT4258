#include <stdio.h>

/* Project includes */
#include "include/prototypes.h"
#include "include/listsAndConstants.h"
#include "include/sampleStructs.h"

Objects *container;
int gameOver = 0;

Objects* generateObjects(int amountOfPlayers){

	container = (Objects*) malloc(sizeof(Objects));

	insertPlayers(container, amountOfPlayers);
	turnOnLEDS();

	insertFirstEnemy(container);

	return container;
}

void turnOnLEDS(){
	lightLeds(0xff);
}

void loseHealth(Type type, int listIndex, int amount){
	switch(type){
		case PLAYER:
		{container->playerList[listIndex]->health -= amount;
		if(container->playerList[listIndex]->health <= 0){
			gameOver = 1;
			killPlayer(container, listIndex);
		} else{ //Turn off next LED
			int dividend = container->playerList[listIndex]->healthMax / 8;
			int leds = container->playerList[listIndex]->health / dividend;
			lightLeds(leds);
		}
		}
		break;

		case ENEMY:
		break;

		case SHOT:
		break;
	}
}

int isPlayerInsideScreen(int listIndex){
	Form *player = container->playerList[listIndex]->form;
	int nextX = player->x + player->dx + player->radius;
	if(nextX >= 0 && nextX < SCREEN_WIDTH){
		return 1;
	}
	return 0;
}

int isEnemyInsideScreen(int listIndex, int nextX, int nextY){
	Form *enemy = container->enemyList[listIndex]->form;
	if(nextX >= 0 && nextX < SCREEN_WIDTH &&
		nextY >= 0 && nextY < SCREEN_HEIGHT){
		return 1;
	}
	return 0;
}

int isShotInsideScreen(int listIndex){

}

void computeMove(Type type, int listIndex){
	switch(type){
		case PLAYER:
		{Form *playForm = container->playerList[listIndex]->form;

		if(isButtonDown(5)){
			// FIRE!
		}
		movePlayer(playForm);}
		break;

		case ENEMY:
		{Form *enemForm = container->enemyList[listIndex]->form;
		int nextX = enemForm->x + enemForm->dx + enemForm->radius;
		int nextY = enemForm->y + enemForm->dy + enemForm->radius;
		if(isEnemyInsideScreen(listIndex, nextX, nextY)){
			enemForm->x = nextX - enemForm->radius;
			enemForm->y = nextY - enemForm->radius;
		}
		redraw_square(enemForm);}
		break;

		case SHOT:
		break;
	}
}

void incrementCoordinates(Type type, int listIndex){
	switch(type){
		case PLAYER:
		{container->playerList[listIndex]->form->x += container->playerList[listIndex]->form->dx;}
		break;

		case ENEMY:
		{container->enemyList[listIndex]->form->x += container->enemyList[listIndex]->form->dx;}
		break;

		case SHOT:
		{container->shotList[listIndex]->form->x += container->shotList[listIndex]->form->dx;}
		break;
	}
}

int checkCollision(Form *form1, Form *form2){
	Form *botForm, *topForm;
	int topFormXleft, topFormXright, topFormYbot;
	int botFormXleft, botFormXright, botFormYtop;
	if(form1->y >= form2->y){
		botForm = form2;
		topForm = form1;
	} else{
		botForm = form1;
		topForm = form2;
	}
	topFormXleft = topForm->x - topForm->radius;
	topFormXright = topForm->x + topForm->radius;
	topFormYbot = topForm->y + topForm->radius;

	botFormXleft = botForm->x - botForm->radius;
	botFormXright = botForm->x + botForm->radius;
	botFormYtop = botForm->y - botForm->radius;

	if(topFormYbot <= botFormYtop &&
		(topFormXright >= botFormXleft ||
		topFormXleft <= botFormXright)){
		return 1;
	} else{
		return 0;
	}
}

void startGame(){
	/* Infinite loop for now */
	initiateIO();
	printf("lightingleds\n");
	lightLeds(0x5f);

	printf("leds lighta\n");
	int i;
	while(1){
		usleep(30000);
		make_new_frame();
	}
}

void make_new_frame(){ //Supposed to move all objects
	int i;
	Form *form;
	for(i = 0; i < container->playerMax; i++){
		form = container->playerList[i]->form;
		movePlayer(form, i);
	}
}
