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
	printf("finished with setUpLCDDriver\n");
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

int redraw_square(Form *form){
	printf("Entered redraw_square...\n");
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

int draw(Form* form){
	if (form->formType == SQUARE){
		draw_square(form->x, form->y, form->radius, form->red, form->green, form->blue);
	} //Else if other forms
}
