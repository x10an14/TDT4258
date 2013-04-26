#include <stdio.h>

/* Project includes */
#include "include/prototypes.h"
#include "include/listsAndConstants.h"
#include "include/sampleStructs.h"
#include <time.h>
#include <stdlib.h>

Objects *container;
int gameOver = 0;
int playerPoints = 50;
int maxEnemiesOnScreen = 1;
int enemyIncSpeed = 0;
Objects* generateObjects(int amountOfPlayers){

	container = (Objects*) malloc(sizeof(Objects));

	insertPlayers(container, amountOfPlayers);
	turnOnLEDS();

	insertFirstEnemy(container);

	return container;
}

void turnOnLEDS(){
	//lightLeds(0xff);
}

int destroyEnemy(int listIndex){
	draw_square_bckg_colored(container->enemyList[listIndex]->form->x, container->enemyList[listIndex]->form->y, container->enemyList[listIndex]->form->radius);
	killEnemy(container,listIndex);
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

		printf("segdault check 77\n");
				usleep(100000);
	switch(type){
		case PLAYER:
		{
			printf("segdault check 771\n");
				usleep(100000);
		pullButtonsState();
		printf("segdault check 772\n");
				usleep(100000);
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
			printf("BUTTONSTATE: l %d r %d s %d\n", playerLeftButDown, playerRightButDown, playerShootButDown);
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
		{Form *enemForm = container->enemyList[listIndex]->form;
			int playerHit = checkPlayerHit(enemForm, container->playerList[0]->form);
			if(playerHit == 1){
				playerPoints++;
				destroyEnemy(listIndex); // hit player, player gains points
				
				//gameOver = 1;
				//void insertEnemy(Objects *container, int startX, int startY, int health, int listIndex){
				
			} else if (playerHit = 2) { // hit bottom line, player loses points
				playerPoints--;
				destroyEnemy(listIndex);
			}

			if (enemForm->y < 210){}
			else
				enemForm->dy = 0;
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
	printf("segdault check 1\n");
				usleep(100000);
	switch(type){
		case PLAYER:
		{container->playerList[listIndex]->form->x += container->playerList[listIndex]->form->dx;}
		break;

		case ENEMY:
		{container->enemyList[listIndex]->form->x += container->enemyList[listIndex]->form->dx;
			container->enemyList[listIndex]->form->y += container->enemyList[listIndex]->form->dy;}
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
int checkPlayerHit(Form* enemyForm, Form* playerForm){
	printf("segdault check 2\n");
				usleep(100000);
	int ex, ey, er, pr, edy, edx, px, py;
	ex = enemyForm->x; ey = enemyForm->y; er = enemyForm->radius; edx = enemyForm->dx; edy = enemyForm->dy; 
	px = playerForm->x; py = playerForm->y; pr = playerForm->radius;

	if(edy+ey+er > py){
		return 2;
	}

	if (edy + er + pr >= py - ey){
		//printf("it happened ey %d edy %d er %d pr %d py %d ey %d\n", ey, edy, er, pr, py, ey);
		if(ex-px >= 0){
			if (ex-px < er + pr){
				return 1;
			} else
				return 0;
		} else{
			if (px-ex < er + pr){
				return 1;
			} else
				return 0;
		} 
	}else
		return 0;
}

void startGame(){
	int enemyX;
	int tick;
	int tickAct;
	tickAct = 30;

	srand(time(NULL));

	
	while(!gameOver){
		tick++;
		if (tick % tickAct == 0){
			if (container->enemySize < maxEnemiesOnScreen){
				int r = rand() % 307;
				enemyX = 12 + r;
				insertEnemy(container, enemyX, 12, 75, ENEMYSPEED+enemyIncSpeed, container->enemySize);
			}
			if (tickAct >30){
				tickAct--;
				maxEnemiesOnScreen++;
			}
		}

		//printf("cont enemy size %d firs obj form %d\n", container->enemySize, container->enemyList[0]->form->formType);
		usleep(30000);
		make_new_frame();
	}
}

void movePlayer(int listIndex){
	printf("segdault check 3\n");
				usleep(100000);
	Form *form = container->playerList[listIndex]->form;
	if(isPlayerInsideScreen(listIndex)){
	//printf("formtype in if %d\n", form->formType);

		redraw_square(form);
		incrementCoordinates(PLAYER, listIndex);
	} else{
		//printf("Object hit wall...\n");
		form->dx = 0;
	//printf("formtype in else %d\n", form->formType);

		redraw_square(form);
	}
}
void moveEnemy(int listIndex){
	printf("segdault check 4\n");
				usleep(100000);
	Form *form = container->enemyList[listIndex]->form;
	
	//printf("called in move enemy\n");
	//printf("formtype in move enemy %d\n", form->formType);
	redraw_square(form);
	incrementCoordinates(ENEMY, listIndex);
	
}

void make_new_frame(){ //Supposed to move all objects
	printf("segdault check 5\n");
				usleep(100000);
	int i;
	Form *form;
	for(i = 0; i < container->playerSize; i++){
		printf("segdault check 51\n");
				usleep(100000);
		form = container->playerList[i]->form;
printf("segdault check 51f\n");
				usleep(100000);

		computeMove(PLAYER, i);
		movePlayer(i);
	}
	for(i = 0; i < container->enemySize; i++){
printf("segdault check 52\n");
				usleep(100000);
		form = container->enemyList[i]->form;
		//printf("checking enemy %d, his speed is %d\n", i, form->dy);
		computeMove(ENEMY, i);
		moveEnemy(i);
	}
}
