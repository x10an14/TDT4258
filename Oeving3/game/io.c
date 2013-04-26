//Whatever includes we need to utilize our drivers.
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

FILE* buttonsDriver;
FILE* ledDriver;

int buttonStatus;

int initButtons(){
	buttonsDriver = (FILE*) fopen("/dev/swdriver","r+");
	fclose(buttonsDriver);
	return 0;
}

char pullButtonsState(){
	char buff[2];

	printf("ButtonState:\nbuttonsDriver = %d, buff = %s, buttonStatus = %d\n", 
		buttonsDriver, buff, buttonStatus);
				usleep(100000);
	//printf("segdault check 782\n");
	//			usleep(100000);
	FILE* bD;
	bD = (FILE*) fopen("/dev/swdriver","r+");
	printf("buttonfriver is %d\n", bD);

	//printf("segdault check 783\n");
				usleep(100000);
	fread(buff, 1, 2, bD);
	//usleep(20000);
	sscanf(buff, "%x", &buttonStatus);
	printf("segdault check 784 %x\n", buttonStatus);
	fclose(bD);
	return buttonStatus;	
}
int isButtonDown(int buttonNumber){
	int button;
	button = (buttonStatus >> buttonNumber) & 1;
	if (button)
		return 0;
	else
		return 1;
}
int lightLeds(int leds){ 
	ledDriver = (FILE*) fopen("/dev/leddriver","w");
	char buff[3];
	sprintf(buff, "%x\0", leds);
	fprintf(ledDriver, "%x", leds);
	printf("%s", buff);
	fclose(ledDriver);
	//printf("print to leddriver returns %d\n", fputs(buff, ledDriver));
	//fputc(leds, ledDriver);
	return 1;
}