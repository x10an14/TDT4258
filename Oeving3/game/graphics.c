//Whatever includes we need to utilize our screen...
#include <stdio.h>
#include <errno.h>

/* Project includes */
#include "include/listsAndConstants.h"
#include "include/sampleStructs.h"

/* Graphics's global variables: */
char background_red = 15;
char background_green = 225;
char background_blue = 15;
FILE *screen;

void setUpLCDDriver(){
	screen = (FILE*) fopen("/dev/fb0","r+");
	printf("Opened screen file: %d errno %s?22\n", screen, strerror(errno));
	draw_background();
}

int draw_background(){
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

int putPixel(FILE* screen, char red, char green, char blue){
	fputc(blue, screen);
	fputc(green, screen);
	fputc(red, screen);
	return 1;
}

int draw_square(int x, int y, int radius, char red, char green, char blue){
	int file_Y, file_X;
	for (file_Y = (y-radius)*SCREEN_WIDTH*3 ; file_Y < (y+radius)*SCREEN_WIDTH*3 ; file_Y+=SCREEN_WIDTH*3){
		file_X = (x-radius)*3;
		fseek(screen, file_Y+file_X, 0);
		while (file_X < (x+radius)*3){
			putPixel(screen, red, green, blue);
			file_X+=3;
		}
	}
	return 1;
}

int redraw_square(Form* form){
	if (form->formType == SQUARE){
		if (form->dx != 0 && form->dy == 0){

		} else if  (form->dx == 0 && form->dy != 0){
			int file_X, file_Y;
			if (form->dy > 0){
				for (file_Y = SCREEN_WIDTH*3*(form->y - form->radius) ; file_Y < SCREEN_WIDTH*3*(form->y - form->radius + form->dy) ; file_Y += SCREEN_WIDTH*3){
					file_X = (form->x - form->radius)*3;
					fseek(screen, file_Y + file_X, 0);
					while (file_X < (form->x+form->radius)*3)				{
						putPixel(screen, background_red, background_green, background_blue);
						file_X+=3;
					}
				}
				for (file_Y = SCREEN_WIDTH*3*(form->y + form->radius) ; file_Y < SCREEN_WIDTH*3*(form->y + form->radius + form->dy) ; file_Y += SCREEN_WIDTH*3){
					file_X = (form->x - form->radius)*3;
					fseek(screen, file_Y + file_X, 0);
					while (file_X < (form->x+form->radius)*3)				{
						putPixel(screen, form->red, form->green, form->blue);
						file_X+=3;
					}
				}
			} else {
				for (file_Y = SCREEN_WIDTH*3*(form->y + form->radius) ; file_Y > SCREEN_WIDTH*3*(form->y + form->radius + form->dy) ; file_Y -= SCREEN_WIDTH*3){
					file_X = (form->x - form->radius)*3;
					fseek(screen, file_Y + file_X, 0);
					while (file_X < (form->x+form->radius)*3)				{
						putPixel(screen, background_red, background_green, background_blue);
						file_X+=3;
					}
				}
				for (file_Y = SCREEN_WIDTH*3*(form->y - form->radius) ; file_Y > SCREEN_WIDTH*3*(form->y - form->radius + form->dy) ; file_Y -= SCREEN_WIDTH*3){
					file_X = (form->x - form->radius)*3;
					fseek(screen, file_Y + file_X, 0);
					while (file_X < (form->x+form->radius)*3)				{
						putPixel(screen, form->red, form->green, form->blue);
						file_X+=3;
					}
				}
			}

		} else if  (form->dx == 0 && form->dy == 0){

		}else
			printf("UNIMPLEMENTED?23\n");
	} else
		printf("UNIMPLEMENTED?22\n");
	return 1;
}

int increment_coordinates(Form* form, int check){
	short successX, successY;
	if (form->x + form->dx + form->radius < SCREEN_WIDTH && form->x + form->dx - form->radius > 0){
		if (!check)
			form->x += form->dx;
		successX = 1;
	} else {
		//form->x += form->dx;
		successX = 0;
	}

	if (form->y + form->dy + form->radius < SCREEN_HEIGHT && form->y + form->dy - form->radius > 0){
		if (!check)
			form->y += form->dy;
		successY = 1;
	} else {
		successY = 0;
		//form->y += form->dy;
	}
	return successY && successX;
}


int draw(Form* form){
	printf("radius:%d\nfx:%d y:%d\nblue:%d\n", form->radius, form->x, form->y, form->blue );
	if (form->formType == SQUARE)
		draw_square(form->x, form->y, form->radius, form->red, form->green, form->blue);
	return 1;
}

int movePlayer(Player* thePlayer){
	if (thePlayer->form->formType == SQUARE){
		if (increment_coordinates(thePlayer->form, 1)){
			redraw_square(thePlayer->form);
			increment_coordinates(thePlayer->form, 0);
		} else {
			printf("increment_coord returned false, stopping object\n");
			thePlayer->form->dx = 0;
			thePlayer->form->dy = 0;
			draw(thePlayer->form);
		}
	} else
		printf("UNIMPLEMENTED?11\n");
}

void make_new_frame(Objects* container){
	movePlayer(container->playerList[0]);
}

