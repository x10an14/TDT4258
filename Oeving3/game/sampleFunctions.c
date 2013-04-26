#include "stdio.h"

/* Project includes */
#include "include/sampleStructs.h"
#include "include/listsAndConstants.h"
#include "include/prototypes.h"


void insertPlayers(Objects *container, int amountOfPlayers){
	Player **List = (Player**) malloc(sizeof(Player*)*2);
	int i;
	for(i = 0; i < amountOfPlayers; i++){
		List[i] = malloc(sizeof(Player));
		List[i]->health = 250; List[i]->healthMax = 250;
		List[i]->form = (Form*) malloc(sizeof(Form));
		int radius = 16;
		List[i]->form->radius = radius;
		List[i]->form->x = 150; List[i]->form->y = SCREEN_HEIGHT-(radius/2)-10;
		List[i]->form->dx = -PLAYERSPEED; List[i]->form->dy = 0;
		List[i]->form->formType = SQUARE;
		List[i]->form->red = 0; List[i]->form->blue = 253;
		List[i]->form->green = 0;
		draw(List[i]->form);
	}
	container->playerList = List;
	container->playerSize = amountOfPlayers;
	container->playerMax = amountOfPlayers;
}

void insertFirstEnemy(Objects *container){
	Enemy **List = calloc(2, sizeof(Enemy*));
	List[0] = malloc(sizeof(Enemy));

	List[0]->health = 75; List[0]->healthMax = 75;
	Form *form = malloc(sizeof(Form));
	int radius = 10;
	form->radius = radius;
	form->x = radius + 10+5;
	form->y = radius + 10+5;
	form->dx = 0;
	form->dy = ENEMYSPEED;
	form->formType = SQUARE;
	form->red = 253; form->blue = 0;
	form->green = 0;

	List[0]->form = form;
	draw(List[0]->form);

	container->enemyList = List;
	container->enemyMax = 2;
	container->enemySize = 1;
}

void insertEnemy(Objects *container, int startX, int startY, int health, int speed){
	int listIndex = container->enemySize;
	while(container->enemySize + 1 >= container->enemyMax){
		container->enemyList = (Enemy**) realloc(container->enemyList, 2*container->enemyMax*sizeof(Enemy*));
		printf("\n##################expanding maxenemy from %d to %d\n\n\n", container->enemyMax, container->enemyMax*2);
		container->enemyMax *= 2;
	}

	int i = listIndex;
	if(container->enemyMax == 1){
		i = 1;
	}

	container->enemyList[i] = malloc(sizeof(Enemy));
	container->enemyList[i]->form = malloc(sizeof(Form));
	printf("\n##################form is %d\n",container->enemyList[i]->form);
	container->enemyList[i]->health = health;
	container->enemyList[i]->healthMax = health;

	container->enemyList[i]->form->x = startX;
	container->enemyList[i]->form->y = startY;
	container->enemyList[i]->form->dy = speed;
	container->enemyList[i]->form->dx = 0;
	container->enemyList[i]->form->radius = 10;
	container->enemyList[i]->form->formType = SQUARE;
	container->enemyList[i]->form->red = 253; container->enemyList[i]->form->blue = 0;
	container->enemyList[i]->form->green = 0;

	container->enemySize += 1;

	draw(container->enemyList[i]->form);
}

void insertShot(Objects *container, int startX, int startY, int damage){

}

void killPlayer(Objects *container, int listIndex){ //Not tested, but should work (?)
	free(container->playerList[listIndex]->form);
	free(container->playerList[listIndex]);
	if(listIndex != container->playerSize - 1){
		int i;
		for(i = listIndex+1; i < container->playerSize; i++){
			container->playerList[i-1] = container->playerList[i];
		}
	}
	container->playerSize -= 1;
}

void killEnemy(Objects *container, int listIndex){ //Not tested, but should work (?)
	free(container->enemyList[listIndex]->form);
	free(container->enemyList[listIndex]);
	if(listIndex != container->enemySize - 1){
		int i;
		for (i = listIndex+1; i < container->enemySize; i++){
			container->enemyList[i-1] = container->enemyList[i];
		}
	}
	container->enemySize -= 1;
}
