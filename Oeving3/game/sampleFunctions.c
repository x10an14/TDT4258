#include "stdio.h"

/* Project includes */
#include "include/sampleStructs.h"
#include "include/listsAndConstants.h"
#include "include/prototypes.h"


void insertPlayers(Objects *container, int amountOfPlayers){
	Player **List = (Player**) malloc(sizeof(Player*)*2);
	printf("no segfault\n");
	int i;
	for(i = 0; i < amountOfPlayers; i++){
		printf("still no segfault\n");
		List[i] = malloc(sizeof(Player));
		List[i]->health = 250; List[i]->healthMax = 250;
		List[i]->form = (Form*) malloc(sizeof(Form));
		int radius = 16;
		List[i]->form->radius = radius;
		List[i]->form->x = 150; List[i]->form->y = SCREEN_HEIGHT-(radius/2)-4;
		List[i]->form->dx = 0; List[i]->form->dy = -5;
		List[i]->form->formType = SQUARE;
		List[i]->form->red = 0; List[i]->form->blue = 253;
		List[i]->form->green = 0;
		printf("going to draw form, yet no segfault\n");
		draw(List[i]->form);
	}
	container->playerList = List;
	container->playerSize = amountOfPlayers;
	container->playerMax = 2;
}

void insertShot(Objects *container, int startX, int startY, int damage){

}

void insertFirstEnemy(Objects *container){
	Enemy **List = malloc(sizeof(Enemy*));
	List[1] = malloc(sizeof(Enemy));

	List[0]->health = 75; List[0]->healthMax = 75;
	Form *form = malloc(sizeof(Form));
	int radius = 10;
	form->radius = radius;
	form->x = radius + 10;
	form->y = radius + 10;
	form->dx = 0;
	form->dy = 0;
	form->formType = SQUARE;
	form->red = 255; form->blue = 0;
	form->green = 0;
	List[0]->form = form;
	draw(List[0]->form);

	container->enemyList = List;
	container->enemyMax = 1;
	container->enemySize = 1;
}

void insertOneEnemy(Objects *container, int startX, int startY, int health){
	if(container->enemySize == container->enemyMax){
		container->enemyList = (Enemy**) realloc(container->enemyList, 2*container->enemyMax*sizeof(Enemy*));
	}

}
