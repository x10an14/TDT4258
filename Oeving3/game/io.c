//Whatever includes we need to utilize our drivers.
#include <stdio.h>
#include <errno.h>

FILE* buttonsDriver;
FILE* ledDriver;

int buttonStatus;

char pullButtonsState(){
	buttonsDriver = (FILE*) fopen("/dev/swdriver","r+");
	char buff[3];
	fgets(buff, 3, buttonsDriver);
	fclose(buttonsDriver);
	sscanf(buff, "%x\n", &buttonStatus);
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