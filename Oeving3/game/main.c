#include "stdio.h"
#include "linux/soundcard.h" //For sound

/* Project include files */
#include "include/listsAndConstants.h"
#include "include/sampleStructs.h"


#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<errno.h>
#include<unistd.h>

static char background_red = 15;
static char background_green = 225;
static char background_blue = 15;

int draw_background(FILE* screen, char red, char green, char blue){
	int addr = 0;
	fseek(screen, 0, 0);
	while(addr < SCREEN_WIDTH*SCREEN_HEIGHT*3){
		fputc(blue, screen);
		fputc(green, screen);
		fputc(red, screen);
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

int main(){
	//short result = -1;
	//printf("Initializing game...\n");

	/* Initialize screen through io.s function A */
	//result = A();
	//if(!result){
	//	printf("A() had following error code: %d\n", result);
	//	return result;
	//}

	/* Initialize drivers through io.s function B(C?) */
	//result = B();
	//if(!result){
	//	printf("B() had following error code: %d\n", result);
	//	return result;
	//}

	/* Initialize structs */

	/* Give structs to engine to play with */

	/* Infinite while to receive events from drivers? And send inputs to gameEngine? */


	FILE* lcdDriver = fopen("/dev/fb0", "r+");
	//FILE* testFile = fopen("/usr/src/testRead", "r");
	draw_background(lcdDriver, background_red, background_green, background_blue);

	printf("hello world, file: %d errno %s\n", lcdDriver, strerror(errno));

	player playerOne;
		playerOne.playerX = 150;
		playerOne.playerY = 220;
		playerOne.dx = 6;
		playerOne.dy = 0;
		playerOne.radius = 15;
		playerOne.col_red = 0;
		playerOne.col_blue = 0;
		playerOne.col_green = 0;

	while(1){
		usleep(100000);
		
		make_new_frame(lcdDriver, &playerOne);
	}


	return 0;
}
