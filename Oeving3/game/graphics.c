//Whatever includes we need to utilize our screen...
#include <stdio.h>
#include "listsAndConstants.h"
#include "sampleStructs.h"

static char background_red = 15;
static char background_green = 225;
static char background_blue = 15;

int draw_background(FILE* screen){
	int addr = 0;
	fseek(screen, 0, 0);
	while(addr < SCREEN_WIDTH*SCREEN_HEIGHT*3){
		fputc(background_blue, screen);
		fputc(background_green, screen);
		fputc(background_red, screen);
		addr+=3;
	}
	return 1;
}

int draw_square(FILE* screen, int x, int y, int radius, char red, char green, char blue){
	int file_Y, file_X;
	for (file_Y = (y-radius)*SCREEN_WIDTH*3 ; file_Y < (y+radius)*SCREEN_WIDTH*3 ; file_Y+=SCREEN_WIDTH*3){
		file_X = (x-radius)*3;
		fseek(screen, file_Y+file_X, 0);
		while (file_X < (x+radius)*3){
			fputc(blue, screen);
			fputc(green, screen);
			fputc(red, screen);
			file_X+=3;
		}
	}
}

int redraw_player(FILE* screen, player* thePlayer){
	draw_square(screen, thePlayer->playerX, thePlayer->playerY, thePlayer->radius, background_red, background_green, background_blue);
	thePlayer->playerX += thePlayer->dx;
	if ((thePlayer->playerX + thePlayer->dx > SCREEN_WIDTH - thePlayer->radius) || (thePlayer->playerX + thePlayer->dx < 0+thePlayer->radius)){
		thePlayer->dx = -thePlayer->dx;
	} else
		thePlayer->playerY += thePlayer->dy;
	draw_square(screen, thePlayer->playerX, thePlayer->playerY, thePlayer->radius, thePlayer->col_red, thePlayer->col_green, thePlayer->col_blue);
}

int make_new_frame(FILE* screen, player* thePlayer){
	//int dRed = 2;
	//int dGreen = -2;

	//if ((background_red < 240) && (background_red > 5) && (background_green < 240) && (background_green > 5)){
	//	background_red+=dRed;
	//	background_green+=dGreen;
	//} else {
	//	dRed = -dRed;
	//	dGreen = -dGreen;
	//	background_red+=dRed;
	//	background_green+=dGreen;
	//}
	redraw_player(screen, thePlayer);

	//draw_background(screen, background_red, background_green, background_blue);
	return 0;
}

void generateMap(FILE *lcdDriver){

}
