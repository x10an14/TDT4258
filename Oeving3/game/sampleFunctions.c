#include "stdio.h"

/* Project includes */
#include "include/sampleStructs.h"
#include "include/prototypes.h"


void insertPlayers(Objects *container, int amountOfPlayers){
	Player **List = malloc(sizeof(Player*) * amountOfPlayers);
	int i;
	for(i = 0; i < amountOfPlayers; i++){
		List[i] = malloc(sizeof(Player));
		List[i]->form = (Form*) malloc(sizeof(Form));
		List[i]->form->x = 150; List[i]->form->y = 150;
		List[i]->form->dx = 0; List[i]->form->dy = -5;
		List[i]->form->radius = 15;
		List[i]->form->formType = SQUARE;
		List[i]->form->red = 0; List[i]->form->blue = 0;
		List[i]->form->green = 0;
	}
	container->playerList = List;
	container->playerSize = amountOfPlayers;
}


