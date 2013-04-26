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
	printf("Done playing sounds...\n\n\n");

	container = (Objects*) malloc(sizeof(Objects));

	insertPlayers(container, amountOfPlayers);
	turnOnLEDS();

	insertFirstEnemy(container);

	return container;
}

void turnOnLEDS(){
	lightLeds(0xff);
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
			//lightLeds(leds);
		}}
		break;

		case ENEMY:
		{container->enemyList[listIndex]->health -= amount;
		if(container->enemyList[listIndex]->health <= 0){
			killEnemy(container, listIndex);
		}}
		break;

		case SHOT:
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
	//printf("Entered compute moves...\n");

	switch(type){
		case PLAYER:
		{
		pullButtonsState();

			Form *playForm = container->playerList[listIndex]->form;
		//printf("passed playform...\n");

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

			if(playerShootButDown){
					// FIRE!
			}
			if ((playerLeftButDown == 1) && (playerRightButDown == 0)){
				playForm->dx = -PLAYERSPEED;
			} else if ((playerLeftButDown == 0) && (playerRightButDown == 1)){
				playForm->dx = PLAYERSPEED;
			} else {
				playForm->dx = 0;
			}
		}

		break;

		case ENEMY:
		{Form *enemyForm = container->enemyList[listIndex]->form;
			int check;
      	check = checkEnemyToPlayerOrGround(enemyForm);
      	if (check == 0){ // no collision whatsoever
      		printf("---check0, moving %d %d\n", listIndex, container->enemySize);

      		moveEnemy(listIndex);
      		enemyForm->y += enemyForm->dy;

      	} else  if(check == 1){ // collision with player
      		//playCash();
      		draw_square_background_color(enemyForm->x, enemyForm->y, enemyForm->radius);
      		killEnemy(container, listIndex);
      		playerPoints+=10;
      		if ((playerPoints % 50 == 0) && (container->playerList[0]->health < 8)){
      			container->playerList[0]->health++;
      		}
      		printf("------->player points %d\n", playerPoints);
      	} else { // collision with ground with no player around
      		draw_square_background_color(enemyForm->x, enemyForm->y, enemyForm->radius);
      		killEnemy(container, listIndex);
      		//playerPoints-=10;
      		
      		if (--container->playerList[0]->health == 0){
      			updateLeds(container->playerList[0]->health);
      			gameOver = 1;
      			drawBackground();
      		}
      		updateLeds(container->playerList[0]->health);
      		printf("------->player healthpoints %d\n", container->playerList[0]->health);
      	}
	      //printf("check is %d\n", check); 
		//Below code is outdated and plain wrong
		// int nextX = enemForm->x + enemForm->dx + enemForm->radius;
		// int nextY = enemForm->y + enemForm->dy + enemForm->radius;
		// if(isEnemyInsideScreen(listIndex, nextX, nextY)){
		// 	enemForm->x = nextX - enemForm->radius;
		// 	enemForm->y = nextY - enemForm->radius;
		// }
		// redraw_square(enemForm, listIndex);
		}
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

int checkEnemyToPlayerOrGround(Form* form){
	printf("beginning checkEnemyToPlayerOrGround\n");
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
	printf("ex %d ey %d px %d py %d out=%d\n", ex, ey, px, py, output);
	return output;

}

void startGame(){
	srand(time(NULL));
	printf("enter startGame\n");

	playBeep();
	printf("enter pstartGame, played beep\n");
	int tick = 0;
	while(!gameOver){
		usleep(30000);
		tick++;
		if(tick % tickAction == 0){
			if (container->enemySize < maxEnemies){
				int r = rand() % 280;
				int enemyStartX = 15 + r;
				printf("startinsert enemy\n");
				insertEnemy(container, enemyStartX, 12, 60, ENEMYSPEED + addEnemySpeed);
				printf("end insert enemy printf form \n");
			}
			if (tickAction>15){
				tickAction--;
				if (maxEnemies < 6){
					maxEnemies++;
					addEnemySpeed++;
				}
			}
		}
		make_new_frame();
	}
	//Game over (Draw RED SCREEN with blinking light/arrow above reset button)
	playBomb();

}

void movePlayer(int listIndex){
	Form *form = container->playerList[listIndex]->form;
	if(isPlayerInsideScreen(listIndex)){
		redraw_square(form);
		incrementCoordinates(PLAYER, listIndex);
	} else{
		printf("Object hit wall...\n");
		form->dx = 0;
		redraw_square(form);
	}
}

void moveEnemy(int listIndex){

  Form *form = container->enemyList[listIndex]->form;
  redraw_square(form);
}

void make_new_frame(){ //Supposed to move all objects
	int i;
	Form *form;
	for(i = 0; i < container->playerMax; i++){
		form = container->playerList[i]->form;
		computeMove(PLAYER, i);
		movePlayer(i);
	}
	printf("enemy size %d\n", container->enemySize);
	
	for(i = 0; i < container->enemySize; i++){
		printf("in loop enemy %d dy \n", i);

		form = container->enemyList[i]->form;
		printf("enemy dy %d\n", form->dy);
    	computeMove(ENEMY, i);
  	} 
}
