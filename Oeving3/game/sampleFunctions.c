#include "stdio.h"

/* Project includes */
#include "include/sampleStructs.h"

/* Prototypes */
void insertPlayers(Objects *container, int amountOfPlayers);
void insertEnemies(Objects *container, int amountOfEnemies);
void insertShot(Objects *container, int x, int y, int damage, int radius);


void insertPlayers(Objects *container, int amountOfPlayers){
	Player **List = malloc(sizeof(Player*) * amountOfPlayers);
	int i;
	for(i = 0; i < amountOfPlayers; i++){
		List[i] = malloc(sizeof(Player));
		List[i]->playerX = 150; List[i]->playerY = 220;
		List[i]->dx = 6; List[i]->dy = 0;
		List[i]->radius = 15;
		List[i]->col_red = 0; List[i]->col_blue = 0;
		List[i]->col_green = 0;
	}
	container->playerList = List;
	container->playerSize = amountOfPlayers;
}


