#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<errno.h>
#include<TIME.H>

static char background_red = 0;
static char background_green = 240;
static char background_blue = 0;


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
int make_new_frame(FILE* screen){
	if (background_red < 240)
		background_red+=5;
	if (background_green > 5)
		background_green-=5;
	draw_background(screen, background_red, background_green, background_blue);
}

int main (){
	player playerOne;
	playerOne.x = 50;
	playerOne.y = 50;
	playerOne.dx = 0;
	playerOne.dy = 1;

	FILE* lcdDriver = fopen("/dev/fb0", "r+");
	//FILE* testFile = fopen("/usr/src/testRead", "r");
	draw_background(lcdDriver, 0, 100, 100);

	printf("hello world, file: %d errno %s\n", lcdDriver, strerror(errno));

	while(1){
		sleep(500);
		make_new_frame(lcdDriver);
	}



	return 0;
}