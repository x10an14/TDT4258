#include <stdio.h>
#include <time.h>
#include <stdlib.h>

/* Project includes */
#include "include/prototypes.h"
#include "include/listsAndConstants.h"
#include "include/sampleStructs.h"


Objects *container;
int gameOver = 0;
int playerPoints = 0;
int maxEnemies = 2;
int tickAction = 16;
int addEnemySpeed = 0;


Objects* generateObjects(int amountOfPlayers){

	container = (Objects*) malloc(sizeof(Objects));

	insertPlayers(container, amountOfPlayers);
	lightLeds(0xff);

	insertFirstEnemy(container);

	return container;
}

void updateLeds(int health){
	int i;
	char ledStatus;
	ledStatus = 0;
	for (i = health-1 ; i >= 0 ; i-- ){
		ledStatus |= 1 << i;
	}
	lightLeds(ledStatus);
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
		}}
		break;

		case ENEMY:
		{container->enemyList[listIndex]->health -= amount;
		if(container->enemyList[listIndex]->health <= 0){
			killEnemy(container, listIndex);
		}}
		break;
	}
}

int isPlayerInsideScreen(int listIndex){
	Form *player = container->playerList[listIndex]->form;
	int nextX = player->x + player->dx;
	if((nextX - player->radius) >= 0 && (nextX + player->radius) < SCREEN_WIDTH){
		return 1;
	}
	return 0;
}

void computeMove(Type type, int listIndex){
	switch(type){
		case PLAYER:
		{pullButtonsState();
		Form *playForm = container->playerList[listIndex]->form;
		int playerLeftButDown, playerRightButDown, playerShootButDown;
		if (listIndex == 0){
			playerLeftButDown = isButtonDown(PLAYER1_LEFT_BUTTON);
			playerRightButDown = isButtonDown(PLAYER1_RIGHT_BUTTON);
			playerShootButDown = isButtonDown(PLAYER1_SHOOT_BUTTON);
		} else {
			playerLeftButDown = isButtonDown(PLAYER2_LEFT_BUTTON);
			playerRightButDown = isButtonDown(PLAYER2_RIGHT_BUTTON);
			playerShootButDown = isButtonDown(PLAYER2_SHOOT_BUTTON);
		}

		if ((playerLeftButDown == 1) && (playerRightButDown == 0)){
			playForm->dx = -PLAYERSPEED;
		} else if ((playerLeftButDown == 0) && (playerRightButDown == 1)){
			playForm->dx = PLAYERSPEED;
		} else {
			playForm->dx = 0;
		}}
		break;

		case ENEMY:
		{Form *enemyForm = container->enemyList[listIndex]->form;
			int check;
		check = checkEnemyToPlayerOrGround(enemyForm);
		if (check == 0){ // no collision whatsoever
			moveEnemy(listIndex);
			enemyForm->y += enemyForm->dy;
		} else  if(check == 1){ // collision with player
			//playCash(); //This function call goes to slow since it's called in the middle of more heavy-weight functions. Therefore commented away.
			draw_square_background_color(enemyForm->x, enemyForm->y, enemyForm->radius);
			killEnemy(container, listIndex);
			playerPoints+=10;
			if ((playerPoints % 50 == 0) && (container->playerList[0]->health < 8)){
				container->playerList[0]->health++;
				updateLeds(container->playerList[0]->health);
			}
		} else { // collision with ground with no player around
			draw_square_background_color(enemyForm->x, enemyForm->y, enemyForm->radius);
			killEnemy(container, listIndex);
			if (--container->playerList[0]->health == 0){
				updateLeds(container->playerList[0]->health);
				gameOver = 1;
			}
			updateLeds(container->playerList[0]->health);
		}}
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
	}
}

int checkEnemyToPlayerOrGround(Form* form){
	int ex, ey, edy, er, px, pr, py;
	int output;

	ex = form->x; ey = form->y; edy = form->dy; er = form->radius;
	px = container->playerList[0]->form->x; py = container->playerList[0]->form->y;
	pr = container->playerList[0]->form->radius;
	if (ey + edy >= py+pr){
		output = 2;
	} else if(er+pr+edy >= py-ey){
		if((ex >= px) && (ex-px < er+pr)){
			output = 1;
		} else if ((px > ex) && (px-ex < er+pr)){
			output = 1;
		} else {
			output = 0;
		}
	} else {
		output = 0;
	}
	return output;
}

void startGame(){
	srand(time(NULL));
	printf("Entered startGame...\n");

	playBeep();
	int tick = 0;
	while(!gameOver){
		usleep(30000);
		tick++;
		if(tick % tickAction == 0){
			if (container->enemySize < maxEnemies){
				int r = rand() % 280;
				int enemyStartX = 15 + r;
				insertEnemy(container, enemyStartX, 12, 60, ENEMYSPEED + addEnemySpeed);
			}
			if (tickAction>15){
				tickAction--;
				if (maxEnemies < 5){
					maxEnemies++;
					addEnemySpeed++;
				}
			}
		}
		make_new_frame();
	}
	//Game over
	playBomb();
	while(playCurrent != 0){
		playCurrent();
	}
}

void movePlayer(int listIndex){
	Form *form = container->playerList[listIndex]->form;
	if(isPlayerInsideScreen(listIndex)){
		redraw_square(form);
		incrementCoordinates(PLAYER, listIndex);
	} else{
		form->dx = 0;
		redraw_square(form);
	}
}

void moveEnemy(int listIndex){
	Form *form = container->enemyList[listIndex]->form;
	redraw_square(form);
}

void make_new_frame(){
	int i;
	Form *form;
	for(i = 0; i < container->playerMax; i++){
		form = container->playerList[i]->form;
		computeMove(PLAYER, i);
		movePlayer(i);
	}
	for(i = 0; i < container->enemySize; i++){
		form = container->enemyList[i]->form;
		computeMove(ENEMY, i);
	}
	playCurrent();
}
