#include <stdio.h>

/* Project includes */
#include "include/prototypes.h"
#include "include/listsAndConstants.h"
#include "include/sampleStructs.h"

Objects *container;

// char LED0 = "01";
// char LED1 = "02";
// char LED2 = "04";
// char LED3 = "08";
// char LED4 = "10";
// char LED5 = "20";
// char LED6 = "40";
// char LED7 = "80";

Objects* generateObjects(int amountOfPlayers){
	container = (Objects*) malloc(sizeof(Objects));

	printf("Finished making container\n");

	insertPlayers(container, amountOfPlayers);

	printf("finished making player 1\n");

	insertFirstEnemy(container);

	printf("finished making first enemy\n");

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

int isPlayerInsideScreen(int listIndex, int nextX){
	Form *player = container->playerList[listIndex]->form;
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
		int nextX = playForm->x + playForm->dx + playForm->radius;
		if(isPlayerInsideScreen(listIndex, nextX)){
			playForm->x = nextX - playForm->radius;
		}
		redraw_square(playForm);}
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

void startGame(){
	/* Infinite loop for now */
	initiateIO();
	printf("lightingleds\n");
	lightLeds(0x5f);

	printf("leds lighta\n");
	int i;
	while(1){
		usleep(30000);
		make_new_frame(container);
	}
}
